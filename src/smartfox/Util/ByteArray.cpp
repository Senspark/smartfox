// ===================================================================
//
// Description
//        Contains the implementation of ByteArray
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#if defined(_MSC_VER)
#pragma warning(disable : 4996) // disable warning 4996
#endif

#include "ByteArray.h"

#include <bitset>

namespace Sfs2X {
namespace Util {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ByteArray::ByteArray() {
    buffer = boost::make_shared<std::vector<std::uint8_t>>();
    position = 0;
    compressed = false;
    zLibIsInitialized = false;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ByteArray::ByteArray(const boost::shared_ptr<std::vector<std::uint8_t>>& buf) {
    buffer = buf;
    position = 0;
    compressed = false;
    zLibIsInitialized = false;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ByteArray::~ByteArray() {}

// -------------------------------------------------------------------
// IsLittleEndian
// -------------------------------------------------------------------
bool ByteArray::IsLittleEndian() const {
    short int number = 0x1;
    char* numPtr = (char*)&number;
    return (numPtr[0] == 1);
}

// -------------------------------------------------------------------
// Bytes
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<std ::uint8_t>> ByteArray::Bytes() const {
    return buffer;
}

// -------------------------------------------------------------------
// Bytes
// -------------------------------------------------------------------
void ByteArray::Bytes(
    const boost::shared_ptr<std::vector<std::uint8_t>>& value) {
    buffer = value;
    compressed = false;
}

// -------------------------------------------------------------------
// Length
// -------------------------------------------------------------------
std::size_t ByteArray::Length() const {
    return buffer->size();
}

// -------------------------------------------------------------------
// Position
// -------------------------------------------------------------------
std::size_t ByteArray::Position() const {
    return position;
}

// -------------------------------------------------------------------
// Position
// -------------------------------------------------------------------
void ByteArray::Position(std::size_t value) {
    position = value;
}

// -------------------------------------------------------------------
// BytesAvailable
// -------------------------------------------------------------------
std::size_t ByteArray::BytesAvailable() const {
    if (Length() < Position()) {
        return 0;
    }
    return Length() - Position();
}

// -------------------------------------------------------------------
// BytesAvailable
// -------------------------------------------------------------------
bool ByteArray::Compressed() const {
    return compressed;
}

// -------------------------------------------------------------------
// BytesAvailable
// -------------------------------------------------------------------
void ByteArray::Compressed(bool value) {
    compressed = value;
}

// -------------------------------------------------------------------
// Compress
// -------------------------------------------------------------------
void ByteArray::Compress() {
    if (compressed) {
        boost::throw_exception(boost::enable_error_info(
            std::runtime_error("Buffer is already compressed")));
    }

    // Destination buffer must be at least 0.1% larger than sourceLen plus 12
    // bytes We set destination buffer length to 1% of source + 12 bytes
    auto sizeCompressed = buffer->size() + (buffer->size() / 100) + 12;
    boost::shared_ptr<std::uint8_t> dataCompressed(
        new std::uint8_t[sizeCompressed], array_deleter<std::uint8_t>());
    std::memset(dataCompressed.get(), 0x00, sizeCompressed);

    boost::shared_ptr<std::uint8_t> dataToCompress(
        new std::uint8_t[buffer->size()], array_deleter<std::uint8_t>());
    std::memset(dataToCompress.get(), 0x00, buffer->size());

    std::copy(buffer->begin(), buffer->end(), dataToCompress.get());

    auto sizeCompressed_ = static_cast<uLongf>(sizeCompressed);
    compress(static_cast<Bytef*>(dataCompressed.get()),
             &sizeCompressed_,
             static_cast<const Bytef*>(dataToCompress.get()),
             static_cast<uLong>(buffer->size()));
    sizeCompressed = static_cast<std::size_t>(sizeCompressed_);

    buffer->clear();
    buffer->insert(buffer->end(), &dataCompressed.get()[0],
                   &dataCompressed.get()[sizeCompressed]);

    this->position = 0;
    this->compressed = true;
}

// -------------------------------------------------------------------
// Uncompress
// -------------------------------------------------------------------
void ByteArray::Uncompress() {
    // We set destination buffer length as double of source
    auto sizeAreaUncompressed = buffer->size() * 2;
    std::size_t sizeUncompressed = 0;
    boost::shared_ptr<std::uint8_t> dataUncompressed;

    std::shared_ptr<std::uint8_t> dataToUncompress(
        new std::uint8_t[buffer->size()], array_deleter<std::uint8_t>());
    std::memset(dataToUncompress.get(), 0x00, buffer->size());

    std::copy(buffer->begin(), buffer->end(), dataToUncompress.get());

    // Loop up to destination buffer is large enough to hold the entire
    // uncompressed data
    do {
        dataUncompressed = boost::shared_ptr<std::uint8_t>(
            new std::uint8_t[sizeAreaUncompressed],
            array_deleter<std::uint8_t>());
        std::memset(dataUncompressed.get(), 0x00, sizeAreaUncompressed);

        sizeUncompressed = sizeAreaUncompressed;
        auto sizeUncompressed_ = static_cast<uLongf>(sizeUncompressed);
        int result =
            uncompress(static_cast<Bytef*>(dataUncompressed.get()),
                       &sizeUncompressed_,
                       static_cast<const Bytef*>(dataToUncompress.get()),
                       static_cast<uLong>(buffer->size()));
        sizeUncompressed = static_cast<std::size_t>(sizeUncompressed_);

        if (result == Z_BUF_ERROR) {
            sizeAreaUncompressed += buffer->size();
            continue;
        }

        break;

    } while (true);

    buffer->clear();
    buffer->insert(buffer->end(), &dataUncompressed.get()[0],
                   &dataUncompressed.get()[sizeUncompressed]);

    this->position = 0;
    this->compressed = false;
}

// -------------------------------------------------------------------
// CheckCompressedWrite
// -------------------------------------------------------------------
void ByteArray::CheckCompressedWrite() {
    if (compressed) {
        boost::throw_exception(boost::enable_error_info(
            std::runtime_error("Only raw bytes can be written to a compressed "
                               "array. Call Uncompress first.")));
    }
}

// -------------------------------------------------------------------
// CheckCompressedRead
// -------------------------------------------------------------------
void ByteArray::CheckCompressedRead() {
    if (compressed) {
        boost::throw_exception(boost::enable_error_info(std::runtime_error(
            "Only raw bytes can be read from a compressed array.")));
    }
}

// -------------------------------------------------------------------
// ReverseOrder
// -------------------------------------------------------------------
void ByteArray::ReverseOrder(std::vector<std::uint8_t>& dt) const {
    // if BitCOnverter becomes BigEndian in future MONO/.NET implementations,
    // use this to work correctly
    if (!IsLittleEndian())
        return;

    std::reverse(dt.begin(), dt.end());
}

// -------------------------------------------------------------------
// WriteByte
// -------------------------------------------------------------------
void ByteArray::WriteByte(const boost::shared_ptr<SFSDataType>& tp) {
    WriteByte(static_cast<std::uint8_t>(*tp));
}

// -------------------------------------------------------------------
// WriteByte
// -------------------------------------------------------------------
void ByteArray::WriteByte(std::uint8_t b) {
    auto buf = boost::make_shared<std::vector<std::uint8_t>>();
    buf->push_back(b);
    WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteBytes
// -------------------------------------------------------------------
void ByteArray::WriteBytes(
    const boost::shared_ptr<std::vector<std::uint8_t>>& data) {
    WriteBytes(data, 0, data->size());
}

// -------------------------------------------------------------------
// WriteBytes
// -------------------------------------------------------------------
void ByteArray::WriteBytes(
    const boost::shared_ptr<std::vector<std::uint8_t>>& data, std::size_t ofs,
    std::size_t count) {
    using difference_type = std::make_signed_t<std::size_t>;
    buffer->insert(buffer->end(),
                   data->begin() + static_cast<difference_type>(ofs),
                   data->begin() + static_cast<difference_type>(ofs + count));
}

// -------------------------------------------------------------------
// WriteBool
// -------------------------------------------------------------------
void ByteArray::WriteBool(bool b) {
    CheckCompressedWrite();

    auto buf = boost::make_shared<std::vector<std::uint8_t>>();
    buf->push_back(b ? 1 : 0);
    WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteInt
// -------------------------------------------------------------------
void ByteArray::WriteInt(std::int32_t i) {
    CheckCompressedWrite();

    std::uint8_t bytes[4];
    bytes[0] = (i >> 24) & 0xFF;
    bytes[1] = (i >> 16) & 0xFF;
    bytes[2] = (i >> 8) & 0xFF;
    bytes[3] = i & 0xFF;

    auto buf = boost::make_shared<std::vector<std::uint8_t>>();
    buf->push_back(bytes[0]);
    buf->push_back(bytes[1]);
    buf->push_back(bytes[2]);
    buf->push_back(bytes[3]);
    WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteUShort
// -------------------------------------------------------------------
void ByteArray::WriteUShort(std::uint16_t us) {
    CheckCompressedWrite();

    std::uint8_t bytes[2];
    bytes[0] = (us >> 8) & 0xFF;
    bytes[1] = us & 0xFF;

    auto buf = boost::make_shared<std::vector<std::uint8_t>>();
    buf->push_back(bytes[0]);
    buf->push_back(bytes[1]);
    WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteShort
// -------------------------------------------------------------------
void ByteArray::WriteShort(std::int16_t s) {
    CheckCompressedWrite();

    std::uint8_t bytes[2];
    bytes[0] = (s >> 8) & 0xFF;
    bytes[1] = s & 0xFF;

    auto buf = boost::make_shared<std::vector<std::uint8_t>>();
    buf->push_back(bytes[0]);
    buf->push_back(bytes[1]);
    WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteLong
// -------------------------------------------------------------------
void ByteArray::WriteLong(std::int64_t l) {
    CheckCompressedWrite();

    std::uint8_t bytes[8];
    bytes[0] = (l >> 56) & 0xFF;
    bytes[1] = (l >> 48) & 0xFF;
    bytes[2] = (l >> 40) & 0xFF;
    bytes[3] = (l >> 32) & 0xFF;
    bytes[4] = (l >> 24) & 0xFF;
    bytes[5] = (l >> 16) & 0xFF;
    bytes[6] = (l >> 8) & 0xFF;
    bytes[7] = l & 0xFF;

    auto buf = boost::make_shared<std::vector<std::uint8_t>>();
    buf->push_back(bytes[0]);
    buf->push_back(bytes[1]);
    buf->push_back(bytes[2]);
    buf->push_back(bytes[3]);
    buf->push_back(bytes[4]);
    buf->push_back(bytes[5]);
    buf->push_back(bytes[6]);
    buf->push_back(bytes[7]);
    WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteFloat
// -------------------------------------------------------------------
void ByteArray::WriteFloat(float f) {
    CheckCompressedWrite();

    union {
        float input;
        std::uint32_t output;
    } data;
    data.input = f;

    std::uint8_t bytes[4];
    bytes[0] = (data.output >> 24) & 0xFF;
    bytes[1] = (data.output >> 16) & 0xFF;
    bytes[2] = (data.output >> 8) & 0xFF;
    bytes[3] = data.output & 0xFF;

    auto buf = boost::make_shared<std::vector<std::uint8_t>>();
    buf->push_back(bytes[0]);
    buf->push_back(bytes[1]);
    buf->push_back(bytes[2]);
    buf->push_back(bytes[3]);
    WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteDouble
// -------------------------------------------------------------------
void ByteArray::WriteDouble(double d) {
    CheckCompressedWrite();

    union {
        double input;
        std::uint64_t output;
    } data;

    data.input = d;

    // ???
    // std::bitset<sizeof(double) * CHAR_BIT> bits(data.output);

    std::uint8_t bytes[8];
    bytes[0] = (data.output >> 56) & 0xFF;
    bytes[1] = (data.output >> 48) & 0xFF;
    bytes[2] = (data.output >> 40) & 0xFF;
    bytes[3] = (data.output >> 32) & 0xFF;
    bytes[4] = (data.output >> 24) & 0xFF;
    bytes[5] = (data.output >> 16) & 0xFF;
    bytes[6] = (data.output >> 8) & 0xFF;
    bytes[7] = data.output & 0xFF;

    auto buf = boost::make_shared<std::vector<std::uint8_t>>();
    buf->push_back(bytes[0]);
    buf->push_back(bytes[1]);
    buf->push_back(bytes[2]);
    buf->push_back(bytes[3]);
    buf->push_back(bytes[4]);
    buf->push_back(bytes[5]);
    buf->push_back(bytes[6]);
    buf->push_back(bytes[7]);
    WriteBytes(buf);
}

// -------------------------------------------------------------------
// WriteUTF
// -------------------------------------------------------------------
void ByteArray::WriteUTF(const std::string& str) {
    WriteUTF(boost::make_shared<std::string>(str));
}

void ByteArray::WriteUTF(const boost::shared_ptr<std::string>& str) {
    CheckCompressedWrite();

    // Incoming string must be encoded as UTF8 by API user
    // No additional conversion to UTF8 is required
    /*
    unsigned long int utfLen = 0;
    for (unsigned long int i = 0; i < str->size(); i++)
    {
        unsigned long int c = (*str)[i];
        if ((c >= (unsigned long int)0x0001) && (c <= (unsigned long
    int)0x007F))
        {
            utfLen++;
        }
        else if (c > (unsigned long int)0x07FF)
        {
            utfLen += 3;
        }
        else
        {
            utfLen += 2;
        }
    }


    if (utfLen > 32768)
    {
        boost::throw_exception(boost::enable_error_info
    (std::runtime_error("String length cannot be greater then 32768 !")));
    }


    WriteUShort((unsigned short int)(utfLen));

    boost::shared_ptr<wstring> src (new wstring());
    src->assign(str->begin(), str->end());

    boost::shared_ptr<std::string> dest (new std::string());
    WStrToUtf8(src, dest);

    vector<unsigned char>utfBuffer;

    const char* utfStringArray = dest->c_str();
    for (unsigned long int enumerator = 0; enumerator < dest->size();
    enumerator++)
    {
        utfBuffer.push_back((const unsigned char)(*(utfStringArray +
    enumerator)));
    }

    boost::shared_ptr<std::vector<unsigned char> > data (new vector<unsigned
    char>(utfBuffer)); WriteBytes(data);
    */

    /*
    if (str->size() > 32768)
    {
        boost::throw_exception(boost::enable_error_info
    (std::runtime_error("String length cannot be greater then 32768 !")));
    }


    WriteUShort((unsigned short int)(str->size()));

    vector<unsigned char>utfBuffer;

    const char* utfStringArray = str->c_str();
    for (unsigned long int enumerator = 0; enumerator < str->size();
    enumerator++)
    {
        utfBuffer.push_back((const unsigned char)(*(utfStringArray +
    enumerator)));
    }

    boost::shared_ptr<std::vector<unsigned char> > data (new vector<unsigned
    char>(utfBuffer)); WriteBytes(data);
    */

    std::vector<std::uint8_t> utfBuffer;
    const char* utfStringArray = str->c_str();
    for (std::size_t enumerator = 0; enumerator < str->size(); enumerator++) {
        utfBuffer.push_back(
            static_cast<std::uint8_t>(*(utfStringArray + enumerator)));
    }

    if (utfBuffer.size() > 32767) {
        boost::throw_exception(boost::enable_error_info(std::runtime_error(
            "String length cannot be greater than 32767 bytes!")));
    }

    WriteUShort(static_cast<std::uint16_t>(utfBuffer.size()));
    auto data = boost::make_shared<std::vector<std::uint8_t>>(utfBuffer);
    WriteBytes(data);
}

// -------------------------------------------------------------------
// WriteText
// -------------------------------------------------------------------
void ByteArray::WriteText(const std::string& str) {
    WriteText(boost::make_shared<std::string>(str));
}

void ByteArray::WriteText(const boost::shared_ptr<std::string>& str) {
    CheckCompressedWrite();

    std::vector<std::uint8_t> utfBuffer;
    const char* utfStringArray = str->c_str();
    for (std::size_t enumerator = 0; enumerator < str->size(); enumerator++) {
        utfBuffer.push_back(
            static_cast<std::uint8_t>(*(utfStringArray + enumerator)));
    }

    // SIZE CHECK NOT NEEDED: byte[] length can't be more than Int32.MaxValue

    WriteInt(static_cast<std::int32_t>(utfBuffer.size()));
    auto data = boost::make_shared<std::vector<std::uint8_t>>(utfBuffer);
    WriteBytes(data);
}

// -------------------------------------------------------------------
// ReadByte
// -------------------------------------------------------------------
void ByteArray::ReadByte(std::uint8_t& returnedValue) {
    CheckCompressedRead();
    returnedValue = buffer->at(position++);
    return;
}

// -------------------------------------------------------------------
// ReadBytes
// -------------------------------------------------------------------
void ByteArray::ReadBytes(std::size_t count,
                          std::vector<std::uint8_t>& returnedValue) {
    for (std::size_t enumerator = 0; enumerator < count; enumerator++) {
        returnedValue.push_back(buffer->at(position + enumerator));
    }
    position += count;
    return;
}

// -------------------------------------------------------------------
// ReadBytes
// -------------------------------------------------------------------
void ByteArray::ReadBytes(std::size_t offset, std::size_t count,
                          std::vector<std::uint8_t>& returnedValue) {
    for (std::size_t enumerator = offset; enumerator < count + offset;
         enumerator++) {
        returnedValue.push_back(buffer->at(position + enumerator));
    }
    position += count;
    return;
}

// -------------------------------------------------------------------
// ReadBool
// -------------------------------------------------------------------
void ByteArray::ReadBool(bool& returnedValue) {
    CheckCompressedRead();
    returnedValue = buffer->at(position++) == 1;
    return;
}

// -------------------------------------------------------------------
// ReadInt
// -------------------------------------------------------------------
void ByteArray::ReadInt(std::int32_t& returnedValue) {
    CheckCompressedRead();
    std::vector<std::uint8_t> data;
    ReadBytes(4, data);

    returnedValue = (static_cast<std::int32_t>(data.at(0)) << 24) |
                    (static_cast<std::int32_t>(data.at(1)) << 16) |
                    (static_cast<std::int32_t>(data.at(2)) << 8) |
                    (static_cast<std::int32_t>(data.at(3)));
    return;
}

// -------------------------------------------------------------------
// ReadUShort
// -------------------------------------------------------------------
void ByteArray::ReadUShort(std::uint16_t& returnedValue) {
    CheckCompressedRead();
    std::vector<std::uint8_t> data;
    ReadBytes(2, data);

    returnedValue = (static_cast<std::uint16_t>(data.at(0)) << 8) |
                    (static_cast<std::uint16_t>(data.at(1)));
    return;
}

// -------------------------------------------------------------------
// ReadShort
// -------------------------------------------------------------------
void ByteArray::ReadShort(std::int16_t& returnedValue) {
    CheckCompressedRead();
    std::vector<std::uint8_t> data;
    ReadBytes(2, data);

    returnedValue = (static_cast<std::int16_t>(data.at(0)) << 8) |
                    (static_cast<std::int16_t>(data.at(1)));
    return;
}

// -------------------------------------------------------------------
// ReadLong
// -------------------------------------------------------------------
void ByteArray::ReadLong(std::int64_t& returnedValue) {
    CheckCompressedRead();
    std::vector<std::uint8_t> data;
    ReadBytes(8, data);

    returnedValue = (static_cast<std::int64_t>(data.at(0)) << 56) |
                    (static_cast<std::int64_t>(data.at(1)) << 48) |
                    (static_cast<std::int64_t>(data.at(2)) << 40) |
                    (static_cast<std::int64_t>(data.at(3)) << 32) |
                    (static_cast<std::int64_t>(data.at(4)) << 24) |
                    (static_cast<std::int64_t>(data.at(5)) << 16) |
                    (static_cast<std::int64_t>(data.at(6)) << 8) |
                    (static_cast<std::int64_t>(data.at(7)));
    return;
}

// -------------------------------------------------------------------
// ReadFloat
// -------------------------------------------------------------------
void ByteArray::ReadFloat(float& returnedValue) {
    CheckCompressedRead();
    std::vector<std::uint8_t> data;
    ReadBytes(4, data);

    auto readNumber = (static_cast<std::uint32_t>(data.at(0)) << 24) |
                      (static_cast<std::uint32_t>(data.at(1)) << 16) |
                      (static_cast<std::uint32_t>(data.at(2)) << 8) |
                      (static_cast<std::uint32_t>(data.at(3)));

    //    std::bitset<32> set(readNumber);
    //    long int hexNumber = set.to_ulong();

    //    bool negative = !!(hexNumber & 0x80000000);
    //    long int exponent = (hexNumber & 0x7f800000) >> 23;
    bool negative = !!(readNumber & 0x80000000);
    int exponent = (readNumber & 0x7f800000) >> 23;
    int sign = negative ? -1 : 1;

    // Subtract 127 from the exponent
    exponent -= 127;

    // Convert the mantissa into decimal using the last 23 bits
    int power = -1;
    float total = 0.0f;
    for (int i = 0; i < 23; i++) {
        std::int32_t c = (readNumber & (0x80000000 >> (9 + i))) != 0 ? 1 : 0;
        total += static_cast<float>(c) * std::pow(2.0f, power);
        power--;
    }
    total += 1.0;

    returnedValue = sign * std::pow(2.0f, exponent) * total;
    return;
}

// -------------------------------------------------------------------
// ReadDouble
// -------------------------------------------------------------------
void ByteArray::ReadDouble(double& returnedValue) {
    CheckCompressedRead();
    std::vector<std::uint8_t> data;
    ReadBytes(8, data);

    auto readNumber = (static_cast<std::uint64_t>(data.at(0)) << 56) |
                      (static_cast<std::uint64_t>(data.at(1)) << 48) |
                      (static_cast<std::uint64_t>(data.at(2)) << 40) |
                      (static_cast<std::uint64_t>(data.at(3)) << 32) |
                      (static_cast<std::uint64_t>(data.at(4)) << 24) |
                      (static_cast<std::uint64_t>(data.at(5)) << 16) |
                      (static_cast<std::uint64_t>(data.at(6)) << 8) |
                      (static_cast<std::uint64_t>(data.at(7)));

    //    std::bitset<64> set(readNumber);
    //    unsigned long long hexNumber = set.to_ullong();

    //    bool negative = !!(hexNumber & 0x8000000000000000);
    //    long int exponent = (hexNumber & 0x7ff0000000000000) >> 52;
    bool negative = !!(readNumber & 0x8000000000000000);
    int exponent = (readNumber & 0x7ff0000000000000) >> 52;
    int sign = negative ? -1 : 1;

    // Subtract 1023 from the exponent
    exponent -= 1023;

    // Convert the mantissa into decimal using the last 52 bits
    int power = -1;
    double total = 0.0;
    for (int i = 0; i < 52; i++) {
        std::int64_t c =
            (readNumber & (0x8000000000000000 >> (12 + i))) != 0 ? 1 : 0;
        total += static_cast<double>(c) * std::pow(2.0, power);
        power--;
    }
    total += 1.0;

    returnedValue = sign * std::pow(2.0, exponent) * total;
    return;
}

// -------------------------------------------------------------------
// ReadUTF
// -------------------------------------------------------------------
void ByteArray::ReadUTF(std::string& returnedValue) {
    CheckCompressedRead();

    // Incoming string must be encoded as UTF8 by API user
    // No additional conversion to UTF8 is required
    /*
    unsigned short int size;
    ReadUShort(size);

    boost::shared_ptr<std::string> src (new std::string());

    for (long int enumerator = 0; enumerator < size; enumerator++)
    {
        src->push_back(buffer->at(position + enumerator));
    }

    boost::shared_ptr<wstring> dest (new wstring());
    Utf8toWStr(src, dest);

    returnedValue.assign(dest->begin(), dest->end());
    position += size;
    */
    std::uint16_t size;
    ReadUShort(size);

    auto src = boost::make_shared<std::string>();
    for (std::size_t enumerator = 0;
         enumerator < static_cast<std::size_t>(size); enumerator++) {
        src->push_back(static_cast<char>(buffer->at(position + enumerator)));
    }

    returnedValue.assign(src->begin(), src->end());
    position += static_cast<std::size_t>(size);
}

// -------------------------------------------------------------------
// ReadText
// -------------------------------------------------------------------
void ByteArray::ReadText(std::string& returnedValue) {
    CheckCompressedRead();

    std::int32_t size;
    ReadInt(size);

    auto src = boost::make_shared<std::string>();
    for (std::size_t enumerator = 0;
         enumerator < static_cast<std::size_t>(size); enumerator++) {
        src->push_back(static_cast<char>(buffer->at(position + enumerator)));
    }

    returnedValue.assign(src->begin(), src->end());
    position += static_cast<std::size_t>(size);
}
} // namespace Util
} // namespace Sfs2X
