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

#ifndef NIU_CSCI340_BST_H_IMPL
#define NIU_CSCI340_BST_H_IMPL

#include "bst.decl.h"
#include <iostream>

/**
 * @brief Find a value in a binary search tree.
 * 
 * @tparam NODE Type of the tree node.
 * @tparam T Type of the value to find.
 * @param root Root node of the tree.
 * @param value Value to find.
 * @return NODE* Pointer to the node containing the value if found, nullptr otherwise.
 */

template <typename NODE, typename T>
NODE * bst_find(NODE *root, const T & value) {
  NODE *p;

  p = root;
  // Traverse the tree until the value is found or end is reached.
  while(p != nullptr && value != p->data)
  {
    if(value < p->data)
    {
      // Move to the left subtree.
      p = p->left;
    }
    else
    {
      // Move to the right subtree.
      p = p->right;
    }
  }
  // Return the pointer to the node containing the value or nullptr.
  return p;
}

/**
 * @brief Insert a value into a binary search tree.
 * 
 * @tparam NODEP Type of the tree node.
 * @tparam T Type of the value to insert.
 * @param root Root node of the tree.
 * @param value Value to insert.
 * @return NODEP* Pointer to the newly inserted node.
 */

template <typename NODEP, typename T>
NODEP * bst_insert(NODEP * &root, const T & value) {
  NODEP *p;
  NODEP *parent;
  NODEP *new_node = new NODEP(value);
  auto key = value;

  p = root;
  parent = nullptr;

  // Traverse the tree to find the appropriate position for insertion.
  while(p != nullptr)
  {
    parent = p;

    if(key < p->data)
    {
      // Move to the left subtree.
      p = p->left;
    }
    else if(key > p->data)
    {
      // Move to the right subtree.
      p = p->right;
    }
    else
    {
      delete new_node;
      // Node already exists, return nullptr.
      return nullptr;
    }
  }

  new_node->parent = parent; 
  // Insert the new node according to the position found.

  if(parent == nullptr)
  {
    // Insert as root.
    root = new_node;
  }
  else if(key < parent->data)
  {
    // Insert as left child.
    parent->left = new_node;
  }
  else
  {
    // Insert as right child.
    parent->right = new_node;
  }
  // Return the newly inserted node.
  return new_node;
}

/**
 * @brief Remove a value from a binary search tree.
 * 
 * @tparam NODEP Type of the tree node.
 * @tparam T Type of the value to remove.
 * @param root Root node of the tree.
 * @param value Value to remove.
 * @return NODEP* Pointer to the parent of the removed node.
 */

template <typename NODEP, typename T>
NODEP * bst_remove_value(NODEP * &root, const T & value) {
    NODEP *p = root;
    NODEP *parent = nullptr;
    NODEP *replace = nullptr;
    //NODEP *replace_parent = nullptr;

    // Search for the node to delete and its parent.
    while (p != nullptr && p->data != value) {
        parent = p;
        if (value < p->data) {
          // Move to the left subtree.
            p = p->left;
        } else {
          // Move to the right subtree.
            p = p->right;
        }
    }

    // If the node to delete was not found, return nullptr.
    if (p == nullptr) {
        return nullptr;
    }

    if (p->left == nullptr && p->right == nullptr) {

        if (parent == nullptr) {
            root = nullptr; // p is the root, remove it by setting root to nullptr.
        } else {
            // Remove p from its parent.
            if (parent->left == p) 
                parent->left = nullptr;
            else if (parent->right == p)
                parent->right = nullptr;
        }

        delete p; // Safely delete p.
        return parent; // Return the parent as the nearest affected node.
    }
    else if (p->left == nullptr || p->right == nullptr) {
        if (p->left != nullptr) 
            replace = p->left;
        else    
            replace = p->right;

        if (parent == nullptr) {
            root = replace; // p is the root, make replace the new root.
        } else {
            // Reattach the correct child pointer in parent.
            if (parent->left == p) 
                parent->left = replace;
            else 
                parent->right = replace;
        }

        replace->parent = parent; // COMMENT: PLEASE Update parent pointer of the child
        
        delete p; 
        return replace; 
    }   
    else 
    { 
        replace = p->right;     

        // Find the inorder predecessor (the rightmost node in the left subtree).
        while (replace->left) {
            //replace_parent = replace;
            replace = replace->left;
        }

        p->data = replace->data;    // swap values with the replace and p

        
        return bst_remove_value(p->right, replace->data); // Remove the successor using recursion

    }

        
}

/**
 * @brief Check if a binary tree is a binary search tree.
 * 
 * @tparam NODE Type of the tree node.
 * @param root Root node of the tree.
 * @return true if the tree is a binary search tree, false otherwise.
 */

template <typename NODE>
bool is_bst(NODE *root) {
  bool lhs;
  bool rhs;
  if(root == nullptr)
  {
    // Base case: an empty tree is a binary search tree.
    return true;
  }
  else
  {
    if(root->left != nullptr)
    {
      if(root->left->data < root->data)
      {
        // Recursively check the left subtree.
        lhs = is_bst(root->left);
      }
      else
      {
        // If left child's data is not less than root's data, it violates the binary search tree property.
        return false;
      }
    }
    else
    {
      // Left child is nullptr, so it satisfies the BST property.
      lhs = true;
    }
    
    if(root->right != nullptr)
    {
      if(root->right->data > root->data)
      {
        // Recursively check the right subtree.
        rhs = is_bst(root->right);
      }
      else
      {
        // If right child's data is not greater than root's data, it violates the binary search tree property.
        return false;
      }
    }
    else
    {
      // Right child is nullptr, so it satisfies the BST property.
      rhs = true;
    }

  }

  if(lhs && rhs)
  {
    // Both left and right subtrees are binary search trees, so the whole tree is a BST.
    return true;
  }
  else
  {
    // Either left or right subtree is not a binary search tree, so the whole tree is not a BST.
    return false;
  }
}

/**
 * @brief Find the minimum value node in a binary search tree.
 * 
 * @tparam NODE Type of the tree node.
 * @param root Root node of the tree.
 * @return NODE* Pointer to the minimum value node.
 */

template <typename NODE>
inline NODE * bst_minimum(NODE * root) {
  if(root == nullptr)
  {
    // Return nullptr if the tree is empty.
    return nullptr;
  }

  while(root->left != nullptr)
  {
    // Keep traversing left until the left child is nullptr.
    root = root->left;
  }
  // Return the minimum value node.
  return root;
}

/**
 * @brief Find the maximum value node in a binary search tree.
 * 
 * @tparam NODE Type of the tree node.
 * @param root Root node of the tree.
 * @return NODE* Pointer to the maximum value node.
 */

template <typename NODE>
inline NODE * bst_maximum(NODE * root) {
  if(root == nullptr)
  {
    // Return nullptr if the tree is empty.
    return nullptr;
  }

  while(root->right != nullptr)
  {
    // Keep traversing right until the right child is nullptr.
    root = root->right;
  }
  // Return the maximum value node.
  return root;
}

/**
 * @brief Find the successor node of a given node in a binary search tree.
 * 
 * @tparam NODEP Type of the tree node.
 * @param node Node whose successor is to be found.
 * @return NODEP* Pointer to the successor node.
 */

template <typename NODEP>
NODEP * successor(NODEP * node) {
  if(node == nullptr)
  {
    // Return nullptr if the given node is nullptr.
    return nullptr;
  }

  if(node->right != nullptr)
  {
    NODEP* tempNode = node->right;
    while(tempNode->left != nullptr)
    {
      // Find the leftmost node in the right subtree.
      tempNode = tempNode->left;
    }
    // Return the leftmost node.
    return tempNode;
  }

  NODEP* par = node->parent;
  while ( par  && par->right == node) {
      node = par;  // Move up to the parent
      par = par->parent;  // Update the parent to its parent
  }
  // Return the successor node.
  return par;

}


#endif