// ===================================================================
//
// Description
//        Contains the implementation of MMOItemVariable
//
// Revision history
//        Date            Description
//        30-Nov-2013        First version
//
// ===================================================================
#include "MMOItemVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<IMMOItemVariable>
MMOItemVariable::FromSFSArray(const boost::shared_ptr<ISFSArray>& sfsa) {
    boost::shared_ptr<IMMOItemVariable> variable(
        new MMOItemVariable(*(sfsa->GetUtfString(0)), // name
                            sfsa->GetElementAt(2),    // typed value
                            sfsa->GetByte(1)          // type id
                            ));

    return variable;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
MMOItemVariable::MMOItemVariable(const std::string& name,
                                 const boost::shared_ptr<void>& val, int type)
    : BaseVariable(name, val, type) {
    // Nothing else to do
}

MMOItemVariable::MMOItemVariable(const std::string& name,
                                 const boost::shared_ptr<std::int64_t>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

MMOItemVariable::MMOItemVariable(const std::string& name,
                                 const boost::shared_ptr<std::uint64_t>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

MMOItemVariable::MMOItemVariable(const std::string& name,
                                 const boost::shared_ptr<std::int32_t>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

MMOItemVariable::MMOItemVariable(const std::string& name,
                                 const boost::shared_ptr<std::uint32_t>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

MMOItemVariable::MMOItemVariable(const std::string& name,
                                 const boost::shared_ptr<bool>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

MMOItemVariable::MMOItemVariable(const std::string& name,
                                 const boost::shared_ptr<double>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

MMOItemVariable::MMOItemVariable(const std::string& name,
                                 const boost::shared_ptr<std::string>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

MMOItemVariable::MMOItemVariable(const std::string& name,
                                 const boost::shared_ptr<SFSObject>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

MMOItemVariable::MMOItemVariable(const std::string& name,
                                 const boost::shared_ptr<SFSArray>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
MMOItemVariable::~MMOItemVariable() {
    this->Name() = boost::shared_ptr<std::string>();
    this->Value() = boost::shared_ptr<void>();
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<std::string> MMOItemVariable::Name() const {
    return BaseVariable::Name();
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
VariableType MMOItemVariable::Type() const {
    return BaseVariable::Type();
}

// -------------------------------------------------------------------
// Value
// -------------------------------------------------------------------
boost::shared_ptr<void> MMOItemVariable::Value() const {
    return BaseVariable::Value();
}

// -------------------------------------------------------------------
// GetBoolValue
// -------------------------------------------------------------------
boost::shared_ptr<bool> MMOItemVariable::GetBoolValue() const {
    return BaseVariable::GetBoolValue();
}

// -------------------------------------------------------------------
// GetIntValue
// -------------------------------------------------------------------
boost::shared_ptr<std::int32_t> MMOItemVariable::GetIntValue() const {
    return BaseVariable::GetIntValue();
}

// -------------------------------------------------------------------
// GetDoubleValue
// -------------------------------------------------------------------
boost::shared_ptr<double> MMOItemVariable::GetDoubleValue() const {
    return BaseVariable::GetDoubleValue();
}

// -------------------------------------------------------------------
// GetStringValue
// -------------------------------------------------------------------
boost::shared_ptr<std::string> MMOItemVariable::GetStringValue() const {
    return BaseVariable::GetStringValue();
}

// -------------------------------------------------------------------
// GetSFSObjectValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> MMOItemVariable::GetSFSObjectValue() const {
    return BaseVariable::GetSFSObjectValue();
}

// -------------------------------------------------------------------
// GetSFSArrayValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> MMOItemVariable::GetSFSArrayValue() const {
    return BaseVariable::GetSFSArrayValue();
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool MMOItemVariable::IsNull() const {
    return BaseVariable::IsNull();
}

// -------------------------------------------------------------------
// ToSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> MMOItemVariable::ToSFSArray() const {
    return BaseVariable::ToSFSArray();
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<std::string> MMOItemVariable::ToString() const {
    boost::shared_ptr<std::string> returned(new std::string());
    returned->append("[MMOItemVar: ");
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
