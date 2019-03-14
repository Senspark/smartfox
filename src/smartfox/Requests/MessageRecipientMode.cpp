// ===================================================================
//
// Description
//        Contains the implementation of MessageRecipientMode
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "MessageRecipientMode.h"

namespace Sfs2X {
namespace Requests {
using Self = MessageRecipientMode;

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::MessageRecipientMode(int mode, const boost::shared_ptr<User>& target) {
    if (mode < static_cast<int>(MESSAGERECIPIENTTYPE_TO_USER) ||
        mode > static_cast<int>(MESSAGERECIPIENTTYPE_TO_ZONE)) {
        boost::throw_exception(boost::enable_error_info(std::runtime_error(
            "Illegal recipient mode: " + std::to_string(mode))));
    }

    this->mode = mode;
    this->targetUser = target;
    this->targetRoom = boost::shared_ptr<Room>();
    this->targetString = boost::shared_ptr<std::string>();
    this->targetInt = boost::shared_ptr<int>();
    this->targetUsersCollection =
        boost::shared_ptr<std::vector<boost::shared_ptr<User>>>();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::MessageRecipientMode(int mode, const boost::shared_ptr<Room>& target) {
    if (mode < static_cast<int>(MESSAGERECIPIENTTYPE_TO_USER) ||
        mode > static_cast<int>(MESSAGERECIPIENTTYPE_TO_ZONE)) {
        boost::throw_exception(boost::enable_error_info(std::runtime_error(
            "Illegal recipient mode: " + std::to_string(mode))));
    }

    this->mode = mode;
    this->targetUser = boost::shared_ptr<User>();
    this->targetRoom = target;
    this->targetString = boost::shared_ptr<std::string>();
    this->targetInt = boost::shared_ptr<int>();
    this->targetUsersCollection =
        boost::shared_ptr<std::vector<boost::shared_ptr<User>>>();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::MessageRecipientMode(int mode, const std::string& target) {
    if (mode < static_cast<int>(MESSAGERECIPIENTTYPE_TO_USER) ||
        mode > static_cast<int>(MESSAGERECIPIENTTYPE_TO_ZONE)) {
        boost::throw_exception(boost::enable_error_info(std::runtime_error(
            "Illegal recipient mode: " + std::to_string(mode))));
    }

    this->mode = mode;
    this->targetUser = boost::shared_ptr<User>();
    this->targetRoom = boost::shared_ptr<Room>();
    this->targetString =
        boost::shared_ptr<std::string>(new std::string(target));
    this->targetInt = boost::shared_ptr<int>();
    this->targetUsersCollection =
        boost::shared_ptr<std::vector<boost::shared_ptr<User>>>();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
Self::~MessageRecipientMode() {
    if (targetUsersCollection != NULL) {
        targetUsersCollection->clear();
    }
}

// -------------------------------------------------------------------
// TargetInt
// -------------------------------------------------------------------
int Self::TargetInt() const {
    if (this->targetInt == NULL)
        return 0;

    return *(this->targetInt);
}

// -------------------------------------------------------------------
// TargetUser
// -------------------------------------------------------------------
boost::shared_ptr<User> Self::TargetUser() const {
    return this->targetUser;
}

// -------------------------------------------------------------------
// TargetRoom
// -------------------------------------------------------------------
boost::shared_ptr<Room> Self::TargetRoom() const {
    return this->targetRoom;
}

// -------------------------------------------------------------------
// TargetString
// -------------------------------------------------------------------
boost::shared_ptr<std::string> Self::TargetString() const {
    if (this->targetString == NULL)
        return boost::shared_ptr<std::string>();

    return this->targetString;
}

// -------------------------------------------------------------------
// TargetUsersCollection
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<boost::shared_ptr<User>>>
Self::TargetUsersCollection() const {
    return this->targetUsersCollection;
}

// -------------------------------------------------------------------
// Mode
// -------------------------------------------------------------------
int Self::Mode() const {
    return this->mode;
}
} // namespace Requests
} // namespace Sfs2X
