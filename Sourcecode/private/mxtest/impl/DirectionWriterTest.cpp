// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mxtest/control/CompileControl.h"
#ifdef MX_COMPILE_IMPL_TESTS

#include "cpul/cpulTestHarness.h"
#include "mx/impl/DirectionWriter.h"
#include "mx/core/elements/Direction.h"
#include "mx/core/elements/DirectionType.h"
#include "mx/api/OttavaData.h"
#include "mx/core/elements/OctaveShift.h"
#include "mx/core/elements/MusicDataChoice.h"

#include <memory>

using namespace mx;
using namespace mx::impl;

TEST( ottavaStartStop, DirectionWriter )
{
    Cursor cursor{ 1, 100 };
    cursor.isFirstMeasureInPart = false;
    api::DirectionData directionData;
    
    directionData.ottavaStops.emplace_back( api::SpannerStop{} );
    auto& stop = directionData.ottavaStops.back();
    stop.numberLevel = 2;
    
    directionData.ottavaStarts.emplace_back( api::OttavaStart{} );
    auto& start = directionData.ottavaStarts.back();
    start.ottavaType = api::OttavaType::o15mb;
    start.spannerStart.positionData.isDefaultXSpecified = true;
    start.spannerStart.positionData.defaultX = 100.0;
    
    DirectionWriter writer{ directionData, cursor };
    const auto mdcSet = writer.getDirectionLikeThings();
    CHECK( mdcSet.front()->getChoice() == core::MusicDataChoice::Choice::direction );
    const auto direction = mdcSet.front()->getDirection();
    const auto& directionTypes = direction->getDirectionTypeSet();
    
    CHECK_EQUAL( 2, directionTypes.size() );
}
T_END


#endif
