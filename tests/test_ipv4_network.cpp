#include <gtest/gtest.h>
#include "network/ipv4_network.h"

TEST(IPv4Network, Constructor)
{
	// Arrange
	IPv4Address ip("1.2.3.4");
	int prefixLength = 24;
	IPv4Network network(ip, prefixLength);

	// Act
	const IPAddress* ipAddr = network.getIp();
	const IPAddress* firstIp = network.getFirstIp();
	const IPAddress* lastIp = network.getLastIp();
	const IPAddress* broadcastIp = network.getBroadcastIp();

	// Assert
	EXPECT_EQ("1.2.3.0", ipAddr->toString());
	EXPECT_EQ("1.2.3.1", firstIp->toString());
	EXPECT_EQ("1.2.3.254", lastIp->toString());
	EXPECT_EQ("1.2.3.255", broadcastIp->toString());
}

TEST(IPv4Network, Segment)
{
	// Arrange
	IPv4Address ip("1.2.3.4");
	int prefixLength = 24;
	IPv4Network network(ip, prefixLength);

	// Act
	network.segment(4);

	// Assert
	EXPECT_EQ(4, (int)network.getSubnetCount());
}