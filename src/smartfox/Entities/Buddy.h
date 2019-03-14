// ===================================================================
//
// Description
//        Contains the definition of Buddy interface
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __Buddy__
#define __Buddy__

#include "../Util/Common.h"
#include "Variables/BuddyVariable.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string>    // STL library: string object
#include <list>      // STL library: list object
#include <vector>    // STL library: vector object

namespace Sfs2X {
namespace Entities {
using namespace Variables;

/// <summary>
/// <see cref="SFSBuddy"/>
/// </summary>
class DLLImportExport Buddy {
public:
    virtual ~Buddy() = default;
    
    /// <summary>
    /// The id of the Buddy
    /// </summary>
    /// <remarks>
    /// The id corresponds to the current id of the User in the system
    /// </remarks>
    virtual int Id() const = 0;

    /// <summary>
    /// The id of the Buddy
    /// </summary>
    /// <remarks>
    /// The id corresponds to the current id of the User in the system
    /// </remarks>
    virtual void Id(int value) = 0;

    /// <summary>
    /// The name of the Buddy
    /// </summary>
    virtual boost::shared_ptr<std::string> Name() const = 0;

    /// <summary>
    /// Return true if the Buddy is blocked in the current Users' BuddyList
    /// </summary>
    /// <seealso cref="Requests.BlockBuddyRequest"/>
    virtual bool IsBlocked() const = 0;

    /// <summary>
    /// Return true if the Buddy is blocked in the current Users' BuddyList
    /// </summary>
    /// <seealso cref="Requests.BlockBuddyRequest"/>
    virtual void IsBlocked(bool value) = 0;

    /// <summary>
    /// Return true if the User is online in the BuddyList system
    /// </summary>
    /// <remarks>
    /// The value is stored in a reserved Buddy Variable
    /// </remarks>
    ///
    /// <seealso cref="Requests.GoOnlineRequest"/>
    /// <seealso cref="ReservedBuddyVariables"/>
    virtual bool IsOnline() const = 0;

    /// <summary>
    /// Return true if the Buddy is temporary (not persistent)
    /// </summary>
    virtual bool IsTemp() const = 0;

    /// <summary>
    /// The current Buddy custom state (e.g. "Available", "Busy", etc...)
    /// </summary>
    /// <remarks>
    /// The value is stored in a reserved Buddy Variable
    /// </remarks>
    /// <seealso cref="ReservedBuddyVariables"/>
    virtual boost::shared_ptr<std::string> State() const = 0;

    /// <summary>
    /// An optional Buddy nickname
    /// </summary>
    /// <remarks>
    /// The value is stored in a reserved Buddy Variable
    /// </remarks>
    /// <seealso cref="ReservedBuddyVariables"/>
    virtual boost::shared_ptr<std::string> NickName() const = 0;

    /// <summary>
    /// Obtain a list of BuddyVariables.
    /// </summary>
    /// <remarks>
    /// Please note that by convention any variable whose name starts with the
    /// dollar sign ($) will be regarded as persistent and stored locally by the
    /// server.
    ///
    /// These variables are also referred to as "offline variables" because they
    /// are available to other Users even when the Buddy is offline.
    /// </remarks>
    /// <seealso cref="SFSBuddyVariable"/>
    /// <seealso cref="Requests.SetBuddyVariablesRequest"/>
    virtual boost::shared_ptr<std::vector<boost::shared_ptr<BuddyVariable>>>
    Variables() const = 0;

    /// <summary>
    /// Get the BuddyVariable with the provided name.
    /// </summary>
    /// <remarks>
    /// Null is returned if not BuddyVariable exists with that name
    /// </remarks>
    /// <param name="varName">
    /// A string
    /// </param>
    /// <returns>
    /// Pointer to a <see cref="BuddyVariable"/> instance
    /// </returns>
    virtual boost::shared_ptr<BuddyVariable>
    GetVariable(const std::string& varName) const = 0;

    /// <summary>
    /// Return true if a BuddyVariable with the provided name exists
    /// </summary>
    /// <param name="varName">
    /// A string
    /// </param>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool ContainsVariable(const std::string& varName) const = 0;

    /// <summary>
    /// Return a list of offline Buddy Variables
    /// </summary>
    /// <returns>
    /// A vector of <see cref="BuddyVariable"/> pointers
    /// </returns>
    virtual boost::shared_ptr<std::vector<boost::shared_ptr<BuddyVariable>>>
    GetOfflineVariables() const = 0;

    /// <summary>
    /// Return a list of non-persistent Buddy Variables
    /// </summary>
    /// <returns>
    /// A vector of <see cref="BuddyVariable"/> pointers
    /// </returns>
    virtual boost::shared_ptr<std::vector<boost::shared_ptr<BuddyVariable>>>
    GetOnlineVariables() const = 0;

    virtual void SetVariable(boost::shared_ptr<BuddyVariable> bVar) = 0;

    virtual void SetVariables(
        boost::shared_ptr<std::vector<boost::shared_ptr<BuddyVariable>>>
            variables) = 0;

    virtual void RemoveVariable(const std::string& varName) = 0;

    virtual void ClearVolatileVariables() = 0;
};
} // namespace Entities
} // namespace Sfs2X

#endif
