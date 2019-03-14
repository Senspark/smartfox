// ===================================================================
//
// Description
//        Contains the definition of IProtocolCodec interface
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __IProtocolCodec__
#define __IProtocolCodec__

namespace Sfs2X {
namespace Protocol {
class IProtocolCodec;
} // namespace Protocol
} // namespace Sfs2X

#include "../Bitswarm/IMessage.h"
#include "../Bitswarm/IoHandler.h"
#include "../Util/ByteArray.h"
#include "../Entities/Data/ISFSObject.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

namespace Sfs2X {
using namespace Bitswarm;
using namespace Util;
using namespace Entities::Data;

namespace Protocol {
class IProtocolCodec {
public:
    virtual ~IProtocolCodec() = default;
    
    virtual void OnPacketRead(boost::shared_ptr<ISFSObject> packet) = 0;
    virtual void OnPacketRead(boost::shared_ptr<ByteArray> packet) = 0;
    virtual void OnPacketWrite(boost::shared_ptr<IMessage> message) = 0;

    virtual boost::shared_ptr<IoHandler> IOHandler() = 0;
    virtual void IOHandler(boost::shared_ptr<IoHandler> value) = 0;
};
} // namespace Protocol
} // namespace Sfs2X

#endif
