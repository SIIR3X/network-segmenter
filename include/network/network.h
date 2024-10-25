#ifndef NETWORK_H
#define NETWORK_H

#include "address/ip_address.h"

/**
 * @class Network
 * @brief Abstract base class representing a Network.
 */
class Network
{
protected:
	/**
	 * @brief The IP address of the network.
	 */
	IPAddress* _ip;

	/**
	 * @brief The first IP address in the network.
	 */
	IPAddress* _firstIp;

	/**
	 * @brief The last IP address in the network.
	 */
	IPAddress* _lastIp;

	/**
	 * @brief The network mask.
	 */
	Mask _mask;

	/**
	 * @brief The subnets of the network.
	 */
	vector<Network*> _subnets;

public:
	/**
	 * @brief Constructs a Network object with the specified IP address and prefix length.
	 * 
	 * @param ip The IP address of the network.
	 * @param prefixLength The prefix length of the network, indicating the number of bits in the network portion of the address.
	 * @throws std::invalid_argument If the prefix length is not compatible with the address type.
	 */
	Network(const IPAddress& ip, int prefixLength);

	/**
	 * @brief Destructor for the Network class.
	 *
	 * This destructor is responsible for cleaning up dynamically allocated memory
	 * associated with the Network object. It deletes the _ip, _firstIp, and _lastIp
	 * members, and iterates through the _subnets vector to delete each subnet.
	 */
	inline virtual ~Network();

	/**
	 * @brief Segments the network into a specified number of subnets.
	 * 
	 * This pure virtual function must be implemented by derived classes to
	 * divide the network into the given number of subnets.
	 * 
	 * @param numberOfSubnets The number of subnets to create from the network.
	 * @throws std::invalid_argument If the number of subnets is invalid or exceeds the network capacity.
	 */
	virtual void segment(uint32_t numberOfSubnets) = 0;

	/**
	 * @brief Retrieves the IP address.
	 * 
	 * This function returns a pointer to the IPAddress object associated with this instance.
	 * 
	 * @return IPAddress* Pointer to the IPAddress object.
	 */
	const IPAddress* getIp() const
	{
		return _ip;
	}

	/**
	 * @brief Retrieves the first IP address.
	 * 
	 * This function returns a pointer to the first IP address stored in the object.
	 * 
	 * @return IPAddress* Pointer to the first IP address.
	 */
	const IPAddress* getFirstIp() const
	{
		return _firstIp;
	}

	/**
	 * @brief Retrieves the last IP address.
	 * 
	 * This function returns a pointer to the last IP address stored in the object.
	 * 
	 * @return const IPAddress* Pointer to the last IP address.
	 */
	const IPAddress* getLastIp() const
	{
		return _lastIp;
	}

	/**
	 * @brief Retrieves the network mask.
	 * 
	 * This function returns the network mask associated with the current object.
	 * 
	 * @return Mask The network mask.
	 */
	Mask getMask() const
	{
		return _mask;
	}

	/**
	 * @brief Retrieves the prefix length of the network mask.
	 * 
	 * This function returns the prefix length of the network mask, which is 
	 * the number of leading 1-bits in the subnet mask. The prefix length 
	 * is used to determine the size of the network.
	 * 
	 * @return int The prefix length of the network mask.
	 */
	int getPrefixLength() const
	{
		return _mask.getPrefixLength();
	}

	/**
	 * @brief Retrieves a subnet from the network by its index.
	 * 
	 * This function returns a pointer to a subnet within the network
	 * based on the provided index.
	 * 
	 * @param index The index of the subnet to retrieve.
	 * @return const Network* A pointer to the subnet at the specified index.
	 * @throws std::out_of_range if the index is out of range.
	 */
	const Network* getSubnet(size_t index) const
	{
		return this->operator[](index);
	}

	/**
	 * @brief Overloaded subscript operator to access network elements by index.
	 * 
	 * This operator allows read-only access to elements within the Network object
	 * using an index. It returns a constant pointer to the Network element at the
	 * specified index.
	 * 
	 * @param index The index of the element to access.
	 * @return const Network* A pointer to the Network element at the specified index.
	 * @throws std::out_of_range if the index is out of range.
	 */
	inline const Network* operator [](size_t index) const;

	/**
	 * @brief Retrieves the number of subnets.
	 * 
	 * @return size_t The count of subnets.
	 */
	size_t getSubnetCount() const
	{
		return _subnets.size();
	}

	/**
	 * @brief Pure virtual function to print the network details to the given output stream.
	 * 
	 * This function must be overridden by derived classes to provide specific 
	 * implementation for printing network details. The default output stream is 
	 * standard output (cout) if no other stream is provided.
	 * 
	 * @param s The output stream to which the network details will be printed. 
	 *          Defaults to standard output (cout).
	 * @return ostream& The output stream after printing the network details.
	 */
	virtual ostream& print(ostream& s = cout) const = 0;

	/**
	 * @brief Overloads the << operator to allow printing of Network objects.
	 * 
	 * This friend function enables the use of the << operator to output the 
	 * contents of a Network object to an output stream.
	 * 
	 * @param s The output stream to which the Network object will be printed.
	 * @param network The Network object to be printed.
	 * @return ostream& The output stream after the Network object has been printed.
	 */
	friend ostream& operator <<(ostream& s, const Network& network)
	{
		return network.print(s);
	}
};

/**
 * @brief Destructor for the Network class.
 *
 * This destructor is responsible for cleaning up dynamically allocated memory
 * associated with the Network object. It deletes the _ip, _firstIp, and _lastIp
 * members, and iterates through the _subnets vector to delete each subnet.
 */
Network::~Network()
{
	delete _ip;
	delete _firstIp;
	delete _lastIp;

	for (Network* subnet : _subnets)
	{
		delete subnet;
	}
}

/**
 * @brief Overloaded subscript operator to access a subnet by index.
 * 
 * @param index The index of the subnet to access.
 * @return const Network* Pointer to the subnet at the specified index.
 * @throws std::out_of_range If the index is out of the valid range.
 */
const Network* Network::operator [](size_t index) const
{
	// Check if the index is out of range
	if (index >= _subnets.size())
	{
		throw out_of_range("Index out of range, must be between 0 and " + to_string(_subnets.size() - 1) + ".");
	}

	// Return the subnet at the specified index
	return _subnets[index];
}

#endif // NETWORK_H