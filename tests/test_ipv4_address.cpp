#include <gtest/gtest.h>
#include "address/ipv4_address.h"

TEST(IPv4Address, Constructor)
{
	// Arrange
	IPv4Address ipv4("1.2.3.4");

	// Act
	uint8_t octet0 = ipv4[0];
	uint8_t octet1 = ipv4[1];
	uint8_t octet2 = ipv4[2];
	uint8_t octet3 = ipv4[3];
	int size = ipv4.getSize();

	// Assert
	EXPECT_EQ(octet0, 1);
	EXPECT_EQ(octet1, 2);
	EXPECT_EQ(octet2, 3);
	EXPECT_EQ(octet3, 4);
	EXPECT_EQ(size, IPV4_NUM_OCTETS);
}

TEST(IPv4Address, Clone)
{
	// Arrange
	IPv4Address ipv4("1.2.3.4");

	// Act
	IPv4Address* clone = ipv4.clone();

	// Assert
	EXPECT_EQ(ipv4.toString(), clone->toString());

	delete clone;
}

TEST(IPv4Address, IsPrefixLengthCompatible)
{
	// Arrange
	IPv4Address ipv4("1.2.3.4");

	// Act
	bool compatible1 = ipv4.isPrefixLengthCompatible(0);
	bool compatible2 = ipv4.isPrefixLengthCompatible(32);
	bool compatible3 = ipv4.isPrefixLengthCompatible(33);

	// Assert
	EXPECT_FALSE(compatible1);
	EXPECT_TRUE(compatible2);
	EXPECT_FALSE(compatible3);
}