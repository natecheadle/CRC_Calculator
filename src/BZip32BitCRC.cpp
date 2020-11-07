#include "../inc/BZip32BitCRC.h"

#include <cstring>

namespace DriveCommLib {
    BZip32BitCRC::BZip32BitCRC() :
        ICRC(CRC_Type::BZip32Bit),
        m_Helper(CRCHelper<unsigned int>(Polynomial, InitialValue, XorOut, ReflectData))
        {}

    std::vector<unsigned char> BZip32BitCRC::CalculateCRC(
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