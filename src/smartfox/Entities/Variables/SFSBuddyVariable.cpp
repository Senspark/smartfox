// ===================================================================
//
// Description
//        Contains the implementation of SFSBuddyVariable
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "SFSBuddyVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {
using Self = SFSBuddyVariable;

boost::shared_ptr<std::string> Self::OFFLINE_PREFIX(new std::string("$"));

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<BuddyVariable>
Self::FromSFSArray(const boost::shared_ptr<ISFSArray>& sfsa) {
    return boost::make_shared<Self>(sfsa->GetUtfString(0), // name
                                    sfsa->GetElementAt(2), // typed value
                                    sfsa->GetByte(1)       // type id
    );
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::SFSBuddyVariable(const std::string& name,
                       const boost::shared_ptr<void>& val, int type)
    : BaseVariable(name, val, type) {
    // Nothing else to do
}

Self::SFSBuddyVariable(const boost::shared_ptr<std::string>& name,
                       const boost::shared_ptr<void>& val, int type)
    : BaseVariable(*name, val, type) {
    // Nothing else to do
}

Self::SFSBuddyVariable(const std::string& name,
                       const boost::shared_ptr<std::int64_t>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

Self::SFSBuddyVariable(const std::string& name,
                       const boost::shared_ptr<std::uint64_t>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

Self::SFSBuddyVariable(const std::string& name,
                       const boost::shared_ptr<std::int32_t>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

Self::SFSBuddyVariable(const std::string& name,
                       const boost::shared_ptr<std::uint32_t>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

Self::SFSBuddyVariable(const std::string& name,
                       const boost::shared_ptr<bool>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

Self::SFSBuddyVariable(const std::string& name,
                       const boost::shared_ptr<double>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

Self::SFSBuddyVariable(const std::string& name,
                       const boost::shared_ptr<std::string>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

Self::SFSBuddyVariable(const std::string& name,
                       const boost::shared_ptr<SFSObject>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

Self::SFSBuddyVariable(const std::string& name,
                       const boost::shared_ptr<SFSArray>& val)
    : BaseVariable(name, val) {
    // Nothing else to do
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
Self::~SFSBuddyVariable() {
    this->Name() = boost::shared_ptr<std::string>();
    this->Value() = boost::shared_ptr<void>();
}

// -------------------------------------------------------------------
// IsOffline
// -------------------------------------------------------------------
bool Self::IsOffline() const {
    return (Name()->find("$") == 0);
}

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

// -------------------------------------------------------------------
// ToSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> Self::ToSFSArray() const {
    return BaseVariable::ToSFSArray();
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<std::string> Self::ToString() const {
    auto returned = boost::make_shared<std::string>();
    returned->append("[BuddyVar: ");
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
