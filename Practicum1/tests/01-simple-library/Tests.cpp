//
// Created by akhtyamovpavel on 5/1/20.
//

#include "Tests.h"
#include "Prac.h"

TEST_F(TestAutomat, main_test1) {
    ASSERT_TRUE(solve("ab+c.aba.*.bac.+.+*", "babc") == 3);
}

TEST_F(TestAutomat, main_test2) {
    ASSERT_TRUE(solve("acb..bab.c.*.ab.ba.+.+*a.", "abbaa") == 5);
}