#include "Tests.h"
#include "Prac.h"

TEST_F(TestAutomat, basic_1) {
    ASSERT_TRUE(solve("ab+c.aba.*.bac.+.+*", "babc") == 3);
}

TEST_F(TestAutomat, basic_2) {
    ASSERT_TRUE(solve("acb..bab.c.*.ab.ba.+.+*a.", "abbaa") == 5);
}

TEST_F(TestAutomat, test_1) {
    Automat automat_a({'a', 'b'});
    Automat automat_b({'a', 'b'});
    automat_a.add_edge(0, 1, 'a');
    automat_b.add_edge(0, 1, 'b');
    unite(automat_a, automat_b);

    Automat automat_ans({'a', 'b'});
    automat_ans.add_edge(0, 1, 'a');
    automat_ans.add_edge(0, 2, 'b');

    ASSERT_TRUE(automat_a == automat_ans);
}

TEST_F(TestAutomat, test_2) {
    Automat automat_a(1, 0, {'a', 'b'});
    Automat automat_b(2, 1, {'a', 'b'});
    automat_a.add_edge(0, 0, 'a');
    automat_b.add_edge(0, 1, 'b');
    unite(automat_a, automat_b); 
    Automat automat_ans({'a', 'b'});
    automat_ans.add_edge(0, 0, 'a');
    automat_ans.add_edge(0, 1, 'b');
    automat_ans.make_terminal(0);
    automat_ans.make_terminal(1);
    ASSERT_TRUE(automat_a == automat_ans);
}

TEST_F(TestAutomat, test_3) {
    Automat automat_a(2, 1, {'a', 'b'});
    Automat automat_b(4, 3, {'a', 'b'});
    automat_a.add_edge(1, 1, 'a');
    automat_a.add_edge(0, 1, 'a');

    automat_b.add_edge(0, 1, 'b');
    automat_b.add_edge(1, 2, 'b');
    automat_b.add_edge(1, 3, 'b');
    unite(automat_a, automat_b);
    Automat automat_ans({'a', 'b'});
    automat_ans.add_edge(0, 1, 'a');
    automat_ans.add_edge(0, 2, 'b');
    automat_ans.add_edge(1, 1, 'a');
    automat_ans.add_edge(2, 3, 'b');
    automat_ans.add_edge(2, 4, 'b');
    automat_ans.make_terminal(1);
    automat_ans.make_terminal(4);
    ASSERT_TRUE(automat_a == automat_ans);    
}

TEST_F(TestAutomat, test_4) {
    Automat automat_a(2, 1, {'a', 'b'});
    Automat automat_b(2, 1, {'a', 'b'});
    automat_a.add_edge(0, 1, 'a');
    automat_b.add_edge(0, 1, 'b');
    unite(automat_a, automat_b);

    Automat automat_ans({'a', 'b'});
    automat_ans.add_edge(0, 1, 'a');
    automat_ans.add_edge(0, 2, 'b');
    automat_ans.make_terminal(1);
    automat_ans.make_terminal(2);

    ASSERT_TRUE(automat_a == automat_ans);
}

TEST_F(TestAutomat, test_5) {
    Automat automat_a(2, 1, {'a', 'b'});
    Automat automat_b(2, 1, {'a', 'b'});
    automat_a.add_edge(0, 1, 'a');
    automat_b.add_edge(0, 1, 'b');
    ASSERT_FALSE(automat_a == automat_b);
}

TEST_F(TestAutomat, test_6) {
    Automat automat_a(2, 1, {'a', 'b'});
    Automat automat_b(2, 0, {'a', 'b'});
    automat_a.add_edge(0, 1, 'a');
    automat_b.add_edge(0, 1, 'a');
    ASSERT_FALSE(automat_a == automat_b);
}

TEST_F(TestAutomat, test7) {
    Automat automat_a(2, 1, {'a', 'b'});
    Automat automat_b(2, 0, {'a', 'b'});
    automat_a.add_edge(0, 1, 'a');
    automat_b.add_edge(0, 1, 'b');
    unite(automat_a, automat_b);

    Automat automat_ans({'a', 'b'});
    automat_ans.add_edge(0, 1, 'a');
    automat_ans.add_edge(0, 2, 'b');
    automat_ans.make_terminal(0);
    automat_ans.make_terminal(1);

    ASSERT_TRUE(automat_a == automat_ans);
}

TEST_F(TestAutomat, test8) {
    Automat automat_a(2, 0, {'a', 'b'});
    Automat automat_b(2, 0, {'a', 'b'});
    automat_a.add_edge(0, 1, 'a');
    automat_b.add_edge(0, 1, 'b');
    unite(automat_a, automat_b);

    Automat automat_ans({'a', 'b'});
    automat_ans.add_edge(0, 1, 'a');
    automat_ans.add_edge(0, 2, 'b');
    automat_ans.make_terminal(0);

    ASSERT_TRUE(automat_a == automat_ans);
}

TEST_F(TestAutomat, test9) {
    Automat automat_a(1, 0, {'a', 'b'});
    star(automat_a);
    Automat automat_ans({'a','b'});
    automat_ans.add_edge(0, 1, '1');
    automat_ans.add_edge(1, 0, '1');
    automat_ans.make_terminal(0);
    ASSERT_TRUE(automat_a == automat_ans);
}

TEST_F(TestAutomat, test10) {
    Automat automat_a({'a', 'b'});
    automat_a.add_edge(0, 1, 'a');
    star(automat_a);

    Automat automat_ans({'a', 'b'});
    automat_ans.add_edge(0, 1, '1');
    automat_ans.add_edge(1, 2, 'a');
    automat_ans.make_terminal(0);
    ASSERT_TRUE(automat_a == automat_ans);
}

TEST_F(TestAutomat, test11) {
    Automat automat_a({'a', 'b'});
    automat_a.add_edge(0, 1, 'a');
    automat_a.add_edge(0, 2, 'b');
    automat_a.make_terminal(1);
    star(automat_a);

    Automat automat_ans({'a', 'b'});
    automat_ans.add_edge(0, 1, '1');
    automat_ans.add_edge(1, 2, 'a');
    automat_ans.add_edge(1, 3, 'b');
    automat_ans.add_edge(2, 0, '1');
    automat_ans.make_terminal(0);
    ASSERT_TRUE(automat_a == automat_ans);
}

TEST_F(TestAutomat, test12) {
    Automat automat_a({'a', 'b'});
    Automat automat_b({'a', 'b'});
    concatenation(automat_a, automat_b);
    Automat automat_ans({'a', 'b'});
    ASSERT_TRUE(automat_ans == automat_a);
}

TEST_F(TestAutomat, test13) {
    Automat automat_a({'a', 'b'});
    Automat automat_b({'a', 'b'});
    automat_a.add_edge(0, 1, 'a');
    automat_a.add_edge(0, 2, 'b');
    automat_a.make_terminal(1);

    automat_b.add_edge(0, 1, 'a');
    automat_b.make_terminal(1);

    concatenation(automat_a, automat_b);

    Automat automat_ans({'a', 'b'});
    automat_ans.add_edge(0, 1, 'a');
    automat_ans.add_edge(0, 2, 'b');
    automat_ans.add_edge(1, 3, '1');
    automat_ans.add_edge(3, 4, 'a');
    automat_ans.make_terminal(4);
    ASSERT_TRUE(automat_a == automat_ans);
}

TEST_F(TestAutomat, test14) {
    Automat automat_a({'a', 'b'});
    Automat automat_b({'a', 'b'});
    automat_a.add_edge(0, 0, 'a');
    automat_b.add_edge(0, 0, 'b');
    automat_a.make_terminal(0);

    concatenation(automat_a, automat_b);

    Automat automat_ans({'a', 'b'});
    automat_ans.add_edge(0, 0, 'a');
    automat_ans.add_edge(0, 1, '1');
    automat_ans.add_edge(1, 1, 'b');

    ASSERT_TRUE(automat_a == automat_ans);
}

TEST_F(TestAutomat, test15) {
    Automat automat_a({'a', 'b'});
    automat_a.add_edge(0, 1, '1');
    automat_a.add_edge(0, 3, '1');
    automat_a.add_edge(1, 2, 'a');
    automat_a.add_edge(3, 4, 'b');
    automat_a.make_terminal(2);

    automat_a.delete_empty_edges();

    Automat automat_ans({'a', 'b'});
    automat_ans.add_edge(0, 2, 'a');
    automat_ans.add_edge(0, 4, 'b');
    automat_ans.add_edge(1, 2, 'a');
    automat_ans.add_edge(3, 4, 'b');
    automat_ans.make_terminal(2);
    ASSERT_TRUE(automat_a == automat_ans);
}

TEST_F(TestAutomat, test16) {
    Automat automat_a({'a', 'b'});
    automat_a.add_edge(0, 0, '1');
    automat_a.add_edge(0, 1, 'a');
    
    automat_a.delete_empty_edges();
    Automat automat_ans({'a', 'b'});
    automat_ans.add_edge(0, 1, 'a');
    ASSERT_TRUE(automat_a == automat_ans);
}

TEST_F(TestAutomat, test17) {
    Automat automat_a({'a', 'b'});
    automat_a.add_edge(0, 1, 'a');
    automat_a.add_edge(1, 2, 'a');
    automat_a.add_edge(0, 3, 'b');
    automat_a.add_edge(0, 4, 'b');
    automat_a.add_edge(1, 1, '1');

    automat_a.delete_empty_edges();
    Automat automat_ans({'a', 'b'});
    automat_ans.add_edge(0, 1, 'a');
    automat_ans.add_edge(0, 3, 'b');
    automat_ans.add_edge(0, 4, 'b');
    automat_ans.add_edge(1, 2, 'a');
    ASSERT_TRUE(automat_a == automat_ans);
}

TEST_F(TestAutomat, test18) {
    Automat automat_a({'a', 'b'});
    automat_a.add_edge(0, 1, 'a');
    automat_a.add_edge(0, 2, 'b');
    automat_a.add_edge(1, 1, 'a');
    automat_a.add_edge(2, 3, 'a');
    automat_a.add_edge(3, 1, 'a');
    automat_a.add_edge(3, 3, 'b');
    automat_a.make_terminal(3);
    automat_a.make_terminal(2);
    
    ASSERT_TRUE(automat_a == automat_a.DFA());
}

TEST_F(TestAutomat, test19) {
    Automat automat_a({'a', 'b'});
    automat_a.add_edge(0, 1, 'a');
    automat_a.add_edge(1, 2, 'b');
    automat_a.add_edge(0, 3, 'a');
    automat_a.add_edge(3, 2, 'b');
    automat_a.make_terminal(2);    

    Automat automat_ans({'a', 'b'});
    automat_ans.add_edge(0, 1, 'a');
    automat_ans.add_edge(1, 2, 'b');
    automat_ans.make_terminal(2);
    ASSERT_TRUE(automat_a.DFA() == automat_ans);
}

TEST(Test_prac, test_solve2) {
    std::string regex = "b*";
    std::string word = "acacacccaccacacacacacacaca";
    ASSERT_EQ(solve(regex, word), 0);
}

TEST(Test_prac, test_solve1) {
    std::string regex = "ac+*";
    std::string word = "aaa..c.b*.c.";
    ASSERT_EQ(solve(regex, word), 3);
}