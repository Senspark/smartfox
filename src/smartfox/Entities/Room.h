// ===================================================================
//
// Description
//        Contains the definition of Room interface
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __Room__
#define __Room__

namespace Sfs2X {
namespace Entities {
class Room;
} // namespace Entities
} // namespace Sfs2X

#include "smartfox/Entities/User.h"
#include "smartfox/Util/Common.h"
#include "smartfox/Entities/Variables/RoomVariable.h"
#include "smartfox/Entities/Managers/IRoomManager.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object
#include <vector> // STL library: vector object
#include <map>    // STL library: map object

namespace Sfs2X {
namespace Entities {
using namespace Managers;
using namespace Variables;

class DLLImportExport Room {
public:
    virtual ~Room() = default;

    /// <summary>
    /// The unique Id of the Room
    /// </summary>
    virtual int Id() const = 0;

    /// <summary>
    /// The unique name of the Room
    /// </summary>
    virtual boost::shared_ptr<std::string> Name() const = 0;

    /// <summary>
    /// The unique name of the Room
    /// </summary>
    virtual void Name(const std::string& value) = 0;

    /// <summary>
    /// The Room <b>Group</b> name
    /// </summary>
    /// <remarks>
    /// Each <b>Group</b> is identified by a unique String and it represent a
    /// different 'container' for Rooms. The idea behind the Room Groups is to
    /// enable the developer to organize Rooms under different types or
    /// categories and let clients select only those Groups they are interested
    /// in. This is done via the <c>SubscribeRoomGroupRequest</c> and
    /// <c>UnsubscribeRoomGroupRequest</c> requests.
    /// </remarks>
    ///
    /// <seealso cref="Requests.SubscribeRoomGroupRequest"/>
    /// <seealso cref="Requests.UnsubscribeRoomGroupRequest"/>
    virtual boost::shared_ptr<std::string> GroupId() const = 0;

    /// <summary>
    /// Returns true if the Room is joined by the client User
    /// </summary>
    virtual bool IsJoined() const = 0;

    /// <summary>
    /// Returns true if the Room is joined by the client User
    /// </summary>
    virtual void IsJoined(bool value) = 0;

    /// <summary>
    /// Returns true is this is a game Room
    /// </summary>
    virtual bool IsGame() const = 0;

    /// <summary>
    /// Returns true is this is a game Room
    /// </summary>
    virtual void IsGame(bool value) = 0;

    /// <summary>
    /// Returns true if the Room <b>hidden</b> flag is turned on.
    /// </summary>
    /// <remarks>
    /// The flag can be used to hide the rooms marked with this flag from the
    /// User
    /// </remarks>
    virtual bool IsHidden() const = 0;

    /// <summary>
    /// Returns true if the Room <b>hidden</b> flag is turned on.
    /// </summary>
    /// <remarks>
    /// The flag can be used to hide the rooms marked with this flag from the
    /// User
    /// </remarks>
    virtual void IsHidden(bool value) = 0;

    /// <summary>
    /// Returns true if the Room requires a password to be joined
    /// </summary>
    virtual bool IsPasswordProtected() const = 0;

    /// <summary>
    /// Returns true if the Room requires a password to be joined
    /// </summary>
    virtual void IsPasswordProtected(bool value) = 0;

    virtual bool IsManaged() const = 0;

    virtual void IsManaged(bool value) = 0;

    /// <summary>
    /// Get the number of Users in the Room
    /// </summary>
    virtual std::size_t UserCount() const = 0;

    /// <summary>
    /// Get the number of Users in the Room
    /// </summary>
    virtual void UserCount(std::size_t value) = 0;

    /// <summary>
    /// Get the max number of Users allowed in the Room
    /// </summary>
    virtual std::size_t MaxUsers() const = 0;

    /// <summary>
    /// Get the max number of Users allowed in the Room
    /// </summary>
    virtual void MaxUsers(std::size_t value) = 0;

    /// <summary>
    /// Get the number of Spectators in the Room (applies only for game Rooms)
    /// </summary>
    virtual std::size_t SpectatorCount() const = 0;

    /// <summary>
    /// Get the number of Spectators in the Room (applies only for game Rooms)
    /// </summary>
    virtual void SpectatorCount(std::size_t value) = 0;

    /// <summary>
    /// Get the max number of Spectators allowed in the Room (applies only for
    /// game Rooms)
    /// </summary>
    virtual std::size_t MaxSpectators() const = 0;

    /// <summary>
    /// Get the max number of Spectators allowed in the Room (applies only for
    /// game Rooms)
    /// </summary>
    virtual void MaxSpectators(std::size_t value) = 0;

    // ???????????????????????????????????????
    virtual std::size_t Capacity() const = 0;

    virtual void AddUser(const boost::shared_ptr<User>& user) = 0;

    virtual void RemoveUser(const boost::shared_ptr<User>& user) = 0;

    /// <summary>
    /// Returns true if the the User is found in this Room
    /// </summary>
    /// <param name="user">
    /// Pointer to an <see cref="User"/> instance
    /// </param>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool ContainsUser(const boost::shared_ptr<User>& user) const = 0;

    /// <summary>
    /// Finds a User from its name
    /// </summary>
    /// <param name="name">
    /// the User name
    /// </param>
    /// <returns>
    /// the User or null if not found
    /// </returns>
    virtual boost::shared_ptr<User>
    GetUserByName(const std::string& name) const = 0;

    /// <summary>
    /// Finds a User from its Id
    /// </summary>
    /// <param name="id">
    /// the User Id
    /// </param>
    /// <returns>
    /// the User or null if not found
    /// </returns>
    virtual boost::shared_ptr<User> GetUserById(int id) const = 0;

    /// <summary>
    /// The Room User-list
    /// </summary>
    virtual boost::shared_ptr<std::vector<boost::shared_ptr<User>>>
    UserList() const = 0;

    /// <summary>
    /// Gets a RoomVariable in the Room
    /// </summary>
    /// <param name="name">
    /// the variable name
    /// </param>
    /// <returns>
    /// the RoomVariable or null if the variable doesn't exist
    /// </returns>
    /// <seealso cref="RoomVariable"/>
    virtual boost::shared_ptr<RoomVariable>
    GetVariable(const std::string& name) const = 0;

    /// <summary>
    /// Return the full list of RoomVariables in the Room
    /// </summary>
    /// <returns>
    /// A vector of <see cref="RoomVariable"/> pointers
    /// </returns>
    /// <seealso cref="RoomVariable"/>
    virtual boost::shared_ptr<std::vector<boost::shared_ptr<RoomVariable>>>
    GetVariables() const = 0;

    virtual void
    SetVariable(const boost::shared_ptr<RoomVariable>& roomVariable) = 0;

    virtual void SetVariables(
        const boost::shared_ptr<std::vector<boost::shared_ptr<RoomVariable>>>&
            roomVariables) = 0;

    /// <summary>
    /// Returns true if a RoomVariable with the passed name exists in the Room
    /// </summary>
    /// <param name="name">
    /// A string
    /// </param>
    /// <returns>
    /// A boolean
    /// </returns>
    /// <seealso cref="RoomVariable"/>
    virtual bool ContainsVariable(const std::string& name) const = 0;

    /// <summary>
    /// A generic object that can be used to store any Room custom data needed
    /// at runtime.
    /// </summary>
    /// <remarks>
    /// The values added/removed in this object are for client side use only an
    /// are never transmitted to the Server.
    /// </remarks>
    virtual boost::shared_ptr<std::map<std::string, std::string>>
    Properties() const = 0;

    /// <summary>
    /// A generic object that can be used to store any Room custom data needed
    /// at runtime.
    /// </summary>
    /// <remarks>
    /// The values added/removed in this object are for client side use only an
    /// are never transmitted to the Server.
    /// </remarks>
    virtual void Properties(
        const boost::shared_ptr<std::map<std::string, std::string>>& value) = 0;

    /// <summary>
    /// A reference to the RoomManager, managing this Room
    /// </summary>
    virtual boost::shared_ptr<IRoomManager> RoomManager() const = 0;

    /// <summary>
    /// A reference to the RoomManager, managing this Room
    /// </summary>
    virtual void RoomManager(const boost::shared_ptr<IRoomManager>& value) = 0;

    virtual void Merge(const boost::shared_ptr<Room>& anotherRoom) = 0;

    virtual void Dispose() = 0;
};
} // namespace Entities
} // namespace Sfs2X

#endif
