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
            return express( myInteger, myDecimal, myMaxDecimalDigits, myIsNegative );
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
            const bool isTooBig = integer > myMaxExpressibleInteger;

            if( isTooBig )
            {
                myInteger = myMaxExpressibleInteger;
                myDecimal = myMaxExpressibleDecimal;
                return;
            }

            const DecimalType decimalPartAsFloat = inValue - static_cast<DecimalType>( integer );
            const auto powerMultiplierAsFloat = std::pow( static_cast<DecimalType>( 10 ), static_cast<DecimalType>( getMaxDecimalDigits() ) );
            const auto powerMultiplier = static_cast<uint64_t>( std::ceil( powerMultiplierAsFloat - 0.5 ) );
            const auto decimalDigitsShifted = decimalPartAsFloat * static_cast<decltype( decimalPartAsFloat )>( powerMultiplier );
            const auto decimalDigits = static_cast<decltype( myDecimal )>( std::ceil( decimalDigitsShifted - 0.5 ) );

            if( decimalDigits > myMaxExpressibleDecimal )
            {
                myInteger = integer + 1;
                myDecimal = 0;
                return;
            }

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
            return express( myMaxExpressibleInteger, myMaxExpressibleDecimal, myMaxDecimalDigits, myIsNegative );
        }


        DecimalType NewDecimal::getMinExpressibleNumber() const
        {
            return -1 * getMaxExpressibleNumber();
        }


        std::ostream& NewDecimal::toStream( std::ostream& os ) const
        {
            if( myInteger == 0 && myDecimal == 0 )
            {
                os << "0";
                return os;
            }

            if( myIsNegative )
            {
                os << "-";
            }

            os << myInteger;

            if( myDecimal == 0 )
            {
                return os;
            }

            os << ".";

            auto decIntStr = std::to_string( myDecimal );
            std::stringstream ss;

            bool isNonZeroReached = false;

            for ( auto c = decIntStr.crbegin();
                  c != decIntStr.crend();
                  ++c )
            {
                if( *c == '0' && !isNonZeroReached )
                {
                    continue;
                }

                isNonZeroReached = true;
                ss << *c;
            }

            const auto backwards = ss.str();

            short digits = 0;
            decltype( myDecimal ) tens = 1;

            for( int i = 0; i <= myMaxDecimalDigits; ++i )
            {
                ++digits;
                tens *= 10;
                const auto r = myDecimal / tens;

                if( r < 1 )
                {
                    break;
                }
            }

            short leadingZeros = myMaxDecimalDigits - digits;

            for ( short i = 0; i < leadingZeros; ++i )
            {
                os << "0";
            }

            for ( auto c = backwards.crbegin();
                  c != backwards.crend();
                  ++c )
            {
                os << *c;
            }

            return os;
        }


        std::string NewDecimal::toString() const
        {
            std::stringstream ss;
            toStream( ss );
            return ss.str();
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


        decltype( NewDecimal::myInteger ) NewDecimal::findMax( short inNumDigits )
        {
            decltype( myInteger ) mult = 0;
            decltype( myInteger ) result = 0;

            for( short i = 0; i < inNumDigits; ++i )
            {
                mult = static_cast<decltype( myInteger )>( std::ceil( std::pow( 10, i ) - 0.5) );
                const auto add = mult * 9;
                result += add;
            }

            return result;
        }


        void NewDecimal::setMaxExpressibleInteger()
        {
            myMaxExpressibleInteger = findMax( getMaxIntegerDigits() );
        }


        void NewDecimal::setMaxExpressibleDecimal()
        {
            myMaxExpressibleDecimal = findMax( getMaxDecimalDigits() );
        }


        void NewDecimal::setMaxExpressibleNumber()
        {
            setMaxExpressibleInteger();
            setMaxExpressibleDecimal();
        }

        DecimalType NewDecimal::express( uint64_t inInteger, uint64_t inDecimal, short inMaxDecimalDigits, bool inIsNegative )
        {
            const auto integer = static_cast<DecimalType>( inInteger );
            const auto decimalPartAsFloat = static_cast<DecimalType>( inDecimal );
            const auto powerMultiplierAsFloat = std::pow( static_cast<DecimalType>( 10 ), static_cast<DecimalType>( inMaxDecimalDigits ) );
            const auto powerMultiplier = static_cast<DecimalType>( std::ceil( powerMultiplierAsFloat - 0.5 ) );
            const auto decimal = decimalPartAsFloat / powerMultiplier;
            auto result = integer + decimal;

            if( inIsNegative )
            {
                result *= -1;
            }

            return result;
        }
    }
}
