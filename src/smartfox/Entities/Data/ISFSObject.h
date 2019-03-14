// ===================================================================
//
// Description
//        Contains the definition of ISFSObject interface
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __ISFSObject__
#define __ISFSObject__

// Forward class declaration
namespace Sfs2X {
namespace Entities {
namespace Data {
class ISFSObject;
} // namespace Data
} // namespace Entities
} // namespace Sfs2X

#include "../../Util/ByteArray.h"
#include "SFSDataWrapper.h"
#include "ISFSArray.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object
#include <vector> // STL library: vector object

using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Entities {
namespace Data {

/// <summary>
/// SFSObject interface
/// </summary>
class DLLImportExport ISFSObject {
public:
    virtual ~ISFSObject() = default;

    /// <summary>
    /// Indicates if the value mapped by the specified key is <c>null</c>.
    /// </summary>
    ///
    /// <param name="key">The key to be checked.</param>
    ///
    /// <returns><c>true</c> if the value mapped by the passed key is
    /// <c>null</c> or the mapping doesn't exist for that key.</returns>
    virtual bool IsNull(const std::string& key) const = 0;

    /// <summary>
    /// Indicates if the value mapped by the specified key is <c>null</c>.
    /// </summary>
    ///
    /// <param name="key">The key to be checked.</param>
    ///
    /// <returns><c>true</c> if the value mapped by the passed key is
    /// <c>null</c> or the mapping doesn't exist for that key.</returns>
    virtual bool IsNull(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Indicates whether this object contains a mapping for the specified key
    /// or not.
    /// </summary>
    ///
    /// <param name="key">The key whose presence in this object is to be
    /// tested.</param>
    ///
    /// <returns><c>true</c> if this object contains a mapping for the specified
    /// key.</returns>
    virtual bool ContainsKey(const std::string& key) const = 0;

    /// <summary>
    /// Indicates whether this object contains a mapping for the specified key
    /// or not.
    /// </summary>
    ///
    /// <param name="key">The key whose presence in this object is to be
    /// tested.</param>
    ///
    /// <returns><c>true</c> if this object contains a mapping for the specified
    /// key.</returns>
    virtual bool
    ContainsKey(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Removes the element corresponding to the passed key from this object.
    /// </summary>
    ///
    /// <param name="key">The key of the element to be removed.</param>
    virtual void RemoveElement(const std::string& key) = 0;

    /// <summary>
    /// Removes the element corresponding to the passed key from this object.
    /// </summary>
    ///
    /// <param name="key">The key of the element to be removed.</param>
    virtual void RemoveElement(const boost::shared_ptr<std::string>& key) = 0;

    /// <summary>
    /// Retrieves a list of all the keys contained in this object.
    /// </summary>
    ///
    /// <returns>The list of all the keys in this object.</returns>
    virtual boost::shared_ptr<std::vector<std::string>> GetKeys() const = 0;

    /// <summary>
    /// Indicates the number of elements in this object.
    /// </summary>
    ///
    /// <returns>The number of elements in this object.</returns>
    virtual std::size_t Size() const = 0;

    /// <summary>
    /// Provides the binary form of this object.
    /// </summary>
    ///
    /// <returns>The binary data representing this object.</returns>
    virtual boost::shared_ptr<ByteArray> ToBinary() = 0;

    /// <summary>
    /// Provides a formatted string representing this object.
    /// </summary>
    ///
    /// <remarks>
    /// The returned string can be logged or traced in the console for debugging
    /// purposes.
    /// </remarks>
    ///
    /// <param name="format">If <c>true</c>, the output is formatted in a
    /// human-readable way.</param>
    ///
    /// <returns>The string representation of this object.</returns>
    virtual boost::shared_ptr<std::string> GetDump(bool format) const = 0;

    /// <summary>
    /// See <see cref="GetDump(bool)"/>.
    /// </summary>
    virtual boost::shared_ptr<std::string>
    GetDump() const = 0; // default to true

    /// <summary>
    /// Provides a detailed hexadecimal representation of this object.
    /// </summary>
    ///
    /// <remarks>
    /// The returned string can be logged or traced in the console for debugging
    /// purposes.
    /// </remarks>
    ///
    /// <returns>The hexadecimal string representation of this object.</returns>
    virtual boost::shared_ptr<std::string> GetHexDump() = 0;

    /*
     * :::::::::::::::::::::::::::::::::::::::::
     * Type getters
     * :::::::::::::::::::::::::::::::::::::::::
     */

    /// <exclude />
    virtual boost::shared_ptr<SFSDataWrapper>
    GetData(const std::string& key) const = 0;

    virtual boost::shared_ptr<SFSDataWrapper>
    GetData(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as a boolean.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>false</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<bool> GetBool(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as a boolean.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>false</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<bool>
    GetBool(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as a signed byte
    /// (8 bits).
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>0</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::uint8_t>
    GetByte(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as a signed byte
    /// (8 bits).
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>0</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::uint8_t>
    GetByte(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as a short
    /// integer (16 bits).
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>0</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::int16_t>
    GetShort(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as a short
    /// integer (16 bits).
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>0</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::int16_t>
    GetShort(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an integer (32
    /// bits).
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>0</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::int32_t>
    GetInt(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an integer (32
    /// bits).
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>0</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::int32_t>
    GetInt(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as a long integer
    /// (64 bits).
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>0</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::int64_t>
    GetLong(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as a long integer
    /// (64 bits).
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>0</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::int64_t>
    GetLong(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as a floating
    /// point number.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>0</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<float> GetFloat(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as a floating
    /// point number.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>0</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<float>
    GetFloat(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as a double
    /// precision number.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>0</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<double>
    GetDouble(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as a double
    /// precision number.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>0</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<double>
    GetDouble(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an UTF-8
    /// string, with max length of 32 KBytes.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>null</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::string>
    GetUtfString(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an UTF-8
    /// string, with max length of 32 KBytes.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>null</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::string>
    GetUtfString(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an UTF-8
    /// string, with max length of 2 GBytes.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>null</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::string>
    GetText(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an UTF-8
    /// string, with max length of 2 GBytes.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object associated with the specified key;
    /// <c>null</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::string>
    GetText(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an array of
    /// booleans.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an array of booleans; <c>null</c>
    /// if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::vector<bool>>
    GetBoolArray(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an array of
    /// booleans.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an array of booleans; <c>null</c>
    /// if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::vector<bool>>
    GetBoolArray(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as a ByteArray
    /// object.
    /// </summary>
    ///
    /// <remarks>
    /// <b>IMPORTANT</b>: ByteArrays transmission is not supported in Unity
    /// WebGL.
    /// </remarks>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as a ByteArray object; <c>null</c>
    /// if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<ByteArray>
    GetByteArray(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as a ByteArray
    /// object.
    /// </summary>
    ///
    /// <remarks>
    /// <b>IMPORTANT</b>: ByteArrays transmission is not supported in Unity
    /// WebGL.
    /// </remarks>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as a ByteArray object; <c>null</c>
    /// if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<ByteArray>
    GetByteArray(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an array of
    /// shorts.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an array of shorts; <c>null</c>
    /// if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::vector<std::int16_t>>
    GetShortArray(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an array of
    /// shorts.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an array of shorts; <c>null</c>
    /// if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::vector<std::int16_t>>
    GetShortArray(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an array of
    /// integers.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an array of integers; <c>null</c>
    /// if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::vector<std::int32_t>>
    GetIntArray(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an array of
    /// integers.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an array of integers; <c>null</c>
    /// if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::vector<std::int32_t>>
    GetIntArray(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an array of
    /// longs.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an array of longs; <c>null</c> if
    /// a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::vector<std::int64_t>>
    GetLongArray(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an array of
    /// longs.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an array of longs; <c>null</c> if
    /// a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::vector<std::int64_t>>
    GetLongArray(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an array of
    /// floats.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an array of floats; <c>null</c>
    /// if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::vector<float>>
    GetFloatArray(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an array of
    /// floats.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an array of floats; <c>null</c>
    /// if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::vector<float>>
    GetFloatArray(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an array of
    /// doubles.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an array of doubles; <c>null</c>
    /// if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::vector<double>>
    GetDoubleArray(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an array of
    /// doubles.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an array of doubles; <c>null</c>
    /// if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::vector<double>>
    GetDoubleArray(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an array of
    /// UTF-8 strings.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an array of UTF-8 strings;
    /// <c>null</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::vector<std::string>>
    GetUtfStringArray(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an array of
    /// UTF-8 strings.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an array of UTF-8 strings;
    /// <c>null</c> if a mapping for the passed key doesn't exist.</returns>
    virtual boost::shared_ptr<std::vector<std::string>>
    GetUtfStringArray(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an ISFSArray
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an object implementing the
    /// ISFSArray interface; <c>null</c> if a mapping for the passed key doesn't
    /// exist.</returns>
    ///
    /// <seealso cref="SFSArray"/>
    virtual boost::shared_ptr<ISFSArray>
    GetSFSArray(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an ISFSArray
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an object implementing the
    /// ISFSArray interface; <c>null</c> if a mapping for the passed key doesn't
    /// exist.</returns>
    ///
    /// <seealso cref="SFSArray"/>
    virtual boost::shared_ptr<ISFSArray>
    GetSFSArray(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an ISFSObject
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an object implementing the
    /// ISFSObject interface; <c>null</c> if a mapping for the passed key
    /// doesn't exist.</returns>
    ///
    /// <seealso cref="SFSObject"/>
    virtual boost::shared_ptr<ISFSObject>
    GetSFSObject(const std::string& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an ISFSObject
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key whose associated value is to be
    /// returned.</param>
    ///
    /// <returns>The element of this object as an object implementing the
    /// ISFSObject interface; <c>null</c> if a mapping for the passed key
    /// doesn't exist.</returns>
    ///
    /// <seealso cref="SFSObject"/>
    virtual boost::shared_ptr<ISFSObject>
    GetSFSObject(const boost::shared_ptr<std::string>& key) const = 0;

    /// <summary>
    /// Returns the element corresponding to the specified key as an instance of
    /// a custom class.
    /// </summary>
    /// <remarks>
    /// This advanced feature allows the transmission of specific object
    /// instances between client-side C++ and server-side Java provided
    /// that:<br/>
    /// - the respective class definitions on both sides have the same package
    /// name<br/>
    /// - the following code is executed right after creating the SmartFox
    /// object: <c>DefaultSFSDataSerializer.RunningAssembly =
    /// Assembly.GetExecutingAssembly();</c> (requires <c>System.Reflection</c>
    /// and <c>Sfs2X.Protocol.Serialization</c>)
    /// </remarks>
    /// <example>
    /// This is an example of the same class on the server and client side:
    ///
    /// <b>Server Java code:</b>
    ///            \code{.cpp}
    ///             package my.game.spacecombat
    ///
    ///             public class SpaceShip
    ///             {
    ///                 private String type;
    ///                 private String name;
    ///                 private int firePower;
    ///                 private int maxSpeed;
    ///                 private List<std::string> weapons;
    ///
    ///                 public SpaceShip(const std::string& name, String type)
    ///                 {
    ///                     this.name = name;
    ///                     this.type = type;
    ///                 }
    ///
    ///                 // ... Getters / Setters ...
    ///             }
    ///         \endcode
    ///
    /// <b>Client AS3 code:</b>
    ///            \code{.cpp}
    ///         package my.game.spacecombat
    ///         {
    ///             public class SpaceShip
    ///             {
    ///                 private var _type:String
    ///                 private var _name:String
    ///                 private var _firePower:int;
    ///                 private var _maxSpeed:int;
    ///                 private var _weapons:Array;
    ///
    ///                 public SpaceShip(name:String, type:Strig)
    ///                 {
    ///                     _name = name
    ///                     _type = type
    ///                 }
    ///
    ///                 // ... Getters / Setters ...
    ///             }
    ///         }
    ///
    ///         \endcode
    ///
    ///     A SpaceShip instance from server side is sent to the client. This is
    /// how you get it:
    ///        \code{.cpp}
    ///            boost::shared_ptr<std::string> name (new
    ///            string("spaceShip")); boost::shared_ptr<SpaceShip>
    ///            mySpaceShip =
    ///(boost::static_pointer_cast<SpaceShip>)sfsObject->getClass(name)
    ///     \endcode
    /// </example>
    /// <param name="key">
    /// A string pointer
    /// </param>
    /// <returns>
    /// A void pointer
    /// </returns>
    virtual boost::shared_ptr<void> GetClass(const std::string& key) const = 0;
    virtual boost::shared_ptr<void>
    GetClass(const boost::shared_ptr<std::string>& key) const = 0;

    /*
     * :::::::::::::::::::::::::::::::::::::::::
     * Type setters
     * :::::::::::::::::::::::::::::::::::::::::
     */

    /// <exclude />
    virtual void PutNull(const std::string& key) = 0;
    virtual void PutNull(const boost::shared_ptr<std::string>& key) = 0;

    /// <summary>
    /// Associates the passed boolean value with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutBool(const std::string& key,
                         const boost::shared_ptr<bool>& val) = 0;

    /// <summary>
    /// Associates the passed boolean value with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutBool(const boost::shared_ptr<std::string>& key,
                         const boost::shared_ptr<bool>& val) = 0;

    /// <summary>
    /// Associates the passed boolean value with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutBool(const std::string& key, bool val) = 0;

    /// <summary>
    /// Associates the passed boolean value with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutBool(const boost::shared_ptr<std::string>& key,
                         bool val) = 0;

    /// <summary>
    /// Associates the passed byte value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutByte(const std::string& key,
                         const boost::shared_ptr<std::uint8_t>& val) = 0;

    /// <summary>
    /// Associates the passed byte value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutByte(const boost::shared_ptr<std::string>& key,
                         const boost::shared_ptr<std::uint8_t>& val) = 0;

    /// <summary>
    /// Associates the passed byte value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutByte(const std::string& key, std::uint8_t val) = 0;

    /// <summary>
    /// Associates the passed byte value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutByte(const boost::shared_ptr<std::string>& key,
                         std::uint8_t val) = 0;

    /// <summary>
    /// Associates the passed short value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutShort(const std::string& key,
                          const boost::shared_ptr<std::int16_t>& val) = 0;

    /// <summary>
    /// Associates the passed short value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutShort(const boost::shared_ptr<std::string>& key,
                          const boost::shared_ptr<std::int16_t>& val) = 0;

    /// <summary>
    /// Associates the passed short value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutShort(const std::string& key, std::int16_t val) = 0;

    /// <summary>
    /// Associates the passed short value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutShort(const boost::shared_ptr<std::string>& key,
                          std::int16_t val) = 0;

    /// <summary>
    /// Associates the passed integer value with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutInt(const std::string& key,
                        const boost::shared_ptr<std::int32_t>& val) = 0;

    /// <summary>
    /// Associates the passed integer value with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutInt(const boost::shared_ptr<std::string>& key,
                        const boost::shared_ptr<std::int32_t>& val) = 0;

    /// <summary>
    /// Associates the passed integer value with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutInt(const std::string& key, std::int32_t val) = 0;

    /// <summary>
    /// Associates the passed integer value with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutInt(const boost::shared_ptr<std::string>& key,
                        std::int32_t val) = 0;

    /// <summary>
    /// Associates the passed long value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutLong(const std::string& key,
                         const boost::shared_ptr<std::int64_t>& val) = 0;

    /// <summary>
    /// Associates the passed long value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutLong(const boost::shared_ptr<std::string>& key,
                         const boost::shared_ptr<std::int64_t>& val) = 0;

    /// <summary>
    /// Associates the passed long value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutLong(const std::string& key, std::int64_t val) = 0;

    /// <summary>
    /// Associates the passed long value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutLong(const boost::shared_ptr<std::string>& key,
                         std::int64_t val) = 0;

    /// <summary>
    /// Associates the passed float value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutFloat(const std::string& key,
                          const boost::shared_ptr<float>& val) = 0;

    /// <summary>
    /// Associates the passed float value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutFloat(const boost::shared_ptr<std::string>& key,
                          const boost::shared_ptr<float>& val) = 0;

    /// <summary>
    /// Associates the passed float value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutFloat(const std::string& key, float val) = 0;

    /// <summary>
    /// Associates the passed float value with the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutFloat(const boost::shared_ptr<std::string>& key,
                          float val) = 0;

    /// <summary>
    /// Associates the passed double value with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutDouble(const std::string& key,
                           const boost::shared_ptr<double>& val) = 0;

    /// <summary>
    /// Associates the passed double value with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutDouble(const boost::shared_ptr<std::string>& key,
                           const boost::shared_ptr<double>& val) = 0;

    /// <summary>
    /// Associates the passed double value with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutDouble(const std::string& key, double val) = 0;

    /// <summary>
    /// Associates the passed double value with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutDouble(const boost::shared_ptr<std::string>& key,
                           double val) = 0;

    /// <summary>
    /// Associates the passed UTF-8 string value (max length: 32 KBytes) with
    /// the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutUtfString(const std::string& key,
                              const boost::shared_ptr<std::string>& val) = 0;

    /// <summary>
    /// Associates the passed UTF-8 string value (max length: 32 KBytes) with
    /// the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutUtfString(const boost::shared_ptr<std::string>& key,
                              const boost::shared_ptr<std::string>& val) = 0;

    /// <summary>
    /// Associates the passed UTF-8 string value (max length: 32 KBytes) with
    /// the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutUtfString(const std::string& key,
                              const std::string& val) = 0;

    /// <summary>
    /// Associates the passed UTF-8 string value (max length: 32 KBytes) with
    /// the specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutUtfString(const boost::shared_ptr<std::string>& key,
                              const std::string& val) = 0;

    /// <summary>
    /// Associates the passed UTF-8 string value (max length: 2 GBytes) with the
    /// specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutText(const std::string& key,
                         const boost::shared_ptr<std::string>& val) = 0;

    /// <summary>
    /// Associates the passed UTF-8 string value (max length: 2 GBytes) with the
    /// specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutText(const boost::shared_ptr<std::string>& key,
                         const boost::shared_ptr<std::string>& val) = 0;

    /// <summary>
    /// Associates the passed UTF-8 string value (max length: 2 GBytes) with the
    /// specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutText(const std::string& key, const std::string& val) = 0;

    /// <summary>
    /// Associates the passed UTF-8 string value (max length: 2 GBytes) with the
    /// specified key in this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified value is to be
    /// associated.</param> <param name="val">The value to be associated with
    /// the specified key.</param>
    virtual void PutText(const boost::shared_ptr<std::string>& key,
                         const std::string& val) = 0;

    /// <summary>
    /// Associates the passed array of booleans with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified array is to be
    /// associated.</param> <param name="val">The array of booleans to be
    /// associated with the specified key.</param>
    virtual void
    PutBoolArray(const std::string& key,
                 const boost::shared_ptr<std::vector<bool>>& val) = 0;

    /// <summary>
    /// Associates the passed array of booleans with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified array is to be
    /// associated.</param> <param name="val">The array of booleans to be
    /// associated with the specified key.</param>
    virtual void
    PutBoolArray(const boost::shared_ptr<std::string>& key,
                 const boost::shared_ptr<std::vector<bool>>& val) = 0;

    /// <summary>
    /// Associates the passed ByteArray object with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <remarks>
    /// <b>IMPORTANT</b>: ByteArrays transmission is not supported in Unity
    /// WebGL.
    /// </remarks>
    ///
    /// <param name="key">The key with which the specified object is to be
    /// associated.</param> <param name="val">The object to be associated with
    /// the specified key.</param>
    virtual void PutByteArray(const std::string& key,
                              const boost::shared_ptr<ByteArray>& val) = 0;

    /// <summary>
    /// Associates the passed ByteArray object with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <remarks>
    /// <b>IMPORTANT</b>: ByteArrays transmission is not supported in Unity
    /// WebGL.
    /// </remarks>
    ///
    /// <param name="key">The key with which the specified object is to be
    /// associated.</param> <param name="val">The object to be associated with
    /// the specified key.</param>
    virtual void PutByteArray(const boost::shared_ptr<std::string>& key,
                              const boost::shared_ptr<ByteArray>& val) = 0;

    /// <summary>
    /// Associates the passed array of shorts with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified array is to be
    /// associated.</param> <param name="val">The array of shorts to be
    /// associated with the specified key.</param>
    virtual void
    PutShortArray(const std::string& key,
                  const boost::shared_ptr<std::vector<std::int16_t>>& val) = 0;

    /// <summary>
    /// Associates the passed array of shorts with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified array is to be
    /// associated.</param> <param name="val">The array of shorts to be
    /// associated with the specified key.</param>
    virtual void
    PutShortArray(const boost::shared_ptr<std::string>& key,
                  const boost::shared_ptr<std::vector<std::int16_t>>& val) = 0;

    /// <summary>
    /// Associates the passed array of integers with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified array is to be
    /// associated.</param> <param name="val">The array of integers to be
    /// associated with the specified key.</param>
    virtual void
    PutIntArray(const std::string& key,
                const boost::shared_ptr<std::vector<std::int32_t>>& val) = 0;

    /// <summary>
    /// Associates the passed array of integers with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified array is to be
    /// associated.</param> <param name="val">The array of integers to be
    /// associated with the specified key.</param>
    virtual void
    PutIntArray(const boost::shared_ptr<std::string>& key,
                const boost::shared_ptr<std::vector<std::int32_t>>& val) = 0;

    /// <summary>
    /// Associates the passed array of longs with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified array is to be
    /// associated.</param> <param name="val">The array of longs to be
    /// associated with the specified key.</param>
    virtual void
    PutLongArray(const std::string& key,
                 const boost::shared_ptr<std::vector<std::int64_t>>& val) = 0;

    /// <summary>
    /// Associates the passed array of longs with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified array is to be
    /// associated.</param> <param name="val">The array of longs to be
    /// associated with the specified key.</param>
    virtual void
    PutLongArray(const boost::shared_ptr<std::string>& key,
                 const boost::shared_ptr<std::vector<std::int64_t>>& val) = 0;

    /// <summary>
    /// Associates the passed array of floats with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified array is to be
    /// associated.</param> <param name="val">The array of floats to be
    /// associated with the specified key.</param>
    virtual void
    PutFloatArray(const std::string& key,
                  const boost::shared_ptr<std::vector<float>>& val) = 0;

    /// <summary>
    /// Associates the passed array of floats with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified array is to be
    /// associated.</param> <param name="val">The array of floats to be
    /// associated with the specified key.</param>
    virtual void
    PutFloatArray(const boost::shared_ptr<std::string>& key,
                  const boost::shared_ptr<std::vector<float>>& val) = 0;

    /// <summary>
    /// Associates the passed array of doubles with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified array is to be
    /// associated.</param> <param name="val">The array of doubles to be
    /// associated with the specified key.</param>
    virtual void
    PutDoubleArray(const std::string& key,
                   const boost::shared_ptr<std::vector<double>>& val) = 0;

    /// <summary>
    /// Associates the passed array of doubles with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified array is to be
    /// associated.</param> <param name="val">The array of doubles to be
    /// associated with the specified key.</param>
    virtual void
    PutDoubleArray(const boost::shared_ptr<std::string>& key,
                   const boost::shared_ptr<std::vector<double>>& val) = 0;

    /// <summary>
    /// Associates the passed array of UTF-8 strings with the specified key in
    /// this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified array is to be
    /// associated.</param> <param name="val">The array of UTF-8 strings to be
    /// associated with the specified key.</param>
    virtual void PutUtfStringArray(
        const std::string& key,
        const boost::shared_ptr<std::vector<std::string>>& val) = 0;

    /// <summary>
    /// Associates the passed array of UTF-8 strings with the specified key in
    /// this object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified array is to be
    /// associated.</param> <param name="val">The array of UTF-8 strings to be
    /// associated with the specified key.</param>
    virtual void PutUtfStringArray(
        const boost::shared_ptr<std::string>& key,
        const boost::shared_ptr<std::vector<std::string>>& val) = 0;

    /// <summary>
    /// Associates the passed ISFSArray object with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified object is to be
    /// associated.</param> <param name="val">The object to be associated with
    /// the specified key.</param>
    virtual void PutSFSArray(const std::string& key,
                             const boost::shared_ptr<ISFSArray>& val) = 0;

    /// <summary>
    /// Associates the passed ISFSArray object with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified object is to be
    /// associated.</param> <param name="val">The object to be associated with
    /// the specified key.</param>
    virtual void PutSFSArray(const boost::shared_ptr<std::string>& key,
                             const boost::shared_ptr<ISFSArray>& val) = 0;

    /// <summary>
    /// Associates the passed ISFSObject object with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified object is to be
    /// associated.</param> <param name="val">The object to be associated with
    /// the specified key.</param>
    virtual void PutSFSObject(const std::string& key,
                              const boost::shared_ptr<ISFSObject>& val) = 0;

    /// <summary>
    /// Associates the passed ISFSObject object with the specified key in this
    /// object.
    /// </summary>
    ///
    /// <param name="key">The key with which the specified object is to be
    /// associated.</param> <param name="val">The object to be associated with
    /// the specified key.</param>
    virtual void PutSFSObject(const boost::shared_ptr<std::string>& key,
                              const boost::shared_ptr<ISFSObject>& val) = 0;

    /// <summary>
    /// Associates the passed custom class instance with the specified key in
    /// this object.
    /// </summary>
    ///
    /// <remarks>
    /// Read the <see cref="GetClass"/> method description for more
    /// informations. <para/>
    /// </remarks>
    ///
    /// <param name="key">The key with which the specified custom class instance
    /// is to be associated.</param> <param name="val">The custom class instance
    /// to be associated with the specified key.</param>
    ///
    /// <seealso cref="GetClass"/>
    virtual void PutClass(const std::string& key,
                          const boost::shared_ptr<void>& val) = 0;

    /// <summary>
    /// Associates the passed custom class instance with the specified key in
    /// this object.
    /// </summary>
    ///
    /// <remarks>
    /// Read the <see cref="GetClass"/> method description for more
    /// informations. <para/>
    /// </remarks>
    ///
    /// <param name="key">The key with which the specified custom class instance
    /// is to be associated.</param> <param name="val">The custom class instance
    /// to be associated with the specified key.</param>
    ///
    /// <seealso cref="GetClass"/>
    virtual void PutClass(const boost::shared_ptr<std::string>& key,
                          const boost::shared_ptr<void>& val) = 0;

    /// <exclude/>
    virtual void Put(const std::string& key,
                     const boost::shared_ptr<SFSDataWrapper>& val) = 0;

    /// <exclude/>
    virtual void Put(const boost::shared_ptr<std::string>& key,
                     const boost::shared_ptr<SFSDataWrapper>& val) = 0;
};
} // namespace Data
} // namespace Entities
} // namespace Sfs2X

#endif
