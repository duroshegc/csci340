/************************************************************************************
* NIU CSCI 340 Section YOUR_SECTION *
* Assignment 1
* Oluwasegun Durosinmi - z1978798*
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
* * Generating random integers that are stored in a STL vector, and the reverse of it into
* another vector, then printing them out.
************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>

using namespace std;

//Constant Low that does not change
const int LOW = 1;

/**
 * @brief Generates random numbers and populates a vector.
 * 
 * This function clears the input vector, sets the seed for the random number
 * generator, generates random numbers within the specified range, and adds them
 * to the vector.
 * 
 * @param v Reference to the vector where random numbers will be stored.
 * @param seed Seed value for the random number generator.
 * @param range_limit Upper limit for the random numbers.
 * @param vec_size Size of the vector to be filled.
 */

void gen_rnd_nums (vector < int >& v , int seed, int range_limit, int vec_size)
{
    //Clear vector first
    v.clear();

    //Set the see value for the random number generator
    srand(seed);

    for(int i = 0; i < vec_size; i++)
    {
        //Generate random number within the specified range and put it in the vector
        int rand_val = rand() % range_limit + 1;
        v.push_back(rand_val);
    }

}

/**
 * @brief Copies elements of one vector into another in reverse order.
 * 
 * This function checks if the sizes of two vectors are equal. If they are,
 * it copies elements from the source vector to the destination vector in reverse order.
 * 
 * @param v1 Reference to the source vector.
 * @param v2 Reference to the destination vector.
 * @return -1 if the sizes of v1 and v2 are different, 1 if successful.
 */

int reverse_copy(vector < int >& v1, vector < int >& v2)
{
    if(v1.size() != v2.size())
    {
        //If the size differ, return negative 1
        return -1;
    }
    
    int j = 0;
    for(int i = v1.size() - 1; i >= 0; i--)
    {
        //Then we copy elements from v1 to v2 in reverse order
        v2[j] = v1[i];
        j++;
    }
    return 1;
}

/**
 * @brief Prints the elements of a vector with specified formatting.
 * 
 * This function prints the elements of the vector with a specified number of
 * items per row and item width.
 * 
 * @param v Reference to the vector to be printed.
 * @param items_per_row Number of items to print per row.
 * @param item_width Width of each item in the output.
 */

void print_vec ( const vector <int>& v, int items_per_row, int item_width)
{
    for(size_t i = 0; i < v.size(); i++)
    {
        

        if((int)i % items_per_row == 0)
        {
            // Start end line after item per row has been printed
            cout << endl;
        }
        //Setting the width of each item
        cout << setw(item_width) << v[i];

    }
    //End line needed for each
    cout << endl;
}