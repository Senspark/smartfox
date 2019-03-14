// ===================================================================
//
// Description
//        Contains the definition of DefaultObjectDumpFormatter
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __DefaultObjectDumpFormatter__
#define __DefaultObjectDumpFormatter__

#include "smartfox/Exceptions/SFSError.h"
#include "smartfox/Util/ByteArray.h"
#include "smartfox/Util/StringFormatter.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object

namespace Sfs2X {
using namespace Util;
using namespace Exceptions;

namespace Protocol {
namespace Serialization {
// -------------------------------------------------------------------
// Class DefaultObjectDumpFormatter
// -------------------------------------------------------------------
class DefaultObjectDumpFormatter {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------
    virtual ~DefaultObjectDumpFormatter();

    static boost::shared_ptr<std::string>
    PrettyPrintDump(const boost::shared_ptr<std::string>& rawDump);
    static boost::shared_ptr<std::string>
    HexDump(boost::shared_ptr<ByteArray> ba);
    static boost::shared_ptr<std::string>
    HexDump(boost::shared_ptr<ByteArray> ba, long int bytesPerLine);

    // -------------------------------------------------------------------
    // Public members
    // -------------------------------------------------------------------

    static constexpr char TOKEN_INDENT_OPEN = '{';  //(char) 0x01;
    static constexpr char TOKEN_INDENT_CLOSE = '}'; //(char) 0x02;
    static constexpr char TOKEN_DIVIDER = ';';      //(char) 0x03;
    static constexpr char NEW_LINE = '\n';
    static constexpr char TAB = '\t';
    static constexpr char DOT = '.';

    static constexpr int HEX_BYTES_PER_LINE = 16;
    static constexpr int MAX_DUMP_LENGTH = 1024;

protected:
    // -------------------------------------------------------------------
    // Protected methods
    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    // Protected members
    // -------------------------------------------------------------------

private:
    // -------------------------------------------------------------------
    // Private methods
    // -------------------------------------------------------------------

    static boost::shared_ptr<std::string> GetFormatTabs(long int howMany);
    static boost::shared_ptr<std::string> StrFill(char ch, long int howMany);

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------
};
} // namespace Serialization
} // namespace Protocol
} // namespace Sfs2X

#endif
