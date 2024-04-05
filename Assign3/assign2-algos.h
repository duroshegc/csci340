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
* * Writing Algorithms that use iterators to perform some simple computing tasks.
* * They will be implemented using template functions.
************************************************************************************/

#ifndef NIUCSCI340ASSIGN2_ALGOS_H
#define NIUCSCI340ASSIGN2_ALGOS_H


#include <iomanip>
#include "assign2-algos.decl.h"

// Implement your algorithms for assignment 2 here.

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Get the next token for a string in strict mode.
 *
 * @param begin The beginning of the sequence being inputed.
 * @param end The end of the sequence being inputed.
 * @param delim The delimiter used to separate tokens.
 * @tparam ITERATOR The type of iterator sequence being inputed.
 * @tparam T The type of the delimiter.
 * @return A token_info structure containing information about the next token.
 */

template <typename ITERATOR, typename T>
token_info<ITERATOR> get_next_token_strict(ITERATOR begin, ITERATOR end, T delim) {

  token_info<ITERATOR> just_stop;
  just_stop.t_begin = begin;
  just_stop.t_end = end;
  just_stop.t_next = end;

  // Create an iterator variable that will go through the range
  ITERATOR it;

  //Count through the input sequence until the end or delimeter is found
  for(it = begin; it != end; it++)
  {
    // if delim is found, change the just.stop token and stop the loop
    if(*it == delim)
    {
      //Update the justdtop end and next token
      just_stop.t_end = it;
      just_stop.t_next = it + 1;
      //Stop the if statment
      break;
    }
  }
  return just_stop; //Return the token info
}

/**
 * @brief Get the next token in a string, greedy mode.
 *
 * This function searches for the next token delimited by the specified delimiter in the input sequence,
 * using the greedy approach, where the leading trailing delimiters are ignored.
 * It returns a token_info structure containing information about the token found.
 *
 * @param begin The beginning of the input sequence.
 * @param end The end of the input sequence.
 * @param delim The delimiter used to difer tokens.
 * @tparam ITERATOR The type of iterator for the input sequence.
 * @tparam T The type of the delimiter.
 * @return A token_info structure containing information about the next token.
 */

template <typename ITERATOR, typename T>
token_info<ITERATOR> get_next_token_greedy(ITERATOR begin, ITERATOR end, T delim) {

  token_info<ITERATOR> just_stop;
  just_stop.t_begin = begin;
  just_stop.t_end = end;
  just_stop.t_next = end;

  // Create an iterator variable that will go through the range
  ITERATOR it;

  //creating a boolean value used to verify the end
  bool foundEnd = false;

  //Check if the beginning starts as a delimeter
  if(*begin == delim)
  {
    //Skip leading delimeters
    for(it = begin; it != end; it++)
    {
      //Check if the current character is not equal to delim
      if(*it != delim)
      {
        // If its not, set the begin update token info
        begin = it;
        just_stop.t_begin = it;

        //Then exit loop once its found
        break;
      }
    }
  }

  //Count through the input sequence until the end or delimeter is found
  for(it = begin; it != end; it++)
  {
    // Check for the end of the token
    if(*it == delim && !foundEnd)
    {
      just_stop.t_end = it;
      foundEnd = true;
    }

    //After the end of the token, we have to find the beginning of the next
    if(*it != delim && foundEnd)
    {
      //Update token info then exit loop
      just_stop.t_next = it;
      break;
    }
  }

  return just_stop;

}

/**
 * @brief Calculate the histogram of a range of values.
 *
 * This function computes the histogram of a range of values and stores the bin counts in a random access container.
 *
 * @param begin The beginning of the input sequence.
 * @param end The end of the input sequence.
 * @param bin_counts Reference to the array storing bin counts.
 * @param N The number of bins.
 * @param width The width of each bin.
 * @tparam ITERATOR The type of iterator for the input sequence.
 * @tparam RANDOM_ACCESS The type of random access container for bin counts.
 */

template<typename ITERATOR, typename RANDOM_ACCESS>
void histogram(ITERATOR begin, ITERATOR end, RANDOM_ACCESS & bin_counts, int N, double width) {

  // Create an iterator variable that will go through the range
  //ITERATOR it;

  //Iterate over first, then initialize all bin counts to zero
  bin_counts.resize(N);
 /* for(ITERATOR it = bin_counts.begin(); it != bin_counts.end(); it++)
  {
    *it = 0;
  }*/

  //Then we calculate bin counts based on the values in the input range
  for(ITERATOR it = begin; it != end; it++)
  {
    int i = *it / width;

    if(i >= 0 && i < N)
    {
      bin_counts[i]++;
    }
    
  }
}

/**
 * @brief Print the elements of a range.
 *
 * This function prints the elements of a range with specified formatting to the given output stream.
 *
 * @param ost The output stream.
 * @param begin The beginning of the input sequence.
 * @param end The end of the input sequence.
 * @param pre The string to be printed before the range.
 * @param sep The separator string between elements.
 * @param post The string to be printed after the range.
 * @param width The width used for printing each element.
 * @tparam ITERATOR The type of iterator for the input sequence.
 */

template <typename ITERATOR>
void print_range(std::ostream & ost, ITERATOR begin, ITERATOR end, const std::string &pre, const std::string &sep, const std::string &post, int width) {
  // Iterate throght the range
  //ITERATOR it;

  //Determining if the first element
  bool isBegin = true;

  //Printing the prefix string before looping through range
  ost << pre;
  for(ITERATOR it = begin; it != end; it++)
  {
    if(isBegin) // Check if its the first element
    {
      isBegin = false;// Set it to false fr subsequent elements
    }
    else
    //If it's not the first, then we can just print the seperator string between elements
      ost << sep;

    ost << setw(width) << *it;// We make sure we add the width needed 
    
  }
  // Lastly, print postfix string after range
  ost << post;
};

/**
 * @brief Calculate the sum of a range of values.
 *
 * This function calculates the sum of all elements in a range.
 *
 * @param begin The beginning of the input sequence.
 * @param end The end of the input sequence.
 * @tparam ITERATOR The type of iterator for the input sequence.
 * @return The sum of the elements in the range.
 */

template <typename ITERATOR>
double range_sum(ITERATOR begin, ITERATOR end) {
  //Store the sum of elements in this variable
  int sum = 0;
  // Create an iterator variable that will go through the range
  //ITERATOR it;
  //Calculate the sum after iterating over
  for(ITERATOR it = begin; it != end; it++)
  {
    sum += *it;
  }
  //Return sum
  return sum;
}

/**
 * @brief Calculate the average of a range of values.
 *
 * This function calculates the average of all elements in a range.
 *
 * @param begin The beginning of the input sequence.
 * @param end The end of the input sequence.
 * @tparam ITERATOR The type of iterator for the input sequence.
 * @return The average of the elements in the range.
 */

template <typename ITERATOR>
double range_avg(ITERATOR begin, ITERATOR end) {
  //Variable storing mean
  double mean = 0;

  //Storing sum
  double sum = 0;

  // Create an iterator variable that will go through the range
  //ITERATOR it;

  // Variable for count
  double numTimes = 0;

  //Iterate over the range, then count elements in it
  for(ITERATOR it = begin; it != end; it++)
  {
    sum+= *it;
    numTimes++;
  }

  //Calculate the mean
  mean = sum / numTimes;

  //Return the mean
  return mean;
}

/**
 * @brief Find the maximum value in a range.
 *
 * This function finds and returns the maximum value in the given range.
 *
 * @param begin The beginning of the input sequence.
 * @param end The end of the input sequence.
 * @tparam ITERATOR The type of iterator for the input sequence.
 * @return The maximum value in the range.
 */

template <typename ITERATOR>
auto range_maxval(ITERATOR begin, ITERATOR end) {
  // varriable for max value
  int max;

  //Initialize the first element to max
  max = *begin;

  // Create an iterator variable that will go through the range
  //ITERATOR it;

  //Find the max value in the range
  for(ITERATOR it = begin; it != end; it++)
  {
    if(*it > max) // Check if the current element is greater than max
    {
      max = *it; //Update it if so
    }
  }

  return max;// Then return max value
}

/**
 * @brief Find the minimum value in a range.
 *
 * This function finds and returns the minimum value in the given range.
 *
 * @param begin The beginning of the input sequence.
 * @param end The end of the input sequence.
 * @tparam ITERATOR The type of iterator for the input sequence.
 * @return The minimum value in the range.
 */

template <typename ITERATOR>
auto range_minval(ITERATOR begin, ITERATOR end) {
  // Variable for min value
  int min;

  //Create an iterator variable that will go through the range
  //ITERATOR it;

  //Initialize min with first element
  min = *begin;

  //Find the minimum value
  for(ITERATOR it = begin; it != end; it++)
  {
    if(*it < min)// Check if the current element is lesser
    {
      min = *it;// If so update it
    }
  }

  return min; // Return min value
}


/**
 * @brief Count the number of elements in a range.
 *
 * This function counts and returns the number of elements in the given range.
 *
 * @param begin The beginning of the input sequence.
 * @param end The end of the input sequence.
 * @tparam ITERATOR The type of iterator for the input sequence.
 * @return The number of elements in the range.
 */

template <typename ITERATOR>
int range_count(ITERATOR begin, ITERATOR end) {
  //Create an iterator variable that will go through the range
  //ITERATOR it;

  // Create count val
  int count = 0;

  //Iterate over the number of elements in range
  for(ITERATOR it = begin; it != end; it++)
  {
    count++;// Increment the count of each element
  }
  return count;// Return the count
}


#endif /*NIUCSCI340ASSIGN2_ALGOS_H*/