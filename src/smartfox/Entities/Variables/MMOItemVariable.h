// ===================================================================
//
// Description
//        Contains the definition of MMOItemVariable
//
// Revision history
//        Date            Description
//        30-Nov-2013        First version
//
// ===================================================================
#ifndef __MMOItemVariable__
#define __MMOItemVariable__

#include "smartfox/Util/Common.h"
#include "smartfox/Entities/Variables/BaseVariable.h"
#include "smartfox/Entities/Variables/IMMOItemVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {
/// <summary>
/// The MMOItemVariable object represents a SmartFoxServer MMOItem Variable
/// entity on the client.
/// </summary>
///
/// <remarks>
/// An MMOItem Variable is a custom value attached to an MMOItem object that
/// gets automatically synchronized between client and server on every change,
/// provided that the MMOItem is inside the Area of Interest of the current user
/// in a MMORoom. <para /> <b>NOTE:</b> MMOItem Variables behave exactly like
/// User Variables and support the same data types, but they can be created,
/// updated and deleted on the server side only.
/// </remarks>
///
/// <seealso cref="Sfs2X.Entities.MMOItem"/>
/// <seealso cref="Sfs2X.Entities.MMORoom"/>
class DLLImportExport MMOItemVariable : public BaseVariable,
                                        public IMMOItemVariable {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    /// <exclude/>
    static boost::shared_ptr<IMMOItemVariable>
    FromSFSArray(const boost::shared_ptr<ISFSArray>& sfsa);

    /// <exclude/>
    explicit MMOItemVariable(const std::string& name,
                             const boost::shared_ptr<void>& val, int type);

    /// <exclude/>
    explicit MMOItemVariable(const std::string& name,
                             const boost::shared_ptr<std::int64_t>& val);

    explicit MMOItemVariable(const std::string& name,
                             const boost::shared_ptr<std::uint64_t>& val);

    explicit MMOItemVariable(const std::string& name,
                             const boost::shared_ptr<std::int32_t>& val);

    explicit MMOItemVariable(const std::string& name,
                             const boost::shared_ptr<std::uint32_t>& val);

    explicit MMOItemVariable(const std::string& name,
                             const boost::shared_ptr<bool>& val);

    explicit MMOItemVariable(const std::string& name,
                             const boost::shared_ptr<double>& val);

    explicit MMOItemVariable(const std::string& name,
                             const boost::shared_ptr<std::string>& val);

    explicit MMOItemVariable(const std::string& name,
                             const boost::shared_ptr<SFSObject>& val);

    explicit MMOItemVariable(const std::string& name,
                             const boost::shared_ptr<SFSArray>& val);

    virtual ~MMOItemVariable() override;

    /// <inheritdoc />
    virtual boost::shared_ptr<std::string> Name() const override;

    /// <inheritdoc />
    virtual VariableType Type() const override;

    /// <inheritdoc />
    virtual boost::shared_ptr<void> Value() const override;

    /// <inheritdoc />
    virtual boost::shared_ptr<bool> GetBoolValue() const override;

    /// <inheritdoc />
    virtual boost::shared_ptr<std::int32_t> GetIntValue() const override;

    /// <inheritdoc />
    virtual boost::shared_ptr<double> GetDoubleValue() const override;

    /// <inheritdoc />
    virtual boost::shared_ptr<std::string> GetStringValue() const override;

    /// <inheritdoc />
    virtual boost::shared_ptr<ISFSObject> GetSFSObjectValue() const override;

    /// <inheritdoc />
    virtual boost::shared_ptr<ISFSArray> GetSFSArrayValue() const override;

    /// <inheritdoc />
    virtual bool IsNull() const override;

    virtual boost::shared_ptr<ISFSArray> ToSFSArray() const override;

    /// <summary>
    /// Returns a string that contains the MMOItem Variable name, type and
    /// value.
    /// </summary>
    ///
    /// <returns>
    /// The string representation of the <see
    /// cref="Sfs2X.Entities.Variables.MMOItemVariable"/> object.
    /// </returns>
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
