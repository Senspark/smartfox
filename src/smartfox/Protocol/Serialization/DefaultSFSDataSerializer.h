// ===================================================================
//
// Description
//        Contains the definition of DefaultSFSDataSerializer
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __DefaultSFSDataSerializer__
#define __DefaultSFSDataSerializer__

#include "ISFSDataSerializer.h"
#include "../../Entities/Data/ISFSObject.h"
#include "../../Entities/Data/ISFSArray.h"
#include "../../Entities/Data/SFSObject.h"
#include "../../Entities/Data/SFSArray.h"
#include "../../Entities/Data/SFSDataType.h"
#include "../../Util/ByteArray.h"
#include "../../Exceptions/SFSCodecError.h"
#include "../../Util/StringFormatter.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object
#include <vector> // STL library: vector object
#include <map>    // STL library: map object

namespace Sfs2X {
namespace Protocol {
namespace Serialization {

using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Util;
using namespace Sfs2X::Exceptions;

// -------------------------------------------------------------------
// Class DefaultSFSDataSerializer
// -------------------------------------------------------------------
class DefaultSFSDataSerializer : public ISFSDataSerializer {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    static boost::shared_ptr<DefaultSFSDataSerializer> Instance();

    DefaultSFSDataSerializer();
    virtual ~DefaultSFSDataSerializer() override;

    // SFSObject ==> Binary

    virtual boost::shared_ptr<ByteArray>
    Object2Binary(const boost::shared_ptr<ISFSObject>& obj) const override;

    // SFSArray ==> Binary

    virtual boost::shared_ptr<ByteArray>
    Array2Binary(const boost::shared_ptr<ISFSArray>& arrayobj) const override;

    // Binary ==> SFSObject

    virtual boost::shared_ptr<ISFSObject>
    Binary2Object(const boost::shared_ptr<ByteArray>& data) const override;

    // Binary ==> SFSArray

    virtual boost::shared_ptr<ISFSArray>
    Binary2Array(const boost::shared_ptr<ByteArray>& data) const override;

    // -------------------------------------------------------------------
    // Public members
    // -------------------------------------------------------------------

    static boost::shared_ptr<std::string> CLASS_MARKER_KEY;
    static boost::shared_ptr<std::string> CLASS_FIELDS_KEY;
    static boost::shared_ptr<std::string> FIELD_NAME_KEY;
    static boost::shared_ptr<std::string> FIELD_VALUE_KEY;

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

    boost::shared_ptr<ByteArray>
    Obj2bin(const boost::shared_ptr<ISFSObject>& obj,
            const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<ByteArray>
    Arr2bin(const boost::shared_ptr<ISFSArray>& arrayobj,
            const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<ISFSObject>
    DecodeSFSObject(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<ISFSArray>
    DecodeSFSArray(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<ByteArray>
    EncodeObject(const boost::shared_ptr<ByteArray>& buffer, int typeId,
                 const boost::shared_ptr<void>& data) const;

    /*
     * The buffer pointer (position) must located on the 1st byte of the object
     * to decode Throws SFSCodecException
     */
    boost::shared_ptr<SFSDataWrapper>
    DecodeObject(const boost::shared_ptr<ByteArray>& buffer) const;

    // Binary Entities Decoding Methods

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_NULL(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_BOOL(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_BYTE(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_SHORT(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_INT(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_LONG(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_FLOAT(const boost::shared_ptr<ByteArray>& buffer) const;
    
    boost::shared_ptr<SFSDataWrapper>
    BinDecode_DOUBLE(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_UTF_STRING(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_TEXT(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_BOOL_ARRAY(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_BYTE_ARRAY(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_SHORT_ARRAY(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_INT_ARRAY(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_LONG_ARRAY(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_FLOAT_ARRAY(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper>
    BinDecode_DOUBLE_ARRAY(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<SFSDataWrapper> BinDecode_UTF_STRING_ARRAY(
        const boost::shared_ptr<ByteArray>& buffer) const;

    std::int32_t
    GetTypedArraySize(const boost::shared_ptr<ByteArray>& buffer) const;

    // Binary Entities Encoding Methods

    boost::shared_ptr<ByteArray>
    BinEncode_NULL(const boost::shared_ptr<ByteArray>& buffer) const;

    boost::shared_ptr<ByteArray>
    BinEncode_BOOL(const boost::shared_ptr<ByteArray>& buffer,
                   const boost::shared_ptr<bool>& val) const;

    boost::shared_ptr<ByteArray>
    BinEncode_BYTE(const boost::shared_ptr<ByteArray>& buffer,
                   const boost::shared_ptr<std::uint8_t>& val) const;

    boost::shared_ptr<ByteArray>
    BinEncode_SHORT(const boost::shared_ptr<ByteArray>& buffer,
                    const boost::shared_ptr<std::int16_t>& val) const;

    boost::shared_ptr<ByteArray>
    BinEncode_INT(const boost::shared_ptr<ByteArray>& buffer,
                  const boost::shared_ptr<std::int32_t>& val) const;

    boost::shared_ptr<ByteArray>
    BinEncode_LONG(const boost::shared_ptr<ByteArray>& buffer,
                   const boost::shared_ptr<std::int64_t>& val) const;

    boost::shared_ptr<ByteArray>
    BinEncode_FLOAT(const boost::shared_ptr<ByteArray>& buffer,
                    const boost::shared_ptr<float>& val) const;

    boost::shared_ptr<ByteArray>
    BinEncode_DOUBLE(const boost::shared_ptr<ByteArray>& buffer,
                     const boost::shared_ptr<double>& val) const;

    boost::shared_ptr<ByteArray>
    BinEncode_INT(const boost::shared_ptr<ByteArray>& buffer,
                  const boost::shared_ptr<double>& val) const;

    boost::shared_ptr<ByteArray>
    BinEncode_UTF_STRING(const boost::shared_ptr<ByteArray>& buffer,
                         const boost::shared_ptr<std::string>& val) const;

    boost::shared_ptr<ByteArray>
    BinEncode_TEXT(const boost::shared_ptr<ByteArray>& buffer,
                   const boost::shared_ptr<std::string>& val) const;

    boost::shared_ptr<ByteArray>
    BinEncode_BOOL_ARRAY(const boost::shared_ptr<ByteArray>& buffer,
                         const boost::shared_ptr<std::vector<bool>>& val) const;

    boost::shared_ptr<ByteArray>
    BinEncode_BYTE_ARRAY(const boost::shared_ptr<ByteArray>& buffer,
                         const boost::shared_ptr<ByteArray>& val) const;

    boost::shared_ptr<ByteArray> BinEncode_SHORT_ARRAY(
        const boost::shared_ptr<ByteArray>& buffer,
        const boost::shared_ptr<std::vector<std::int16_t>>& val) const;

    boost::shared_ptr<ByteArray> BinEncode_INT_ARRAY(
        const boost::shared_ptr<ByteArray>& buffer,
        const boost::shared_ptr<std::vector<boost::int32_t>>& val) const;

    boost::shared_ptr<ByteArray> BinEncode_LONG_ARRAY(
        const boost::shared_ptr<ByteArray>& buffer,
        const boost::shared_ptr<std::vector<std::int64_t>>& val) const;

    boost::shared_ptr<ByteArray> BinEncode_FLOAT_ARRAY(
        const boost::shared_ptr<ByteArray>& buffer,
        const boost::shared_ptr<std::vector<float>>& val) const;

    boost::shared_ptr<ByteArray> BinEncode_DOUBLE_ARRAY(
        const boost::shared_ptr<ByteArray>& buffer,
        const boost::shared_ptr<std::vector<double>>& val) const;

    boost::shared_ptr<ByteArray> BinEncode_UTF_STRING_ARRAY(
        const boost::shared_ptr<ByteArray>& buffer,
        const boost::shared_ptr<std::vector<std::string>>& val) const;

    boost::shared_ptr<ByteArray>
    EncodeSFSObjectKey(const boost::shared_ptr<ByteArray>& buffer,
                       const boost::shared_ptr<std::string>& val) const;

    /*
     * Returns the same buffer
     * (could be used also to create copies)
     */
    boost::shared_ptr<ByteArray>
    AddData(const boost::shared_ptr<ByteArray>& buffer,
            const boost::shared_ptr<ByteArray>& newData) const;

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------

    static boost::shared_ptr<DefaultSFSDataSerializer> instance;
};
} // namespace Serialization
} // namespace Protocol
} // namespace Sfs2X

#endif
