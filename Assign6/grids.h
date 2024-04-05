/************************************************************************************
* NIU CSCI 340 Section 1 *
* Assignment 6 
* Oluwasegun Durosinmi - z1978798 *
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
* * Implementing a class that provides resizeable 2D grid functionality
************************************************************************************/
#ifndef NIU_CSCI_340_GRIDS_IMPL_H
#define NIU_CSCI_340_GRIDS_IMPL_H



// include the declarations needed for this
#include <iostream>
#include <fstream>
#include "grids.decl.h"

////////////////////////////////////////////////////////////////////////////////
//
// grid_row_major method implementations
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks if the given coordinates (x, y) are within the bounds of the grid.
 *
 * This function checks if the given coordinates (x, y) are within the bounds of the grid.
 *
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 * @return True if the coordinates are within bounds, false otherwise.
 */

template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::boundscheckxy(int x, int y) const {
  // Check to see if the coordinates are within the bounds of the grid
  if(x >= 0 && y >= 0 && x < this->_width && y < this->_height)
  {
    return true; //Applies if they are within bounds
  }
  else
  {
    return false;// Applies if they are out of bounds
  }
}

/**
 * @brief Checks if the given row and column indices are within the bounds of the grid.
 *
 * This function checks if the given row and column indices are within the bounds of the grid.
 *
 * @param row The row index.
 * @param col The column index.
 * @return True if the indices are within bounds, false otherwise.
 */

template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::boundscheckrc(int row, int col) const {
  // Check to the given row and column are within the bounds of the grid
  if(col >= 0 && row >= 0 && col < this->_width && row < this->_height)
  {
    return true;//Applies if they are within bounds
  }
  else
  {
    return false; // Applies if they are out of bounds
  }
}
/**
 * @brief Checks if the grid is empty.
 *
 * This function checks if the grid is empty.
 *
 * @return True if the grid is empty, false otherwise.
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::empty() const {
  // Check to see if the grid is empty
  if(this->_width == 0 && this->_height == 0)
  {
    return true; //returns if empty
  }
  else
  {
    return false; // returns if not
  }


}

/**
 * @brief Clears the grid.
 *
 * This function resets the dimensions of the grid to zero and clears the grid data.
 */

template <typename T, typename RA_CONTAINER>
void grid_row_major<T,RA_CONTAINER>::clear() {
  // Reset the dimensions to zero and clear the grid data 
  data.clear();
  this->_height = 0;
  this->_width = 0;
}

/**
 * @brief Accesses the element at the specified coordinates (x, y) in the grid.
 *
 * This function accesses the element at the specified coordinates (x, y) in the grid.
 *
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 * @return Reference to the element at the specified coordinates.
 */

template <typename T, typename RA_CONTAINER>
T & grid_row_major<T,RA_CONTAINER>::atxy(int x, int y) {
  // Access element at the coordinate x and y in the grid
  if(!boundscheckxy(x, y))
  {
    // Throw out of range exception in case
    throw std::out_of_range("The coordinates are not in range");
  }
 
 return this->data[y * this->_width + x];

}

/**
 * @brief Accesses the element at the specified coordinates (x, y) in the grid (const version).
 *
 * This function accesses the element at the specified coordinates (x, y) in the grid (const version).
 *
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 * @return Const reference to the element at the specified coordinates.
 * @throw std::out_of_range if the coordinates are out of bounds.
 */
template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T,RA_CONTAINER>::atxy(int x, int y) const {
  // Access element at the coordinate x and y in the grid, just as constants
   if(!boundscheckxy(x, y))
  {
    // Throw out of range exception in case
    throw std::out_of_range("The coordinates are not in range");
  }
 
 return this->data[y * this->_width + x];

}

/**
 * @brief Accesses the element at the specified row and column indices in the grid.
 *
 * This function accesses the element at the specified row and column indices in the grid.
 *
 * @param row The row index.
 * @param col The column index.
 * @return Reference to the element at the specified row and column.
 * @throw std::out_of_range if the indices are out of bounds.
 */

template <typename T, typename RA_CONTAINER>
T & grid_row_major<T,RA_CONTAINER>::atrc(int row, int col) {
  // Access element at the given row and column indices in the grid
   if(!boundscheckxy(col, row))
  {
    // Throw out of range exception in case
    throw std::out_of_range("The coordinates are not in range");
  }
 
 return this->data[row * this->_width + col];
}

/**
 * @brief Accesses the element at the specified row and column indices in the grid (const version).
 *
 * This function accesses the element at the specified row and column indices in the grid (const version).
 *
 * @param row The row index.
 * @param col The column index.
 * @return Const reference to the element at the specified row and column.
 * @throw std::out_of_range if the indices are out of bounds.
 */
template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T,RA_CONTAINER>::atrc(int row, int col) const {
  // Access element at the given row and column indices in the grid, just constants
  if(!boundscheckxy(col, row))
  {
    // Throw out of range exception in case
    throw std::out_of_range("The coordinates are not in range");
  }
 
 return this->data[row * this->_width + col];
}

/**
 * @brief Gets the width of the grid.
 *
 * This function returns the width of the grid.
 *
 * @return The width of the grid.
 */

template <typename T, typename RA_CONTAINER>
int grid_row_major<T,RA_CONTAINER>::width() const {
  // Getting the width of the grid
  return this->_width;
}

/**
 * @brief Gets the height of the grid.
 *
 * This function returns the height of the grid.
 *
 * @return The height of the grid.
 */

template <typename T, typename RA_CONTAINER>
int grid_row_major<T,RA_CONTAINER>::height() const {
  // Getting the height of the grid
  return this->_height;
}


/**
 * @brief Assignment operator for assigning grid data from another grid.
 *
 * This function assigns grid data from another grid using the assignment operator.
 *
 * @tparam OTHER_CONTAINER The type of the other grid container.
 * @param source The source grid from which to copy data.
 * @return Reference to the modified grid.
 */

template <typename T, typename RA_CONTAINER>
template <typename OTHER_CONTAINER>
grid_row_major <T, RA_CONTAINER> & grid_row_major<T, RA_CONTAINER>::operator = (const grid_row_major<T, OTHER_CONTAINER> & source) {
  // Assignment operator for assigning grid data from another grid
  // In this case, source
  if(this != &source)
  {
    this->_width = source._width;
    this->_height = source._height;
    this->data = source.data;
  }
  return *this;
 
}

/**
 * @brief Returns an iterator to the beginning of the specified row in the grid.
 *
 * This function returns an iterator to the beginning of the specified row in the grid.
 *
 * @param row The row index.
 * @return An iterator to the beginning of the specified row.
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowbegin(int row) {
  // Get iterator to the beginning of the row in the grid
  return data.begin() + (row * this->_width);
}

/**
 * @brief Returns an iterator to the end of the specified row in the grid.
 *
 * This function returns an iterator to the end of the specified row in the grid.
 *
 * @param row The row index.
 * @return An iterator to the end of the specified row.
 */

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowend(int row) {
   // Get iterator to the end of the row in the grid
  return (data.begin() + (row * this->_width)) + this->_width;
}

/**
 * @brief Returns an iterator to the beginning of the specified row in the grid (const version).
 *
 * This function returns an iterator to the beginning of the specified row in the grid (const version).
 *
 * @param row The row index.
 * @return A const iterator to the beginning of the specified row.
 */

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowbegin(int row) const {
  // Return an iterator to the beginning of the row in the grid (const version)
  return data.cbegin() + (row * this->_width);
}

/**
 * @brief Returns an iterator to the end of the specified row in the grid (const version).
 *
 * This function returns an iterator to the end of the specified row in the grid (const version).
 *
 * @param row The row index.
 * @return A const iterator to the end of the specified row.
 */

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowend(int row) const {
  // Return an iterator to the end of the row in the grid (const version)
  return (data.cbegin() + (row * this->_width)) + this->_width;
}

/**
 * @brief Returns an iterator to the beginning of the specified column in the grid.
 *
 * This function returns an iterator to the beginning of the specified column in the grid.
 *
 * @param col The column index.
 * @return An iterator to the beginning of the specified column.
 */

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colbegin(int col) {
  // Return a the column iterator to the beginning of the column in the grid
  return col_iterator(data.begin() + col, this->_width);
}

/**
 * @brief Returns an iterator to the end of the specified column in the grid.
 *
 * This function returns an iterator to the end of the specified column in the grid.
 *
 * @param col The column index.
 * @return An iterator to the end of the specified column.
 */

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colend(int col) {
  // Return a column iterator to the end of the column in the grid
  return col_iterator((data.begin() + col) +(this->_width * this->_height), this->_width);
}

/**
 * @brief Resizes the grid to the specified dimensions.
 *
 * This function resizes the grid to the specified dimensions.
 *
 * @param new_width The new width of the grid.
 * @param new_height The new height of the grid.
 */

template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::resize(int new_width, int new_height) {
  // Resize the grid to the specified dimensions
  data.resize(new_width * new_height);
  this->_height = new_height;
  this->_width = new_width;
}

/**
 * @brief Loads the grid data from a file.
 *
 * This function loads the grid data from a file with the specified filename.
 *
 * @param filename The name of the file to load the data from.
 * @return True if the loading was successful, false otherwise.
 */

template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::load_from_file(const std::string & filename) {
  // Load the grid data from a file called filename
  std::ifstream file(filename);
  if(!file)
  {
    //If file fails to open
    return false;
  }

  //Intializing height and width that will be read
  int file_height; 
  int file_width;

  // Read width and height from the file
  file >> file_width >> file_height;
  resize(file_width, file_height);

  // Read grid data from the file
  for(int i = 0; i < file_height; i++)
  {
    for(int j = 0; j < file_width; j++)
    {
      if(file >> this->data[i * file_width + j])
      {
        // If data is read successfully
        continue;
      }
      else
      {
        //If it fails to read it
        return false;
      }
    }
  }
  
  //If the entire process was successful
  return true; 
}

////////////////////////////////////////////////////////////////////////////////
//
// Matrix Multiplication Implementation
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Performs matrix multiplication.
 *
 * This function performs matrix multiplication on the given matrices `lhs` and `rhs`,
 * storing the result in the matrix `result`.
 *
 * @tparam GRID1 The type of the first matrix (lhs).
 * @tparam GRID2 The type of the second matrix (rhs).
 * @tparam GRID3 The type of the result matrix.
 * @param lhs The left-hand side matrix.
 * @param rhs The right-hand side matrix.
 * @param result The matrix to store the result.
 * @return True if the multiplication was successful, false otherwise.
 */

template <typename GRID1, typename GRID2, typename GRID3>
bool matrix_multiply(GRID1 lhs, GRID2 rhs, GRID3 & result) {
  // Lets see if these dimensions are okay for multiplication
  if(lhs.width() != rhs.height() || lhs.height() < 0 || rhs.width() < 0)
  {
    // If not compatable
    return false;
  }
  else
  {
    // Resize the result matrix to correct dimensions for multiplication
    result.resize(rhs.width(), lhs.height());
  }
  //Performing the multiplication
  for(int row = 0; row < result.height(); row++ )
  {
    for(int col = 0; col < result.width(); col++)
    {
      // We have to nitialize the result cell to 0
      result.atrc(row, col) = 0;
      for(int i = 0; i < lhs.width(); i++)
      {
        // Perform the dot product of row from the lhs and column from the rhs
        result.atrc(row, col) += lhs.atrc(row, i) * rhs.atrc(i, col);
      }
    }
  }
  
  //If the process is successful
  return true;
}

////////////////////////////////////////////////////////////////////////////////
//
// Column iterator implementation
//    These are for the col_iterator class I provided for you. Feel free to
// implement these to use that for your column iterators, or you can implement
// it in another way if you prefer that.
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Increments the iterator that will point to the next element in the column.
 *
 * This function will increment the iterator to point to the next element in the column.
 * It will perform a pre-increment operation.
 *
 * @return Reference to the incremented iterator.
 */
template <typename ITERATOR>
auto & col_iterator<ITERATOR>::operator ++ () { // preincrement
  // Mving the iterator to the next column
  pos += this->width;

  return *this;
}

/**
 * @brief Increments the iterator that will point to the next element in the column.
 *
 * This function will increment the iterator to point to the next element in the column.
 * It will perform a post-increment operation.
 *
 * @param Just an unused integer that is required for overloading
 * @return The temp iterator created before the increment.
 */
template <typename ITERATOR>
auto col_iterator<ITERATOR>::operator ++ (int) { // postincrement
  //Create a temp val
  col_iterator it;
  //Move the iterator to the next column
  it = *this;
  pos += this->width;

  //return the temp val before increment
  return it;
}

 /**
 * @brief Advances the iterator by a specified number of columns.
 *
 * This function advances the iterator by a specified number of columns.
 *
 * @param n The number of columns to advance the iterator by.
 * @return An iterator advanced by the specified number of columns.
 */

template <typename ITERATOR>
col_iterator <ITERATOR> col_iterator<ITERATOR>::operator + (int n) const {

  // Create a temp iterator
  col_iterator it;
  //Accessing it
  it = col_iterator(n * this->width + this->pos, this->width);

  //return the temp val
  return it;


}

/**
 * @brief Accesses the element at a specific position in the column.
 *
 * This function accesses the element at a specific position in the column
 * using the subscript operator.
 *
 * @param n The index of the element to access.
 * @return Reference to the element at the specified position.
 */

template <typename ITERATOR>
auto & col_iterator <ITERATOR>::operator [] (int n) {
  
  //Accessing the nth element in column
  return *(n * this->width + this->pos);
}

/**
 * @brief Accesses the element at a specific position in the column (const version).
 *
 * This function accesses the element at a specific position in the column
 * using the subscript operator (const version).
 *
 * @param n The index of the element to access.
 * @return Reference to the element at the specified position.
 */

template <typename ITERATOR>
const auto & col_iterator <ITERATOR>::operator [] (int n) const {
  // Access the nth element in the column just const version
  return *(n * this->width + this->pos);
}

/**
 * @brief Dereferences the iterator to access the current element.
 *
 * This function dereferences the iterator to access the current element.
 *
 * @return Reference to the current element.
 */

template <typename ITERATOR>
auto & col_iterator<ITERATOR>::operator * () {
  // Dereference the iterator to access the current element
  return *this->pos;
}

/**
 * @brief Dereferences the iterator to access the current element (const version).
 *
 * This function dereferences the iterator to access the current element (const version).
 *
 * @return Reference to the current element.
 */

template <typename ITERATOR>
const auto & col_iterator<ITERATOR>::operator * () const {
  // Dereference the iterator to access the current element just constant version
  return *this->pos;
}

/**
 * @brief Checks if two iterators point to the same position.
 *
 * This function checks if two iterators point to the same position.
 *
 * @param other The iterator to compare with.
 * @return True if the iterators point to the same position, false otherwise.
 */

template <typename ITERATOR>
bool col_iterator <ITERATOR>::operator == (const col_iterator <ITERATOR> &other) {
  // Check if two iterators are pointing to the same position
  if(pos == other.pos)
  {
    return true; //if so
  }
  else
  {
    return false; // if not
  }
}

#endif
