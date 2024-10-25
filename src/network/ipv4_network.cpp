#include "network/ipv4_network.h"
#include <cmath>
#include <iomanip>

/**
 * @brief Constructs an IPv4Network object with the given IP address and prefix length.
 * 
 * @param ip The IP address of the network.
 * @param prefixLength The prefix length of the network.
 */
IPv4Network::IPv4Network(const IPAddress& ip, int prefixLength)
	: Network(ip, prefixLength)
{
	// Initialize the broadcast IP address
	_broadcastIp = _lastIp->clone();

	// Recalculate the last IP address
	--(*_lastIp);
}

/**
 * @brief Segments the IPv4 network into a specified number of subnets.
 *
 * This function divides the current IPv4 network into the given number of subnets.
 * It performs several checks to ensure the number of subnets is valid and does not
 * exceed the network's capacity. If the checks pass, it calculates the new prefix
 * length and creates the subnets accordingly.
 *
 * @param numberOfSubnets The number of subnets to create.
 * @throws std::invalid_argument If the number of subnets is invalid or exceeds the network capacity.
 */
void IPv4Network::segment(uint32_t numberOfSubnets)
{
	// Check if the number of subnets is valid
	if (numberOfSubnets < 1)
	{
		throw invalid_argument("Number of subnets must be greater than 0.");
	}

	// Check if the number of subnets exceeds the network capacity
	if (numberOfSubnets > dynamic_cast<IPv4Address*>(_ip)->calculateCapacity(getPrefixLength()))
	{
		throw invalid_argument("Number of subnets must be less than or equal to the capacity of the network.");
	}

	// Calculate the new prefix length
	int newPrefixLength = getPrefixLength() + ceil(log2(numberOfSubnets));

	// Check if the new prefix length is valid
	if (newPrefixLength > 32)
	{
		throw invalid_argument("Number of subnets is too large for the network.");
	}

	// Calculate the increment for the new subnets
	int increment = 1 << (32 - newPrefixLength);

	// Clear the existing subnets
	_subnets.clear();

	// Get the base IP address
	IPv4Address* baseIp = dynamic_cast<IPv4Address*>(_ip);

	// Create the new subnets
	for (uint32_t i = 0; i < numberOfSubnets; ++i)
	{
		IPv4Address newAddress = *baseIp;

		// Calculate the new address
		newAddress += increment * i;

		// Add the new subnet to the list
		_subnets.push_back(new IPv4Network(newAddress, newPrefixLength));
	}
}

/**
 * @brief Prints the details of the IPv4 network subnets in a formatted table.
 *
 * This function outputs a table with the following columns:
 * - Subnet: The IP address and prefix length of the subnet.
 * - Host Range: The range of host IP addresses within the subnet.
 * - Broadcast: The broadcast IP address of the subnet.
 * - Host Number: The number of hosts within the subnet.
 *
 * The table is printed with a header, the details of each subnet, and a footer.
 *
 * @param s The output stream to which the table will be printed.
 * @return ostream& A reference to the output stream.
 */
ostream& IPv4Network::print(ostream& s) const
{
	// Print the header
	s << "+----------------------+-----------------------------------+---------------------+---------------+\n";
	s << "|        Subnet        |             Host Range            |      Broadcast      |    Capacity   |\n";
	s << "+----------------------+-----------------------------------+---------------------+---------------+\n";

	// Print the details of each subnet
	for (const auto& subnet : _subnets)
	{
		// Get the prefix length
		int prefixLength = subnet->getPrefixLength();

		// Print the ip and prefix length
		s << "| " << left << setw(17) << subnet->getIp()->toString() << "/" + to_string(prefixLength) << " | ";
		
		// Print the host range
		s << left << setw(15) << subnet->getFirstIp()->toString() << " - ";
		s << left << setw(15) << subnet->getLastIp()->toString() << " | ";

		// Print the broadcast IP
		s << left << setw(19) << dynamic_cast<IPv4Network*>(subnet)->getBroadcastIp()->toString() << " | ";

		// Print the number of hosts
		s << right << setw(13) << to_string(subnet->getIp()->calculateCapacity(prefixLength)) << " |\n";
	}

	// Print the footer
	s << "+----------------------+-----------------------------------+---------------------+---------------+";

	return s;
}