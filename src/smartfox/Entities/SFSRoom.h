// ===================================================================
//
// Description
//        Contains the definition of SFSRoom
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __SFSRoom__
#define __SFSRoom__

#include "smartfox/Entities/Data/ISFSArray.h"
#include "smartfox/Entities/Room.h"
#include "smartfox/Entities/Managers/IRoomManager.h"

#include <boost/shared_ptr.hpp>              // Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp> // Boost shared_ptr for this

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object
#include <map>    // STL library: map object

namespace Sfs2X {
using namespace Exceptions;
using namespace Util;

namespace Entities {
using namespace Data;
using namespace Managers;
using namespace Variables;

/// <summary>
/// The <b>Room</b> object represent a server Room.
/// </summary>
/// <remarks>
/// The client API don't know about all Rooms on the server side but only about
/// those that are joined and those in the Room Groups that were subscribed.
/// <para/>
/// Subscribing to one or more Group allows the client to listen for Room events
/// in specific "areas" of the Zone without having to know and download details
/// for all Rooms available. <para/> The RoomList is created after a succesful
/// login in the <c>SmartFox.RoomList</c> object and it is kept updated at all
/// times by the Server.
/// </remarks>
/// <seealso cref="SmartFox.RoomList"/>
/// <seealso cref="Requests.CreateRoomRequest"/>
/// <seealso cref="Requests.JoinRoomRequest"/>
/// <seealso cref="Requests.SubscribeRoomGroupRequest"/>
/// <seealso cref="Requests.UnsubscribeRoomGroupRequest"/>
/// <seealso cref="Requests.ChangeRoomNameRequest"/>
/// <seealso cref="Requests.ChangeRoomPasswordStateRequest"/>
/// <seealso cref="Requests.ChangeRoomCapacityRequest"/>
class DLLImportExport SFSRoom : public Room,
                                public boost::enable_shared_from_this<SFSRoom> {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    explicit SFSRoom(int id, const std::string& name);
    explicit SFSRoom(int id, const std::string& name,
                     const std::string& groupId);

    virtual void Dispose() override;

    virtual ~SFSRoom() override;

    static boost::shared_ptr<Room>
    FromSFSArray(const boost::shared_ptr<ISFSArray>& sfsa);

    virtual int Id() const override;

    /// <summary>
    /// The Room name
    /// </summary>
    virtual boost::shared_ptr<std::string> Name() const override;

    /// <summary>
    /// The Room name
    /// </summary>
    virtual void Name(const std::string& value) override;

    /// <summary>
    /// The Room Group. Each Room is assigned to its Group.
    /// </summary>
    /// <remarks>
    /// By default SmartFoxServer uses one single group called <i>default</i>
    /// </remarks>
    virtual boost::shared_ptr<std::string> GroupId() const override;

    /// <summary>
    /// Determines if a Room is a Game Room
    /// </summary>
    virtual bool IsGame() const override;

    /// <summary>
    /// Determines if a Room is a Game Room
    /// </summary>
    virtual void IsGame(bool value) override;

    /// <summary>
    /// Determines if the Room is hidden
    /// </summary>
    virtual bool IsHidden() const override;

    /// <summary>
    /// Determines if the Room is hidden
    /// </summary>
    virtual void IsHidden(bool value) override;

    /// <summary>
    /// Returns true if the Room is joined by
    /// the current User
    /// </summary>
    virtual bool IsJoined() const override;

    /// <summary>
    /// Returns true if the Room is joined by
    /// the current User
    /// </summary>
    virtual void IsJoined(bool value) override;

    /// <summary>
    /// Returns true if the Room requires a
    /// password for joining it
    /// </summary>
    virtual bool IsPasswordProtected() const override;

    /// <summary>
    /// Returns true if the Room requires a
    /// password for joining it
    /// </summary>
    virtual void IsPasswordProtected(bool value) override;

    virtual bool IsManaged() const override;

    virtual void IsManaged(bool value) override;

    virtual std::size_t MaxSpectators() const override;
    virtual void MaxSpectators(std::size_t value) override;

    virtual boost::shared_ptr<std::map<std::string, std::string>>
    Properties() const override;

    virtual void Properties(
        const boost::shared_ptr<std::map<std::string, std::string>>& value)
        override;

    /// <summary>
    /// Returns all the Room Variables
    /// </summary>
    /// <returns>
    /// A vector of <see cref="RoomVariable"/>
    /// pointers
    /// </returns>
    virtual boost::shared_ptr<std::vector<boost::shared_ptr<RoomVariable>>>
    GetVariables() const override;

    /// <summary>
    /// Get a Room Variable
    /// </summary>
    /// <param name="name">
    /// the name of the variable
    /// </param>
    /// <returns>
    /// the Room Variable, or null if no
    /// variable exists with that name
    /// </returns>
    virtual boost::shared_ptr<RoomVariable>
    GetVariable(const std::string& name) const override;

    /// <summary>
    /// Get the current number of users
    /// </summary>
    /// <remarks>
    /// If the room is joined the user count is
    /// taken from the Room's UserManager
    /// otherwise we return the static counter
    /// (which will work only if you have
    /// activated the uCount updates)
    /// </remarks>
    virtual std::size_t UserCount() const override;

    /// <summary>
    /// Get the current number of users
    /// </summary>
    /// <remarks>
    /// If the room is joined the user count is
    /// taken from the Room's UserManager
    /// otherwise we return the static counter
    /// (which will work only if you have
    /// activated the uCount updates)
    /// </remarks>
    virtual void UserCount(std::size_t value) override;

    /// <summary>
    /// Get the maximum number of users allowed
    /// for this Room
    /// </summary>
    virtual std::size_t MaxUsers() const override;

    /// <summary>
    /// Get the maximum number of users allowed
    /// for this Room
    /// </summary>
    virtual void MaxUsers(std::size_t value) override;

    /// <summary>
    /// Returns the max amount of users (both
    /// Users and Spectators) that can be
    /// contained in this room
    /// </summary>
    virtual std::size_t Capacity() const override;

    /// <summary>
    /// Get the number of spectators (only for
    /// Game Rooms)
    /// </summary>
    virtual std::size_t SpectatorCount() const override;

    /// <summary>
    /// Get the number of spectators (only for
    /// Game Rooms)
    /// </summary>
    virtual void SpectatorCount(std::size_t value) override;

    /// <summary>
    /// Get a User from its name
    /// </summary>
    /// <param name="name">
    /// A string pointer
    /// </param>
    /// <returns>
    /// the User, or null if no User with that
    /// name exists in the Room
    /// </returns>
    virtual boost::shared_ptr<User>
    GetUserByName(const std::string& name) const override;

    /// <summary>
    /// Get a User from its ID
    /// </summary>
    /// <param name="id">
    /// A std::int32_teger
    /// </param>
    /// <returns>
    /// the User, or null if no User with that
    /// ID exists in the Room
    /// </returns>
    virtual boost::shared_ptr<User> GetUserById(int id) const override;

    /// <summary>
    /// Get the full list of users in the Room
    /// </summary>
    virtual boost::shared_ptr<std::vector<boost::shared_ptr<User>>>
    UserList() const override;

    boost::shared_ptr<std::vector<boost::shared_ptr<User>>> PlayerList() const;
    boost::shared_ptr<std::vector<boost::shared_ptr<User>>>
    SpectatorList() const;

    virtual void RemoveUser(const boost::shared_ptr<User>& user) override;

    virtual void
    SetVariable(const boost::shared_ptr<RoomVariable>& roomVariable) override;

    virtual void SetVariables(
        const boost::shared_ptr<std::vector<boost::shared_ptr<RoomVariable>>>&
            roomVariables) override;

    /// <summary>
    /// Check for the presence of a Room
    /// Variable
    /// </summary>
    /// <param name="name">
    /// A string pointer
    /// </param>
    /// <returns>
    /// true if the the Room Variable exists
    /// </returns>
    virtual bool ContainsVariable(const std::string& name) const override;

    virtual void AddUser(const boost::shared_ptr<User>& user) override;

    /// <summary>
    /// Checks if a User is joined in this Room
    /// </summary>
    /// <param name="user">
    /// Pointer to an <see cref="User"/>
    /// instance
    /// </param>
    /// <returns>
    /// true if the User exists in the Room
    /// </returns>
    virtual bool
    ContainsUser(const boost::shared_ptr<User>& user) const override;

    virtual boost::shared_ptr<IRoomManager> RoomManager() const override;

    virtual void
    RoomManager(const boost::shared_ptr<IRoomManager>& value) override;

    boost::shared_ptr<std::string> ToString() const;

    virtual void Merge(const boost::shared_ptr<Room>& anotherRoom) override;

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

    int id;
    boost::shared_ptr<std::string> name;
    boost::shared_ptr<std::string> groupId;
    bool isGame;
    bool isHidden;
    bool isJoined;
    bool isPasswordProtected;
    bool isManaged;
    boost::shared_ptr<std::map<std::string, boost::shared_ptr<RoomVariable>>>
        variables;
    boost::shared_ptr<std::map<std::string, std::string>> properties;
    mutable boost::shared_ptr<IUserManager> userManager;
    std::size_t maxUsers;
    std::size_t maxSpectators;
    std::size_t userCount; // only for non joined rooms
    std::size_t specCount; // only for non joined rooms
    boost::shared_ptr<IRoomManager> roomManager;

private:
    // -------------------------------------------------------------------
    // Private methods
    // -------------------------------------------------------------------

    void Init(int id, const std::string& name, const std::string& groupId);

    void RemoveUserVariable(const std::string& varName);

    const boost::shared_ptr<IUserManager>& UserManager() const;

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------
};
} // namespace Entities
} // namespace Sfs2X

#endif
