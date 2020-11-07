#include <map>

#include <gtest/gtest.h>
#include <ICRC.h>

namespace CRC_Calculator {

	class CRCParameterizedTestSuite : public testing::TestWithParam<CRC_Type> {};

	static const std::vector<unsigned char> defaultTestData = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 };
	static const std::map<CRC_Type, std::vector<unsigned char>> expectedResult =
	{
		{ CRC_Type::CCITFalse16Bit, { 0xB1, 0x29 } },
		{ CRC_Type::XModem16Bit, { 0xC3, 0x31 } },
		{ CRC_Type::BZip32Bit, { 0x18, 0x19, 0x89, 0xFC } },
		{ CRC_Type::CRC32Bit, {0x26, 0x39, 0xF4, 0xCB} },
		{ CRC_Type::CRC8Bit, { 0xF4 } },
		{ CRC_Type::Modbus16Bit, { 0x37, 0x4B } }
	};

	TEST_P(CRCParameterizedTestSuite, ValidateCreation)
	{
		std::unique_ptr<ICRC> crc = ICRC::Factory(GetParam());
		EXPECT_NE(nullptr, crc);
	}

	TEST_P(CRCParameterizedTestSuite, ValidateTableCalculation)
	{
		std::unique_ptr<ICRC> crc = ICRC::Factory(GetParam());
		EXPECT_NE(nullptr, crc);

		std::vector<unsigned char> result = crc->CalculateCRC(&defaultTestData[0], defaultTestData.size(), CRC_Method::CRCTable);
		EXPECT_EQ(result, expectedResult.at(GetParam()));
	}

	TEST_P(CRCParameterizedTestSuite, ValidateBitWiseCalculation)
	{
		std::unique_ptr<ICRC> crc = ICRC::Factory(GetParam());
		EXPECT_NE(nullptr, crc);

		std::vector<unsigned char> result = crc->CalculateCRC(&defaultTestData[0], defaultTestData.size(), CRC_Method::BitWise);
		EXPECT_EQ(result, expectedResult.at(GetParam()));
	}

	INSTANTIATE_TEST_SUITE_P(CRCTypes, CRCParameterizedTestSuite,
		testing::Values(
			CRC_Type::XModem16Bit,
			CRC_Type::CCITFalse16Bit,
			CRC_Type::CRC32Bit,
			CRC_Type::CRC8Bit,
			CRC_Type::BZip32Bit,
			CRC_Type::Modbus16Bit)
	);

	

}
