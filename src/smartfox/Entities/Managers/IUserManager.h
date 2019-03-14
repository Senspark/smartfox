// ===================================================================
//
// Description
//        Contains the definition of IUserManager interface
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __IUserManager__
#define __IUserManager__

// Forward class declaration
namespace Sfs2X {
namespace Entities {
namespace Managers {
class IUserManager;
} // namespace Managers
} // namespace Entities
} // namespace Sfs2X

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object
#include <vector> // STL library: vector object

#include "../User.h"
#include "../../SmartFox.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

namespace Sfs2X {
namespace Entities {
namespace Managers {

/// <summary>
/// The User Manager interface
/// </summary>
class DLLImportExport IUserManager {
public:
    virtual ~IUserManager() = default;
    
    /// <summary>
    /// Checks if a specific User name exists in the local User list
    /// </summary>
    /// <param name="userName">
    /// A string pointer
    /// </param>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool ContainsUserName(const std::string& userName) = 0;

    /// <summary>
    /// Checks if a specific User id exists in the local User list
    /// </summary>
    /// <param name="userId">
    /// A long integer
    /// </param>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool ContainsUserId(int userId) = 0;

    /// <summary>
    /// Checks if a specific User object exists in the local User list
    /// </summary>
    /// <param name="user">
    /// Pointer to an <see cref="User"/> instance
    /// </param>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool ContainsUser(const boost::shared_ptr<User>& user) = 0;

    /// <summary>
    /// Get a User object from its name
    /// </summary>
    /// <param name="userName">
    /// A string pointer
    /// </param>
    /// <returns>
    /// Pointer to an <see cref="User"/> instance
    /// </returns>
    virtual boost::shared_ptr<User>
    GetUserByName(const std::string& userName) = 0;

    /// <summary>
    /// Get a User object from its id
    /// </summary>
    /// <param name="userId">
    /// A long integer
    /// </param>
    /// <returns>
    /// Pointer to an <see cref="User"/> instance
    /// </returns>
    virtual boost::shared_ptr<User> GetUserById(int userId) = 0;

    virtual void AddUser(const boost::shared_ptr<User>& user) = 0;

    virtual void RemoveUser(const boost::shared_ptr<User>& user) = 0;

    virtual void RemoveUserById(int id) = 0;

    /// <summary>
    /// Get the total number of Users
    /// </summary>
    virtual std::size_t UserCount() = 0;

    /// <summary>
    /// Get the full list of Users
    /// </summary>
    /// <returns>
    /// A vector of <see cref="User"/> pointers
    /// </returns>
    virtual boost::shared_ptr<std::vector<boost::shared_ptr<User>>>
    GetUserList() = 0;

    virtual boost::shared_ptr<SmartFox> SmartFoxClient() = 0;

    virtual void ClearAll() = 0;

    virtual void Dispose() = 0;
};
} // namespace Managers
} // namespace Entities
} // namespace Sfs2X

#endif
