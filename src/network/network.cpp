#include "network/network.h"

/**
 * @brief Constructs a Network object with the given IP address and prefix length.
 *
 * This constructor initializes the network with the specified IP address and prefix length.
 * It checks if the prefix length is compatible with the address type, initializes the IP address
 * and mask, applies the mask to the IP address, and calculates the first and last IP addresses
 * in the network.
 *
 * @param ip The IP address to initialize the network with.
 * @param prefixLength The prefix length to initialize the network with.
 * @throws std::invalid_argument If the prefix length is not compatible with the address type.
 */
Network::Network(const IPAddress& ip, int prefixLength)
{
	// Check if the prefix length is compatible with the address type
	if (!ip.isPrefixLengthCompatible(prefixLength))
	{
		throw invalid_argument("Prefix length is not compatible with address type.");
	}
	
	// Initialize the IP address and mask
	_ip = ip.clone();
	_mask = Mask(prefixLength);

	// Apply the mask to the IP address
	(*_ip) &= _mask;

	// Clone the IP address for the first and last addresses
	_firstIp = _ip->clone();
	_lastIp = _ip->clone();

	// Calculate the first and last IP addresses in the network
	++(*_firstIp);
	(*_lastIp) |= ~_mask;
}