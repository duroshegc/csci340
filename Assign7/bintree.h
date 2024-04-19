/************************************************************************************
* NIU CSCI 340 Section 1 *
* Assignment 7 
* Oluwasegun Durosinmi - z1978798 *
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
* * The purpose of this assignment is to have you perform a practical task using binary trees. This time, that task will be to
implement a simplified XML parser
************************************************************************************/

#ifndef NIU_CSCI330_BINTREE_IMPL_H
#define NIU_CSCI330_BINTREE_IMPL_H

#include "bintree.decl.h"
#include <vector>
#include <queue>
#include <deque>

using namespace std;

/**
 * @brief Performs a preorder traversal of the binary tree rooted at 'root', applying the function 'fn' to each node.
 * 
 * @tparam BINTREENODE Type of the binary tree node.
 * @tparam FN Type of the function to apply to each node.
 * @param root Root of the binary tree.
 * @param fn Function to apply to each node.
 */

template <typename BINTREENODE, typename FN>
void preorder(BINTREENODE *root, FN fn) {
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
 * @brief Performs an inorder traversal of the binary tree rooted at 'root', applying the function 'fn' to each node.
 * 
 * @tparam BINTREENODE Type of the binary tree node.
 * @tparam FN Type of the function to apply to each node.
 * @param root Root of the binary tree.
 * @param fn Function to apply to each node.
 */

template <typename BINTREENODE, typename FN>
void inorder(BINTREENODE *root, FN fn) {
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
 * @brief Performs a postorder traversal of the binary tree rooted at 'root', applying the function 'fn' to each node.
 * 
 * @tparam BINTREENODE Type of the binary tree node.
 * @tparam FN Type of the function to apply to each node.
 * @param root Root of the binary tree.
 * @param fn Function to apply to each node.
 */

template <typename BINTREENODE, typename FN>
void postorder(BINTREENODE *root, FN fn) {
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
 * @brief Performs a level-order traversal of the binary tree rooted at 'root', applying the function 'fn' to each node.
 * 
 * @tparam BINTREENODE Type of the binary tree node.
 * @tparam FN Type of the function to apply to each node.
 * @param root Root of the binary tree.
 * @param fn Function to apply to each node.
 */

template <typename BINTREENODE, typename FN>
void levelorder(BINTREENODE *root, FN fn) {
  BINTREENODE *p;
  queue<BINTREENODE *> q;
  if(root == nullptr)
  {
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
 * @brief Returns all of the direct children of the given node.
 * 
 * @tparam BINTREENODE Type of the binary tree node.
 * @param node The node whose children are to be returned.
 * @return std::vector<BINTREENODE*> Vector containing all direct children of the given node.
 */


template <typename BINTREENODE>
std::vector <BINTREENODE *> tilted_get_children(BINTREENODE * node) {
  vector <BINTREENODE*> myvec;
  
  if(node != nullptr)
  {
    BINTREENODE *ptr = node->left;
    if(ptr != nullptr)
  {
    // Add left child to the vector
    myvec.push_back(ptr);
    while(ptr->right != nullptr)
    {
      // Add right children to the vector
      myvec.push_back(ptr->right);
      ptr = ptr->right;
    }

  }
  }

  return myvec; 
}

/**
 * @brief Finds the parent node of the given node in the binary tree.
 * 
 * This function requires that the BINTREENODE type has the 'parent' member.
 * 
 * @tparam BINTREENODE Type of the binary tree node.
 * @param node The node whose parent is to be found.
 * @return BINTREENODE* Pointer to the parent node, or nullptr if the given node is the root or nullptr.
 */

template <typename BINTREENODE>
BINTREENODE * tilted_find_parent(BINTREENODE *node) {
  
  if(node == nullptr)
  {
    return nullptr;
  }

  BINTREENODE *ptr = node->parent;


  while(ptr != nullptr)
  {
    if(ptr->left == node) 
    {
      // Return parent node if found
      return ptr;
    }

    node = ptr;
    ptr = ptr->parent;
  }
  // Return nullptr if parent not found
  return nullptr;
  
  
}


/**
 * @brief Performs a level-order traversal of the binary tree rooted at 'Eroot', applying the function 'fn' to each node.
 * 
 * @tparam BINTREENODE Type of the binary tree node.
 * @tparam FN Type of the function to apply to each node.
 * @param Eroot Root of the binary tree.
 * @param fn Function to apply to each node.
 */

template <typename BINTREENODE, typename FN>
void tilted_levelorder(BINTREENODE *Eroot, FN fn) {
  queue<BINTREENODE*> q;

  if(Eroot == nullptr)
  {
    return;
  }
  q.push(Eroot);

  while(!q.empty())
  {
    // Apply function to the current node
    fn(q.front());
    BINTREENODE *ptr = q.front();
    BINTREENODE *child = ptr->left;
    q.pop();

    while(child != nullptr)
    {
      // Push child nodes to the queue for further processing
      q.push(child);
      // Move to the right sibling
      child = child->right;
    }

  }

}


/**
 * @brief Deletes the binary tree rooted at 'node'.
 * 
 * This function performs a recursive deletion of all nodes in the binary tree.
 * 
 * @tparam BINTREENODE Type of the binary tree node.
 * @param node Root of the binary tree to delete.
 */

template <typename BINTREENODE>
void delete_tree(BINTREENODE * &node) {
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
