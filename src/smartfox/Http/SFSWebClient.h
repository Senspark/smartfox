// ===================================================================
//
// Description
//        Contains the definition of SFSWebClient
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __SFSWebClient__
#define __SFSWebClient__

// Forward class declaration
namespace Sfs2X {
namespace Http {
class SFSWebClient;
} // namespace Http
} // namespace Sfs2XBitswarm

#include "smartfox/Bitswarm/BBox/BBClient.h"
#include "smartfox/Util/DelegateTwoArguments.h" // Delegate with two parameters

#include <boost/asio.hpp>       // Boost Asio header
#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object
#include <vector> // STL library: vector object

using boost::asio::ip::tcp; // Boost Asio namespace

namespace Sfs2X {
using namespace Bitswarm::BBox;
using namespace Util;

namespace Http {
typedef DelegateTwoArguments<bool, boost::shared_ptr<std::string>>
    HttpResponseDelegate;

// -------------------------------------------------------------------
// Class SFSWebClient
// -------------------------------------------------------------------
class SFSWebClient {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------
    SFSWebClient(boost::asio::io_service& io_service);
    ~SFSWebClient();

    void UploadValuesAsync(const boost::shared_ptr<std::string>& uriHost,
                           std::uint16_t uriPort,
                           boost::shared_ptr<std::string> paramName,
                           boost::shared_ptr<std::string> encodedData);

    boost::shared_ptr<HttpResponseDelegate> OnHttpResponse();
    void OnHttpResponse(boost::shared_ptr<HttpResponseDelegate> onHttpResponse);

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
    boost::asio::io_service& boostIoService; // Boost Asio IO service
    boost::shared_ptr<HttpResponseDelegate> onHttpResponse;
};
} // namespace Http
} // namespace Sfs2X

#endif
