// ===================================================================
//
// Description
//        Contains the definition of IMessage interface
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __IMessage__
#define __IMessage__

#include "../Entities/Data/ISFSObject.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Bitswarm {

// -------------------------------------------------------------------
// Interface IMessage
// -------------------------------------------------------------------
class IMessage {
public:
    virtual ~IMessage() = default;

    virtual int Id() const = 0;
    virtual void Id(int value) = 0;

    virtual boost::shared_ptr<ISFSObject> Content() const = 0;
    virtual void Content(const boost::shared_ptr<ISFSObject>& object) = 0;

    virtual int TargetController() const = 0;
    virtual void TargetController(int) = 0;

    virtual bool IsEncrypted() const = 0;
    virtual void IsEncrypted(bool value) = 0;

    virtual bool IsUDP() const = 0;
    virtual void IsUDP(bool value) = 0;

    virtual std::int64_t PacketId() const = 0;
    virtual void PacketId(std::int64_t value) = 0;
};
} // namespace Bitswarm
} // namespace Sfs2X

#endif
