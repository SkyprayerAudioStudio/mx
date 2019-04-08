// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once 

#include "mx/api/ScoreData.h"
#include "mxtest/api/ScoreDataCreator.h"
#include "mxtest/file/MxFile.h"
#include "mxtest/file/MxFileTest.h"

namespace mxtest
{
    class ApiTester : public MxFileTest
    {
    public:
        ApiTester(
        	ScoreDataCreatorPtr&& inScoreDataCreator,
        	MxFile inFile,
          	std::string cppFileName,
          	int cppFileLineNumber); 

    virtual void runTestCode() override;
        
    private:
        ScoreDataCreatorPtr myScoreDataCreator;
        std::string myIntermediateFilePath;
        std::string myScrubbedFilePath;
        std::string myExpectedFilePath;
        std::string myFinalFilePath;
        
    private:
        void deleteFiles() const;
    };
}

