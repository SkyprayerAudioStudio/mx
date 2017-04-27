// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mx/core/NewDecimal.h"

#include <string>
#include <sstream>
#include <cmath>

namespace mx
{
    namespace core
    {
        NewDecimal::NewDecimal( short inMaxIntegerDigits, short inMaxDecimalDigits, DecimalType inValue )
        : myIsNegative{ inValue < 0.0 }
        , myInteger{ 0 }
        , myDecimal{ 0 }
        , myMaxIntegerDigits{ DEFAULT_MAX_INTEGER_DIGITS }
        , myMaxDecimalDigits{ DEFAULT_MAX_DECIMAL_DIGITS }
        {
            setMaxIntegerDigits( inMaxIntegerDigits );
            setMaxDecimalDigits( inMaxDecimalDigits );
            setMaxExpressibleNumber();
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
            const auto integer = static_cast<DecimalType>( myInteger );
            const auto decimalPartAsFloat = static_cast<DecimalType>( myDecimal );
            const auto powerMultiplierAsFloat = std::pow( static_cast<DecimalType>( 10 ), static_cast<DecimalType>( getMaxDecimalDigits() ) );
            const auto powerMultiplier = static_cast<DecimalType>( std::ceil( powerMultiplierAsFloat - 0.5 ) );
            const auto decimal = decimalPartAsFloat / powerMultiplier;
            auto result = integer + decimal;

            if( myIsNegative )
            {
                result *= -1;
            }

            return result;
        }


        void NewDecimal::setValue( DecimalType inValue )
        {
            if ( inValue < 0 )
            {
                myIsNegative = true;
                inValue *= -1;
            }
            else
            {
                myIsNegative = false;
            }

            const auto integer = static_cast<decltype( myInteger )>( inValue );
            const DecimalType decimalPartAsFloat = inValue - static_cast<DecimalType>( integer );
            const auto powerMultiplierAsFloat = std::pow( static_cast<DecimalType>( 10 ), static_cast<DecimalType>( getMaxDecimalDigits() ) );
            const auto powerMultiplier = static_cast<int>( std::ceil( powerMultiplierAsFloat - 0.5 ) );
            const auto decimalDigitsShifted = decimalPartAsFloat * static_cast<decltype( decimalPartAsFloat )>( powerMultiplier );
            const auto decimalDigits = static_cast<decltype( myDecimal )>( std::ceil( decimalDigitsShifted - 0.5 ) );
            myInteger = integer;
            myDecimal = decimalDigits;
        }


        short NewDecimal::getMaxIntegerDigits() const
        {
            return myMaxIntegerDigits;
        }


        short NewDecimal::getMaxDecimalDigits() const
        {
            return myMaxDecimalDigits;
        }


        DecimalType NewDecimal::getMaxExpressibleNumber() const
        {
            return myMaxExpressibleNumber;
        }


        DecimalType NewDecimal::getMinExpressibleNumber() const
        {
            return -1 * myMaxExpressibleNumber;
        }


        void NewDecimal::setMaxIntegerDigits( short inNumDigits )
        {
            if( inNumDigits < 1 )
            {
                myMaxIntegerDigits = 1;
                return;
            }

            if( inNumDigits > MAX_STORAGE_TYPE_DIGITS )
            {
                myMaxIntegerDigits = MAX_STORAGE_TYPE_DIGITS;
                return;
            }

            myMaxIntegerDigits = inNumDigits;
        }


        void NewDecimal::setMaxDecimalDigits( short inNumDigits )
        {
            if( inNumDigits < 1 )
            {
                myMaxDecimalDigits = 1;
                return;
            }

            if( inNumDigits > MAX_STORAGE_TYPE_DIGITS )
            {
                myMaxDecimalDigits = MAX_STORAGE_TYPE_DIGITS;
                return;
            }

            myMaxDecimalDigits = inNumDigits;
        }


        void NewDecimal::setMaxExpressibleNumber()
        {
            std::stringstream ss;

            for( int i = 0; i < getMaxIntegerDigits(); ++i )
            {
                ss << "9";
            }

            ss << ".";

            for( int i = 0; i < getMaxDecimalDigits(); ++i )
            {
                ss << "9";
            }

            ss >> myMaxExpressibleNumber;
        }
    }
}
