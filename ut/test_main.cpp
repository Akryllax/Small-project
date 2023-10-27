#include <gtest/gtest.h>

TEST(ExampleTest, SampleTest) {
    ASSERT_TRUE(true);
    std::cout << "Hello, test!" << std::endl;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
