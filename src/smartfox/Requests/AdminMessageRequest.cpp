// ===================================================================
//
// Description
//        Contains the implementation of AdminMessageRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "AdminMessageRequest.h"

namespace Sfs2X {
namespace Requests {
// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
AdminMessageRequest::AdminMessageRequest(
    const std::string& message,
    const boost::shared_ptr<MessageRecipientMode>& recipientMode,
    const boost::shared_ptr<ISFSObject>& parameters) {
    if (recipientMode == NULL) {
        boost::throw_exception(boost::enable_error_info(
            std::runtime_error("RecipientMode cannot be null!")));
    }

    this->type = static_cast<int>(GENERICMESSAGETYPE_ADMIN_MSG);
    this->message = boost::shared_ptr<std::string>(new std::string(message));
    this->parameters = parameters;
    this->recipientInt = boost::make_shared<int>(recipientMode->TargetInt());
    this->recipientUser = recipientMode->TargetUser();
    this->recipientRoom = recipientMode->TargetRoom();
    this->recipientString = recipientMode->TargetString();
    this->recipientUsersCollection = recipientMode->TargetUsersCollection();
    this->sendMode = recipientMode->Mode();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
AdminMessageRequest::AdminMessageRequest(
    const std::string& message,
    const boost::shared_ptr<MessageRecipientMode>& recipientMode) {
    if (recipientMode == NULL) {
        boost::throw_exception(boost::enable_error_info(
            std::runtime_error("RecipientMode cannot be null!")));
    }

    this->type = (long int)GENERICMESSAGETYPE_ADMIN_MSG;
    this->message = boost::shared_ptr<std::string>(new std::string(message));
    this->parameters = boost::shared_ptr<ISFSObject>();
    this->recipientInt = boost::make_shared<int>(recipientMode->TargetInt());
    this->recipientUser = recipientMode->TargetUser();
    this->recipientRoom = recipientMode->TargetRoom();
    this->recipientString = recipientMode->TargetString();
    this->recipientUsersCollection = recipientMode->TargetUsersCollection();
    this->sendMode = recipientMode->Mode();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
AdminMessageRequest::~AdminMessageRequest() {}
} // namespace Requests
} // namespace Sfs2X
