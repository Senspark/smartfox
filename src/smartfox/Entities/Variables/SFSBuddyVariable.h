// ===================================================================
//
// Description
//        Contains the definition of SFSBuddyVariable
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __SFSBuddyVariable__
#define __SFSBuddyVariable__

#include "../../Util/Common.h"
#include "BaseVariable.h"
#include "BuddyVariable.h"
#include "../Data/ISFSArray.h"
#include "../Data/SFSArray.h"
#include "../Data/SFSObject.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object

namespace Sfs2X {
namespace Entities {
using namespace Data;

namespace Variables {

/// <summary>
/// BuddyVariables are custom values attached to any Buddy in a BuddyList.
/// </summary>
/// <remarks>
/// They work with the same principle of the User/Room Variables.<br/>
/// The only difference is the logic by which they get propagated to other
/// Users. While RoomVariables are broadcast to all clients in the same Room,
/// BuddyVariables are updated to all Users who have the BuddyVariable owner in
/// their BuddyLists.
///  <para/>
/// BuddyVariables support basic data types and nested complex objects:
///
/// <ul>
///         <li>Null</li>
///         <li>Bool</li>
///         <li>Int</li>
///         <li>Double</li>
///         <li>String</li>
///         <li>SFSObject</li>
///         <li>SFSArray</li>
/// </ul>
///
/// Also there is a special convention that allows certain Variables to be
/// "offline" Buddy Variables. <br/> All variable names starting with a dollar
/// sign ($) will set the BuddyVariable as persistent and make them available at
/// any time whether the owner is online or not.
/// </remarks>
/// <seealso cref="SFSBuddy"/>
/// <seealso cref="Requests.SetBuddyVariablesRequest"/>
/// <seealso cref="Core.SFSBuddyEvent.BUDDY_VARIABLES_UPDATE"/>
class DLLImportExport SFSBuddyVariable : public BaseVariable,
                                         public BuddyVariable {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    static boost::shared_ptr<BuddyVariable>
    FromSFSArray(const boost::shared_ptr<ISFSArray>& sfsa);

    /// <param name="name">
    /// the name of the variable
    /// </param>
    /// <param name="val">
    /// the variable value ( can be Boolean, int, Number, String, SFSObject,
    /// SFSArray )
    /// </param>
    /// <param name="type">
    /// it's usually not necessary to pass this parameter as the variable value
    /// is auto-detected
    /// </param>
    explicit SFSBuddyVariable(const std::string& name,
                              const boost::shared_ptr<void>& val, int type);

    /// <param name="name">
    /// the name of the variable
    /// </param>
    /// <param name="val">
    /// the variable value ( can be Boolean, int, Number, String, SFSObject,
    /// SFSArray )
    /// </param>
    /// <param name="type">
    /// it's usually not necessary to pass this parameter as the variable value
    /// is auto-detected
    /// </param>
    explicit SFSBuddyVariable(const boost::shared_ptr<std::string>& name,
                              const boost::shared_ptr<void>& val, int type);

    /// <exclude/>
    explicit SFSBuddyVariable(const std::string& name,
                              const boost::shared_ptr<std::int64_t>& val);

    explicit SFSBuddyVariable(const std::string& name,
                              const boost::shared_ptr<std::uint64_t>& val);

    explicit SFSBuddyVariable(const std::string& name,
                              const boost::shared_ptr<std::int32_t>& val);

    explicit SFSBuddyVariable(const std::string& name,
                              const boost::shared_ptr<std::uint32_t>& val);

    explicit SFSBuddyVariable(const std::string& name,
                              const boost::shared_ptr<bool>& val);

    explicit SFSBuddyVariable(const std::string& name,
                              const boost::shared_ptr<double>& val);

    explicit SFSBuddyVariable(const std::string& name,
                              const boost::shared_ptr<std::string>& val);

    explicit SFSBuddyVariable(const std::string& name,
                              const boost::shared_ptr<SFSObject>& val);

    explicit SFSBuddyVariable(const std::string& name,
                              const boost::shared_ptr<SFSArray>& val);

    virtual ~SFSBuddyVariable() override;

    virtual bool IsOffline() const override;
    virtual boost::shared_ptr<std::string> Name() const override;
    virtual VariableType Type() const override;
    virtual boost::shared_ptr<void> Value() const override;
    virtual boost::shared_ptr<bool> GetBoolValue() const override;
    virtual boost::shared_ptr<std::int32_t> GetIntValue() const override;
    virtual boost::shared_ptr<double> GetDoubleValue() const override;
    virtual boost::shared_ptr<std::string> GetStringValue() const override;
    virtual boost::shared_ptr<ISFSObject> GetSFSObjectValue() const override;
    virtual boost::shared_ptr<ISFSArray> GetSFSArrayValue() const override;
    virtual bool IsNull() const override;
    virtual boost::shared_ptr<ISFSArray> ToSFSArray() const override;

    /// <summary>
    /// Returns a string that contains the Buddy Variable name, type and value.
    /// </summary>
    ///
    /// <returns>
    /// The string representation of the <see
    /// cref="Sfs2X.Entities.Variables.SFSBuddyVariable"/> object.
    /// </returns>
    boost::shared_ptr<std::string> ToString() const;

    // -------------------------------------------------------------------
    // Public members
    // -------------------------------------------------------------------

    static boost::shared_ptr<std::string> OFFLINE_PREFIX;

protected:
    // -------------------------------------------------------------------
    // Protected methods
    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    // Protected members
    // -------------------------------------------------------------------

private:
    // -------------------------------------------------------------------
    // Private methods
    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------
};
} // namespace Variables
} // namespace Entities
} // namespace Sfs2X

#endif
