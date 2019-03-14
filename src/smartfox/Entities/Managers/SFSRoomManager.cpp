// ===================================================================
//
// Description
//        Contains the implementation of SFSRoomManager
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "SFSRoomManager.h"
#include <typeinfo>

namespace Sfs2X {
namespace Entities {
namespace Managers {
// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSRoomManager::SFSRoomManager(const boost::shared_ptr<SmartFox>& sfs) {
    smartFox = sfs;
    ownerZone = boost::shared_ptr<std::string>();
    groups.clear();
    roomsById.clear();
    roomsByName.clear();
}

// -------------------------------------------------------------------
// Dispose
// -------------------------------------------------------------------
void SFSRoomManager::Dispose() {
    smartFox = boost::shared_ptr<SmartFox>();
    groups.clear();
    roomsById.clear();
    roomsByName.clear();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSRoomManager::~SFSRoomManager() {}

// -------------------------------------------------------------------
// OwnerZone
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSRoomManager::OwnerZone() {
    return ownerZone;
}

// -------------------------------------------------------------------
// OwnerZone
// -------------------------------------------------------------------
void SFSRoomManager::OwnerZone(const std::string& value) {
    ownerZone = boost::shared_ptr<std::string>(new std::string(value));
}

// -------------------------------------------------------------------
// SmartFoxClient
// -------------------------------------------------------------------
boost::shared_ptr<SmartFox> SFSRoomManager::SmartFoxClient() {
    return smartFox;
}

// -------------------------------------------------------------------
// AddRoom
// -------------------------------------------------------------------
void SFSRoomManager::AddRoom(const boost::shared_ptr<Room>& room) {
    AddRoom(room, true);
}

// -------------------------------------------------------------------
// AddRoom
// -------------------------------------------------------------------
void SFSRoomManager::AddRoom(const boost::shared_ptr<Room>& room,
                             bool addGroupIfMissing) {
    lockRoomsById.lock();
    roomsById.emplace(room->Id(), room);
    lockRoomsById.unlock();

    lockRoomsByName.lock();
    roomsByName.emplace(*room->Name(), room);
    lockRoomsByName.unlock();

    // If group is not known, add it to the susbscribed list
    if (addGroupIfMissing) {
        if (!ContainsGroup(*(room->GroupId()))) {
            AddGroup(*(room->GroupId()));
        }
    }

    /*
     * We don't add a group that was not subscribed
     * Instead we mark the Room as *NOT MANAGED* which means that it will be
     * removed from the local RoomList as soon as we leave it
     */
    else {
        room->IsManaged(false);
    }
}

// -------------------------------------------------------------------
// ReplaceRoom
// -------------------------------------------------------------------
boost::shared_ptr<Room>
SFSRoomManager::ReplaceRoom(const boost::shared_ptr<Room>& room) {
    return ReplaceRoom(room, true);
}

// -------------------------------------------------------------------
// ReplaceRoom
// -------------------------------------------------------------------
boost::shared_ptr<Room>
SFSRoomManager::ReplaceRoom(const boost::shared_ptr<Room>& room,
                            bool addToGroupIfMissing) {
    // Take the Room object that should be replaced
    boost::shared_ptr<Room> oldRoom = GetRoomById(room->Id());

    /*
     * If found, the Room is already in the RoomList and we don't want
     * to replace the object, only update it
     */
    if (oldRoom != NULL) {
        oldRoom->Merge(room);
        return oldRoom;
    }

    // There's no previous instance, just add it
    else {
        AddRoom(room, addToGroupIfMissing);
        return room;
    }
}

// -------------------------------------------------------------------
// ChangeRoomName
// -------------------------------------------------------------------
void SFSRoomManager::ChangeRoomName(const boost::shared_ptr<Room>& room,
                                    const std::string& newName) {
    string oldName = *room->Name();
    room->Name(newName);

    auto guard = boost::make_lock_guard(lockRoomsByName);

    // Update keys in the byName collection
    roomsByName.emplace(newName, room);

    auto iterator = roomsByName.find(oldName);
    if (iterator != roomsByName.end()) {
        roomsByName.erase(iterator);
    }
}

// -------------------------------------------------------------------
// ChangeRoomPasswordState
// -------------------------------------------------------------------
void SFSRoomManager::ChangeRoomPasswordState(
    const boost::shared_ptr<Room>& room, bool isPassProtected) {
    room->IsPasswordProtected(isPassProtected);
}

// -------------------------------------------------------------------
// ChangeRoomCapacity
// -------------------------------------------------------------------
void SFSRoomManager::ChangeRoomCapacity(const boost::shared_ptr<Room>& room,
                                        std::size_t maxUsers,
                                        std::size_t maxSpect) {
    room->MaxUsers(maxUsers);
    room->MaxSpectators(maxSpect);
}

// -------------------------------------------------------------------
// GetRoomGroups
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<std::string>> SFSRoomManager::GetRoomGroups() {
    boost::shared_ptr<std::vector<std::string>> returned(
        new vector<string>(groups));
    return returned;
}

// -------------------------------------------------------------------
// AddGroup
// -------------------------------------------------------------------
void SFSRoomManager::AddGroup(const std::string& groupId) {
    auto guard = boost::make_lock_guard(lockGroups);
    groups.push_back(groupId);
}

// -------------------------------------------------------------------
// RemoveGroup
// -------------------------------------------------------------------
void SFSRoomManager::RemoveGroup(const std::string& groupId) {
    // remove group
    lockGroups.lock();

    auto iterator = std::find(groups.begin(), groups.end(), groupId);
    if (iterator != groups.end()) {
        groups.erase(iterator);
    }

    lockGroups.unlock();

    auto roomsInGroup = GetRoomListFromGroup(groupId);

    /*
     * We remove all rooms from the Group with the exception
     * of those that are joined. The joined Rooms must remain in the local Room
     * List but they are marked as unmanaged because we no longer subscribe to
     * their Group
     *
     * The unmanaged Room(s) will be removed as soon as we leave it
     */
    for (auto iteratorRooms = roomsInGroup->begin();
         iteratorRooms != roomsInGroup->end(); iteratorRooms++) {
        auto&& room = (*iteratorRooms);
        if (!room->IsJoined()) {
            RemoveRoom(room);
        } else {
            room->IsManaged(false);
        }
    }
}

// -------------------------------------------------------------------
// ContainsGroup
// -------------------------------------------------------------------
bool SFSRoomManager::ContainsGroup(const std::string& groupId) {
    auto guard = boost::make_lock_guard(lockGroups);
    auto iterator = std::find(groups.begin(), groups.end(), groupId);
    bool returned = iterator == groups.end() ? false : true;
    return returned;
}

// -------------------------------------------------------------------
// ContainsRoom
// -------------------------------------------------------------------
bool SFSRoomManager::ContainsRoom(int id) {
    auto guard = boost::make_lock_guard(lockRoomsById);
    auto iterator = roomsById.find(id);
    bool returned = iterator == roomsById.end() ? false : true;
    return returned;
}

bool SFSRoomManager::ContainsRoom(const std::string& name) {
    auto guard = boost::make_lock_guard(lockRoomsByName);
    auto iterator = roomsByName.find(name);
    bool returned = iterator == roomsByName.end() ? false : true;
    return returned;
}

// -------------------------------------------------------------------
// ContainsRoomInGroup
// -------------------------------------------------------------------
bool SFSRoomManager::ContainsRoomInGroup(int id,
                                         const std::string& groupId) {
    auto roomList = GetRoomListFromGroup(groupId);

    for (auto iterator = roomList->begin(); iterator != roomList->end();
         iterator++) {
        auto&& room = (*iterator);
        if (room->Id() == id) {
            return true;
        }
    }
    return false;
}

bool SFSRoomManager::ContainsRoomInGroup(const std::string& name,
                                         const std::string& groupId) {
    auto roomList = GetRoomListFromGroup(groupId);

    for (auto iterator = roomList->begin(); iterator != roomList->end();
         iterator++) {
        auto&& room = (*iterator);
        if ((*room->Name()) == name) {
            return true;
        }
    }
    return false;
}

// -------------------------------------------------------------------
// GetRoomById
// -------------------------------------------------------------------
boost::shared_ptr<Room> SFSRoomManager::GetRoomById(int id) {
    auto guard = boost::make_lock_guard(lockRoomsById);
    auto iterator = roomsById.find(id);
    if (iterator == roomsById.end()) {
        return boost::shared_ptr<Room>();
    }
    boost::shared_ptr<Room> room = iterator->second;
    return room;
}

// -------------------------------------------------------------------
// GetRoomByName
// -------------------------------------------------------------------
boost::shared_ptr<Room> SFSRoomManager::GetRoomByName(const std::string& name) {
    auto guard = boost::make_lock_guard(lockRoomsByName);
    auto iterator = roomsByName.find(name);
    if (iterator == roomsByName.end()) {
        return boost::shared_ptr<Room>();
    }
    boost::shared_ptr<Room> room = iterator->second;
    return room;
}

// -------------------------------------------------------------------
// GetRoomList
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<boost::shared_ptr<Room>>>
SFSRoomManager::GetRoomList() {
    boost::shared_ptr<std::vector<boost::shared_ptr<Room>>> rooms(
        new vector<boost::shared_ptr<Room>>());

    auto guard = boost::make_lock_guard(lockRoomsById);
    for (auto iterator = roomsById.begin(); iterator != roomsById.end();
         iterator++) {
        rooms->push_back(iterator->second);
    }
    return rooms;
}

// -------------------------------------------------------------------
// GetRoomCount
// -------------------------------------------------------------------
std::size_t SFSRoomManager::GetRoomCount() {
    return roomsById.size();
}

// -------------------------------------------------------------------
// GetRoomListFromGroup
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<boost::shared_ptr<Room>>>
SFSRoomManager::GetRoomListFromGroup(const std::string& groupId) {
    boost::shared_ptr<std::vector<boost::shared_ptr<Room>>> rooms(
        new vector<boost::shared_ptr<Room>>());

    auto guard = boost::make_lock_guard(lockRoomsById);
    for (auto iterator = roomsById.begin(); iterator != roomsById.end();
         iterator++) {
        boost::shared_ptr<Room> room = iterator->second;
        if ((*room->GroupId()) == groupId) {
            rooms->push_back(iterator->second);
        }
    }
    return rooms;
}

// -------------------------------------------------------------------
// RemoveRoom
// -------------------------------------------------------------------
void SFSRoomManager::RemoveRoom(const boost::shared_ptr<Room>& room) {
    RemoveRoom(room->Id(), *(room->Name()));
}

// -------------------------------------------------------------------
// RemoveRoomById
// -------------------------------------------------------------------
void SFSRoomManager::RemoveRoomById(int id) {
    lockRoomsById.lock();

    auto iterator = roomsById.find(id);
    if (iterator == roomsById.end()) {
        lockRoomsById.unlock();
        return;
    }
    boost::shared_ptr<Room> room = iterator->second;
    lockRoomsById.unlock();

    RemoveRoom(id, *(room->Name()));
}

// -------------------------------------------------------------------
// RemoveRoomByName
// -------------------------------------------------------------------
void SFSRoomManager::RemoveRoomByName(const std::string& name) {
    lockRoomsByName.lock();

    auto iterator = roomsByName.find(name);
    if (iterator == roomsByName.end()) {
        lockRoomsByName.unlock();
        return;
    }

    boost::shared_ptr<Room> room = iterator->second;
    lockRoomsByName.unlock();

    RemoveRoom(room->Id(), name);
}

// -------------------------------------------------------------------
// GetJoinedRooms
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<boost::shared_ptr<Room>>>
SFSRoomManager::GetJoinedRooms() {
    boost::shared_ptr<std::vector<boost::shared_ptr<Room>>> rooms(
        new vector<boost::shared_ptr<Room>>());

    auto guard = boost::make_lock_guard(lockRoomsById);
    for (auto iterator = roomsById.begin(); iterator != roomsById.end();
         iterator++) {
        auto&& room = iterator->second;
        if (room->IsJoined()) {
            rooms->push_back(iterator->second);
        }
    }
    return rooms;
}

// -------------------------------------------------------------------
// GetUserRooms
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<boost::shared_ptr<Room>>>
SFSRoomManager::GetUserRooms(const boost::shared_ptr<User>& user) {
    boost::shared_ptr<std::vector<boost::shared_ptr<Room>>> rooms(
        new vector<boost::shared_ptr<Room>>());

    auto guard = boost::make_lock_guard(lockRoomsById);
    for (auto iterator = roomsById.begin(); iterator != roomsById.end();
         iterator++) {
        auto&& room = iterator->second;
        if (room->ContainsUser(user)) {
            rooms->push_back(iterator->second);
        }
    }
    return rooms;
}

// -------------------------------------------------------------------
// RemoveUser
// -------------------------------------------------------------------
void SFSRoomManager::RemoveUser(const boost::shared_ptr<User>& user) {
    auto guard = boost::make_lock_guard(lockRoomsById);
    for (auto iterator = roomsById.begin(); iterator != roomsById.end();
         iterator++) {
        auto&& room = iterator->second;
        if (room->ContainsUser(user)) {
            room->RemoveUser(user);
        }
    }
}

// -------------------------------------------------------------------
// RemoveRoom
// -------------------------------------------------------------------
void SFSRoomManager::RemoveRoom(int id, const std::string& name) {
    lockRoomsById.lock();
    auto iteratorById = roomsById.find(id);
    if (iteratorById != roomsById.end()) {
        roomsById.erase(iteratorById);
    }
    lockRoomsById.unlock();

    lockRoomsByName.lock();
    auto iteratorByName = roomsByName.find(name);
    if (iteratorByName != roomsByName.end()) {
        roomsByName.erase(iteratorByName);
    }
    lockRoomsByName.unlock();
}
} // namespace Managers
} // namespace Entities
} // namespace Sfs2X
