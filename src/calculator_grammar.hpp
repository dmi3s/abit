#pragma once
///////////////////////////////////////////////////////////////////////////////
// calculator_grammar.hpp
#ifndef CALCULATOR_GRAMMAR_HPP__
#define CALCULATOR_GRAMMAR_HPP__

#include <stdexcept>

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

#include "symbol_table.hpp"


namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

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

        let =
            lit("let")     >> '(' 
            >> var_declaration[ phx::bind(&symbols_table::push, phx::ref(stable), _1) ]
            >> ',' >> expr[ _val = _1, phx::bind(&symbols_table::pop, phx::ref(stable)) ]
            >> ')'
        ;

        var_declaration = (+alpha >> ',' >> factor)
            ;

        variable =
            qi::as_string[+alpha][_pass = phx::bind(&symbols_table::lookup, phx::ref(stable), _1, _val)]
        ;

        factor =
            qi::int_
            | expr
            | variable
        ;
    }

    qi::rule<Iterator, int(), qi::space_type>
        expr, add, sub, mult, div, let
        , factor, variable;

    qi::rule<Iterator, std::pair<std::string, int>(), qi::space_type> 
        var_declaration;

    symbols_table stable;
};


#endif
