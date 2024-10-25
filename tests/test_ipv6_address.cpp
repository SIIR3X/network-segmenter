#include <gtest/gtest.h>
#include "address/ipv6_address.h"

TEST(IPv6Address, Constructor)
{
	// Arrange
	IPv6Address ipv6("2001:0db8:85a3:0000:0000:8a2e:0370:7334");

	// Act
	uint16_t hextet0 = ipv6[0];
	uint16_t hextet1 = ipv6[1];
	uint16_t hextet2 = ipv6[2];
	uint16_t hextet3 = ipv6[3];
	uint16_t hextet4 = ipv6[4];
	uint16_t hextet5 = ipv6[5];
	uint16_t hextet6 = ipv6[6];
	uint16_t hextet7 = ipv6[7];
	int size = ipv6.getSize();
	
	// Assert
	EXPECT_EQ(hextet0, 0x2001);
	EXPECT_EQ(hextet1, 0x0db8);
	EXPECT_EQ(hextet2, 0x85a3);
	EXPECT_EQ(hextet3, 0x0000);
	EXPECT_EQ(hextet4, 0x0000);
	EXPECT_EQ(hextet5, 0x8a2e);
	EXPECT_EQ(hextet6, 0x0370);
	EXPECT_EQ(hextet7, 0x7334);
	EXPECT_EQ(size, IPV6_NUM_OCTETS);
}

TEST(IPv6Address, Clone)
{
	// Arrange
	IPv6Address ipv6("2001:0db8:85a3:0000:0000:8a2e:0370:7334");

	// Act
	IPv6Address* clone = ipv6.clone();
	
	// Assert
	EXPECT_EQ(ipv6.toString(), clone->toString());

	delete clone;
}

TEST(IPv6Address, IsPrefixLengthCompatible)
{
	// Arrange
	IPv6Address ipv6("2001:0db8:85a3:0000:0000:8a2e:0370:7334");

	// Act
	bool compatible1 = ipv6.isPrefixLengthCompatible(0);
	bool compatible2 = ipv6.isPrefixLengthCompatible(128);
	bool compatible3 = ipv6.isPrefixLengthCompatible(129);
	
	// Assert
	EXPECT_FALSE(compatible1);
	EXPECT_TRUE(compatible2);
	EXPECT_FALSE(compatible3);
}

TEST(IPv6Address, SumIncrementOperator)
{
	// Arrange
	IPv6Address ipv6("2001:0db8:85a3:0000:0000:8a2e:0370:7334");
	vector<uint8_t> increment(IPV6_NUM_OCTETS, 0);
	increment[15] = 1;

	// Act
	ipv6 += increment;

	// Assert
	EXPECT_EQ(ipv6.toString(), "2001:db8:85a3::8a2e:370:7335");
}