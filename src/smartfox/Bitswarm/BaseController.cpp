// ===================================================================
//
// Description
//        Contains the implementation of BaseController
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================

#include <cinttypes>

#include "BaseController.h"

namespace Sfs2X {
namespace Bitswarm {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BaseController::BaseController() {
    id = -1;
    sfs = nullptr;
    bitSwarm = nullptr;
    log = nullptr;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BaseController::BaseController(
    const boost::shared_ptr<BitSwarmClient>& bitSwarm) {
    id = -1;
    sfs = boost::shared_ptr<SmartFox>();
    this->bitSwarm = bitSwarm;
    log = boost::shared_ptr<Logger>();

    if (bitSwarm != NULL) {
        log = bitSwarm->Log();
        sfs = bitSwarm->Sfs();
    }
}

// -------------------------------------------------------------------
// Dispose
// -------------------------------------------------------------------
void BaseController::Dispose() {
    this->bitSwarm.reset();
    this->sfs.reset();
    this->log.reset();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
BaseController::~BaseController() {}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
int BaseController::Id() const {
    return id;
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
void BaseController::Id(int value) {
    if (id == -1) {
        id = value;
    } else {
        char buffer[512];
        std::sprintf(buffer,
                     "Controller ID is already set: %" PRId32
                     ". Can't be changed at runtime!",
                     id);

        auto message = boost::make_shared<std::string>(buffer);
        auto exception = boost::make_shared< SFSError>(message);
        throw exception;
    }
}
} // namespace Bitswarm
} // namespace Sfs2X
