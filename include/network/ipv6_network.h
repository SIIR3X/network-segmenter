#ifndef IPV6_NETWORK_H
#define IPV6_NETWORK_H

#include "network/network.h"
#include "address/ipv6_address.h"

/**
 * @class IPv6Network
 * @brief Represents an IPv6 network.
 */
class IPv6Network : public Network
{
public:
	/**
	 * @brief Constructs an IPv6Network object with the specified IP address and prefix length.
	 * 
	 * @param ip The IPAddress object representing the IPv6 address.
	 * @param prefixLength The prefix length of the network.
	 * @throws std::invalid_argument If the prefix length is not compatible with the address type.
	 */
	IPv6Network(const IPAddress& ip, int prefixLength)
		: Network(ip, prefixLength) {}

	/**
	 * @brief Segments the network into a specified number of subnets.
	 * 
	 * This function overrides the base class implementation to divide the 
	 * network into the given number of subnets.
	 * 
	 * @param numberOfSubnets The number of subnets to divide the network into.
	 * @throws std::invalid_argument If the number of subnets is invalid or exceeds the network capacity.
	 */
	void segment(uint32_t numberOfSubnets) override;

	/**
	 * @brief Prints the IPv6 network information to the given output stream.
	 * 
	 * This function overrides the base class implementation to provide
	 * specific details about the IPv6 network. It outputs the network
	 * information in a human-readable format.
	 * 
	 * @param s The output stream to which the network information will be printed.
	 * @return ostream& A reference to the output stream after the network information has been printed.
	 */
	ostream& print(ostream& s) const override;
};

#endif // IPV6_NETWORK_H