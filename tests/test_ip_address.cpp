#include <gtest/gtest.h>
#include "address/ipv4_address.h"

TEST(IPAddress, PreIncrementOperator)
{
	// Arrange
	IPv4Address ipv4("1.2.3.4");

	// Act
	++ipv4;

	// Assert
	EXPECT_EQ(ipv4[3], 5);
}

TEST(IPAddress, PreDecrementOperator)
{
	// Arrange
	IPv4Address ipv4("1.2.3.4");

	// Act
	--ipv4;

	// Assert
	EXPECT_EQ(ipv4[3], 3);
}

TEST(IPAddress, SumIncrementOperator)
{
	// Arrange
	IPv4Address ipv4("1.2.3.4");

	// Act
	ipv4 += 2;

	// Assert
	EXPECT_EQ(ipv4[3], 6);
}

TEST(IPAddress, SumDecrementOperator)
{
	// Arrange
	IPv4Address ipv4("1.2.3.4");

	// Act
	ipv4 -= 2;

	// Assert
	EXPECT_EQ(ipv4[3], 2);
}

TEST(IPAddress, BitwiseAndOperator)
{
	// Arrange
	IPv4Address ipv4("1.2.3.4");

	// Act
	ipv4 &= Mask(24);
	
	// Assert
	EXPECT_EQ(ipv4[3], 0);
}

TEST(IPAddress, BitwiseOrOperator)
{
	// Arrange
	IPv4Address ipv4("1.2.3.4");

	// Act
	ipv4 |= Mask(24);

	// Assert
	EXPECT_EQ(ipv4[3], 255);
}