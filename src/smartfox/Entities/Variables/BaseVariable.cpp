// ===================================================================
//
// Description
//        Contains the implementation of BaseVariable
//
// Revision history
//        Date            Description
//        30-Nov-2016        First version
//
// ===================================================================

#include <cinttypes>

#include "BaseVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BaseVariable::BaseVariable(const std::string& name,
                           const boost::shared_ptr<void>& val, int type) {
    this->name = boost::make_shared<std::string>(name);

    // If type is specfied let's use it
    if (type > -1) {
        this->val = val;
        this->type = static_cast<VariableType>(type);
    }
    // Otherwise let's autodetect the type
    else {
        // SetValue(val);
    }
}

BaseVariable::BaseVariable(const std::string& name,
                           const boost::shared_ptr<std::int64_t>& val) {
    this->name = boost::make_shared<std::string>(name);
    SetValue(val);
}

BaseVariable::BaseVariable(const std::string& name,
                           const boost::shared_ptr<std::uint64_t>& val) {
    this->name = boost::make_shared<std::string>(name);
    SetValue(val);
}

BaseVariable::BaseVariable(const std::string& name,
                           const boost::shared_ptr<std::int32_t>& val) {
    this->name = boost::make_shared<std::string>(name);
    SetValue(val);
}

BaseVariable::BaseVariable(const std::string& name,
                           const boost::shared_ptr<std::uint32_t>& val) {
    this->name = boost::make_shared<std::string>(name);
    SetValue(val);
}

BaseVariable::BaseVariable(const std::string& name,
                           const boost::shared_ptr<bool>& val) {
    this->name = boost::make_shared<std::string>(name);
    SetValue(val);
}

BaseVariable::BaseVariable(const std::string& name,
                           const boost::shared_ptr<double>& val) {
    this->name = boost::make_shared<std::string>(name);
    SetValue(val);
}

BaseVariable::BaseVariable(const std::string& name,
                           const boost::shared_ptr<std::string>& val) {
    this->name = boost::make_shared<std::string>(name);
    SetValue(val);
}

BaseVariable::BaseVariable(const std::string& name,
                           const boost::shared_ptr<SFSObject>& val) {
    this->name = boost::make_shared<std::string>(name);
    SetValue(val);
}

BaseVariable::BaseVariable(const std::string& name,
                           const boost::shared_ptr<SFSArray>& val) {
    this->name = boost::make_shared<std::string>(name);
    SetValue(val);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
BaseVariable::~BaseVariable() {
    this->name.reset();
    this->val.reset();
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<std::string> BaseVariable::Name() const {
    return name;
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
VariableType BaseVariable::Type() const {
    return type;
}

// -------------------------------------------------------------------
// Value
// -------------------------------------------------------------------
boost::shared_ptr<void> BaseVariable::Value() const {
    return val;
}

// -------------------------------------------------------------------
// GetBoolValue
// -------------------------------------------------------------------
boost::shared_ptr<bool> BaseVariable::GetBoolValue() const {
    return boost::static_pointer_cast<bool>(val);
}

// -------------------------------------------------------------------
// GetIntValue
// -------------------------------------------------------------------
boost::shared_ptr<std::int32_t> BaseVariable::GetIntValue() const {
    return boost::static_pointer_cast<std::int32_t>(val);
}

// -------------------------------------------------------------------
// GetDoubleValue
// -------------------------------------------------------------------
boost::shared_ptr<double> BaseVariable::GetDoubleValue() const {
    return boost::static_pointer_cast<double>(val);
}

// -------------------------------------------------------------------
// GetStringValue
// -------------------------------------------------------------------
boost::shared_ptr<std::string> BaseVariable::GetStringValue() const {
    return boost::static_pointer_cast<std::string>(val);
}

// -------------------------------------------------------------------
// GetSFSObjectValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> BaseVariable::GetSFSObjectValue() const {
    return boost::static_pointer_cast<ISFSObject>(val);
}

// -------------------------------------------------------------------
// GetSFSArrayValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> BaseVariable::GetSFSArrayValue() const {
    return boost::static_pointer_cast<ISFSArray>(val);
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool BaseVariable::IsNull() const {
    return type == VARIABLETYPE_NULL;
}

// -------------------------------------------------------------------
// ToSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> BaseVariable::ToSFSArray() const {
    auto sfsa = SFSArray::NewInstance();

    // var name (0)
    sfsa->AddUtfString(name);

    // var type (1)
    sfsa->AddByte(static_cast<std::uint8_t>(type));

    // var value (2)
    PopulateArrayWithValue(sfsa);

    return sfsa;
}

// -------------------------------------------------------------------
// PopulateArrayWithValue
// -------------------------------------------------------------------
void BaseVariable::PopulateArrayWithValue(
    const boost::shared_ptr<ISFSArray>& arr) const {
    switch (type) {
    case VARIABLETYPE_UNKNOWN:
        break;

    case VARIABLETYPE_NULL:
        arr->AddNull();
        break;

    case VARIABLETYPE_BOOL:
        arr->AddBool(GetBoolValue());
        break;

    case VARIABLETYPE_INT:
        arr->AddInt(GetIntValue());
        break;

    case VARIABLETYPE_DOUBLE:
        arr->AddDouble(GetDoubleValue());
        break;

    case VARIABLETYPE_STRING:
        arr->AddUtfString(GetStringValue());
        break;

    case VARIABLETYPE_OBJECT:
        arr->AddSFSObject(GetSFSObjectValue());
        break;

    case VARIABLETYPE_ARRAY:
        arr->AddSFSArray(GetSFSArrayValue());
        break;
    }
}

// -------------------------------------------------------------------
// SetValue
// -------------------------------------------------------------------
void BaseVariable::SetValue(const boost::shared_ptr<std::int64_t>& val) {
    this->val = val;

    if (val == NULL) {
        type = VARIABLETYPE_NULL;
    } else {
        type = VARIABLETYPE_INT;
    }
}

void BaseVariable::SetValue(const boost::shared_ptr<std::uint64_t>& val) {
    this->val = val;

    if (val == NULL) {
        type = VARIABLETYPE_NULL;
    } else {
        type = VARIABLETYPE_INT;
    }
}

void BaseVariable::SetValue(const boost::shared_ptr<std::int32_t>& val) {
    this->val = val;

    if (val == NULL) {
        type = VARIABLETYPE_NULL;
    } else {
        type = VARIABLETYPE_INT;
    }
}

void BaseVariable::SetValue(const boost::shared_ptr<std::uint32_t>& val) {
    this->val = val;

    if (val == NULL) {
        type = VARIABLETYPE_NULL;
    } else {
        type = VARIABLETYPE_INT;
    }
}

void BaseVariable::SetValue(const boost::shared_ptr<bool>& val) {
    this->val = val;

    if (val == NULL) {
        type = VARIABLETYPE_NULL;
    } else {
        type = VARIABLETYPE_BOOL;
    }
}

void BaseVariable::SetValue(const boost::shared_ptr<double>& val) {
    this->val = val;

    if (val == NULL) {
        type = VARIABLETYPE_NULL;
    } else {
        type = VARIABLETYPE_DOUBLE;
    }
}

void BaseVariable::SetValue(const boost::shared_ptr<std::string>& val) {
    this->val = val;

    if (val == NULL) {
        type = VARIABLETYPE_NULL;
    } else {
        type = VARIABLETYPE_STRING;
    }
}

void BaseVariable::SetValue(const boost::shared_ptr<SFSObject>& val) {
    this->val = val;

    if (val == NULL) {
        type = VARIABLETYPE_NULL;
    } else {
        type = VARIABLETYPE_OBJECT;
    }
}

void BaseVariable::SetValue(const boost::shared_ptr<SFSArray>& val) {
    this->val = val;

    if (val == NULL) {
        type = VARIABLETYPE_NULL;
    } else {
        type = VARIABLETYPE_ARRAY;
    }
}

// -------------------------------------------------------------------
// TypeAsString
// -------------------------------------------------------------------
boost::shared_ptr<std::string> BaseVariable::TypeAsString() const {
    switch (type) {
    case VARIABLETYPE_UNKNOWN:
        return boost::make_shared<std::string>("UNKNOWN");

    case VARIABLETYPE_NULL:
        return boost::make_shared<std::string>("NULL");

    case VARIABLETYPE_BOOL:
        return boost::make_shared<std::string>("BOOL");

    case VARIABLETYPE_INT:
        return boost::make_shared<std::string>("INT");

    case VARIABLETYPE_DOUBLE:
        return boost::make_shared<std::string>("DOUBLE");

    case VARIABLETYPE_STRING:
        return boost::make_shared<std::string>("STRING");

    case VARIABLETYPE_OBJECT:
        return boost::make_shared<std::string>("OBJECT");

    case VARIABLETYPE_ARRAY:
        return boost::make_shared<std::string>("ARRAY");
    }

    return nullptr;
}

// -------------------------------------------------------------------
// ValueAsString
// -------------------------------------------------------------------
boost::shared_ptr<std::string> BaseVariable::ValueAsString() const {
    boost::shared_ptr<std::string> valueReturned;

    switch (type) {
    case VARIABLETYPE_UNKNOWN:
        valueReturned = boost::make_shared<std::string>();
        break;

    case VARIABLETYPE_NULL:
        valueReturned = boost::make_shared<std::string>();
        break;

    case VARIABLETYPE_BOOL:
        if (*GetBoolValue()) {
            valueReturned = boost::make_shared<std::string>("true");
        } else {
            valueReturned = boost::make_shared<std::string>("false");
        }
        break;

    case VARIABLETYPE_INT:
        valueReturned = boost::make_shared<std::string>(
            StringFormatter("%" PRId32, *GetIntValue()));
        break;

    case VARIABLETYPE_DOUBLE:
        valueReturned = boost::make_shared<std::string>(
            StringFormatter("%f", *GetDoubleValue()));
        break;

    case VARIABLETYPE_STRING:
        valueReturned = boost::make_shared<std::string>(*GetStringValue());
        break;

    case VARIABLETYPE_OBJECT:
        valueReturned =
            boost::make_shared<std::string>(*GetSFSObjectValue()->GetDump());
        break;

    case VARIABLETYPE_ARRAY:
        valueReturned =
            boost::make_shared<std::string>(*GetSFSArrayValue()->GetDump());
        break;
    }

    return valueReturned;
}
} // namespace Variables
} // namespace Entities
} // namespace Sfs2X
