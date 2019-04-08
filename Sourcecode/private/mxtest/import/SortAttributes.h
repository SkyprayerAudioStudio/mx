// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include "mx/xml/XDoc.h"
#include "mx/xml/XElement.h"
#include "mx/xml/XAttribute.h"
#include "mx/xml/XElementIterator.h"
#include "mx/xml/XAttributeIterator.h"

#include <map>
#include <string>

namespace mxtest
{
    
    using StringMap = std::map<std::string, std::string>;
    
    // unfortunately xml does not care about the order of attributes
    // so both the expected and actual files will need to have their
    // attributes sorted into alphabetical order so that they match.
    
    void sortAttributes( mx::xml::XDoc& xdoc );
    void sortAttributes ( mx::xml::XElement& xelement );
    void deleteFirstAttribute( mx::xml::XElement& xelement );
}
