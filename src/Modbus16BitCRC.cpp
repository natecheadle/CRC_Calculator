#include "../inc/Modbus16BitCRC.h"

#include <cstring>

namespace CRC_Calculator {
    Modbus16BitCRC::Modbus16BitCRC() :
        ICRC(CRC_Type::Modbus16Bit),
        m_Helper(CRCHelper<unsigned short>(Polynomial, InitialValue, XorOut, ReflectData))
        {}

    std::vector<unsigned char> Modbus16BitCRC::CalculateCRC(
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
            unsigned short crcValue = m_Helper.CalculateCRCBitWise(data, size);
            std::memcpy(&crc[0], &crcValue, GetCRCSize());
            break;
        }
        case CRC_Method::CRCTable:
        {
            unsigned short crcValue = m_Helper.CalculateCRCViaTable(data, size);
            std::memcpy(&crc[0], &crcValue, GetCRCSize());
            break;
        }
        }

        return crc;
    }
}