// ===================================================================
//
// Description
//        Contains the implementation of SFSUserVariable
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include <typeinfo>

#include "SFSUserVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {
// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<UserVariable>
SFSUserVariable::FromSFSArray(const boost::shared_ptr<ISFSArray>& sfsa) {
    auto variable = boost::make_shared<SFSUserVariable>(
        *(sfsa->GetUtfString(0)), // name
        sfsa->GetElementAt(2),    // typed value
        sfsa->GetByte(1)          // type id
    );

    // Since SFS v2.12.0 we're getting a new element at position #3
    if (sfsa->Size() > 3)
        variable->IsPrivate(sfsa->GetBool(3)); // 'private' flag

    return variable;
}

// -------------------------------------------------------------------
// newPrivateVariable
// -------------------------------------------------------------------
boost::shared_ptr<SFSUserVariable> SFSUserVariable::newPrivateVariable(
    const std::string& name, const boost::shared_ptr<std::int64_t>& val) {
    boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
    uv->IsPrivate(true);
    return uv;
}

boost::shared_ptr<SFSUserVariable> SFSUserVariable::newPrivateVariable(
    const std::string& name, const boost::shared_ptr<std::uint64_t>& val) {
    boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
    uv->IsPrivate(true);
    return uv;
}

boost::shared_ptr<SFSUserVariable> SFSUserVariable::newPrivateVariable(
    const std::string& name, const boost::shared_ptr<std::int32_t>& val) {
    boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
    uv->IsPrivate(true);
    return uv;
}

boost::shared_ptr<SFSUserVariable> SFSUserVariable::newPrivateVariable(
    const std::string& name, const boost::shared_ptr<std::uint32_t>& val) {
    boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
    uv->IsPrivate(true);
    return uv;
}

boost::shared_ptr<SFSUserVariable>
SFSUserVariable::newPrivateVariable(const std::string& name,
                                    const boost::shared_ptr<bool>& val) {
    boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
    uv->IsPrivate(true);
    return uv;
}

boost::shared_ptr<SFSUserVariable>
SFSUserVariable::newPrivateVariable(const std::string& name,
                                    const boost::shared_ptr<double>& val) {
    boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
    uv->IsPrivate(true);
    return uv;
}

boost::shared_ptr<SFSUserVariable>
SFSUserVariable::newPrivateVariable(const std::string& name,
                                    const boost::shared_ptr<std::string>& val) {
    boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
    uv->IsPrivate(true);

    return uv;
}

boost::shared_ptr<SFSUserVariable>
SFSUserVariable::newPrivateVariable(const std::string& name,
                                    const boost::shared_ptr<SFSObject>& val) {
    boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
    uv->IsPrivate(true);
    return uv;
}

boost::shared_ptr<SFSUserVariable>
SFSUserVariable::newPrivateVariable(const std::string& name,
                                    const boost::shared_ptr<SFSArray>& val) {
    boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
    uv->IsPrivate(true);

    return uv;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSUserVariable::SFSUserVariable(const std::string& name,
                                 const boost::shared_ptr<std::int64_t>& val)
    : BaseVariable(name, val) {
    isPrivate = false;
}

SFSUserVariable::SFSUserVariable(const std::string& name,
                                 const boost::shared_ptr<std::uint64_t>& val)
    : BaseVariable(name, val) {
    isPrivate = false;
}

SFSUserVariable::SFSUserVariable(const std::string& name,
                                 const boost::shared_ptr<std::int32_t>& val)
    : BaseVariable(name, val) {
    isPrivate = false;
}

SFSUserVariable::SFSUserVariable(const std::string& name,
                                 const boost::shared_ptr<std::uint32_t>& val)
    : BaseVariable(name, val) {
    isPrivate = false;
}

SFSUserVariable::SFSUserVariable(const std::string& name,
                                 const boost::shared_ptr<bool>& val)
    : BaseVariable(name, val) {
    isPrivate = false;
}

SFSUserVariable::SFSUserVariable(const std::string& name,
                                 const boost::shared_ptr<double>& val)
    : BaseVariable(name, val) {
    isPrivate = false;
}

SFSUserVariable::SFSUserVariable(const std::string& name,
                                 const boost::shared_ptr<std::string>& val)
    : BaseVariable(name, val) {
    isPrivate = false;
}

SFSUserVariable::SFSUserVariable(const std::string& name,
                                 const boost::shared_ptr<SFSObject>& val)
    : BaseVariable(name, val) {
    isPrivate = false;
}

SFSUserVariable::SFSUserVariable(const std::string& name,
                                 const boost::shared_ptr<SFSArray>& val)
    : BaseVariable(name, val) {
    isPrivate = false;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSUserVariable::SFSUserVariable(const std::string& name,
                                 const boost::shared_ptr<void>& val, int type)
    : BaseVariable(name, val, type) {
    isPrivate = false;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSUserVariable::~SFSUserVariable() {
    this->Name() = boost::shared_ptr<std::string>();
    this->Value() = boost::shared_ptr<void>();
}

// -------------------------------------------------------------------
// IsPrivate
// -------------------------------------------------------------------
bool SFSUserVariable::IsPrivate() const {
    return isPrivate;
}

// -------------------------------------------------------------------
// IsPrivate
// -------------------------------------------------------------------
void SFSUserVariable::IsPrivate(bool value) {
    isPrivate = value;
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSUserVariable::Name() const {
    return BaseVariable::Name();
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
VariableType SFSUserVariable::Type() const {
    return BaseVariable::Type();
}

// -------------------------------------------------------------------
// Value
// -------------------------------------------------------------------
boost::shared_ptr<void> SFSUserVariable::Value() const {
    return BaseVariable::Value();
}

// -------------------------------------------------------------------
// GetBoolValue
// -------------------------------------------------------------------
boost::shared_ptr<bool> SFSUserVariable::GetBoolValue() const {
    return BaseVariable::GetBoolValue();
}

// -------------------------------------------------------------------
// GetIntValue
// -------------------------------------------------------------------
boost::shared_ptr<std::int32_t> SFSUserVariable::GetIntValue() const {
    return BaseVariable::GetIntValue();
}

// -------------------------------------------------------------------
// GetDoubleValue
// -------------------------------------------------------------------
boost::shared_ptr<double> SFSUserVariable::GetDoubleValue() const {
    return BaseVariable::GetDoubleValue();
}

// -------------------------------------------------------------------
// GetStringValue
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSUserVariable::GetStringValue() const {
    return BaseVariable::GetStringValue();
}

// -------------------------------------------------------------------
// GetSFSObjectValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> SFSUserVariable::GetSFSObjectValue() const {
    return BaseVariable::GetSFSObjectValue();
}

// -------------------------------------------------------------------
// GetSFSArrayValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> SFSUserVariable::GetSFSArrayValue() const {
    return BaseVariable::GetSFSArrayValue();
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool SFSUserVariable::IsNull() const {
    return BaseVariable::IsNull();
}

// -------------------------------------------------------------------
// ToSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> SFSUserVariable::ToSFSArray() const {
    auto sfsa = BaseVariable::ToSFSArray();

    // private flag (3)
    sfsa->AddBool(isPrivate);

    return sfsa;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSUserVariable::ToString() const {
    auto returned = boost::make_shared<std::string>();
    returned->append("[UserVar: ");
    returned->append(Name()->c_str());
    returned->append(", type: ");
    returned->append(TypeAsString()->c_str());
    returned->append(", value: ");
    returned->append(ValueAsString()->c_str());
    returned->append("]");
    return returned;
}
} // namespace Variables
} // namespace Entities
} // namespace Sfs2X
