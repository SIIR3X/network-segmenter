#include "utils/utils.h"
#include <sstream>

/**
 * @brief Splits a string into a vector of substrings based on a specified delimiter.
 *
 * This function takes a string and a delimiter, and splits the string into 
 * multiple substrings wherever the delimiter is found. The resulting substrings 
 * are stored in a vector and returned.
 *
 * @param s The input string to be split.
 * @param delimiter The delimiter string used to split the input string.
 * @return vector<string> A vector of substrings obtained by splitting the input string.
 */
vector<string> split(const string& s, const string& delimiter)
{
	vector<string> tokens;
	size_t start = 0, end = 0;

	// Iterate over the string and split it using the delimiter
	while ((end = s.find(delimiter, start)) != string::npos)
	{
		tokens.push_back(s.substr(start, end - start));
		start = end + delimiter.length();
	}

	// Add the last token
	tokens.push_back(s.substr(start));

	return tokens;
}