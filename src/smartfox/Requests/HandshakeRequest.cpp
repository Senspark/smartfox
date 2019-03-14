// ===================================================================
//
// Description
//        Contains the implementation of HandshakeRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "HandshakeRequest.h"

namespace Sfs2X {
namespace Requests {
using Self = HandshakeRequest;

boost::shared_ptr<std::string> Self::KEY_SESSION_TOKEN(new std::string("tk"));
boost::shared_ptr<std::string> Self::KEY_API(new std::string("api"));
boost::shared_ptr<std::string>
    Self::KEY_COMPRESSION_THRESHOLD(new std::string("ct"));
boost::shared_ptr<std::string>
    Self::KEY_RECONNECTION_TOKEN(new std::string("rt"));
boost::shared_ptr<std::string> Self::KEY_CLIENT_TYPE(new std::string("cl"));
boost::shared_ptr<std::string>
    Self::KEY_MAX_MESSAGE_SIZE(new std::string("ms"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::HandshakeRequest(const std::string& apiVersion,
                       const std::string& reconnectionToken,
                       const std::string& clientDetails)
    : BaseRequest(RequestType_Handshake) {
    sfso->PutUtfString(KEY_API, boost::make_shared<std::string>(apiVersion));
    sfso->PutUtfString(KEY_CLIENT_TYPE,
                       boost::make_shared<std::string>(clientDetails));

    sfso->PutBool("bin", boost::make_shared<bool>(true));

    // send reconnection token, if any
    if (reconnectionToken.size() > 0) {
        sfso->PutUtfString(KEY_RECONNECTION_TOKEN,
                           boost::make_shared<std::string>(reconnectionToken));
    }
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
Self::~HandshakeRequest() {}
} // namespace Requests
} // namespace Sfs2X
