// ===================================================================
//
// Description
//        Contains the definition of BBClient
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __BBClient__
#define __BBClient__

// Forward class declaration
namespace Sfs2X {
namespace Bitswarm {
namespace BBox {
class BBClient;
} // namespace BBox
} // namespace Bitswarm
} // namespace Sfs2X

#include "../../Http/SFSWebClient.h"
#include "../../Core/IDispatchable.h"
#include "../../Util/ByteArray.h"
#include "../../Logging/Logger.h"
#include "../BitSwarmClient.h"

#include <boost/asio/deadline_timer.hpp>     // Boost Asio header
#include <boost/shared_ptr.hpp>              // Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp> // Boost shared_ptr for this

namespace Sfs2X {
using namespace Core;
using namespace Util;
using namespace Logging;
using namespace Http;

namespace Bitswarm {
namespace BBox {

// -------------------------------------------------------------------
// Class BBClient
// -------------------------------------------------------------------
class BBClient : public boost::enable_shared_from_this<BBClient> {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------
    void Initialize();
    void Dispose();

    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // Getters / Setters
    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    BBClient(boost::shared_ptr<BitSwarmClient> bs);

    bool IsConnected();

    bool IsDebug();

    void IsDebug(bool value);

    boost::shared_ptr<std::string> Host();

    std::uint16_t Port();

    boost::shared_ptr<std::string> SessionId();

    int PollSpeed();

    void PollSpeed(int value);

    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // Public methods
    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    void Connect(const boost::shared_ptr<std::string>& host,
                 std::uint16_t port);

    void Send(boost::shared_ptr<ByteArray> binData);

    void Close();

    void AddEventListener(const boost::shared_ptr<std::string>& eventType,
                          boost::shared_ptr<EventListenerDelegate> listener);

    boost::shared_ptr<EventDispatcher> Dispatcher();

    void DispatchEvent(const boost::shared_ptr<BaseEvent>& evt);

    // ------------------------------------------------------------------
    // Public members
    // -------------------------------------------------------------------
    static boost::shared_ptr<std::string> BB_SERVLET;

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
    static void OnHttpResponse(unsigned long long context, bool error,
                               boost::shared_ptr<std::string> response);

    void Poll(const boost::system::error_code& code);
    void SendRequest(const boost::shared_ptr<std::string>& cmd);
    void SendRequest(const boost::shared_ptr<std::string>& cmd,
                     boost::shared_ptr<void> data);
    boost::shared_ptr<SFSWebClient> GetWebClient();
    void HandleConnectionLost(bool fireEvent);
    boost::shared_ptr<std::string>
    UrlEncode(const boost::shared_ptr<std::string>& data);
    boost::shared_ptr<std::string>
    UrlDecode(const boost::shared_ptr<std::string>& data);
    bool isXdigit(char c);

    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // Message Codec
    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    boost::shared_ptr<std::string>
    EncodeRequest(const boost::shared_ptr<std::string>& cmd);

    boost::shared_ptr<std::string>
    EncodeRequest(const boost::shared_ptr<std::string>& cmd,
                  boost::shared_ptr<void> data);

    boost::shared_ptr<ByteArray>
    DecodeResponse(const boost::shared_ptr<std::string>& rawData);

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------

    static boost::shared_ptr<std::string> BB_DEFAULT_HOST;
    const static unsigned short int BB_DEFAULT_PORT = 8080;
    static boost::shared_ptr<std::string> BB_NULL;

    static boost::shared_ptr<std::string> CMD_CONNECT;
    static boost::shared_ptr<std::string> CMD_POLL;
    static boost::shared_ptr<std::string> CMD_DATA;
    static boost::shared_ptr<std::string> CMD_DISCONNECT;
    static boost::shared_ptr<std::string> ERR_INVALID_SESSION;

    static boost::shared_ptr<std::string> SFS_HTTP;

    static constexpr int MIN_POLL_SPEED = 50;
    // ms
    static constexpr int MAX_POLL_SPEED = 5000;
    // ms
    static constexpr int DEFAULT_POLL_SPEED = 300;
    // ms

    bool isConnected;
    boost::shared_ptr<std::string> host;
    std::uint16_t port;
    boost::shared_ptr<std::string> bbUrl;
    bool debug;
    boost::shared_ptr<std::string> sessId;
    int pollSpeed;

    boost::shared_ptr<EventDispatcher> dispatcher;

    boost::shared_ptr<Logger> log;

    boost::shared_ptr<boost::asio::deadline_timer>
        pollTimer; // Boost Asio deadline timer
    boost::shared_ptr<boost::asio::io_service> boostService;
    boost::shared_ptr<boost::asio::io_service> io_service_pollTimer;
};
} // namespace BBox
} // namespace Bitswarm
} // namespace Sfs2X

#endif
