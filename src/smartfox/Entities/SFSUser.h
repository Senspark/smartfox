// ===================================================================
//
// Description
//        Contains the definition of SFSUser
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __SFSUser__
#define __SFSUser__

#include "smartfox/Entities/User.h"
#include "smartfox/Entities/Data/Vec3D.h"

#include <boost/shared_ptr.hpp>              // Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp> // Boost shared_ptr for this

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object
#include <list>   // STL library: list object
#include <vector> // STL library: vector object
#include <map>    // STL library: map object

namespace Sfs2X {
using namespace Exceptions;

namespace Entities {
using namespace Data;
using namespace Managers;
using namespace Variables;

/// <summary>
/// The <b>User</b> object represent a client logged in the Server.
/// </summary>
/// <remarks>
/// The client API don't know about all Users connected to the server side but
/// only about those that are in the same Rooms where the client is joined.
/// <para/>
/// In order to interact with other Users the client can join different Rooms or
/// use a BuddyList to keep track of and interact with his friends.
/// </remarks>
class DLLImportExport SFSUser : public User,
                                public boost::enable_shared_from_this<SFSUser> {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    static boost::shared_ptr<User>
    FromSFSArray(const boost::shared_ptr<ISFSArray>& sfsa,
                 const boost::shared_ptr<Room>& room);

    static boost::shared_ptr<User>
    FromSFSArray(const boost::shared_ptr<ISFSArray>& sfsa);

    explicit SFSUser(int id, const std::string& name);
    explicit SFSUser(int id, const std::string& name, bool isItMe);

    virtual ~SFSUser() override;

    /// <summary>
    /// Get the unique User Id
    /// </summary>
    virtual int Id() const override;

    /// <summary>
    /// The user name
    /// </summary>
    virtual boost::shared_ptr<std::string> Name() const override;

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
    virtual int PlayerId() const override;

    /// <summary>
    /// Return true if the User is a Player (playerId > 0) in the last joined
    /// Room
    /// </summary>
    /// <remarks>
    /// Non game Rooms will always return false
    /// </remarks>
    /// <seealso cref="SmartFox.LastJoinedRoom"/>
    virtual bool IsPlayer() const override;

    /// <summary>
    /// Return true if the User is a Spectator (playerId < 0) in the last joined
    /// Room
    /// </summary>
    /// <remarks>
    /// Non game Rooms will always return false
    /// </remarks>
    /// <seealso cref="SmartFox.LastJoinedRoom"/>
    virtual bool IsSpectator() const override;

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
    virtual int GetPlayerId(const boost::shared_ptr<Room>& room) const override;

    virtual void
    SetPlayerId(int id, const boost::shared_ptr<Room>& room) const override;

    virtual void
    RemovePlayerId(const boost::shared_ptr<Room>& room) const override;

    /// <summary>
    /// Get the privilegeId of the User
    /// </summary>
    /// <seealso cref="UserPrivileges"/>
    virtual int PrivilegeId() const override;

    /// <summary>
    /// Get the privilegeId of the User
    /// </summary>
    /// <seealso cref="UserPrivileges"/>
    virtual void PrivilegeId(int value) override;

    /// <summary>
    /// Get the UserManager of this User
    /// </summary>
    /// <seealso cref="SFSUserManager"/>
    virtual boost::shared_ptr<IUserManager> UserManager() const override;

    /// <summary>
    /// Get the UserManager of this User
    /// </summary>
    /// <seealso cref="SFSUserManager"/>
    virtual void
    UserManager(const boost::shared_ptr<IUserManager>& value) override;

    /// <inheritdoc />
    virtual boost::shared_ptr<Vec3D> AOIEntryPoint() const override;

    /// <inheritdoc />
    virtual void AOIEntryPoint(const boost::shared_ptr<Vec3D>& value) override;

    //--------------------------------------------------

    /// <summary>
    /// Return true if the User is logged in as guest user
    /// </summary>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool IsGuest() const override;

    /// <summary>
    /// Return true if the User is logged in as standard user
    /// </summary>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool IsStandardUser() const override;

    /// <summary>
    /// Return true if the User is logged in as moderator user
    /// </summary>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool IsModerator() const override;

    /// <summary>
    /// Return true if the User is logged in as administrator user
    /// </summary>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool IsAdmin() const override;

    /// <summary>
    /// Return true if the User is a Player in the specified Room
    /// </summary>
    /// <param name="room">
    /// Pointer to a <see cref="Room"/> instance
    /// </param>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool
    IsPlayerInRoom(const boost::shared_ptr<Room>& room) const override;

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
    IsSpectatorInRoom(const boost::shared_ptr<Room>& room) const override;

    /// <summary>
    /// Return true if the User is joined in the specified Room
    /// </summary>
    /// <param name="room">
    /// Pointer to a <see cref="Room"/> instance
    /// </param>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool
    IsJoinedInRoom(const boost::shared_ptr<Room>& room) const override;

    /// <summary>
    /// Return true if the User object is the client's User object, also known
    /// as <c>SmartFox.MySelf</c>
    /// </summary>
    virtual bool IsItMe() const override;

    /// <summary>
    /// Get all the User Variables
    /// </summary>
    /// <returns>
    /// A vector of <see cref="UserVariable"/> pointers
    /// </returns>
    /// <seealso cref="UserVariable"/>
    virtual boost::shared_ptr<std::vector<boost::shared_ptr<UserVariable>>>
    GetVariables() const override;

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
    GetVariable(const std::string& varName) const override;

    virtual void
    SetVariable(const boost::shared_ptr<UserVariable>& userVariable) override;

    virtual void SetVariables(
        const boost::shared_ptr<std::vector<boost::shared_ptr<UserVariable>>>&
            userVaribles) override;

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
    bool ContainsVariable(const std::string& name) const override;

    /// <summary>
    /// A generic object that can be used to store any User custom data needed
    /// at runtime.
    /// </summary>
    /// <remarks>
    /// The values added/removed in this object are for client side use only an
    /// are never transmitted to the Server.
    /// </remarks>
    virtual boost::shared_ptr<std::map<std::string, boost::shared_ptr<void>>>
    Properties() const override;

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
            value) override;

    boost::shared_ptr<std::string> ToString() const;

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
    int privilegeId;
    boost::shared_ptr<std::string> name;
    bool isItMe;
    boost::shared_ptr<std::map<std::string, boost::shared_ptr<UserVariable>>>
        variables;
    boost::shared_ptr<std::map<std::string, boost::shared_ptr<void>>>
        properties;
    bool isModerator;
    boost::shared_ptr<std::map<int, int>> playerIdByRoomId;
    boost::shared_ptr<IUserManager> userManager;
    boost::shared_ptr<Vec3D> aoiEntryPoint;

private:
    // -------------------------------------------------------------------
    // Private methods
    // -------------------------------------------------------------------

    void Init(int id, const std::string& name, bool isItMe);
    void RemoveUserVariable(const std::string& varName);

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------
};
} // namespace Entities
} // namespace Sfs2X

#endif
