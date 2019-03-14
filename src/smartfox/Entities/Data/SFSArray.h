// ===================================================================
//
// Description
//        Contains the definition of SFSArray
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __SFSArray__
#define __SFSArray__

#include "ISFSArray.h"
#include "../../Util/ByteArray.h"
#include "../../Protocol/Serialization/ISFSDataSerializer.h"
#include "../../Entities/Data/SFSDataWrapper.h"

#include <boost/shared_ptr.hpp>              // Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp> // Boost shared_ptr for this

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object
#include <map>    // STL library: map object
#include <vector> // STL library: vector object

using namespace Sfs2X::Protocol::Serialization;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Entities {
namespace Data {

/// <summary>
/// SFSArray
/// </summary>
/// <remarks>
/// <b>SFSArray</b> is used from server and client side to exchange data. It can
/// be thought of a specialized Array/List object that can contain any type of
/// data. The advantage of using SFSArray is that you can fine tune the way your
/// data will be transmitted over the network. For instance, a number like 100
/// can be transmitted as a normal <b>integer</b> (which takes 32 bits) but also
/// a <b>short</b> (16 bit) or even a <b>byte</b> (8 bit) <para/>
/// <b>SFSArray</b> supports many primitive data types and related arrays of
/// primitives. It also allows to serialize class instances and rebuild them on
/// the Java side. This is explained in greater detail in a separate document.
/// </remarks>
/// <seealso cref="SFSObject"/>
class DLLImportExport SFSArray
    : public ISFSArray,
      public boost::enable_shared_from_this<SFSArray> {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    /// <summary>
    /// Alternative static constructor that builds an SFSArray populated with
    /// the data found in the passed Array
    /// </summary>
    /// <param name="o">
    /// A vector of <see cref="SFSDataWrapper"/> pointers
    /// </param>
    /// <returns>
    /// Pointer to an <see cref="SFSArray"/> instance
    /// </returns>
    static boost::shared_ptr<SFSArray>
    NewFromArray(const std::vector<boost::shared_ptr<SFSDataWrapper>>& o);

    /// <summary>
    /// Alternative static constructor that builds an SFSArray from a valid
    /// SFSArray binary representation
    /// </summary>
    /// <param name="ba">
    /// Pointer to a <see cref="ByteArray"/> instance
    /// </param>
    /// <returns>
    /// Pointer to a <see cref="SFSArray"/> instance
    /// </returns>
    static boost::shared_ptr<SFSArray>
    NewFromBinaryData(const boost::shared_ptr<ByteArray>& ba);

    /// <summary>
    /// Alternative static constructor
    /// </summary>
    /// <returns>
    /// Pointer to a <see cref="SFSArray"/> instance
    /// </returns>
    static boost::shared_ptr<SFSArray> NewInstance();

    SFSArray();
    virtual ~SFSArray() override;

    virtual bool Contains(const boost::shared_ptr<void>& obj) const override;

    virtual boost::shared_ptr<SFSDataWrapper>
    GetWrappedElementAt(std::size_t index) const override;

    virtual boost::shared_ptr<void>
    GetElementAt(std::size_t index) const override;

    virtual boost::shared_ptr<void> RemoveElementAt(std::size_t index) override;
    virtual std::size_t Size() const override;
    virtual boost::shared_ptr<ByteArray> ToBinary() override;
    virtual boost::shared_ptr<std::string> GetDump() const override;
    virtual boost::shared_ptr<std::string> GetDump(bool format) const override;
    virtual boost::shared_ptr<std::string> GetHexDump() override;

    /*
     * :::::::::::::::::::::::::::::::::::::::::
     * Type setters
     * :::::::::::::::::::::::::::::::::::::::::
     */
    virtual void AddNull() override;

    virtual void AddBool(const boost::shared_ptr<bool>& val) override;
    virtual void AddBool(bool val) override;

    virtual void AddByte(const boost::shared_ptr<std::uint8_t>& val) override;
    virtual void AddByte(std::uint8_t val) override;

    virtual void AddShort(const boost::shared_ptr<std::int16_t>& val) override;
    virtual void AddShort(std::int16_t val) override;

    virtual void AddInt(const boost::shared_ptr<std::int32_t>& val) override;
    virtual void AddInt(std::int32_t val) override;

    virtual void AddLong(const boost::shared_ptr<std::int64_t>& val) override;
    virtual void AddLong(std::int64_t val) override;

    virtual void AddFloat(const boost::shared_ptr<float>& val) override;
    virtual void AddFloat(float val) override;

    virtual void AddDouble(const boost::shared_ptr<double>& val) override;
    virtual void AddDouble(double val) override;

    virtual void
    AddUtfString(const boost::shared_ptr<std::string>& val) override;
    virtual void AddUtfString(const std::string& val) override;

    virtual void AddText(const boost::shared_ptr<std::string>& val) override;
    virtual void AddText(const std::string& val) override;

    virtual void AddBoolArray(
        const boost::shared_ptr<std::vector<boost::shared_ptr<bool>>>& val)
        override;
    virtual void AddByteArray(const boost::shared_ptr<ByteArray>& val) override;

    virtual void AddShortArray(
        const boost::shared_ptr<std::vector<boost::shared_ptr<std::int16_t>>>&
            val) override;

    virtual void AddIntArray(
        const boost::shared_ptr<std::vector<boost::shared_ptr<std::int32_t>>>&
            val) override;

    virtual void AddLongArray(
        const boost::shared_ptr<std::vector<boost::shared_ptr<std::int64_t>>>&
            val) override;

    virtual void AddFloatArray(
        const boost::shared_ptr<std::vector<boost::shared_ptr<float>>>& val)
        override;

    virtual void AddDoubleArray(
        const boost::shared_ptr<std::vector<boost::shared_ptr<double>>>& val)
        override;

    virtual void AddUtfStringArray(
        const boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>>&
            val) override;

    virtual void AddSFSArray(const boost::shared_ptr<ISFSArray>& val) override;

    virtual void
    AddSFSObject(const boost::shared_ptr<ISFSObject>& val) override;

    virtual void AddClass(const boost::shared_ptr<void>& val) override;

    virtual void
    Add(const boost::shared_ptr<SFSDataWrapper>& wrappedObject) override;

    void AddObject(const boost::shared_ptr<void>& val, SFSDataType tp);

    /*
     * :::::::::::::::::::::::::::::::::::::::::
     * Type getters
     * :::::::::::::::::::::::::::::::::::::::::
     */
    virtual bool IsNull(std::size_t index) const override;
    // T GetValue<T>(int index)
    virtual bool GetBool(std::size_t index) const override;
    virtual std::uint8_t GetByte(std::size_t index) const override;
    virtual std::int16_t GetShort(std::size_t index) const override;
    virtual std::int32_t GetInt(std::size_t index) const override;
    virtual std::int64_t GetLong(std::size_t index) const override;
    virtual float GetFloat(std::size_t index) const override;
    virtual double GetDouble(std::size_t index) const override;

    virtual boost::shared_ptr<std::string>
    GetUtfString(std::size_t index) const override;

    virtual boost::shared_ptr<std::string>
    GetText(std::size_t index) const override;

    boost::shared_ptr<std::vector<boost::shared_ptr<void>>>
    GetArray(std::size_t index) const;

    virtual boost::shared_ptr<std::vector<bool>>
    GetBoolArray(std::size_t index) const override;

    virtual boost::shared_ptr<ByteArray>
    GetByteArray(std::size_t index) const override;

    virtual boost::shared_ptr<std::vector<std::int16_t>>
    GetShortArray(std::size_t index) const override;

    virtual boost::shared_ptr<std::vector<std::int32_t>>
    GetIntArray(std::size_t index) const override;

    virtual boost::shared_ptr<std::vector<std::int64_t>>
    GetLongArray(std::size_t index) const override;

    virtual boost::shared_ptr<std::vector<float>>
    GetFloatArray(std::size_t index) const override;

    virtual boost::shared_ptr<std::vector<double>>
    GetDoubleArray(std::size_t index) const override;

    virtual boost::shared_ptr<std::vector<std::string>>
    GetUtfStringArray(std::size_t index) const override;

    virtual boost::shared_ptr<ISFSArray>
    GetSFSArray(std::size_t index) const override;

    virtual boost::shared_ptr<void> GetClass(std::size_t index) const override;

    virtual boost::shared_ptr<ISFSObject>
    GetSFSObject(std::size_t index) const override;

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

    boost::shared_ptr<std::string> Dump() const;

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------

    boost::shared_ptr<ISFSDataSerializer> serializer;
    boost::shared_ptr<std::vector<boost::shared_ptr<SFSDataWrapper>>>
        dataHolder;
};
} // namespace Data
} // namespace Entities
} // namespace Sfs2X

#endif
