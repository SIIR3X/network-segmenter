#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

/**
 * @brief Splits a given string into a vector of substrings based on a specified delimiter.
 * 
 * This function takes a string and a delimiter as input and returns a vector of substrings
 * that are separated by the delimiter in the original string.
 * 
 * @param s The input string to be split.
 * @param delimiter The string used as the delimiter to split the input string.
 * @return vector<string> A vector of substrings obtained by splitting the input string by the delimiter.
 */
vector<string> split(const string& s, const string& delimiter);

#endif // UTILS_H