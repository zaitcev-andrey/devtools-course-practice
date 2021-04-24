// Copyright 2021 Zaitsev Andrey

#ifndef MODULES_RB_TREES_INCLUDE_RB_TREES_H_
#define MODULES_RB_TREES_INCLUDE_RB_TREES_H_

#include <iostream>

#define RED true
#define BLACK false

struct Node {
    int value;
    bool color;
    Node *left;
    Node *right;
    Node *parent;

    Node(int _value = 0, bool _color = BLACK, Node *_left = nullptr,
        Node *_right = nullptr, Node *_parent = nullptr);
    Node(const Node& node);

    Node& operator=(const Node& node);

    bool operator==(const Node& node);
    bool operator!=(const Node& node);

    friend std::ostream& operator<<(std::ostream& out, const Node& node);
};

#endif  // MODULES_RB_TREES_INCLUDE_RB_TREES_H_
