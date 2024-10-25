#include "utils/utils.h"
#include "address/ipv4_address.h"
#include <algorithm>

/**
 * @brief Sets the IPv4 address from a string representation.
 *
 * This function takes a string representation of an IPv4 address, splits it into octets,
 * validates each octet, and sets the address if all parts are valid.
 *
 * @param address The string representation of the IPv4 address.
 * @throws std::invalid_argument if the address does not have exactly 4 parts,
 *         if any part is empty or contains non-digit characters,
 *         or if any part is not within the range 0 to 255.
 */
void IPv4Address::setAddress(const string& address)
{
	// Split the address into octets
	vector<string> octets = split(address, ".");

	// Check if the address has the correct number of parts
	if (octets.size() != IPV4_NUM_OCTETS)
	{
		throw invalid_argument("Invalid IPv4 address: must have " + to_string(IPV4_NUM_OCTETS) + " parts.");
	}

	// Iterate over the octets and validate each part
	for (size_t i = 0; i < IPV4_NUM_OCTETS; ++i)
	{
		// Get the current octet
		const string& octet = octets[i];

		// Check if the octet is empty or contains non-digit characters
		if (octet.empty() || !all_of(octet.begin(), octet.end(), ::isdigit))
		{
			throw invalid_argument("Invalid IPv4 address: parts must be non-empty and contain only digits.");
		}

		// Convert the octet to an integer
		int octetValue = stoi(octet);

		// Check if the octet is within the valid range
		if (octetValue < 0 || octetValue > 255)
		{
			throw invalid_argument("Invalid IPv4 address: parts must be between 0 and 255.");
		}

		// Set the octet value in the address
		_address[i] = octetValue;
	}
}