/************************************************************************************
* NIU CSCI 340 Section 1 *
* Assignment 8 
* Oluwasegun Durosinmi - z1978798 *
* *
* The purpose of this assignment is for you to implement a fully 
* functional binary search tree. No auto-balancing is done, but
* the insertion and removal functions will return information that 
* will be useful when adding it at a later time.
************************************************************************************/

#ifndef LEHUTA_BINTREE_H_IMPL
#define LEHUTA_BINTREE_H_IMPL



#include "bintree.decl.h"
#include <algorithm>
#include <queue>

using namespace std;

/**
 * @brief Calculate the height of a binary tree.
 * 
 * @tparam NODE Type of the tree node.
 * @param node Root node of the tree.
 * @return int Height of the tree.
 */

template <typename NODE>
int height(NODE * node) {
  // Calculate the height of a binary tree.
  if(node == nullptr)
  {
    // If the node is nullptr, height is -1.
    return -1;
  }
  else
  {
    int count = 0;
    int lh, rh;
    lh = height(node->left);
    rh = height(node->right);

    count = max(lh, rh);
    // Height is maximum of left and right subtree heights plus 1.
     return count + 1;
  }
 
}

/**
 * @brief Count the number of nodes in a binary tree.
 * 
 * @tparam NODE Type of the tree node.
 * @param root Root node of the tree.
 * @return int Number of nodes in the tree.
 */

template <typename NODE>
int count(NODE * root) {
  // Count the number of nodes in a binary tree.
  if(root == nullptr)
  {
    // If root is nullptr, tree is empty, return 0.
    return 0;
  }

  int lhs = count(root->left);
  int rhs = count(root->right);

  // Return 1 plus the sum of nodes in left and right subtrees.
  return 1 + lhs + rhs;
}

/**
 * @brief Perform preorder traversal on a binary tree.
 * 
 * @tparam NODE Type of the tree node.
 * @tparam FN Functor to apply to each node.
 * @param root Root node of the tree.
 * @param fn Functor to apply.
 */

template <typename NODE, typename FN>
void preorder(NODE *root, FN fn) {
  if(root != nullptr)
  {
    // Apply function to the current node
    fn(root);
    // Recursively traverse left and right subtree
    preorder(root->left, fn);
    preorder(root->right, fn);
  }
}

/**
 * @brief Perform inorder traversal on a binary tree.
 * 
 * @tparam NODE Type of the tree node.
 * @tparam FN Functor to apply to each node.
 * @param root Root node of the tree.
 * @param fn Functor to apply.
 */

template <typename NODE, typename FN>
void inorder(NODE *root, FN fn) {
  if(root != nullptr)
  {
    // Recursively traverse left subtree
    inorder(root->left, fn);
    // Apply function to the current node
    fn(root);
    // Recursively traverse right subtree
    inorder(root->right, fn);
  }
}

/**
 * @brief Perform postorder traversal on a binary tree.
 * 
 * @tparam NODE Type of the tree node.
 * @tparam FN Functor to apply to each node.
 * @param root Root node of the tree.
 * @param fn Functor to apply.
 */

template <typename NODE, typename FN>
void postorder(NODE *root, FN fn) {
   if(root != nullptr)
  {
    // Recursively traverse left and right subtree
    postorder(root->left, fn);
    postorder(root->right, fn);
    // Apply function to the current node
    fn(root);
  }
}

/**
 * @brief Perform level-order traversal on a binary tree.
 * 
 * @tparam NODE Type of the tree node.
 * @tparam FN Functor to apply to each node.
 * @param root Root node of the tree.
 * @param fn Functor to apply.
 */

template <typename NODE, typename FN>
void levelorder(NODE *root, FN fn) {
  NODE *p;
  queue<NODE *> q;
  if(root == nullptr)
  {
    // If root is nullptr, tree is empty, return.
    return;
  }

  q.push(root);

  while(!q.empty())
  {
    p = q.front();
    q.pop();
    // Apply function to the current node

    fn(p);

    if(p->left != nullptr)
    {
      q.push(p->left);
    }

    if(p->right != nullptr)
    {
      q.push(p->right);
    }
  }
}


/**
 * @brief Delete a binary tree.
 * 
 * @tparam NODE Type of the tree node.
 * @param node Root node of the tree.
 */

template <typename NODE>
void delete_tree(NODE * &node) {
  if(node != nullptr)
  {
    // Recursively delete left and right subtree
    delete_tree(node->left);
    delete_tree(node->right);
  // Delete current node
    delete node;
  }
}

#endif