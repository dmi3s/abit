///////////////////////////////////////////////////////////////////////////////
// calculator_grammar_simple.hpp
#ifndef __CALCULATOR_GRAMMAR_SIMPLE_HPP__
#define __CALCULATOR_GRAMMAR_SIMPLE_HPP__

#ifdef _MSC_VER
#pragma once
#endif

#include  <stdexcept>

//#define BOOST_RESULT_OF_USE_DECLTYPE

#pragma warning(push,3)
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/phoenix/statement.hpp>
#pragma warning(pop)

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;
namespace phx = boost::phoenix;

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
            ;

        add =
            "add" >> qi::lit('(')
            >> factor[qi::_val = qi::_1] >> ','
            >> factor[qi::_val += qi::_1]
            >> ')';

        sub =
            "sub" >> qi::lit('(')
            >> factor[qi::_val = qi::_1] >> ','
            >> factor[qi::_val -= qi::_1]
            >> ')';

        mult =
            "mult" >> qi::lit('(')
            >> factor[qi::_val = qi::_1] >> ','
            >> factor[qi::_val *= qi::_1]
            >> ')';

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
            >> ')';

        factor =
            qi::int_[qi::_val = qi::_1]
            | expr[qi::_val = qi::_1];
    }

    qi::rule<Iterator, int(), qi::space_type>
        expr,add,sub,mult,div,factor;

};


#endif
