#include "../inc/ICRC.h"
#include "../inc/XModem16BitCRC.h"
#include "../inc/CCITTFalse16BitCRC.h"
#include "../inc/BZip32BitCRC.h"
#include "../inc/CRC32Bit.h"
#include "../inc/CRC8Bit.h"
#include "../inc/Modbus16BitCRC.h"

namespace DriveCommLib {
    std::unique_ptr<ICRC> ICRC::Factory(CRC_Type type)
    {
        switch (type)
        {
        case CRC_Type::XModem16Bit:
            return std::unique_ptr<ICRC>(new XModem16BitCRC());
        case CRC_Type::CCITFalse16Bit:
            return std::unique_ptr<ICRC>(new CCITTFalse16BitCRC());
        case CRC_Type::CRC32Bit:
            return std::unique_ptr<ICRC>(new CRC32Bit());
        case CRC_Type::BZip32Bit:
            return std::unique_ptr<ICRC>(new BZip32BitCRC());
        case CRC_Type::CRC8Bit:
            return std::unique_ptr<ICRC>(new CRC8Bit());
        case CRC_Type::Modbus16Bit:
            return std::unique_ptr<ICRC>(new Modbus16BitCRC());
        default:
            return nullptr;
        }
    }
}