#include "AbstractTest.h"

using namespace ttp;

class ItemTest : public AbstractTest {
};


TEST(ItemTest, Constructor) {
    ttp::Item i(2,3);
    EXPECT_EQ(2, i.getValue());
    EXPECT_EQ(3, i.getWeight());
}

TEST(ItemTest, StreamOperator) {
    ttp::Item i(2,3);
    std::stringstream ss;
    ss << i;
    std::string s = ss.str();
    EXPECT_EQ("{value:2,weight:3}", s);
}


