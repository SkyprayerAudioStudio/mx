// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mx/core/Decimals.h"
#include "mx/core/PreciseDecimal.h"
#include "mx/core/UnusedParameter.h"

#include <sstream>
#include <iomanip>

namespace mx
{
    namespace core
    {
        class Decimal::impl
        {
        public:
            impl( short inMaxIntegerDigits,
                  short inMaxDecimalDigits,
                  const DecimalType inValue )
            :myValue( inMaxIntegerDigits, inMaxDecimalDigits, inValue ) {}
            ~impl ()
            {

            }
            
            void setValue( DecimalType value )
            {
                myValue.setValue( value );
            }


            DecimalType getValue() const
            {
                return myValue.getValue();
            }


            std::string toString() const
            {
                return myValue.toString();
            }


            std::ostream& toStream( std::ostream& os ) const
            {
                return myValue.toStream( os );
            }

        private:
            PreciseDecimal myValue;

        };
        
        
        Decimal::Decimal( DecimalType value )
        :myImpl( new Decimal::impl( 19, DEFAULT_PRECISION, value ) )
        {

        }

        
        Decimal::Decimal()
        :myImpl( new Decimal::impl( 19, DEFAULT_PRECISION, 0 ) )
        {

        }


        Decimal::~Decimal()
        {

        }
        
        Decimal::Decimal( const Decimal& other )
        :myImpl( new Decimal::impl( *other.myImpl ) )
        {

        }


        Decimal::Decimal( Decimal&& other )
        :myImpl( std::move( other.myImpl ) )
        {

        }


        Decimal& Decimal::operator=( const Decimal& other )
        {
            this->myImpl = std::unique_ptr<Decimal::impl>( new Decimal::impl( *other.myImpl ) );
            return *this;
        }


        Decimal& Decimal::operator=( Decimal&& other )
        {
            myImpl = std::move( other.myImpl );
            return *this;
        }


        DecimalType Decimal::getValue() const
        {
            return myImpl->getValue();
        }


        void Decimal::setValue( DecimalType value )
        {
            myImpl->setValue( value );
        }


        void Decimal::parse( const std::string& value )
        {
            std::stringstream ss( value );
            DecimalType temp = 0;
            if ( ( ss >> temp).fail() || !( ss >> std::ws).eof())
            {
                return;
            }
            setValue( temp );
        }


        std::string Decimal::toString() const
        {
            return myImpl->toString();
        }


        std::ostream& Decimal::toStream( std::ostream& os ) const
        {
            return myImpl->toStream( os );
        }


        std::string toString( const Decimal& value, unsigned int precision )
        {
            MX_UNUSED( precision );
            return value.toString();
        }


        std::ostream& toStream( std::ostream& os, const Decimal& value, unsigned int precision )
        {
            MX_UNUSED( precision );
            return value.toStream( os );
        }


        std::ostream& operator<<( std::ostream& os, const Decimal& value )
        {
            return value.toStream( os );
        }


        DecimalRange::DecimalRange( DecimalType min, DecimalType max, DecimalType value )
        :Decimal( value )
        ,myMin( min )
        ,myMax( max )
        {
            setValue( value );
        }


        DecimalRange& DecimalRange::operator=( const DecimalRange& other )
        {
            setValue( other.getValue() );
            return *this;
        }


        DecimalRange::DecimalRange( DecimalRange&& other )
        :Decimal( std::move( other ) )
        ,myMin( std::move( other.myMin ) )
        ,myMax( std::move( other.myMax ) )
        {

        }


        DecimalRange& DecimalRange::operator=( DecimalRange&& other )
        {
            setValue( other.getValue() );
            return *this;
        }


        void DecimalRange::setValue( DecimalType value )
        {
            if ( value < myMin )
            {
                Decimal::setValue( myMin );
            }
            else if ( value > myMax )
            {
                Decimal::setValue( myMax );
            }
            else
            {
                Decimal::setValue( value );
            }
        }


        void DecimalRange::parse( const std::string& value )
        {
            std::stringstream ss( value );
            DecimalType temp = 0;
            if ((ss >> temp).fail() || !(ss >> std::ws).eof())
            {
                return;
            }
            setValue( temp );
        }
        
        PositiveDecimal::PositiveDecimal( DecimalType value )
        :Decimal( value )
        {
            setValue( value );
        }


        PositiveDecimal::PositiveDecimal()
        :Decimal( 1 )
        {

        }
        

        void PositiveDecimal::setValue( DecimalType value )
        {
            if ( value <= 0 )
            {
                Decimal::setValue( NON_ZERO_AMOUNT );
            }
            else
            {
                Decimal::setValue( value );
            }
        }


        void PositiveDecimal::parse( const std::string& value )
        {
            std::stringstream ss( value );
            DecimalType temp = NON_ZERO_AMOUNT;
            if ((ss >> temp).fail() || !(ss >> std::ws).eof())
            {
                return;
            }
            setValue( temp );
        }


        NonNegativeDecimal::NonNegativeDecimal( DecimalType value )
        :Decimal( value )
        {
            setValue( value );
        }


        NonNegativeDecimal::NonNegativeDecimal()
        :Decimal( 0 )
        {

        }
        

        void NonNegativeDecimal::setValue( DecimalType value )
        {
            if ( value < 0 )
            {
                Decimal::setValue( 0 );
            }
            else
            {
                Decimal::setValue( value );
            }
        }


        void NonNegativeDecimal::parse( const std::string& value )
        {
            std::stringstream ss( value );
            DecimalType temp = 0;
            if ((ss >> temp).fail() || !(ss >> std::ws).eof())
            {
                return;
            }
            this->setValue( temp );
        }

        
        Percent::Percent( DecimalType value )
        :DecimalRange( 0, 100, value )
        {

        }


        Percent::Percent()
        :DecimalRange( 0, 100, 0 )
        {

        }
        
        RotationDegrees::RotationDegrees()
        :DecimalRange( -180, 180, 0 )
        {

        }


        RotationDegrees::RotationDegrees( DecimalType value )
        :DecimalRange( -180, 180, value )
        {

        }

        
        TrillBeats::TrillBeats( DecimalType value )
        :Decimal( value )
        {
            this->setValue( value );
        }


        TrillBeats::TrillBeats()
        :Decimal( 2 )
        {

        }


        void TrillBeats::setValue( DecimalType value )
        {
            if ( value < 2 )
            {
                Decimal::setValue( 2 );
            }
            else
            {
                Decimal::setValue( value );
            }
        }

        
        void TrillBeats::parse( const std::string& value )
        {
            std::stringstream ss( value );
            DecimalType temp = 0;
            if ((ss >> temp).fail() || !(ss >> std::ws).eof())
            {
                return;
            }
            this->setValue( temp );
        }
    }
}
