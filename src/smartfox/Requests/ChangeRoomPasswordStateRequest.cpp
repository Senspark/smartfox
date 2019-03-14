// ===================================================================
//
// Description
//        Contains the implementation of ChangeRoomPasswordStateRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "ChangeRoomPasswordStateRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<std::string>
    ChangeRoomPasswordStateRequest::KEY_ROOM(new std::string("r"));
boost::shared_ptr<std::string>
    ChangeRoomPasswordStateRequest::KEY_PASS(new std::string("p"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ChangeRoomPasswordStateRequest::ChangeRoomPasswordStateRequest(
    const boost::shared_ptr<Room>& room, const std::string& newPass)
    : BaseRequest(RequestType_ChangeRoomPassword) {
    this->room = room;
    this->newPass = boost::shared_ptr<std::string>(new std::string(newPass));
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ChangeRoomPasswordStateRequest::~ChangeRoomPasswordStateRequest() {}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void ChangeRoomPasswordStateRequest::Validate(
    const boost::shared_ptr<SmartFox>& sfs) {
    boost::shared_ptr<list<string>> errors(new list<string>());

    // Missing room id
    if (this->room == NULL)
        errors->push_back("Provided room is null");

    if (newPass == NULL)
        errors->push_back(
            "Invalid new room password. It must be a non-null string.");

    if (errors->size() > 0) {
        boost::shared_ptr<std::string> message(
            new std::string("ChangePassState request error"));
        boost::shared_ptr<SFSValidationError> exception(
            new SFSValidationError(message, errors));
        throw exception;
    }
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void ChangeRoomPasswordStateRequest::Execute(
    const boost::shared_ptr<SmartFox>& sfs) {
    sfso->PutInt(KEY_ROOM, static_cast<std::int32_t>(room->Id()));
    sfso->PutUtfString(KEY_PASS, newPass);
}
} // namespace Requests
} // namespace Sfs2X
