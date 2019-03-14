// ===================================================================
//
// Description
//        Contains the definition of SFSObject
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __SFSObject__
#define __SFSObject__

#include "../../Protocol/Serialization/DefaultObjectDumpFormatter.h"
#include "../../Protocol/Serialization/DefaultSFSDataSerializer.h"
#include "ISFSObject.h"
#include "../../Util/StringFormatter.h"
#include <boost/exception/exception.hpp>
#include <boost/exception/all.hpp>
#include <boost/shared_ptr.hpp>              // Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp> // Boost shared_ptr for this

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object
#include <map>    // STL library: map object

using namespace Sfs2X::Exceptions;
using namespace Sfs2X::Protocol::Serialization;
using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Entities {
namespace Data {

/// <summary>
/// SFSObject
/// </summary>
/// <remarks>
/// <b>SFSObject</b> is used from server and client side to exchange data. It
/// can be thought of a specialized Dictionary/Map object that can contain any
/// type of data. <br/> The advantage of using SFSObject is that you can fine
/// tune the way your data will be transmitted over the network.<br/> For
/// instance, a number like 100 can be transmitted as a normal <b>integer</b>
/// (which takes 32 bits) but also a <b>short</b> (16 bit) or even a <b>byte</b>
/// (8 bit) <para/> <b>SFSObject</b> supports many primitive data types and
/// related arrays of primitives. It also allows to serialize class instances
/// and rebuild them on the Java side. <br/> This is explained in greater detail
/// in a separate document.
/// </remarks>
/// <seealso cref="SFSArray"/>
class DLLImportExport SFSObject
    : public ISFSObject,
      public boost::enable_shared_from_this<SFSObject> {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    /// <summary>
    /// Alternative static constructor that builds an SFSObject populated with
    /// the data found in the passed Object
    /// </summary>
    /// <param name="o">
    /// A void pointer
    /// </param>
    /// <returns>
    /// Pointer to a <see cref="SFSObject"/> instance
    /// </returns>
    static boost::shared_ptr<SFSObject>
    NewFromObject(const boost::shared_ptr<void>& o);

    /// <summary>
    /// Alternative static constructor that builds an SFSObject from a valid
    /// SFSObject binary representation
    /// </summary>
    /// <param name="ba">
    /// Pointer to a <see cref="ByteArray"/> instance
    /// </param>
    /// <returns>
    /// Pointer to a <see cref="SFSObject"/> instance
    /// </returns>
    static boost::shared_ptr<SFSObject>
    NewFromBinaryData(const boost::shared_ptr<ByteArray>& ba);

    /// <summary>
    /// Alternative static constructor
    /// </summary>
    /// <returns>
    /// Pointer to a <see cref="SFSObject"/> instance
    /// </returns>
    static boost::shared_ptr<SFSObject> NewInstance();

    /// <summary>
    ///
    /// </summary>
    /// <summary>
    ///
    /// </summary>
    SFSObject();
    virtual ~SFSObject() override;

    virtual boost::shared_ptr<SFSDataWrapper>
    GetData(const std::string& key) const override;

    virtual boost::shared_ptr<SFSDataWrapper>
    GetData(const boost::shared_ptr<std::string>& key) const override;

    // T GetValue<T>(const std::string& key);
    virtual boost::shared_ptr<bool>
    GetBool(const std::string& key) const override;

    virtual boost::shared_ptr<bool>
    GetBool(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<unsigned char>
    GetByte(const std::string& key) const override;

    virtual boost::shared_ptr<unsigned char>
    GetByte(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<std::int16_t>
    GetShort(const std::string& key) const override;

    virtual boost::shared_ptr<std::int16_t>
    GetShort(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<std::int32_t>
    GetInt(const std::string& key) const override;

    virtual boost::shared_ptr<std::int32_t>
    GetInt(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<std::int64_t>
    GetLong(const std::string& key) const override;

    virtual boost::shared_ptr<std::int64_t>
    GetLong(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<float>
    GetFloat(const std::string& key) const override;

    virtual boost::shared_ptr<float>
    GetFloat(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<double>
    GetDouble(const std::string& key) const override;

    virtual boost::shared_ptr<double>
    GetDouble(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<std::string>
    GetUtfString(const std::string& key) const override;

    virtual boost::shared_ptr<std::string>
    GetUtfString(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<std::string>
    GetText(const std::string& key) const override;

    virtual boost::shared_ptr<std::string>
    GetText(const boost::shared_ptr<std::string>& key) const override;

    boost::shared_ptr<std::vector<std::uint8_t>>
    GetArray(const std::string& key) const;

    boost::shared_ptr<std::vector<std::uint8_t>>
    GetArray(const boost::shared_ptr<std::string>& key) const;

    virtual boost::shared_ptr<std::vector<bool>>
    GetBoolArray(const std::string& key) const override;

    virtual boost::shared_ptr<std::vector<bool>>
    GetBoolArray(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<ByteArray>
    GetByteArray(const std::string& key) const override;

    virtual boost::shared_ptr<ByteArray>
    GetByteArray(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<std::vector<std::int16_t>>
    GetShortArray(const std::string& key) const override;

    virtual boost::shared_ptr<std::vector<std::int16_t>>
    GetShortArray(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<std::vector<std::int32_t>>
    GetIntArray(const std::string& key) const override;

    virtual boost::shared_ptr<std::vector<std::int32_t>>
    GetIntArray(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<std::vector<std::int64_t>>
    GetLongArray(const std::string& key) const override;

    virtual boost::shared_ptr<std::vector<std::int64_t>>
    GetLongArray(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<std::vector<float>>
    GetFloatArray(const std::string& key) const override;

    virtual boost::shared_ptr<std::vector<float>>
    GetFloatArray(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<std::vector<double>>
    GetDoubleArray(const std::string& key) const override;

    virtual boost::shared_ptr<std::vector<double>>
    GetDoubleArray(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<std::vector<std::string>>
    GetUtfStringArray(const std::string& key) const override;

    virtual boost::shared_ptr<std::vector<std::string>>
    GetUtfStringArray(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<ISFSArray>
    GetSFSArray(const std::string& key) const override;

    virtual boost::shared_ptr<ISFSArray>
    GetSFSArray(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<ISFSObject>
    GetSFSObject(const std::string& key) const override;

    virtual boost::shared_ptr<ISFSObject>
    GetSFSObject(const boost::shared_ptr<std::string>& key) const override;

    virtual void PutNull(const std::string& key) override;
    virtual void PutNull(const boost::shared_ptr<std::string>& key) override;

    virtual void PutBool(const std::string& key,
                         const boost::shared_ptr<bool>& val) override;
    virtual void PutBool(const boost::shared_ptr<std::string>& key,
                         const boost::shared_ptr<bool>& val) override;
    virtual void PutBool(const std::string& key, bool val) override;
    virtual void PutBool(const boost::shared_ptr<std::string>& key,
                         bool val) override;

    virtual void PutByte(const std::string& key,
                         const boost::shared_ptr<std::uint8_t>& val) override;
    virtual void PutByte(const boost::shared_ptr<std::string>& key,
                         const boost::shared_ptr<std::uint8_t>& val) override;
    virtual void PutByte(const std::string& key, std::uint8_t val) override;
    virtual void PutByte(const boost::shared_ptr<std::string>& key,
                         std::uint8_t val) override;

    virtual void PutShort(const std::string& key,
                          const boost::shared_ptr<std::int16_t>& val) override;
    virtual void PutShort(const boost::shared_ptr<std::string>& key,
                          const boost::shared_ptr<std::int16_t>& val) override;
    virtual void PutShort(const std::string& key, std::int16_t val) override;
    virtual void PutShort(const boost::shared_ptr<std::string>& key,
                          std::int16_t val) override;

    virtual void PutInt(const std::string& key,
                        const boost::shared_ptr<std::int32_t>& val) override;
    virtual void PutInt(const boost::shared_ptr<std::string>& key,
                        const boost::shared_ptr<std::int32_t>& val) override;
    virtual void PutInt(const std::string& key, std::int32_t val) override;
    virtual void PutInt(const boost::shared_ptr<std::string>& key,
                        std::int32_t val) override;

    virtual void PutLong(const std::string& key,
                         const boost::shared_ptr<std::int64_t>& val) override;
    virtual void PutLong(const boost::shared_ptr<std::string>& key,
                         const boost::shared_ptr<std::int64_t>& val) override;
    virtual void PutLong(const std::string& key, std::int64_t val) override;
    virtual void PutLong(const boost::shared_ptr<std::string>& key,
                         std::int64_t val) override;

    virtual void PutFloat(const std::string& key,
                          const boost::shared_ptr<float>& val) override;
    virtual void PutFloat(const boost::shared_ptr<std::string>& key,
                          const boost::shared_ptr<float>& val) override;
    virtual void PutFloat(const std::string& key, float val) override;
    virtual void PutFloat(const boost::shared_ptr<std::string>& key,
                          float val) override;

    virtual void PutDouble(const std::string& key,
                           const boost::shared_ptr<double>& val) override;
    virtual void PutDouble(const boost::shared_ptr<std::string>& key,
                           const boost::shared_ptr<double>& val) override;
    virtual void PutDouble(const std::string& key, double val) override;
    virtual void PutDouble(const boost::shared_ptr<std::string>& key,
                           double val) override;

    virtual void
    PutUtfString(const std::string& key,
                 const boost::shared_ptr<std::string>& val) override;

    virtual void
    PutUtfString(const boost::shared_ptr<std::string>& key,
                 const boost::shared_ptr<std::string>& val) override;

    virtual void PutUtfString(const std::string& key,
                              const std::string& val) override;

    virtual void PutUtfString(const boost::shared_ptr<std::string>& key,
                              const std::string& val) override;

    virtual void PutText(const std::string& key,
                         const boost::shared_ptr<std::string>& val) override;

    virtual void PutText(const boost::shared_ptr<std::string>& key,
                         const boost::shared_ptr<std::string>& val) override;

    virtual void PutText(const std::string& key,
                         const std::string& val) override;

    virtual void PutText(const boost::shared_ptr<std::string>& key,
                         const std::string& val) override;

    virtual void
    PutBoolArray(const std::string& key,
                 const boost::shared_ptr<std::vector<bool>>& val) override;

    virtual void
    PutBoolArray(const boost::shared_ptr<std::string>& key,
                 const boost::shared_ptr<std::vector<bool>>& val) override;

    virtual void PutByteArray(const std::string& key,
                              const boost::shared_ptr<ByteArray>& val) override;

    virtual void PutByteArray(const boost::shared_ptr<std::string>& key,
                              const boost::shared_ptr<ByteArray>& val) override;
    virtual void PutShortArray(
        const std::string& key,
        const boost::shared_ptr<std::vector<std::int16_t>>& val) override;

    virtual void PutShortArray(
        const boost::shared_ptr<std::string>& key,
        const boost::shared_ptr<std::vector<std::int16_t>>& val) override;

    virtual void PutIntArray(
        const std::string& key,
        const boost::shared_ptr<std::vector<std::int32_t>>& val) override;

    virtual void PutIntArray(
        const boost::shared_ptr<std::string>& key,
        const boost::shared_ptr<std::vector<std::int32_t>>& val) override;

    virtual void PutLongArray(
        const std::string& key,
        const boost::shared_ptr<std::vector<std::int64_t>>& val) override;

    virtual void PutLongArray(
        const boost::shared_ptr<std::string>& key,
        const boost::shared_ptr<std::vector<std::int64_t>>& val) override;

    virtual void
    PutFloatArray(const std::string& key,
                  const boost::shared_ptr<std::vector<float>>& val) override;

    virtual void
    PutFloatArray(const boost::shared_ptr<std::string>& key,
                  const boost::shared_ptr<std::vector<float>>& val) override;

    virtual void
    PutDoubleArray(const std::string& key,
                   const boost::shared_ptr<std::vector<double>>& val) override;

    virtual void
    PutDoubleArray(const boost::shared_ptr<std::string>& key,
                   const boost::shared_ptr<std::vector<double>>& val) override;

    virtual void PutUtfStringArray(
        const std::string& key,
        const boost::shared_ptr<std::vector<std::string>>& val) override;

    virtual void PutUtfStringArray(
        const boost::shared_ptr<std::string>& key,
        const boost::shared_ptr<std::vector<std::string>>& val) override;

    virtual void PutSFSArray(const std::string& key,
                             const boost::shared_ptr<ISFSArray>& val) override;

    virtual void PutSFSArray(const boost::shared_ptr<std::string>& key,
                             const boost::shared_ptr<ISFSArray>& val) override;

    virtual void
    PutSFSObject(const std::string& key,
                 const boost::shared_ptr<ISFSObject>& val) override;

    virtual void
    PutSFSObject(const boost::shared_ptr<std::string>& key,
                 const boost::shared_ptr<ISFSObject>& val) override;

    virtual void Put(const std::string& key,
                     const boost::shared_ptr<SFSDataWrapper>& val) override;

    virtual void Put(const boost::shared_ptr<std::string>& key,
                     const boost::shared_ptr<SFSDataWrapper>& val) override;

    virtual bool ContainsKey(const std::string& key) const override;
    virtual bool
    ContainsKey(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<void>
    GetClass(const std::string& key) const override;
    virtual boost::shared_ptr<void>
    GetClass(const boost::shared_ptr<std::string>& key) const override;

    virtual boost::shared_ptr<std::string> GetDump(bool format) const override;
    virtual boost::shared_ptr<std::string> GetDump() const override;
    virtual boost::shared_ptr<std::string> GetHexDump() override;

    virtual boost::shared_ptr<std::vector<std::string>>
    GetKeys() const override;

    virtual bool
    IsNull(const boost::shared_ptr<std::string>& key) const override;
    virtual bool IsNull(const std::string& key) const override;

    virtual void PutClass(const std::string& key,
                          const boost::shared_ptr<void>& val) override;
    virtual void PutClass(const boost::shared_ptr<std::string>& key,
                          const boost::shared_ptr<void>& val) override;

    virtual void RemoveElement(const std::string& key) override;
    virtual void
    RemoveElement(const boost::shared_ptr<std::string>& key) override;

    virtual std::size_t Size() const override;

    virtual boost::shared_ptr<ByteArray> ToBinary() override;

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

    boost::shared_ptr<std::map<std::string, boost::shared_ptr<SFSDataWrapper>>>
        dataHolder;
    boost::shared_ptr<ISFSDataSerializer> serializer;
};
} // namespace Data
} // namespace Entities
} // namespace Sfs2X

#endif
