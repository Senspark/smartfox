// ===================================================================
//
// Description
//        Contains the implementation of SFSDataWrapper
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================

#include "SFSDataWrapper.h"
#include "ISFSObject.h"

namespace Sfs2X {
namespace Entities {
namespace Data {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSDataWrapper::SFSDataWrapper(int type, const boost::shared_ptr<void>& data) {
    this->type = type;
    this->data = data;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSDataWrapper::SFSDataWrapper(SFSDataType tp,
                               const boost::shared_ptr<void>& data) {
    this->type = static_cast<int>(tp);
    this->data = data;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSDataWrapper::~SFSDataWrapper() {
    this->data.reset();
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
int SFSDataWrapper::Type() const {
    return type;
}

// -------------------------------------------------------------------
// Data
// -------------------------------------------------------------------
const boost::shared_ptr<void>& SFSDataWrapper::Data() const {
    return data;
}
} // namespace Data
} // namespace Entities
} // namespace Sfs2X
