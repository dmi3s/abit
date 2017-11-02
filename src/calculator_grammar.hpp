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
#include <boost/phoenix/bind/bind_member_function.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>
//#include <boost/bind.hpp>
#pragma warning(pop)

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;
namespace phx = boost::phoenix;

class symbols_table {
public:
    void push(const std::pair<std::string, int>& local_variable)
    {
        table.push_back(local_variable);
    }
    void pop() // can throw
    {
        if (table.empty())
            throw std::runtime_error("trying pop scope from empty table");
        table.pop_back();
    }
    int  get_value(const std::string& name) // can throw
    {
        auto i = find_if(rbegin(table), rend(table), [&name](auto const& el) -> bool { return el.first == name; });
        if (i == rend(table))
            throw std::runtime_error("failed to find variable " + name);
        return i->second;
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
        expr = 
            add[qi::_val = qi::_1]
            | sub[qi::_val = qi::_1]
            | mult[qi::_val = qi::_1]
            | div[qi::_val = qi::_1]
            | let[qi::_val = qi::_1]
            ;

        add =
            qi::lit("add") >> '('
            >> factor[qi::_val = qi::_1] >> ','
            >> factor[qi::_val += qi::_1]
            >> ')'
            ;
        sub =
            "sub" >> qi::lit('(')
            >> factor[qi::_val = qi::_1] >> ','
            >> factor[qi::_val -= qi::_1]
            >> ')'
            ;
        mult =
            "mult" >> qi::lit('(')
            >> factor[qi::_val = qi::_1] >> ','
            >> factor[qi::_val *= qi::_1]
            >> ')'
            ;
        div =
            "div" >> qi::lit('(')
            >> factor[qi::_val = qi::_1] >> ','
            >> factor[
                qi::_val = phx::if_else(
                    qi::_1,
                    qi::_val /= qi::_1,
                    (phx::throw_(std::runtime_error("division by zero")), qi::_1)
                )
            ]
            >> ')'
        ;
        var_decl =
            qi::alpha >> ',' >> expr
        ;
        var_usage =
            expr[qi::_val = qi::_1]
        ;

        let =
            "let" >> qi::lit('(')
            >> var_decl >> ',' >> var_usage[qi::_val = qi::_1]
            >> ')'
        ;

        factor =
            qi::int_[qi::_val = qi::_1]
            | expr[qi::_val = qi::_1];
    }

    qi::rule<Iterator, int(), qi::space_type>
        expr,add,sub,mult,div,factor,var_usage,let;

    qi::rule<Iterator, std::pair<std::string, int>(), qi::space_type> var_decl;

    symbols_table stable;
};


#endif
