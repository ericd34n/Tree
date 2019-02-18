//
// Created by Eric Sanchez on 3/29/18.
//
#ifndef MAP_NODE_H
#define MAP_NODE_H

#include <iostream>
#include <memory>
#include <tuple>
#include <utility>
#include <vector>

struct BalancedStatusWithHeight;

template <typename K, typename V>
class Node {
public:
    const K key;
    V value;
    std::unique_ptr<Node<K, V>> left, right;
    using UP = std::unique_ptr<Node<K, V>>;
    explicit Node(const K data, V value)
        : key(std::move(data))
        , value(std::move(value))
    {
    }

    bool isBalanced(const std::unique_ptr<Node<K, V>>&);
    void insert(UP&, const K&, const V&);
    void insert(UP&, UP&);
    void insert(UP&, std::pair<K, V>);

    Node<K, V>* find(const UP& root, const K&);

    bool insert_unique(UP&, const K&, const V&);
    bool insert_unique(UP&, std::pair<K, V>);
    bool update(const UP& root, const K&, const K&);
    BalancedStatusWithHeight CheckBalanced(const std::unique_ptr<Node<K, V>>&);
};

template <typename K, typename V>
Node<K, V>*
Node<K, V>::find(const std::unique_ptr<Node<K, V>>& root, const K& key)
{
    auto cursor = root.get();
    while (cursor && cursor->key != key) {
        if (cursor->key > key)
            cursor = cursor->left.get();
        else
            cursor = cursor->right.get();
    }
    return cursor;
}

template <typename K, typename V>
void Node<K, V>::insert(std::unique_ptr<Node<K, V>>& root,
    const K& key,
    const V& data)
{
    if (!root) {
        root = std::move(std::make_unique<Node<K, V>>(Node<K, V>(key, data)));
    } else {
        if (root->key > key) {
            insert(root->left, key, data);
        } else {
            insert(root->right, key, data);
        }
    }
}

template <typename K, typename V>
void Node<K, V>::insert(std::unique_ptr<Node<K, V>>& root,
    std::unique_ptr<Node<K, V>>& node)
{
    if (!root) {
        root = std::move(node);
    } else {
        if (root->key > node->key) {
            insert(root->left, node);
        } else {
            insert(root->right, node);
        }
    }
}

template <typename K, typename V>
void Node<K, V>::insert(std::unique_ptr<Node<K, V>>& root, std::pair<K, V> kv_pair)
{
    if (!root) {
        root = std::move(
            std::make_unique<Node<K, V>>(Node<K, V>(kv_pair.first, kv_pair.second)));
    } else {
        if (root->key > kv_pair.first) {
            insert(root->left, kv_pair);
        } else {
            insert(root->right, kv_pair);
        }
    }
}

template <typename K, typename V>
bool Node<K, V>::update(const std::unique_ptr<Node<K, V>>& root,
    const K& key,
    const K& new_value)
{
    auto target = root->find(root, key);
    if (target) {
        target->value = new_value;
        return true;
    }
    return false;
}

template <typename K, typename V>
bool Node<K, V>::insert_unique(std::unique_ptr<Node<K, V>>& root,
    const K& key,
    const V& value)
{
    auto target = root->find(root, key);
    if (!target) {
        root->insert(root, key, value);
        return true;
    }
    return false;
}

template <typename K, typename V>
bool Node<K, V>::insert_unique(std::unique_ptr<Node<K, V>>& root,
    std::pair<K, V> kv_pair)
{
    auto target = root->find(root, kv_pair.first);
    if (!target) {
        root->insert(root, kv_pair);
        return true;
    }
    return false;
}

template <typename K, typename V>
void in_order_traversal(std::unique_ptr<Node<K, V>>& root)
{
    if (root) {
        in_order_traversal(root->left);
        std::cout << " {" << root->key << ": " << root->value << "} ";
        in_order_traversal(root->right);
    }
}

template <typename K, typename V>
void pre_order_traversal(std::unique_ptr<Node<K, V>>& root)
{
    if (root) {
        std::cout << " {" << root->key << ": " << root->value << "} ";
        pre_order_traversal(root->left);
        pre_order_traversal(root->right);
    }
}

template <typename K, typename V>
void post_order_traversal(std::unique_ptr<Node<K, V>>& root)
{
    if (root) {
        post_order_traversal(root->left);
        post_order_traversal(root->right);
        std::cout << " {" << root->key << ": " << root->value << "} ";
    }
}

struct BalancedStatusWithHeight {
    bool balanced;
    int height;
};

template <typename K, typename V>
BalancedStatusWithHeight Node<K, V>::CheckBalanced(const std::unique_ptr<Node<K, V>>& tree)
{
    if (tree == nullptr) {
        return { true, -1 };
    }

    auto left_result = CheckBalanced(tree->left);
    if (!left_result.balanced) {
        return { false, 0 };
    }

    auto right_result = CheckBalanced(tree->right);
    if (!right_result.balanced) {
        return { false, 0 };
    }

    bool is_balanced = abs(left_result.height - right_result.height) <= 1;
    int height = std::max(left_result.height, right_result.height) + 1;
    return { is_balanced, height };
}

template <typename K, typename V>
bool Node<K, V>::isBalanced(const std::unique_ptr<Node<K, V>>& tree)
{
    return CheckBalanced(tree).balanced;
}

#endif //MAP_NODE_H
