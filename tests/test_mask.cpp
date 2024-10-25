#include <gtest/gtest.h>
#include "mask/mask.h"

TEST(Mask, Constructor)
{
	// Arrange
	Mask mask(24);

	// Act
	int prefixLength = mask.getPrefixLength();
	uint8_t octet0 = mask[0];
	uint8_t octet1 = mask[1];
	uint8_t octet2 = mask[2];
	int size = mask.getSize();

	// Assert
	EXPECT_EQ(prefixLength, 24);
	EXPECT_EQ(octet0, 255);
	EXPECT_EQ(octet1, 255);
	EXPECT_EQ(octet2, 255);
	EXPECT_EQ(size, 3);
}

TEST(Mask, OperatorNot)
{
	// Arrange
	Mask mask(24);

	// Act
	Mask notMask = ~mask;
	uint8_t octet0 = notMask[0];
	uint8_t octet1 = notMask[1];
	uint8_t octet2 = notMask[2];

	// Assert
	EXPECT_EQ(octet0, 0);
	EXPECT_EQ(octet1, 0);
	EXPECT_EQ(octet2, 0);
}