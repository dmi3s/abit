#include <gtest/gtest.h>
#include "interpret.hpp"
#include <strstream>
#include <array>
#include <utility>

using namespace std;
using abit::interpret;

TEST(interp, from_task)
{
    const array<pair<string, int>,6> examples =
    { {
        {"add(1, 2)"s, 3},
        {"add(1, mult(2, 3))"s, 7},
        {"mult(add(2, 2), div(9, 3))"s, 12},
        {"let(a, 5, add(a, a))"s, 10},
        {"let(a, 5, let(b, mult(a, 10), add(b, a)))"s, 55},
        {"let(a, let(b, 10, add(b, b)), let(b, 20, add(a, b)))"s, 40},
    } };

    ostringstream serr;
    for (auto& ex: examples)
    {
        auto& src = ex.first;
        auto& expected = ex.second;
        auto result = interpret(begin(src), end(src), serr);
        ASSERT_TRUE(result);
        ASSERT_EQ(result, expected);
    }
}