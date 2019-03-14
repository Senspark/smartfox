// ===================================================================
//
// Description
//        Contains the definition of IRoomManager interface
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __IRoomManager__
#define __IRoomManager__

// Forward class declaration
namespace Sfs2X {
namespace Entities {
namespace Managers {
class IRoomManager;
} // namespace Managers
} // namespace Entities
} // namespace Sfs2X

#include "../Room.h"
#include "../../SmartFox.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object
#include <vector> // STL library: vector object

namespace Sfs2X {
namespace Entities {
namespace Managers {

/// <summary>
/// The Room Manager interface
/// </summary>
class DLLImportExport IRoomManager {
public:
    virtual ~IRoomManager() = default;

    virtual boost::shared_ptr<std::string> OwnerZone() = 0;

    virtual void AddRoom(const boost::shared_ptr<Room>& room,
                         bool addGroupIfMissing) = 0;

    virtual void AddRoom(const boost::shared_ptr<Room>& room) = 0;

    virtual void AddGroup(const std::string& groupId) = 0;

    virtual boost::shared_ptr<Room>
    ReplaceRoom(const boost::shared_ptr<Room>& room,
                bool addToGroupIfMissing) = 0;

    virtual boost::shared_ptr<Room>
    ReplaceRoom(const boost::shared_ptr<Room>& room) = 0;

    virtual void RemoveGroup(const std::string& groupId) = 0;

    virtual bool ContainsGroup(const std::string& groupId) = 0;

    virtual bool ContainsRoom(int id) = 0;

    virtual bool ContainsRoom(const std::string& name) = 0;

    virtual bool ContainsRoomInGroup(int id, const std::string& groupId) = 0;

    virtual bool ContainsRoomInGroup(const std::string& name,
                                     const std::string& groupId) = 0;

    virtual void ChangeRoomName(const boost::shared_ptr<Room>& room,
                                const std::string& newName) = 0;

    virtual void ChangeRoomPasswordState(const boost::shared_ptr<Room>& room,
                                         bool isPassProtected) = 0;

    virtual void ChangeRoomCapacity(const boost::shared_ptr<Room>& room,
                                    std::size_t maxUsers,
                                    std::size_t maxSpect) = 0;

    virtual boost::shared_ptr<Room> GetRoomById(int id) = 0;

    virtual boost::shared_ptr<Room> GetRoomByName(const std::string& name) = 0;

    virtual boost::shared_ptr<std::vector<boost::shared_ptr<Room>>>
    GetRoomList() = 0;

    virtual std::size_t GetRoomCount() = 0;

    virtual boost::shared_ptr<std::vector<std::string>> GetRoomGroups() = 0;

    virtual boost::shared_ptr<std::vector<boost::shared_ptr<Room>>>
    GetRoomListFromGroup(const std::string& groupId) = 0;

    virtual boost::shared_ptr<std::vector<boost::shared_ptr<Room>>>
    GetJoinedRooms() = 0;

    virtual boost::shared_ptr<std::vector<boost::shared_ptr<Room>>>
    GetUserRooms(const boost::shared_ptr<User>& user) = 0;

    virtual void RemoveRoom(const boost::shared_ptr<Room>& room) = 0;

    virtual void RemoveRoomById(int id) = 0;

    virtual void RemoveRoomByName(const std::string& name) = 0;

    virtual void RemoveUser(const boost::shared_ptr<User>& user) = 0;

    virtual boost::shared_ptr<SmartFox> SmartFoxClient() = 0;

    virtual void Dispose() = 0;
};
} // namespace Managers
} // namespace Entities
} // namespace Sfs2X

#endif
