#include <gtest/gtest.h>

int main()
{
    srand(time(NULL));
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
