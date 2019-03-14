// ===================================================================
//
// Description
//        Contains the definition of Message
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __Message__
#define __Message__

#include "../Entities/Data/ISFSObject.h"
#include "IMessage.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Bitswarm {

// -------------------------------------------------------------------
// Class Message
// -------------------------------------------------------------------
class Message : public IMessage {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    Message();
    virtual ~Message() override;

    virtual int Id() const override;
    virtual void Id(int value) override;

    virtual boost::shared_ptr<ISFSObject> Content() const override;
    virtual void Content(const boost::shared_ptr<ISFSObject>& value) override;

    virtual int TargetController() const override;
    virtual void TargetController(int value) override;

    virtual bool IsEncrypted() const override;
    virtual void IsEncrypted(bool value) override;

    virtual bool IsUDP() const override;
    virtual void IsUDP(bool value) override;

    virtual std::int64_t PacketId() const override;
    virtual void PacketId(std::int64_t value) override;

    boost::shared_ptr<std::string> ToString() const;

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

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------

    int id;
    boost::shared_ptr<ISFSObject> content;
    int targetController;
    bool isEncrypted;
    bool isUDP;
    std::int64_t packetId;
};
} // namespace Bitswarm
} // namespace Sfs2X

#endif
