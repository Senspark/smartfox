// ===================================================================
//
// Description
//        Contains the definition of SFSRoomVariable
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __SFSRoomVariable__
#define __SFSRoomVariable__

#include "smartfox/Util/Common.h"
#include "smartfox/Entities/Variables/BaseVariable.h"
#include "smartfox/Entities/Variables/RoomVariable.h"
#include "smartfox/Entities/Data/ISFSArray.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

namespace Sfs2X {
namespace Entities {
using namespace Data;

namespace Variables {

/// <summary>
/// The RoomVariable class is used to represent variables maintained on the
/// Server side and automatically updated to the clients.
/// </summary>
/// <remarks>
/// They are particularly useful to "attach" any custom data to each Room such
/// as the current game status and other Room-specific properties etc... <para/>
/// RoomVariables support basic data types and nested complex objects:
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
/// <para/>
/// RoomVariables also support different flags:
/// <ul>
///         <li><b>Private</b>: a private variable can only be modified by its
/// creator</li>         <li><b>Persistent</b>: a persistent variable will
/// continue to exist even if its creator has left the room. </li>
///         <li><b>Global</b>: a global variable will fire updates not only to
/// all Users in the Room but also to all Users in the Room Group</li>
/// </ul>
/// </remarks>
/// <seealso cref="SFSRoom"/>
/// <seealso cref="Requests.SetRoomVariablesRequest"/>
class DLLImportExport SFSRoomVariable : public BaseVariable,
                                        public RoomVariable {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    static boost::shared_ptr<RoomVariable>
    FromSFSArray(const boost::shared_ptr<ISFSArray>& sfsa);

    /// <overrides>
    /// <summary>
    ///
    /// </summary>
    /// </overrides>
    /// <param name="name">
    /// the name of the variable
    /// </param>
    /// <param name="val">
    /// the variable value ( can be Boolean, int, Number, String, SFSObject,
    /// SFSArray )
    /// </param>
    explicit SFSRoomVariable(const std::string& name,
                             const boost::shared_ptr<std::int64_t>& val);

    explicit SFSRoomVariable(const std::string& name,
                             const boost::shared_ptr<std::uint64_t>& val);

    explicit SFSRoomVariable(const std::string& name,
                             const boost::shared_ptr<std::int32_t>& val);

    explicit SFSRoomVariable(const std::string& name,
                             const boost::shared_ptr<std::uint32_t>& val);

    explicit SFSRoomVariable(const std::string& name,
                             const boost::shared_ptr<bool>& val);

    explicit SFSRoomVariable(const std::string& name,
                             const boost::shared_ptr<double>& val);

    explicit SFSRoomVariable(const std::string& name,
                             const boost::shared_ptr<std::string>& val);

    explicit SFSRoomVariable(const std::string& name,
                             const boost::shared_ptr<SFSObject>& val);

    explicit SFSRoomVariable(const std::string& name,
                             const boost::shared_ptr<SFSArray>& val);

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
    explicit SFSRoomVariable(const std::string& name,
                             const boost::shared_ptr<void>& val, int type);

    virtual ~SFSRoomVariable() override;

    virtual bool IsPrivate() const override;
    virtual void IsPrivate(bool value) override;

    virtual bool IsPersistent() const override;
    virtual void IsPersistent(bool value) override;

    boost::shared_ptr<std::string> ToString() const;
    virtual boost::shared_ptr<ISFSArray> ToSFSArray() const override;

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

private:
    // -------------------------------------------------------------------
    // Private methods
    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------

    bool isPersistent;
    bool isPrivate;
};
} // namespace Variables
} // namespace Entities
} // namespace Sfs2X

#endif
