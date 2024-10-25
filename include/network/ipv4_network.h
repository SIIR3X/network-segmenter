#ifndef IPV4_NETWORK_H
#define IPV4_NETWORK_H

#include "network/network.h"
#include "address/ipv4_address.h"

/**
 * @class IPv4Network
 * @brief Represents an IPv4 network.
 */
class IPv4Network : public Network
{
private:
	/**
	 * @brief The broadcast IP address of the network.
	 */
	IPAddress *_broadcastIp;

public:
	/**
	 * @brief Constructs an IPv4Network object with the given IP address and prefix length.
	 * 
	 * @param ip The IP address of the network.
	 * @param prefixLength The prefix length of the network, indicating the number of bits in the network portion of the address.
	 * @throws std::invalid_argument If the prefix length is not compatible with the address type.
	 */
	IPv4Network(const IPAddress& ip, int prefixLength);

	/**
	 * @brief Destructor for the IPv4Network class.
	 *
	 * This destructor is responsible for cleaning up resources used by the IPv4Network instance.
	 * Specifically, it deletes the dynamically allocated broadcast IP address.
	 */
	inline virtual ~IPv4Network();

	/**
	 * @brief Retrieves the broadcast IP address of the network.
	 * 
	 * This function returns a pointer to the broadcast IP address
	 * associated with the network. The broadcast IP address is used
	 * to send data to all hosts on the network.
	 * 
	 * @return const IPAddress* Pointer to the broadcast IP address.
	 */
	const IPAddress* getBroadcastIp() const
	{
		return _broadcastIp;
	}

	/**
	 * @brief Segments the network into a specified number of subnets.
	 * 
	 * This function divides the current network into the given number of subnets.
	 * The segmentation process is based on the provided number of subnets.
	 * 
	 * @param numberOfSubnets The number of subnets to divide the network into.
	 * @throws std::invalid_argument If the number of subnets is invalid or exceeds the network capacity.
	 */
	void segment(uint32_t numberOfSubnets) override;

	/**
	 * @brief Prints the IPv4 network details to the provided output stream.
	 * 
	 * This function overrides the base class implementation to provide
	 * specific details about the IPv4 network. It outputs the network
	 * information in a human-readable format to the given ostream.
	 * 
	 * @param s The output stream where the network details will be printed.
	 * @return ostream& A reference to the output stream after printing the network details.
	 */
	ostream& print(ostream& s) const override;
};

/**
 * @brief Destructor for the IPv4Network class.
 *
 * This destructor is responsible for cleaning up resources used by the IPv4Network instance.
 * Specifically, it deletes the dynamically allocated broadcast IP address.
 */
IPv4Network::~IPv4Network()
{
	delete _broadcastIp;
}

#endif // IPV4_NETWORK_H