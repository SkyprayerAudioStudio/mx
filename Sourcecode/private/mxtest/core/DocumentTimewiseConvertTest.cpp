// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mxtest/control/CompileControl.h"
#ifdef MX_COMPILE_CORE_TESTS

#include "cpul/cpulTestHarness.h"
#include "mx/core/Document.h"
#include "mxtest/core/DocumentHeaderTest.h"
#include "DocumentTimewiseCreate.h"
#include "DocumentPartwiseCreate.h"

using namespace mx::core;
using namespace std;
using namespace mxtest;

TEST( DocumentTimewiseConvert, DocumentTimewise )
{
    auto docExpected = mxtest::createDocumentTimewise();
    auto docActual = mxtest::createDocumentPartwise();
    docActual->convertContents();
    stringstream expected;
    docExpected->toStream( expected );
    stringstream actual;
    docActual->toStream( actual );
    CHECK_EQUAL( expected.str(), actual.str() )
}

#endif
