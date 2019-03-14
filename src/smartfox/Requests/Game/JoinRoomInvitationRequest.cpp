// ===================================================================
//
// Description
//        Contains the implementation of JoinRoomInvitationRequest
//
// Revision history
//        Date            Description
//        30-Nov-2016        First version
//
// ===================================================================
#include "JoinRoomInvitationRequest.h"

namespace Sfs2X {
namespace Requests {
namespace Game {

boost::shared_ptr<std::string>
    JoinRoomInvitationRequest::KEY_ROOM_ID(new std::string("r"));
boost::shared_ptr<std::string>
    JoinRoomInvitationRequest::KEY_EXPIRY_SECONDS(new std::string("es"));
boost::shared_ptr<std::string>
    JoinRoomInvitationRequest::KEY_INVITED_NAMES(new std::string("in"));
boost::shared_ptr<std::string>
    JoinRoomInvitationRequest::KEY_AS_SPECT(new std::string("as"));
boost::shared_ptr<std::string>
    JoinRoomInvitationRequest::KEY_OPTIONAL_PARAMS(new std::string("op"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomInvitationRequest::JoinRoomInvitationRequest(
    const boost::shared_ptr<Room>& targetRoom,
    boost::shared_ptr<list<string>> invitedUserNames,
    boost::shared_ptr<ISFSObject> parameters, long int expirySeconds,
    bool asSpectator)
    : BaseRequest(RequestType_JoinRoomInvite) {
    Init(targetRoom, invitedUserNames, parameters, expirySeconds, asSpectator);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomInvitationRequest::JoinRoomInvitationRequest(
    const boost::shared_ptr<Room>& targetRoom,
    boost::shared_ptr<list<string>> invitedUserNames,
    boost::shared_ptr<ISFSObject> parameters, long int expirySeconds)
    : BaseRequest(RequestType_JoinRoomInvite) {
    Init(targetRoom, invitedUserNames, parameters, expirySeconds, false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomInvitationRequest::JoinRoomInvitationRequest(
    const boost::shared_ptr<Room>& targetRoom,
    boost::shared_ptr<list<string>> invitedUserNames,
    boost::shared_ptr<ISFSObject> parameters)
    : BaseRequest(RequestType_JoinRoomInvite) {
    Init(targetRoom, invitedUserNames, parameters, 30, false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomInvitationRequest::JoinRoomInvitationRequest(
    const boost::shared_ptr<Room>& targetRoom,
    boost::shared_ptr<list<string>> invitedUserNames)
    : BaseRequest(RequestType_JoinRoomInvite) {
    Init(targetRoom, invitedUserNames, boost::shared_ptr<ISFSObject>(), 30,
         false);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
JoinRoomInvitationRequest::~JoinRoomInvitationRequest() {
    if (targetRoom != NULL) {
        targetRoom = boost::shared_ptr<Room>();
    }

    if (invitedUserNames != NULL) {
        invitedUserNames->clear();
        invitedUserNames = boost::shared_ptr<list<string>>();
    }
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void JoinRoomInvitationRequest::Init(
    const boost::shared_ptr<Room>& targetRoom,
    boost::shared_ptr<list<string>> invitedUserNames,
    boost::shared_ptr<ISFSObject> parameters, long int expirySeconds,
    bool asSpectator) {
    this->targetRoom = targetRoom;
    this->invitedUserNames = invitedUserNames;
    this->expirySeconds = expirySeconds;
    this->asSpectator = asSpectator;

    this->parameters = (parameters != NULL)
                           ? parameters
                           : boost::shared_ptr<ISFSObject>(new SFSObject());
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void JoinRoomInvitationRequest::Validate(
    const boost::shared_ptr<SmartFox>& sfs) {
    boost::shared_ptr<list<string>> errors(new list<string>());

    if (targetRoom == NULL)
        errors->push_back("Missing target room");

    if (invitedUserNames == NULL || invitedUserNames->size() < 1)
        errors->push_back("No invitees provided");

    if (errors->size() > 0) {
        boost::shared_ptr<std::string> message(
            new std::string("JoinRoomInvitationRequest request error"));
        boost::shared_ptr<SFSValidationError> exception(
            new SFSValidationError(message, errors));
        throw exception;
    }
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void JoinRoomInvitationRequest::Execute(
    const boost::shared_ptr<SmartFox>& sfs) {
    sfso->PutInt(KEY_ROOM_ID, static_cast<std::int32_t>(targetRoom->Id()));

    auto invitedNames = boost::make_shared<std::vector<std::string>>(
        invitedUserNames->begin(), invitedUserNames->end());
    sfso->PutUtfStringArray(KEY_INVITED_NAMES, invitedNames);

    if (parameters != NULL) {
        sfso->PutSFSObject(KEY_OPTIONAL_PARAMS, parameters);
    }
    sfso->PutInt(KEY_EXPIRY_SECONDS, static_cast<std::int32_t>(expirySeconds));

    auto valueAsSpectator = boost::make_shared<bool>(asSpectator);
    sfso->PutBool(KEY_AS_SPECT, valueAsSpectator);
}

} // namespace Game
} // namespace Requests
} // namespace Sfs2X
