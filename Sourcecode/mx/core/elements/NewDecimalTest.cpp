// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mxtest/control/CompileControl.h"
#ifdef MX_COMPILE_NEW_DECIMAL_TESTS

#include "cpul/cpulTestHarness.h"
#include "mx/core/NewDecimal.h"
#include <sstream>

using namespace mx::core;

TEST( test0, NewDecimalTest )
{
    const DecimalType expected = 123.654;
    NewDecimal d{ 10, 5, 123.654 };
    const auto actual = d.getValue();
    CHECK_DOUBLES_EQUAL( expected, actual, 0.0001 );
}
T_END;

#endif
