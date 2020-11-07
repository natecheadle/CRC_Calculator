#pragma once
#include "ICRC.h"
#include "../src/CRCHelper.hpp"

namespace CRC_Calculator {
    class XModem16BitCRC : public ICRC{
    public:
        XModem16BitCRC();
        ~XModem16BitCRC() = default;

        std::vector<unsigned char> CalculateCRC(
            const unsigned char* data,
            size_t size,
            CRC_Method method) final;

        unsigned short GetCRCSize() final { return sizeof(unsigned short); }

    private:
        static constexpr unsigned short Polynomial = 0x1021;
        static constexpr unsigned short InitialValue = 0x000;
        static constexpr unsigned short XorOut = 0x000;
        static constexpr bool ReflectData = false;

        CRCHelper<unsigned short> m_Helper;
    };
}