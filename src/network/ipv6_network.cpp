#include "network/ipv6_network.h"
#include <cmath>
#include <iomanip>

/**
 * @brief Segments the IPv6 network into a specified number of subnets.
 *
 * This function divides the current IPv6 network into the given number of subnets.
 * It performs several checks to ensure the number of subnets is valid and does not
 * exceed the network's capacity or the maximum prefix length of 128 bits.
 *
 * @param numberOfSubnets The number of subnets to create from the current network.
 * @throws std::invalid_argument If the number of subnets is invalid or exceeds the network capacity.
 */
void IPv6Network::segment(uint32_t numberOfSubnets)
{
	// Check if the number of subnets is valid
	if (numberOfSubnets < 1)
	{
		throw invalid_argument("Number of subnets must be greater than 0.");
	}

	// Check if the number of subnets exceeds the network capacity
	if (numberOfSubnets > dynamic_cast<IPv6Address*>(_ip)->calculateCapacity(getPrefixLength()))
	{
		throw invalid_argument("Number of subnets must be less than or equal to the capacity of the network.");
	}

	// Calculate the new prefix length for the subnets
	int newPrefixLength = getPrefixLength() + ceil(log2(numberOfSubnets));
		
	// Check if the new prefix length exceeds the maximum length of 128 bits
	if (newPrefixLength > 128)
	{
		throw invalid_argument("The new prefix length exceeds the maximum length of 128 bits.");
	}

	// Calculate the number of bits for the subnets
	int bitsForSubnets = 128 - newPrefixLength;

	// Create an increment vector to generate the subnets
	vector<uint8_t> increment(IPV6_NUM_OCTETS, 0);

	// Calculate the increment value based on the number of bits for the subnets
	increment[15 - bitsForSubnets / IPV6_NUM_HEXTETS] = 1 << (bitsForSubnets % IPV6_NUM_HEXTETS);

	// Clear the existing subnets
	_subnets.clear();

	// Get the base address for the subnets
	IPv6Address* baseAddress = dynamic_cast<IPv6Address*>(_ip);

	// Create the new subnets
	for (uint32_t i = 0; i < numberOfSubnets; ++i)
	{
		IPv6Address newAddress = *baseAddress;

		// Calculate the new address
		for (uint32_t j = 0; j < i; ++j)
		{
			newAddress += increment;
		}

		// Add the new subnet to the list
		_subnets.push_back(new IPv6Network(newAddress, newPrefixLength));
	}
}

/**
 * @brief Prints the details of the IPv6 network subnets in a formatted table.
 *
 * This function outputs a table to the provided output stream, displaying the
 * subnet and host range information for each subnet in the IPv6 network.
 *
 * @param s The output stream to which the table will be printed.
 * @return ostream& A reference to the output stream after the table has been printed.
 */
ostream& IPv6Network::print(ostream& s) const
{
	// Print the header
	s << "+------------------------------------------------+----------------------------------------------------------------------------------------+\n";
	s << "|                     Subnet                     |                                       Host Range                                       |\n";
	s << "+------------------------------------------------+----------------------------------------------------------------------------------------+\n";

	// Print the details of each subnet
	for (const auto& subnet : _subnets)
	{
		int prefixLength = subnet->getPrefixLength();

		// Print the ip and prefix length
		s << "| " << left << setw(43) << subnet->getIp()->toString() << "/" + to_string(prefixLength) << " | ";

		// Print the host range
		s << left << setw(45) << subnet->getFirstIp()->toString() << " - ";
		s << left << setw(30) << subnet->getLastIp()->toString() << " |\n";
	}

	// Print the footer
	s << "+------------------------------------------------+----------------------------------------------------------------------------------------+";

	return s;
}