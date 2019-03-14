// ===================================================================
//
// Description
//        Contains the definition of UDPManager
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __UDPManager__
#define __UDPManager__

#include "smartfox/Bitswarm/IUDPManager.h"      // IUDPManager interface
#include "smartfox/Core/Sockets/ISocketLayer.h" // ISocketLayer interface
#include "smartfox/SmartFox.h"                  // SmartFox class
#include "smartfox/Logging/Logger.h"            // Logging service
#include "smartfox/Core/IPacketEncrypter.h"

#include <boost/bind.hpp>                    // Boost Asio header
#include <boost/asio.hpp>                    // Boost Asio header
#include <boost/asio/deadline_timer.hpp>     // Boost Asio header
#include <boost/shared_ptr.hpp>              // Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp> // Boost shared_ptr for this

using boost::asio::ip::tcp; // Boost Asio namespace

namespace Sfs2X {
using namespace Logging;

namespace Bitswarm {

// -------------------------------------------------------------------
// Class UDPManager
// -------------------------------------------------------------------
class UDPManager : public IUDPManager,
                   public boost::enable_shared_from_this<UDPManager> {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------
    explicit UDPManager(boost::asio::io_service& io_service,
                        const boost::shared_ptr<SmartFox>& sfs);

    virtual ~UDPManager() override;

    virtual void Dispose() override;

    virtual void Initialize(const std::string& udpAddr,
                            std::uint16_t udpPort) override;
    virtual std::int64_t NextUdpPacketId() override;
    virtual void Send(const boost::shared_ptr<ByteArray>& binaryData) override;
    virtual bool Inited() const override;
    bool isConnected() const;
    virtual void Reset() override;
    virtual void Disconnect() override;

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
    static void OnUDPData(unsigned long long context,
                          boost::shared_ptr<std::vector<std::uint8_t>> bt);
    static void OnUDPError(unsigned long long context,
                           boost::shared_ptr<std::string> msg, SocketErrors se);
    void SendInitializationRequest();
    void OnTimeout(const boost::system::error_code& code);
    void StartTimer();
    void StopTimer();

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------
    boost::shared_ptr<SmartFox> sfs;
    std::int64_t packetId;
    boost::shared_ptr<ISocketLayer> udpSocket;
    bool inited;
    boost::shared_ptr<Logger> log;
    bool locked;
    bool initSuccess;

    // Init transaction variables
    static constexpr int MAX_RETRY = 3; // Retry max 3 times
    static constexpr int RESPONSE_TIMEOUT =
        3000; // Wait response for max 3 seconds

    boost::asio::io_service& boostIoService; // Boost Asio IO service
    boost::asio::deadline_timer initThread;

    int currentAttempt;
    boost::shared_ptr<IPacketEncrypter> packetEncrypter;
};

} // namespace Bitswarm
} // namespace Sfs2X

#endif
