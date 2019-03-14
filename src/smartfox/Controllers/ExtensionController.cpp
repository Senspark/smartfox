// ===================================================================
//
// Description
//        Contains the implementation of ExtensionController
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================

#include <cinttypes>

#include "ExtensionController.h"

namespace Sfs2X {
namespace Controllers {
boost::shared_ptr<std::string>
    ExtensionController::KEY_CMD(new std::string("c"));

boost::shared_ptr<std::string>
    ExtensionController::KEY_PARAMS(new std::string("p"));

boost::shared_ptr<std::string>
    ExtensionController::KEY_ROOM(new std::string("r"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ExtensionController::ExtensionController(
    const boost::shared_ptr<BitSwarmClient>& bitSwarm)
    : BaseController(bitSwarm) {}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ExtensionController::~ExtensionController() {}

// -------------------------------------------------------------------
// HandleMessage
// -------------------------------------------------------------------
void ExtensionController::HandleMessage(
    const boost::shared_ptr<IMessage>& message) {
    if (sfs->Debug()) {
        auto logMessage = StringFormatter("Message: %" PRId32, message->Id());
        auto logMessages = boost::make_shared<std::vector<std::string>>();
        logMessages->push_back(logMessage);
        log->Info(logMessages);
    }

    auto obj = message->Content();
    auto evtParams =
        boost::make_shared<std::map<std::string, boost::shared_ptr<void>>>();

    auto cmd = obj->GetUtfString(*KEY_CMD);
    evtParams->emplace("cmd", cmd);

    auto params = obj->GetSFSObject(*KEY_PARAMS);
    evtParams->emplace("params", params);

    if (obj->ContainsKey(*KEY_ROOM)) {
        auto roomId = *(obj->GetInt(*KEY_ROOM));

        auto sourceRoom = boost::make_shared<std::int32_t>(roomId);
        evtParams->emplace("sourceRoom", sourceRoom); // Deprecated!

        auto room = sfs->GetRoomById(roomId);
        evtParams->emplace("room", room);
    }

    if (message->IsUDP()) {
        auto packetId = boost::make_shared<std::int64_t>(message->PacketId());
        evtParams->emplace("packetId", packetId);
    }

    auto evt =
        boost::make_shared<SFSEvent>(SFSEvent::EXTENSION_RESPONSE, evtParams);
    sfs->DispatchEvent(evt);
}
} // namespace Controllers
} // namespace Sfs2X
