#include "../inc/CRC8Bit.h"

#include <cstring>

namespace CRC_Calculator {
    CRC8Bit::CRC8Bit() :
        ICRC(CRC_Type::CRC8Bit),
        m_Helper(CRCHelper<unsigned char>(Polynomial, InitialValue, XorOut, ReflectData))
        {}

    std::vector<unsigned char> CRC8Bit::CalculateCRC(
        const unsigned char* data,
        size_t size,
        CRC_Method method)
    {
        std::vector<unsigned char> crc;
        crc.resize(GetCRCSize());
        switch (method)
        {
        case CRC_Method::BitWise:
        {
            unsigned char crcValue = m_Helper.CalculateCRCBitWise(data, size);
            std::memcpy(&crc[0], &crcValue, GetCRCSize());
            break;
        }
        case CRC_Method::CRCTable:
        {
            unsigned char crcValue = m_Helper.CalculateCRCViaTable(data, size);
            std::memcpy(&crc[0], &crcValue, GetCRCSize());
            break;
        }
        }

        return crc;
    }
}