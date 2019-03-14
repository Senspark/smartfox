// ===================================================================
//
// Description
//        Contains the implementation of PlayerToSpectatorRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "PlayerToSpectatorRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<std::string>
    PlayerToSpectatorRequest::KEY_ROOM_ID(new std::string("r"));
boost::shared_ptr<std::string>
    PlayerToSpectatorRequest::KEY_USER_ID(new std::string("u"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
PlayerToSpectatorRequest::PlayerToSpectatorRequest()
    : BaseRequest(RequestType_PlayerToSpectator) {
    Init(boost::shared_ptr<Room>());
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
PlayerToSpectatorRequest::PlayerToSpectatorRequest(
    const boost::shared_ptr<Room>& targetRoom)
    : BaseRequest(RequestType_PlayerToSpectator) {
    Init(targetRoom);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
PlayerToSpectatorRequest::~PlayerToSpectatorRequest() {}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void PlayerToSpectatorRequest::Init(const boost::shared_ptr<Room>& targetRoom) {
    this->room = targetRoom;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void PlayerToSpectatorRequest::Validate(
    const boost::shared_ptr<SmartFox>& sfs) {
    boost::shared_ptr<list<string>> errors(new list<string>());

    // No validation needed
    if (sfs->JoinedRooms()->size() < 1)
        errors->push_back("You are not joined in any rooms");

    if (errors->size() > 0) {
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
void PlayerToSpectatorRequest::Execute(const boost::shared_ptr<SmartFox>& sfs) {
    if (room == NULL) {
        room = sfs->LastJoinedRoom();
    }
    sfso->PutInt(KEY_ROOM_ID, static_cast<std::int32_t>(room->Id()));
}
} // namespace Requests
} // namespace Sfs2X
