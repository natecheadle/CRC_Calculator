#pragma once
#include "ICRC.h"
#include "../src/CRCHelper.hpp"

namespace DriveCommLib {
    class CRC8Bit : public ICRC {
    public:
        CRC8Bit();
        ~CRC8Bit() = default;

        std::vector<unsigned char> CalculateCRC(
            const unsigned char* data,
            size_t size,
            CRC_Method method) final;

        unsigned short GetCRCSize() final { return sizeof(unsigned char); }

    private:
        static constexpr unsigned char Polynomial = 0x07;
        static constexpr unsigned char InitialValue = 0x00;
        static constexpr unsigned char XorOut = 0x000;
        static constexpr bool ReflectData = false;

        CRCHelper<unsigned char> m_Helper;
    };
}