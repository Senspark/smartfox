// ===================================================================
//
// Description
//        Contains the definition of ExtensionController
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __ExtensionController__
#define __ExtensionController__

// Forward class declaration
namespace Sfs2X {
namespace Controllers {
class ExtensionController;
} // namespace Controllers
} // namespace Sfs2X

#include "../Bitswarm/BaseController.h"
#include "../Bitswarm/BitSwarmClient.h"
#include "../Bitswarm/IMessage.h"
#include "../Entities/Data/ISFSObject.h"
#include "../Core/SFSEvent.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

namespace Sfs2X {
using namespace Bitswarm;
using namespace Core;
using namespace Entities::Data;

namespace Controllers {

// -------------------------------------------------------------------
// Class ExtensionController
// -------------------------------------------------------------------
class ExtensionController : public BaseController {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    explicit ExtensionController(
        const boost::shared_ptr<BitSwarmClient>& bitSwarm);

    virtual ~ExtensionController() override;

    virtual void
    HandleMessage(const boost::shared_ptr<IMessage>& message) override;

    // -------------------------------------------------------------------
    // Public members
    // -------------------------------------------------------------------

    static boost::shared_ptr<std::string> KEY_CMD;
    static boost::shared_ptr<std::string> KEY_PARAMS;
    static boost::shared_ptr<std::string> KEY_ROOM;

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
};
} // namespace Controllers
} // namespace Sfs2X

#endif
