#include <gtest/gtest.h>
#include "interpret.hpp"
#include <strstream>
#include <limits>

using namespace std;
using abit::interpret;

TEST(interp_base, empty)
{
    string empty;
    stringstream serr;

    const auto result = interpret(begin(empty), end(empty), serr);
    ASSERT_FALSE(result);
}

TEST(interp_base, add)
{
    string in("add(12,13)");
    stringstream serr;

    const auto result = interpret(begin(in), end(in), serr);
    ASSERT_TRUE(result.is_initialized());
    ASSERT_EQ(result.get(), 25);
}

TEST(interp_base, mult)
{
    string in("mult(45,10)");
    stringstream serr;

    const auto result = interpret(begin(in), end(in), serr);
    ASSERT_TRUE(result.is_initialized());
    ASSERT_EQ(result.get(), 450 );
}

TEST(interp_base, sub)
{
    string in("sub(16,32)");
    stringstream serr;

    const auto result = interpret(begin(in), end(in), serr);
    ASSERT_TRUE(result.is_initialized());
    ASSERT_EQ(result.get(), -16);
}

TEST(interp_base, div)
{
    string in("div(16,3)");
    stringstream serr;

    const auto result = interpret(begin(in), end(in), serr);
    ASSERT_TRUE(result.is_initialized());
    ASSERT_EQ(result.get(), 5);
}

TEST(interp_base, max_int)
{
    const auto max_int = numeric_limits<int>::max();
    string max_str = to_string(max_int);

    string in("sub("+max_str+",1)");
    stringstream serr;

    const auto result = interpret(begin(in), end(in), serr);
    ASSERT_TRUE(result.is_initialized());
    ASSERT_EQ(result.get(), max_int-1);
}

TEST(interp_base, min_int)
{
    const auto min_int = numeric_limits<int>::min();
    string min_str = to_string(min_int);

    string in("add(" + min_str + ",1)");
    stringstream serr;

    const auto result = interpret(begin(in), end(in), serr);
    ASSERT_TRUE(result.is_initialized());
    ASSERT_EQ(result.get(), min_int + 1);
}

TEST(interp_base, whitespaces)
{
    string in("  add\t  ( 12  ,    13   )    ");
    stringstream serr;

    const auto result = interpret(begin(in), end(in), serr);
    ASSERT_TRUE(result.is_initialized());
    ASSERT_EQ(result.get(), 25);
}

TEST(interp_base, missing_open_parenthesis)
{
    string in("sub 12,13)");
    stringstream serr;

    const auto result = interpret(begin(in), end(in), serr);
    ASSERT_FALSE(result.is_initialized());
}

TEST(interp_base, missing_close_parenthesis)
{
    string in("add(12,13");
    stringstream serr;

    const auto result = interpret(begin(in), end(in), serr);
    ASSERT_FALSE(result.is_initialized());
}

TEST(interp_base, missing_comma)
{
    string in("mul(12 13)");
    stringstream serr;

    const auto result = interpret(begin(in), end(in), serr);
    ASSERT_FALSE(result.is_initialized());
}

TEST(interp_base, division_by_zero)
{
    string in("div(12,0)");
    stringstream serr;

    const auto result = interpret(begin(in), end(in), serr);
    ASSERT_FALSE(result.is_initialized());
}

