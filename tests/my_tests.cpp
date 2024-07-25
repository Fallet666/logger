//
// Created by user on 25.07.2024.
//
#include <gtest/gtest.h>


TEST(SampleTest, Example) {
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
