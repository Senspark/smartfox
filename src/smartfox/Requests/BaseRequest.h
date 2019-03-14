// ===================================================================
//
// Description
//        Contains the definition of BaseRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __BaseRequest__
#define __BaseRequest__

// Forward class declaration
namespace Sfs2X {
namespace Requests {
class BaseRequest;
} // namespace Requests
} // namespace Sfs2X

#include "IRequest.h"
#include "RequestType.h"
#include "../Util/Common.h"
#include "../Entities/Data/ISFSObject.h"
#include "../Entities/Data/SFSObject.h"
#include "../Bitswarm/Message.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object

namespace Sfs2X {
using namespace Bitswarm;
using namespace Logging;
using namespace Entities::Data;

namespace Requests {
// -------------------------------------------------------------------
// Class BaseRequest
// -------------------------------------------------------------------
class DLLImportExport BaseRequest : public IRequest {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    BaseRequest();
    explicit BaseRequest(RequestType tp);
    explicit BaseRequest(int id);

    virtual ~BaseRequest() override;

    int Id() const;
    void Id(int value);

    RequestType Type() const;
    void Type(RequestType value);

    // IRequest implementation

    virtual void Validate(const boost::shared_ptr<SmartFox>& sfs) override;
    virtual void Execute(const boost::shared_ptr<SmartFox>& sfs) override;

    virtual int TargetController() const override;
    virtual void TargetController(int value) override;

    virtual bool IsEncrypted() const override;
    virtual void IsEncrypted(bool value) override;

    virtual boost::shared_ptr<IMessage> Message() const override;

    // -------------------------------------------------------------------
    // Public members
    // -------------------------------------------------------------------

    static boost::shared_ptr<std::string> KEY_ERROR_CODE;
    static boost::shared_ptr<std::string> KEY_ERROR_PARAMS;

protected:
    // -------------------------------------------------------------------
    // Protected methods
    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    // Protected members
    // -------------------------------------------------------------------

    boost::shared_ptr<ISFSObject> sfso;
    int targetController;

private:
    // -------------------------------------------------------------------
    // Private methods
    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------

    int id;
    bool isEncrypted;
};
} // namespace Requests
} // namespace Sfs2X

#endif
