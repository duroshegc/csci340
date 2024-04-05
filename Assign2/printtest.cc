
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "assign2-algos.h"

template <typename CONTAINER>
void test_print_range(std::ostream & ost, const char * label, int argc, const char * const argv[], const char *pre, const char *sep, const char *post) {
  using namespace std;

  const std::string indent = "  ";

  ost << "Testing print_range with (" << label << ")";


  // handle command line arguments
  CONTAINER input{};
  if(argc > 1) {
    cout << " - Found command-line arguments, using them for sequence.\n"; 
    for(int i=1;i<argc;++i) {
      input.push_back(atoi(argv[i])); 
    }
  }
  else {
    ost << " - No command-line arguments, using default sequence.\n";
    input = { 8, 6, 7, 5, 3, 0, 9, 1, 800, 22263, 63, 588, 2300, 367473};
  }

  cout << indent << "sequence: ";
  for(auto x : input) { cout << x << " "; }
  cout << "\n";
  cout << indent << "pre = \"" << pre << "\" ; ";
  cout << "sep = \"" << sep << "\" ; ";
  cout << "post = \"" << post << "\"\n\n";

  for(int colw = 0; colw < 9; ++colw) {
    cout << indent << "colw=" << colw << ": " ;
    print_range(ost, input.begin(), input.end(), pre, sep, post, colw);
    cout << "\n";
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
  using namespace std;
  const char *indent = "  ";

  cout << "// printtest - testing print_range with various parameters\n";
  cout << "// \n";
  cout << "//   This test program prints out a given range using the print_range function  \n";
  cout << "// that you are required to implement. It tries it on multiple container types, \n";
  cout << "// with different parameters used so you can make sure your function does what  \n";
  cout << "// is required with them.                                                       \n";
  cout << "//                                                                              \n";
  cout << "//   The reference output provided to you was generated by running the program  \n";
  cout << "// without any arguments. It can also be tested with another sequence by        \n";
  cout << "// passing integers as command-line arguments.                                  \n";
  cout << "////////////////////////////////////////////////////////////////////////////////\n";
  cout << "\n";

  if(argc > 1) {
    cout << "Command line arguments:\n";
    for(int i=1; i<argc; ++i) { 
      cout << indent << i << ") \"" << argv[i] << "\"\n"; } }

  test_print_range<vector<int>>(cout, "vector", argc, argv, "[ ", ", ", " ]"); 
  test_print_range<deque<int>>(cout, "deque", argc, argv, "| ", " | ", " |"); 
  test_print_range<list<int>>(cout, "list", argc, argv, "(", ") -> (", ") -> end"); 
}