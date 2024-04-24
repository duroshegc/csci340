#ifndef NIU_CSCI340_HEAP_H
#define NIU_CSCI340_HEAP_H

#include <algorithm>
#include <stdexcept>
#include <utility>

using namespace std;

inline constexpr size_t heap_left(size_t node) { 
  size_t left = 2 * node + 1;
  return left;
}
inline constexpr size_t heap_right(size_t node) { 
  size_t right = 2 * node + 2;
  return right;
}
inline constexpr size_t heap_parent(size_t node) {
  if(node <= 0)
  {
    return 0;
  }
  else
  {
    size_t parent = (node - 1)/ 2;
    return parent;
  }


}

template <typename ArrayLike, typename FN>
void heap_preorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
  if(node < heapnodes)
  {
    fn(node);
    heap_preorder(heapdata, heapnodes, (2 * node) + 1, fn);
    heap_preorder(heapdata, heapnodes, (2 * node) + 2, fn);
  }
}

template <typename ArrayLike, typename FN>
void heap_inorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
  if(node < heapnodes)
  {
    heap_inorder(heapdata, heapnodes, (2 * node) + 1, fn);
    fn(node);
    heap_inorder(heapdata, heapnodes, (2 * node) + 2, fn);
  }
}

template <typename ArrayLike, typename FN>
void heap_postorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
  if(node < heapnodes)
  {
    heap_postorder(heapdata, heapnodes, (2 * node) + 1, fn);
    heap_postorder(heapdata, heapnodes, (2 * node) + 2, fn);
    fn(node);
  }
}

template <typename ArrayLike, typename FN>
void heap_levelorder(ArrayLike & heapdata, size_t heapnodes, FN fn) {
  for(size_t i = 0; i < heapnodes; i++)
  {
    fn(heapdata[i]);
  }
}

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

template <typename RAIterator, typename COMPARE>
size_t heap_bubble_down(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
  auto parent_index = start;
  auto parent = begin + parent_index;
  auto left_child_index = 2 * parent_index + 1;
  auto left_child = begin + left_child_index;
  auto right_child_index = 2 * parent_index + 2;
  auto right_child = begin + right_child_index;
  size_t swaps = 0;
  RAIterator ans;
  size_t ans_index;

  if(right_child_index >= nodes)
  {
    ans = left_child;
    ans_index = left_child_index;
  }
  else
  {
    if(compare(*left_child, *right_child))
    {
      ans = left_child;
      ans_index = left_child_index;
    }
    else
    {
      ans = right_child;
      ans_index = right_child_index;
    }
  }


  
  while(parent_index < nodes && compare(*ans, *parent))
  {
    swap(*ans, *parent);
    parent_index = ans_index;
    parent = ans;
    left_child_index = 2 * parent_index + 1;
    left_child = begin + left_child_index;
    right_child_index = 2 * parent_index + 2;
    right_child = begin + right_child_index;
    swaps++;
    if(right_child_index >= nodes)
    {
      ans = left_child;
      ans_index = left_child_index;
    }
    else
    {
      if(compare(*left_child, *right_child))
      {
        ans = left_child;
        ans_index = left_child_index;
      }
      else
      {
        ans = right_child;
        ans_index = right_child_index;
      }
    }
  }

  return swaps;
}

template <typename T, typename CONTAINER, typename COMPARISON>
void heap_insert(CONTAINER & heapdata, size_t &nodes, T key, COMPARISON compare) {
  auto root = key;
  auto left_child = 2 * key + 1;
  auto right_child = 2 * key + 2;

  if(compare())
  {
    root = left_child
  } 

  if(right_child < nodes && heapdata[right_child] > heapdata[root])
  {
    root = right_child
  }

  if(root != key)
  {
    swap(heapdata[key], heapdata[root] );

    heap_insert(heapdata, nodes, );
  }

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
