#pragma once
///////////////////////////////////////////////////////////////////////////////
// calculator_grammar.hpp
#ifndef CALCULATOR_GRAMMAR_HPP__
#define CALCULATOR_GRAMMAR_HPP__

#include <stdexcept>
#include <ostream>

#pragma warning(push,3)

#define BOOST_SPIRIT_USE_PHOENIX_V3
//#define BOOST_RESULT_OF_USE_DECLTYPE

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/phoenix/object/construct.hpp>
#include <boost/fusion/include/std_pair.hpp>

#pragma warning(pop)

#include "symbol_table.hpp"
namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

template <typename Iterator>
struct calculator_interpreter
    : qi::grammar<Iterator, int(), qi::space_type>
{
    explicit
    calculator_interpreter(std::ostream& errors_stream)
        : calculator_interpreter::base_type(expr, "expr")
        , serr(errors_stream)
    {
        using namespace qi;
        using qi::_1;
        using qi::_2;
        using qi::_3;
        using qi::_4;
        using qi::_val;

        expr %= add | sub | mult | div | let
            ;

        add = lit("add")   > '(' > factor[_val = _1] > ',' > factor[_val += _1] > ')'
            ;

        sub = lit("sub")   > '(' > factor[_val = _1] > ',' > factor[_val -= _1] > ')'
            ;

        mult = lit("mult") > '(' > factor[_val = _1] > ',' > factor[_val *= _1] > ')'
            ;

        div = lit("div")   > '(' > factor[_val = _1] > ',' > factor[
                _val = phx::if_else(
                    _1,
                    _val /= _1,
                    (phx::throw_(std::runtime_error("division by zero")), _1)
                )] 
            > ')'
            ;

        let =
            lit("let")     > '(' 
            > var_declaration[ phx::bind(&symbols_table::push, phx::ref(stable), _1) ]
            > ',' > expr[ _val = _1, phx::bind(&symbols_table::pop, phx::ref(stable)) ]
            > ')'
        ;

        var_declaration = (+alpha > ',' > factor)
            ;

        variable =
            qi::as_string[+alpha][_pass = phx::bind(&symbols_table::lookup, phx::ref(stable), _1, _val)]
        ;

        factor %=
            qi::int_
            | expr
            | variable
        ;

        /// Errors handlign

        expr.name("expr");
        add.name("add");
        sub.name("sub");
        mult.name("mult");
        div.name("div");
        let.name("let");
        factor.name("factor");
        var_declaration.name("var_declaration");
        variable.name("variable");

        on_error<fail>
            (
                expr
                , serr
                << phx::val("Error! Expecting ")
                << _4                               // what failed?
                << phx::val(" here: \"")
                << phx::construct<std::string>(_3, _2)   // iterators to error-pos, end
                << phx::val("\"")
                << std::endl
            );
    }

    qi::rule<Iterator, int(), qi::space_type>
        expr, add, sub, mult, div, let
        , factor, variable;

    qi::rule<Iterator, std::pair<std::string, int>(), qi::space_type> 
        var_declaration;

    symbols_table stable;

    std::ostream& serr;

};

#endif
