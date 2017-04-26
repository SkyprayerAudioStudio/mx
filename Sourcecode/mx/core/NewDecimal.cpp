// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mx/core/NewDecimal.h"

namespace mx
{
    namespace core
    {
        NewDecimal::NewDecimal( short inMaxIntegerDigits, short inMaxDecimalDigits, DecimalType inValue )
        : myIsNegative{ inValue < 0.0 }
        , myInteger{ 0 }
        , myDecimal{ 0 }
        , myMaxIntegerDigits{ inMaxIntegerDigits }
        , myMaxDecimalDigits{ inMaxDecimalDigits }
        {
            setValue( inValue );
        }


        NewDecimal::NewDecimal( short inMaxIntegerDigits, short inMaxDecimalDigits )
        : NewDecimal{ inMaxIntegerDigits, inMaxDecimalDigits, 0.0 }
        {

        }


        NewDecimal::NewDecimal( DecimalType inValue )
        : NewDecimal{ DEFAULT_MAX_INTEGER_DIGITS, DEFAULT_MAX_DECIMAL_DIGITS, inValue }
        {

        }


        NewDecimal::NewDecimal()
        : NewDecimal{ DEFAULT_MAX_INTEGER_DIGITS, DEFAULT_MAX_DECIMAL_DIGITS, 0.0 }
        {

        }


        DecimalType NewDecimal::getValue() const
        {
            return 0.0;
        }


        void NewDecimal::setValue( DecimalType inValue )
        {
            throw inValue;
        }
    }
}
