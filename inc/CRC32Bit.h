#pragma once
#include "ICRC.h"
#include "../src/CRCHelper.hpp"

namespace DriveCommLib {
    class CRC32Bit : public ICRC {
    public:
        CRC32Bit();
        ~CRC32Bit() = default;

        std::vector<unsigned char> CalculateCRC(
            const unsigned char* data,
            size_t size,
            CRC_Method method) final;

        unsigned short GetCRCSize() final { return sizeof(unsigned int); }

    private:
        static constexpr unsigned int Polynomial = 0x04C11DB7;
        static constexpr unsigned int InitialValue = 0xFFFFFFFF;
        static constexpr unsigned int XorOut = 0xFFFFFFFF;
        static constexpr bool ReflectData = true;

        CRCHelper<unsigned int> m_Helper;
    };
}