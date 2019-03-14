// ===================================================================
//
// Description
//        Contains the implementation of SFSUser
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "smartfox/Entities/SFSUser.h"
#include "smartfox/Entities/Variables/SFSUserVariable.h"
#include "smartfox/Entities/UserPrivileges.h"

namespace Sfs2X {
namespace Entities {
using Self = SFSUser;

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<User>
SFSUser::FromSFSArray(const boost::shared_ptr<ISFSArray>& sfsa,
                      const boost::shared_ptr<Room>& room) {
    // Pass id and name
    boost::shared_ptr<User> newUser(
        new SFSUser(sfsa->GetInt(0), *(sfsa->GetUtfString(1))));

    // Set privileges
    newUser->PrivilegeId(sfsa->GetShort(2));

    // Set playerId
    if (room != NULL) {
        newUser->SetPlayerId(sfsa->GetShort(3), room);
    }

    // Populate variables
    boost::shared_ptr<ISFSArray> uVars = sfsa->GetSFSArray(4);
    for (std::size_t i = 0; i < uVars->Size(); i++) {
        newUser->SetVariable(
            SFSUserVariable::FromSFSArray(uVars->GetSFSArray(i)));
    }

    return newUser;
}

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<User>
SFSUser::FromSFSArray(const boost::shared_ptr<ISFSArray>& sfsa) {
    return FromSFSArray(sfsa, boost::shared_ptr<Room>());
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSUser::SFSUser(int id, const std::string& name) {
    Init(id, name, false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSUser::SFSUser(int id, const std::string& name, bool isItMe) {
    Init(id, name, isItMe);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSUser::~SFSUser() {
    name = boost::shared_ptr<std::string>();
    variables->clear();
    variables.reset();
    playerIdByRoomId->clear();
    playerIdByRoomId.reset();
    properties->clear();
    properties.reset();
    if (userManager != NULL) {
        // userManager->Dispose();
        userManager.reset();
    }
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void SFSUser::Init(int id, const std::string& name, bool isItMe) {
    this->id = id;
    this->name = boost::shared_ptr<std::string>(new std::string(name));
    this->isItMe = isItMe;
    this->variables = boost::make_shared<
        std::map<std::string, boost::shared_ptr<UserVariable>>>();
    this->variables->clear();
    this->properties =
        boost::make_shared<std::map<std::string, boost::shared_ptr<void>>>();
    this->properties->clear();
    this->isModerator = false;
    this->playerIdByRoomId = boost::make_shared<std::map<int, int>>();
    this->playerIdByRoomId->clear();
    this->privilegeId = 0;
    this->userManager.reset();
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
int SFSUser::Id() const {
    return id;
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSUser::Name() const {
    return name;
}

// -------------------------------------------------------------------
// PlayerId
// -------------------------------------------------------------------
int SFSUser::PlayerId() const {
    // Return from default room
    return GetPlayerId(userManager->SmartFoxClient()->LastJoinedRoom());
}

// -------------------------------------------------------------------
// IsJoinedInRoom
// -------------------------------------------------------------------
bool SFSUser::IsJoinedInRoom(const boost::shared_ptr<Room>& room) const {
    return room->ContainsUser(const_cast<Self*>(this)->shared_from_this());
}

// -------------------------------------------------------------------
// PrivilegeId
// -------------------------------------------------------------------
int SFSUser::PrivilegeId() const {
    return privilegeId;
}

// -------------------------------------------------------------------
// PrivilegeId
// -------------------------------------------------------------------
void SFSUser::PrivilegeId(int value) {
    privilegeId = value;
}

// -------------------------------------------------------------------
// IsGuest
// -------------------------------------------------------------------
bool SFSUser::IsGuest() const {
    return privilegeId == static_cast<int>(USERPRIVILEGES_GUEST);
}

// -------------------------------------------------------------------
// IsStandardUser
// -------------------------------------------------------------------
bool SFSUser::IsStandardUser() const {
    return privilegeId == static_cast<int>(USERPRIVILEGES_STANDARD);
}

// -------------------------------------------------------------------
// IsModerator
// -------------------------------------------------------------------
bool SFSUser::IsModerator() const {
    return privilegeId == static_cast<int>(USERPRIVILEGES_MODERATOR);
}

// -------------------------------------------------------------------
// IsAdmin
// -------------------------------------------------------------------
bool SFSUser::IsAdmin() const {
    return privilegeId == static_cast<int>(USERPRIVILEGES_ADMINISTRATOR);
}

// -------------------------------------------------------------------
// IsPlayer
// -------------------------------------------------------------------
bool SFSUser::IsPlayer() const {
    return this->PlayerId() > 0;
}

// -------------------------------------------------------------------
// IsSpectator
// -------------------------------------------------------------------
bool SFSUser::IsSpectator() const {
    return not this->IsPlayer();
}

// -------------------------------------------------------------------
// GetPlayerId
// -------------------------------------------------------------------
int SFSUser::GetPlayerId(const boost::shared_ptr<Room>& room) const {
    int pId = 0;

    auto iterator = playerIdByRoomId->find(room->Id());
    if (iterator != playerIdByRoomId->end()) {
        pId = iterator->second;
    }

    return pId;
}

// -------------------------------------------------------------------
// SetPlayerId
// -------------------------------------------------------------------
void SFSUser::SetPlayerId(int id, const boost::shared_ptr<Room>& room) const {
    auto iterator = playerIdByRoomId->find(room->Id());
    if (iterator != playerIdByRoomId->end()) {
        iterator->second = id;
    } else {
        playerIdByRoomId->emplace(room->Id(), id);
    }
}

// -------------------------------------------------------------------
// RemovePlayerId
// -------------------------------------------------------------------
void SFSUser::RemovePlayerId(const boost::shared_ptr<Room>& room) const {
    auto iterator = playerIdByRoomId->find(room->Id());
    if (iterator != playerIdByRoomId->end()) {
        playerIdByRoomId->erase(iterator);
    }
}

// -------------------------------------------------------------------
// IsPlayerInRoom
// -------------------------------------------------------------------
bool SFSUser::IsPlayerInRoom(const boost::shared_ptr<Room>& room) const {
    auto iterator = playerIdByRoomId->find(room->Id());
    if (iterator == playerIdByRoomId->end()) {
        return false;
    }
    return iterator->second > 0;
}

// -------------------------------------------------------------------
// IsSpectatorInRoom
// -------------------------------------------------------------------
bool SFSUser::IsSpectatorInRoom(const boost::shared_ptr<Room>& room) const {
    auto iterator = playerIdByRoomId->find(room->Id());
    if (iterator == playerIdByRoomId->end()) {
        return true;
    }
    return iterator->second < 0;
}

// -------------------------------------------------------------------
// IsItMe
// -------------------------------------------------------------------
bool SFSUser::IsItMe() const {
    return isItMe;
}

// -------------------------------------------------------------------
// UserManager
// -------------------------------------------------------------------
boost::shared_ptr<IUserManager> SFSUser::UserManager() const {
    return userManager;
}

// -------------------------------------------------------------------
// UserManager
// -------------------------------------------------------------------
void SFSUser::UserManager(const boost::shared_ptr<IUserManager>& value) {
    if (value == NULL) {
        userManager = value;
        return;
    }

    if (userManager != NULL) {
        boost::shared_ptr<std::string> message(new std::string(
            "Cannot re-assign the User manager. Already set. User: " +
            *(this->Name())));
        boost::shared_ptr<SFSError> exception(new SFSError(message));
        throw exception;
    }

    userManager = value;
}

// -------------------------------------------------------------------
// AOIEntryPoint
// -------------------------------------------------------------------
boost::shared_ptr<Vec3D> SFSUser::AOIEntryPoint() const {
    return aoiEntryPoint;
}

// -------------------------------------------------------------------
// AOIEntryPoint
// -------------------------------------------------------------------
void SFSUser::AOIEntryPoint(const boost::shared_ptr<Vec3D>& value) {
    aoiEntryPoint = value;
}

// -------------------------------------------------------------------
// GetVariables
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<boost::shared_ptr<UserVariable>>>
SFSUser::GetVariables() const {
    boost::shared_ptr<std::vector<boost::shared_ptr<UserVariable>>> result(
        new vector<boost::shared_ptr<UserVariable>>());

    map<string, boost::shared_ptr<UserVariable>>::iterator iterator;
    for (iterator = variables->begin(); iterator != variables->end();
         iterator++) {
        result->push_back(iterator->second);
    }

    return result;
}

// -------------------------------------------------------------------
// GetVariable
// -------------------------------------------------------------------
boost::shared_ptr<UserVariable>
SFSUser::GetVariable(const std::string& varName) const {
    map<string, boost::shared_ptr<UserVariable>>::iterator iterator;
    iterator = variables->find(varName);
    if (iterator == variables->end()) {
        return boost::shared_ptr<UserVariable>();
    }

    return iterator->second;
}

// -------------------------------------------------------------------
// SetVariable
// -------------------------------------------------------------------
void SFSUser::SetVariable(const boost::shared_ptr<UserVariable>& userVariable) {
    if (userVariable != NULL) {
        // If varType == NULL delete var
        if (userVariable->IsNull()) {
            map<string, boost::shared_ptr<UserVariable>>::iterator iterator;
            iterator = variables->find(*userVariable->Name());
            if (iterator != variables->end()) {
                iterator->second = boost::shared_ptr<UserVariable>();
                variables->erase(iterator);
            }
        } else {
            map<string, boost::shared_ptr<UserVariable>>::iterator iterator;
            iterator = variables->find(*userVariable->Name());
            if (iterator != variables->end()) {
                iterator->second = boost::shared_ptr<UserVariable>();
                iterator->second = userVariable;
            } else {
                variables->insert(pair<string, boost::shared_ptr<UserVariable>>(
                    *userVariable->Name(), userVariable));
            }
        }
    }
}

// -------------------------------------------------------------------
// SetVariables
// -------------------------------------------------------------------
void SFSUser::SetVariables(
    const boost::shared_ptr<std::vector<boost::shared_ptr<UserVariable>>>&
        userVaribles) {
    vector<boost::shared_ptr<UserVariable>>::iterator iterator;
    for (iterator = userVaribles->begin(); iterator != userVaribles->end();
         iterator++) {
        SetVariable(*iterator);
    }
}

// -------------------------------------------------------------------
// ContainsVariable
// -------------------------------------------------------------------
bool SFSUser::ContainsVariable(const std::string& name) const {
    map<string, boost::shared_ptr<UserVariable>>::iterator iterator;
    iterator = variables->find(name);
    if (iterator == variables->end()) {
        return false;
    }

    return true;
}

// -------------------------------------------------------------------
// RemoveUserVariable
// -------------------------------------------------------------------
void SFSUser::RemoveUserVariable(const std::string& varName) {
    map<string, boost::shared_ptr<UserVariable>>::iterator iterator;
    iterator = variables->find(varName);
    if (iterator != variables->end()) {
        iterator->second = boost::shared_ptr<UserVariable>();
        variables->erase(iterator);
    }
}

// -------------------------------------------------------------------
// Properties
// -------------------------------------------------------------------
boost::shared_ptr<std::map<std::string, boost::shared_ptr<void>>>
SFSUser::Properties() const {
    return properties;
}

// -------------------------------------------------------------------
// Properties
// -------------------------------------------------------------------
void SFSUser::Properties(
    const boost::shared_ptr<std::map<std::string, boost::shared_ptr<void>>>&
        value) {
    properties = value;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSUser::ToString() const {
    char buffer[512];
    sprintf(buffer, "[User: %s, Id: %ld, isMe: %ld]", name->c_str(), id,
            isItMe);

    return boost::shared_ptr<std::string>(new std::string(buffer));
}
} // namespace Entities
} // namespace Sfs2X
