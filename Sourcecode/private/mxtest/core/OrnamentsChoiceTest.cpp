// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mxtest/control/CompileControl.h"
#ifdef MX_COMPILE_CORE_TESTS

#include "cpul/cpulTestHarness.h"
#include "mxtest/core/HelperFunctions.h"
#include "mxtest/core/OrnamentsChoiceTest.h"
#include "mxtest/core/ScalingTest.h"
#include "mxtest/core/LayoutGroupTest.h"
#include "mxtest/core/AppearanceTest.h"

using namespace mx::core;
using namespace std;
using namespace mxtest;

TEST( Test01, OrnamentsChoice )
{
    variant v = variant::one;
	OrnamentsChoicePtr object = tgenOrnamentsChoice( v );
	stringstream expected;
	tgenOrnamentsChoiceExpected( expected, 1, v );
	stringstream actual;
	// object->toStream( std::cout, 1 );
    bool isOneLineOnly = false;
	object->streamContents( actual, 1, isOneLineOnly );
	CHECK_EQUAL( expected.str(), actual.str() )
	CHECK( ! object->hasAttributes() )
	CHECK( object->hasContents() )
}
TEST( Test02, OrnamentsChoice )
{
    variant v = variant::two;
	OrnamentsChoicePtr object = tgenOrnamentsChoice( v );
	stringstream expected;
	tgenOrnamentsChoiceExpected( expected, 1, v );
	stringstream actual;
	// object->toStream( std::cout, 1 );
    bool isOneLineOnly = false;
	object->streamContents( actual, 1, isOneLineOnly );
	CHECK_EQUAL( expected.str(), actual.str() )
	CHECK( ! object->hasAttributes() )
	CHECK( object->hasContents() )
}
TEST( Test03, OrnamentsChoice )
{
    variant v = variant::three;
	OrnamentsChoicePtr object = tgenOrnamentsChoice( v );
	stringstream expected;
	tgenOrnamentsChoiceExpected( expected, 1, v );
	stringstream actual;
	// object->toStream( std::cout, 1 );
    bool isOneLineOnly = false;
	object->streamContents( actual, 1, isOneLineOnly );
	CHECK_EQUAL( expected.str(), actual.str() )
	CHECK( ! object->hasAttributes() )
	CHECK( object->hasContents() )
}

namespace mxtest
{
    OrnamentsChoicePtr tgenOrnamentsChoice( variant v )
    {
        OrnamentsChoicePtr o = makeOrnamentsChoice();
        switch ( v )
        {
            case variant::one:
            {
                o->getTrillMark()->getAttributes()->hasFontStyle = true;
                o->getTrillMark()->getAttributes()->fontStyle = FontStyle::italic;
            }
                break;
            case variant::two:
            {
                o->setChoice( OrnamentsChoice::Choice::otherOrnament );
                o->getOtherOrnament()->setValue( XsString( "Mordiarty" ) );
                o->getOtherOrnament()->getAttributes()->hasPlacement = true;
            }
                break;
            case variant::three:
            {
                o->setChoice( OrnamentsChoice::Choice::shake );
            }
                break;
            default:
                break;
        }
        return o;
    }
    void tgenOrnamentsChoiceExpected( std::ostream& os, int i, variant v )
    {
        
        switch ( v )
        {
            case variant::one:
            {
                streamLine( os, i, R"(<trill-mark font-style="italic"/>)", false );
            }
                break;
            case variant::two:
            {

                streamLine( os, i, R"(<other-ornament placement="above">Mordiarty</other-ornament>)", false );
            }
                break;
            case variant::three:
            {

                streamLine( os, i, R"(<shake/>)", false );
            }
                break;
            default:
                break;
        }
    }
}

#endif
