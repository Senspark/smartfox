// ===================================================================
//
// Description
//        Helper class for crypting
//
// Revision history
//        Date            Description
//        01-May-2015        First version
//
// ===================================================================
#ifndef __CryptoInitializer__
#define __CryptoInitializer__

#include "./Common.h"
#include "../SmartFox.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object

namespace Sfs2X {
namespace Util {
/// <summary>
/// Initializer for encryption
/// </summary>
class CryptoInitializer {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    CryptoInitializer(const boost::shared_ptr<SmartFox>& sfs);

    /// <summary>
    /// Initialize encryption
    /// </summary>
    void Run();

    // -------------------------------------------------------------------
    // Public members
    // -------------------------------------------------------------------
    static boost::shared_ptr<std::string> KEY_SESSION_TOKEN;
    static boost::shared_ptr<std::string> TARGET_SERVLET;

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
    void RunHelper();
    bool RunHelperAsync();
    bool RunHelperSSLAsync();
    void OnHttpResponse(const boost::shared_ptr<std::string>& rawData);
    void OnHttpError(const boost::shared_ptr<std::string>& errorMsg);

    boost::shared_ptr<ByteArray>
    DecodeResponse(const boost::shared_ptr<std::string>& rawData);

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------
    boost::shared_ptr<SmartFox> sfs;
    boost::shared_ptr<std::string> key; // This is the session key retrieved by
                                        // RunHelperAsync/RunHelperSSLAsync that
                                        // for linux compatibility is stored as
                                        // local variabile instead of returned
                                        // from methods
    boost::shared_ptr<std::string>
        errorMessage; // This is the error string if it exists
    bool useHttps;
};
} // namespace Util
} // namespace Sfs2X

#endif
