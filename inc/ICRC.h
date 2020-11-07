#pragma once
#include <vector>
#include <memory>

namespace CRC_Calculator {
    enum class CRC_Method
    {
        BitWise,
        CRCTable
    };

    enum class CRC_Type
    {
        XModem16Bit,
        CCITFalse16Bit,
        CRC32Bit,
        CRC8Bit,
        BZip32Bit,
        Modbus16Bit
    };

    class ICRC {
    public:
        virtual ~ICRC() = default;

        virtual std::vector<unsigned char> CalculateCRC(
            const unsigned char* data,
            size_t size,
            CRC_Method method) = 0;

        virtual unsigned short GetCRCSize() = 0;

        CRC_Type GetCRCTtype() { return m_CRCType; }

        static std::unique_ptr<ICRC> Factory(CRC_Type type);

    protected:
        ICRC(CRC_Type type): 
            m_CRCType(type){}
    private:
        CRC_Type m_CRCType;
    };
}