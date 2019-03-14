// ===================================================================
//
// Description
//        Contains the implementation of ChangeRoomNameRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "ChangeRoomNameRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<std::string>
    ChangeRoomNameRequest::KEY_ROOM(new std::string("r"));
boost::shared_ptr<std::string>
    ChangeRoomNameRequest::KEY_NAME(new std::string("n"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ChangeRoomNameRequest::ChangeRoomNameRequest(
    const boost::shared_ptr<Room>& room, const std::string& newName)
    : BaseRequest(RequestType_ChangeRoomName) {
    this->room = room;
    this->newName = boost::shared_ptr<std::string>(new std::string(newName));
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ChangeRoomNameRequest::~ChangeRoomNameRequest() {}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void ChangeRoomNameRequest::Validate(const boost::shared_ptr<SmartFox>& sfs) {
    boost::shared_ptr<list<string>> errors(new list<string>());

    // Missing room id
    if (this->room == NULL)
        errors->push_back("Provided room is null");

    if (this->newName == NULL || this->newName->size() == 0)
        errors->push_back("Invalid new room name. It must be a non-null and "
                          "non-empty string.");

    if (errors->size() > 0) {
        boost::shared_ptr<std::string> message(
            new std::string("ChangeRoomName request error"));
        boost::shared_ptr<SFSValidationError> exception(
            new SFSValidationError(message, errors));
        throw exception;
    }
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void ChangeRoomNameRequest::Execute(const boost::shared_ptr<SmartFox>& sfs) {
    sfso->PutInt(KEY_ROOM, static_cast<std::int32_t>(room->Id()));
    sfso->PutUtfString(KEY_NAME, newName);
}
} // namespace Requests
} // namespace Sfs2X
