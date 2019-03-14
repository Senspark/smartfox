// ===================================================================
//
// Description
//        Contains the implementation of BaseRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "BaseRequest.h"
#include "ExtensionRequest.h"

namespace Sfs2X {
namespace Requests {
using Self = BaseRequest;

boost::shared_ptr<std::string> Self::KEY_ERROR_CODE(new std::string("ec"));
boost::shared_ptr<std::string> Self::KEY_ERROR_PARAMS(new std::string("ep"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::BaseRequest() {
    sfso = SFSObject::NewInstance();
    targetController = 0;
    isEncrypted = false;
    id = 0;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::BaseRequest(RequestType tp) {
    sfso = SFSObject::NewInstance();
    targetController = 0;
    isEncrypted = false;
    id = static_cast<int>(tp);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::BaseRequest(int id) {
    sfso = SFSObject::NewInstance();
    targetController = 0;
    isEncrypted = false;
    this->id = id;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
Self::~BaseRequest() {}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
int Self::Id() const {
    return id;
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
void Self::Id(int value) {
    id = value;
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
RequestType Self::Type() const {
    return static_cast<RequestType>(id);
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
void Self::Type(RequestType value) {
    id = static_cast<int>(value);
}

// IRequest implementation

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void Self::Validate(const boost::shared_ptr<SmartFox>& sfs) {
    // Override in child class
    // Throws exception if invalid request.
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void Self::Execute(const boost::shared_ptr<SmartFox>& sfs) {
    // Override in child class
}

// -------------------------------------------------------------------
// TargetController
// -------------------------------------------------------------------
int Self::TargetController() const {
    return targetController;
}

// -------------------------------------------------------------------
// TargetController
// -------------------------------------------------------------------
void Self::TargetController(int value) {
    targetController = value;
}

// -------------------------------------------------------------------
// IsEncrypted
// -------------------------------------------------------------------
bool Self::IsEncrypted() const {
    return isEncrypted;
}

// -------------------------------------------------------------------
// IsEncrypted
// -------------------------------------------------------------------
void Self::IsEncrypted(bool value) {
    isEncrypted = value;
}

// -------------------------------------------------------------------
// Message
// -------------------------------------------------------------------
boost::shared_ptr<IMessage> Self::Message() const {
    auto message = boost::make_shared<Bitswarm::Message>();
    message->Id(id);
    message->IsEncrypted(isEncrypted);
    message->TargetController(targetController);
    message->Content(sfso);

    /*
     * An extension request carries the UseUDP flag
     * Check if this is the case and set the flag on the message object
     * This will tell the bitswarm engine how to handle the socket write (TCP vs
     * UDP)
     */
    if (dynamic_cast<const ExtensionRequest*>(this) != nullptr) {
        message->IsUDP((dynamic_cast<const ExtensionRequest*>(this))->UseUDP());
    }
    return message;
}
} // namespace Requests
} // namespace Sfs2X
