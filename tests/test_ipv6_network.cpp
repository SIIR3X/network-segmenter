#include <gtest/gtest.h>
#include "network/ipv6_network.h"

TEST(IPv6Network, Constructor)
{
	// Arrange
	IPv6Address ip("2001:0db8:85a3:0000:0000:8a2e:0370:7334");
	int prefixLength = 64;
	IPv6Network network(ip, prefixLength);

	// Act
	const IPAddress* ipAddr = network.getIp();
	const IPAddress* firstIp = network.getFirstIp();
	const IPAddress* lastIp = network.getLastIp();

	// Assert
	EXPECT_EQ("2001:db8:85a3::", ipAddr->toString());
	EXPECT_EQ("2001:db8:85a3::1", firstIp->toString());
	EXPECT_EQ("2001:db8:85a3::ffff:ffff:ffff:ffff", lastIp->toString());
}

TEST(IPv6Network, Segment)
{
	// Arrange
	IPv6Address ip("2001:0db8:85a3:0000:0000:8a2e:0370:7334");
	int prefixLength = 64;
	IPv6Network network(ip, prefixLength);

	// Act
	network.segment(4);

	// Assert
	EXPECT_EQ(4, (int)network.getSubnetCount());
}