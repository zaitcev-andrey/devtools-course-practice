// Copyright 2021 Zaitsev Andrey

#include <gtest/gtest.h>

#include <random>
#include <iostream>
#include <vector>
#include <algorithm>

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

TEST(RBTreeTest, Create_Tree_Default_Constructor) {
    ASSERT_NO_THROW(RBTree());
}

TEST(RBTreeTest, Create_Tree_from_Node) {
    Node *node = new Node();

    ASSERT_NO_THROW(RBTree(node));
}

TEST(RBTreeTest, Create_Tree_from_Vector) {
    std::vector<int> vec = {4, 7, 9};

    ASSERT_NO_THROW(RBTree(vec));
}

TEST(RBTreeTest, Get_Root) {
    Node *node = new Node(5);
    RBTree tree(node);

    ASSERT_EQ(5, tree.getRoot()->value);
}

TEST(RBTreeTest, Get_Current) {
    Node *node = new Node(5);
    RBTree tree(node);

    tree.Begin();

    ASSERT_EQ(5, tree.getCurrent()->value);
}

TEST(RBTreeTest, Get_Nodes_Number) {
    Node *node = new Node(5);
    RBTree tree(node);

    ASSERT_EQ(static_cast<unsigned int>(1), tree.getNodesNumber());
}

TEST(RBTreeTest, Can_Find_Existing_Node) {
    std::vector<int> vec = {-24, 45, 16};
    RBTree tree(vec);

    bool is_found = tree.findNode(45);

    ASSERT_TRUE(is_found);
}

TEST(RBTreeTest, Can_Not_Find_Nonexistent_Node) {
    std::vector<int> vec = {-24, 45, 16};
    RBTree tree(vec);

    bool is_found = tree.findNode(10);

    ASSERT_FALSE(is_found);
}

TEST(RBTreeTest, Can_Insert_New_Node) {
    std::vector<int> vec = {0, 1, 2};
    RBTree tree(vec);

    Node *node = new Node(3);

    ASSERT_NO_THROW(tree.insertNode(node));
}

TEST(RBTreeTest, Can_Not_Insert_Existing_Node) {
    std::vector<int> vec = {0, 1, 2};
    RBTree tree(vec);

    Node *node = new Node(1);

    ASSERT_ANY_THROW(tree.insertNode(node));
}

TEST(RBTreeTest, Can_Remove_Existing_Node) {
    std::vector<int> vec = {0, 1, 2};
    RBTree tree(vec);

    ASSERT_NO_THROW(tree.removeNode(1));
}

TEST(RBTreeTest, Can_Not_Remove_Nonexistent_Node) {
    std::vector<int> vec = {0, 1, 2};
    RBTree tree(vec);

    ASSERT_ANY_THROW(tree.removeNode(3));
}

TEST(RBTreeTest, Removing_All_Nodes_In_a_Tree) {
    std::vector<int> vec = {22, 14, 6, -12, 27, 1, -19};
    RBTree tree(vec);

    for (auto i = vec.begin(); i < vec.end(); i++)
        tree.removeNode(*i);

    ASSERT_EQ(static_cast<unsigned int>(0), tree.getNodesNumber());
}

TEST(RBTreeTest, Create_And_Remove_Node_In_a_Tree) {
    std::vector<int> vec = {3, 5, 7};
    RBTree tree(vec);
    int value = 6;

    tree.add_and_remove(6);

    ASSERT_EQ(static_cast<unsigned int>(3), tree.getNodesNumber());
}

TEST(RBTreeTest, Operations_With_Large_Tree) {
    std::vector<int> vec;

    for (int i = -300; i <= 300; ++i)
        vec.emplace_back(i);

    std::default_random_engine reng(0);
    std::shuffle(vec.begin(), vec.end(), reng);

    RBTree tree(vec);

    auto several_tree_operations = [&tree, &vec, &reng] {
        for (tree.Begin(); !tree.End(); tree.Next())
            Node *node = tree.getCurrent();

        std::shuffle(vec.begin(), vec.end(), reng);

        for (auto i = vec.begin(); i < vec.end(); ++i)
            tree.removeNode(*i);
    };

    ASSERT_NO_THROW(several_tree_operations());
}
