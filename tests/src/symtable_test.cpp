#include <gtest/gtest.h>
#include "symbol_table.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(sym_tbl, pop)
{
    symbols_table st;
    st.push({"test",42});
    ASSERT_NO_THROW(st.pop());
}

TEST(sym_tbl, empty_pop)
{
    symbols_table st;
    ASSERT_THROW(st.pop(), std::runtime_error);
}

class sym_tbl_content : public testing::Test {
protected:
    void SetUp()
    {
        table.push({ "first", 13 });
        table.push({ "second", 14 });
        table.push({ "third", 17 });
    }
    void TearDown()
    {
        table = {};
    }
    symbols_table table;
};

TEST_F(sym_tbl_content, lookup_existing)
{
    int value = 666;
    ASSERT_TRUE( table.lookup("second", value) );
    ASSERT_EQ(14, value);
}

TEST_F(sym_tbl_content, lookup_non_existing)
{
    int value = 666;
    ASSERT_FALSE(table.lookup("Second", value));
    ASSERT_EQ(666, value);
}

TEST_F(sym_tbl_content, lookup_inner_scope)
{
    table.push({"first", 42});
    int value = 666;
    ASSERT_TRUE(table.lookup("first", value));
    ASSERT_EQ(42, value);
}

TEST_F(sym_tbl_content, lookup_outer_scope)
{
    table.push({ "second", 42 });
    int value = 666;
    //ASSERT_TRUE(table.lookup("second", value));
    //ASSERT_EQ(42, value);
    table.pop();
    ASSERT_TRUE(table.lookup("second", value));
    ASSERT_EQ(14, value);
}
