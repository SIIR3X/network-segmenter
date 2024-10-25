#ifndef IPV6_ADDRESS_H
#define IPV6_ADDRESS_H

#include "address/ip_address.h"

#define IPV6_NUM_HEXTETS 8 ///< The number of hextets in an IPv6 address.
#define IPV6_NUM_OCTETS 16 ///< The number of octets in an IPv6 address.

/**
 * @class IPv6Address
 * @brief Represents an IPv6 address.
 */
class IPv6Address : public IPAddress
{
private:
	/**
	 * @brief Sets the IPv6 address.
	 * 
	 * This function overrides the base class method to set the IPv6 address.
	 * 
	 * @param address A string representing the IPv6 address to be set.
	 * @throws std::invalid_argument if the address is not a valid IPv6 address.
	 */
	void setAddress(const string& address) override;

	/**
	 * @brief Finds the longest sequence of consecutive zero blocks in the IPv6 address.
	 * 
	 * This function scans the IPv6 address and identifies the longest sequence of 
	 * consecutive zero blocks. It returns a pair of integers where the first integer 
	 * represents the starting index of the sequence and the second integer represents 
	 * the length of the sequence.
	 * 
	 * @return pair<int, int> A pair of integers representing the start index and length of the sequence.
	 */
	pair<int, int> findLongestZeroSequence() const;

public:
	/**
	 * @brief Constructs an IPv6Address object with the given address string.
	 *
	 * This constructor initializes an IPv6Address object by calling the base class
	 * IPAddress constructor with the number of octets for an IPv6 address. It then
	 * attempts to set the address using the provided string. If the address is invalid,
	 * an invalid_argument exception is thrown.
	 *
	 * @param address A string representing the IPv6 address.
	 * @throws std::invalid_argument If the provided address string is not a valid IPv6 address.
	 */
	IPv6Address(const string& address)
		: IPAddress(IPV6_NUM_OCTETS)
	{
		try
		{
			setAddress(address);
		}
		catch (const invalid_argument& e)
		{
			throw e;
		}
	}

	/**
	 * @brief Creates a copy of the current IPv6Address object.
	 * 
	 * This method creates a new instance of IPv6Address that is a copy of the current object.
	 * 
	 * @return IPv6Address* Pointer to the cloned IPv6Address object.
	 */
	IPv6Address* clone() const
	{
		return new IPv6Address(*this);
	}

	/**
	 * @brief Retrieves the hextet (16-bit segment) at the specified index from the IPv6 address.
	 * 
	 * @param index The index of the hextet to retrieve. Must be in the range [0, 7].
	 * @return uint16_t The hextet at the specified index.
	 * @throws std::out_of_range If the index is out of range.
	 */
	uint16_t getHextet(size_t index) const
	{
		return this->operator[](index);
	}

	/**
	 * @brief Overloads the subscript operator to access elements of the IPv6 address.
	 * 
	 * @param index The position of the element to access.
	 * @return uint16_t The value of the element at the specified position.
	 * @throws std::out_of_range If the index is out of range.
	 */
	inline uint16_t operator [](size_t index) const;

	/**
	 * @brief Checks if the given prefix length is compatible with an IPv6 address.
	 * 
	 * This function verifies whether the provided prefix length falls within the
	 * valid range for IPv6 addresses, which is between 1 and 128 inclusive.
	 * 
	 * @param prefixLength The prefix length to be checked.
	 * @return bool True if the prefix length is compatible, false otherwise.
	 */
	bool isPrefixLengthCompatible(int prefixLength) const override
	{
		return prefixLength >= 1 && prefixLength <= 128;
	}

	/**
	 * @brief Overloads the += operator to increment the IPv6 address.
	 *
	 * This operator allows for incrementing the IPv6 address by a given vector of bytes.
	 *
	 * @param increment A vector of uint8_t representing the increment value.
	 * @return IPv6Address& A reference to the updated IPv6Address object.
	 */
	IPv6Address& operator +=(const vector<uint8_t>& increment);

	/**
	 * @brief Prints the IPv6 address to the given output stream.
	 * 
	 * This function overrides the base class implementation to provide
	 * a custom print functionality for IPv6 addresses.
	 * 
	 * @param s The output stream to which the IPv6 address will be printed.
	 * @return ostream& A reference to the output stream.
	 */
	ostream& print(ostream& s) const override;
};

/**
 * @brief Overloaded subscript operator to access a specific hextet of the IPv6 address.
 * 
 * @param index The index of the hextet to access (0-based).
 * @return uint16_t The hextet at the specified index.
 * @throws std::out_of_range if the index is out of the valid range [0, IPV6_NUM_HEXTETS - 1].
 */
uint16_t IPv6Address::operator [](size_t index) const
{
	// Check if the index is out of range
	if (index >= IPV6_NUM_HEXTETS)
	{
		throw out_of_range("Index out of range, must be between 0 and " + to_string(IPV6_NUM_HEXTETS - 1) + ".");
	}

	// Calculate the index in the address vector
	size_t i = index * 2;

	// Return the hextet at the specified index
	return _address[i] << 8 | _address[i + 1];
}

#endif // IPV6_ADDRESS_H