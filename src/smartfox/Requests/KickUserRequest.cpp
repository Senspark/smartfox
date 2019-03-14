// ===================================================================
//
// Description
//        Contains the implementation of KickUserRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "KickUserRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<std::string>
    KickUserRequest::KEY_USER_ID(new std::string("u"));
boost::shared_ptr<std::string>
    KickUserRequest::KEY_MESSAGE(new std::string("m"));
boost::shared_ptr<std::string> KickUserRequest::KEY_DELAY(new std::string("d"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
KickUserRequest::KickUserRequest(long int userId)
    : BaseRequest(RequestType_KickUser) {
    Init(userId, "", 5);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
KickUserRequest::KickUserRequest(long int userId, const std::string& message)
    : BaseRequest(RequestType_KickUser) {
    Init(userId, message, 5);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
KickUserRequest::KickUserRequest(long int userId, const std::string& message,
                                 long int delaySeconds)
    : BaseRequest(RequestType_KickUser) {
    Init(userId, message, delaySeconds);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
KickUserRequest::~KickUserRequest() {}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void KickUserRequest::Init(long int userId, const std::string& message,
                           long int delaySeconds) {
    this->userId = userId;
    this->message = boost::shared_ptr<std::string>(new std::string(message));
    this->delay = delaySeconds;

    // avoid negatives
    if (this->delay < 0)
        this->delay = 0;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void KickUserRequest::Validate(const boost::shared_ptr<SmartFox>& sfs) {
    boost::shared_ptr<list<string>> errors(new list<string>());

    // No valudation needed; will be done by the server
    /*
    if (!sfs->MySelf()->IsModerator() && !sfs->MySelf()->IsAdmin())
        errors->push_back("You don't have enough permissions to execute this
    request.");
    */

    if (errors->size() > 0) {
        boost::shared_ptr<std::string> message(
            new std::string("KickUser request error"));
        boost::shared_ptr<SFSValidationError> exception(
            new SFSValidationError(message, errors));
        throw exception;
    }
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void KickUserRequest::Execute(const boost::shared_ptr<SmartFox>& sfs) {
    sfso->PutInt(KEY_USER_ID, static_cast<std::int32_t>(userId));
    sfso->PutInt(KEY_DELAY, static_cast<std::int32_t>(delay));
    if (message != NULL && message->size() > 0) {
        sfso->PutUtfString(KEY_MESSAGE, message);
    }
}
} // namespace Requests
} // namespace Sfs2X
