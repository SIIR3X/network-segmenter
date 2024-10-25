#include "utils/utils.h"
#include "address/ipv6_address.h"
#include <algorithm>

/**
 * @brief Overloads the += operator to increment the IPv6 address by a given vector of uint8_t.
 *
 * This function performs an addition operation on the IPv6 address, incrementing it by the values
 * provided in the input vector. The addition is performed in reverse order, starting from the least
 * significant byte, and handles carry-over for each byte.
 *
 * @param increment A vector of uint8_t values to add to the IPv6 address.
 * @return A reference to the updated IPv6Address object.
 */
IPv6Address& IPv6Address::operator +=(const vector<uint8_t>& increment)
{
	// Initialize variables for the addition operation
	int carry = 0;
	auto addressIt = _address.rbegin();
	auto incrementIt = increment.rbegin();

	// Iterate over the address and increment vectors
	while (incrementIt != increment.rend() || carry != 0)
	{
		int sum = carry;

		// Add the corresponding elements from the address and increment vectors
		if (incrementIt != increment.rend())
		{
			sum += *incrementIt;
			++incrementIt;
		}

		// Update the current hextet in the address
		if (addressIt != _address.rend())
		{
			sum += *addressIt;
			*addressIt = sum & 0xFF;
			++addressIt;
		}
		else
		{
			_address.insert(_address.begin(), sum & 0xFF);
		}

		// Update the carry for the next iteration
		carry = sum >> 8;
	}

	return *this;
}

/**
 * @brief Prints the IPv6 address to the given output stream.
 *
 * This function prints the IPv6 address in a compressed format by finding the longest sequence
 * of consecutive zero hextets and replacing them with "::". It iterates over the hextets of the
 * IPv6 address and prints them to the stream, skipping the hextets that are part of the longest
 * zero sequence.
 *
 * @param s The output stream to print the IPv6 address to.
 * @return ostream& A reference to the output stream.
 */
ostream& IPv6Address::print(ostream& s) const
{
	// Find the longest sequence of consecutive zero hextets
	auto longestZeroSequence = findLongestZeroSequence();
	
	int start = longestZeroSequence.first;
	int end = longestZeroSequence.second;

	// Iterate over the hextets and print them to the stream
	for (int i = 0; i < IPV6_NUM_HEXTETS; ++i)
	{
		// Print a colon before the longest zero sequence
		if (i == start)
		{
			s << ":";
		}

		// If the hextet is part of the longest zero sequence, skip it
		if (i >= start && i <= end)
		{
			continue;
		}

		// Get the current hextet
		uint16_t hextet = this->operator[](i);

		// Print the hextet to the stream
		s << hex << (int)hextet << dec;

		// Print a colon after the hextet if it is not the last hextet
		if (i < IPV6_NUM_HEXTETS - 1 && i != end)
		{
			s << ":";
		}
	}

	return s;
}

/**
 * @brief Sets the IPv6 address from a string representation.
 *
 * This function parses the given IPv6 address string and sets the internal
 * address representation. It supports the "::" compression for zero hextets.
 *
 * @param address The string representation of the IPv6 address.
 * @throws std::invalid_argument if the address is not a valid IPv6 address.
 */
void IPv6Address::setAddress(const string& address)
{
	// Create a vector to store the hextets
	vector<string> hextets;

	// Check if the address contains the "::" compression
	if (address.find("::") != string::npos)
	{
		// Split the address into parts before and after the "::"
		vector<string> parts = split(address, "::");

		// Split the left and right parts into hextets
		vector<string> leftPart = parts[0].empty() ? vector<string>() : split(parts[0], ":");
		vector<string> rightPart = parts[1].empty() ? vector<string>() : split(parts[1], ":");

		// Combine the left and right parts with zeros in between
		hextets.insert(hextets.end(), leftPart.begin(), leftPart.end());
		hextets.resize(IPV6_NUM_HEXTETS - rightPart.size(), "0");
		hextets.insert(hextets.end(), rightPart.begin(), rightPart.end());
	}
	else
	{
		// Split the address into hextets
		hextets = split(address, ":");
	}

	// Check if the address has the correct number of hextets
	if (hextets.size() != IPV6_NUM_HEXTETS)
	{
		throw invalid_argument("Invalid address format: must have " + to_string(IPV6_NUM_HEXTETS) + " parts.");
	}

	// Iterate over the hextets and set the address
	for (size_t i = 0; i < IPV6_NUM_HEXTETS; ++i)
	{
		// Get the current hextet
		const string& hextet = hextets[i];

		// Check if the hextet is empty or contains non-hexadecimal characters
		if (hextet.empty() || !all_of(hextet.begin(), hextet.end(), ::isxdigit))
		{
			throw invalid_argument("Invalid address format: hextets must be non-empty and contain only hexadecimal digits.");
		}

		// Convert the hextet to an integer
		int hextetValue = stoi(hextet, nullptr, 16);

		// Check if the hextet is within the valid range
		if (hextetValue < 0 || hextetValue > 0xFFFF)
		{
			throw invalid_argument("Invalid address format: hextets must be between 0x0000 and 0xFFFF.");
		}

		// Calculate the index in the address array
		size_t j = i * 2;

		// Set the hextet value in the address
		_address[j] = (uint8_t)(hextetValue >> 8);
		_address[j + 1] = (uint8_t)(hextetValue & 0xFF);
	}
}

/**
 * @brief Finds the longest sequence of consecutive zero hextets in the IPv6 address.
 *
 * This function iterates over the hextets of the IPv6 address and identifies the longest
 * sequence of consecutive zero hextets. It returns the start and end indices of this sequence.
 *
 * @return pair<int, int> A pair of integers representing the start and end indices of the longest zero sequence.
 */
pair<int, int> IPv6Address::findLongestZeroSequence() const
{
	// Initialize variables to store the longest zero sequence
	int longestStart = -1;
	int longestLength = 0;

	// Initialize variables to store the current zero sequence
	int currentStart = -1;
	int currentLength = 0;

	// Iterate over the hextets to find the longest zero sequence
	for (int i = 0; i < IPV6_NUM_HEXTETS; ++i)
	{
		// Get the current hextet
		uint16_t hextet = this->operator[](i);

		// Check if the hextet is zero
		if (hextet == 0)
		{
			// If the current sequence has not started, set the start index
			if (currentStart == -1)
			{
				currentStart = i;
			}

			currentLength++;
		}
		else
		{
			// If the current sequence has ended, check if it is the longest sequence
			if (currentLength > longestLength)
			{
				longestStart = currentStart;
				longestLength = currentLength;
			}

			// Reset the current sequence
			currentStart = -1;
			currentLength = 0;
		}
	}

	// Check if the current sequence is the longest sequence
	if (currentLength > longestLength)
	{
		longestStart = currentStart;
		longestLength = currentLength;
	}

	// Return the start and end indices of the longest zero sequence
	return (longestStart == -1) ? make_pair(-1, -1) : make_pair(longestStart, longestStart + longestLength - 1);
}