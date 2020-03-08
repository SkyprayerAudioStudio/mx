// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mx/core/ElementInterface.h"
#include "ezxml/XElement.h"
#include "ezxml/XElementIterator.h"
#include "ezxml/XFactory.h"
#include <sstream>
#include "mx/utility/Throw.h"

namespace mx
{
    namespace core
    {
        const char* INDENT = "   ";
 
        ElementInterface::ElementInterface()
        {

        }

        
        ElementInterface::~ElementInterface()
        {
            std::cout << "ElementInterface::~ElementInterface()" << std::endl;
        }
        
        
        std::ostream& ElementInterface::streamOpenTag( std::ostream& os ) const
        {
            os << "<";
            this->streamName( os );
            if ( hasAttributes() )
            {
                streamAttributes( os );
            }
            os << ">";
            return os;
        }


        std::ostream& ElementInterface::streamCloseTag( std::ostream& os ) const
        {
            os << "</";
            this->streamName( os );
            os << ">";
            return os;
        }


        std::ostream& ElementInterface::streamSelfCloseTag( std::ostream& os ) const
        {
            os << "<";
            this->streamName( os );
            if ( hasAttributes() )
            {
                streamAttributes( os );
            }
            os << "/>";
            return os;
        }
        bool ElementInterface::hasContents() const
        {
            std::stringstream ss;
            bool discard;
            streamContents( ss, 0, discard );
            return ( ss.str() ).length() > 0;
        }


        std::ostream& ElementInterface::toStream( std::ostream& os, const int indentLevel ) const
        {
            indent( os, indentLevel );

            if( myProcessingInstructions.empty() )
            {
                return streamWithoutProcessingInstructions( os, indentLevel );
            }
            else
            {
                std::stringstream ss;
                streamWithoutProcessingInstructions( ss, 0 );
                const auto xml = ss.str();
                std::istringstream iss{ xml };
                const auto xdoc = ::ezxml::XFactory::makeXDoc();
                xdoc->loadStream( iss );
                const auto root = xdoc->getRoot();
                const bool hasChildren = root->getType() == ::ezxml::XElementType::element && root->begin() != root->end();
                streamWithProcessingInstructions( os, indentLevel, hasChildren );
            }

            return os;
        }
        
        
        const std::string ElementInterface::getElementName() const
        {
            std::stringstream ss;
            this->streamName( ss );
            return ss.str();
        }


        std::ostream& indent( std::ostream& os, const int indentLevel )
        {
            for ( int i = 0; i < indentLevel; ++i )
            {
                os << INDENT;
            }
            return os;
        }
        
        
        bool ElementInterface::hasAttributes() const
        {
            return false;
        }


        bool ElementInterface::fromXElement( std::ostream& message, ::ezxml::XElement& xelement )
        {
            if( xelement.getIsProcessingInstruction() )
            {
                const auto next = xelement.getNextSibling();

                if( next )
                {
                    return this->fromXElement( message, *next );
                }
            }
            
            const bool result = this->fromXElementImpl( message, xelement );

            // check for processing instructions

            if( xelement.getType() == ezxml::XElementType::element )
            {
                MX_LOG("trace");
                auto childIter = xelement.beginWithProcessingInstructions();

                MX_LOG("trace"); 
                const auto childEnd = xelement.end();

                while( childIter != childEnd && childIter->getIsProcessingInstruction() )
                {
                    auto n = childIter->getName();
                    auto v = childIter->getValue();
                    MX_LOG("trace");
                    ProcessingInstruction pi{ n, v };
                    

                    MX_LOG("trace"); 
                    pi.setIsChild( true );
                    

                    MX_LOG("trace"); 
                    addProcessingInstruction( std::move( pi ) );
                    

                    MX_LOG("trace"); 
                    ++childIter;
                }
            }


            MX_LOG("trace"); 
            auto lookahead = xelement.getNextSibling();

            while( lookahead != nullptr && lookahead->getIsProcessingInstruction() )
            {

                MX_LOG("trace");
                ProcessingInstruction pi{ lookahead->getName(), lookahead->getValue() };
                

                MX_LOG("trace"); 
                pi.setIsChild( false );
                

                MX_LOG("trace"); 
                addProcessingInstruction( std::move( pi ) );
                

                MX_LOG("trace"); 
                lookahead = lookahead->getNextSibling();
            }

            return result;
        }


        const ProcessingInstructions& ElementInterface::getProcessingInstructions() const
        {
            return myProcessingInstructions;
        }


        void ElementInterface::clearProcessingInstructions()
        {
            myProcessingInstructions.clear();
        }


        void ElementInterface::addProcessingInstruction( ProcessingInstruction inProcessingInstruction )
        {
            myProcessingInstructions.emplace_back( std::move( inProcessingInstruction ) );
        }


        std::ostream& operator<<( std::ostream& os, const ElementInterface& value )
        {
            return value.toStream( os, 0 );
        }


        std::ostream& ElementInterface::writeChildProcessingInstructions( std::ostream& os, const int indentLevel ) const
        {
            bool isFirst = true;

            for( const auto& pi : myProcessingInstructions )
            {
                if( pi.getIsChild() )
                {
                    if (!isFirst)
                    {
                        os << std::endl;
                    }
                    indent( os, indentLevel + 1 );
                    pi.toStream( os );
                    isFirst = false;
                }
            }

            return os;
        }


        std::ostream& ElementInterface::writeSiblingProcessingInstructions( std::ostream& os, const int indentLevel ) const
        {
            bool isFirst = true;

            for( const auto& pi : myProcessingInstructions )
            {
                if( !pi.getIsChild() )
                {
                    if (!isFirst)
                    {
                        os << std::endl;
                    }
                    indent( os, indentLevel );
                    pi.toStream( os );
                    isFirst = false;
                }
            }

            return os;
        }


        std::ostream& ElementInterface::writeAllProcessingInstructions( std::ostream& os, const int indentLevel ) const
        {
            bool isFirst = true;

            for( const auto& pi : myProcessingInstructions )
            {
                if (!isFirst)
                {
                    os << std::endl;
                }
                indent( os, indentLevel );
                pi.toStream( os );
                isFirst = false;
            }

            return os;
        }


        std::ostream& ElementInterface::streamWithoutProcessingInstructions( std::ostream& os, const int indentLevel ) const
        {
            const bool isSelfClosing = !hasContents();

            if ( !isSelfClosing )
            {
                streamOpenTag( os );
                bool isOneLineOnly = false;
                streamContents( os, indentLevel, isOneLineOnly );
                if ( !isOneLineOnly )
                {
                    indent( os, indentLevel );
                }
                streamCloseTag( os );
            }
            else
            {
                streamSelfCloseTag( os );
            }
            return os;
        }


        std::ostream& ElementInterface::streamWithProcessingInstructions( std::ostream& os, const int indentLevel, const bool inHasChildren ) const
        {
            const bool isSelfClosing = !hasContents();

            if ( !isSelfClosing )
            {
                streamOpenTag( os );
                bool isOneLineOnly = false;

                if( inHasChildren )
                {
                    writeChildProcessingInstructions( os, indentLevel );
                }

                streamContents( os, indentLevel, isOneLineOnly );

                if ( !isOneLineOnly )
                {
                    indent( os, indentLevel );
                }
                streamCloseTag( os );

                if( inHasChildren )
                {
                    os << std::endl;
                    writeSiblingProcessingInstructions( os, indentLevel );
                }
                else
                {
                    os << std::endl;
                    writeAllProcessingInstructions( os, indentLevel );
                }
            }
            else
            {
                streamSelfCloseTag( os );
                os << std::endl;
                writeAllProcessingInstructions( os, indentLevel );
            }
            return os;
        }
    }
}
