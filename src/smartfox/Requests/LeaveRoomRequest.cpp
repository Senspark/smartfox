// ===================================================================
//
// Description
//        Contains the implementation of LeaveRoomRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "LeaveRoomRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<std::string>
    LeaveRoomRequest::KEY_ROOM_ID(new std::string("r"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
LeaveRoomRequest::LeaveRoomRequest(const boost::shared_ptr<Room>& room)
    : BaseRequest(RequestType_LeaveRoom) {
    Init(room);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
LeaveRoomRequest::LeaveRoomRequest()
    : BaseRequest(RequestType_LeaveRoom) {
    Init(boost::shared_ptr<Room>());
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
LeaveRoomRequest::~LeaveRoomRequest() {}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void LeaveRoomRequest::Init(const boost::shared_ptr<Room>& room) {
    this->room = room;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void LeaveRoomRequest::Validate(const boost::shared_ptr<SmartFox>& sfs) {
    if (sfs->JoinedRooms()->size() < 1) {
        boost::shared_ptr<list<string>> errors(new list<string>());
        errors->push_back("You are not joined in any rooms");

        boost::shared_ptr<std::string> message(
            new std::string("LeaveRoom request error"));
        boost::shared_ptr<SFSValidationError> exception(
            new SFSValidationError(message, errors));
        throw exception;
    }
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void LeaveRoomRequest::Execute(const boost::shared_ptr<SmartFox>& sfs) {
    if (room != NULL) {
        this->sfso->PutInt(KEY_ROOM_ID,
                           static_cast<std::int32_t>(this->room->Id()));
    }
}
} // namespace Requests
} // namespace Sfs2X
