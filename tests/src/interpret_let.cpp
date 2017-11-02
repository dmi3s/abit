#include <gtest/gtest.h>
#include "interpret.hpp"
#include <strstream>

using namespace std;
using abit::interpret;

TEST(interp_let, base)
{
    string let{ "let(a,10,add(a,0))" };
    ostringstream serr;

    const auto result = interpret(begin(let), end(let), serr);
    ASSERT_TRUE(result);
    ASSERT_EQ(result, 10);
}

TEST(interp_let, init_expression)
{
    string let{ "let(a,mult(5,2),add(a,17))" };
    ostringstream serr;

    const auto result = interpret(begin(let), end(let), serr);
    ASSERT_TRUE(result);
    ASSERT_EQ(result, 27);
}


TEST(interp_let, inner_scope)
{
    string let{ "let(a,10,add(a,let(a,2,mult(a,2))))" };
    ostringstream serr;

    const auto result = interpret(begin(let), end(let), serr);
    ASSERT_TRUE(result);
    ASSERT_EQ(result, 14);
}

TEST(interp_let, outer_scope)
{
    string let{ 
        "let(a,10,"
        "  add("
        "      a"                      // 50
        "      , mult("                // 40
        "         let(a,2, mult(a,2))" // 4
        "        ,a)"
        "      )"
        ")" 
    };

    ostringstream serr;

    const auto result = interpret(begin(let), end(let), serr);
    ASSERT_TRUE(result);
    ASSERT_EQ(result, 50);
}

TEST(interp_let, no_reserved_names)
{
    string let{ "add( div(10,2), let(div, 20, div(div,10)) )" }; //7
    ostringstream serr;

    const auto result = interpret(begin(let), end(let), serr);
    ASSERT_TRUE(result);
    ASSERT_EQ(result, 7);
}
