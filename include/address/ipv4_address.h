#ifndef IPV4_ADDRESS_H
#define IPV4_ADDRESS_H

#include "address/ip_address.h"

#define IPV4_NUM_OCTETS 4 ///< The number of octets in an IPv4 address.

/**
 * @class IPv4Address
 * @brief Represents an IPv4 address.
 */
class IPv4Address : public IPAddress
{
private:
	/**
	 * @brief Sets the IPv4 address.
	 * 
	 * This function overrides the base class method to set the IPv4 address.
	 * 
	 * @param address A string representing the IPv4 address to be set.
	 * @throws std::invalid_argument if the address is not a valid IPv4 address.
	 */
	void setAddress(const string& address) override;

public:
	/**
	 * @brief Constructs an IPv4Address object with the given address string.
	 * 
	 * This constructor initializes an IPv4Address object by calling the base class
	 * IPAddress constructor with the number of octets for an IPv4 address. It then
	 * attempts to set the address using the provided string. If the address is 
	 * invalid, an invalid_argument exception is thrown.
	 * 
	 * @param address A string representing the IPv4 address.
	 * @throws std::invalid_argument If the provided address string is not a valid IPv4 address.
	 */
	IPv4Address(const string& address)
		: IPAddress(IPV4_NUM_OCTETS) 
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
	 * @brief Creates a clone of the current IPv4Address object.
	 * 
	 * This method overrides the clone function to provide a deep copy
	 * of the current IPv4Address instance. It returns a pointer to a 
	 * new IPv4Address object that is a copy of the current instance.
	 * 
	 * @return IPv4Address* Pointer to the newly created IPv4Address object.
	 */
	IPv4Address* clone() const override
	{
		return new IPv4Address(*this);
	}

	/**
	 * @brief Checks if the given prefix length is compatible with IPv4 addressing.
	 *
	 * This function verifies whether the provided prefix length falls within the
	 * valid range for IPv4 addresses, which is between 1 and 32 inclusive.
	 *
	 * @param prefixLength The prefix length to be checked.
	 * @return bool True if the prefix length is compatible with IPv4 addressing, false otherwise.
	 */
	bool isPrefixLengthCompatible(int prefixLength) const override
	{
		return prefixLength >= 1 && prefixLength <= 32;
	}

	/**
	 * @brief Prints the IPv4 address to the given output stream.
	 *
	 * This function iterates through the octets of the IPv4 address and prints each octet
	 * to the provided output stream. Octets are separated by periods.
	 *
	 * @param s The output stream to which the IPv4 address will be printed.
	 * @return ostream& A reference to the output stream.
	 */
	inline ostream& print(ostream& s) const override;
};

/**
 * @brief Prints the IPv4 address to the given output stream.
 *
 * This function iterates through the octets of the IPv4 address and prints each octet
 * to the provided output stream. Octets are separated by periods.
 *
 * @param s The output stream to which the IPv4 address will be printed.
 * @return ostream& A reference to the output stream.
 */
ostream& IPv4Address::print(ostream& s) const
{
	// Iterate through the address octets and print them to the stream
	for (vector<uint8_t>::const_iterator it = _address.begin(); it != _address.end(); ++it)
	{
		// Print the octet to the stream
		s << (int)(*it);

		// If this is not the last octet, print a period
		if (it != _address.end() - 1)
		{
			s << ".";
		}
	}

	return s;
}

#endif // IPV4_ADDRESS_H