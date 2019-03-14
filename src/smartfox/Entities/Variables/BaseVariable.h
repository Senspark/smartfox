// ===================================================================
//
// Description
//        Contains the definition of BaseVariable
//
// Revision history
//        Date            Description
//        30-Nov-2016        First version
//
// ===================================================================
#ifndef __BaseVariable__
#define __BaseVariable__

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object

#include "../../Util/Common.h"
#include "Variable.h"
#include "VariableType.h"
#include "../Data/ISFSObject.h"
#include "../Data/ISFSArray.h"
#include "../Data/SFSArray.h"
#include "../Data/SFSObject.h"
#include "../../Exceptions/SFSError.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

namespace Sfs2X {
namespace Entities {
namespace Variables {

// -------------------------------------------------------------------
// Class BaseVariable
// -------------------------------------------------------------------

/// <summary>
/// The BaseVariable object is the base class for all SmartFoxServer Variable
/// entities on the client.
/// </summary>
///
/// <seealso cref="Sfs2X.Entities.Variables.SFSUserVariable"/>
/// <seealso cref="Sfs2X.Entities.Variables.SFSRoomVariable"/>
/// <seealso cref="Sfs2X.Entities.Variables.SFSBuddyVariable"/>
/// <seealso cref="Sfs2X.Entities.Variables.MMOItemVariable"/>
class DLLImportExport BaseVariable : public Variable {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    /// <summary>
    /// Creates a new BaseVariable instance.
    /// </summary>
    ///
    /// <param name="name">The name of the Variable.</param>
    /// <param name="val">The value of the Variable.</param>
    /// <param name="type">The type of the Variable among those available in the
    /// <see cref="VariableType"/> class. Usually it is not necessary to pass
    /// this parameter, as the type is auto-detected from the value.</param>
    ///
    /// <exclude/>
    explicit BaseVariable(const std::string& name,
                          const boost::shared_ptr<void>& val, int type);

    /// <summary>
    /// Creates a new BaseVariable instance.
    /// </summary>
    ///
    /// <param name="name">The name of the Variable.</param>
    /// <param name="val">The value of the Variable ( can be Boolean, int,
    /// Number, String, SFSObject, SFSArray ).</param>
    ///
    /// <exclude/>
    explicit BaseVariable(const std::string& name,
                          const boost::shared_ptr<std::int64_t>& val);

    explicit BaseVariable(const std::string& name,
                          const boost::shared_ptr<std::uint64_t>& val);

    explicit BaseVariable(const std::string& name,
                          const boost::shared_ptr<std::int32_t>& val);

    explicit BaseVariable(const std::string& name,
                          const boost::shared_ptr<std::uint32_t>& val);

    explicit BaseVariable(const std::string& name,
                          const boost::shared_ptr<bool>& val);

    explicit BaseVariable(const std::string& name,
                          const boost::shared_ptr<double>& val);

    explicit BaseVariable(const std::string& name,
                          const boost::shared_ptr<std::string>& val);

    explicit BaseVariable(const std::string& name,
                          const boost::shared_ptr<SFSObject>& val);

    explicit BaseVariable(const std::string& name,
                          const boost::shared_ptr<SFSArray>& val);

    virtual ~BaseVariable() override;

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

    boost::shared_ptr<std::string> TypeAsString() const;
    boost::shared_ptr<std::string> ValueAsString() const;

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

    void PopulateArrayWithValue(const boost::shared_ptr<ISFSArray>& arr) const;
    void SetValue(const boost::shared_ptr<std::int64_t>& val);
    void SetValue(const boost::shared_ptr<std::uint64_t>& val);
    void SetValue(const boost::shared_ptr<std::int32_t>& val);
    void SetValue(const boost::shared_ptr<std::uint32_t>& val);
    void SetValue(const boost::shared_ptr<bool>& val);
    void SetValue(const boost::shared_ptr<double>& val);
    void SetValue(const boost::shared_ptr<std::string>& val);
    void SetValue(const boost::shared_ptr<SFSObject>& val);
    void SetValue(const boost::shared_ptr<SFSArray>& val);

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------

    /// <exclude/>
    boost::shared_ptr<std::string> name;

    /// <exclude/>
    VariableType type;

    /// <exclude/>
    boost::shared_ptr<void> val;
};
} // namespace Variables
} // namespace Entities
} // namespace Sfs2X

#endif
