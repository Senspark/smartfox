// ===================================================================
//
// Description
//        Contains the implementation of BanUserRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "BanUserRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<std::string>
    BanUserRequest::KEY_USER_ID(new std::string("u"));
boost::shared_ptr<std::string>
    BanUserRequest::KEY_MESSAGE(new std::string("m"));
boost::shared_ptr<std::string> BanUserRequest::KEY_DELAY(new std::string("d"));
boost::shared_ptr<std::string>
    BanUserRequest::KEY_BAN_MODE(new std::string("b"));
boost::shared_ptr<std::string>
    BanUserRequest::KEY_BAN_DURATION_HOURS(new std::string("dh"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BanUserRequest::BanUserRequest(long int userId)
    : BaseRequest(RequestType_BanUser) {
    Init(userId, "", BANMODE_BY_NAME, 5, 0);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BanUserRequest::BanUserRequest(long int userId, const std::string& message)
    : BaseRequest(RequestType_BanUser) {
    Init(userId, message, BANMODE_BY_NAME, 5, 0);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BanUserRequest::BanUserRequest(long int userId, const std::string& message,
                               BanMode banMode)
    : BaseRequest(RequestType_BanUser) {
    Init(userId, message, banMode, 5, 0);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BanUserRequest::BanUserRequest(long int userId, const std::string& message,
                               BanMode banMode, long int delaySeconds)
    : BaseRequest(RequestType_BanUser) {
    Init(userId, message, banMode, delaySeconds, 0);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BanUserRequest::BanUserRequest(long int userId, const std::string& message,
                               BanMode banMode, long int delaySeconds,
                               long int durationHours)
    : BaseRequest(RequestType_BanUser) {
    Init(userId, message, banMode, delaySeconds, durationHours);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
BanUserRequest::~BanUserRequest() {}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void BanUserRequest::Init(long int userId, const std::string& message,
                          BanMode banMode, long int delaySeconds,
                          long int durationHours) {
    this->userId = userId;
    this->message = boost::shared_ptr<std::string>(new std::string(message));
    this->banMode = banMode;
    this->delay = delaySeconds;
    this->durationHours = durationHours;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void BanUserRequest::Validate(const boost::shared_ptr<SmartFox>& sfs) {
    boost::shared_ptr<list<string>> errors(new list<string>());

    // No valudation needed; will be done by the server
    /*
    if (!sfs->MySelf()->IsModerator() && !sfs->MySelf()->IsAdmin())
        errors->push_back("You don't have enough permissions to execute this
    request.");
    */

    if (errors->size() > 0) {
        boost::shared_ptr<std::string> message(
            new std::string("BanUser request error"));
        boost::shared_ptr<SFSValidationError> exception(
            new SFSValidationError(message, errors));
        throw exception;
    }
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void BanUserRequest::Execute(const boost::shared_ptr<SmartFox>& sfs) {
    sfso->PutInt(KEY_USER_ID, static_cast<std::int32_t>(userId));
    sfso->PutInt(KEY_DELAY, static_cast<std::int32_t>(delay));
    sfso->PutInt(KEY_BAN_MODE, static_cast<std::int32_t>(banMode));
    sfso->PutInt(KEY_BAN_DURATION_HOURS,
                 static_cast<std::int32_t>(durationHours));
    if (message != NULL && message->size() > 0)
        sfso->PutUtfString(KEY_MESSAGE, message);
}
} // namespace Requests
} // namespace Sfs2X
