#include "mask/mask.h"

/**
 * @brief Constructs a Mask object with the specified prefix length.
 *
 * This constructor initializes a Mask object and sets its prefix length.
 * It validates the prefix length to ensure it is within the acceptable range.
 * If the prefix length is invalid, an invalid_argument exception is thrown.
 * The mask octets are then set based on the provided prefix length.
 *
 * @param prefixLength The prefix length to initialize the Mask object with.
 * @throws std::invalid_argument if the prefix length is not between MASK_MIN_PREFIX and MASK_MAX_PREFIX.
 */
Mask::Mask(int prefixLength)
	: _prefixLength(prefixLength)
{
	// Check if the prefix length is valid
	if (!isValidPrefixLength(_prefixLength))
	{
		throw invalid_argument("Invalid prefix length: must be between " + to_string(MASK_MIN_PREFIX) + " and " + to_string(MASK_MAX_PREFIX) + ".");
	}

	// Set the mask octets based on the prefix length
	setMaskOctets();
}

/**
 * @brief Sets the mask octets based on the prefix length.
 * 
 * This function calculates the network mask octets from the given prefix length
 * and stores them in the _maskOctets vector. The prefix length is copied to a 
 * local variable and the mask octets are cleared before calculation. The function 
 * iterates through the prefix length, adding 255 to the mask octets for every 
 * 8 bits, and calculates the remaining octet based on the remaining prefix length.
 */
void Mask::setMaskOctets()
{
	// Copy the prefix length to a local variable
	int prefixLength = _prefixLength;

	// Clear the mask octets
	_maskOctets.clear();

	// While the prefix length is greater than 0, calculate the octets
	while (prefixLength > 0)
	{
		// If the prefix length is greater than or equal to 8, add 255 to the mask octets
		if (prefixLength >= 8)
		{
			_maskOctets.push_back(255);
			prefixLength -= 8;
		}
		// Else, calculate the octet based on the remaining prefix length
		else
		{
			_maskOctets.push_back((uint8_t)(255 << (8 - prefixLength)));
			prefixLength = 0;
		}
	}
}