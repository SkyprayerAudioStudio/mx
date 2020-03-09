// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mxtest/control/CompileControl.h"
#ifdef MX_COMPILE_CORE_TESTS

#include "cpul/cpulTestHarness.h"
#include "mxtest/core/HelperFunctions.h"
#include "mx/core/Elements.h"
#include "mxtest/core/MordentTest.h"
#include "mxtest/core/MidiInstrumentTest.h"


using namespace mx::core;
using namespace std;
using namespace mxtest;

TEST( Test01, Mordent )
{
    variant v = variant::one;
	MordentPtr object = tgenMordent( v );
	stringstream expected;
	tgenMordentExpected( expected, 1, v );
	stringstream actual;
	// object->toStream( std::cout, 1 );
	object->toStream( actual, 1 );
	CHECK_EQUAL( expected.str(), actual.str() )
	CHECK( ! object->hasAttributes() )
	CHECK( ! object->hasContents() )
}
TEST( Test02, Mordent )
{
    variant v = variant::two;
	MordentPtr object = tgenMordent( v );
	stringstream expected;
	tgenMordentExpected( expected, 1, v );
	stringstream actual;
	// object->toStream( std::cout, 1 );
	object->toStream( actual, 1 );
	CHECK_EQUAL( expected.str(), actual.str() )
	CHECK( object->hasAttributes() )
	CHECK( ! object->hasContents() )
}
TEST( Test03, Mordent )
{
    variant v = variant::three;
	MordentPtr object = tgenMordent( v );
	stringstream expected;
	tgenMordentExpected( expected, 1, v );
	stringstream actual;
	// object->toStream( std::cout, 1 );
	object->toStream( actual, 1 );
	CHECK_EQUAL( expected.str(), actual.str() )
	CHECK( object->hasAttributes() )
	CHECK( ! object->hasContents() )
}

namespace mxtest
{
    MordentPtr tgenMordent( variant v )
    {
        MordentPtr o = makeMordent();
        switch ( v )
        {
            case variant::one:
            {
                
            }
                break;
            case variant::two:
            {
                o->getAttributes()->hasBeats = true;
                o->getAttributes()->beats = TrillBeats( 1.2 );
                o->getAttributes()->hasApproach = true;
                o->getAttributes()->approach = AboveBelow::above;
                o->getAttributes()->hasAccelerate = true;
                o->getAttributes()->accelerate = YesNo::yes;
            }
                break;
            case variant::three:
            {
                o->getAttributes()->hasDeparture = true;
                o->getAttributes()->departure = AboveBelow::below;
            }
                break;
            default:
                break;
        }
        return o;
    }
    void tgenMordentExpected( std::ostream& os, int i, variant v )
    {
        
        switch ( v )
        {
            case variant::one:
            {
                streamLine( os, i, R"(<mordent/>)", false );
            }
                break;
            case variant::two:
            {
                streamLine( os, i, R"(<mordent accelerate="yes" beats="2" approach="above"/>)", false );
            }
                break;
            case variant::three:
            {
                streamLine( os, i, R"(<mordent departure="below"/>)", false );
            }
                break;
            default:
                break;
        }
    }
}

#endif
