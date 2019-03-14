// ===================================================================
//
// Description
//        Contains the definition of Variable interface
//
// Revision history
//        Date            Description
//        30-Nov-2016        First version
//
// ===================================================================
#ifndef __Variable__
#define __Variable__

#include "smartfox/Entities/Variables/VariableType.h"
#include "smartfox/Entities/Data/ISFSArray.h"
#include "smartfox/Entities/Data/ISFSObject.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {
/// <summary>
/// The Variable interface defines all the default public methods and properties
/// that an object representing a SmartFoxServer Variable exposes.
/// </summary>
class DLLImportExport Variable {
public:
    virtual ~Variable() = default;

    /// <summary>
    /// Indicates the name of this variable.
    /// </summary>
    virtual boost::shared_ptr<std::string> Name() const = 0;

    /// <summary>
    /// Indicates the type of this variable.
    /// </summary>
    ///
    /// <seealso cref="VariableType"/>
    virtual VariableType Type() const = 0;

    /// <summary>
    /// Returns the untyped value of this variable.
    /// </summary>
    virtual boost::shared_ptr<void> Value() const = 0;

    /// <summary>
    /// Retrieves the value of a boolean variable.
    /// </summary>
    ///
    /// <returns>The variable value as a boolean.</returns>
    virtual boost::shared_ptr<bool> GetBoolValue() const = 0;

    /// <summary>
    /// Retrieves the value of an integer variable.
    /// </summary>
    ///
    /// <returns>The variable value as an integer.</returns>
    virtual boost::shared_ptr<std::int32_t> GetIntValue() const = 0;

    /// <summary>
    /// Retrieves the value of a double precision variable.
    /// </summary>
    ///
    /// <returns>The variable value as a double.</returns>
    virtual boost::shared_ptr<double> GetDoubleValue() const = 0;

    /// <summary>
    /// Retrieves the value of a string variable.
    /// </summary>
    ///
    /// <returns>The variable value as a string.</returns>
    virtual boost::shared_ptr<std::string> GetStringValue() const = 0;

    /// <summary>
    /// Retrieves the value of a SFSObject variable.
    /// </summary>
    ///
    /// <returns>The variable value as an object implementing the <see
    /// cref="ISFSObject"/> interface.</returns>
    ///
    /// <seealso cref="SFSObject"/>
    virtual boost::shared_ptr<ISFSObject> GetSFSObjectValue() const = 0;

    /// <summary>
    /// Retrieves the value of a SFSArray variable.
    /// </summary>
    ///
    /// <returns>The variable value as an object implementing the <see
    /// cref="ISFSArray"/> interface.</returns>
    ///
    /// <seealso cref="SFSArray"/>
    virtual boost::shared_ptr<ISFSArray> GetSFSArrayValue() const = 0;

    /// <summary>
    /// Indicates if the variable is <c>null</c>.
    /// </summary>
    ///
    /// <returns><c>true</c> if the variable has a <c>null</c> value.</returns>
    virtual bool IsNull() const = 0;

    /// <exclude/>
    virtual boost::shared_ptr<ISFSArray> ToSFSArray() const = 0;
};
} // namespace Variables
} // namespace Entities
} // namespace Sfs2X

#endif
