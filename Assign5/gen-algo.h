
#ifndef NIU_CSCI340_GEN_ALGO_IMPL_H
#define NIU_CSCI340_GEN_ALGO_IMPL_H


#include "gen-algo.decl.h"

#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std;

/**
 * @brief This template function reads lines from the input stream and then applies the provided callback function
 * to each line.
 *
 * @param instream This is the input stream.
 * @param linecb This is the callback function applied to each line.
 * @return This is the number of lines read.
 */

template <typename FN>
size_t read_lines(std::istream &instream, FN linecb) 
{
  // Line count set to zero
  size_t numLines = 0;
  // We have to create a buffer string to hold each line and also read
  string buffer_line;

  //Then we loop until there are no more lines to read from the stream
   while (getline(instream, buffer_line)) 
  {
    // We take care of the current line
      linecb(buffer_line);
      //Increment the line count
      numLines++;
  }
  //Total number of lines that we read
  return numLines;
}



/**
 * @brief This template function splits a string using the provided delimiter and applies the provided callback
 * function to each token.
 *
 * @tparam FN The type of the callback function.
 * @param instring The input string to split.
 * @param tokencb The callback function applied to each token.
 * @param delim The delimiter used for splitting the string.
 * @return The number of tokens extracted.
 */
template <typename FN>
size_t split_string_strict(const std::string &instring, FN tokencb, char delim) 
{
   // We have to create a buffer string to hold each line and also read 
  string buffer_val;
  size_t numTokens = 0; //initialize to zero

  //Iterate over each character in the string
  for(auto it = instring.begin(); it != instring.end(); ++it)
  {

    // Check if the current character might be a delimiter.
    if(*it == delim)
    {
      //Handle the current token
      tokencb(buffer_val);
      //clear buffer for next token
      buffer_val.clear();
      //Increment the token count
      numTokens++;
    }
    else
    {
      // Add the current character to the token.
      buffer_val += *it;
    }
  }

  // Check for the remaining token if theres is any.
  if(!buffer_val.empty())
  {
    // Handle the last token
    tokencb(buffer_val);
    //Increment the number of tokens found
    numTokens++;
  }

  // Return the total number of tokens found
  return numTokens;
}

/**
 * @brief This template function splits a string greedily using the provided delimiter and applies the provided
 * callback function to each token.
 *
 * @tparam FN The type of the callback function.
 * @param instring The input string to split.
 * @param tokencb The callback function applied to each token.
 * @param delim The delimiter used for splitting the string.
 * @return The number of tokens extracted.
 */

template <typename FN>
size_t split_string_greedy(const std::string &instring, FN tokencb, char delim) {
  size_t numTokens = 0; //initialize to zero
  // We have to create a buffer string to hold each line and also read 
  string buffer_val;

  // Create a flag that keeps track of non-delimiter characters.
  bool checkChar = false;

  //Iterate over each character in the string
  for(auto it = instring.begin(); it != instring.end(); ++it)
  {
    // Check if the current character might be a delimiter.
    if(*it == delim)
    {
      // Check if there are non-delimiter characters that might precede current delimiter.
      if(checkChar)
      {
        //Handle the current token
        tokencb(buffer_val);
        //clear buffer for next token
        buffer_val.clear();
        //Increment the number of tokens found
        numTokens++;
        // Reset flag for the non-delimiter characters.
        checkChar = false;
      }
     
    }
    else
    {
      // Set flag for the non-delimiter characters.
      checkChar = true;

      // Add current character to the token.
      buffer_val += *it;
    }
  }

  // Check if there non-delimiter characters are in the buffer.
  if(checkChar && !buffer_val.empty())
  {
    // Handle the last token
    tokencb(buffer_val);
    //Increment the number of tokens found
    numTokens++;
  }

  // Return the number of tokens found
  return numTokens;
}

/**
 * @brief This function prints a table to the output stream with specified format options.
 *
 * @tparam TABLE The type of the table.
 * @tparam ARRLIKE The type of the array-like object for column widths.
 * @param ost The output stream to print the table.
 * @param table The table to print.
 * @param widths The array-like object containing column widths.
 * @param maxcol The maximum number of columns to print.
 * @param pre The prefix string before each row.
 * @param sep The separator string between columns.
 * @param post The postfix string after each row.
 * @param leftalign Whether to left-align the columns.
 */

template <typename TABLE, typename ARRLIKE>
void print_table(std::ostream & ost, 
                 const TABLE & table, 
                 const ARRLIKE & widths, 
                 unsigned int maxcol, 
                 const std::string &pre, 
                 const std::string &sep,
                 const std::string &post,
                 bool leftalign) 
{
    // Iterate over each row in the table.
    for (size_t i = 0; i < table.size(); i++)
    {
      // Find the current row.
        auto row = table[i];
         // Print the prefix string first
        ost << pre;
        // Iterate over each column in the row.
        for (size_t j = 0; j < std::min(row.size(), static_cast<size_t>(maxcol)); j++) 
        {
          // Check left alignment if it is specified.
            if (leftalign) 
            {
              // Left-align the column content and print it with the width that is  specified 
                ost << left << std::setw(widths[j]) << row[j];
            } 
            else 
            {
              // Print the content of the current column.
                ost << right << std::setw(widths[j]) << row[j];
            }
              // Check if the current column is not the last column that determine whether separator should be appended.
            if (j != min(row.size(), static_cast<size_t>(maxcol)) - 1) 
            {
              // Append the separator if the current column is not the last column.
                ost << sep;
            }
        }
        // Append the postfix string to the output stream after everything else is printed
        ost << post << endl; // Make sure to end the line after each row.
    }

} 


// NOTE: This is not a template, and typically you should not put non-templated
// function definitions in header files. I'm leaving it anyway to keep things
// simpler for the assignment, but it could cause problem if multiple files
// were separately compiled after including this header. This is not happening
// for this assignment.

/**
 * @brief This function determines the minimum number of columns in a table.
 *
 * @param table The table to analyze.
 * @return The minimum number of columns.
 */

int table_min_cols(const STR_TABLE &table) {
  
  // Declare vectore to store differences in the number of colums between
  vector<int> diff;

  // Iterate over each row in the 'table' using the for_each algorithm.
  for_each(table.begin(), table.end(), [&diff](
    const vector<string> &vec)
    {
      // Push the size of the current row into the 'diff' vector.
      diff.push_back(vec.size());
    });
    // Now lets find the minimum element in diff
  auto min = min_element(diff.begin(), diff.end());

//return the minimum
  return *min;


}

/**
 * @brief This function calculates the widths of columns in a table.
 *
 * @tparam STR_TABLE The type of the table.
 * @param table The table for which to calculate column widths.
 * @return A vector containing the widths of columns.
 */

template <typename STR_TABLE>
std::vector <int> calc_widths(const STR_TABLE & table) 
{
  // If there is nothing in the table
  if(table.empty())
  {
    return{};
  }

  vector<int> widths(table[0].size(), 0);  //we  set the size of widths to table[0].size()

// Iterates over each row in the table, using a lambda function to process each row individually.
  for_each(table.begin(), table.end(), [&widths](
    const vector<string> &row)
    {
       
      for (size_t i = 0; i < row.size(); i++)
      {
        // Updates the width of the current column
        widths[i]= max(widths[i], static_cast<int>(row[i].length()));
      }
    });

    return widths;

}

// NOTE: This is not a template, and typically you should not put non-templated
// function definitions in header files. I'm leaving it anyway to keep things
// simpler for the assignment, but it could cause problem if multiple files
// were separately compiled after including this header. This is not happening
// for this assignment.

/**
 * @brief This function loads a table from a tab-separated values file.
 *
 * @param filename The name of TSV file that we want to load.
 * @return The loaded table.
 */

STR_TABLE load_tsv(const std::string & filename) {
  
  STR_TABLE table;

  // Try openning the specified file
  ifstream file(filename);
  if(!file.is_open())
  {
    // Throw a runtime exception if the file cannot be opened
    throw runtime_error("File cannot be open");
  }
  else
  {
    // Read lines from file and split them into tokens
    read_lines(file, [&](const string& line)
    {
      vector<string> col;
      // Splitting each line into tokens using the tab delimiter ('\t')
      split_string_strict(line, [&col](const string& token)
      {
        // Adding each token as a column in present row
        col.push_back(token);
      },'\t');

      // Adding the token line as a row to the table
      table.push_back(col);
    });

    return table;
  }

  


}

// NOTE: This is not a template, and typically you should not put non-templated
// function definitions in header files. I'm leaving it anyway to keep things
// simpler for the assignment, but it could cause problem if multiple files
// were separately compiled after including this header. This is not happening
// for this assignment.

/**
 * @brief This function sorts a table in alphabetic order based on a specified column.
 *
 * @param table The table that we are sorting.
 * @param col The index of column to sort
 */

void table_sort_alpha(STR_TABLE & table, unsigned int col) 
{
   
  sort(table.begin(), table.end(), [&](const vector<string> v1, const vector<string>v2)
  {
    // Sorting based on the values in the column
    return v1[col] < v2[col];
  }); 
}

// NOTE: This is not a template, and typically you should not put non-templated
// function definitions in header files. I'm leaving it anyway to keep things
// simpler for the assignment, but it could cause problem if multiple files
// were separately compiled after including this header. This is not happening
// for this assignment.

/*
  In table_sort_numer, converting strings to doubles for comparison involves handling 
  potential std::invalid_argument exceptions from std::stod. Correctly managing these 
  exceptions and ensuring default values are used when conversion fails helps avoid 
  runtime errors.
*/

/**
 * @brief This function sorts the table numerically based on a specified column.
 *
 * @param table The table to sort.
 * @param col The index of the column to sort by.
 */

void table_sort_numer(STR_TABLE & table, unsigned int col) 
{
  sort(table.begin(), table.end(), [&](const vector<string> v1, const vector<string>v2)
  {

    // Initializes the flags to track whether the conversion from string to double has been successful for each value in the compared rows.

    bool var1_assign = false;   
    bool var2_assign = false;
    
    // Initializes variables to hold the double representations of the values in the specified column for the two rows being compared.
    double var1 = 0.0;    
    double var2 = 0.0;

    try
    {
      // Checks if the string value is not empty before trying to convert
        {
          //String to double while assigning to variable 1
        var1 = stod(v1[col]);
        //For succesful conversion
        var1_assign = true;
        }

        if(!v1[col].empty())
        {
          //String to double while assigning to variable 2
        var2 = stod(v2[col]);
        //For succesful conversion
        var2_assign = true;
        }
    }
    catch(const std::invalid_argument& ia)
    {
      // in case var1 failed, sets var1 to 0.0 as a default value.
        if (!var1_assign)
            var1 = 0.0;
        // Same for var2
        if (!var2_assign)
            var2 = 0.0;

    }
    //compares the double values and returns true if var1 is lesser
    
    return var1 < var2;
  });
}



#endif
