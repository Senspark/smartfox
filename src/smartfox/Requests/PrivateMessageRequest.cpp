// ===================================================================
//
// Description
//        Contains the implementation of PrivateMessageRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "PrivateMessageRequest.h"

namespace Sfs2X {
namespace Requests {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
PrivateMessageRequest::PrivateMessageRequest(
    const std::string& message, int recipientId,
    boost::shared_ptr<ISFSObject> parameters) {
    this->type = (long int)GENERICMESSAGETYPE_PRIVATE_MSG;
    this->message = boost::make_shared<std::string>(message);
    this->recipientInt = boost::make_shared<int>(recipientId);
    this->parameters = parameters;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
PrivateMessageRequest::PrivateMessageRequest(const std::string& message,
                                             int recipientId) {
    this->type = (long int)GENERICMESSAGETYPE_PRIVATE_MSG;
    this->message = boost::make_shared<std::string>(message);
    this->recipientInt = boost::make_shared<int>(recipientId);
    this->parameters = boost::shared_ptr<ISFSObject>();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
PrivateMessageRequest::~PrivateMessageRequest() {}

} // namespace Requests
} // namespace Sfs2X
