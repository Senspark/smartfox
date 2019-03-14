// ===================================================================
//
// Description
//        Contains the implementation of SFSObject
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================

#include "SFSObject.h"
#include "../../Protocol/Serialization/DefaultSFSDataSerializer.h"
#include "smartfox/Entities/Data/SFSDataConverter.hpp"

#include <boost/make_shared.hpp>

namespace Sfs2X {
namespace Entities {
namespace Data {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSObject::SFSObject() {
    dataHolder = boost::make_shared<
        std::map<std::string, boost::shared_ptr<SFSDataWrapper>>>();
    serializer = DefaultSFSDataSerializer::Instance();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSObject::~SFSObject() {
    dataHolder->clear();
    dataHolder = boost::shared_ptr<
        std::map<std::string, boost::shared_ptr<SFSDataWrapper>>>();
}

// -------------------------------------------------------------------
// NewFromObject
// -------------------------------------------------------------------
boost::shared_ptr<SFSObject>
SFSObject::NewFromObject(const boost::shared_ptr<void>& o) {
    boost::throw_exception(
        boost::enable_error_info(std::runtime_error("Not implemented")));
}

// -------------------------------------------------------------------
// NewFromBinaryData
// -------------------------------------------------------------------
boost::shared_ptr<SFSObject>
SFSObject::NewFromBinaryData(const boost::shared_ptr<ByteArray>& ba) {
    return boost::static_pointer_cast<SFSObject>(
        DefaultSFSDataSerializer::Instance()->Binary2Object(ba));
}

// -------------------------------------------------------------------
// NewInstance
// -------------------------------------------------------------------
boost::shared_ptr<SFSObject> SFSObject::NewInstance() {
    boost::shared_ptr<SFSObject> returned(new SFSObject());
    return returned;
}

// -------------------------------------------------------------------
// Dump
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSObject::Dump() const {
    auto strDump = boost::make_shared<std::string>();
    strDump->append(1, DefaultObjectDumpFormatter::TOKEN_INDENT_OPEN);

    for (auto iterator = dataHolder->begin(); iterator != dataHolder->end();
         ++iterator) {
        auto&& wrapper = iterator->second;
        auto&& key = iterator->first;
        auto type = wrapper->Type();

        strDump->append("(");

        switch (type) {
        case SFSDATATYPE_NULL:
            strDump->append("null");
            break;
        case SFSDATATYPE_BOOL:
            strDump->append("bool");
            break;
        case SFSDATATYPE_BYTE:
            strDump->append("byte");
            break;
        case SFSDATATYPE_SHORT:
            strDump->append("short");
            break;
        case SFSDATATYPE_INT:
            strDump->append("int");
            break;
        case SFSDATATYPE_LONG:
            strDump->append("long");
            break;
        case SFSDATATYPE_FLOAT:
            strDump->append("float");
            break;
        case SFSDATATYPE_DOUBLE:
            strDump->append("double");
            break;
        case SFSDATATYPE_UTF_STRING:
            strDump->append("utf_string");
            break;
        case SFSDATATYPE_BOOL_ARRAY:
            strDump->append("bool_array");
            break;
        case SFSDATATYPE_BYTE_ARRAY:
            strDump->append("byte_array");
            break;
        case SFSDATATYPE_SHORT_ARRAY:
            strDump->append("short_array");
            break;
        case SFSDATATYPE_INT_ARRAY:
            strDump->append("int_array");
            break;
        case SFSDATATYPE_LONG_ARRAY:
            strDump->append("long_array");
            break;
        case SFSDATATYPE_FLOAT_ARRAY:
            strDump->append("float_array");
            break;
        case SFSDATATYPE_DOUBLE_ARRAY:
            strDump->append("double_array");
            break;
        case SFSDATATYPE_UTF_STRING_ARRAY:
            strDump->append("utf_string_array");
            break;
        case SFSDATATYPE_SFS_ARRAY:
            strDump->append("sfs_array");
            break;
        case SFSDATATYPE_SFS_OBJECT:
            strDump->append("sfs_object");
            break;
        case SFSDATATYPE_CLASS:
            strDump->append("class");
            break;
        }

        strDump->append(")");

        strDump->append(" ");
        strDump->append(key);
        strDump->append(": ");

        switch (type) {
        case SFSDATATYPE_NULL:
            break;
        case SFSDATATYPE_BOOL: {
            strDump->append(DataConverter(wrapper->Data()).toBool());
            break;
        }
        case SFSDATATYPE_BYTE: {
            strDump->append(DataConverter(wrapper->Data()).toByte());
            break;
        }
        case SFSDATATYPE_SHORT: {
            strDump->append(DataConverter(wrapper->Data()).toShort());
            break;
        }
        case SFSDATATYPE_INT: {
            strDump->append(DataConverter(wrapper->Data()).toInt());
            break;
        }
        case SFSDATATYPE_LONG: {
            strDump->append(DataConverter(wrapper->Data()).toLong());
            break;
        }
        case SFSDATATYPE_FLOAT: {
            strDump->append(DataConverter(wrapper->Data()).toFloat());
            break;
        }
        case SFSDATATYPE_DOUBLE: {
            strDump->append(DataConverter(wrapper->Data()).toDouble());
            break;
        }
        case SFSDATATYPE_UTF_STRING: {
            strDump->append(DataConverter(wrapper->Data()).toString());
            break;
        }
        case SFSDATATYPE_BOOL_ARRAY: {
            strDump->append(DataConverter(wrapper->Data()).toBoolArray());
            break;
        }
        case SFSDATATYPE_BYTE_ARRAY: {
            strDump->append(DataConverter(wrapper->Data()).toByteArray());
            break;
        }
        case SFSDATATYPE_SHORT_ARRAY: {
            strDump->append(DataConverter(wrapper->Data()).toShortArray());
            break;
        }
        case SFSDATATYPE_INT_ARRAY: {
            strDump->append(DataConverter(wrapper->Data()).toIntArray());
            break;
        }
        case SFSDATATYPE_LONG_ARRAY: {
            strDump->append(DataConverter(wrapper->Data()).toLongArray());
            break;
        }
        case SFSDATATYPE_FLOAT_ARRAY: {
            strDump->append(DataConverter(wrapper->Data()).toLongArray());
            break;
        }
        case SFSDATATYPE_DOUBLE_ARRAY: {
            strDump->append(DataConverter(wrapper->Data()).toDoubleArray());
            break;
        }
        case SFSDATATYPE_UTF_STRING_ARRAY: {
            strDump->append(DataConverter(wrapper->Data()).toStringArray());
            break;
        }
        case SFSDATATYPE_SFS_ARRAY:
            strDump->append(
                *(((SFSArray*)wrapper->Data().get())->GetDump(false)));
            break;
        case SFSDATATYPE_SFS_OBJECT:
            strDump->append(
                *(((SFSObject*)wrapper->Data().get())->GetDump(false)));
            break;
        case SFSDATATYPE_CLASS:
            break;
        }
        strDump->append(1, DefaultObjectDumpFormatter::TOKEN_DIVIDER);
    }

    // We do this only if the object is not empty
    if (Size() > 0) {
        strDump = boost::make_shared<std::string>(
            strDump->substr(0, strDump->size() - 1));
    }

    strDump->append(1, DefaultObjectDumpFormatter::TOKEN_INDENT_CLOSE);
    return strDump;
}

// Type getters
// Raw

// -------------------------------------------------------------------
// GetData
// -------------------------------------------------------------------
boost::shared_ptr<SFSDataWrapper>
SFSObject::GetData(const std::string& key) const {
    return dataHolder->at(key);
}

// -------------------------------------------------------------------
// GetData
// -------------------------------------------------------------------
boost::shared_ptr<SFSDataWrapper>
SFSObject::GetData(const boost::shared_ptr<std::string>& key) const {
    return GetData(*key);
}

// -------------------------------------------------------------------
// GetBool
// -------------------------------------------------------------------
boost::shared_ptr<bool> SFSObject::GetBool(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return boost::make_shared<bool>();
    }
    return boost::static_pointer_cast<bool>(iterator->second->Data());
}

// -------------------------------------------------------------------
// GetBool
// -------------------------------------------------------------------
boost::shared_ptr<bool>
SFSObject::GetBool(const boost::shared_ptr<std::string>& key) const {
    return GetBool(*key);
}

// -------------------------------------------------------------------
// GetByte
// -------------------------------------------------------------------
boost::shared_ptr<std::uint8_t>
SFSObject::GetByte(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return boost::make_shared<std::uint8_t>();
    }
    return boost::static_pointer_cast<std::uint8_t>(iterator->second->Data());
}

// -------------------------------------------------------------------
// GetByte
// -------------------------------------------------------------------
boost::shared_ptr<std::uint8_t>
SFSObject::GetByte(const boost::shared_ptr<std::string>& key) const {
    return GetByte(*key);
}

// -------------------------------------------------------------------
// GetShort
// -------------------------------------------------------------------
boost::shared_ptr<std::int16_t>
SFSObject::GetShort(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return boost::make_shared<std::int16_t>();
    }
    return boost::static_pointer_cast<std::int16_t>(iterator->second->Data());
}

// -------------------------------------------------------------------
// GetShort
// -------------------------------------------------------------------
boost::shared_ptr<std::int16_t>
SFSObject::GetShort(const boost::shared_ptr<std::string>& key) const {
    return GetShort(*key);
}

// -------------------------------------------------------------------
// GetInt
// -------------------------------------------------------------------
boost::shared_ptr<std::int32_t>
SFSObject::GetInt(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return boost::make_shared<std::int32_t>();
    }
    return boost::static_pointer_cast<std::int32_t>(iterator->second->Data());
}

// -------------------------------------------------------------------
// GetInt
// -------------------------------------------------------------------
boost::shared_ptr<std::int32_t>
SFSObject::GetInt(const boost::shared_ptr<std::string>& key) const {
    return GetInt(*key);
}

// -------------------------------------------------------------------
// GetLong
// -------------------------------------------------------------------
boost::shared_ptr<std::int64_t>
SFSObject::GetLong(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return boost::make_shared<std::int64_t>();
    }
    return boost::static_pointer_cast<std::int64_t>(iterator->second->Data());
}

// -------------------------------------------------------------------
// GetLong
// -------------------------------------------------------------------
boost::shared_ptr<std::int64_t>
SFSObject::GetLong(const boost::shared_ptr<std::string>& key) const {
    return GetLong(*key);
}

// -------------------------------------------------------------------
// GetFloat
// -------------------------------------------------------------------
boost::shared_ptr<float> SFSObject::GetFloat(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return boost::make_shared<float>();
    }
    return boost::static_pointer_cast<float>(iterator->second->Data());
}

// -------------------------------------------------------------------
// GetFloat
// -------------------------------------------------------------------
boost::shared_ptr<float>
SFSObject::GetFloat(const boost::shared_ptr<std::string>& key) const {
    return GetFloat(*key);
}

// -------------------------------------------------------------------
// GetDouble
// -------------------------------------------------------------------
boost::shared_ptr<double> SFSObject::GetDouble(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return boost::make_shared<double>();
    }
    return boost::static_pointer_cast<double>(iterator->second->Data());
}

// -------------------------------------------------------------------
// GetDouble
// -------------------------------------------------------------------
boost::shared_ptr<double>
SFSObject::GetDouble(const boost::shared_ptr<std::string>& key) const {
    return GetDouble(*key);
}

// -------------------------------------------------------------------
// GetUtfString
// -------------------------------------------------------------------
boost::shared_ptr<std::string>
SFSObject::GetUtfString(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return boost::shared_ptr<std::string>();
    }
    return boost::static_pointer_cast<std::string>(iterator->second->Data());
}

// -------------------------------------------------------------------
// GetUtfString
// -------------------------------------------------------------------
boost::shared_ptr<std::string>
SFSObject::GetUtfString(const boost::shared_ptr<std::string>& key) const {
    return GetUtfString(*key);
}

// -------------------------------------------------------------------
// GetText
// -------------------------------------------------------------------
boost::shared_ptr<std::string>
SFSObject::GetText(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return nullptr;
    }
    return boost::static_pointer_cast<std::string>(iterator->second->Data());
}

// -------------------------------------------------------------------
// GetText
// -------------------------------------------------------------------
boost::shared_ptr<std::string>
SFSObject::GetText(const boost::shared_ptr<std::string>& key) const {
    return GetUtfString(*key);
}

// -------------------------------------------------------------------
// GetArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<std::uint8_t>>
SFSObject::GetArray(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return nullptr;
    }
    return boost::static_pointer_cast<std::vector<std::uint8_t>>(
        iterator->second->Data());
}

// -------------------------------------------------------------------
// GetArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<std::uint8_t>>
SFSObject::GetArray(const boost::shared_ptr<std::string>& key) const {
    return GetArray(*key);
}

// Arrays

// -------------------------------------------------------------------
// GetBoolArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<bool>>
SFSObject::GetBoolArray(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return nullptr;
    }
    return boost::static_pointer_cast<std::vector<bool>>(
        iterator->second->Data());
}

// -------------------------------------------------------------------
// GetBoolArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<bool>>
SFSObject::GetBoolArray(const boost::shared_ptr<std::string>& key) const {
    return GetBoolArray(*key);
}

// -------------------------------------------------------------------
// GetByteArray
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray>
SFSObject::GetByteArray(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return nullptr;
    }
    return boost::static_pointer_cast<ByteArray>(iterator->second->Data());
}

// -------------------------------------------------------------------
// GetByteArray
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray>
SFSObject::GetByteArray(const boost::shared_ptr<std::string>& key) const {
    return GetByteArray(*key);
}

// -------------------------------------------------------------------
// GetShortArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<std::int16_t>>
SFSObject::GetShortArray(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return nullptr;
    }
    return boost::static_pointer_cast<std::vector<std::int16_t>>(
        iterator->second->Data());
}

// -------------------------------------------------------------------
// GetShortArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<std::int16_t>>
SFSObject::GetShortArray(const boost::shared_ptr<std::string>& key) const {
    return GetShortArray(*key);
}

// -------------------------------------------------------------------
// GetIntArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<std::int32_t>>
SFSObject::GetIntArray(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return nullptr;
    }
    return boost::static_pointer_cast<std::vector<std::int32_t>>(
        iterator->second->Data());
}

// -------------------------------------------------------------------
// GetIntArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<std::int32_t>>
SFSObject::GetIntArray(const boost::shared_ptr<std::string>& key) const {
    return GetIntArray(*key);
}

// -------------------------------------------------------------------
// GetLongArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<std::int64_t>>
SFSObject::GetLongArray(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return nullptr;
    }
    return boost::static_pointer_cast<std::vector<std::int64_t>>(
        iterator->second->Data());
}

// -------------------------------------------------------------------
// GetLongArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<std::int64_t>>
SFSObject::GetLongArray(const boost::shared_ptr<std::string>& key) const {
    return GetLongArray(*key);
}

// -------------------------------------------------------------------
// GetFloatArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<float>>
SFSObject::GetFloatArray(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return nullptr;
    }
    return boost::static_pointer_cast<std::vector<float>>(
        iterator->second->Data());
}

// -------------------------------------------------------------------
// GetFloatArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<float>>
SFSObject::GetFloatArray(const boost::shared_ptr<std::string>& key) const {
    return GetFloatArray(*key);
}

// -------------------------------------------------------------------
// GetDoubleArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<double>>
SFSObject::GetDoubleArray(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return nullptr;
    }
    return boost::static_pointer_cast<std::vector<double>>(
        iterator->second->Data());
}

// -------------------------------------------------------------------
// GetDoubleArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<double>>
SFSObject::GetDoubleArray(const boost::shared_ptr<std::string>& key) const {
    return GetDoubleArray(*key);
}

// -------------------------------------------------------------------
// GetUtfStringArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<std::string>>
SFSObject::GetUtfStringArray(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return nullptr;
    }
    return boost::static_pointer_cast<std::vector<std::string>>(
        iterator->second->Data());
}

// -------------------------------------------------------------------
// GetUtfStringArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<std::string>>
SFSObject::GetUtfStringArray(const boost::shared_ptr<std::string>& key) const {
    return GetUtfStringArray(*key);
}

// -------------------------------------------------------------------
// GetSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray>
SFSObject::GetSFSArray(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return nullptr;
    }
    return boost::static_pointer_cast<ISFSArray>(iterator->second->Data());
}

// -------------------------------------------------------------------
// GetSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray>
SFSObject::GetSFSArray(const boost::shared_ptr<std::string>& key) const {
    return GetSFSArray(*key);
}

// -------------------------------------------------------------------
// GetSFSObject
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject>
SFSObject::GetSFSObject(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return nullptr;
    }
    return boost::static_pointer_cast<ISFSObject>(iterator->second->Data());
}

// -------------------------------------------------------------------
// GetSFSObject
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject>
SFSObject::GetSFSObject(const boost::shared_ptr<std::string>& key) const {
    return GetSFSObject(*key);
}

// -------------------------------------------------------------------
// PutNull
// -------------------------------------------------------------------
void SFSObject::PutNull(const std::string& key) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_NULL, nullptr));
}

// -------------------------------------------------------------------
// PutNull
// -------------------------------------------------------------------
void SFSObject::PutNull(const boost::shared_ptr<std::string>& key) {
    PutNull(*key);
}

// -------------------------------------------------------------------
// PutBool
// -------------------------------------------------------------------
void SFSObject::PutBool(const std::string& key,
                        const boost::shared_ptr<bool>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_BOOL, val));
}

// -------------------------------------------------------------------
// PutBool
// -------------------------------------------------------------------
void SFSObject::PutBool(const boost::shared_ptr<std::string>& key,
                        const boost::shared_ptr<bool>& val) {
    PutBool(*key, val);
}

// -------------------------------------------------------------------
// PutBool
// -------------------------------------------------------------------
void SFSObject::PutBool(const std::string& key, bool val) {
    PutBool(key, boost::make_shared<bool>(val));
}

// -------------------------------------------------------------------
// PutBool
// -------------------------------------------------------------------
void SFSObject::PutBool(const boost::shared_ptr<std::string>& key, bool val) {
    PutBool(*key, val);
}

// -------------------------------------------------------------------
// PutByte
// -------------------------------------------------------------------
void SFSObject::PutByte(const std::string& key,
                        const boost::shared_ptr<std::uint8_t>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_BYTE, val));
}

// -------------------------------------------------------------------
// PutByte
// -------------------------------------------------------------------
void SFSObject::PutByte(const boost::shared_ptr<std::string>& key,
                        const boost::shared_ptr<std::uint8_t>& val) {
    PutByte(*key, val);
}

// -------------------------------------------------------------------
// PutByte
// -------------------------------------------------------------------
void SFSObject::PutByte(const std::string& key, std::uint8_t val) {
    PutByte(key, boost::make_shared<std::uint8_t>(val));
}

// -------------------------------------------------------------------
// PutByte
// -------------------------------------------------------------------
void SFSObject::PutByte(const boost::shared_ptr<std::string>& key,
                        std::uint8_t val) {
    PutByte(*key, val);
}

// -------------------------------------------------------------------
// PutShort
// -------------------------------------------------------------------
void SFSObject::PutShort(const std::string& key,
                         const boost::shared_ptr<std::int16_t>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_SHORT, val));
}

// -------------------------------------------------------------------
// PutShort
// -------------------------------------------------------------------
void SFSObject::PutShort(const boost::shared_ptr<std::string>& key,
                         const boost::shared_ptr<std::int16_t>& val) {
    PutShort(*key, val);
}

// -------------------------------------------------------------------
// PutShort
// -------------------------------------------------------------------
void SFSObject::PutShort(const std::string& key, std::int16_t val) {
    PutShort(key, boost::make_shared<std::int16_t>(val));
}

// -------------------------------------------------------------------
// PutShort
// -------------------------------------------------------------------
void SFSObject::PutShort(const boost::shared_ptr<std::string>& key,
                         std::int16_t val) {
    PutShort(*key, val);
}

// -------------------------------------------------------------------
// PutInt
// -------------------------------------------------------------------
void SFSObject::PutInt(const std::string& key,
                       const boost::shared_ptr<std::int32_t>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_INT, val));
}

// -------------------------------------------------------------------
// PutInt
// -------------------------------------------------------------------
void SFSObject::PutInt(const boost::shared_ptr<std::string>& key,
                       const boost::shared_ptr<std::int32_t>& val) {
    PutInt(*key, val);
}

// -------------------------------------------------------------------
// PutInt
// -------------------------------------------------------------------
void SFSObject::PutInt(const std::string& key, std::int32_t val) {
    PutInt(key, boost::make_shared<std::int32_t>(val));
}

// -------------------------------------------------------------------
// PutInt
// -------------------------------------------------------------------
void SFSObject::PutInt(const boost::shared_ptr<std::string>& key,
                       std::int32_t val) {
    PutInt(*key, val);
}

// -------------------------------------------------------------------
// PutLong
// -------------------------------------------------------------------
void SFSObject::PutLong(const std::string& key,
                        const boost::shared_ptr<std::int64_t>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_LONG, val));
}

// -------------------------------------------------------------------
// PutLong
// -------------------------------------------------------------------
void SFSObject::PutLong(const boost::shared_ptr<std::string>& key,
                        const boost::shared_ptr<std::int64_t>& val) {
    PutLong(*key, val);
}

// -------------------------------------------------------------------
// PutLong
// -------------------------------------------------------------------
void SFSObject::PutLong(const std::string& key, std::int64_t val) {
    PutLong(key, boost::make_shared<std::int64_t>(val));
}

// -------------------------------------------------------------------
// PutLong
// -------------------------------------------------------------------
void SFSObject::PutLong(const boost::shared_ptr<std::string>& key,
                        std::int64_t val) {
    PutLong(*key, val);
}

// -------------------------------------------------------------------
// PutFloat
// -------------------------------------------------------------------
void SFSObject::PutFloat(const std::string& key,
                         const boost::shared_ptr<float>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_FLOAT, val));
}

// -------------------------------------------------------------------
// PutFloat
// -------------------------------------------------------------------
void SFSObject::PutFloat(const boost::shared_ptr<std::string>& key,
                         const boost::shared_ptr<float>& val) {
    PutFloat(*key, val);
}

// -------------------------------------------------------------------
// PutFloat
// -------------------------------------------------------------------
void SFSObject::PutFloat(const std::string& key, float val) {
    PutFloat(key, boost::make_shared<float>(val));
}

// -------------------------------------------------------------------
// PutFloat
// -------------------------------------------------------------------
void SFSObject::PutFloat(const boost::shared_ptr<std::string>& key, float val) {
    PutFloat(*key, val);
}

// -------------------------------------------------------------------
// PutDouble
// -------------------------------------------------------------------
void SFSObject::PutDouble(const std::string& key,
                          const boost::shared_ptr<double>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_DOUBLE, val));
}

// -------------------------------------------------------------------
// PutDouble
// -------------------------------------------------------------------
void SFSObject::PutDouble(const boost::shared_ptr<std::string>& key,
                          const boost::shared_ptr<double>& val) {
    PutDouble(*key, val);
}

// -------------------------------------------------------------------
// PutDouble
// -------------------------------------------------------------------
void SFSObject::PutDouble(const std::string& key, double val) {
    PutDouble(key, boost::make_shared<double>(val));
}

// -------------------------------------------------------------------
// PutDouble
// -------------------------------------------------------------------
void SFSObject::PutDouble(const boost::shared_ptr<std::string>& key,
                          double val) {
    PutDouble(*key, val);
}

// -------------------------------------------------------------------
// PutUtfString
// -------------------------------------------------------------------
void SFSObject::PutUtfString(const std::string& key,
                             const boost::shared_ptr<std::string>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_UTF_STRING, val));
}

// -------------------------------------------------------------------
// PutUtfString
// -------------------------------------------------------------------
void SFSObject::PutUtfString(const boost::shared_ptr<std::string>& key,
                             const boost::shared_ptr<std::string>& val) {
    PutUtfString(*key, val);
}

// -------------------------------------------------------------------
// PutUtfString
// -------------------------------------------------------------------
void SFSObject::PutUtfString(const std::string& key, const std::string& val) {
    PutUtfString(key, boost::make_shared<std::string>(val));
}

// -------------------------------------------------------------------
// PutUtfString
// -------------------------------------------------------------------
void SFSObject::PutUtfString(const boost::shared_ptr<std::string>& key,
                             const std::string& val) {
    PutUtfString(*key, val);
}

// -------------------------------------------------------------------
// PutText
// -------------------------------------------------------------------
void SFSObject::PutText(const std::string& key,
                        const boost::shared_ptr<std::string>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_TEXT, val));
}

// -------------------------------------------------------------------
// PutText
// -------------------------------------------------------------------
void SFSObject::PutText(const boost::shared_ptr<std::string>& key,
                        const boost::shared_ptr<std::string>& val) {
    PutUtfString(*key, val);
}

// -------------------------------------------------------------------
// PutText
// -------------------------------------------------------------------
void SFSObject::PutText(const std::string& key, const std::string& val) {
    PutUtfString(key, boost::make_shared<std::string>(val));
}

// -------------------------------------------------------------------
// PutText
// -------------------------------------------------------------------
void SFSObject::PutText(const boost::shared_ptr<std::string>& key,
                        const std::string& val) {
    PutUtfString(*key, val);
}

// Arrays

// -------------------------------------------------------------------
// PutBoolArray
// -------------------------------------------------------------------
void SFSObject::PutBoolArray(const std::string& key,
                             const boost::shared_ptr<std::vector<bool>>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_BOOL_ARRAY, val));
}

// -------------------------------------------------------------------
// PutBoolArray
// -------------------------------------------------------------------
void SFSObject::PutBoolArray(const boost::shared_ptr<std::string>& key,
                             const boost::shared_ptr<std::vector<bool>>& val) {
    PutBoolArray(*key, val);
}

// -------------------------------------------------------------------
// PutByteArray
// -------------------------------------------------------------------
void SFSObject::PutByteArray(const std::string& key,
                             const boost::shared_ptr<ByteArray>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_BYTE_ARRAY, val));
}

// -------------------------------------------------------------------
// PutByteArray
// -------------------------------------------------------------------
void SFSObject::PutByteArray(const boost::shared_ptr<std::string>& key,
                             const boost::shared_ptr<ByteArray>& val) {
    PutByteArray(*key, val);
}

// -------------------------------------------------------------------
// PutShortArray
// -------------------------------------------------------------------
void SFSObject::PutShortArray(
    const std::string& key,
    const boost::shared_ptr<std::vector<std::int16_t>>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_SHORT_ARRAY, val));
}

// -------------------------------------------------------------------
// PutShortArray
// -------------------------------------------------------------------
void SFSObject::PutShortArray(
    const boost::shared_ptr<std::string>& key,
    const boost::shared_ptr<std::vector<std::int16_t>>& val) {
    PutShortArray(*key, val);
}

// -------------------------------------------------------------------
// PutIntArray
// -------------------------------------------------------------------
void SFSObject::PutIntArray(
    const std::string& key,
    const boost::shared_ptr<std::vector<std::int32_t>>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_INT_ARRAY, val));
}

// -------------------------------------------------------------------
// PutIntArray
// -------------------------------------------------------------------
void SFSObject::PutIntArray(
    const boost::shared_ptr<std::string>& key,
    const boost::shared_ptr<std::vector<std::int32_t>>& val) {
    PutIntArray(*key, val);
}

// -------------------------------------------------------------------
// PutLongArray
// -------------------------------------------------------------------
void SFSObject::PutLongArray(
    const std::string& key,
    const boost::shared_ptr<std::vector<std::int64_t>>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_LONG_ARRAY, val));
}

// -------------------------------------------------------------------
// PutLongArray
// -------------------------------------------------------------------
void SFSObject::PutLongArray(
    const boost::shared_ptr<std::string>& key,
    const boost::shared_ptr<std::vector<std::int64_t>>& val) {
    PutLongArray(*key, val);
}

// -------------------------------------------------------------------
// PutFloatArray
// -------------------------------------------------------------------
void SFSObject::PutFloatArray(
    const std::string& key, const boost::shared_ptr<std::vector<float>>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_FLOAT_ARRAY, val));
}

// -------------------------------------------------------------------
// PutFloatArray
// -------------------------------------------------------------------
void SFSObject::PutFloatArray(
    const boost::shared_ptr<std::string>& key,
    const boost::shared_ptr<std::vector<float>>& val) {
    PutFloatArray(*key, val);
}

// -------------------------------------------------------------------
// PutDoubleArray
// -------------------------------------------------------------------
void SFSObject::PutDoubleArray(
    const std::string& key, const boost::shared_ptr<std::vector<double>>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_DOUBLE_ARRAY, val));
}

// -------------------------------------------------------------------
// PutDoubleArray
// -------------------------------------------------------------------
void SFSObject::PutDoubleArray(
    const boost::shared_ptr<std::string>& key,
    const boost::shared_ptr<std::vector<double>>& val) {
    PutDoubleArray(*key, val);
}

// -------------------------------------------------------------------
// PutUtfStringArray
// -------------------------------------------------------------------
void SFSObject::PutUtfStringArray(
    const std::string& key,
    const boost::shared_ptr<std::vector<std::string>>& val) {
    dataHolder->emplace(key, boost::make_shared<SFSDataWrapper>(
                                 SFSDATATYPE_UTF_STRING_ARRAY, val));
}

// -------------------------------------------------------------------
// PutUtfStringArray
// -------------------------------------------------------------------
void SFSObject::PutUtfStringArray(
    const boost::shared_ptr<std::string>& key,
    const boost::shared_ptr<std::vector<std::string>>& val) {
    PutUtfStringArray(*key, val);
}

// -------------------------------------------------------------------
// PutSFSArray
// -------------------------------------------------------------------
void SFSObject::PutSFSArray(const std::string& key,
                            const boost::shared_ptr<ISFSArray>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_SFS_ARRAY, val));
}

// -------------------------------------------------------------------
// PutSFSArray
// -------------------------------------------------------------------
void SFSObject::PutSFSArray(const boost::shared_ptr<std::string>& key,
                            const boost::shared_ptr<ISFSArray>& val) {
    PutSFSArray(*key, val);
}

// -------------------------------------------------------------------
// PutSFSObject
// -------------------------------------------------------------------
void SFSObject::PutSFSObject(const std::string& key,
                             const boost::shared_ptr<ISFSObject>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_SFS_OBJECT, val));
}

// -------------------------------------------------------------------
// PutSFSObject
// -------------------------------------------------------------------
void SFSObject::PutSFSObject(const boost::shared_ptr<std::string>& key,
                             const boost::shared_ptr<ISFSObject>& val) {
    PutSFSObject(*key, val);
}

// -------------------------------------------------------------------
// Put
// -------------------------------------------------------------------
void SFSObject::Put(const std::string& key,
                    const boost::shared_ptr<SFSDataWrapper>& val) {
    dataHolder->emplace(key, val);
}

// -------------------------------------------------------------------
// Put
// -------------------------------------------------------------------
void SFSObject::Put(const boost::shared_ptr<std::string>& key,
                    const boost::shared_ptr<SFSDataWrapper>& val) {
    Put(*key, val);
}

// -------------------------------------------------------------------
// ContainsKey
// -------------------------------------------------------------------
bool SFSObject::ContainsKey(const std::string& key) const {
    auto iterator = dataHolder->find(key);
    if (iterator == dataHolder->end()) {
        return false;
    }
    return true;
}

// -------------------------------------------------------------------
// ContainsKey
// -------------------------------------------------------------------
bool SFSObject::ContainsKey(const boost::shared_ptr<std::string>& key) const {
    return ContainsKey(*key);
}

// -------------------------------------------------------------------
// GetClass
// -------------------------------------------------------------------
boost::shared_ptr<void> SFSObject::GetClass(const std::string& key) const {
    if (not ContainsKey(key)) {
        return nullptr;
    }
    auto&& wrapper = dataHolder->at(key);
    if (wrapper->Data() != nullptr) {
        return wrapper->Data();
    }
    return nullptr;
}

// -------------------------------------------------------------------
// GetClass
// -------------------------------------------------------------------
boost::shared_ptr<void>
SFSObject::GetClass(const boost::shared_ptr<std::string>& key) const {
    return GetClass(*key);
}

// -------------------------------------------------------------------
// GetDump
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSObject::GetDump(bool format) const {
    if (format == false) {
        return Dump();
    }
    return DefaultObjectDumpFormatter::PrettyPrintDump(Dump());
}

// -------------------------------------------------------------------
// GetDump
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSObject::GetDump() const {
    return GetDump(true);
}

// -------------------------------------------------------------------
// GetHexDump
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSObject::GetHexDump() {
    return DefaultObjectDumpFormatter::HexDump(this->ToBinary());
}

// -------------------------------------------------------------------
// GetKeys
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<std::string>> SFSObject::GetKeys() const {
    auto keyList = boost::make_shared<std::vector<std::string>>();
    for (auto iterator = dataHolder->begin(); iterator != dataHolder->end();
         ++iterator) {
        keyList->push_back(iterator->first);
    }
    return keyList;
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool SFSObject::IsNull(const std::string& key) const {
    if (not ContainsKey(key)) {
        return true;
    }

    auto&& wrapper = dataHolder->at(key);
    return (wrapper->Type() ==
                static_cast<int>(SFSDataType::SFSDATATYPE_NULL) ||
            wrapper->Data() == NULL);
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool SFSObject::IsNull(const boost::shared_ptr<std::string>& key) const {
    return IsNull(*key);
}

// -------------------------------------------------------------------
// PutClass
// -------------------------------------------------------------------
void SFSObject::PutClass(const std::string& key,
                         const boost::shared_ptr<void>& val) {
    dataHolder->emplace(
        key, boost::make_shared<SFSDataWrapper>(SFSDATATYPE_CLASS, val));
}

// -------------------------------------------------------------------
// PutClass
// -------------------------------------------------------------------
void SFSObject::PutClass(const boost::shared_ptr<std::string>& key,
                         const boost::shared_ptr<void>& val) {
    PutClass(*key, val);
}

// -------------------------------------------------------------------
// RemoveElement
// -------------------------------------------------------------------
void SFSObject::RemoveElement(const std::string& key) {
    auto iterator = dataHolder->find(key);
    if (iterator != dataHolder->end()) {
        dataHolder->erase(iterator);
    }
}

// -------------------------------------------------------------------
// RemoveElement
// -------------------------------------------------------------------
void SFSObject::RemoveElement(const boost::shared_ptr<std::string>& key) {
    RemoveElement(*key);
}

// -------------------------------------------------------------------
// Size
// -------------------------------------------------------------------
std::size_t SFSObject::Size() const {
    return dataHolder->size();
}

// -------------------------------------------------------------------
// ToBinary
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> SFSObject::ToBinary() {
    return serializer->Object2Binary(shared_from_this());
}
} // namespace Data
} // namespace Entities
} // namespace Sfs2X
