// ===================================================================
//
// Description
//        Contains the definition of IUDPManager interface
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __IUDPManager__
#define __IUDPManager__

#include "../Util/ByteArray.h"
//#include "smartfox/Util/ByteArray.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object

namespace Sfs2X {
using namespace Util;

namespace Bitswarm {

// -------------------------------------------------------------------
// Interface IUDPManager
// -------------------------------------------------------------------
class IUDPManager {
public:
    virtual ~IUDPManager() = default;
    virtual void Initialize(const std::string& udpAddr,
                            std::uint16_t udpPort) = 0;
    virtual bool Inited() const = 0;
    virtual std::int64_t NextUdpPacketId() = 0;
    virtual void Send(const boost::shared_ptr<ByteArray>& binaryData) = 0;
    virtual void Reset() = 0;
    virtual void Disconnect() = 0;
    virtual void Dispose() = 0;
};
} // namespace Bitswarm
} // namespace Sfs2X

#endif
