#include "utils/utils.h"
#include "network/ipv4_network.h"
#include "network/ipv6_network.h"
#include <algorithm>

int main(int argc, char* argv[])
{
	// Check if the correct number of arguments is provided
	if (argc < 3)
	{
		cerr << "Usage: " << argv[0] << " <IP address/prefix> <number of subnets>" << endl;
		return 1;
	}

	// Store the IP address and number of subnets
	vector<string> tokens = split(argv[1], "/");
	int numSubnets = stoi(argv[2]);

	// Validate the IP address and prefix
	if (tokens.size() != 2)
	{
		cerr << "Invalid IP address/prefix format. Use the format <IP address>/<prefix length>." << endl;
		return 1;
	}

	// Check if the IP address is IPv4 or IPv6
	if (find(tokens[0].begin(), tokens[0].end(), ':') != tokens[0].end())
	{
		// IPv6 address
		try
		{
			// Create an IPv6 address object
			IPv6Address ip(tokens[0]);
			
			// Create an IPv6 network object
			IPv6Network network(ip, stoi(tokens[1]));

			// Segment the network into the specified number of subnets
			network.segment(numSubnets);

			// Print the network information
			cout << network << endl;
		}
		catch (const exception& e)
		{
			cerr << "Error: " << e.what() << endl;
			return 1;
		}
	}
	else
	{
		// IPv4 address
		try
		{
			// Create an IPv4 address object
			IPv4Address ip(tokens[0]);

			// Create an IPv4 network object
			IPv4Network network(ip, stoi(tokens[1]));

			// Segment the network into the specified number of subnets
			network.segment(numSubnets);

			// Print the network information
			cout << network << endl;
		}
		catch (const exception& e)
		{
			cerr << "Error: " << e.what() << endl;
			return 1;
		}
	}
	
	return 0;
}