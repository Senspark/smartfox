// ===================================================================
//
// Description
//        Contains the definition of IRequest interface
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __IRequest__
#define __IRequest__

namespace Sfs2X {
namespace Requests {
class IRequest;
} // namespace Requests
} // namespace Sfs2X

#include "../Util/Common.h"
#include "../Bitswarm/IMessage.h"
#include "../SmartFox.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

namespace Sfs2X {
using namespace Bitswarm;

namespace Requests {
class DLLImportExport IRequest {
public:
    virtual ~IRequest() = default;

    virtual void Validate(const boost::shared_ptr<SmartFox>& sfs) = 0;
    virtual void Execute(const boost::shared_ptr<SmartFox>& sfs) = 0;

    virtual int TargetController() const = 0;
    virtual void TargetController(int value) = 0;

    virtual bool IsEncrypted() const = 0;
    virtual void IsEncrypted(bool value) = 0;

    virtual boost::shared_ptr<IMessage> Message() const = 0;
};
} // namespace Requests
} // namespace Sfs2X

#endif
