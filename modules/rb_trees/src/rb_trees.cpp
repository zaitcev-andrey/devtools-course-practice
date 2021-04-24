// Copyright 2021 Zaitsev Andrey

#include <vector>
#include <stack>

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

RBTree::RBTree() {
    NIL = new Node();
    root = NIL;
    current = NIL;
    nodes_number = 0;
    counter = 0;
}

RBTree::RBTree(Node *node) {
    NIL = new Node();
    root = node;
    current = NIL;
    nodes_number = 1;
    counter = 0;

    root->left = NIL;
    root->right = NIL;
    root->parent = NIL;
}

RBTree::RBTree(const std::vector<int>& vec) {
    NIL = new Node();
    root = NIL;
    current = NIL;
    nodes_number = 0;
    counter = 0;

    for (size_t i = 0; i < vec.size(); i++) {
        Node *node = new Node(vec[i]);
        insertNode(node);
    }
}

Node* RBTree::getRoot() const {
    return root;
}

Node* RBTree::getCurrent() const {
    return current;
}

unsigned int RBTree::getNodesNumber() const {
    return nodes_number;
}

bool RBTree::findNode(const int value) {
    current = root;

    while (current != NIL) {
        if (value == current->value)
            return true;
        else if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }

    return false;
}

void RBTree::insertNode(Node *node) {
    if (findNode(node->value))
        throw "Node with this value is already in the tree";

    Node *par = NIL;
    Node *node_place = root;

    while (node_place != NIL) {
        par = node_place;
        if (node->value < node_place->value)
            node_place = node_place->left;
        else
            node_place = node_place->right;
    }

    node->parent = par;

    if (par == NIL)
        root = node;
    else if (node->value < par->value)
        par->left = node;
    else
        par->right = node;

    node->left = NIL;
    node->right = NIL;
    node->color = RED;

    shuffle_for_insert(node);

    nodes_number++;
}

void RBTree::removeNode(const int value) {
    if (!findNode(value))
        throw "There is no node with this value in the tree";

    Node *del_node = current;
    Node *replace_node = current;
    Node *x;

    bool y_original_color = replace_node->color;

    if (del_node->left == NIL) {
        x = del_node->right;
        transplant(del_node, del_node->right);
    } else if (del_node->right == NIL) {
        x = del_node->left;
        transplant(del_node, del_node->left);
    } else {
        replace_node = get_minimum(del_node->right);
        y_original_color = replace_node->color;
        x = replace_node->right;

        if (replace_node->parent == del_node) {
            x->parent = replace_node;
        } else {
            transplant(replace_node, replace_node->right);
            replace_node->right = del_node->right;
            replace_node->right->parent = replace_node;
        }

        transplant(del_node, replace_node);
        replace_node->left = del_node->left;
        replace_node->left->parent = replace_node;
        replace_node->color = del_node->color;
    }

    if (y_original_color == BLACK)
        shuffle_for_remove(x);

    nodes_number--;
}

void RBTree::Begin() {
    while (!node_stack.empty())
        node_stack.pop();

    counter = 0;
    current = root;

    while (current->left != NIL) {
        node_stack.push(current);
        current = current->left;
    }
    node_stack.push(current);
}

bool RBTree::End() const {
    return (counter == nodes_number);
}

void RBTree::Next() {
    if (!node_stack.empty())
        node_stack.pop();

    if (current->right != NIL) {
        current = current->right;

        while (current->left != NIL) {
            node_stack.push(current);
            current = current->left;
        }
        node_stack.push(current);
    } else if (!node_stack.empty()) {
        current = node_stack.top();
    }

    counter++;
}

void RBTree::shuffle_for_insert(Node *node) {
    while (node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;

            if (uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    left_rotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                right_rotate(node->parent->parent);
            }
        } else {
            Node* uncle = node->parent->parent->left;

            if (uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    right_rotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                left_rotate(node->parent->parent);
            }
        }
    }

    root->color = BLACK;
}

void RBTree::left_rotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RBTree::right_rotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;

    if (y->right != NIL)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

void RBTree::transplant(Node *x, Node *y) {
    if (x->parent == NIL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->parent = x->parent;
}

void RBTree::shuffle_for_remove(Node *node) {
    while (node != root && node->color == BLACK) {
        if (node == node->parent->left) {
            Node *tmp = node->parent->right;

            if (tmp->color == RED) {
                tmp->color = BLACK;
                node->parent->color = RED;
                left_rotate(node->parent);
                tmp = node->parent->right;
            }

            if (tmp->left->color == BLACK && tmp->right->color == BLACK) {
                tmp->color = RED;
                node = node->parent;
            } else {
                if (tmp->right->color == BLACK) {
                    tmp->left->color = BLACK;
                    tmp->color = RED;
                    right_rotate(tmp);
                    tmp = node->parent->right;
                }
                tmp->color = node->parent->color;
                node->parent->color = BLACK;
                tmp->right->color = BLACK;
                left_rotate(node->parent);
                node = root;
            }
        } else {
            Node *tmp = node->parent->left;

            if (tmp->color == RED) {
                tmp->color = BLACK;
                node->parent->color = RED;
                right_rotate(node->parent);
                tmp = node->parent->left;
            }

            if (tmp->right->color == BLACK && tmp->left->color == BLACK) {
                tmp->color = RED;
                node = node->parent;
            } else {
                if (tmp->left->color == BLACK) {
                    tmp->right->color = BLACK;
                    tmp->color = RED;
                    left_rotate(tmp);
                    tmp = node->parent->left;
                }
                tmp->color = node->parent->color;
                node->parent->color = BLACK;
                tmp->left->color = BLACK;
                right_rotate(node->parent);
                node = root;
            }
        }
    }

    node->color = BLACK;
}

Node* RBTree::get_minimum(Node* const node) {
    current = node;

    while (current->left != NIL)
        current = current->left;

    return current;
}
