// ===================================================================
//
// Description
//        Contains the implementation of SFSErrorCodes
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "SFSErrorCodes.h"

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

using boost::format;
using boost::io::group;

namespace Sfs2X {
namespace Util {
std::string* SFSErrorCodes::errorsByCode[] = {
    new std::string(
        "Client API version is obsolete: %s; required version: %s"), // 0
    new std::string("Requested Zone %s does not exist"),
    new std::string("User name %s is not recognized"),
    new std::string("Wrong password for user %s"),
    new std::string("User %s is banned"),
    new std::string("Zone %s is full"), // 5
    new std::string("User %s is already logged in Zone %s"),
    new std::string("The server is full"),
    new std::string("Zone %s is currently inactive"),
    new std::string("User name %s contains bad words; filtered: %s"),
    new std::string("Guest users not allowed in Zone %s"), // 10
    new std::string("IP address %s is banned"),
    new std::string("A Room with the same name already exists: %s"),
    new std::string("Requested Group is not available - Room: %s; Group: %s"),
    new std::string(
        "Bad Room name length -  Min: %s; max: %s; passed name length: %s"),
    new std::string("Room name contains bad words: %s"), // 15
    new std::string("Zone is full; can't add Rooms anymore"),
    new std::string("You have exceeded the number of Rooms that you can create "
                    "per session: %s"),
    new std::string("Room creation failed, wrong parameter: %s"),
    new std::string("Room %s already joined"),
    new std::string("Room %s is full"), // 20
    new std::string("Wrong password for Room %s"),
    new std::string("Requested Room does not exist"),
    new std::string("Room %s is locked"),
    new std::string("Group %s is already subscribed"),
    new std::string("Group %s does not exist"), // 25
    new std::string("Group %s is not subscribed"),
    new std::string("Group %s does not exist"),
    new std::string("%s"),
    new std::string("Room permission error; Room %s cannot be renamed"),
    new std::string(
        "Room permission error; Room %s cannot change password statee"), // 30
    new std::string("Room permission error; Room %s cannot change capacity"),
    new std::string("Switch user error; no player slots available in Room %s"),
    new std::string(
        "Switch user error; no spectator slots available in Room %s"),
    new std::string("Switch user error; Room %s is not a Game Room"),
    new std::string("Switch user error; you are not joined in Room %s"), // 35
    new std::string(
        "Buddy Manager initialization error, could not load buddy list: %s"),
    new std::string("Buddy Manager error, your buddy list is full; size is %s"),
    new std::string(
        "Buddy Manager error, was not able to block buddy %s because offline"),
    new std::string("Buddy Manager error, you are attempting to set too many "
                    "Buddy Variables; limit is %s"),
    new std::string(
        "Game %s access denied, user does not match access criteria"), // 40
    new std::string("QuickJoin action failed: no matching Rooms were found"),
    new std::string(
        "Your previous invitation reply was invalid or arrived too late")};

// -------------------------------------------------------------------
// SetErrorMessage
// -------------------------------------------------------------------
void SFSErrorCodes::SetErrorMessage(int code, const std::string& message) {
    delete errorsByCode[code];
    errorsByCode[code] = new std::string(message);
}

// -------------------------------------------------------------------
// GetErrorMessage
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSErrorCodes::GetErrorMessage(
    int code, const boost::shared_ptr<Logger>& log,
    const boost::shared_ptr<std::vector<std::string>>& args) {
    format f(*errorsByCode[code]);
    for (auto it = args->begin(); it != args->end(); ++it) {
        f % *it;
    }
    return boost::shared_ptr<std::string>(new std::string(f.str()));
}

// -------------------------------------------------------------------
// Dispose
// -------------------------------------------------------------------
void SFSErrorCodes::Dispose() {
    for (int code = 0; code < NUM_ENTRIES_errorsByCode; code++) {
        delete errorsByCode[code];
    }
}
} // namespace Util
} // namespace Sfs2X
