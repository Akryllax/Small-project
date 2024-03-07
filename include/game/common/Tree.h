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
template <typename K, typename V>
class TreeNode {
public:
  /**
   * @brief Constructor for TreeNode.
   * @param id The ID of the node.
   * @param data The data associated with the node.
   */
  TreeNode(K const& id, V const& data) : id_(id), data_(data) {}

  /**
   * @brief Get the ID of the node.
   * @return The ID of the node.
   */
  K const& getId() const { return id_; }

  /**
   * @brief Get the data associated with the node.
   * @return The data associated with the node.
   */
  V const& getData() const { return data_; }

  /**
   * @brief Add a child node to the current node.
   * @param child The child node to add.
   */
  void addChild(std::shared_ptr<TreeNode<K, V>> const child) { children.push_back(child); }

  std::vector<std::shared_ptr<TreeNode<K, V>>> children; /**< Children nodes of the current node. */
private:
  K id_;   /**< The ID of the node. */
  V data_; /**< The data associated with the node. */
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
  void insert(K const& key, V const& value) {
    if (!root_) {
      root_ = std::make_shared<TreeNode<K, V>>(key, value);
    } else {
      insert(root_, key, value);
    }
  }

  /**
   * @brief Find a node in the tree by its key.
   * @param key The key of the node to find.
   * @return A shared pointer to the found node, or nullptr if not found.
   */
  std::shared_ptr<TreeNode<K, V>> find(K const& key) { return find(root_, key); }

  /**
   * @brief Remove a node from the tree by its key.
   * @param key The key of the node to be removed.
   * @return true if the node is successfully removed, false otherwise.
   */
  bool remove(K const& key) { return remove(root_, key); }

  /**
   * @brief Get the root TreeNode of this Tree.
   * @return const reference to root TreeNode
   */
  std::shared_ptr<TreeNode<K, V>> const& root() { return root_; }

private:
  std::shared_ptr<TreeNode<K, V>> root_; /**< The root node of the tree. */

  /**
   * @brief Recursive function to insert a node into the tree.
   * @param node The current node being processed.
   * @param key The key of the node to be inserted.
   * @param value The value associated with the node.
   */
  void insert(std::shared_ptr<TreeNode<K, V>>& node, K const& key, V const& value) {
    if (!node) {
      node = std::make_shared<TreeNode<K, V>>(key, value);
    } else {
      // You can define your own logic for inserting nodes in the tree
      // For simplicity, this example just inserts all nodes as children of the root
      node->children.push_back(std::make_shared<TreeNode<K, V>>(key, value));
    }
  }

  /**
   * @brief Recursive function to find a node in the tree by its key.
   * @param node The current node being processed.
   * @param key The key of the node to find.
   * @return A shared pointer to the found node, or nullptr if not found.
   */
  std::shared_ptr<TreeNode<K, V>> find(std::shared_ptr<TreeNode<K, V>>& node, K const& key) {
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

  /**
   * @brief Recursive function to remove a node from the tree by its key.
   * @param node The current node being processed.
   * @param key The key of the node to be removed.
   * @return true if the node is successfully removed, false otherwise.
   */
  bool remove(std::shared_ptr<TreeNode<K, V>>& node, K const& key) {
    if (!node) {
      return false;  // Node not found
    }

    if (node->getId() == key) {
      // Node found, remove it
      node.reset();  // Release memory
      return true;
    }

    // Recursively search for the node to remove in the children
    for (auto it = node->children.begin(); it != node->children.end(); ++it) {
      if ((*it)->getId() == key) {
        // Node found, remove it from children vector
        node->children.erase(it);
        return true;
      } else {
        // Recursively search in children
        if (remove(*it, key)) {
          return true;  // Node removed from children
        }
      }
    }

    return false;  // Node not found
  }

  void clear() { clear(root_); }

private:
  void clear(std::shared_ptr<TreeNode<K, V>>& node) {
    if (!node) {
      return;
    }

    for (auto child : node->children) {
      clear(child);
    }

    node.reset();  // Release memory
  }
};
}  // namespace Akr::Common
