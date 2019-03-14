// ===================================================================
//
// Description
//        Contains the definition of ISFSArray interface
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __ISFSArray__
#define __ISFSArray__

// Forward class declaration
namespace Sfs2X {
namespace Entities {
namespace Data {
class ISFSArray;
} // namespace Data
} // namespace Entities
} // namespace Sfs2X

#include "../../Util/ByteArray.h"
#include "SFSDataWrapper.h"
#include "ISFSObject.h"

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
/// SFSArray interface
/// </summary>
class DLLImportExport ISFSArray {
public:
    virtual ~ISFSArray() = default;

    /// <summary>
    /// Returns true if the passed object is contained in the Array
    /// </summary>
    /// <param name="obj">
    /// A void pointer
    /// </param>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool Contains(const boost::shared_ptr<void>& obj) const = 0;

    /// <summary>
    /// Returns the element at the specified index
    /// </summary>
    /// <param name="index">
    /// A long integer
    /// </param>
    /// <returns>
    /// A void pointer
    /// </returns>
    virtual boost::shared_ptr<void> GetElementAt(std::size_t index) const = 0;

    virtual boost::shared_ptr<SFSDataWrapper>
    GetWrappedElementAt(std::size_t index) const = 0;

    /// <summary>
    /// Remove the element at the specified index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A void pointer
    /// </returns>
    virtual boost::shared_ptr<void> RemoveElementAt(std::size_t index) = 0;

    /// <summary>
    /// Return the number of elements in the Array
    /// </summary>
    /// <returns>
    /// A long integer
    /// </returns>
    virtual std::size_t Size() const = 0;

    /// <summary>
    /// Return the binary form of the object
    /// </summary>
    /// <returns>
    /// Pointer to a <see cref="ByteArray"/> instance
    /// </returns>
    virtual boost::shared_ptr<ByteArray> ToBinary() = 0;

    /// <summary>
    /// Return a formatted dump of the object that can logged or traced in the
    /// console for debugging purposes.
    /// </summary>
    /// <param name="format">
    /// turns the "pretty print" on/off
    /// </param>
    /// <returns>
    /// A string pointer
    /// </returns>
    virtual boost::shared_ptr<std::string> GetDump(bool format) const = 0;

    /// <summary>
    /// Return a formatted dump of the object that can logged or traced in the
    /// console for debugging purposes.
    /// </summary>
    /// <returns>
    /// A string pointer
    /// </returns>
    virtual boost::shared_ptr<std::string>
    GetDump() const = 0; // Default to true

    /// <summary>
    /// Returns a detailed hex-dump of the object that can logged or traced in
    /// the console for debugging purposes.
    /// </summary>
    /// <returns>
    /// A string pointer
    /// </returns>
    virtual boost::shared_ptr<std::string> GetHexDump() = 0;

    /*
     * :::::::::::::::::::::::::::::::::::::::::
     * Type setters
     * :::::::::::::::::::::::::::::::::::::::::
     */

    // Primitives
    /// <summary>
    /// Add a null element
    /// </summary>
    virtual void AddNull() = 0;

    /// <summary>
    /// Add a Boolean value
    /// </summary>
    /// <param name="val">
    /// A boolean
    /// </param>
    virtual void AddBool(const boost::shared_ptr<bool>& val) = 0;

    /// <summary>
    /// Add a Boolean value
    /// </summary>
    /// <param name="val">
    /// A boolean
    /// </param>
    virtual void AddBool(bool val) = 0;

    /// <summary>
    /// Add a byte value (8 bit)
    /// </summary>
    /// <param name="val">
    /// An unsigned char
    /// </param>
    virtual void AddByte(const boost::shared_ptr<std::uint8_t>& val) = 0;

    /// <summary>
    /// Add a byte value (8 bit)
    /// </summary>
    /// <param name="val">
    /// An unsigned char
    /// </param>
    virtual void AddByte(std::uint8_t val) = 0;

    /// <summary>
    /// Add a short int value (16 bit)
    /// </summary>
    /// <param name="val">
    /// A short integer
    /// </param>
    virtual void AddShort(const boost::shared_ptr<std::int16_t>& val) = 0;

    /// <summary>
    /// Add a short int value (16 bit)
    /// </summary>
    /// <param name="val">
    /// A short integer
    /// </param>
    virtual void AddShort(std::int16_t val) = 0;

    /// <summary>
    /// Add an int value (32 bit)
    /// </summary>
    /// <param name="val">
    /// A long integer
    /// </param>
    virtual void AddInt(const boost::shared_ptr<std::int32_t>& val) = 0;

    /// <summary>
    /// Add an int value (32 bit)
    /// </summary>
    /// <param name="val">
    /// A long integer
    /// </param>
    virtual void AddInt(std::int32_t val) = 0;

    /// <summary>
    /// Add a long int value (64 bit)
    /// </summary>
    /// <param name="val">
    /// A long
    /// </param>
    virtual void AddLong(const boost::shared_ptr<std::int64_t>& val) = 0;

    /// <summary>
    /// Add a long int value (64 bit)
    /// </summary>
    /// <param name="val">
    /// A long
    /// </param>
    virtual void AddLong(std::int64_t val) = 0;

    /// <summary>
    /// Add a float value (32 bit)
    /// </summary>
    /// <param name="val">
    /// A float
    /// </param>
    virtual void AddFloat(const boost::shared_ptr<float>& val) = 0;

    /// <summary>
    /// Add a float value (32 bit)
    /// </summary>
    /// <param name="val">
    /// A float
    /// </param>
    virtual void AddFloat(float val) = 0;

    /// <summary>
    /// Add a dobule value (64 bit)
    /// </summary>
    /// <param name="val">
    /// A double
    /// </param>
    virtual void AddDouble(const boost::shared_ptr<double>& val) = 0;

    /// <summary>
    /// Add a dobule value (64 bit)
    /// </summary>
    /// <param name="val">
    /// A double
    /// </param>
    virtual void AddDouble(double val) = 0;

    /// <summary>
    /// Appends a UTF-8 string (with max length of 32 KBytes) value to the end
    /// of this array.
    /// </summary>
    /// <param name="val">
    /// A string pointer
    /// </param>
    virtual void AddUtfString(const boost::shared_ptr<std::string>& val) = 0;

    /// <summary>
    /// Appends a UTF-8 string (with max length of 32 KBytes) value to the end
    /// of this array.
    /// </summary>
    /// <param name="val">
    /// A string pointer
    /// </param>
    virtual void AddUtfString(const std::string& val) = 0;

    /// <summary>
    /// Appends a UTF-8 string (with max length of 2 GBytes) value to the end of
    /// this array.
    /// </summary>
    /// <param name="val">
    /// The value to be appended to this array.
    /// </param>
    virtual void AddText(const boost::shared_ptr<std::string>& val) = 0;

    /// <summary>
    /// Appends a UTF-8 string (with max length of 2 GBytes) value to the end of
    /// this array.
    /// </summary>
    /// <param name="val">
    /// The value to be appended to this array.
    /// </param>
    virtual void AddText(const std::string& val) = 0;

    /// <summary>
    /// Add an array of Booleans
    /// </summary>
    /// <param name="val">
    /// A bool[]
    /// </param>
    virtual void AddBoolArray(
        const boost::shared_ptr<std::vector<boost::shared_ptr<bool>>>& val) = 0;

    /// <summary>
    /// Add an array of bytes
    /// </summary>
    /// <param name="val">
    /// Pointer to a <see cref="ByteArray"/> instance
    /// </param>
    virtual void AddByteArray(const boost::shared_ptr<ByteArray>& val) = 0;

    /// <summary>
    /// Add an array of short ints
    /// </summary>
    /// <param name="val">
    /// A short[]
    /// </param>
    virtual void AddShortArray(
        const boost::shared_ptr<std::vector<boost::shared_ptr<std::int16_t>>>&
            val) = 0;

    /// <summary>
    /// Add an array of ints
    /// </summary>
    /// <param name="val">
    /// A int[]
    /// </param>
    virtual void AddIntArray(
        const boost::shared_ptr<std::vector<boost::shared_ptr<std::int32_t>>>&
            val) = 0;

    /// <summary>
    /// Add an array of long ints
    /// </summary>
    /// <param name="val">
    /// A long[]
    /// </param>
    virtual void AddLongArray(
        const boost::shared_ptr<std::vector<boost::shared_ptr<std::int64_t>>>&
            val) = 0;

    /// <summary>
    /// Add an array of floats
    /// </summary>
    /// <param name="val">
    /// A float[]
    /// </param>
    virtual void AddFloatArray(
        const boost::shared_ptr<std::vector<boost::shared_ptr<float>>>&
            val) = 0;

    /// <summary>
    /// Add an array of doubles
    /// </summary>
    /// <param name="val">
    /// A double[]
    /// </param>
    virtual void AddDoubleArray(
        const boost::shared_ptr<std::vector<boost::shared_ptr<double>>>&
            val) = 0;

    /// <summary>
    /// Add an array of UTF-8 String
    /// </summary>
    /// <param name="val">
    /// A string[]
    /// </param>
    virtual void AddUtfStringArray(
        const boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>>&
            val) = 0;

    /// <summary>
    /// Add an SFSArray
    /// </summary>
    /// <param name="val">
    /// Pointer to a <see cref="ISFSArray"/> instance
    /// </param>const
    virtual void AddSFSArray(const boost::shared_ptr<ISFSArray>& val) = 0;

    /// <summary>
    /// Add an SFSObject
    /// </summary>
    /// <param name="val">
    /// Pointer to a <see cref="ISFSObject"/> instance
    /// </param>
    /// <seealso cref="SFSObject"/>
    virtual void AddSFSObject(const boost::shared_ptr<ISFSObject>& val) = 0;

    /// <summary>
    /// Add an instance of a custom Class.
    /// </summary>
    /// <remarks>
    /// This is an advanced feature that allows to transmit object instances
    /// between Actionscript and Java provided that both classes are definined
    /// under the same package name.
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
    ///                 private List<String> weapons;
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
    ///         boost::shared_ptr<SpaceShip> mySpaceShip =
    /// (boost::shared_ptr<SpaceShip>)sfsArray->getClass(0)     \endcode
    ///
    /// </example>
    /// <param name="val">
    /// A void pointer
    /// </param>
    virtual void AddClass(const boost::shared_ptr<void>& val) = 0;

    virtual void Add(const boost::shared_ptr<SFSDataWrapper>& val) = 0;

    /*
     * :::::::::::::::::::::::::::::::::::::::::
     * Type getters
     * :::::::::::::::::::::::::::::::::::::::::
     */

    /// <summary>
    /// Checks if a certain element in the Array is null
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool IsNull(std::size_t index) const = 0;

    /// <summary>
    /// Get a Boolean element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A boolean
    /// </returns>
    virtual bool GetBool(std::size_t index) const = 0;

    /// <summary>
    /// Get a byte element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// An unsigned char
    /// </returns>
    virtual std::uint8_t GetByte(std::size_t index) const = 0;

    /// <summary>
    /// Get a short int element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A short integer
    /// </returns>
    virtual std::int16_t GetShort(std::size_t index) const = 0;

    /// <summary>
    /// Get an int element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A long integer
    /// </returns>
    virtual std::int32_t GetInt(std::size_t index) const = 0;

    /// <summary>
    /// Get a long int element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A long
    /// </returns>
    virtual std::int64_t GetLong(std::size_t index) const = 0;

    /// <summary>
    /// Get a float element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A float
    /// </returns>
    virtual float GetFloat(std::size_t index) const = 0;

    /// <summary>
    /// Get a double element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A double
    /// </returns>
    virtual double GetDouble(std::size_t index) const = 0;

    /// <summary>
    /// Returns the element at the specified position as an UTF-8 string, with
    /// max length of 32 KBytes.
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A string pointer
    /// </returns>
    virtual boost::shared_ptr<std::string>
    GetUtfString(std::size_t index) const = 0;

    /// <summary>
    /// Returns the element at the specified position as an UTF-8 string, with
    /// max length of 2 GBytes.
    /// </summary>
    /// <param name="index">
    ///    The position of the element to return.
    ///    </param>
    /// <returns>
    ///    The element of this array at the specified index.
    ///    </returns>
    virtual boost::shared_ptr<std::string> GetText(std::size_t index) const = 0;

    /// <summary>
    /// Get a Boolean Array element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A bool[]
    /// </returns>
    virtual boost::shared_ptr<std::vector<bool>>
    GetBoolArray(std::size_t index) const = 0;

    /// <summary>
    /// Get a byte Array element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// Pointer to a <see cref="ByteArray"/> instance
    /// </returns>
    virtual boost::shared_ptr<ByteArray>
    GetByteArray(std::size_t index) const = 0;

    /// <summary>
    /// Get a short Array element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A short[]
    /// </returns>
    virtual boost::shared_ptr<std::vector<std::int16_t>>
    GetShortArray(std::size_t index) const = 0;

    /// <summary>
    /// Get a int Array element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A int[]
    /// </returns>
    virtual boost::shared_ptr<std::vector<std::int32_t>>
    GetIntArray(std::size_t index) const = 0;

    /// <summary>
    /// Get a lomg Array element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A long[]
    /// </returns>
    virtual boost::shared_ptr<std::vector<std::int64_t>>
    GetLongArray(std::size_t index) const = 0;

    /// <summary>
    /// Get a float Array element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A float[]
    /// </returns>
    virtual boost::shared_ptr<std::vector<float>>
    GetFloatArray(std::size_t index) const = 0;

    /// <summary>
    /// Get a double Array element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A double[]
    /// </returns>
    virtual boost::shared_ptr<std::vector<double>>
    GetDoubleArray(std::size_t index) const = 0;

    /// <summary>
    /// Get a String Array element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A string[]
    /// </returns>
    virtual boost::shared_ptr<std::vector<std::string>>
    GetUtfStringArray(std::size_t index) const = 0;

    /// <summary>
    /// Get an SFSArray element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// Pointer to a <see cref="ISFSArray"/> instance
    /// </returns>
    virtual boost::shared_ptr<ISFSArray>
    GetSFSArray(std::size_t index) const = 0;

    /// <summary>
    /// Get an SFSObject element at the provided index
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// Pointer to a <see cref="ISFSObject"/> instance
    /// </returns>
    virtual boost::shared_ptr<ISFSObject>
    GetSFSObject(std::size_t index) const = 0;

    /// <summary>
    /// Get a class instance at the provided index.
    /// </summary>
    /// <param name="index">
    /// An unsigned long integer
    /// </param>
    /// <returns>
    /// A void pointer
    /// </returns>
    /// <seealso cref="AddClass"/>
    virtual boost::shared_ptr<void> GetClass(std::size_t index) const = 0;
};
} // namespace Data
} // namespace Entities
} // namespace Sfs2X

#endif
