// ===================================================================
//
// Description
//        Contains the definition of SFSUserManager
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __SFSUserManager__
#define __SFSUserManager__

#include "IUserManager.h"
#include "../User.h"
#include "../../SmartFox.h"
#include "../Room.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <map>       // STL library: map object
#include <vector>    // STL library: vector object
#include <string>    // STL library: string object

namespace Sfs2X {
using namespace Logging;

namespace Entities {
namespace Managers {

/// <summary>
/// Manages the local Users.
/// </summary>
/// <remarks>
/// The client side API only see the Users that are joined in the same Rooms of
/// the current User.
/// </remarks>
class DLLImportExport SFSUserManager : public IUserManager {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    SFSUserManager(const boost::shared_ptr<SmartFox>& sfs);
    SFSUserManager(const boost::shared_ptr<Room>& room);
    virtual void Dispose() override;
    virtual ~SFSUserManager() override;
    virtual bool ContainsUserName(const std::string& userName) override;
    virtual bool ContainsUserId(int userId) override;
    virtual bool ContainsUser(const boost::shared_ptr<User>& user) override;
    virtual boost::shared_ptr<User> GetUserByName(const std::string& userName) override;
    virtual boost::shared_ptr<User> GetUserById(int userId) override;
    virtual void AddUser(const boost::shared_ptr<User>& user) override;
    virtual void RemoveUser(const boost::shared_ptr<User>& user) override;
    virtual void RemoveUserById(int id) override;
    virtual std::size_t UserCount() override;
    virtual boost::shared_ptr<SmartFox> SmartFoxClient() override;
    virtual boost::shared_ptr<std::vector<boost::shared_ptr<User>>> GetUserList() override;
    virtual void ClearAll() override;

    // -------------------------------------------------------------------
    // Public members
    // -------------------------------------------------------------------

protected:
    // -------------------------------------------------------------------
    // Protected methods
    // -------------------------------------------------------------------

    void LogWarn(const boost::shared_ptr<std::string>& msg);
    void AddUserInternal(const boost::shared_ptr<User>& user);

    // -------------------------------------------------------------------
    // Protected members
    // -------------------------------------------------------------------

    boost::shared_ptr<Room> room;
    boost::shared_ptr<SmartFox> sfs;

private:
    // -------------------------------------------------------------------
    // Private methods
    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------

    boost::shared_ptr<std::map<std::string, boost::shared_ptr<User>>>
        usersByName;
    boost::shared_ptr<std::map<int, boost::shared_ptr<User>>>
        usersById;

    boost::recursive_mutex lockUsersById;
    boost::recursive_mutex lockUsersByName;
};
} // namespace Managers
} // namespace Entities
} // namespace Sfs2X

#endif
