// ===================================================================
//
// Description
//        Contains the implementation of SFSRoom
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================

#include "smartfox/Entities/SFSRoom.h"
#include "smartfox/Entities/MMORoom.h"
#include "smartfox/Entities/Room.h"
#include "smartfox/Entities/Managers/SFSUserManager.h"
#include "smartfox/Entities/Variables/SFSRoomVariable.h"

namespace Sfs2X {
namespace Entities {
using Self = SFSRoom;

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<Room>
Self::FromSFSArray(const boost::shared_ptr<ISFSArray>& sfsa) {
    // An MMO Room contains 14 properties
    bool isMMORoom = sfsa->Size() == 14;

    boost::shared_ptr<Room> newRoom = nullptr;
    auto roomId = static_cast<int>(sfsa->GetInt(0));
    auto roomName = *sfsa->GetUtfString(1);
    auto groupId = *sfsa->GetUtfString(2);
    if (isMMORoom) {
        newRoom = boost::make_shared<MMORoom>(roomId, roomName, groupId);
    } else {
        newRoom = boost::make_shared<SFSRoom>(roomId, roomName, groupId);
    }
    newRoom->IsGame(sfsa->GetBool(3));
    newRoom->IsHidden(sfsa->GetBool(4));
    newRoom->IsPasswordProtected(sfsa->GetBool(5));
    newRoom->UserCount(static_cast<std::size_t>(sfsa->GetShort(6)));
    newRoom->MaxUsers(static_cast<std::size_t>(sfsa->GetShort(7)));

    // Room vars
    auto varsList = sfsa->GetSFSArray(8);
    if (varsList->Size() > 0) {
        auto vars =
            boost::make_shared<std::vector<boost::shared_ptr<RoomVariable>>>();
        for (std::size_t j = 0; j < varsList->Size(); j++) {
            vars->push_back(
                SFSRoomVariable::FromSFSArray(varsList->GetSFSArray(j)));
        }
        newRoom->SetVariables(vars);
    }

    if (newRoom->IsGame()) {
        newRoom->SpectatorCount(static_cast<std::size_t>(sfsa->GetShort(9)));
        newRoom->MaxSpectators(static_cast<std::size_t>(sfsa->GetShort(10)));
    }

    if (isMMORoom) {
        auto mmoRoom = boost::static_pointer_cast<MMORoom>(newRoom);
        mmoRoom->DefaultAOI(Vec3D::fromArray(
            sfsa->GetWrappedElementAt(11)->Type(), sfsa->GetElementAt(11)));

        // Check if map limits are non null
        if (!sfsa->IsNull(13)) {
            mmoRoom->LowerMapLimit(Vec3D::fromArray(
                sfsa->GetWrappedElementAt(12)->Type(), sfsa->GetElementAt(12)));
            mmoRoom->HigherMapLimit(Vec3D::fromArray(
                sfsa->GetWrappedElementAt(13)->Type(), sfsa->GetElementAt(13)));
        }
    }
    return newRoom;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::SFSRoom(int id, const std::string& name) {
    Init(id, name, "default");
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::SFSRoom(int id, const std::string& name, const std::string& groupId) {
    Init(id, name, groupId);
}

// -------------------------------------------------------------------
// Dispose
// -------------------------------------------------------------------
void Self::Dispose() {}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
Self::~SFSRoom() {
    this->userManager.reset();
    this->roomManager.reset();

    variables->clear();
    variables.reset();

    this->name.reset();
    this->groupId.reset();

    this->properties->clear();
    this->properties.reset();
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void Self::Init(int id, const std::string& name, const std::string& groupId) {
    this->id = id;
    this->name = boost::make_shared<std::string>(name);
    this->groupId = boost::make_shared<std::string>(groupId);

    // default flags
    this->isJoined = this->isGame = this->isHidden = false;
    this->isManaged = true;

    // counters
    this->userCount = this->specCount = 0;

    this->variables = boost::make_shared<
        std::map<std::string, boost::shared_ptr<RoomVariable>>>();
    this->variables->clear();

    this->properties = boost::make_shared<std::map<std::string, std::string>>();
    this->properties->clear();

    // Note: shared pointer for class instance (shared_from_this()) is not
    // available up to the class constructor is completed so any initialization
    // that need of instance shared pointer (like userManager) should be moved
    // into other methods Here we set userManager to NULL and its initialization
    // to SFSUserManager instance will be done at the first access of
    // userManager
    this->userManager = nullptr;

    this->roomManager = boost::shared_ptr<IRoomManager>();
    this->maxSpectators = 0;
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
int Self::Id() const {
    return id;
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<std::string> Self::Name() const {
    return name;
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
void Self::Name(const std::string& value) {
    name = boost::shared_ptr<std::string>(new std::string(value));
}

// -------------------------------------------------------------------
// GroupId
// -------------------------------------------------------------------
boost::shared_ptr<std::string> Self::GroupId() const {
    return groupId;
}

// -------------------------------------------------------------------
// IsGame
// -------------------------------------------------------------------
bool Self::IsGame() const {
    return isGame;
}

// -------------------------------------------------------------------
// IsGame
// -------------------------------------------------------------------
void Self::IsGame(bool value) {
    isGame = value;
}

// -------------------------------------------------------------------
// IsHidden
// -------------------------------------------------------------------
bool Self::IsHidden() const {
    return isHidden;
}

// -------------------------------------------------------------------
// IsHidden
// -------------------------------------------------------------------
void Self::IsHidden(bool value) {
    isHidden = value;
}

// -------------------------------------------------------------------
// IsJoined
// -------------------------------------------------------------------
bool Self::IsJoined() const {
    return isJoined;
}

// -------------------------------------------------------------------
// IsJoined
// -------------------------------------------------------------------
void Self::IsJoined(bool value) {
    isJoined = value;
}

// -------------------------------------------------------------------
// IsPasswordProtected
// -------------------------------------------------------------------
bool Self::IsPasswordProtected() const {
    return isPasswordProtected;
}

// -------------------------------------------------------------------
// IsPasswordProtected
// -------------------------------------------------------------------
void Self::IsPasswordProtected(bool value) {
    isPasswordProtected = value;
}

// -------------------------------------------------------------------
// IsManaged
// -------------------------------------------------------------------
bool Self::IsManaged() const {
    return isManaged;
}

// -------------------------------------------------------------------
// IsManaged
// -------------------------------------------------------------------
void Self::IsManaged(bool value) {
    isManaged = value;
}

// -------------------------------------------------------------------
// MaxSpectators
// -------------------------------------------------------------------
std::size_t Self::MaxSpectators() const {
    return maxSpectators;
}

// -------------------------------------------------------------------
// MaxSpectators
// -------------------------------------------------------------------
void Self::MaxSpectators(std::size_t value) {
    maxSpectators = value;
}

// -------------------------------------------------------------------
// Properties
// -------------------------------------------------------------------
boost::shared_ptr<std::map<std::string, std::string>> Self::Properties() const {
    return properties;
}

// -------------------------------------------------------------------
// Properties
// -------------------------------------------------------------------
void Self::Properties(
    const boost::shared_ptr<std::map<std::string, std::string>>& value) {
    properties = value;
}

// -------------------------------------------------------------------
// GetVariables
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<boost::shared_ptr<RoomVariable>>>
Self::GetVariables() const {
    boost::shared_ptr<std::vector<boost::shared_ptr<RoomVariable>>> result(
        new vector<boost::shared_ptr<RoomVariable>>());

    for (auto iterator = variables->begin(); iterator != variables->end();
         iterator++) {
        result->push_back(iterator->second);
    }

    return result;
}

// -------------------------------------------------------------------
// GetVariable
// -------------------------------------------------------------------
boost::shared_ptr<RoomVariable>
Self::GetVariable(const std::string& name) const {
    auto iterator = variables->find(name);
    if (iterator == variables->end()) {
        return boost::shared_ptr<RoomVariable>();
    }
    return iterator->second;
}

// -------------------------------------------------------------------
// UserCount
// -------------------------------------------------------------------
std::size_t Self::UserCount() const {
    if (not isJoined) {
        return userCount;
    } else {
        // For game rooms, return only player count
        if (isGame) {
            return PlayerList()->size();
        }
        // For regular rooms, return the full user count
        else {
            return UserManager()->UserCount();
        }
    }
}

// -------------------------------------------------------------------
// UserCount
// -------------------------------------------------------------------
void Self::UserCount(std::size_t value) {
    userCount = value;
}

// -------------------------------------------------------------------
// MaxUsers
// -------------------------------------------------------------------
std::size_t Self::MaxUsers() const {
    return maxUsers;
}

// -------------------------------------------------------------------
// MaxUsers
// -------------------------------------------------------------------
void Self::MaxUsers(std::size_t value) {
    maxUsers = value;
}

// -------------------------------------------------------------------
// Capacity
// -------------------------------------------------------------------
std::size_t Self::Capacity() const {
    return maxUsers + maxSpectators;
}

// -------------------------------------------------------------------
// SpectatorCount
// -------------------------------------------------------------------
std::size_t Self::SpectatorCount() const {
    if (not isGame) {
        return 0;
    }

    // Joined Room? Dynamically calculate spectators
    if (isJoined) {
        return SpectatorList()->size();
    }
    // Not joined, use the static value sent by the server
    else {
        return specCount;
    }
}

// -------------------------------------------------------------------
// SpectatorCount
// -------------------------------------------------------------------
void Self::SpectatorCount(std::size_t value) {
    specCount = value;
}

// -------------------------------------------------------------------
// GetUserByName
// -------------------------------------------------------------------
boost::shared_ptr<User> Self::GetUserByName(const std::string& name) const {
    return UserManager()->GetUserByName(name);
}

// -------------------------------------------------------------------
// GetUserById
// -------------------------------------------------------------------
boost::shared_ptr<User> Self::GetUserById(int id) const {
    return UserManager()->GetUserById(id);
}

// -------------------------------------------------------------------
// UserList
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<boost::shared_ptr<User>>> Self::UserList() const {
    return UserManager()->GetUserList();
}

// -------------------------------------------------------------------
// PlayerList
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<boost::shared_ptr<User>>>
Self::PlayerList() const {
    boost::shared_ptr<std::vector<boost::shared_ptr<User>>> playerList(
        new vector<boost::shared_ptr<User>>());
    auto listUsers = UserManager()->GetUserList();
    for (auto iterator = listUsers->begin(); iterator != listUsers->end();
         iterator++) {
        boost::shared_ptr<User> user = (*iterator);
        if (user->IsPlayerInRoom(const_cast<Self*>(this)->shared_from_this())) {
            playerList->push_back(user);
        }
    }
    return playerList;
}

// -------------------------------------------------------------------
// SpectatorList
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<boost::shared_ptr<User>>>
Self::SpectatorList() const {
    boost::shared_ptr<std::vector<boost::shared_ptr<User>>> spectatorList(
        new vector<boost::shared_ptr<User>>());
    boost::shared_ptr<std::vector<boost::shared_ptr<User>>> listUsers =
        UserManager()->GetUserList();
    for (auto iterator = listUsers->begin(); iterator != listUsers->end();
         iterator++) {
        boost::shared_ptr<User> user = (*iterator);
        if (user->IsSpectatorInRoom(
                const_cast<Self*>(this)->shared_from_this())) {
            spectatorList->push_back(user);
        }
    }
    return spectatorList;
}

// -------------------------------------------------------------------
// RemoveUser
// -------------------------------------------------------------------
void Self::RemoveUser(const boost::shared_ptr<User>& user) {
    UserManager()->RemoveUser(user);
}

// -------------------------------------------------------------------
// SetVariable
// -------------------------------------------------------------------
void Self::SetVariable(const boost::shared_ptr<RoomVariable>& roomVariable) {
    // If varType == NULL delete var
    if (roomVariable->IsNull()) {
        map<string, boost::shared_ptr<RoomVariable>>::iterator iterator;
        iterator = variables->find(*roomVariable->Name());
        if (iterator != variables->end()) {
            variables->erase(iterator);
        }
    } else {
        map<string, boost::shared_ptr<RoomVariable>>::iterator iterator;
        iterator = variables->find(*roomVariable->Name());
        if (iterator != variables->end()) {
            iterator->second = roomVariable;
        } else {
            variables->insert(pair<string, boost::shared_ptr<RoomVariable>>(
                *roomVariable->Name(), roomVariable));
        }
    }
}

// -------------------------------------------------------------------
// SetVariables
// -------------------------------------------------------------------
void Self::SetVariables(
    const boost::shared_ptr<std::vector<boost::shared_ptr<RoomVariable>>>&
        roomVariables) {
    for (auto iterator = roomVariables->begin();
         iterator != roomVariables->end(); iterator++) {
        SetVariable(*iterator);
    }
}

// -------------------------------------------------------------------
// ContainsVariable
// -------------------------------------------------------------------
bool Self::ContainsVariable(const std::string& name) const {
    auto iterator = variables->find(name);
    if (iterator == variables->end()) {
        return false;
    }
    return true;
}

// -------------------------------------------------------------------
// RemoveUserVariable
// -------------------------------------------------------------------
void Self::RemoveUserVariable(const std::string& varName) {
    auto iterator = variables->find(varName);
    if (iterator != variables->end()) {
        variables->erase(iterator);
    }
}

// -------------------------------------------------------------------
// AddUser
// -------------------------------------------------------------------
void Self::AddUser(const boost::shared_ptr<User>& user) {
    UserManager()->AddUser(user);
}

// -------------------------------------------------------------------
// ContainsUser
// -------------------------------------------------------------------
bool Self::ContainsUser(const boost::shared_ptr<User>& user) const {
    return UserManager()->ContainsUser(user);
}

// -------------------------------------------------------------------
// RoomManager
// -------------------------------------------------------------------
boost::shared_ptr<IRoomManager> Self::RoomManager() const {
    return roomManager;
}

// -------------------------------------------------------------------
// RoomManager
// -------------------------------------------------------------------
void Self::RoomManager(const boost::shared_ptr<IRoomManager>& value) {
    if (roomManager != NULL) {
        boost::shared_ptr<std::string> message(new std::string(
            "Room manager already assigned. Room: " + *(this->Name())));
        boost::shared_ptr<SFSError> exception(new SFSError(message));
        throw exception;
    }

    roomManager = value;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<std::string> Self::ToString() const {
    char buffer[512];
    sprintf(buffer, "[Room: %s, Id: %ld, GroupId: %s]", name->c_str(), id,
            groupId->c_str());

    return boost::shared_ptr<std::string>(new std::string(buffer));
}

// -------------------------------------------------------------------
// Merge
// -------------------------------------------------------------------
void Self::Merge(const boost::shared_ptr<Room>& anotherRoom) {
    vector<boost::shared_ptr<RoomVariable>>::iterator iteratorRoomVariable;
    boost::shared_ptr<std::vector<boost::shared_ptr<RoomVariable>>>
        collectionAnotherRoomVariables = anotherRoom->GetVariables();

    for (iteratorRoomVariable = collectionAnotherRoomVariables->begin();
         iteratorRoomVariable != collectionAnotherRoomVariables->end();
         iteratorRoomVariable++) {
        boost::shared_ptr<RoomVariable> rv = (*iteratorRoomVariable);
        map<string, boost::shared_ptr<RoomVariable>>::iterator iterator;
        iterator = variables->find(*rv->Name());
        if (iterator != variables->end()) {
            iterator->second = rv;
        } else {
            variables->insert(
                pair<string, boost::shared_ptr<RoomVariable>>(*rv->Name(), rv));
        }
    }

    // Rebuild User List
    UserManager()->ClearAll();

    vector<boost::shared_ptr<User>>::iterator iteratorUser;
    boost::shared_ptr<std::vector<boost::shared_ptr<User>>>
        collectionAnotherRoomUserList = anotherRoom->UserList();
    for (iteratorUser = collectionAnotherRoomUserList->begin();
         iteratorUser != collectionAnotherRoomUserList->end(); iteratorUser++) {
        boost::shared_ptr<User> user = (*iteratorUser);
        UserManager()->AddUser(user);
    }
}

const boost::shared_ptr<IUserManager>& Self::UserManager() const {
    if (userManager == nullptr) {
        // Note: shared pointer for class instance (shared_from_this()) is not
        // available up to the class constructor is completed so any
        // initialization that need of instance shared pointer (like
        // userManager) should be moved into other methods In class constructor
        // we have set userManager to NULL and real initialization to
        // SFSUserManager instance is done at the first access
        userManager = boost::shared_ptr<IUserManager>(
            new SFSUserManager(const_cast<Self*>(this)->shared_from_this()));
    }
    return userManager;
}
} // namespace Entities
} // namespace Sfs2X

