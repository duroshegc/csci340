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
#ifndef NIU_CSCI340_HEAP_H
#define NIU_CSCI340_HEAP_H

#include <algorithm>
#include <stdexcept>
#include <utility>

using namespace std;

/**
 * @brief Calculate the index of the left child of a node in a heap.
 * 
 * @param node The index of the parent node.
 * @return size_t The index of the left child.
 */

inline constexpr size_t heap_left(size_t node) { 
  // calculate the index of the left child of a node in a heap
  size_t left = 2 * node + 1;
  return left;
}

/**
 * @brief Calculate the index of the right child of a node in a heap.
 * 
 * @param node The index of the parent node.
 * @return size_t The index of the right child.
 */

inline constexpr size_t heap_right(size_t node) { 
  //  calculate the index of the right child of a node in a heap
  size_t right = 2 * node + 2;
  return right;
}

/**
 * @brief Calculate the index of the parent of a node in a heap.
 * 
 * @param node The index of the child node.
 * @return size_t The index of the parent node.
 */

inline constexpr size_t heap_parent(size_t node) {
  // If the node is the root (index 0), return 0 as it has no parent
  if(node <= 0)
  {
    return 0;
  }
  else
  {
    // Calculate and return the index of the parent node
    size_t parent = (node - 1)/ 2;
    return parent;
  }


}

/**
 * @brief Traverse a heap in pre-order fashion and apply a function to each node.
 * 
 * @tparam ArrayLike Type of the array-like structure representing the heap.
 * @tparam FN Type of the function object to be applied to each node.
 * @param heapdata The array-like structure representing the heap.
 * @param heapnodes Number of nodes in the heap.
 * @param node Index of the current node being visited.
 * @param fn Function object to be applied to each node.
 */

template <typename ArrayLike, typename FN>
void heap_preorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    if (node < heapnodes) {
        // Pass the value at the node to the function, not the index
        fn(heapdata[node]);  
        
        // Recursive call to the left child
        heap_preorder(heapdata, heapnodes, 2 * node + 1, fn);  
        
        // Recursive call to the right child
        heap_preorder(heapdata, heapnodes, 2 * node + 2, fn);  
    }
}

/**
 * @brief Traverse a heap in in-order fashion and apply a function to each node.
 * 
 * @tparam ArrayLike Type of the array-like structure representing the heap.
 * @tparam FN Type of the function object to be applied to each node.
 * @param heapdata The array-like structure representing the heap.
 * @param heapnodes Number of nodes in the heap.
 * @param node Index of the current node being visited.
 * @param fn Function object to be applied to each node.
 */

template <typename ArrayLike, typename FN>
void heap_inorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    if (node < heapnodes) {

        // Recursive call to the left child
        heap_inorder(heapdata, heapnodes, 2 * node + 1, fn);

        // Call fn on the current node's value
        fn(heapdata[node]);

        // Recursive call to the right child
        heap_inorder(heapdata, heapnodes, 2 * node + 2, fn);
    }
}

/**
 * @brief Traverse a heap in post-order fashion and apply a function to each node.
 * 
 * @tparam ArrayLike Type of the array-like structure representing the heap.
 * @tparam FN Type of the function object to be applied to each node.
 * @param heapdata The array-like structure representing the heap.
 * @param heapnodes Number of nodes in the heap.
 * @param node Index of the current node being visited.
 * @param fn Function object to be applied to each node.
 */

template <typename ArrayLike, typename FN>
void heap_postorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    if (node < heapnodes) {

        // Recursive call to the left child
        heap_postorder(heapdata, heapnodes, 2 * node + 1, fn);

        // Recursive call to the right child
        heap_postorder(heapdata, heapnodes, 2 * node + 2, fn);

        // Call fn on the current node's value
        fn(heapdata[node]);
    }
}

/**
 * @brief Traverse a heap in level-order fashion and apply a function to each node.
 * 
 * @tparam ArrayLike Type of the array-like structure representing the heap.
 * @tparam FN Type of the function object to be applied to each node.
 * @param heapdata Reference to the array-like structure representing the heap.
 * @param heapnodes Number of nodes in the heap.
 * @param fn Function object to be applied to each node.
 */

template <typename ArrayLike, typename FN>
void heap_levelorder(ArrayLike & heapdata, size_t heapnodes, FN fn) {
  for(size_t i = 0; i < heapnodes; i++)
  {
    fn(heapdata[i]);
  }
}

/**
 * @brief Check if a given array-like structure forms a heap according to a comparison function.
 * 
 * @tparam ArrayLike Type of the array-like structure representing the heap.
 * @tparam COMPARISON Type of the comparison function object.
 * @param heapdata Reference to the array-like structure representing the heap.
 * @param nodes Number of nodes in the heap.
 * @param compare Comparison function object for comparing elements.
 * @return true if the array forms a valid heap, false otherwise.
 */
// min tree uses less than, so compare(parent, child) should be true
template <typename ArrayLike, typename COMPARISON>
bool is_heap(const ArrayLike & heapdata, size_t nodes, COMPARISON compare) { 
    for (size_t i = 0; i <= (nodes / 2) - 1; i++) {
        size_t left_child_index = 2 * i + 1;
        size_t right_child_index = 2 * i + 2;

        // Check if left child exists and if it violates the heap property
        if (left_child_index < nodes && !compare(heapdata[i], heapdata[left_child_index])) {
            return false;
        }

        // Check if right child exists and if it violates the heap property
        if (right_child_index < nodes && !compare(heapdata[i], heapdata[right_child_index])) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Perform the bubble-up operation in a heap after an insertion.
 * 
 * @tparam RAIterator Type of the random-access iterator.
 * @tparam COMPARE Type of the comparison function object.
 * @param begin Iterator pointing to the beginning of the heap.
 * @param nodes Number of nodes in the heap.
 * @param start Index of the node where the bubble-up operation starts.
 * @param compare Comparison function object for comparing elements.
 * @return size_t Number of swaps performed during the operation.
 */

template <typename RAIterator, typename COMPARE>
size_t heap_bubble_up(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
  auto child_index = start;
  auto child = begin + child_index;
  size_t parent_index = (start - 1)/ 2;
  auto parent = begin + parent_index;
  size_t swaps = 0;
  
  while(child_index > 0 && compare(*child, *parent))
  {
      swap(*child, *parent);
      child_index = parent_index;
      child = parent;
      parent_index = (parent_index - 1)/ 2;
      parent = begin + parent_index;
      swaps++; 
  }

  return swaps;

}

/**
 * @brief Perform the bubble-down operation in a heap after an insertion.
 * 
 * @tparam RAIterator Type of the random-access iterator.
 * @tparam COMPARE Type of the comparison function object.
 * @param begin Iterator pointing to the beginning of the heap.
 * @param nodes Number of nodes in the heap.
 * @param start Index of the node to be bubbled down.
 * @param compare Comparison function object for comparing elements.
 * @return size_t Number of swaps performed during the operation.
 */

template <typename RAIterator, typename COMPARE>
size_t heap_bubble_down(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
// root index
 size_t root = start; 

  // keep track of swaps
 size_t swaps = 0; 

 while (2 * root + 1 < nodes)
 {
  // left child
   size_t left_child = 2 * root + 1; 
   // Initialize the child node
   size_t child_node = left_child; 

   if (left_child < nodes)
   {
    // right child index
    size_t right_child = left_child + 1; 

    if (right_child < nodes && compare(*(begin + right_child), *(begin + left_child)))
    {
       // change the child index if right child is smaller
     child_node = right_child;
    }
   }

   if (compare(*(begin + child_node), *(begin + root)))
   {
    // Swap the smallest value
    swap(*(begin + root), *(begin + child_node)); 
    
    //keep track of swap count
    swaps++;

    //Update the root
    root = child_node; 
   }
   else
   {
    //In case theres only one child which is left
    break; 
   }
 }
 // Return the number of swap times
 return swaps;
}

/**
 * @brief Insert a new element into the heap.
 * 
 * @tparam T Type of the elements in the heap.
 * @tparam CONTAINER Type of the container representing the heap.
 * @tparam COMPARISON Type of the comparison function object.
 * @param heapdata Reference to the container representing the heap.
 * @param nodes Reference to the number of nodes in the heap.
 * @param key The value to be inserted.
 * @param compare Comparison function object for comparing elements.
 */
template <typename T, typename CONTAINER, typename COMPARISON>
void heap_insert(CONTAINER & heapdata, size_t &nodes, T key, COMPARISON compare) {
 if (nodes == heapdata.size())
 {
  // change the size if needed
  heapdata.resize(nodes + 1);  
 }

  // Put the key at the end
 heapdata[nodes] = key; 
  // add the extra node
 nodes = nodes + 1; 

  
  // We want to move the element upward and swap
 heap_bubble_up(heapdata.begin(), nodes, nodes - 1, compare); 

}

/**
 * @brief Extract the top element from the heap.
 * 
 * @tparam CONTAINER Type of the container representing the heap.
 * @tparam COMPARISON Type of the comparison function object.
 * @param heapdata Reference to the container representing the heap.
 * @param nodes Reference to the number of nodes in the heap.
 * @param compare Comparison function object for comparing elements.
 * @return auto Extracted top element from the heap.
 * @throw std::out_of_range If the heap is empty.
 */

template <typename CONTAINER, typename COMPARISON>
auto heap_extract(CONTAINER & heapdata, size_t &nodes, COMPARISON compare) {

 if (nodes == 0)
 {
  // out of range exception if the heap is empty
  throw ::out_of_range("Heap is empty"); 
 }

  // We want to put the top element on
 typename CONTAINER::value_type heap_ext;
 heap_ext = heapdata[0]; 

  // switch the last element and first
 heapdata[0] = heapdata[nodes - 1]; 

 nodes = nodes - 1;

  // Start from the root node
 size_t beg = 0; 

 // Let's bubble down
 while (2 * beg + 1 < nodes)
 { 
  //left child index
   auto left_child_index = 2 * beg + 1; 

   //right child index
   auto right_child_index = 2 * beg + 2; 

   // need a variable to keep track of smallest child prefarably left child
   size_t small_child = left_child_index; 

   if (right_child_index < nodes && compare(heapdata[right_child_index], heapdata[left_child_index]))
   {
    //update small chile if smaller
    small_child = right_child_index; 
   }

   if (compare(heapdata[small_child], heapdata[beg]))
   {
    // Swap the node with its smallest child if necessary
    swap(heapdata[beg], heapdata[small_child]);

    // start should now have the smallest child value
    beg = small_child; 
   }
   else
   {
    // break if not needed
      break; 
   }
 }
  // Return the heap_ext element since non void
 return heap_ext; 
}

/**
 * @brief Heapify an array-like structure in place from bottom to top.
 * 
 * @tparam RAIterator Type of the random-access iterator.
 * @tparam COMPARE Type of the comparison function object.
 * @param begin Iterator pointing to the beginning of the array.
 * @param end Iterator pointing to the end of the array.
 * @param compare Comparison function object for comparing elements.
 * @return size_t Number of swaps performed during heapification.
 */
template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_up(RAIterator begin, RAIterator end, COMPARE compare) {
 
 size_t swaps = 0;
 
 // Use an iterator to keep track
 size_t it = distance(begin, end); 

 for (size_t i = 1; i < it; i++)
 { 
   size_t index = i; 

   while (index > 0)
   { 
    // Lets get the parent index
    size_t parent_index = (index - 1) / 2; 

    if (!compare(*(begin + index), *(begin + parent_index)))
    { 
      // break
     break; 
    }

    // Swap parent and index values
    swap(*(begin + index), *(begin + parent_index)); 

    swaps++;
    //Set new index
    index = parent_index; 
   }
 }
  // Return the number of swap occurrence
  return swaps; 
}

/**
 * @brief Heapify an array-like structure in place from top to bottom.
 * 
 * This function rearranges the elements of the array-like structure to form a heap.
 * It starts from the middle of the array and iterates down to the first element, 
 * performing bubble-down operations to maintain the heap property.
 * 
 * @tparam RAIterator Random-access iterator type.
 * @tparam COMPARE Comparison function object type.
 * @param begin Iterator pointing to the beginning of the array.
 * @param end Iterator pointing to the end of the array.
 * @param compare Comparison function object for comparing elements.
 * @return Number of swaps performed during heapification.
 */

template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_down(RAIterator begin, RAIterator end, COMPARE compare) {
// keep track of number of swaps

 auto swaps = 0; 

 // Use an iterator to keep track of distance
 size_t dis = distance(begin, end); 


 for (size_t i = (dis - 2) / 2; ; --i)
 { 

  // initialize node
  size_t node = i; 

  while (true)
  { 
    // continue looping if true

     size_t left_child = 2 * node + 1;
     size_t right_child = 2 * node + 2; 

    // Store current node
     size_t var = node; 

     if (left_child < dis && compare(*(begin + left_child), *(begin + var)))
     { 
       // Set var to left child
      var = left_child;
     }

     if (right_child < dis && compare(*(begin + right_child), *(begin + var)))
     { 
      // Set var to right child
      var = right_child; 
     }

     if (var != node) 
     { 

      //if not equal, lets swap

      // Swap node with var
      swap(*(begin + node), *(begin + var)); 
      swaps++;
      // Update node
      node = var; 
     }
     else
     {
      //break if condition is restored at heap
      break; 
     }
   }

   if (i == 0) 
   {
    // lets break when roo reached
      break; 
   }
 }
  // Return the number of swap occurrence
 return swaps;
}

/**
 * @brief Sorts the elements of an array-like structure using the heap sort algorithm.
 * 
 * This function sorts the elements of the array-like structure in non-decreasing order 
 * using the heap sort algorithm. It first constructs a heap from the elements and 
 * then repeatedly extracts the maximum element from the heap until the array is sorted.
 * 
 * @tparam RAIterator Random-access iterator type.
 * @tparam COMPARE Comparison function object type.
 * @param begin Iterator pointing to the beginning of the array.
 * @param end Iterator pointing to the end of the array.
 * @param compare Comparison function object for comparing elements.
 */
template <typename RAIterator, typename COMPARE>
void heap_sort(RAIterator begin, RAIterator end, COMPARE compare) {
  // Lets see the distance from the beg to end
 size_t node = distance(begin, end); 

//CALL THE PLACE DOWN FUNCTION SO WE CAN USE THE TOP DOWN METHOD
 heapify_in_place_down(begin, end, compare);

 for(size_t i = node - 1; i > 0; i--)
 {
   // We start from the back for proper sorting

   // swap the values of the first and last
   swap(*begin, *(begin + i)); 

  // now call bubble down for proper heap maintanance
   heap_bubble_down(begin, i, 0, compare); 
 }
}


#endif /* NIU_CSCI340_HEAP_H */
