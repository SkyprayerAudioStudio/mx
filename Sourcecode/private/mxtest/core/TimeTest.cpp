// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mxtest/control/CompileControl.h"
#ifdef MX_COMPILE_CORE_TESTS

#include "cpul/cpulTestHarness.h"
#include "mxtest/core/HelperFunctions.h"
#include "mx/core/Elements.h"

using namespace mx::core;
using namespace std;
using namespace mxtest;

TEST( Test01, Time )
{
	Time object;
	stringstream expected;
	streamLine( expected, 1, R"(<time>)" );
	streamLine( expected, 2, R"(<beats></beats>)" );
	streamLine( expected, 2, R"(<beat-type></beat-type>)" );
	streamLine( expected, 1, R"(</time>)", false );
	stringstream actual;
	// object.toStream( std::cout, 1 );
	object.toStream( actual, 1 );
	CHECK_EQUAL( expected.str(), actual.str() )
	CHECK( ! object.hasAttributes() )
	CHECK( object.hasContents() )
}
TEST( Test02, Time )
{
	Time object;
    object.getAttributes()->hasNumber = true;
    object.getAttributes()->number = StaffNumber{ 9 };
    object.getTimeChoice()->setChoice( TimeChoice::Choice::timeSignature );
    
    auto timeSignature = makeTimeSignatureGroup();
    timeSignature->getBeats()->setValue( XsString( "Test1" ) );
    timeSignature->getBeatType()->setValue( XsString( "Test2" ) );
    timeSignature->setHasInterchangeable( true );
    timeSignature->getInterchangeable()->getBeats()->setValue( XsString( "Bishop" ) );
    timeSignature->getInterchangeable()->getBeatType()->setValue( XsString( "Bones" ) );
    timeSignature->getInterchangeable()->setHasTimeRelation( true );
    timeSignature->getInterchangeable()->getTimeRelation()->setValue( TimeRelationEnum::bracket );
    object.getTimeChoice()->addTimeSignatureGroup( timeSignature );
    object.getTimeChoice()->removeTimeSignatureGroup( object.getTimeChoice()->getTimeSignatureGroupSet().cbegin() );

	stringstream expected;
	streamLine( expected, 1, R"(<time number="9">)" );
	streamLine( expected, 2, R"(<beats>Test1</beats>)" );
	streamLine( expected, 2, R"(<beat-type>Test2</beat-type>)" );
	streamLine( expected, 2, R"(<interchangeable>)" );
    streamLine( expected, 3, R"(<time-relation>bracket</time-relation>)" );
    streamLine( expected, 3, R"(<beats>Bishop</beats>)" );
    streamLine( expected, 3, R"(<beat-type>Bones</beat-type>)" );
    streamLine( expected, 2, R"(</interchangeable>)" );
	streamLine( expected, 1, R"(</time>)", false );
	stringstream actual;
	// object.toStream( std::cout, 1 );
	object.toStream( actual, 1 );
	CHECK_EQUAL( expected.str(), actual.str() )
	CHECK( object.hasAttributes() )
	CHECK( object.hasContents() )
}

#endif
