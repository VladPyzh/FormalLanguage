#include "Tests.h"
#include "Prac.h"

TEST(Basic_tests, basic_1) {
    ASSERT_TRUE(solve("ab+c.aba.*.bac.+.+*", "babc") == 3);
}

TEST(Basic_tests, basic_2) {
    ASSERT_TRUE(solve("acb..bab.c.*.ab.ba.+.+*a.", "abbaa") == 5);
}

TEST_F(TestAutomat, test_1) {
    Automat automat_a({'a', 'b'});
}