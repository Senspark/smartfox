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
#define BOOST_THREAD_USES_MOVE

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/remove_whitespace.hpp>
#include <boost/asio/ssl.hpp>
#include "CryptoInitializer.h"
#include "CryptoKey.h"
#include "../Core/Sockets/TCPClientSSL.h" // SSL TCP client handler

using namespace boost::archive::iterators;

namespace Sfs2X {
namespace Util {
using Self = CryptoInitializer;

boost::shared_ptr<std::string>
    Self::KEY_SESSION_TOKEN(new std::string("SessToken"));
boost::shared_ptr<std::string>
    Self::TARGET_SERVLET(new std::string("BlueBox/CryptoManager"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::CryptoInitializer(const boost::shared_ptr<SmartFox>& sfs) {
    this->useHttps = true;
    this->key.reset();
    this->errorMessage = nullptr;

    // These are not events because they should fail at test time
    if (!sfs->IsConnected())
        boost::throw_exception(boost::enable_error_info(
            std::runtime_error("Cryptography cannot be initialized before "
                               "connecting to SmartFoxServer!")));

    if (sfs->GetSocketEngine()->CryptoKey() != NULL)
        boost::throw_exception(boost::enable_error_info(
            std::runtime_error("Cryptography is already initialized!")));

    this->sfs = sfs;
}

// -------------------------------------------------------------------
// Run
// -------------------------------------------------------------------
void Self::Run() {
    RunHelper();
}

// -------------------------------------------------------------------
// RunHelper
// -------------------------------------------------------------------
void Self::RunHelper() {
    // To grant linux compatibility, below statements have been replaced with
    // RunHelperSSLAsync/RunHelperAsync methods that return a bool instead of
    // the key session string The new implementation of
    // RunHelperSSLAsync/RunHelperAsync store key session in a local member (see
    // key member)
    /*
    boost::future<boost::shared_ptr<std::string> > f =
    boost::async(boost::bind((useHttps ? &CryptoInitializer::RunHelperSSLAsync :
    &CryptoInitializer::RunHelperAsync), this));

    // Wait for asynch compution of RunHelperAsync, then process returned value
    as http response OnHttpResponse(f.get());
    */

    boost::future<bool> f = boost::async(
        boost::launch::async,
        boost::bind((useHttps ? &CryptoInitializer::RunHelperSSLAsync
                              : &CryptoInitializer::RunHelperAsync),
                    this));

    bool result = f.get();

    if (result && !errorMessage) {
        // Wait for asynch compution of RunHelperAsync, then process returned
        // value as http response
        OnHttpResponse(this->key);
    } else {
        if (errorMessage) {
            OnHttpError(errorMessage);
        } else {
            OnHttpError(boost::make_shared<std::string>(
                "Error retrieving crypto key from SFS2X"));
        }
    }
}

// -------------------------------------------------------------------
// RunHelperAsync
// -------------------------------------------------------------------
bool Self::RunHelperAsync() {
    bool returned = false;
    auto client = boost::shared_ptr<TCPClient>();

    try {
        client = boost::make_shared<TCPClient>(*sfs->GetBoostService());

        auto address = boost::make_shared<IPAddress>(*sfs->GetIPAddress(
            sfs->Config()->Host(), (useHttps ? sfs->Config()->HttpsPort()
                                             : sfs->Config()->HttpPort())));

        client->SynchConnect(address, (useHttps ? sfs->Config()->HttpsPort()
                                                : sfs->Config()->HttpPort()));
    } catch (const std::exception& e) {
        this->errorMessage = boost::make_shared<std::string>(
            "Http error creating http connection: " + std::string(e.what()));

        try {
            client->Shutdown();
        } catch (const std::exception& e) {
            this->errorMessage = boost::make_shared<std::string>(
                "Error during http scocket shutdown: " + std::string(e.what()));
        }

        return returned;
    }

    try {
        string data = (*KEY_SESSION_TOKEN) + "=" + (*sfs->SessionToken());

        auto dataAsNative = boost::make_shared<std::wstring>();
        dataAsNative->assign(data.begin(), data.end());

        auto dataAsUtf8 = boost::make_shared<std::string>();
        WStrToUtf8(dataAsNative, dataAsUtf8);

        std::string sb;
        sb.append("POST /" + (*CryptoInitializer::TARGET_SERVLET) +
                  " HTTP/1.0\r\n");
        sb.append("Content-Type: application/x-www-form-urlencoded; "
                  "charset=utf-8\r\n");
        sb.append(
            StringFormatter("Content-Length: %zu\r\n", dataAsUtf8->size()));
        sb.append("\r\n");
        sb.append(data);

        auto outputData =
            boost::make_shared<std::vector<std::uint8_t>>(sb.begin(), sb.end());
        outputData->push_back('\0');

        client->SynchWrite(outputData);

        std::string responseFromServer;
        do {
            auto receive = client->SynchRead();
            if (receive->size() == 0) {
                break;
            }

            auto src = boost::make_shared<std::string>(receive->begin(),
                                                       receive->end());
            auto dest = boost::make_shared<std::wstring>();
            Utf8toWStr(src, dest);

            responseFromServer.append(dest->begin(), dest->end());
        } while (true);

        // Remove http header and trim whitespaces at the end
        std::vector<std::string> parts;

        const char* chunkCurrent = responseFromServer.c_str();
        const char* chunkNext = chunkCurrent;

        while ((chunkNext = std::strstr(chunkCurrent, "\r\n\r\n")) != nullptr) {
            std::string tokenizedValue(chunkCurrent, chunkNext - chunkCurrent);
            parts.push_back(tokenizedValue);
            chunkCurrent = chunkNext + 4;
        }

        std::string tokenizedValueLast(chunkCurrent);
        if (tokenizedValueLast.length() > 0) {
            parts.push_back(tokenizedValueLast);
        }

        if ((responseFromServer.size() > 4) &&
            (responseFromServer.compare(responseFromServer.size() - 4, 4,
                                        "\r\n\r\n") == 0)) {
            parts.push_back("");
        }

        if (parts.size() < 2) {
            this->errorMessage = boost::make_shared<std::string>(
                "Error during http response: connection closed by remote side");
            return returned;
        }

        string charsToTrim = " ";
        string dataPayload =
            parts[1].substr(0, parts[1].find_last_not_of(charsToTrim) + 1);

        this->key = boost::make_shared<std::string>(dataPayload);
        returned = true;
    } catch (const std::exception& e) {
        this->errorMessage = boost::make_shared<std::string>(
            "Error during http request: " + std::string(e.what()));
    }

    try {
        client->Shutdown();
    } catch (const std::exception& e) {
        this->errorMessage = boost::make_shared<std::string>(
            "Error during http scocket shutdown: " + std::string(e.what()));
    }

    return returned;
}

// -------------------------------------------------------------------
// RunHelperSSLAsync
// -------------------------------------------------------------------
bool CryptoInitializer::RunHelperSSLAsync() {
    bool returned = false;
    auto client = boost::shared_ptr<TCPClientSSL>();

    try {
        // Create a context that uses the default paths for
        // finding CA certificates.
        boost::asio::ssl::context contextSSL(boost::asio::ssl::context::sslv23);
        contextSSL.set_default_verify_paths();
        // contextSSL.load_verify_file("ca.pem");

        client = boost::make_shared<TCPClientSSL>(*sfs->GetBoostService(),
                                                  contextSSL);

        auto address = boost::make_shared<IPAddress>(*sfs->GetIPAddress(
            sfs->Config()->Host(), (useHttps ? sfs->Config()->HttpsPort()
                                             : sfs->Config()->HttpPort())));

        client->SynchConnect(address, (useHttps ? sfs->Config()->HttpsPort()
                                                : sfs->Config()->HttpPort()));
    } catch (const std::exception& e) {
        boost::shared_ptr<std::string> messageException(
            new std::string(e.what()));
        boost::shared_ptr<std::string> message(new std::string(
            "Http error creating http connection: " + (*messageException)));

        this->errorMessage = message;

        try {
            client->Shutdown();
        } catch (exception e) {
            boost::shared_ptr<std::string> messageException(
                new std::string(e.what()));
            boost::shared_ptr<std::string> message(new std::string(
                "Error during http scocket shutdown: " + (*messageException)));

            this->errorMessage = message;
        }

        return returned;
    }

    try {
        string data = (*KEY_SESSION_TOKEN) + "=" + (*sfs->SessionToken());

        boost::shared_ptr<wstring> dataAsNative(new wstring());
        dataAsNative->assign(data.begin(), data.end());

        boost::shared_ptr<std::string> dataAsUtf8(new std::string());
        WStrToUtf8(dataAsNative, dataAsUtf8);

        std::string sb;
        sb.append("POST /" + (*CryptoInitializer::TARGET_SERVLET) +
                  " HTTP/1.0\r\n");
        sb.append("Content-Type: application/x-www-form-urlencoded; "
                  "charset=utf-8\r\n");
        sb.append(StringFormatter("Content-Length: %ld\r\n",
                                  (long int)dataAsUtf8->size()));
        sb.append("\r\n");
        sb.append(data);

        auto outputData =
            boost::make_shared<std::vector<std::uint8_t>>(sb.begin(), sb.end());
        outputData->push_back('\0');

        client->SynchWrite(outputData);

        string responseFromServer;
        do {
            auto receive = client->SynchRead();
            if (receive->size() == 0) {
                break;
            }

            auto src = boost::make_shared<std::string>(receive->begin(),
                                                       receive->end());
            auto dest = boost::make_shared<std::wstring>();
            Utf8toWStr(src, dest);

            responseFromServer.append(dest->begin(), dest->end());
        } while (true);

        // Remove http header and trim whitespaces at the end
        std::vector<std::string> parts;

        const char* chunkCurrent = responseFromServer.c_str();
        const char* chunkNext = chunkCurrent;

        while ((chunkNext = strstr(chunkCurrent, "\r\n\r\n")) != NULL) {
            string tokenizedValue(chunkCurrent, chunkNext - chunkCurrent);
            parts.push_back(tokenizedValue);
            chunkCurrent = chunkNext + 4;
        }

        string tokenizedValueLast(chunkCurrent);
        if (tokenizedValueLast.length() > 0) {
            parts.push_back(tokenizedValueLast);
        }

        if ((responseFromServer.size() > 4) &&
            (responseFromServer.compare(responseFromServer.size() - 4, 4,
                                        "\r\n\r\n") == 0)) {
            parts.push_back("");
        }

        if (parts.size() < 2) {
            this->errorMessage = boost::shared_ptr<std::string>(
                new string("Error during http response: connection closed by "
                           "remote side"));
            return returned;
        }

        string charsToTrim = " ";
        string dataPayload =
            parts[1].substr(0, parts[1].find_last_not_of(charsToTrim) + 1);

        this->key =
            boost::shared_ptr<std::string>(new std::string(dataPayload));
        returned = true;
    } catch (const std::exception& e) {
        boost::shared_ptr<std::string> messageException(
            new std::string(e.what()));
        boost::shared_ptr<std::string> message(new std::string(
            "Error during http request: " + (*messageException)));

        this->errorMessage = message;
    }

    try {
        client->Shutdown();
    } catch (const std::exception& e) {
        boost::shared_ptr<std::string> messageException(
            new std::string(e.what()));
        boost::shared_ptr<std::string> message(new std::string(
            "Error during http scocket shutdown: " + (*messageException)));

        this->errorMessage = message;
    }

    return returned;
}

// -------------------------------------------------------------------
// OnHttpResponse
// -------------------------------------------------------------------
void CryptoInitializer::OnHttpResponse(
    const boost::shared_ptr<std::string>& rawData) {
    auto byteData = DecodeResponse(rawData);
    auto key = boost::make_shared<ByteArray>();
    auto iv = boost::make_shared<ByteArray>();

    // Extract the key and init vector and pass them to the BitSwarmClient
    auto keyValues = boost::make_shared<std::vector<std::uint8_t>>();
    byteData->Position(0);
    byteData->ReadBytes(0, 16, *keyValues.get());
    key->WriteBytes(keyValues);

    auto ivValues = boost::make_shared<std::vector<std::uint8_t>>();
    byteData->Position(0);
    byteData->ReadBytes(16, 16, *ivValues.get());
    iv->WriteBytes(ivValues);

    auto cryptoKey = boost::make_shared<CryptoKey>(iv, key);
    sfs->GetSocketEngine()->CryptoKey(cryptoKey);

    auto evtParams =
        boost::make_shared<std::map<std::string, boost::shared_ptr<void>>>();
    evtParams->emplace("success", boost::make_shared<bool>(true));

    auto evt = boost::make_shared<SFSEvent>(SFSEvent::CRYPTO_INIT, evtParams);
    sfs->DispatchEvent(evt);
}

// -------------------------------------------------------------------
// OnHttpError
// -------------------------------------------------------------------
void CryptoInitializer::OnHttpError(
    const boost::shared_ptr<std::string>& errorMsg) {
    auto evtParams =
        boost::make_shared<std::map<std::string, boost::shared_ptr<void>>>();
    evtParams->emplace("success", boost::make_shared<bool>(false));
    evtParams->emplace("errorMessage", errorMsg);
    auto evt = boost::make_shared<SFSEvent>(SFSEvent::CRYPTO_INIT, evtParams);
    sfs->DispatchEvent(evt);
}

// -------------------------------------------------------------------
// DecodeResponse
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> CryptoInitializer::DecodeResponse(
    const boost::shared_ptr<std::string>& rawData) {
    typedef transform_width<
        binary_from_base64<remove_whitespace<string::const_iterator>>, 8, 6>
        base64_decoder;

    unsigned int paddChars =
        (unsigned int)count(rawData->begin(), rawData->end(), '=');
    std::replace(rawData->begin(), rawData->end(), '=',
                 'A'); // replace '=' by base64 encoding of '\0'
    string result(base64_decoder(rawData->begin()),
                  base64_decoder(rawData->end())); // decode
    result.erase(result.end() - paddChars,
                 result.end()); // erase padding '\0' characters

    auto data = boost::make_shared<std::vector<std::uint8_t>>(result.begin(),
                                                              result.end());
    return boost::make_shared<ByteArray>(data);
}
} // namespace Util
} // namespace Sfs2X
