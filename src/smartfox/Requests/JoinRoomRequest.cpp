// ===================================================================
//
// Description
//        Contains the implementation of JoinRoomRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "JoinRoomRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<std::string> JoinRoomRequest::KEY_ROOM(new std::string("r"));
boost::shared_ptr<std::string>
    JoinRoomRequest::KEY_USER_LIST(new std::string("ul"));
boost::shared_ptr<std::string>
    JoinRoomRequest::KEY_ROOM_NAME(new std::string("n"));
boost::shared_ptr<std::string>
    JoinRoomRequest::KEY_ROOM_ID(new std::string("i"));
boost::shared_ptr<std::string> JoinRoomRequest::KEY_PASS(new std::string("p"));
boost::shared_ptr<std::string>
    JoinRoomRequest::KEY_ROOM_TO_LEAVE(new std::string("rl"));
boost::shared_ptr<std::string>
    JoinRoomRequest::KEY_AS_SPECTATOR(new std::string("sp"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(const boost::shared_ptr<Room>& id,
                                 const std::string& pass,
                                 boost::shared_ptr<int> roomIdToLeave,
                                 bool asSpectator)
    : BaseRequest(RequestType_JoinRoom) {
    Init(id, boost::shared_ptr<std::string>(new std::string(pass)),
         roomIdToLeave, asSpectator);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(const std::string& id, const std::string& pass,
                                 boost::shared_ptr<int> roomIdToLeave,
                                 bool asSpectator)
    : BaseRequest(RequestType_JoinRoom) {
    Init(id, boost::shared_ptr<std::string>(new std::string(pass)),
         roomIdToLeave, asSpectator);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(int id, const std::string& pass,
                                 boost::shared_ptr<int> roomIdToLeave,
                                 bool asSpectator)
    : BaseRequest(RequestType_JoinRoom) {
    Init(id, boost::shared_ptr<std::string>(new std::string(pass)),
         roomIdToLeave, asSpectator);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(const boost::shared_ptr<Room>& id,
                                 const std::string& pass,
                                 boost::shared_ptr<int> roomIdToLeave)
    : BaseRequest(RequestType_JoinRoom) {
    Init(id, boost::shared_ptr<std::string>(new std::string(pass)),
         roomIdToLeave, false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(const std::string& id, const std::string& pass,
                                 boost::shared_ptr<int> roomIdToLeave)
    : BaseRequest(RequestType_JoinRoom) {
    Init(id, boost::shared_ptr<std::string>(new std::string(pass)),
         roomIdToLeave, false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(int id, const std::string& pass,
                                 boost::shared_ptr<int> roomIdToLeave)
    : BaseRequest(RequestType_JoinRoom) {
    Init(id, boost::shared_ptr<std::string>(new std::string(pass)),
         roomIdToLeave, false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(const boost::shared_ptr<Room>& id,
                                 const std::string& pass)
    : BaseRequest(RequestType_JoinRoom) {
    Init(id, boost::shared_ptr<std::string>(new std::string(pass)),
         boost::shared_ptr<int>(), false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(const std::string& id, const std::string& pass)
    : BaseRequest(RequestType_JoinRoom) {
    Init(id, boost::shared_ptr<std::string>(new std::string(pass)),
         boost::shared_ptr<int>(), false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(int id, const std::string& pass)
    : BaseRequest(RequestType_JoinRoom) {
    Init(id, boost::shared_ptr<std::string>(new std::string(pass)),
         boost::shared_ptr<int>(), false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(const boost::shared_ptr<Room>& id)
    : BaseRequest(RequestType_JoinRoom) {
    Init(id, boost::shared_ptr<std::string>(),
         boost::shared_ptr<int>(), false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(const std::string& id)
    : BaseRequest(RequestType_JoinRoom) {
    Init(id, boost::shared_ptr<std::string>(),
         boost::shared_ptr<int>(), false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
JoinRoomRequest::JoinRoomRequest(int id)
    : BaseRequest(RequestType_JoinRoom) {
    Init(id, boost::shared_ptr<std::string>(),
         boost::shared_ptr<int>(), false);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
JoinRoomRequest::~JoinRoomRequest() {}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void JoinRoomRequest::Init(const boost::shared_ptr<Room>& id,
                           boost::shared_ptr<std::string> pass,
                           boost::shared_ptr<int> roomIdToLeave,
                           bool asSpectator) {
    this->id = -1;
    this->id = id->Id();

    this->pass = pass;
    this->roomIdToLeave = roomIdToLeave;
    this->asSpectator = asSpectator;
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void JoinRoomRequest::Init(const std::string& id,
                           boost::shared_ptr<std::string> pass,
                           boost::shared_ptr<int> roomIdToLeave,
                           bool asSpectator) {
    this->id = -1;
    this->name = boost::shared_ptr<std::string>(new string(id));

    this->pass = pass;
    this->roomIdToLeave = roomIdToLeave;
    this->asSpectator = asSpectator;
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void JoinRoomRequest::Init(int id, boost::shared_ptr<std::string> pass,
                           boost::shared_ptr<int> roomIdToLeave,
                           bool asSpectator) {
    this->id = -1;
    this->id = id;

    this->pass = pass;
    this->roomIdToLeave = roomIdToLeave;
    this->asSpectator = asSpectator;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void JoinRoomRequest::Validate(const boost::shared_ptr<SmartFox>& sfs) {
    if (this->id < 0 && this->name == NULL) {
        boost::shared_ptr<list<string>> errors(new list<string>());
        errors->push_back(
            "Missing Room id or name, you should provide at least one");

        boost::shared_ptr<std::string> message(
            new std::string("JoinRoomRequest Error"));
        boost::shared_ptr<SFSValidationError> exception(
            new SFSValidationError(message, errors));
        throw exception;
    }
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void JoinRoomRequest::Execute(const boost::shared_ptr<SmartFox>& sfs) {
    if (this->id > -1) {
        this->sfso->PutInt(KEY_ROOM_ID, static_cast<std::int32_t>(this->id));
    } else if (this->name != NULL) {
        this->sfso->PutUtfString(KEY_ROOM_NAME, this->name);
    }

    if (this->pass != NULL) {
        this->sfso->PutUtfString(KEY_PASS, this->pass);
    }

    /*
     * If == null     --->> Leave Last Joined Room
     * If > 0         --->> Leave the Room with that ID
     * If < 0        --->> Do not leave any Room
     */
    if (this->roomIdToLeave != NULL) {
        this->sfso->PutInt(KEY_ROOM_TO_LEAVE, this->roomIdToLeave);
    }

    if (this->asSpectator) {
        auto valueAsSpectator = boost::make_shared<bool>(this->asSpectator);
        this->sfso->PutBool(KEY_AS_SPECTATOR, valueAsSpectator);
    }
}

} // namespace Requests
} // namespace Sfs2X
