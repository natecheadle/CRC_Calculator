#pragma once

namespace CRC_Calculator {   
    template<class T>
    class CRCHelper
    {
    public:
        CRCHelper(
            T polynomial,
            T initValue,
            T xorOut,
            bool reflectData
        ) : 
        m_Polynomial(polynomial),
        m_ReflectData(reflectData),
        m_Width(sizeof(polynomial) * 8),
        m_InitValue(initValue),
        m_XorOut(xorOut)
        {
            PopulateCRCTable();
        };

        ~CRCHelper() = default;

        T CalculateCRCBitWise(const unsigned char* data, size_t size)
        {
            T tableValue{m_InitValue};

            for (size_t bytes = 0; bytes < size; bytes++)
            {
                if(m_ReflectData)
                {
                    tableValue = (tableValue >> 8) ^ obtainTableValue(static_cast<unsigned char>(tableValue & 0xFF) ^ data[bytes]);
                }
                else
                {
                    tableValue = (tableValue << 8) ^ obtainTableValue(static_cast<unsigned char>((tableValue >> (m_Width - 8)) & 0xFF) ^ data[bytes]);
                }
            }

            if ((8 * sizeof(T)) > m_Width)
            {
                tableValue = tableValue & ((static_cast<T>(1) << m_Width) - 1);
            }

            return tableValue ^ m_XorOut;
        }

        T CalculateCRCViaTable(const unsigned char* data, size_t size)
        {
            T tableValue{ m_InitValue };

            for (size_t bytes = 0; bytes < size; bytes++)
            {
                if (m_ReflectData)
                {
                    tableValue = (tableValue >> 8) ^ m_CRCTable[static_cast<unsigned char>(tableValue & 0xFF) ^ data[bytes]];
                }
                else
                {
                    tableValue = (tableValue << 8) ^ m_CRCTable[(static_cast<unsigned char>(tableValue >> (m_Width - 8)) & 0xFF) ^ data[bytes]];
                }
            }
        
            if ((8 * sizeof(T)) > m_Width)
            {
                tableValue = tableValue & ((static_cast<T>(1) << m_Width) - 1);
            }

            return tableValue ^ m_XorOut;
        }

    private:
        void PopulateCRCTable()
        {
            for (unsigned short posArray = 0; posArray < 256; posArray++)
            {
                m_CRCTable[posArray] = obtainTableValue(static_cast<unsigned char>(posArray & 0xFF));
            }
        }

        T reflectValue(T data, unsigned short numBits)
        {
            T reflectedValue{ 0 };
            unsigned short posBit{ 0 };

            for (posBit = 0; posBit < numBits; posBit++)
            {
                if ((data & 1) == 1)
                {
                    reflectedValue |= static_cast<T>(1) << ((numBits - 1) - posBit);
                }

                data = (data >> 1);
            }
            return reflectedValue;
        }       

        T obtainTableValue(unsigned char tablePos)
        {
            T tableValue{ 0 };
            unsigned char posBit = 0;

            if(m_ReflectData)
            {
                tableValue = static_cast<T>(reflectValue(tablePos, 8) & 0xFF) << (m_Width - 8);
            }
            else
            {
                tableValue = static_cast<T>(tablePos) << (m_Width - 8);
            }
            
            for (posBit = 0; posBit < 8; posBit++)
            {
                if (tableValue & (static_cast<T>(1) << (m_Width - 1)))
                {
                    tableValue = (tableValue << 1) ^ m_Polynomial;
                }
                else
                {
                    tableValue = (tableValue << 1);
                }
            }
            return m_ReflectData ? reflectValue(tableValue, m_Width) : tableValue;
        }

        const T m_Polynomial;
        const T m_InitValue;
        const T m_XorOut;
        const unsigned short m_Width;
        const bool m_ReflectData;
        T m_CRCTable[256];
    };
} // namespace CRC
