// ===================================================================
//
// Description
//        Contains the implementation of SFSArray
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================

#include <typeinfo>

#include "SFSArray.h"
#include "../../Protocol/Serialization/DefaultSFSDataSerializer.h"
#include "smartfox/Entities/Data/SFSDataConverter.hpp"

#include <boost/make_shared.hpp>

namespace Sfs2X {
namespace Entities {
namespace Data {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSArray::SFSArray() {
    dataHolder =
        boost::make_shared<std::vector<boost::shared_ptr<SFSDataWrapper>>>();
    serializer = DefaultSFSDataSerializer::Instance();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSArray::~SFSArray() {
    dataHolder->clear();
    dataHolder =
        boost::shared_ptr<std::vector<boost::shared_ptr<SFSDataWrapper>>>();
}

// -------------------------------------------------------------------
// NewFromArray
// -------------------------------------------------------------------
boost::shared_ptr<SFSArray> SFSArray::NewFromArray(
    const std::vector<boost::shared_ptr<SFSDataWrapper>>& o) {
    return boost::shared_ptr<SFSArray>();
}

// -------------------------------------------------------------------
// NewFromBinaryData
// -------------------------------------------------------------------
boost::shared_ptr<SFSArray>
SFSArray::NewFromBinaryData(const boost::shared_ptr<ByteArray>& ba) {
    return boost::static_pointer_cast<SFSArray>(
        DefaultSFSDataSerializer::Instance()->Binary2Array(ba));
}

// -------------------------------------------------------------------
// NewInstance
// -------------------------------------------------------------------
boost::shared_ptr<SFSArray> SFSArray::NewInstance() {
    boost::shared_ptr<SFSArray> returned(new SFSArray());
    return returned;
}

// -------------------------------------------------------------------
// Contains
// -------------------------------------------------------------------
bool SFSArray::Contains(const boost::shared_ptr<void>& obj) const {
    if ((typeid(obj) == typeid(boost::shared_ptr<ISFSArray>)) ||
        (typeid(obj) == typeid(boost::shared_ptr<ISFSObject>))) {
        auto message = boost::make_shared<std::string>(
            "ISFSArray and ISFSObject are not supported by this method.");
        auto exception = boost::make_shared<SFSError>(message);
        throw exception;
    }

    for (std::size_t j = 0; j < Size(); j++) {
        auto&& wrappedObj = GetElementAt(j);
        if (wrappedObj == obj) {
            return true;
        }
    }

    return false;
}

// -------------------------------------------------------------------
// GetWrappedElementAt
// -------------------------------------------------------------------
boost::shared_ptr<SFSDataWrapper>
SFSArray::GetWrappedElementAt(std::size_t index) const {
    return dataHolder->at(index);
}

// -------------------------------------------------------------------
// GetElementAt
// -------------------------------------------------------------------
boost::shared_ptr<void> SFSArray::GetElementAt(std::size_t index) const {
    boost::shared_ptr<void> obj = boost::shared_ptr<void>();
    // if (index < 0 || dataHolder->size() <= index) return obj;
    if (dataHolder->at(index) != NULL) {
        obj = dataHolder->at(index)->Data();
    }

    return obj;
}

// -------------------------------------------------------------------
// RemoveElementAt
// -------------------------------------------------------------------
boost::shared_ptr<void> SFSArray::RemoveElementAt(std::size_t index) {
    if (index >= dataHolder->size())
        return boost::shared_ptr<void>();
    boost::shared_ptr<SFSDataWrapper> elem = dataHolder->at(index);
    using difference_type = std::make_signed_t<std::size_t>;
    dataHolder->erase(dataHolder->begin() +
                      static_cast<difference_type>(index));
    return elem->Data();
}

// -------------------------------------------------------------------
// Size
// -------------------------------------------------------------------
std::size_t SFSArray::Size() const {
    return dataHolder->size();
}

// -------------------------------------------------------------------
// ToBinary
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> SFSArray::ToBinary() {
    return serializer->Array2Binary(shared_from_this());
}

// -------------------------------------------------------------------
// GetDump
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSArray::GetDump() const {
    return GetDump(true);
}

// -------------------------------------------------------------------
// GetDump
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSArray::GetDump(bool format) const {
    if (!format) {
        return Dump();
    } else {
        return DefaultObjectDumpFormatter::PrettyPrintDump(Dump());
    }
}

// -------------------------------------------------------------------
// Dump
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSArray::Dump() const {
    auto strDump = boost::make_shared<std::string>();
    strDump->append(1, DefaultObjectDumpFormatter::TOKEN_INDENT_OPEN);

    for (auto iterator = dataHolder->begin(); iterator != dataHolder->end();
         ++iterator) {
        auto&& wrapper = *iterator;
        auto type = wrapper->Type();

        switch (type) {
        case SFSDATATYPE_NULL: {
            strDump->append("(");
            strDump->append("null");
            strDump->append(") ");
            strDump->append("NULL");
            break;
        }
        case SFSDATATYPE_BOOL: {
            strDump->append("(");
            strDump->append("bool");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toBool());
            break;
        }
        case SFSDATATYPE_BYTE: {
            strDump->append("(");
            strDump->append("byte");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toByte());
            break;
        }
        case SFSDATATYPE_SHORT: {
            strDump->append("(");
            strDump->append("short");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toShort());
            break;
        }
        case SFSDATATYPE_INT: {
            strDump->append("(");
            strDump->append("int");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toInt());
            break;
        }
        case SFSDATATYPE_LONG: {
            strDump->append("(");
            strDump->append("long");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toLong());
            break;
        }
        case SFSDATATYPE_FLOAT: {
            strDump->append("(");
            strDump->append("float");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toFloat());
            break;
        }
        case SFSDATATYPE_DOUBLE: {
            strDump->append("(");
            strDump->append("double");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toDouble());
            break;
        }
        case SFSDATATYPE_UTF_STRING: {
            strDump->append("(");
            strDump->append("utf_string");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toString());
            break;
        }
        case SFSDATATYPE_BOOL_ARRAY: {
            strDump->append("(");
            strDump->append("bool_array");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toBoolArray());
            break;
        }
        case SFSDATATYPE_BYTE_ARRAY: {
            strDump->append("(");
            strDump->append("byte_array");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toByteArray());
            break;
        }
        case SFSDATATYPE_SHORT_ARRAY: {
            strDump->append("(");
            strDump->append("short_array");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toShortArray());
            break;
        }
        case SFSDATATYPE_INT_ARRAY: {
            strDump->append("(");
            strDump->append("int_array");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toIntArray());
            break;
        }
        case SFSDATATYPE_LONG_ARRAY: {
            strDump->append("(");
            strDump->append("long_array");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toLongArray());
            break;
        }
        case SFSDATATYPE_FLOAT_ARRAY: {
            strDump->append("(");
            strDump->append("float_array");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toFloatArray());
            break;
        }
        case SFSDATATYPE_DOUBLE_ARRAY: {
            strDump->append("(");
            strDump->append("double_array");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toDoubleArray());
            break;
        }
        case SFSDATATYPE_UTF_STRING_ARRAY: {
            strDump->append("(");
            strDump->append("utf_string_array");
            strDump->append(") ");
            strDump->append(DataConverter(wrapper->Data()).toStringArray());
            break;
        }
        case SFSDATATYPE_SFS_ARRAY: {
            strDump->append("(");
            strDump->append("sfs_array");
            strDump->append(") ");

            strDump->append(
                *((boost::static_pointer_cast<SFSArray>(wrapper->Data()))
                      ->GetDump(false)));
            break;
        }
        case SFSDATATYPE_SFS_OBJECT: {
            strDump->append("(");
            strDump->append("sfs_object");
            strDump->append(") ");

            strDump->append(
                *((boost::static_pointer_cast<SFSObject>(wrapper->Data()))
                      ->GetDump(false)));
            break;
        }
        case SFSDATATYPE_CLASS: {
            strDump->append("(");
            strDump->append("class");
            strDump->append(") ");
            break;
        }
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

// -------------------------------------------------------------------
// GetHexDump
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSArray::GetHexDump() {
    return DefaultObjectDumpFormatter::HexDump(this->ToBinary());
}

/*
 * :::::::::::::::::::::::::::::::::::::::::
 * Type setters
 * :::::::::::::::::::::::::::::::::::::::::
 */

void SFSArray::AddNull() {
    AddObject(boost::shared_ptr<void>(), SFSDATATYPE_NULL);
}

void SFSArray::AddBool(const boost::shared_ptr<bool>& val) {
    AddObject(val, SFSDATATYPE_BOOL);
}

void SFSArray::AddBool(bool val) {
    AddBool(boost::make_shared<bool>(val));
}

void SFSArray::AddByte(const boost::shared_ptr<std::uint8_t>& val) {
    AddObject(val, SFSDATATYPE_BYTE);
}

void SFSArray::AddByte(std::uint8_t val) {
    AddByte(boost::make_shared<std::uint8_t>(val));
}

void SFSArray::AddShort(const boost::shared_ptr<std::int16_t>& val) {
    AddObject(val, SFSDATATYPE_SHORT);
}

void SFSArray::AddShort(std::int16_t val) {
    AddShort(boost::make_shared<std::int16_t>(val));
}

void SFSArray::AddInt(const boost::shared_ptr<std::int32_t>& val) {
    AddObject(val, SFSDATATYPE_INT);
}

void SFSArray::AddInt(std::int32_t val) {
    AddInt(boost::make_shared<std::int32_t>(val));
}

void SFSArray::AddLong(const boost::shared_ptr<std::int64_t>& val) {
    AddObject(val, SFSDATATYPE_LONG);
}

void SFSArray::AddLong(std::int64_t val) {
    AddLong(boost::make_shared<std::int64_t>(val));
}

void SFSArray::AddFloat(const boost::shared_ptr<float>& val) {
    AddObject(val, SFSDATATYPE_FLOAT);
}

void SFSArray::AddFloat(float val) {
    AddFloat(boost::make_shared<float>(val));
}

void SFSArray::AddDouble(const boost::shared_ptr<double>& val) {
    AddObject(val, SFSDATATYPE_DOUBLE);
}

void SFSArray::AddDouble(double val) {
    AddDouble(boost::make_shared<double>(val));
}

void SFSArray::AddUtfString(const boost::shared_ptr<std::string>& val) {
    AddObject(val, SFSDATATYPE_UTF_STRING);
}

void SFSArray::AddUtfString(const std::string& val) {
    AddUtfString(boost::make_shared<std::string>(val));
}

void SFSArray::AddText(const boost::shared_ptr<std::string>& val) {
    AddObject(val, SFSDATATYPE_TEXT);
}

void SFSArray::AddText(const std::string& val) {
    AddText(boost::make_shared<std::string>(val));
}

void SFSArray::AddBoolArray(
    const boost::shared_ptr<std::vector<boost::shared_ptr<bool>>>& val) {
    AddObject(val, SFSDATATYPE_BOOL_ARRAY);
}

void SFSArray::AddByteArray(const boost::shared_ptr<ByteArray>& val) {
    AddObject(val, SFSDATATYPE_BYTE_ARRAY);
}

void SFSArray::AddShortArray(
    const boost::shared_ptr<std::vector<boost::shared_ptr<std::int16_t>>>&
        val) {
    AddObject(val, SFSDATATYPE_SHORT_ARRAY);
}

void SFSArray::AddIntArray(
    const boost::shared_ptr<std::vector<boost::shared_ptr<std::int32_t>>>&
        val) {
    AddObject(val, SFSDATATYPE_INT_ARRAY);
}

void SFSArray::AddLongArray(
    const boost::shared_ptr<std::vector<boost::shared_ptr<std::int64_t>>>&
        val) {
    AddObject(val, SFSDATATYPE_LONG_ARRAY);
}

void SFSArray::AddFloatArray(
    const boost::shared_ptr<std::vector<boost::shared_ptr<float>>>& val) {
    AddObject(val, SFSDATATYPE_FLOAT_ARRAY);
}

void SFSArray::AddDoubleArray(
    const boost::shared_ptr<std::vector<boost::shared_ptr<double>>>& val) {
    AddObject(val, SFSDATATYPE_DOUBLE_ARRAY);
}

void SFSArray::AddUtfStringArray(
    const boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>>& val) {
    AddObject(val, SFSDATATYPE_UTF_STRING_ARRAY);
}

void SFSArray::AddSFSArray(const boost::shared_ptr<ISFSArray>& val) {
    AddObject(val, SFSDATATYPE_SFS_ARRAY);
}

void SFSArray::AddSFSObject(const boost::shared_ptr<ISFSObject>& val) {
    AddObject(val, SFSDATATYPE_SFS_OBJECT);
}

void SFSArray::AddClass(const boost::shared_ptr<void>& val) {
    AddObject(val, SFSDATATYPE_CLASS);
}

void SFSArray::Add(const boost::shared_ptr<SFSDataWrapper>& wrappedObject) {
    dataHolder->push_back(wrappedObject);
}

void SFSArray::AddObject(const boost::shared_ptr<void>& val, SFSDataType tp) {
    dataHolder->push_back(boost::make_shared<SFSDataWrapper>(tp, val));
}

/*
 * :::::::::::::::::::::::::::::::::::::::::
 * Type getters
 * :::::::::::::::::::::::::::::::::::::::::
 */
bool SFSArray::IsNull(std::size_t index) const {
    // if (index >= dataHolder->size()) return true;
    auto&& wrapper = dataHolder->at(index);
    return wrapper->Type() == static_cast<int>(SFSDATATYPE_NULL);
}

bool SFSArray::GetBool(std::size_t index) const {
    // if (index >= dataHolder->size()) return false;
    auto&& wrapper = dataHolder->at(index);
    return *boost::static_pointer_cast<bool>(wrapper->Data());
}

std::uint8_t SFSArray::GetByte(std::size_t index) const {
    // if (index >= dataHolder->size()) return 0;
    auto&& wrapper = dataHolder->at(index);
    return *boost::static_pointer_cast<std::uint8_t>(wrapper->Data());
}

std::int16_t SFSArray::GetShort(std::size_t index) const {
    // if (index >= dataHolder->size()) return 0;
    auto&& wrapper = dataHolder->at(index);
    return *boost::static_pointer_cast<std::int16_t>(wrapper->Data());
}

std::int32_t SFSArray::GetInt(std::size_t index) const {
    // if (index >= dataHolder->size()) return 0;
    auto&& wrapper = dataHolder->at(index);
    return *(boost::static_pointer_cast<std::int32_t>(wrapper->Data()));
}

std::int64_t SFSArray::GetLong(std::size_t index) const {
    // if (index >= dataHolder->size()) return 0;
    auto&& wrapper = dataHolder->at(index);
    return *(boost::static_pointer_cast<std::int64_t>(wrapper->Data()));
}

float SFSArray::GetFloat(std::size_t index) const {
    // if (index >= dataHolder->size()) return 0;
    auto&& wrapper = dataHolder->at(index);
    return *(boost::static_pointer_cast<float>(wrapper->Data()));
}

double SFSArray::GetDouble(std::size_t index) const {
    // if (index >= dataHolder->size()) return 0;
    auto&& wrapper = dataHolder->at(index);
    return *(boost::static_pointer_cast<double>(wrapper->Data()));
}

boost::shared_ptr<std::string> SFSArray::GetUtfString(std::size_t index) const {
    // if (index >= dataHolder->size()) return boost::shared_ptr<std::string>(new
    // string());
    auto&& wrapper = dataHolder->at(index);
    return boost::static_pointer_cast<std::string>(wrapper->Data());
}

boost::shared_ptr<std::string> SFSArray::GetText(std::size_t index) const {
    // if (index >= dataHolder->size()) return boost::shared_ptr<std::string>(new
    // string());
    auto&& wrapper = dataHolder->at(index);
    return boost::static_pointer_cast<std::string>(wrapper->Data());
}

boost::shared_ptr<std::vector<boost::shared_ptr<void>>>
SFSArray::GetArray(std::size_t index) const {
    // if (index >= dataHolder->size()) return
    // boost::shared_ptr<std::vector<boost::shared_ptr<void> > >();
    auto&& wrapper = dataHolder->at(index);
    return boost::static_pointer_cast<std::vector<boost::shared_ptr<void>>>(
        wrapper->Data());
}

boost::shared_ptr<std::vector<bool>>
SFSArray::GetBoolArray(std::size_t index) const {
    // if (index >= dataHolder->size()) return boost::shared_ptr<std::vector<bool>
    // >();
    auto&& wrapper = dataHolder->at(index);
    return boost::static_pointer_cast<std::vector<bool>>(wrapper->Data());
}

boost::shared_ptr<ByteArray> SFSArray::GetByteArray(std::size_t index) const {
    // if (index >= dataHolder->size()) return boost::shared_ptr<ByteArray>();
    auto&& wrapper = dataHolder->at(index);
    return (boost::static_pointer_cast<ByteArray>)(wrapper->Data());
}

boost::shared_ptr<std::vector<std::int16_t>>
SFSArray::GetShortArray(std::size_t index) const {
    // if (index >= dataHolder->size()) return boost::shared_ptr<std::vector<short
    // int> >();
    auto&& wrapper = dataHolder->at(index);
    return boost::static_pointer_cast<std::vector<std::int16_t>>(
        wrapper->Data());
}

boost::shared_ptr<std::vector<std::int32_t>>
SFSArray::GetIntArray(std::size_t index) const {
    // if (index >= dataHolder->size()) return boost::shared_ptr<std::vector<long
    // int> >();
    auto&& wrapper = dataHolder->at(index);
    return boost::static_pointer_cast<std::vector<std::int32_t>>(
        wrapper->Data());
}

boost::shared_ptr<std::vector<std::int64_t>>
SFSArray::GetLongArray(std::size_t index) const {
    // if (index >= dataHolder->size()) return boost::shared_ptr<std::vector<long
    // long> >();
    auto&& wrapper = dataHolder->at(index);
    return boost::static_pointer_cast<std::vector<std::int64_t>>(
        wrapper->Data());
}

boost::shared_ptr<std::vector<float>>
SFSArray::GetFloatArray(std::size_t index) const {
    // if (index >= dataHolder->size()) return boost::shared_ptr<std::vector<float>
    // >();
    auto&& wrapper = dataHolder->at(index);
    return boost::static_pointer_cast<std::vector<float>>(wrapper->Data());
}

boost::shared_ptr<std::vector<double>>
SFSArray::GetDoubleArray(std::size_t index) const {
    // if (index >= dataHolder->size()) return boost::shared_ptr<std::vector<double>
    // >();
    auto&& wrapper = dataHolder->at(index);
    return boost::static_pointer_cast<std::vector<double>>(wrapper->Data());
}

boost::shared_ptr<std::vector<std::string>>
SFSArray::GetUtfStringArray(std::size_t index) const {
    // if (index >= dataHolder->size()) return boost::shared_ptr<std::vector<string>
    // >();
    auto&& wrapper = dataHolder->at(index);
    return boost::static_pointer_cast<std::vector<std::string>>(
        wrapper->Data());
}

boost::shared_ptr<ISFSArray> SFSArray::GetSFSArray(std::size_t index) const {
    // if (index >= dataHolder->size()) return boost::shared_ptr<ISFSArray>();
    auto&& wrapper = dataHolder->at(index);
    return boost::static_pointer_cast<ISFSArray>(wrapper->Data());
}

boost::shared_ptr<void> SFSArray::GetClass(std::size_t index) const {
    // if (index >= dataHolder->size()) return boost::shared_ptr<void>();
    auto&& wrapper = dataHolder->at(index);
    return wrapper != nullptr ? wrapper->Data() : nullptr;
}

boost::shared_ptr<ISFSObject> SFSArray::GetSFSObject(std::size_t index) const {
    // if (index >= dataHolder->size()) return boost::shared_ptr<ISFSObject>();
    auto&& wrapper = dataHolder->at(index);
    return boost::static_pointer_cast<ISFSObject>(wrapper->Data());
}
} // namespace Data
} // namespace Entities
} // namespace Sfs2X
