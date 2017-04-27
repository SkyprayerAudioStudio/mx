// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mxtest/control/CompileControl.h"
#ifdef MX_COMPILE_NEW_DECIMAL_TESTS

#include "cpul/cpulTestHarness.h"
#include "mx/core/NewDecimal.h"
#include <sstream>

using namespace mx::core;

TEST( ctorSSD, NewDecimalTest )
{
    NewDecimal d{ 3, 2, 123.45 };
    CHECK_EQUAL( 3, d.getMaxIntegerDigits() );
    CHECK_EQUAL( 2, d.getMaxDecimalDigits() );
    CHECK_DOUBLES_EQUAL( 999.99, d.getMaxExpressibleNumber(), 0.00001 );
    CHECK_DOUBLES_EQUAL( -999.99, d.getMinExpressibleNumber(), 0.00001 );
    CHECK_DOUBLES_EQUAL( 123.45, d.getValue(), 0.00002 );
}
T_END;


TEST( ctorSS, NewDecimalTest )
{
    NewDecimal d{ 4, 1 };
    CHECK_EQUAL( 4, d.getMaxIntegerDigits() );
    CHECK_EQUAL( 1, d.getMaxDecimalDigits() );
    CHECK_DOUBLES_EQUAL( 9999.9, d.getMaxExpressibleNumber(), 0.00001 );
    CHECK_DOUBLES_EQUAL( -9999.9, d.getMinExpressibleNumber(), 0.00001 );
    CHECK_DOUBLES_EQUAL( 0, d.getValue(), 0.00001 );
}
T_END;


TEST( ctorD, NewDecimalTest )
{
    NewDecimal d{ 44.33 };
    CHECK_EQUAL( 10, d.getMaxIntegerDigits() );
    CHECK_EQUAL( 6, d.getMaxDecimalDigits() );
    CHECK_DOUBLES_EQUAL( 9999999999.99999, d.getMaxExpressibleNumber(), 0.1 );
    CHECK_DOUBLES_EQUAL( -9999999999.99999, d.getMinExpressibleNumber(), 0.1 );
    CHECK_DOUBLES_EQUAL( 44.33, d.getValue(), 0.00001 );
}
T_END;


TEST( ctor, NewDecimalTest )
{
    NewDecimal d{};
    CHECK_EQUAL( 10, d.getMaxIntegerDigits() );
    CHECK_EQUAL( 6, d.getMaxDecimalDigits() );
    CHECK_DOUBLES_EQUAL( 9999999999.99999, d.getMaxExpressibleNumber(), 0.1 );
    CHECK_DOUBLES_EQUAL( -9999999999.99999, d.getMinExpressibleNumber(), 0.1 );
    CHECK_DOUBLES_EQUAL( 0.0, d.getValue(), 0.00001 );
}
T_END;


TEST( getValue, NewDecimalTest )
{
    const DecimalType expected = 123.654;
    NewDecimal d{ 10, 5, expected };
    const auto actual = d.getValue();
    CHECK_DOUBLES_EQUAL( expected, actual, 0.0001 );
}
T_END;


TEST( getValueRounded, NewDecimalTest )
{
    const short numIntDigits = 4;
    const short numDecDeigits = 2;
    const DecimalType value = 7321.83940239;
    const DecimalType expected = 7321.84;
    NewDecimal d{ numIntDigits, numDecDeigits, value };
    const auto actual = d.getValue();
    CHECK_DOUBLES_EQUAL( expected, actual, 0.0000001 );
}
T_END;


TEST( setValue, NewDecimalTest )
{
    const DecimalType expected = 8329.9238;
    const short numIntDigits = 6;
    const short numDecDeigits = 7;
    NewDecimal d{ numIntDigits, numDecDeigits, 3458.2342 };
    d.setValue( expected );
    const auto actual = d.getValue();
    CHECK_DOUBLES_EQUAL( expected, actual, 0.0001 );
}
T_END;


TEST( setValueRounded, NewDecimalTest )
{
    const short numIntDigits = 1;
    const short numDecDeigits = 1;
    const DecimalType value = 0.55;
    const DecimalType expected = 0.6;
    NewDecimal d{ numIntDigits, numDecDeigits, 1232.1212 };
    d.setValue( value );
    const auto actual = d.getValue();
    CHECK_DOUBLES_EQUAL( expected, actual, 0.0000001 );
}
T_END;


TEST( tooBig, NewDecimalTest )
{
    const short numIntDigits = 3;
    const short numDecDeigits = 1;
    const DecimalType value = 8769.5;
    const DecimalType expected = 999.9;
    NewDecimal d{ numIntDigits, numDecDeigits };
    d.setValue( value );
    const auto actual = d.getValue();
    CHECK_DOUBLES_EQUAL( expected, actual, 0.0000001 );
}
T_END;


TEST( str01, NewDecimalTest )
{
    const short numIntDigits = 4;
    const short numDecDeigits = 3;
    const DecimalType value = 8769.5;
    const std::string expected = "8769.5";
    NewDecimal d{ numIntDigits, numDecDeigits, value };
    const auto actual = d.toString();
    CHECK_EQUAL( expected, actual );
}
T_END;


TEST( str02, NewDecimalTest )
{
    const short numIntDigits = 4;
    const short numDecDeigits = 3;
    const DecimalType value = 1234.99999;
    const std::string expected = "1235";
    NewDecimal d{ numIntDigits, numDecDeigits, value };
    const auto actual = d.toString();
    CHECK_EQUAL( expected, actual );
}
T_END;


TEST( str03, NewDecimalTest )
{
    const short numIntDigits = 4;
    const short numDecDeigits = 10;
    const DecimalType value = -0.0000000001;
    const std::string expected = "-0.0000000001";
    NewDecimal d{ numIntDigits, numDecDeigits, value };
    const auto actual = d.toString();
    CHECK_EQUAL( expected, actual );
}
T_END;


#endif
