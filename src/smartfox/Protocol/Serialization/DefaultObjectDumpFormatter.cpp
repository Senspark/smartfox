// ===================================================================
//
// Description
//        Contains the implementation of DefaultObjectDumpFormatter
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "DefaultObjectDumpFormatter.h"

namespace Sfs2X {
namespace Protocol {
namespace Serialization {

/*
const char DefaultObjectDumpFormatter::TOKEN_INDENT_OPEN = '{'; //(char) 0x01;
const char DefaultObjectDumpFormatter::TOKEN_INDENT_CLOSE = '}'; //(char) 0x02;
const char DefaultObjectDumpFormatter::TOKEN_DIVIDER = ';'; //(char) 0x03;
const char DefaultObjectDumpFormatter::NEW_LINE = '\n';
const char DefaultObjectDumpFormatter::TAB = '\t';
const char DefaultObjectDumpFormatter::DOT = '.';
*/

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
DefaultObjectDumpFormatter::~DefaultObjectDumpFormatter() {}

// -------------------------------------------------------------------
// PrettyPrintDump
// -------------------------------------------------------------------
boost::shared_ptr<std::string> DefaultObjectDumpFormatter::PrettyPrintDump(
    const boost::shared_ptr<std::string>& rawDump) {
    boost::shared_ptr<std::string> strBuf(new std::string());

    long int indentPos = 0;
    for (unsigned int i = 0; i < rawDump->size(); i++) {
        char ch = rawDump->at(i);

        if (ch == TOKEN_INDENT_OPEN) {
            indentPos++;
            strBuf->append(NEW_LINE + (*GetFormatTabs(indentPos)));
        } else if (ch == TOKEN_INDENT_CLOSE) {
            indentPos--;
            if (indentPos < 0) {
                boost::shared_ptr<std::string> message(
                    new std::string("DumpFormatter: the indentPos is negative. "
                                    "TOKENS ARE NOT BALANCED!"));
                boost::shared_ptr<SFSError> exception(new SFSError(message));
                throw exception;
            }

            strBuf->append(NEW_LINE + (*(GetFormatTabs(indentPos))));
        } else if (ch == TOKEN_DIVIDER) {
            strBuf->append(NEW_LINE + (*(GetFormatTabs(indentPos))));
        } else {
            strBuf->append(StringFormatter("%c", ch));
        }
    }

    if (indentPos != 0) {
        boost::shared_ptr<std::string> message(new std::string(
            "DumpFormatter: the indentPos is not == 0. TOKENS ARE "
            "NOT BALANCED!"));
        boost::shared_ptr<SFSError> exception(new SFSError(message));
        throw exception;
    }

    return strBuf;
}

// -------------------------------------------------------------------
// GetFormatTabs
// -------------------------------------------------------------------
boost::shared_ptr<std::string>
DefaultObjectDumpFormatter::GetFormatTabs(long int howMany) {
    return StrFill(TAB, howMany);
}

// -------------------------------------------------------------------
// StrFill
// -------------------------------------------------------------------
boost::shared_ptr<std::string>
DefaultObjectDumpFormatter::StrFill(char ch, long int howMany) {
    boost::shared_ptr<std::string> strBuf(new std::string());
    for (int i = 0; i < howMany; i++) {
        strBuf->append(StringFormatter("%c", ch));
    }
    return strBuf;
}

// -------------------------------------------------------------------
// HexDump
// -------------------------------------------------------------------
boost::shared_ptr<std::string>
DefaultObjectDumpFormatter::HexDump(boost::shared_ptr<ByteArray> ba) {
    return HexDump(ba, HEX_BYTES_PER_LINE);
}

// -------------------------------------------------------------------
// HexDump
// -------------------------------------------------------------------
boost::shared_ptr<std::string>
DefaultObjectDumpFormatter::HexDump(boost::shared_ptr<ByteArray> ba,
                                    long int bytesPerLine) {
    boost::shared_ptr<std::string> sb(new std::string());
    sb->append(StringFormatter("Binary Size: %d%c", ba->Length(), NEW_LINE));
    if (ba->Length() > MAX_DUMP_LENGTH) {
        sb->append(StringFormatter(
            "** Data larger than max dump size of %d. Data not displayed",
            MAX_DUMP_LENGTH));
        return sb;
    }

    std::string hexLine;
    std::string chrLine;

    long int index = 0;
    long int count = 0;
    char currChar;
    unsigned char currByte;

    do {
        boost::shared_ptr<std::vector<unsigned char>> vectorBaBytes =
            ba->Bytes();
        currByte = vectorBaBytes->at(index);
        std::string hexByte(StringFormatter("%02x", currByte));

        if (hexByte.size() == 1) {
            hexByte = "0" + hexByte;
        }

        hexLine.append(hexByte);
        hexLine.append(" ");

        if (currByte >= 33 && currByte <= 126) {
            currChar = (unsigned char)(currByte);
        } else {
            currChar = DOT;
        }

        chrLine.append(StringFormatter("%c", currChar));
        if (++count == bytesPerLine) {
            count = 0;
            sb->append(hexLine);

            sb->append(StringFormatter("%c", TAB));
            sb->append(chrLine);
            sb->append(StringFormatter("%c", NEW_LINE));

            hexLine.clear();
            chrLine.clear();
        }
    } while (++index < ba->Length());

    // Add last incomplete line
    if (count != 0) {
        for (int j = bytesPerLine - count; j > 0; j--) {
            hexLine.append("   ");
            chrLine.append(" ");
        }

        sb->append(hexLine);
        sb->append(StringFormatter("%c", TAB));
        sb->append(chrLine);
        sb->append(StringFormatter("%c", NEW_LINE));
    }
    return sb;
}
} // namespace Serialization
} // namespace Protocol
} // namespace Sfs2X
