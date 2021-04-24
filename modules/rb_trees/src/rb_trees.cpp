// Copyright 2021 Zaitsev Andrey

#include "../include/rb_trees.h"

Node::Node(int _value, bool _color, Node* _left, Node* _right, Node* _parent) {
    value = _value;
    color = _color;
    left = _left;
    right = _right;
    parent = _parent;
}

Node::Node(const Node& node) {
    value = node.value;
    color = node.color;
    left = node.left;
    right = node.right;
    parent = node.parent;
}

Node& Node::operator=(const Node& node) {
    value = node.value;
    color = node.color;
    left = node.left;
    right = node.right;
    parent = node.parent;

    return *this;
}

bool Node::operator==(const Node& node) {
    if (value == node.value && left == node.left && right == node.right
        && parent == node.parent && color == node.color)
        return true;

    return false;
}

bool Node::operator!=(const Node& node) {
    return !(*this == node);
}

std::ostream& operator<<(std::ostream& out, const Node& node) {
    out << "Node(" << node.value << ", " << node.color << ")";
    return out;
}
