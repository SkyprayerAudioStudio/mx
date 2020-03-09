// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mxtest/control/CompileControl.h"
#ifdef MX_COMPILE_CORE_TESTS

#include "cpul/cpulTestHarness.h"
#include "mx/core/Elements.h"
#include <sstream>

using namespace mx::core;

TEST( Test01, Tie )
{
	std::string indentString( INDENT );
	Tie object1;
	Tie object2;
	TieAttributesPtr attributes1 = std::make_shared<TieAttributes>();
	TieAttributesPtr attributesNull;
	/* set some attribute1 values here */
    attributes1->hasTimeOnly = true;
    attributes1->timeOnly = TimeOnly{ "1,4,6" };
    attributes1->type = StartStop::stop;
	object2.setAttributes( attributes1 );
	object2.setAttributes( attributesNull ); /* should have no affect */
	std::stringstream default_constructed;
	object1.toStream( default_constructed, 0 );
	std::stringstream object2_stream;
	object2.toStream( object2_stream, 2 );
	std::string expected = R"(<tie type="start"/>)";
	std::string actual = default_constructed.str();
	CHECK_EQUAL( expected, actual )
	expected = indentString+indentString+R"(<tie type="stop" time-only="1,4,6"/>)";
	actual = object2_stream.str();
	CHECK_EQUAL( expected, actual )
	std::stringstream o1;	std::stringstream o2;	bool isOneLineOnly = false;
	object1.streamContents( o1, 0, isOneLineOnly );
	object2.streamContents( o2, 0, isOneLineOnly );
	CHECK( isOneLineOnly )
	CHECK_EQUAL( o1.str(), o2.str() )
	CHECK( !object1.hasContents() )
	CHECK( object1.hasAttributes() )
	CHECK( object2.hasAttributes() )
}

#endif
