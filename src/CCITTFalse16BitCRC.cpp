#include "../inc/CCITTFalse16BitCRC.h"

#include <cstring>

namespace DriveCommLib {
     CCITTFalse16BitCRC::CCITTFalse16BitCRC() : 
     ICRC(CRC_Type::CCITFalse16Bit),
     m_Helper(CRCHelper<unsigned short>(Polynomial, InitialValue, XorOut, ReflectData))
     {}

    std::vector<unsigned char> CCITTFalse16BitCRC::CalculateCRC(
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
        }}

        return crc;
    }
}