// ===================================================================
//
// Description
//        Contains the definition of SFSRoomManager
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __SFSRoomManager__
#define __SFSRoomManager__

#include "IRoomManager.h"
#include "../../SmartFox.h"
#include "../Room.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <map>    // STL library: map object
#include <vector> // STL library: vector object
#include <string> // STL library: string object

namespace Sfs2X {
using namespace Util;

namespace Entities {
namespace Managers {

// -------------------------------------------------------------------
// Class SFSRoomManager
// -------------------------------------------------------------------
class SFSRoomManager : public IRoomManager {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    explicit SFSRoomManager(const boost::shared_ptr<SmartFox>& sfs);

    virtual void Dispose() override;

    virtual ~SFSRoomManager() override;

    virtual boost::shared_ptr<std::string> OwnerZone() override;

    void OwnerZone(const std::string& value);

    virtual boost::shared_ptr<SmartFox> SmartFoxClient() override;

    virtual void AddRoom(const boost::shared_ptr<Room>& room) override;

    virtual void AddRoom(const boost::shared_ptr<Room>& room,
                         bool addGroupIfMissing) override;

    virtual boost::shared_ptr<Room>
    ReplaceRoom(const boost::shared_ptr<Room>& room) override;

    virtual boost::shared_ptr<Room>
    ReplaceRoom(const boost::shared_ptr<Room>& room,
                bool addToGroupIfMissing) override;

    virtual void ChangeRoomName(const boost::shared_ptr<Room>& room,
                                const std::string& newName) override;

    virtual void ChangeRoomPasswordState(const boost::shared_ptr<Room>& room,
                                         bool isPassProtected) override;

    virtual void ChangeRoomCapacity(const boost::shared_ptr<Room>& room,
                                    std::size_t maxUsers,
                                    std::size_t maxSpect) override;

    virtual boost::shared_ptr<std::vector<std::string>>
    GetRoomGroups() override;

    virtual void AddGroup(const std::string& groupId) override;

    virtual void RemoveGroup(const std::string& groupId) override;

    virtual bool ContainsGroup(const std::string& groupId) override;

    virtual bool ContainsRoom(int id) override;

    virtual bool ContainsRoom(const std::string& name) override;

    virtual bool ContainsRoomInGroup(int id,
                                     const std::string& groupId) override;

    virtual bool ContainsRoomInGroup(const std::string& name,
                                     const std::string& groupId) override;

    virtual boost::shared_ptr<Room> GetRoomById(int id) override;

    virtual boost::shared_ptr<Room>
    GetRoomByName(const std::string& name) override;

    virtual boost::shared_ptr<std::vector<boost::shared_ptr<Room>>>
    GetRoomList() override;

    virtual std::size_t GetRoomCount() override;

    virtual boost::shared_ptr<std::vector<boost::shared_ptr<Room>>>
    GetRoomListFromGroup(const std::string& groupId) override;

    virtual void RemoveRoom(const boost::shared_ptr<Room>& room) override;

    virtual void RemoveRoomById(int id) override;

    virtual void RemoveRoomByName(const std::string& name) override;

    /// <summary>
    /// Return rooms joined by local user
    /// </summary>
    /// <returns>
    /// A vector of <see cref="Room"/> pointers
    /// </returns>
    /// boost::shared_ptr<std::vector<boost::shared_ptr<Room>>>
    /// GetJoinedRooms();
    virtual boost::shared_ptr<std::vector<boost::shared_ptr<Room>>>
    GetJoinedRooms() override;

    virtual boost::shared_ptr<std::vector<boost::shared_ptr<Room>>>
    GetUserRooms(const boost::shared_ptr<User>& user) override;

    virtual void RemoveUser(const boost::shared_ptr<User>& user) override;

    // -------------------------------------------------------------------
    // Public members
    // -------------------------------------------------------------------

protected:
    // -------------------------------------------------------------------
    // Protected methods
    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    // Protected members
    // -------------------------------------------------------------------

    boost::shared_ptr<SmartFox> smartFox;

private:
    // -------------------------------------------------------------------
    // Private methods
    // -------------------------------------------------------------------

    void RemoveRoom(int id, const std::string& name);

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------

    boost::shared_ptr<std::string> ownerZone;
    std::vector<std::string> groups;
    std::map<int, boost::shared_ptr<Room>> roomsById;
    std::map<std::string, boost::shared_ptr<Room>> roomsByName;

    boost::recursive_mutex lockRoomsById;
    boost::recursive_mutex lockRoomsByName;
    boost::recursive_mutex lockGroups;
};
} // namespace Managers
} // namespace Entities
} // namespace Sfs2X

#endif
