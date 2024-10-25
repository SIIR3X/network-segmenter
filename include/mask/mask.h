#ifndef MASK_H
#define MASK_H

#include <string>
#include <vector>
#include <cstdint>
#include <ostream>
#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace std;

#define MASK_MIN_PREFIX 1 ///< The minimum prefix length for a network mask.
#define MASK_MAX_PREFIX 128 ///< The maximum prefix length for a network mask.

/**
 * @class Mask
 * @brief Represents a network mask.
 */
class Mask 
{
private:
	/**
	 * @brief The prefix length of the network mask.
	 */
	int _prefixLength;

	/**
	 * @brief A vector containing the octets of the network mask.
	 * 
	 * This vector stores the individual octets (8-bit values) that make up the network mask.
	 * Each element in the vector represents one octet of the mask.
	 */
	vector<uint8_t> _maskOctets;

	/**
	 * @brief Checks if the given prefix length is valid.
	 * 
	 * This function verifies whether the provided prefix length falls within the
	 * acceptable range defined by MASK_MIN_PREFIX and MASK_MAX_PREFIX.
	 * 
	 * @param prefixLength The prefix length to be validated.
	 * @return bool true if the prefix length is within the valid range, false otherwise.
	 */
	bool isValidPrefixLength(int prefixLength) const
	{
		return prefixLength >= MASK_MIN_PREFIX && prefixLength <= MASK_MAX_PREFIX;
	}

	/**
	 * @brief Sets the octets of the network mask.
	 *
	 * This function configures the individual octets of the network mask
	 * based on the provided parameters or internal logic. It ensures that
	 * the mask is correctly formatted and applied to the network segment.
	 */
	void setMaskOctets();

public:
	/**
	 * @brief Default constructor for the Mask class.
	 *
	 * Initializes a Mask object with a prefix length of MASK_MIN_PREFIX and mask octets set to 0.
	 */
	Mask()
		: _prefixLength(MASK_MIN_PREFIX), _maskOctets(0) {}

	/**
	 * @brief Constructs a Mask object with a specified prefix length.
	 * 
	 * @param prefixLength The length of the prefix for the mask.
	 * @throws std::invalid_argument if the prefix length is not within the valid range.
	 */
	Mask(int prefixLength);

	/**
	 * @brief Retrieves the prefix length of the network mask.
	 * 
	 * @return The prefix length as an integer.
	 */
	int getPrefixLength() const
	{
		return _prefixLength;
	}

	/**
	 * @brief Retrieves the octet at the specified index.
	 * 
	 * This function returns the octet (8-bit unsigned integer) located at the given index
	 * within the mask. The index is zero-based.
	 * 
	 * @param index The zero-based index of the octet to retrieve.
	 * @return uint8_t The octet at the specified index.
	 * @throws std::out_of_range if the index is out of range.
	 */
	uint8_t getOctet(size_t index) const
	{
		return this->operator[](index);
	}

	/**
	 * @brief Overloads the subscript operator to access elements of the mask.
	 * 
	 * This operator allows read-only access to the elements of the mask by index.
	 * 
	 * @param index The position of the element to access.
	 * @return uint8_t The value of the element at the specified index.
	 * @throws std::out_of_range if the index is out of range.
	 */
	inline uint8_t operator [](size_t index) const;

	/**
	 * @brief Retrieves the size of the mask.
	 * 
	 * This function returns the number of octets in the mask.
	 * 
	 * @return The size of the mask in octets.
	 */
	size_t getSize() const
	{
		return _maskOctets.size();
	}

	/**
	 * @brief Overloads the bitwise NOT operator for the Mask class.
	 * 
	 * This operator returns a new Mask object where each bit is the 
	 * complement of the corresponding bit in the original Mask object.
	 * 
	 * @return Mask A new Mask object with each bit inverted.
	 */
	inline Mask operator ~() const;

	/**
	 * @brief Converts the current object to its string representation.
	 * 
	 * @return A string that represents the current object.
	 */
	inline string toString() const;

	/**
	 * @brief Prints the mask object to the specified output stream.
	 * 
	 * This function outputs the mask object to the provided output stream.
	 * If no output stream is specified, it defaults to standard output (cout).
	 * 
	 * @param s The output stream to which the mask object will be printed. Defaults to std::cout.
	 * @return A reference to the output stream.
	 */
	inline ostream& print(ostream& s = cout) const;

	/**
	 * @brief Overloads the stream insertion operator to output the Mask object.
	 * 
	 * This friend function allows the Mask object to be output to an ostream
	 * using the << operator. It calls the print method of the Mask object to
	 * perform the actual output.
	 * 
	 * @param s The output stream to which the Mask object will be written.
	 * @param mask The Mask object to be output.
	 * @return ostream& The output stream after the Mask object has been written to it.
	 */
	friend ostream& operator <<(ostream& s, const Mask& mask)
	{
		return mask.print(s);
	}
};

/**
 * @brief Overloaded subscript operator to access octets in the mask.
 *
 * This operator allows read-only access to the octets in the mask by index.
 * If the provided index is out of range, an exception is thrown.
 *
 * @param index The index of the octet to access.
 * @return The octet at the specified index.
 * @throws std::out_of_range If the index is out of the valid range.
 */
uint8_t Mask::operator [](size_t index) const
{
	// Check if the index is out of range
	if (index >= _maskOctets.size())
	{
		throw out_of_range("Index out of range, must be between 0 and " + to_string(_maskOctets.size() - 1) + ".");
	}

	// Return the octet at the specified index
	return _maskOctets[index];
}

/**
 * @brief Overloaded bitwise NOT operator for the Mask class.
 *
 * This operator creates a new Mask object that is the bitwise NOT
 * (inversion) of the current Mask object. Each bit in the mask octets
 * is inverted.
 *
 * @return A new Mask object with each bit in the mask octets inverted.
 */
Mask Mask::operator ~() const
{
	// Create a copy of the current mask
	Mask mask = *this;

	// Iterate through the mask octets and invert each bit
	for (vector<uint8_t>::iterator it = mask._maskOctets.begin(); it != mask._maskOctets.end(); ++it)
	{
		*it = ~(*it);
	}

	return mask;
}

/**
 * @brief Prints the mask octets to the given output stream.
 *
 * This function iterates through the mask octets and prints each one as an integer.
 * Octets are separated by periods.
 *
 * @param s The output stream to print to.
 * @return A reference to the output stream.
 */
ostream& Mask::print(ostream& s) const
{
	// Iterate through the mask octets and print each one
	for (vector<uint8_t>::const_iterator it = _maskOctets.begin(); it != _maskOctets.end(); ++it)
	{
		// Print the octet as an integer
		s << (int)(*it);
		
		// If the octet is not the last one, print a period
		if (it != _maskOctets.end() - 1)
		{
			s << ".";
		}
	}

	return s;
}

/**
 * @brief Converts the Mask object to a string representation.
 * 
 * This function uses an output string stream to generate a string
 * that represents the current state of the Mask object.
 * 
 * @return A string that represents the Mask object.
 */
string Mask::toString() const
{
	ostringstream oss;
	print(oss);
	return oss.str();
}

#endif // MASK_H