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
#include "DefaultSFSDataSerializer.h"

#include <boost/make_shared.hpp>

namespace Sfs2X {
namespace Protocol {
namespace Serialization {
using Self = DefaultSFSDataSerializer;

boost::shared_ptr<std::string> Self::CLASS_MARKER_KEY(new std::string("$C"));
boost::shared_ptr<std::string> Self::CLASS_FIELDS_KEY(new std::string("$F"));
boost::shared_ptr<std::string> Self::FIELD_NAME_KEY(new std::string("N"));
boost::shared_ptr<std::string> Self::FIELD_VALUE_KEY(new std::string("V"));

boost::shared_ptr<Self> Self::instance = boost::shared_ptr<Self>();

// -------------------------------------------------------------------
// Instance
// -------------------------------------------------------------------
boost::shared_ptr<Self> Self::Instance() {
    if (instance == NULL) {
        instance = boost::make_shared<Self>();
    }
    return instance;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::DefaultSFSDataSerializer() {}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
Self::~DefaultSFSDataSerializer() {}

// SFSObject ==> Binary

// -------------------------------------------------------------------
// Object2Binary
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray>
Self::Object2Binary(const boost::shared_ptr<ISFSObject>& obj) const {
    auto buffer = boost::make_shared<ByteArray>();
    buffer->WriteByte(static_cast<std::uint8_t>(SFSDATATYPE_SFS_OBJECT));
    buffer->WriteShort(static_cast<std::int8_t>(obj->Size()));
    return Obj2bin(obj, buffer);
}

boost::shared_ptr<ByteArray>
Self::Obj2bin(const boost::shared_ptr<ISFSObject>& obj,
              const boost::shared_ptr<ByteArray>& buffer) const {
    auto keys = obj->GetKeys();
    auto result = buffer;
    for (auto&& key : *keys) {
        auto wrapper = obj->GetData(key);

        // Store the key
        result =
            EncodeSFSObjectKey(buffer, boost::make_shared<std::string>(key));

        // Convert 2 binary
        result = EncodeObject(buffer, wrapper->Type(), wrapper->Data());
    }
    return result;
}

// SFSArray ==> Binary
boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::Array2Binary(
    const boost::shared_ptr<ISFSArray>& arrayobj) const {
    boost::shared_ptr<ByteArray> buffer(new ByteArray());
    buffer->WriteByte((unsigned char)SFSDATATYPE_SFS_ARRAY);
    buffer->WriteShort((short)arrayobj->Size());
    return Arr2bin(arrayobj, buffer);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::Arr2bin(
    const boost::shared_ptr<ISFSArray>& arrayobj,
    const boost::shared_ptr<ByteArray>& buffer) const {
    auto result = buffer;
    boost::shared_ptr<SFSDataWrapper> wrapper;
    for (std::size_t i = 0; i < arrayobj->Size(); i++) {
        wrapper = arrayobj->GetWrappedElementAt(i);
        result = EncodeObject(buffer, wrapper->Type(), wrapper->Data());
    }
    return result;
}

// Binary ==> SFSObject

boost::shared_ptr<ISFSObject> DefaultSFSDataSerializer::Binary2Object(
    const boost::shared_ptr<ByteArray>& data) const {
    if (data->Length() < 3) {
        auto err = StringFormatter("Can't decode an SFSObject. Byte data is "
                                   "insufficient. Size: %d byte(s)",
                                   data->Length());
        auto exception = boost::make_shared<SFSCodecError>(
            boost::make_shared<std::string>(err));
        throw exception;
    }

    data->Position(0);
    return DecodeSFSObject(data);
}

boost::shared_ptr<ISFSObject> DefaultSFSDataSerializer::DecodeSFSObject(
    const boost::shared_ptr<ByteArray>& buffer) const {
    boost::shared_ptr<SFSObject> sfsObject(SFSObject::NewInstance());

    // Get tpyeId
    unsigned char headerByte;
    buffer->ReadByte(headerByte);

    // Validate typeId
    if (headerByte != (unsigned char)SFSDATATYPE_SFS_OBJECT) {
        auto err = StringFormatter(
            "Invalid SFSDataType. Expected: %d, found: %d",
            static_cast<int>(SFSDATATYPE_SFS_OBJECT), headerByte);

        boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
        throw exception;
    }

    short int size;
    buffer->ReadShort(size);

    // Validate size
    if (size < 0) {
        auto err = StringFormatter(
            "Can't decode SFSObject. Size is negative: %d", size);
        boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
        throw exception;
    }

    /*
     * NOTE: we catch codec exceptions OUTSIDE of the loop
     * meaning that any exception of that type will stop the process of looping
     * through the object data and immediately discard the whole packet of data.
     */

    try {
        for (int i = 0; i < size; i++) {
            // Decode object key
            std::string key;
            buffer->ReadUTF(key);

            // Console.WriteLine("Decoding object "+key);

            // Decode the next object
            boost::shared_ptr<SFSDataWrapper> decodedObject =
                DecodeObject(buffer);

            // Store decoded object and keep going
            if (decodedObject != NULL) {
                const boost::shared_ptr<std::string> keyRef(
                    new std::string(key));
                sfsObject->Put(keyRef, decodedObject);
            } else {
                auto err = StringFormatter(
                    "Could not decode value for SFSObject with key: %s",
                    key.c_str());
                const boost::shared_ptr<SFSCodecError> exception(
                    new SFSCodecError(err));
                throw exception;
            }
        }
    } catch (SFSCodecError err) {
        throw err;
    }

    return sfsObject;
}

// Binary ==> SFSArray

boost::shared_ptr<ISFSArray> DefaultSFSDataSerializer::Binary2Array(
    const boost::shared_ptr<ByteArray>& data) const {
    if (data->Length() < 3) {
        auto err = StringFormatter("Can't decode an SFSArray. Byte data is "
                                   "insufficient. Size:: %d byte(s)",
                                   data->Length());

        auto exception = boost::make_shared<SFSCodecError>(err);
        throw exception;
    }

    data->Position(0);
    return DecodeSFSArray(data);
}

boost::shared_ptr<ISFSArray> DefaultSFSDataSerializer::DecodeSFSArray(
    const boost::shared_ptr<ByteArray>& buffer) const {
    auto sfsArray = SFSArray::NewInstance();

    // Get tpyeId
    std::uint8_t type;
    buffer->ReadByte(type);
    SFSDataType headerType = (SFSDataType)(long int)(type);

    // Validate typeId
    if (headerType != SFSDATATYPE_SFS_ARRAY) {
        auto err =
            StringFormatter("Invalid SFSDataType. Expected: %d, found: %d",
                            SFSDATATYPE_SFS_ARRAY, headerType);
        boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
        throw exception;
    }

    short int size;
    buffer->ReadShort(size);

    // Validate size
    if (size < 0) {
        auto err = StringFormatter(
            "Can't decode SFSArray. Size is negative: %d", size);
        boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
        throw exception;
    }

    /*
     * NOTE: we catch codec exceptions OUTSIDE of the loop
     * meaning that any exception of that type will stop the process of looping
     * through the object data and immediately discard the whole packet of data.
     */

    try {
        for (long int i = 0; i < size; i++) {
            // Decode the next object
            boost::shared_ptr<SFSDataWrapper> decodedObject =
                DecodeObject(buffer);

            // Store decoded object and keep going
            if (decodedObject != NULL) {
                sfsArray->Add(decodedObject);
            } else {
                auto err = StringFormatter(
                    "Could not decode SFSArray item at index: %d", i);
                const boost::shared_ptr<SFSCodecError> exception(
                    new SFSCodecError(err));
                throw exception;
            }
        }
    } catch (SFSCodecError err) {
        throw err;
    }

    return sfsArray;
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::DecodeObject(
    const boost::shared_ptr<ByteArray>& buffer) const {
    boost::shared_ptr<SFSDataWrapper> decodedObject;
    std::uint8_t headerValue;
    buffer->ReadByte(headerValue);
    SFSDataType headerByte = (SFSDataType)(long int)(headerValue);

    // Console.WriteLine(headerByte);
    if (headerByte == SFSDATATYPE_NULL)
        decodedObject = BinDecode_NULL(buffer);
    else if (headerByte == SFSDATATYPE_BOOL)
        decodedObject = BinDecode_BOOL(buffer);
    else if (headerByte == SFSDATATYPE_BOOL_ARRAY)
        decodedObject = BinDecode_BOOL_ARRAY(buffer);
    else if (headerByte == SFSDATATYPE_BYTE)
        decodedObject = BinDecode_BYTE(buffer);
    else if (headerByte == SFSDATATYPE_BYTE_ARRAY)
        decodedObject = BinDecode_BYTE_ARRAY(buffer);
    else if (headerByte == SFSDATATYPE_SHORT)
        decodedObject = BinDecode_SHORT(buffer);
    else if (headerByte == SFSDATATYPE_SHORT_ARRAY)
        decodedObject = BinDecode_SHORT_ARRAY(buffer);
    else if (headerByte == SFSDATATYPE_INT)
        decodedObject = BinDecode_INT(buffer);
    else if (headerByte == SFSDATATYPE_INT_ARRAY)
        decodedObject = BinDecode_INT_ARRAY(buffer);
    else if (headerByte == SFSDATATYPE_LONG)
        decodedObject = BinDecode_LONG(buffer);
    else if (headerByte == SFSDATATYPE_LONG_ARRAY)
        decodedObject = BinDecode_LONG_ARRAY(buffer);
    else if (headerByte == SFSDATATYPE_FLOAT)
        decodedObject = BinDecode_FLOAT(buffer);
    else if (headerByte == SFSDATATYPE_FLOAT_ARRAY)
        decodedObject = BinDecode_FLOAT_ARRAY(buffer);
    else if (headerByte == SFSDATATYPE_DOUBLE)
        decodedObject = BinDecode_DOUBLE(buffer);
    else if (headerByte == SFSDATATYPE_DOUBLE_ARRAY)
        decodedObject = BinDecode_DOUBLE_ARRAY(buffer);
    else if (headerByte == SFSDATATYPE_UTF_STRING)
        decodedObject = BinDecode_UTF_STRING(buffer);
    else if (headerByte == SFSDATATYPE_TEXT)
        decodedObject = BinDecode_TEXT(buffer);
    else if (headerByte == SFSDATATYPE_UTF_STRING_ARRAY)
        decodedObject = BinDecode_UTF_STRING_ARRAY(buffer);
    else if (headerByte == SFSDATATYPE_SFS_ARRAY) {
        // pointer goes back 1 position
        buffer->Position(buffer->Position() - 1);
        decodedObject = boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(
            (long int)SFSDATATYPE_SFS_ARRAY, DecodeSFSArray(buffer)));
    } else if (headerByte == SFSDATATYPE_SFS_OBJECT) {
        // pointer goes back 1 position
        buffer->Position(buffer->Position() - 1);

        /*
         * See if this is a special type of SFSObject, the one that actually
         * describes a Class
         */
        boost::shared_ptr<ISFSObject> sfsObj = DecodeSFSObject(buffer);
        unsigned char type = (unsigned char)((long int)SFSDATATYPE_SFS_OBJECT);
        boost::shared_ptr<void> finalSfsObj = sfsObj;

        if (sfsObj->ContainsKey(CLASS_MARKER_KEY) &&
            sfsObj->ContainsKey(CLASS_FIELDS_KEY)) {
            type = (unsigned char)((long int)SFSDATATYPE_CLASS);
        }

        decodedObject = boost::shared_ptr<SFSDataWrapper>(
            new SFSDataWrapper(type, finalSfsObj));
    }
    // What is this typeID??
    else {
        auto err = StringFormatter("Unknown SFSDataType ID: %d", headerByte);
        boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
        throw exception;
    }

    return decodedObject;
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::EncodeObject(
    const boost::shared_ptr<ByteArray>& buffer_, int typeId,
    const boost::shared_ptr<void>& data) const {
    auto buffer = buffer_;
    switch (static_cast<SFSDataType>(typeId)) {
    case SFSDATATYPE_NULL:
        buffer = BinEncode_NULL(buffer);
        break;
    case SFSDATATYPE_BOOL:
        buffer =
            BinEncode_BOOL(buffer, (boost::static_pointer_cast<bool>)(data));
        break;
    case SFSDATATYPE_BYTE:
        buffer = BinEncode_BYTE(
            buffer, (boost::static_pointer_cast<unsigned char>)(data));
        break;
    case SFSDATATYPE_SHORT:
        buffer = BinEncode_SHORT(
            buffer, (boost::static_pointer_cast<std::int16_t>)(data));
        break;
    case SFSDATATYPE_INT:
        buffer = BinEncode_INT(
            buffer, (boost::static_pointer_cast<std::int32_t>)(data));
        break;
    case SFSDATATYPE_LONG:
        buffer = BinEncode_LONG(
            buffer, (boost::static_pointer_cast<std::int64_t>)(data));
        break;
    case SFSDATATYPE_FLOAT:
        buffer =
            BinEncode_FLOAT(buffer, (boost::static_pointer_cast<float>)(data));
        break;
    case SFSDATATYPE_DOUBLE:
        buffer = BinEncode_DOUBLE(buffer,
                                  (boost::static_pointer_cast<double>)(data));
        break;
    case SFSDATATYPE_UTF_STRING:
        buffer = BinEncode_UTF_STRING(
            buffer, (boost::static_pointer_cast<std::string>)(data));
        break;
    case SFSDATATYPE_TEXT:
        buffer = BinEncode_TEXT(
            buffer, (boost::static_pointer_cast<std::string>)(data));
        break;
    case SFSDATATYPE_BOOL_ARRAY:
        buffer = BinEncode_BOOL_ARRAY(
            buffer, (boost::static_pointer_cast<std::vector<bool>>)(data));
        break;
    case SFSDATATYPE_BYTE_ARRAY:
        buffer = BinEncode_BYTE_ARRAY(
            buffer, (boost::static_pointer_cast<ByteArray>)(data));
        break;
    case SFSDATATYPE_SHORT_ARRAY:
        buffer = BinEncode_SHORT_ARRAY(
            buffer,
            boost::static_pointer_cast<std::vector<std::int16_t>>(data));
        break;
    case SFSDATATYPE_INT_ARRAY:
        buffer = BinEncode_INT_ARRAY(
            buffer,
            (boost::static_pointer_cast<std::vector<std::int32_t>>)(data));
        break;
    case SFSDATATYPE_LONG_ARRAY:
        buffer = BinEncode_LONG_ARRAY(
            buffer,
            (boost::static_pointer_cast<std::vector<std::int64_t>>)(data));
        break;
    case SFSDATATYPE_FLOAT_ARRAY:
        buffer = BinEncode_FLOAT_ARRAY(
            buffer, (boost::static_pointer_cast<std::vector<float>>)(data));
        break;
    case SFSDATATYPE_DOUBLE_ARRAY:
        buffer = BinEncode_DOUBLE_ARRAY(
            buffer, (boost::static_pointer_cast<std::vector<double>>)(data));
        break;
    case SFSDATATYPE_UTF_STRING_ARRAY:
        buffer = BinEncode_UTF_STRING_ARRAY(
            buffer,
            (boost::static_pointer_cast<std::vector<std::string>>)(data));
        break;
    case SFSDATATYPE_SFS_ARRAY:
        buffer = AddData(
            buffer,
            Array2Binary((boost::static_pointer_cast<ISFSArray>)(data)));
        break;
    case SFSDATATYPE_SFS_OBJECT:
        buffer = AddData(
            buffer,
            Object2Binary((boost::static_pointer_cast<SFSObject>)(data)));
        break;
    case SFSDATATYPE_CLASS:
        buffer = AddData(
            buffer,
            Object2Binary((boost::static_pointer_cast<SFSObject>)(data)));
        break;
    default: {
        auto err = StringFormatter(
            "Unrecognized type in SFSObject serialization: %d", typeId);
        boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
        throw exception;
    }
    }

    return buffer;
}

// Binary Entities Decoding Methods

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_NULL(
    const boost::shared_ptr<ByteArray>& buffer) const {
    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_NULL, nullptr);
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_BOOL(
    const boost::shared_ptr<ByteArray>& buffer) const {
    auto value = boost::make_shared<bool>();
    buffer->ReadBool(*value);
    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_BOOL, value);
}
boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_BYTE(
    const boost::shared_ptr<ByteArray>& buffer) const {
    auto value = boost::make_shared<unsigned char>();
    buffer->ReadByte(*value);
    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_BYTE, value);
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_SHORT(
    const boost::shared_ptr<ByteArray>& buffer) const {
    auto value = boost::make_shared<std::int16_t>();
    buffer->ReadShort(*value);
    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_SHORT, value);
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_INT(
    const boost::shared_ptr<ByteArray>& buffer) const {
    auto value = boost::make_shared<std::int32_t>();
    buffer->ReadInt(*value);
    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_INT, value);
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_LONG(
    const boost::shared_ptr<ByteArray>& buffer) const {
    auto value = boost::make_shared<std::int64_t>();
    buffer->ReadLong(*value);
    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_LONG, value);
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_FLOAT(
    const boost::shared_ptr<ByteArray>& buffer) const {
    auto value = boost::make_shared<float>();
    buffer->ReadFloat(*value);
    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_FLOAT, value);
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_DOUBLE(
    const boost::shared_ptr<ByteArray>& buffer) const {
    auto value = boost::make_shared<double>();
    buffer->ReadDouble(*value);
    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_DOUBLE, value);
}

boost::shared_ptr<SFSDataWrapper>
DefaultSFSDataSerializer::BinDecode_UTF_STRING(
    const boost::shared_ptr<ByteArray>& buffer) const {
    auto value = boost::make_shared<std::string>();
    buffer->ReadUTF(*value);
    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_UTF_STRING, value);
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_TEXT(
    const boost::shared_ptr<ByteArray>& buffer) const {
    auto value = boost::make_shared<std::string>();
    buffer->ReadText(*value);
    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_UTF_STRING, value);
}

boost::shared_ptr<SFSDataWrapper>
DefaultSFSDataSerializer::BinDecode_BOOL_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer) const {
    long int size = GetTypedArraySize(buffer);
    auto arrayobj = boost::make_shared<std::vector<bool>>();

    for (int j = 0; j < size; j++) {
        bool value;
        buffer->ReadBool(value);
        arrayobj->push_back(value);
    }

    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_BOOL_ARRAY, arrayobj);
}

boost::shared_ptr<SFSDataWrapper>
DefaultSFSDataSerializer::BinDecode_BYTE_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer) const {
    std::int32_t size;
    buffer->ReadInt(size);

    if (size < 0) {
        auto err = StringFormatter("Array negative size: %d", size);
        auto exception = boost::make_shared<SFSCodecError>(err);
        throw exception;
    }

    // copy bytes
    auto values = boost::make_shared<std::vector<std::uint8_t>>();
    buffer->ReadBytes(static_cast<std::size_t>(size), *values.get());
    auto arrayobj = boost::make_shared<ByteArray>();
    arrayobj->WriteBytes(values);

    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_BYTE_ARRAY, arrayobj);
}

boost::shared_ptr<SFSDataWrapper>
DefaultSFSDataSerializer::BinDecode_SHORT_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer) const {
    std::int32_t size = GetTypedArraySize(buffer);
    auto arrayobj = boost::make_shared<std::vector<std::int16_t>>();

    for (std::int32_t j = 0; j < size; j++) {
        std::int16_t value;
        buffer->ReadShort(value);
        arrayobj->push_back(value);
    }

    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_SHORT_ARRAY,
                                              arrayobj);
}

boost::shared_ptr<SFSDataWrapper> DefaultSFSDataSerializer::BinDecode_INT_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer) const {
    std::int32_t size = GetTypedArraySize(buffer);
    auto arrayobj = boost::make_shared<std::vector<std::int32_t>>();

    for (std::int32_t j = 0; j < size; j++) {
        std::int32_t value;
        buffer->ReadInt(value);
        arrayobj->push_back(value);
    }

    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_INT_ARRAY, arrayobj);
}

boost::shared_ptr<SFSDataWrapper>
DefaultSFSDataSerializer::BinDecode_LONG_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer) const {
    std::int32_t size = GetTypedArraySize(buffer);
    auto arrayobj = boost::make_shared<std::vector<std::int64_t>>();

    for (std::int32_t j = 0; j < size; j++) {
        std::int64_t value;
        buffer->ReadLong(value);
        arrayobj->push_back(value);
    }

    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_LONG_ARRAY, arrayobj);
}

boost::shared_ptr<SFSDataWrapper>
DefaultSFSDataSerializer::BinDecode_FLOAT_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer) const {
    std::int32_t size = GetTypedArraySize(buffer);

    auto arrayobj = boost::make_shared<std::vector<float>>();

    for (std::int32_t j = 0; j < size; j++) {
        float value;
        buffer->ReadFloat(value);
        arrayobj->push_back(value);
    }

    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_FLOAT_ARRAY,
                                              arrayobj);
}

boost::shared_ptr<SFSDataWrapper>
DefaultSFSDataSerializer::BinDecode_DOUBLE_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer) const {
    std::int32_t size = GetTypedArraySize(buffer);

    auto arrayobj = boost::make_shared<std::vector<double>>();

    for (std::int32_t j = 0; j < size; j++) {
        double value;
        buffer->ReadDouble(value);
        arrayobj->push_back(value);
    }

    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_DOUBLE_ARRAY,
                                              arrayobj);
}

boost::shared_ptr<SFSDataWrapper>
DefaultSFSDataSerializer::BinDecode_UTF_STRING_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer) const {
    std::int32_t size = GetTypedArraySize(buffer);

    auto arrayobj = boost::make_shared<std::vector<std::string>>();

    for (std::int32_t j = 0; j < size; j++) {
        std::string value;
        buffer->ReadUTF(value);
        arrayobj->push_back(value);
    }

    return boost::make_shared<SFSDataWrapper>(SFSDATATYPE_UTF_STRING_ARRAY,
                                              arrayobj);
}

std::int32_t DefaultSFSDataSerializer::GetTypedArraySize(
    const boost::shared_ptr<ByteArray>& buffer) const {
    std::int16_t size;
    buffer->ReadShort(size);

    if (size < 0) {
        auto err = StringFormatter("Array negative size: %d", size);
        boost::shared_ptr<SFSCodecError> exception(new SFSCodecError(err));
        throw exception;
    }

    return size;
}

// Binary Entities Encoding Methods

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_NULL(
    const boost::shared_ptr<ByteArray>& buffer) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte((unsigned char)0x00);
    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_BOOL(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<bool>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_BOOL);
    data->WriteBool(*val);
    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_BYTE(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<unsigned char>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_BYTE);
    data->WriteByte(*val);
    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_SHORT(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<std::int16_t>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_SHORT);
    data->WriteShort(*val);
    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_INT(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<std::int32_t>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_INT);
    data->WriteInt(*val);
    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_LONG(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<std::int64_t>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_LONG);
    data->WriteLong(*val);
    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_FLOAT(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<float>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_FLOAT);
    data->WriteFloat(*val);
    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_DOUBLE(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<double>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_DOUBLE);
    data->WriteDouble(*val);
    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_INT(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<double>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_DOUBLE);
    data->WriteDouble(*val);
    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_UTF_STRING(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<std::string>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_UTF_STRING);
    data->WriteUTF(val);
    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_TEXT(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<std::string>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_TEXT);
    data->WriteText(val);
    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_BOOL_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<std::vector<bool>>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_BOOL_ARRAY);
    data->WriteShort((short int)(val->size()));

    for (auto iterator = val->begin(); iterator != val->end(); ++iterator) {
        data->WriteBool(*iterator);
    }

    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_BYTE_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<ByteArray>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_BYTE_ARRAY);
    data->WriteInt(static_cast<std::int32_t>(val->Length()));
    data->WriteBytes(val->Bytes());
    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_SHORT_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<std::vector<std::int16_t>>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_SHORT_ARRAY);
    data->WriteShort((short int)(val->size()));

    for (auto iterator = val->begin(); iterator != val->end(); ++iterator) {
        data->WriteShort(*iterator);
    }

    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_INT_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<std::vector<std::int32_t>>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_INT_ARRAY);
    data->WriteShort((short int)(val->size()));

    for (auto iterator = val->begin(); iterator != val->end(); ++iterator) {
        data->WriteInt(*iterator);
    }

    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_LONG_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<std::vector<std::int64_t>>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_LONG_ARRAY);
    data->WriteShort((short int)(val->size()));

    for (auto iterator = val->begin(); iterator != val->end(); ++iterator) {
        data->WriteLong(*iterator);
    }

    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_FLOAT_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<std::vector<float>>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_FLOAT_ARRAY);
    data->WriteShort((short int)(val->size()));

    for (auto iterator = val->begin(); iterator != val->end(); ++iterator) {
        data->WriteFloat(*iterator);
    }

    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::BinEncode_DOUBLE_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<std::vector<double>>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_DOUBLE_ARRAY);
    data->WriteShort((short int)(val->size()));

    for (auto iterator = val->begin(); iterator != val->end(); ++iterator) {
        data->WriteDouble(*iterator);
    }

    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray>
DefaultSFSDataSerializer::BinEncode_UTF_STRING_ARRAY(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<std::vector<std::string>>& val) const {
    auto data = boost::make_shared<ByteArray>();
    data->WriteByte(SFSDATATYPE_UTF_STRING_ARRAY);
    data->WriteShort((short int)(val->size()));

    for (auto iterator = val->begin(); iterator != val->end(); ++iterator) {
        data->WriteUTF(*iterator);
    }

    return AddData(buffer, data);
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::EncodeSFSObjectKey(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<std::string>& val) const {
    buffer->WriteUTF(val);
    return buffer;
}

boost::shared_ptr<ByteArray> DefaultSFSDataSerializer::AddData(
    const boost::shared_ptr<ByteArray>& buffer,
    const boost::shared_ptr<ByteArray>& newData) const {
    buffer->WriteBytes(newData->Bytes());
    return buffer;
}
} // namespace Serialization
} // namespace Protocol
} // namespace Sfs2X
