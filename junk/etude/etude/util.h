#pragma once

#include "mx/api/ScoreData.h"

namespace etude
{
    inline mx::api::MeasureData& getMeasure( mx::api::ScoreData& score, int partIndex, int measureIndex )
    {
        auto& part = *( score.parts.begin() + static_cast<size_t>( partIndex ) );
        auto& measure = *( part.measures.begin() + static_cast<size_t>( measureIndex ) );
        return measure;
    }
    
    
    inline mx::api::StaffData& getStaff( mx::api::ScoreData& score, int partIndex, int measureIndex, int staffIndex )
    {
        auto& measure = getMeasure( score, partIndex, measureIndex );
        return *( measure.staves.begin() + static_cast<size_t>( staffIndex ) );
    }
    
    
    inline mx::api::VoiceData& getVoice( mx::api::ScoreData& score, int partIndex, int measureIndex, int staffIndex, int voiceIndex )
    {
        auto& staff = getStaff( score, partIndex, measureIndex, staffIndex );
        
        if( staff.voices.find( voiceIndex ) == staff.voices.end() )
        {
            staff.voices.emplace( voiceIndex, mx::api::VoiceData{} );
        }
        
        auto& voice = ( staff.voices.find( voiceIndex ) )->second;
        return voice;
    }
    
    inline mx::api::MeasureData& addAndGetMeasure( mx::api::ScoreData& score, int partIndex )
    {
        mx::api::PartData& part = score.parts.at( static_cast<size_t>( partIndex) );
        part.measures.emplace_back();
        mx::api::MeasureData& measure = *( part.measures.rbegin() );
        return measure;
    }
    
    inline mx::api::StaffData& addAndGetStaff( mx::api::MeasureData& ioMeasure )
    {
        ioMeasure.staves.emplace_back();
        auto& staff = *( ioMeasure.staves.rbegin() );
        return staff;
    }
    
    
    inline mx::api::NoteData getNotePrototype( int ticksPerQuarter )
    {
        mx::api::NoteData n;
        n.durationData.durationName = mx::api::DurationName::whole;
        n.durationData.durationTimeTicks = ticksPerQuarter * 4;
        n.pitchData.step = mx::api::Step::b;
        n.pitchData.octave = 4;
        n.pitchData.alter = -1;
        return n;
    }
}
