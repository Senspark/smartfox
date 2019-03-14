// ===================================================================
//
// Description
//        Contains the implementation of SFSRoomVariable
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "SFSRoomVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {
using Self = SFSRoomVariable;

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<RoomVariable>
Self::FromSFSArray(const boost::shared_ptr<ISFSArray>& sfsa) {
    auto variable =
        boost::make_shared<Self>(*(sfsa->GetUtfString(0)), // name
                                 sfsa->GetElementAt(2),    // typed value
                                 sfsa->GetByte(1)          // type id
        );

    variable->IsPrivate(sfsa->GetBool(3));    // "Private" flag
    variable->IsPersistent(sfsa->GetBool(4)); // "Persistent" flag
    return variable;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::SFSRoomVariable(const std::string& name,
                      const boost::shared_ptr<std::int64_t>& val)
    : BaseVariable(name, val) {
    isPersistent = false;
    isPrivate = false;
}

Self::SFSRoomVariable(const std::string& name,
                      const boost::shared_ptr<std::uint64_t>& val)
    : BaseVariable(name, val) {
    isPersistent = false;
    isPrivate = false;
}

Self::SFSRoomVariable(const std::string& name,
                      const boost::shared_ptr<std::int32_t>& val)
    : BaseVariable(name, val) {
    isPersistent = false;
    isPrivate = false;
}

Self::SFSRoomVariable(const std::string& name,
                      const boost::shared_ptr<std::uint32_t>& val)
    : BaseVariable(name, val) {
    isPersistent = false;
    isPrivate = false;
}

Self::SFSRoomVariable(const std::string& name,
                      const boost::shared_ptr<bool>& val)
    : BaseVariable(name, val) {
    isPersistent = false;
    isPrivate = false;
}

Self::SFSRoomVariable(const std::string& name,
                      const boost::shared_ptr<double>& val)
    : BaseVariable(name, val) {
    isPersistent = false;
    isPrivate = false;
}

Self::SFSRoomVariable(const std::string& name,
                      const boost::shared_ptr<std::string>& val)
    : BaseVariable(name, val) {
    isPersistent = false;
    isPrivate = false;
}

Self::SFSRoomVariable(const std::string& name,
                      const boost::shared_ptr<SFSObject>& val)
    : BaseVariable(name, val) {
    isPersistent = false;
    isPrivate = false;
}

Self::SFSRoomVariable(const std::string& name,
                      const boost::shared_ptr<SFSArray>& val)
    : BaseVariable(name, val) {
    isPersistent = false;
    isPrivate = false;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::SFSRoomVariable(const std::string& name,
                      const boost::shared_ptr<void>& val, int type)
    : BaseVariable(name, val, type) {
    isPersistent = false;
    isPrivate = false;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
Self::~SFSRoomVariable() {
    this->Name() = boost::shared_ptr<std::string>();
    this->Value() = boost::shared_ptr<void>();
}

// -------------------------------------------------------------------
// IsPrivate
// -------------------------------------------------------------------
bool Self::IsPrivate() const {
    return isPrivate;
}

// -------------------------------------------------------------------
// IsPrivate
// -------------------------------------------------------------------
void Self::IsPrivate(bool value) {
    isPrivate = value;
}

// -------------------------------------------------------------------
// IsPersistent
// -------------------------------------------------------------------
bool Self::IsPersistent() const {
    return isPersistent;
}

// -------------------------------------------------------------------
// IsPersistent
// -------------------------------------------------------------------
void Self::IsPersistent(bool value) {
    isPersistent = value;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<std::string> Self::ToString() const {
    auto returned = boost::make_shared<std::string>();
    returned->append("[RoomVar: ");
    returned->append(Name()->c_str());
    returned->append(", type: ");
    returned->append(TypeAsString()->c_str());
    returned->append(", value: ");
    returned->append(ValueAsString()->c_str());
    returned->append("]");
    return returned;
}

// -------------------------------------------------------------------
// ToSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> Self::ToSFSArray() const {
    auto arr = BaseVariable::ToSFSArray();

    // isPrivate (3)
    arr->AddBool(boost::make_shared<bool>(IsPrivate()));

    // isPersistent (4)
    arr->AddBool(boost::make_shared<bool>(IsPersistent()));

    return arr;
}

// -----
// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<std::string> Self::Name() const {
    return BaseVariable::Name();
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
VariableType Self::Type() const {
    return BaseVariable::Type();
}

// -------------------------------------------------------------------
// Value
// -------------------------------------------------------------------
boost::shared_ptr<void> Self::Value() const {
    return BaseVariable::Value();
}

// -------------------------------------------------------------------
// GetBoolValue
// -------------------------------------------------------------------
boost::shared_ptr<bool> Self::GetBoolValue() const {
    return BaseVariable::GetBoolValue();
}

// -------------------------------------------------------------------
// GetIntValue
// -------------------------------------------------------------------
boost::shared_ptr<std::int32_t> Self::GetIntValue() const {
    return BaseVariable::GetIntValue();
}

// -------------------------------------------------------------------
// GetDoubleValue
// -------------------------------------------------------------------
boost::shared_ptr<double> Self::GetDoubleValue() const {
    return BaseVariable::GetDoubleValue();
}

// -------------------------------------------------------------------
// GetStringValue
// -------------------------------------------------------------------
boost::shared_ptr<std::string> Self::GetStringValue() const {
    return BaseVariable::GetStringValue();
}

// -------------------------------------------------------------------
// GetSFSObjectValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> Self::GetSFSObjectValue() const {
    return BaseVariable::GetSFSObjectValue();
}

// -------------------------------------------------------------------
// GetSFSArrayValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> Self::GetSFSArrayValue() const {
    return BaseVariable::GetSFSArrayValue();
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool Self::IsNull() const {
    return BaseVariable::IsNull();
}
} // namespace Variables
} // namespace Entities
} // namespace Sfs2X
