// Copyright 2021 Zaitsev Andrey

#include <gtest/gtest.h>

#include "include/rb_trees.h"

TEST(RBTreeNodeTest, Create_Node_Default_Constructor) {
    ASSERT_NO_THROW(Node());
}

TEST(RBTreeNodeTest, Create_Node_Copy_Constructor) {
    Node node;

    ASSERT_NO_THROW(Node(node));
}

TEST(RBTreeNodeTest, Assignment_Of_Nodes) {
    Node node1(1), node2(2);

    ASSERT_NO_THROW(node1 = node2);
}

TEST(RBTreeNodeTest, Same_Nodes_Are_Equal) {
    Node node1(1), node2(1);

    ASSERT_TRUE(node1 == node2);
}

TEST(RBTreeNodeTest, Different_Nodes_Are_Not_Equal) {
    Node node1(1), node2(2);

    ASSERT_TRUE(node1 != node2);
}

TEST(RBTreeNodeTest, Print_Node) {
    Node node;

    ASSERT_NO_THROW(std::cout << node << std::endl;);
}
