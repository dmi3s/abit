///////////////////////////////////////////////////////////////////////////////
// calculator_grammar_simple.hpp
#ifndef __CALCULATOR_GRAMMAR_SIMPLE_HPP__
#define __CALCULATOR_GRAMMAR_SIMPLE_HPP__

#ifdef _MSC_VER
#pragma once
#endif

#include <stdexcept>
#include <vector>
#include <utility>
#include <iostream>

#pragma warning(push,3)

#define BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_RESULT_OF_USE_DECLTYPE

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/statement.hpp>
#include <boost/phoenix/stl/container/container.hpp>
#include <boost/phoenix/scope/local_variable.hpp>
#include <boost/phoenix/bind/bind_member_function.hpp>
#include <boost/phoenix/scope/let.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>
#include <boost/fusion/container/vector.hpp>

#pragma warning(pop)

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

class symbols_table {
public:
    void push(const std::pair<std::string,int>& local_variable)
    {
        table.push_back(local_variable);
    }
    void pop()
    {
        if (table.empty())
            throw std::runtime_error("trying pop scope from empty table");
        table.pop_back();
    }
    bool lookup(const std::string& name, int& value)
    {
        auto i = find_if(rbegin(table), rend(table), [&name](auto const& el) -> bool { return el.first == name; });
        if (i == rend(table))
            return false;

        value = i->second;
        return true;
    }
private:
    std::vector<std::pair<std::string, int>> table;
};




template <typename Iterator>
struct calculator_interpreter
    : qi::grammar<Iterator, int(), qi::space_type>
{
    calculator_interpreter()
        : calculator_interpreter::base_type(expr)
    {
        using namespace qi;
        using qi::_1;
        using qi::_val;

        expr = add | sub | mult | div | let
            ;

        add = lit("add")   >> '(' >> factor[_val = _1] >> ',' >> factor[_val += _1] >> ')'
            ;

        sub = lit("sub")   >> '(' >> factor[_val = _1] >> ',' >> factor[_val -= _1] >> ')'
            ;

        mult = lit("mult") >> '(' >> factor[_val = _1] >> ',' >> factor[_val *= _1] >> ')'
            ;

        div = lit("div")   >> '(' >> factor[_val = _1] >> ',' >> factor[
                _val = phx::if_else(
                    _1,
                    _val /= _1,
                    (phx::throw_(std::runtime_error("division by zero")), _1)
                )] 
            >> ')'
            ;

        var_declaration = (+qi::alpha >> ',' >> factor)
            ;

        let =
            lit("let") >> '(' 
            >> var_declaration[ phx::bind(&symbols_table::push, phx::ref(stable), qi::_1) ]
            >> ',' >> expr[ qi::_val = qi::_1, phx::bind(&symbols_table::pop, phx::ref(stable)) ]
            >> ')'
        ;

        var_usage =
            qi::as_string[+qi::alpha][qi::_pass = phx::bind(&symbols_table::lookup, phx::ref(stable), qi::_1, qi::_val)]
        ;

        factor =
            qi::int_
            | expr
            | var_usage
        ;
    }

    qi::rule<Iterator, int(), qi::space_type>
        expr,add,sub,mult,div,factor,let,var_usage;

    qi::rule<Iterator, std::pair<std::string, int>(), qi::space_type> var_declaration;

    symbols_table stable;
};


#endif
