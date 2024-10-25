#ifndef IP_ADDRESS_H
#define IP_ADDRESS_H

#include "mask/mask.h"

using namespace std;

/**
 * @class IPAddress
 * @brief Abstract base class representing an IP address.
 */
class IPAddress
{
protected:
	/**
	 * @brief A vector containing the octets of the address.
	 * 
	 * This vector stores the individual octets (8-bit values) that make up the address.
	 * Each element in the vector represents one octet of the address.
	 */
	vector<uint8_t> _address;

	/**
	 * @brief Sets the IP address.
	 * 
	 * This pure virtual function sets the IP address for the implementing class.
	 * 
	 * @param address A string representing the IP address to be set.
	 * @throws std::invalid_argument if the address is not a valid IP address.
	 */
	virtual void setAddress(const string& address) = 0;

public:
	/**
	 * @brief Constructs an IPAddress object with a specified size.
	 * 
	 * This constructor initializes the IPAddress object with a given size,
	 * setting all elements of the internal address vector to zero.
	 * 
	 * @param size The size of the IP address.
	 */
	IPAddress(size_t size)
		: _address(size, 0) {}

	/**
	 * @brief Virtual destructor for the IPAddress class.
	 * 
	 * This destructor ensures that the destructor of the derived class
	 * is called when an object of the derived class is deleted through
	 * a pointer to the base class.
	 */
	virtual ~IPAddress() = default;

	/**
	 * @brief Creates a clone of the current IPAddress object.
	 * 
	 * This is a pure virtual function that must be implemented by derived classes.
	 * It returns a pointer to a new IPAddress object that is a copy of the current object.
	 * 
	 * @return IPAddress* Pointer to the cloned IPAddress object.
	 */
	virtual IPAddress* clone() const = 0;

	/**
	 * @brief Checks if the given prefix length is compatible.
	 * 
	 * This pure virtual function must be overridden by derived classes to 
	 * determine if the specified prefix length is compatible with the IP address.
	 * 
	 * @param prefixLength The prefix length to check for compatibility.
	 * @return bool True if the prefix length is compatible, false otherwise.
	 */
	virtual bool isPrefixLengthCompatible(int prefixLength) const = 0;

	/**
	 * @brief Calculates the capacity of the network segment based on the given prefix length.
	 * 
	 * This function computes the number of possible addresses in a network segment
	 * defined by the provided prefix length. The prefix length determines the size
	 * of the network portion of the address, and the remaining bits define the host
	 * portion.
	 * 
	 * @param prefixLength The length of the network prefix in bits.
	 * @return uint32_t The number of possible addresses in the network segment.
	 */
	inline uint32_t calculateCapacity(int prefixLength) const;

	/**
	 * @brief Retrieves the octet at the specified index from the IP address.
	 * 
	 * This function returns the value of the octet at the given index in the IP address.
	 * The index should be within the valid range of octets for the IP address.
	 * 
	 * @param index The zero-based index of the octet to retrieve.
	 * @return uint8_t The value of the octet at the specified index.
	 * @throws std::out_of_range if the index is out of range.
	 */
	uint8_t getOctet(size_t index)
	{
		return this->operator[](index);
	}

	/**
	 * @brief Overloads the subscript operator to access individual bytes of the IP address.
	 * 
	 * @param index The position of the byte to access (0-based index).
	 * @return uint8_t The byte at the specified position.
	 * @throws std::out_of_range If the index is out of range.
	 */
	inline uint8_t operator [](size_t index) const;

	/**
	 * @brief Retrieves the size of the IP address.
	 * 
	 * This function returns the size of the IP address stored in the _address member.
	 * 
	 * @return size_t The size of the IP address.
	 */
	size_t getSize() const
	{
		return _address.size();
	}

	/**
	 * @brief Pre-increment operator for IPAddress.
	 *
	 * This operator increments the IP address to the next sequential address.
	 * 
	 * @return IPAddress& A reference to the incremented IPAddress object.
	 */
	IPAddress& operator ++();

	/**
	 * @brief Pre-decrement operator for IPAddress.
	 *
	 * This operator decrements the IP address by one.
	 *
	 * @return IPAddress& A reference to the decremented IPAddress object.
	 */
	IPAddress& operator --();
	
	/**
	 * @brief Increments the IP address by a given integer value.
	 * 
	 * This operator overload allows for incrementing the IP address
	 * by a specified integer value. The increment operation modifies
	 * the current IP address object.
	 * 
	 * @param increment The integer value to add to the IP address.
	 * @return IPAddress& A reference to the modified IPAddress object.
	 */
	IPAddress& operator +=(int increment);

	/**
	 * @brief Subtracts a given integer value from the IP address.
	 *
	 * This operator modifies the current IPAddress object by decrementing
	 * its value by the specified integer amount.
	 *
	 * @param decrement The integer value to subtract from the IP address.
	 * @return IPAddress& A reference to the modified IPAddress object.
	 */
	IPAddress& operator -=(int decrement);

	/**
	 * @brief Applies a bitwise AND operation between the IP address and the given mask.
	 * 
	 * This operator modifies the current IP address by performing a bitwise AND 
	 * operation with the provided mask. The result is stored in the current IP address.
	 * 
	 * @param mask The mask to be applied to the IP address.
	 * @return IPAddress& A reference to the modified IP address.
	 */
	IPAddress& operator &=(const Mask& mask);

	/**
	 * @brief Applies a bitwise OR operation between the IP address and the given mask.
	 * 
	 * This operator modifies the current IP address by performing a bitwise OR 
	 * operation with the specified mask. The result is stored in the current IP address.
	 * 
	 * @param mask The mask to be used in the bitwise OR operation.
	 * @return IPAddress& A reference to the modified IP address.
	 */
	IPAddress& operator |=(const Mask& mask);

	/**
	 * @brief Converts the IP address to its string representation.
	 * 
	 * @return string A string representation of the IP address.
	 */
	inline string toString() const;

	/**
	 * @brief Pure virtual function to print the IP address.
	 * 
	 * This function must be overridden by derived classes to provide
	 * a specific implementation for printing the IP address.
	 * 
	 * @param s The output stream to which the IP address will be printed.
	 *          Defaults to the standard output stream (cout).
	 * @return ostream& A reference to the output stream.
	 */
	virtual ostream& print(ostream& s = cout) const = 0;

	/**
	 * @brief Overloads the stream insertion operator to output the IPAddress object.
	 * 
	 * This friend function allows an IPAddress object to be output to an ostream
	 * using the << operator. It calls the print method of the IPAddress class to
	 * perform the actual output.
	 * 
	 * @param s The output stream to which the IPAddress object will be written.
	 * @param ip The IPAddress object to be output.
	 * @return A reference to the output stream after the IPAddress object has been written.
	 */
	friend ostream& operator <<(ostream& s, const IPAddress& ip)
	{
		return ip.print(s);
	}
};

/**
 * @brief Calculates the capacity of an IP address range based on the given prefix length.
 *
 * This function determines the number of possible IP addresses within a subnet
 * defined by the given prefix length. If the prefix length is greater than or equal 32,
 * it returns a fixed value of 65536 (2^16). Otherwise, it calculates the capacity
 * as 2^(32 - prefixLength).
 *
 * @param prefixLength The prefix length of the subnet.
 * @return uint32_t The capacity of the IP address range.
 */
uint32_t IPAddress::calculateCapacity(int prefixLength) const
{
	// If the prefix length is greater than or equal to 32, return 65536
	if (prefixLength >= 32)
	{
		return 65536;
	}

	// Otherwise, return 2^(32 - prefixLength)
	return 1 << (32 - prefixLength);
}

/**
 * @brief Overloaded subscript operator to access individual octets of the IP address.
 * 
 * @param index The zero-based index of the octet to access.
 * @return uint8_t The octet at the specified index.
 * @throws std::out_of_range If the index is out of the valid range (0 to _address.size() - 1).
 */
uint8_t IPAddress::operator [](size_t index) const
{
	// Check if the index is out of range
	if (index >= _address.size())
	{
		throw out_of_range("Index out of range, must be between 0 and " + to_string(_address.size() - 1) + ".");
	}

	// Return the octet at the specified index
	return _address[index];
}

/**
 * @brief Converts the IPAddress object to its string representation.
 * 
 * This function uses an output string stream to generate a string
 * representation of the IPAddress object by calling the print method.
 * 
 * @return string A string representation of the IPAddress object.
 */
string IPAddress::toString() const
{
	ostringstream oss;
	print(oss);
	return oss.str();
}

#endif // IP_ADDRESS_H