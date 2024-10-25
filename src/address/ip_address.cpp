#include "address/ip_address.h"

/**
 * @brief Pre-increment operator for IPAddress.
 *
 * This operator increments the IP address by one. It iterates through the 
 * address in reverse order (from the least significant octet to the most 
 * significant octet). If an octet is not 255, it increments that octet and 
 * stops. This ensures that the address is incremented correctly, handling 
 * overflow from lower-order octets to higher-order octets.
 *
 * @return IPAddress& A reference to the incremented IP address.
 */
IPAddress& IPAddress::operator++()
{
	// Iterate through the address in reverse order
	for (vector<uint8_t>::reverse_iterator it = _address.rbegin(); it != _address.rend(); ++it)
	{
		// If the octet is not 255, increment it and break
		if ((*it) != 255)
		{
			(*it)++;
			break;
		}
	}

	return *this;
}

/**
 * @brief Decrements the IP address by one.
 * 
 * This operator overload function iterates through the IP address octets in reverse order.
 * If an octet is not zero, it decrements the octet by one and breaks the loop.
 * 
 * @return IPAddress& A reference to the decremented IP address.
 */
IPAddress& IPAddress::operator--()
{
	// Iterate through the address in reverse order
	for (vector<uint8_t>::reverse_iterator it = _address.rbegin(); it != _address.rend(); ++it)
	{
		// If the octet is not 0, decrement it and break
		if ((*it) != 0)
		{
			(*it)--;
			break;
		}
	}

	return *this;
}

/**
 * @brief Overloads the += operator to increment the IP address by a given integer value.
 *
 * This function adds the specified increment to the IP address, handling overflow
 * by carrying over to the next octet as necessary. The operation is performed in
 * reverse order, starting from the least significant octet.
 *
 * @param increment The integer value to add to the IP address.
 * @return IPAddress& A reference to the modified IPAddress object.
 */
IPAddress& IPAddress::operator +=(int increment)
{
	// Initialize the carry value to the increment
	int carry = increment;

	// Iterate through the address in reverse order
	for (vector<uint8_t>::reverse_iterator it = _address.rbegin(); it != _address.rend(); ++it)
	{
		// If the carry is zero, break
		if (carry == 0)
		{
			break;
		}

		// Add the octet and the carry value
		int sum = (*it) + carry;
		(*it) = sum % 256;
		carry = sum / 256;
	}

	return *this;
}

/**
 * @brief Overloads the -= operator to decrement the IP address by a specified integer value.
 *
 * This operator modifies the current IP address by subtracting the given decrement value.
 * The subtraction is performed on the IP address octets in reverse order, handling any necessary
 * borrow operations to ensure proper subtraction across octet boundaries.
 *
 * @param decrement The integer value to subtract from the IP address.
 * @return IPAddress& A reference to the modified IPAddress object.
 */
IPAddress& IPAddress::operator -=(int decrement)
{
	// Initialize the borrow value to the decrement
	int borrow = decrement;

	// Iterate through the address in reverse order
	for (vector<uint8_t>::reverse_iterator it = _address.rbegin(); it != _address.rend(); ++it)
	{
		// If the borrow is zero, break
		if (borrow == 0)
		{
			break;
		}

		// Subtract the octet and the borrow value
		int difference = (*it) - borrow;
		(*it) = difference % 256;
		borrow = difference / 256;
	}

	return *this;
}

/**
 * @brief Applies a bitwise AND operation between the IP address and the given mask.
 *
 * This operator modifies the current IP address by performing a bitwise AND operation
 * with each octet of the provided mask. If the mask size is zero, the corresponding
 * octet in the IP address is set to zero.
 *
 * @param mask The mask to be applied to the IP address.
 * @return IPAddress& A reference to the modified IP address.
 */
IPAddress& IPAddress::operator&=(const Mask& mask)
{
	// Get the size of the mask
	size_t maskSize = mask.getSize();

	// Initialize the mask index
	size_t maskIndex = 0;

	// Iterate through the address octets
	for (vector<uint8_t>::iterator it = _address.begin(); it != _address.end(); ++it)
	{
		if (maskIndex < maskSize)
		{
			// Apply the mask to the octet
			(*it) &= mask[maskIndex++];
		}
		else
		{
			// Set the octet to zero if the mask is exhausted
			(*it) = 0;
		}
	}

	return *this;
}

/**
 * @brief Applies a bitwise OR operation between the IP address and the given mask.
 *
 * This operator modifies the current IP address by performing a bitwise OR operation
 * with each octet of the provided mask. If the mask size is zero, the corresponding
 * octet in the IP address is set to 255.
 *
 * @param mask The mask to be applied to the IP address.
 * @return IPAddress& A reference to the modified IP address.
 */
IPAddress& IPAddress::operator|=(const Mask& mask)
{
	// Get the size of the mask
	size_t maskSize = mask.getSize();

	// Initialize the mask index
	size_t maskIndex = 0;

	// Iterate through the address octets
	for (vector<uint8_t>::iterator it = _address.begin(); it != _address.end(); ++it)
	{
		if (maskIndex < maskSize)
		{
			// Apply the mask to the octet
			(*it) |= mask[maskIndex++];
		}
		else
		{
			// Set the octet to 255 if the mask is exhausted
			(*it) = 255;
		}
	}
	
	return *this;
}