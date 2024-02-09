/**
 * @file
 * @brief Definition of TreeNode and Tree classes.
 */

#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Akr::Common {

/**
 * @brief Represents a node in the tree.
 * @tparam T The type of data stored in the node.
 */
template <typename T>
class TreeNode {
public:
    /**
     * @brief Constructor for TreeNode.
     * @param id The ID of the node.
     * @param data The data associated with the node.
     */
    TreeNode(const std::string& id, const T& data) : id_(id), data_(data) {}

    /**
     * @brief Get the ID of the node.
     * @return The ID of the node.
     */
    const std::string& getId() const { return id_; }

    /**
     * @brief Get the data associated with the node.
     * @return The data associated with the node.
     */
    const T& getData() const { return data_; }

    /**
     * @brief Add a child node to the current node.
     * @param child The child node to add.
     */
    void addChild(const std::shared_ptr<TreeNode<T>>& child) {
        children.push_back(child);
    }

    std::vector<std::shared_ptr<TreeNode<T>>> children; /**< Children nodes of the current node. */
private:
    std::string id_; /**< The ID of the node. */
    T data_;         /**< The data associated with the node. */
};


/**
 * @brief Represents a tree structure.
 * @tparam K The type of the key used to identify nodes in the tree.
 * @tparam V The type of data stored in the tree nodes.
 */
template <typename K, typename V>
class Tree {
public:
    /**
     * @brief Default constructor for Tree.
     */
    Tree() : root_(nullptr) {}

    /**
     * @brief Insert a node into the tree.
     * @param key The key of the node to be inserted.
     * @param value The value associated with the node.
     */
    void insert(const K& key, const V& value) {
        if (!root_) {
            root_ = std::make_shared<TreeNode<V>>(key, value);
        } else {
            insert(root_, key, value);
        }
    }

    /**
     * @brief Find a node in the tree by its key.
     * @param key The key of the node to find.
     * @return A shared pointer to the found node, or nullptr if not found.
     */
    std::shared_ptr<TreeNode<V>> find(const K& key) {
        return find(root_, key);
    }

private:
    std::shared_ptr<TreeNode<V>> root_; /**< The root node of the tree. */

    /**
     * @brief Recursive function to insert a node into the tree.
     * @param node The current node being processed.
     * @param key The key of the node to be inserted.
     * @param value The value associated with the node.
     */
    void insert(std::shared_ptr<TreeNode<V>>& node, const K& key, const V& value) {
        if (!node) {
            node = std::make_shared<TreeNode<V>>(key, value);
        } else {
            // You can define your own logic for inserting nodes in the tree
            // For simplicity, this example just inserts all nodes as children of the root
            node->children.push_back(std::make_shared<TreeNode<V>>(key, value));
        }
    }

    /**
     * @brief Recursive function to find a node in the tree by its key.
     * @param node The current node being processed.
     * @param key The key of the node to find.
     * @return A shared pointer to the found node, or nullptr if not found.
     */
    std::shared_ptr<TreeNode<V>> find(std::shared_ptr<TreeNode<V>>& node, const K& key) {
        if (!node) {
            return nullptr;
        }

        if (node->getId() == key) {
            return node;
        }

        for (auto child : node->children) {
            auto result = find(child, key);
            if (result) {
                return result;
            }
        }

        return nullptr;
    }
};

} // namespace Akr::Common
