#pragma once
#include "ICRC.h"
#include "../src/CRCHelper.hpp"

namespace DriveCommLib {
    class Modbus16BitCRC : public ICRC {
    public:
        Modbus16BitCRC();
        ~Modbus16BitCRC() = default;

        std::vector<unsigned char> CalculateCRC(
            const unsigned char* data,
            size_t size,
            CRC_Method method) final;

        unsigned short GetCRCSize() final { return sizeof(unsigned short); }

    private:
        static constexpr unsigned short Polynomial = 0x8005;
        static constexpr unsigned short InitialValue = 0xFFFF;
        static constexpr unsigned short XorOut = 0x000;
        static constexpr bool ReflectData = true;

        CRCHelper<unsigned short> m_Helper;
    };
}