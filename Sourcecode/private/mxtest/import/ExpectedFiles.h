// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mxtest/control/CompileControl.h"
#ifdef MX_COMPILE_IMPORT_TESTS

#include "mxtest/file/Path.h"
#include "mxtest/file/StupidFileFunctions.h"
#include "mxtest/file/MxFileRepository.h"
#include "mx/utility/Parse.h"
#include "mx/xml/XFactory.h"
#include "mx/xml/XDoc.h"
#include "mx/xml/XAttributeIterator.h"

#include <map>
#include <cstdio>

namespace mxtest
{
    
    void generateExpectedFile( const std::string& subdir, const std::string& fileName );
    
    mx::xml::XDocPtr readInputFile( const std::string& subdir, const std::string& fileName );
    
    void setXmlDeclaration( mx::xml::XDocPtr& xdoc );
    
    bool getIsScorePartwise( const mx::xml::XDocPtr& xdoc );
    
    void setDoctype( mx::xml::XDocPtr& xdoc, bool isScorePartwise );
    
    void setRootMusicXmlVersion( mx::xml::XDocPtr& xdoc, bool isScorePartwsise );
    
    std::string getExpectedFileName( const std::string& subdir, const std::string& fileName );
    
    std::string getExpectedFileFullPath( const std::string& subdir, const std::string& fileName );

    void deleteExpectedFiles();
    
    void generateExpectedFiles();
    
    std::string gettestOutputErrorFileName( const std::string& subdir, const std::string& fileName );
    
    std::string getTestOutputErrorFileFullPath( const std::string& subdir, const std::string& fileName );
    
    std::string getTestOutputExpectedFileName( const std::string& subdir, const std::string& fileName );

    std::string getTestOutputExpectedFileFullPath( const std::string& subdir, const std::string& fileName );

    void deleteTestOutputFiles();
}

#endif
