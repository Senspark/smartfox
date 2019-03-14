// ===================================================================
//
// Description
//        Contains the implementation of Message
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================

#include <cinttypes>

#include "Message.h"

#include <boost/make_shared.hpp>

namespace Sfs2X {
namespace Bitswarm {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Message::Message() {
    id = 0;
    content = nullptr;
    targetController = 0;
    isEncrypted = false;
    isUDP = false;
    packetId = 0;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
Message::~Message() {}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
int Message::Id() const {
    return id;
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
void Message::Id(int value) {
    id = value;
}

// -------------------------------------------------------------------
// Content
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> Message::Content() const {
    return content;
}

// -------------------------------------------------------------------
// Content
// -------------------------------------------------------------------
void Message::Content(const boost::shared_ptr<ISFSObject>& value) {
    content = value;
}

// -------------------------------------------------------------------
// TargetController
// -------------------------------------------------------------------
int Message::TargetController() const {
    return targetController;
}

// -------------------------------------------------------------------
// TargetController
// -------------------------------------------------------------------
void Message::TargetController(int value) {
    targetController = value;
}

// -------------------------------------------------------------------
// IsEncrypted
// -------------------------------------------------------------------
bool Message::IsEncrypted() const {
    return isEncrypted;
}

// -------------------------------------------------------------------
// IsEncrypted
// -------------------------------------------------------------------
void Message::IsEncrypted(bool value) {
    isEncrypted = value;
}

// -------------------------------------------------------------------
// IsUDP
// -------------------------------------------------------------------
bool Message::IsUDP() const {
    return isUDP;
}

// -------------------------------------------------------------------
// IsUDP
// -------------------------------------------------------------------
void Message::IsUDP(bool value) {
    isUDP = value;
}

// -------------------------------------------------------------------
// PacketId
// -------------------------------------------------------------------
std::int64_t Message::PacketId() const {
    return packetId;
}

// -------------------------------------------------------------------
// PacketId
// -------------------------------------------------------------------
void Message::PacketId(std::int64_t value) {
    packetId = value;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<std::string> Message::ToString() const {
    char buffer[512];
    sprintf(buffer, "{ Message id: " PRId32 " }\n", id);

    auto str = boost::make_shared<std::string>(buffer);
    str->append("{ Dump: }\n");
    str->append(*(content->GetDump()));

    return str;
}
} // namespace Bitswarm
} // namespace Sfs2X
