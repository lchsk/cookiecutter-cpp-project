#include <gtest/gtest.h>

TEST(Test{{cookiecutter.project_name|capitalize}}, {{cookiecutter.project_name|lower}}) {
    ASSERT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
