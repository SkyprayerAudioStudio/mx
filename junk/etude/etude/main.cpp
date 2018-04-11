//
//  main.cpp
//  etude
//
//  Created by mjb on 4/9/18.
//  Copyright © 2018 mjb. All rights reserved.
//

#include "util.h"
#include "mx/api/DocumentManager.h"
#include "mx/api/ScoreData.h"
#include <iostream>
#include <map>

int main( int argc, const char * argv[] )
{
    using namespace mx::api;
    using namespace etude;
    
    ScoreData score;
    score.workTitle = "C++ Etude";
    score.composer = "Matthew James Briggs";
    score.parts.emplace_back();
    score.parts.emplace_back();
    PartData& violin = ( score.parts.at( 0 ) );
    PartData& marimba = ( score.parts.at( 1 ) );
    
    violin.uniqueId = "VLN";
    violin.name = "Violin";
    violin.displayName = "Violin";
    violin.instrumentData.name = "Marimba";
    violin.instrumentData.uniqueId = "YVSQNWVWPEVWVWI";
    violin.instrumentData.soundID = SoundID::stringsViolin;
    marimba.uniqueId = "MBA";
    marimba.name = "Marimba";
    marimba.displayName = "Marimba";
    marimba.instrumentData.name = "Marimba";
    marimba.instrumentData.uniqueId = "ERWEVWWVWEVOIWV";
    marimba.instrumentData.soundID = SoundID::pitchedPercussionMarimba;
    
    PartGroupData pgd;
    pgd.displayName = "Marimba";
    pgd.name = "Marimba";
    pgd.bracketType = BracketType::brace;
    pgd.firstPartIndex = 1;
    pgd.lastPartIndex = 1;
    score.partGroups.push_back( pgd );
    
    const int measCount = 16;
    int clock = 0;
    const int tpq = 4 * 4 * 4;
    score.ticksPerQuarter = tpq;
    
    constexpr const auto S = DurationName::dur16th;
    constexpr const auto E = DurationName::eighth;
    constexpr const auto Q = DurationName::quarter;
    constexpr const auto H = DurationName::half;
    constexpr const auto W = DurationName::whole;
    
    std::map<DurationName, int> ticks = {
        { Q, tpq },
        { H, tpq * 2 },
        { W, tpq * 4 },
        { E, tpq / 2 },
        { S, tpq / 4 },
    };
    
    const auto NOTE_PROTO = getNotePrototype( tpq );
    bool isFirstMeasure = true;
    TimeSignatureData ts;
    ts.beats = 4;
    ts.beatType = 4;
    TempoData td;
    td.beatsPerMinute.beatsPerMinute = 126;
    td.tempoType = TempoType::beatsPerMinute;
    td.beatsPerMinute.durationName = DurationName::quarter;
    
    for( int i = 0; i < measCount; ++i )
    {
        auto& mbaMeas = addAndGetMeasure( score, 1 );

        auto& mbaStaff0 = addAndGetStaff( mbaMeas );
        mbaStaff0.voices[0].notes.push_back( NOTE_PROTO );
        
        if( isFirstMeasure )
        {
            mbaMeas.timeSignature = ts;
            ClefData clef;
            clef.setTreble();
            mbaStaff0.clefs.push_back( clef );
        }
        
        auto& mbaStaff1 = addAndGetStaff( mbaMeas );
        auto lowNote = NOTE_PROTO;
        lowNote.pitchData.octave -= 2;
        mbaStaff1.voices[1].notes.push_back( lowNote );
        
        if( isFirstMeasure )
        {
            mbaMeas.timeSignature = ts;
            ClefData clef;
            clef.setBass();
            mbaStaff1.clefs.push_back( clef );
        }
        
        auto& vlnMeas = addAndGetMeasure( score, 0 );
        
        auto& vlnStaff = addAndGetStaff( vlnMeas );
        vlnStaff.voices[0].notes.push_back( NOTE_PROTO );
        
        if( isFirstMeasure )
        {
            vlnMeas.timeSignature = ts;
            ClefData clef;
            clef.setTreble();
            vlnStaff.clefs.push_back( clef );
            DirectionData dir;
            dir.tempos.push_back( td );
            mbaStaff0.directions.push_back( dir );
        }
        
        isFirstMeasure = false;
    }
    
    auto& dmgr = DocumentManager::getInstance();
    const auto docid = dmgr.createFromScore( score );
    dmgr.writeToFile( docid, "./etude.xml" );
    return 0;
}
