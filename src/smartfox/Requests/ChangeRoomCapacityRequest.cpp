// ===================================================================
//
// Description
//        Contains the implementation of ChangeRoomCapacityRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "ChangeRoomCapacityRequest.h"

namespace Sfs2X {
namespace Requests {
using Self = ChangeRoomCapacityRequest;

boost::shared_ptr<std::string> Self::KEY_ROOM(new std::string("r"));
boost::shared_ptr<std::string> Self::KEY_USER_SIZE(new std::string("u"));
boost::shared_ptr<std::string> Self::KEY_SPEC_SIZE(new std::string("s"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::ChangeRoomCapacityRequest(const boost::shared_ptr<Room>& room,
                                std::size_t newMaxUsers,
                                std::size_t newMaxSpect)
    : BaseRequest(RequestType_ChangeRoomCapacity) {
    this->room = room;
    this->newMaxUsers = newMaxUsers;
    this->newMaxSpect = newMaxSpect;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
Self::~ChangeRoomCapacityRequest() {}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void Self::Validate(const boost::shared_ptr<SmartFox>& sfs) {
    boost::shared_ptr<list<string>> errors(new list<string>());

    // Missing room id
    if (this->room == NULL)
        errors->push_back("Provided room is null");

    if (errors->size() > 0) {
        boost::shared_ptr<std::string> message(
            new std::string("ChangeRoomCapacity request error"));
        boost::shared_ptr<SFSValidationError> exception(
            new SFSValidationError(message, errors));
        throw exception;
    }
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void ChangeRoomCapacityRequest::Execute(
    const boost::shared_ptr<SmartFox>& sfs) {
    sfso->PutInt(KEY_ROOM, static_cast<std::int32_t>(room->Id()));
    sfso->PutInt(KEY_USER_SIZE, static_cast<std::int32_t>(newMaxUsers));
    sfso->PutInt(KEY_SPEC_SIZE, static_cast<std::int32_t>(newMaxSpect));
}
} // namespace Requests
} // namespace Sfs2X
