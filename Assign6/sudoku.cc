/************************************************************************************
* NIU CSCI 340 Section 1 *
* Assignment 6
* Oluwasasegun Durosinmi   Z1978798 *
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
*  This assignment uses STL associative container types map and set to create a sudoku solver using INI files
************************************************************************************/

// Implementations of the sudoku functions go in this file
// Details can be found in README.md

#include "settings.h"
#include "sudoku.h"
#include <iostream>
#include <set>
#include <vector>
#include <sstream>
#include "grids.h" 
#include <string>

using namespace std;

// Function to mark a Sudoku cell as known
void set_sudoku_cell_known(SUDOKUGRID &grid, int row, int col, int solution) {
  // If the possibility is not the solution, erase it
      grid.atrc(row, col).clear();
    
  
   grid.atrc(row, col).insert(solution);
}

// Function to mark a Sudoku cell as unknown
void set_sudoku_cell_unknown(SUDOKUGRID &grid, int row, int col) {
  // Fill the cell with all possibilities (1-9)
  for(int i = 1; i <= 9; i++)
  {
    grid.atrc(row, col).insert(i);
  }
}

// Function to remove a specific possibility from a Sudoku cell
void remove_sudoku_option(SUDOKUGRID &grid, int row, int col, int value) {
  // Erase the specified value from the cell's possibilities
  grid.atrc(row, col).erase(value);
}

// Function to print the Sudoku grid
void print_sudoku_grid(std::ostream & ost, const SUDOKUGRID &grid, char unknown, char impossible) {
  // Iterate over each cell in the grid
  for(int i = 0; i < 9; i++)
  {
      if (i != 0 && i % 3 == 0) 
      {
        // Print horizontal divider for subgrids every 3 rows
        ost << "---------|---------|---------\n";
      }

    for(int j = 0; j < 9; j++)
    {
        if (j != 0 && j % 3 == 0) 
        {
        // Print vertical divider for subgrids every 3 columns
        ost << "|";
        }

      if(grid.atrc(i, j).size() == 1)
      {
        // If only one possibility, print the value
        ost << " " << *grid.atrc(i, j).begin() << " ";
      }
      else if(grid.atrc(i, j).size() == 0)
      {
        // If no possibilities, print the impossible character
        ost << " " << impossible << " ";
      }
      else
      {
        // If multiple possibilities, print the unknown character
        ost <<  " " << unknown << " ";
      }
    }
    ost << endl;
  }
  ost << endl;
}

////////////////////////////////////////////////////////////////////////////////
// This one is provided. You do not need to change it.
////////////////////////////////////////////////////////////////////////////////
// Function to handle a Sudoku cell and remove its value from possibilities of other cells
int handle_sudoku_cell(SUDOKUGRID &grid, int row, int col) {
  int count = 0;

  // Call functions to handle the cell for row, column, and subgrid
  count += handle_row_for_cell(grid, row, col); 
  count += handle_col_for_cell(grid, row, col); 
  count += handle_subgrid_for_cell(grid, row, col); 

  return count; 
}

// Function to handle a Sudoku cell to remove its value from possibilities of other cells in the same row
int handle_row_for_cell(SUDOKUGRID &grid, int row, int col) {
  int numPosb = 0;

  for(int i = 0; i < 9; i++)
  {
    if(grid.atrc(row, col).size()  == 1)
    {
      auto it = grid.atrc(row, col).begin();
      if(i == col)
      {
        continue;
      }
      numPosb += grid.atrc(row, i).erase(*it);
    }
  }
  return numPosb;
}

// Function to handle a Sudoku cell to remove its value from possibilities of other cells in the same column
int handle_col_for_cell(SUDOKUGRID &grid, int row, int col) {
  int numPosb = 0;

  for(int i = 0; i < 9; i++)
  {
    if(grid.atrc(row, col).size()  == 1)
    {
      auto it = grid.atrc(row, col).begin();
      if(i == row)
      {
        continue;
      }
      numPosb += grid.atrc(i, col).erase(*it);
    }
  }
  return numPosb;
}

// Function to handle a Sudoku cell to remove its value from possibilities of other cells in the same subgrid
int handle_subgrid_for_cell(SUDOKUGRID &grid, int row, int col) {
  int numPosb = 0;
  int start_row = (row / 3) * 3;
  int start_col = (col / 3) * 3;

  for(int i = start_row; i < start_row + 3; i++)
  {
    for(int j = start_col; j < start_col + 3; j++)
    {
      if(grid.atrc(row, col).size()  == 1)
      {
        auto it = grid.atrc(row, col).begin();
        if(i == row && j == col)
        {
          continue;
        }
        else
        {
          numPosb += grid.atrc(i, j).erase(*it);
        }
      }
    }
  }
  return numPosb;
}

// Function to load a Sudoku grid from a file
bool load_sudoku_grid(const std::string &filename, SUDOKUGRID &grid) {
  std::ifstream file(filename);

  if (!file.is_open()) 
  {
    std::cerr << "Error: Unable to open file " << filename << std::endl;
    return false;
  }

  int width, height;
  file >> width >> height;

  if (width != 9 || height != 9) {
    std::cerr << "Error: Invalid dimensions. Sudoku grid must be 9x9." << std::endl;
    file.close();
    return false;
  }

  grid.resize(9, 9);

  for (int i = 0; i < 9; i++) 
  {
    for (int j = 0; j < 9; j++) 
    {
      int val;
      file >> val;

      if (val < 0 || val > 9) {
        std::cerr << "Error: Invalid value in grid (" << i << ", " << j << "). Value must be between 0 and 9." << std::endl;
        file.close();
        return false;
      }

      if (val != 0) 
      {
        grid.atrc(i, j) = {val};
      } 
      else 
      {
        for (int k = 1; k <= 9; k++) 
        {
          grid.atrc(i, j).insert(k);
          }
      }
    }
  } 

  file.close();
  return true;
}

////////////////////////////////////////////////////////////////////////////////
// This is what the implementation looks like for grid_row_major,
// if you're using another SUDOKUGRID type, you will likely have to change it.
////////////////////////////////////////////////////////////////////////////////
// Function to initialize the Sudoku grid
void initialize_grid(SUDOKUGRID &grid) {
  grid.resize(9,9);
}
