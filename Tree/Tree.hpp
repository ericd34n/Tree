//
// Created by Eric Sanchez on 3/29/18.
//

#ifndef MAP_TREE_H
#define MAP_TREE_H

#include "Node.h"
#include <iostream>
#include <memory>
#include <tuple>
#include <utility>

template <typename K, typename V>
class Tree {
    friend Node<K, V>;

private:
    K root_key;
    V root_value;
    std::unique_ptr<Node<K, V>> root = std::unique_ptr<Node<K, V>>(new Node<K, V>(root_key, root_value));

public:
    Tree(const K& k, const V& v)
        : root_key(k)
        , root_value(v)
    {
    }

    bool isBalanced();
    void insert(const std::pair<K, V>&);
    void in_order_print();
    void pre_order_print();
    void post_order_print();
};

template <typename K, typename V>
void Tree<K, V>::insert(const std::pair<K, V>& _pair)
{
    root->insert_unique(root, _pair);
}

template <typename K, typename V>
void Tree<K, V>::in_order_print()
{
    std::cout << "\n{";
    in_order_traversal(root);
    std::cout << "}\n";
}

template <typename K, typename V>
void Tree<K, V>::pre_order_print()
{
    std::cout << "\n{";
    pre_order_traversal(root);
    std::cout << "}\n";
}

template <typename K, typename V>
void Tree<K, V>::post_order_print()
{
    std::cout << "\n{";
    post_order_traversal(root);
    std::cout << "}\n";
}

template <typename K, typename V>
bool Tree<K, V>::isBalanced() {
    return root->isBalanced(this->root);
}

#endif //MAP_TREE_H
