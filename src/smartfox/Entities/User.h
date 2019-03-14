// ===================================================================
//
// Description
//        Contains the definition of User interface
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __User__
#define __User__

namespace Sfs2X {
namespace Entities {
class User;
} // namespace Entities
} // namespace Sfs2X

#include "smartfox/Util/Common.h"
#include "smartfox/Entities/Variables/UserVariable.h"
#include "smartfox/Entities/Managers/IUserManager.h"
#include "smartfox/Entities/Room.h"
#include "smartfox/Entities/Data/Vec3D.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object
#include <list>   // STL library: list object
#include <vector> // STL library: vector object
#include <map>    // STL library: map object

namespace Sfs2X {
namespace Entities {
using namespace Managers;
using namespace Data;
using namespace Variables;

/// <summary>
/// The User interface defines all the methods and properties that an object
/// representing a SmartFoxServer User entity exposes.
/// </summary>
///
/// <remarks>
/// In the SmartFoxServer 2X client API this interface is implemented by the
/// <see cref="SFSUser"/> class. Read the class description for additional
/// informations.
/// </remarks>
///
/// <seealso cref="SFSUser"/>
class DLLImportExport User {
public:
    virtual ~User() = default;

    /// <summary>
    /// Get the unique User Id
    /// </summary>
    virtual int Id() const = 0;

    /// <summary>
    /// The user name
    /// </summary>
    virtual boost::shared_ptr<std::string> Name() const = 0;

    /// <summary>
    /// Get the <b>playerId</b> of the User.
    /// </summary>
    /// <remarks>
    /// The <b>playerId</b> is different from the User ID and it used to
    /// indicate which player number is the user inside a Game Room. Example: in
    /// a Game Room for 5 players the first client joining will have <b>playerId
    /// = 1</b>, the 2nd will have <b>playerId = 2</b> and so forth. When a User
    /// leaves the Room its player slot is freed up and the next User joining
    /// the Room will take it.
    ///
    /// The <b>playerId</b> is only applicable for Game Rooms, in the other
    /// Rooms it is always == 0 A playerId < 0 indicates that the User is a
    /// spectator.
    ///
    /// If the User is joined in multiple game Rooms at the same time he will be
    /// assigned one <b>playerId</b> per Room. In order to obtain a specific
    /// <b>playerId</b> you can use the <c>User.GetPlayerId(Room room)</c>
    /// method.
    /// </remarks>
    virtual int PlayerId() const = 0;

    /// <summary>
    /// Return true if the User is a Player (playerId > 0) in the last joined
    /// Room
    /// </summary>
    /// <remarks>
    /// Non game Rooms will always return false
    /// </remarks>
    /// <seealso cref="SmartFox.LastJoinedRoom"/>
    virtual bool IsPlayer() const = 0;

    /// <summary>
    /// Return true if the User is a Spectator (playerId < 0) in the last joined
    /// Room
    /// </summary>
    /// <remarks>
    /// Non game Rooms will always return false
    /// </remarks>
    /// <seealso cref="SmartFox.LastJoinedRoom"/>
    virtual bool IsSpectator() const = 0;

    /// <summary>
    /// Return the <b>playerId</b> for the specific Room.
    /// </summary>
    /// <remarks>
    /// If you don't use multi-room you can use <c>User.PlayerId</c>
    /// </remarks>
    /// <param name="room">
    /// Pointer to a <see cref="Room"/> instance
    /// </param>
    /// <returns>
    /// A long integer
    /// </returns>
    /// <seealso cref="PlayerId"/>
    virtual int GetPlayerId(const boost::shared_ptr<Room>& room) const = 0;

    virtual void SetPlayerId(int id,
                             const boost::shared_ptr<Room>& room) const = 0;

    virtual void RemovePlayerId(const boost::shared_ptr<Room>& room) const = 0;

    /// <summary>
    /// Get the privilegeId of the User
    /// </summary>
    /// <seealso cref="UserPrivileges"/>
    virtual int PrivilegeId() const = 0;

    /// <summary>
    /// Get the privilegeId of the User
    /// </summary>
    /// <seealso cref="UserPrivileges"/>
    virtual void PrivilegeId(int value) = 0;

    /// <summary>
    /// Get the UserManager of this User
    /// </summary>
    /// <seealso cref="SFSUserManager"/>
    virtual boost::shared_ptr<IUserManager> UserManager() const = 0;

    /// <summary>
    /// Get the UserManager of this User
    /// </summary>
    /// <seealso cref="SFSUserManager"/>
    virtual void UserManager(const boost::shared_ptr<IUserManager>& value) = 0;

    //--------------------------------------------------

    /// <summary>
    /// Return true if the User is logged in as guest user
    /// </summary>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool IsGuest() const = 0;

    /// <summary>
    /// Return true if the User is logged in as standard user
    /// </summary>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool IsStandardUser() const = 0;

    /// <summary>
    /// Return true if the User is logged in as moderator user
    /// </summary>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool IsModerator() const = 0;

    /// <summary>
    /// Return true if the User is logged in as administrator user
    /// </summary>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool IsAdmin() const = 0;
    //--------------------------------------------------

    /// <summary>
    /// Return true if the User is a Player in the specified Room
    /// </summary>
    /// <param name="room">
    /// Pointer to a <see cref="Room"/> instance
    /// </param>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool IsPlayerInRoom(const boost::shared_ptr<Room>& room) const = 0;

    /// <summary>
    /// Return true if the User is a Spectator in the specified Room
    /// </summary>
    /// <param name="room">
    /// Pointer to a <see cref="Room"/> instance
    /// </param>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool
    IsSpectatorInRoom(const boost::shared_ptr<Room>& room) const = 0;

    /// <summary>
    /// Return true if the User is joined in the specified Room
    /// </summary>
    /// <param name="room">
    /// Pointer to a <see cref="Room"/> instance
    /// </param>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool IsJoinedInRoom(const boost::shared_ptr<Room>& room) const = 0;

    /// <summary>
    /// Return true if the User object is the client's User object, also known
    /// as <c>SmartFox.MySelf</c>
    /// </summary>
    virtual bool IsItMe() const = 0;

    /// <summary>
    /// Get all the User Variables
    /// </summary>
    /// <returns>
    /// A vector of <see cref="UserVariable"/> pointers
    /// </returns>
    /// <seealso cref="UserVariable"/>
    virtual boost::shared_ptr<std::vector<boost::shared_ptr<UserVariable>>>
    GetVariables() const = 0;

    /// <summary>
    /// Get a UserVariable
    /// </summary>
    /// <param name="varName">
    /// the name of the variable
    /// </param>
    /// <returns>
    /// the UserVariable or null if the variable doesn't exist
    /// </returns>
    /// <seealso cref="UserVariable"/>
    virtual boost::shared_ptr<UserVariable>
    GetVariable(const std::string& varName) const = 0;

    virtual void
    SetVariable(const boost::shared_ptr<UserVariable>& userVariable) = 0;

    virtual void SetVariables(
        const boost::shared_ptr<std::vector<boost::shared_ptr<UserVariable>>>&
            userVaribles) = 0;

    /// <summary>
    /// Check if a UserVariable exists
    /// </summary>
    /// <param name="name">
    /// the name of the variable
    /// </param>
    /// <returns>
    /// true if the UserVariable exists
    /// </returns>
    /// <seealso cref="UserVariable"/>
    virtual bool ContainsVariable(const std::string& name) const = 0;

    /// <summary>
    /// A generic object that can be used to store any User custom data needed
    /// at runtime.
    /// </summary>
    /// <remarks>
    /// The values added/removed in this object are for client side use only an
    /// are never transmitted to the Server.
    /// </remarks>
    virtual boost::shared_ptr<std::map<std::string, boost::shared_ptr<void>>>
    Properties() const = 0;

    /// <summary>
    /// A generic object that can be used to store any User custom data needed
    /// at runtime.
    /// </summary>
    /// <remarks>
    /// The values added/removed in this object are for client side use only an
    /// are never transmitted to the Server.
    /// </remarks>
    virtual void Properties(
        const boost::shared_ptr<std::map<std::string, boost::shared_ptr<void>>>&
            value) = 0;

    /// <summary>
    /// Returns the entry point of this user in the current user's AoI.
    /// </summary>
    ///
    /// <remarks>
    /// The returned coordinates are those that the user had when his presence
    /// in the current user's Area of Interest was last notified by a <see
    /// cref="Sfs2X.Core.SFSEvent.PROXIMITY_LIST_UPDATE">PROXIMITY_LIST_UPDATE</see>
    /// event. This field is populated only if the user joined a Room of type
    /// MMORoom and this is configured to receive such data from the server.
    /// </remarks>
    ///
    /// <seealso cref="Sfs2X.Requests.MMO.MMORoomSettings.SendAOIEntryPoint"/>
    /// <seealso cref="Sfs2X.Core.SFSEvent.PROXIMITY_LIST_UPDATE"/>
    virtual boost::shared_ptr<Vec3D> AOIEntryPoint() const = 0;

    /// <summary>
    /// Returns the entry point of this user in the current user's AoI.
    /// </summary>
    ///
    /// <remarks>
    /// The returned coordinates are those that the user had when his presence
    /// in the current user's Area of Interest was last notified by a <see
    /// cref="Sfs2X.Core.SFSEvent.PROXIMITY_LIST_UPDATE">PROXIMITY_LIST_UPDATE</see>
    /// event. This field is populated only if the user joined a Room of type
    /// MMORoom and this is configured to receive such data from the server.
    /// </remarks>
    ///
    /// <seealso cref="Sfs2X.Requests.MMO.MMORoomSettings.SendAOIEntryPoint"/>
    /// <seealso cref="Sfs2X.Core.SFSEvent.PROXIMITY_LIST_UPDATE"/>
    virtual void AOIEntryPoint(const boost::shared_ptr<Vec3D>& value) = 0;
};
} // namespace Entities
} // namespace Sfs2X

#endif
