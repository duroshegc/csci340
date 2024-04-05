/************************************************************************************
* NIU CSCI 340 Section 1 *
* Assignment 3 
* Oluwasegun Durosinmi - z1978798 *
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
* * Implementing a container and its iterators such that carious STL algorithms
* * will just work with it.
************************************************************************************/
#ifndef NIUCSCI340_LIST_H
#define NIUCSCI340_LIST_H

#include "simple_linked_list.decl.h"

#include <iostream>

/**
 * @brief Constructor copying the contents of another container.
 *
 * This constructor will initialize a simple_linked_list object by copying the contents
 * of another container defined by the iterator range [beg, end].
 *
 * @param beg The beginning of the input sequence.
 * @param end The end of the input sequence.
 * @tparam ITERATOR The type of iterator for the input sequence.
 */

template <typename T>
template <typename ITERATOR> // constructor copying the contents of another container
simple_linked_list <T>::simple_linked_list(ITERATOR beg, ITERATOR end) {

  head = nullptr;
  tail = nullptr;

  // Iterate over the elements from beginning to end
  for(auto it = beg; it != end; ++it)
  {
    //Putting each element at the end of the list
    push_back(*it);

  }


}

/**
 * @brief Check if the list is empty.
 *
 * This function will check if the list is empty.
 *
 * @return true if the list is empty, false otherwise.
 */

template <typename T>
bool simple_linked_list<T>::empty() const {

  // Checking if the list is empty
  if(head == nullptr && tail == nullptr)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * @brief Get an iterator pointing to the first element.
 *
 * This function will return an iterator pointing to the first element in the list.
 *
 * @return An iterator pointing to the first element.
 */

template <typename T>
simple_linked_iterator <T> simple_linked_list<T>::begin() {

  // Point to the element iterator using an iterator
  return simple_linked_iterator <T> (head);

}

/**
 * @brief Get an iterator pointing to one past the last element.
 *
 * This function returns an iterator pointing to one past the last element in the list.
 *
 * @return An iterator pointing to one past the last element.
 */

template <typename T>
simple_linked_iterator <T> simple_linked_list<T>::end() {
  //Point to the one past the last element
  return simple_linked_iterator <T> (nullptr);
}

/**
 * @brief Get a reference to the first element.
 *
 * This function will return a reference to the first element in the list.
 *
 * @return Reference to the first element.
 */

template <typename T>
T & simple_linked_list<T>::front() {
  //Reference to the first element
  return head->data;
}

/**
 * @brief Get a reference to the last element.
 *
 * This function returns a reference to the last element in the list.
 *
 * @return A reference to the last element.
 */

template <typename T>
T & simple_linked_list<T>::back() {
  //Reference to the last element
  return tail->data;
}

/**
 * @brief Will Remove the last element.
 *
 * This function will remove the last element from the list.
 */

template <typename T>
void simple_linked_list<T>::pop_back() {

  //Added: Check if the list has only one value in it
    if (head == tail) {
        delete tail;
        head = tail = nullptr;
        return;
    }

  // Find the second to last node
  linked_node <T> *p;
  p = head;

  while(p->next != tail)
  {
    p = p->next;
  }

  // Now we can delete the last node
  delete tail;
  tail = p;
  p->next = nullptr;

  n_elements--;

}

/**
 * @brief Add an element to the end of the list.
 *
 * This function will add an element to the end of the list.
 *
 * @param x The element to be added.
 */

template <typename T>
void simple_linked_list<T>::push_back(const T & x) {
  //Create a new node and give it the given value
  linked_node <T> *new_node = nullptr;

  new_node = new linked_node(x);

  //If list is empty, set both head and tail to the new node
  if(head == nullptr && tail == nullptr)
  {
    head = new_node;
    tail = new_node;
  }
  else
  {
      //Else append the new_node to the end of the list
     tail->next = new_node;

     tail = new_node;

  }

  // Always have to increment the element count
  n_elements++;
}

/**
 * @brief Destructor.
 *
 * This function will clear the list by removing all elements.
 */

template <typename T>
simple_linked_list<T>::~simple_linked_list() {
  clear();
}

/**
 * @brief Get the size of the list.
 *
 * This function returns the number of elements in the list.
 *
 * @return The number of elements in the list.
 */

template <class T>
size_t simple_linked_list<T>::size() const {
  // Clear the list
  return n_elements;
}

/**
 * @brief Clear the list.
 *
 * This function clears the list by removing all elements.
 */

template <typename T>
void simple_linked_list<T>::clear() {

  //Iterate through the list by removing all elements
    for (; head != nullptr; ) {
        pop_back();
    }
}


// IMPLEMENTATIONS FOR ITERATOR

/**
 * @brief Check if two iterators are equal.
 *
 * This function will check if two iterators are equal.
 *
 * @param other The other iterator to compare with.
 * @return true if the two iterators are equal, false otherwise.
 */

template <typename T>
bool simple_linked_iterator<T>::operator == (const simple_linked_iterator <T> & other) const {
    //Check if the two iterators are equal
  if(pos == other.pos)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * @brief Pre-increment operator (++it).
 *
 * This function will increment the iterator to the next node.
 *
 * @return Reference to the incremented iterator.
 */

template <typename T>
simple_linked_iterator <T> & simple_linked_iterator <T>::operator ++ () { // preincrement
 // Change the iterator to the next node

  pos = pos->next;

  return *this;
}

/**
 * @brief Post-increment operator.
 *
 * This function will create a copy of the iterator, then increments the original iterator
 * to the next node.
 *
 * @return A copy of the original iterator before incrementing.
 */

template <typename T>
simple_linked_iterator <T> simple_linked_iterator<T>::operator ++ (int) { // postincrement
  //Creating the copy of the iterator
  simple_linked_iterator it(pos);
  //Change the iterator to the next node
  pos = pos->next;

  return it;
}

/**
 * @brief Dereference operator.
 *
 * This function will return  a reference to the data stored in the current node.
 *
 * @return A reference to the stored data in the current node.
 */

template <typename T>
T & simple_linked_iterator<T>::operator * () { // dereference operator
  //Return to the stored data in the current node
  return pos->data;
}

#endif
