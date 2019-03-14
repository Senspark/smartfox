// ===================================================================
//
// Description
//        Contains the definition of ByteArray
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __ByteArray__
#define __ByteArray__

#include "./Common.h"
#include "./StringFormatter.h"

#include "../Entities/Data/SFSDataType.h"
#include "zlib.h" // #include "../ZLib/zlib.h"
#include <boost/container/string.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/all.hpp>

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object
#include <vector> // STL library: vector object

#define ZlibChunk 1024 // Chunk size (bytes) for Zlib buffers

namespace Sfs2X {
namespace Util {

using namespace Sfs2X::Entities::Data;
// -------------------------------------------------------------------
// Class ByteArray
// -------------------------------------------------------------------
class DLLImportExport ByteArray {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    ByteArray();
    explicit ByteArray(const boost::shared_ptr<std::vector<std::uint8_t>>& buf);

    ~ByteArray();

    boost::shared_ptr<std::vector<std::uint8_t>> Bytes() const;
    void Bytes(const boost::shared_ptr<std::vector<std::uint8_t>>& value);

    std::size_t Length() const;
    std::size_t Position() const;
    void Position(std::size_t value);

    std::size_t BytesAvailable() const;

    bool Compressed() const;
    void Compressed(bool value);

    void Compress();
    void Uncompress();
    void CheckCompressedWrite();
    void CheckCompressedRead();

    void ReverseOrder(std::vector<std::uint8_t>& dt) const;

    void WriteByte(const boost::shared_ptr<SFSDataType>& tp);
    void WriteByte(std::uint8_t b);
    void WriteBytes(const boost::shared_ptr<std::vector<std::uint8_t>>& data);
    void WriteBytes(const boost::shared_ptr<std::vector<std::uint8_t>>& data,
                    std::size_t ofs, std::size_t count);
    void WriteBool(bool b);
    void WriteUShort(std::uint16_t us);
    void WriteShort(std::int16_t s);
    void WriteInt(std::int32_t i);
    void WriteLong(std::int64_t l);
    void WriteFloat(float f);
    void WriteDouble(double d);
    void WriteUTF(const boost::shared_ptr<std::string>& str);
    void WriteUTF(const std::string& str);
    void WriteText(const boost::shared_ptr<std::string>& str);
    void WriteText(const std::string& str);

    void ReadByte(std::uint8_t&);
    void ReadBytes(std::size_t count, std::vector<std::uint8_t>&);
    void ReadBytes(std::size_t offset, std::size_t count, std::vector<std::uint8_t>&);
    void ReadBool(bool&);
    void ReadUShort(std::uint16_t&);
    void ReadShort(std::int16_t&);
    void ReadInt(std::int32_t&);
    void ReadLong(std::int64_t&);
    void ReadFloat(float&);
    void ReadDouble(double&);
    void ReadUTF(std::string&);
    void ReadText(std::string&);

    // -------------------------------------------------------------------
    // Public members
    // -------------------------------------------------------------------

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

    bool IsLittleEndian() const;

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------

    boost::shared_ptr<std::vector<std::uint8_t>> buffer;
    std::size_t position;
    bool compressed;

    bool zLibIsInitialized;
    z_stream zlibStrm;
    unsigned char zlibIn[ZlibChunk];
    unsigned char zlibOut[ZlibChunk];
};
} // namespace Util
} // namespace Sfs2X

#endif
