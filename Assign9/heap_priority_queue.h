/************************************************************************************
* NIU CSCI 340 Section 1 *
* Assignment 9 
* Oluwasegun Durosinmi - z1978798 *
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
* * The purpose of this assignment is to have you implement the heap data structure. You will also implement a priority queue
* * class using that heap implementation, which will work like the STL priority queue
************************************************************************************/

#ifndef NIU_CSCI340_HEAP_PQ_H
#define NIU_CSCI340_HEAP_PQ_H

// This file is the version distributed to students for implementation.

#include "heap_priority_queue.decl.h"
#include <utility>

using namespace std;

template <class T, class CONTAINER, class COMPARE>
template <class ITERATOR>
heap_priority_queue<T,CONTAINER,COMPARE>::heap_priority_queue(ITERATOR begin, ITERATOR end) {
  
    // set the data by giving it the elements
    data = CONTAINER(begin, end);
    //give the nodes the given size of the data
    nodes = data.size();


    // now we can heapify the queue
    for (size_t index = nodes / 2; index >= 0; index--) 
    {
        heap_bubble_down(data.begin(), nodes, index - 1, compare);
    }
  
}

template <class T, class CONTAINER, class COMPARE>
T & heap_priority_queue<T,CONTAINER,COMPARE>::top() {
  // We can return the front element
   return data.front(); 
}

template <class T, class CONTAINER, class COMPARE>
bool heap_priority_queue<T,CONTAINER,COMPARE>::empty() const {
  //call empty function to check if data is empty
  if(data.empty())
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <class T, class CONTAINER, class COMPARE>
size_t heap_priority_queue<T,CONTAINER,COMPARE>::size() const {
  // We can just call the size function to return the size of the data
  return data.size();
}

template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T,CONTAINER,COMPARE>::push(const T & x) {
 // add the element to the back
 data.push_back(x); 

  // Then we can bubble up
 heap_bubble_up(data.begin(), data.size(), data.size() - 1, compare);
}

template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T,CONTAINER,COMPARE>::pop() {
  
  // Swap the last and first values
  swap(data.front(), data.back());

  // now we can remove the last element
  data.pop_back(); 

  // lets bubble down so that we can pass th eheap check
  heap_bubble_down(data.begin(), data.size(), 0, compare); 

}

// This one is provided for you and does not need changes.
template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T,CONTAINER,COMPARE>::dump_data(std::ostream &ost) const {
  ost << "[ ";
  for(size_t i = 0; i < nodes; ++i) {
    ost << data[i] << " "; }
  ost << "]"; }


#endif /* NIU_CSCI340_HEAP_PQ_H */