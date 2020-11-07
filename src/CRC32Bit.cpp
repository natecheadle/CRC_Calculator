#include "../inc/CRC32Bit.h"

#include <cstring>

namespace DriveCommLib {
    CRC32Bit::CRC32Bit() :
        ICRC(CRC_Type::CRC32Bit),
        m_Helper(CRCHelper<unsigned int>(Polynomial, InitialValue, XorOut, ReflectData))
        {}

    std::vector<unsigned char> CRC32Bit::CalculateCRC(
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
            unsigned int crcValue = m_Helper.CalculateCRCBitWise(data, size);
            std::memcpy(&crc[0], &crcValue, GetCRCSize());
            break;
        }
        case CRC_Method::CRCTable:
        {
            unsigned int crcValue = m_Helper.CalculateCRCViaTable(data, size);
            std::memcpy(&crc[0], &crcValue, GetCRCSize());
            break;
        }
        }

        return crc;
    }
}