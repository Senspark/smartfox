// ===================================================================
//
// Description
//        Contains the implementation of BitSwarmEvent
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "BitSwarmEvent.h"

namespace Sfs2X {
namespace Bitswarm {
boost::shared_ptr<std::string>
    BitSwarmEvent::CONNECT(new std::string("connect"));
boost::shared_ptr<std::string>
    BitSwarmEvent::DISCONNECT(new std::string("disconnect"));
boost::shared_ptr<std::string>
    BitSwarmEvent::RECONNECTION_TRY(new std::string("reconnectionTry"));
boost::shared_ptr<std::string>
    BitSwarmEvent::IO_ERROR(new std::string("ioError"));
boost::shared_ptr<std::string>
    BitSwarmEvent::SECURITY_ERROR(new std::string("securityError"));
boost::shared_ptr<std::string>
    BitSwarmEvent::DATA_ERROR(new std::string("dataError"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BitSwarmEvent::BitSwarmEvent(const boost::shared_ptr<std::string>& type)
    : BaseEvent(type,
                boost::shared_ptr<map<string, boost::shared_ptr<void>>>()) {}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BitSwarmEvent::BitSwarmEvent(
    const boost::shared_ptr<std::string>& type,
    boost::shared_ptr<map<string, boost::shared_ptr<void>>> arguments)
    : BaseEvent(type, arguments) {}

} // namespace Bitswarm
} // namespace Sfs2X
