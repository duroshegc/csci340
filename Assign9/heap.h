#ifndef NIU_CSCI340_HEAP_H
#define NIU_CSCI340_HEAP_H

#include <algorithm>
#include <stdexcept>

using namspace std;

inline constexpr size_t heap_left(size_t node) { 
  size_t left = 2 * node + 1;
  return left;
}
inline constexpr size_t heap_right(size_t node) { 
  size_t right = 2 * node + 2;
}
inline constexpr size_t heap_parent(size_t node) {
  if(node <= 0)
  {
    return 0;
  }
  else
  {
    size_t parent = (node - 1)/ 2;
  }


}

template <typename ArrayLike, typename FN>
void heap_preorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
  
}

template <typename ArrayLike, typename FN>
void heap_inorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
  // XXX You must implement this.
}

template <typename ArrayLike, typename FN>
void heap_postorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
  // XXX You must implement this.
}

template <typename ArrayLike, typename FN>
void heap_levelorder(ArrayLike & heapdata, size_t heapnodes, FN fn) {
  // XXX You must implement this.
}

// min tree uses less than, so compare(parent, child) should be true
template <typename ArrayLike, typename COMPARISON>
bool is_heap(const ArrayLike & heapdata, size_t nodes, COMPARISON compare) { 
  // XXX You must implement this properly.
  return false;
}

template <typename RAIterator, typename COMPARE>
size_t heap_bubble_up(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
  // XXX You must implement this properly.
  return 9999999;
}

template <typename RAIterator, typename COMPARE>
size_t heap_bubble_down(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
  // XXX You must implement this properly.
  return 9999999;
}

template <typename T, typename CONTAINER, typename COMPARISON>
void heap_insert(CONTAINER & heapdata, size_t &nodes, T key, COMPARISON compare) {
  // XXX You must implement this properly.
}

template <typename CONTAINER, typename COMPARISON>
auto heap_extract(CONTAINER & heapdata, size_t &nodes, COMPARISON compare) {
  // XXX You must implement this properly.
  return heapdata[9999999];
}

template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_up(RAIterator begin, RAIterator end, COMPARE compare) {
  // XXX You must implement this properly.
  return 9999999;
}

template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_down(RAIterator begin, RAIterator end, COMPARE compare) {
  // XXX You must implement this properly.
  return 9999999;
}

template <typename RAIterator, typename COMPARE>
void heap_sort(RAIterator begin, RAIterator end, COMPARE compare) {
  // XXX You must implement this properly.
}


#endif /* NIU_CSCI340_HEAP_H */
