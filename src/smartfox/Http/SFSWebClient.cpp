// ===================================================================
//
// Description
//        Contains the implementation of SFSWebClient
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "SFSWebClient.h"
#include <cstring>
//#include <boost/regex.hpp>

namespace Sfs2X {
namespace Http {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSWebClient::SFSWebClient(boost::asio::io_service& io_service)
    : boostIoService(io_service) {
    onHttpResponse = boost::shared_ptr<HttpResponseDelegate>();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSWebClient::~SFSWebClient() {}

// -------------------------------------------------------------------
// UploadValuesAsync
// -------------------------------------------------------------------
void SFSWebClient::UploadValuesAsync(const boost::shared_ptr<std::string>& uriHost,
                                     std::uint16_t uriPort,
                                     boost::shared_ptr<std::string> paramName,
                                     boost::shared_ptr<std::string> encodedData) {
    boost::shared_ptr<TCPClient> client = boost::shared_ptr<TCPClient>();

    try {
        client = boost::shared_ptr<TCPClient>(new TCPClient(boostIoService));

        boost::shared_ptr<IPAddress> address(new IPAddress(*uriHost));
        client->SynchConnect(address, uriPort);
    } catch (exception e) {
        boost::shared_ptr<std::string> messageException(new std::string(e.what()));
        boost::shared_ptr<std::string> message(new std::string(
            "Http error creating http connection: " + (*messageException)));

        OnHttpResponse()->Invoke(true, message);

        try {
            client->Shutdown();
        } catch (exception e) {
            boost::shared_ptr<std::string> messageException(new std::string(e.what()));
            boost::shared_ptr<std::string> message(new std::string(
                "Error during http scocket shutdown: " + (*messageException)));

            OnHttpResponse()->Invoke(true, message);
        }

        return;
    }

    try {
        string data = (*paramName) + "=" + (*encodedData);

        boost::shared_ptr<wstring> dataAsNative(new wstring());
        dataAsNative->assign(data.begin(), data.end());

        boost::shared_ptr<std::string> dataAsUtf8(new std::string());
        WStrToUtf8(dataAsNative, dataAsUtf8);

        string sb;
        sb.append("POST /" + (*BBClient::BB_SERVLET) + " HTTP/1.0\r\n");
        sb.append("Content-Type: application/x-www-form-urlencoded; "
                  "charset=utf-8\r\n");

        auto valueContentLength =
            StringFormatter("Content-Length: %zu\r\n", dataAsUtf8->size());

        sb.append(valueContentLength);
        sb.append("\r\n");
        sb.append(data);

        boost::shared_ptr<std::vector<unsigned char>> outputData(
            new vector<unsigned char>(sb.begin(), sb.end()));
        outputData->push_back('\0');

        client->SynchWrite(outputData);

        string responseFromServer;
        do {
            boost::shared_ptr<std::vector<unsigned char>> receive =
                client->SynchRead();
            if (receive->size() == 0) {
                break;
            }

            boost::shared_ptr<std::string> src(
                new std::string(receive->begin(), receive->end()));
            boost::shared_ptr<wstring> dest(new wstring());
            Utf8toWStr(src, dest);

            responseFromServer.append(dest->begin(), dest->end());

        } while (true);

        // Remove http header and trim whitespaces at the end
        std::vector<string> parts;

        /*
        boost::regex re("\\r\\n\\r\\n");
        boost::sregex_token_iterator i(responseFromServer.begin(),
        responseFromServer.end(), re, -1); boost::sregex_token_iterator j;

        while (i != j)
        {
            parts.push_back(*i++);
        }
        */

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
            OnHttpResponse()->Invoke(
                true, boost::shared_ptr<std::string>(
                          new std::string("Error during http response: connection "
                                     "closed by remote side")));
            return;
        }

        string charsToTrim = " ";
        string dataPayload =
            parts[1].substr(0, parts[1].find_last_not_of(charsToTrim) + 1);

        // Sending to the higher layer
        boost::shared_ptr<std::string> payload(new std::string(dataPayload));
        OnHttpResponse()->Invoke(false, payload);
    } catch (exception e) {
        boost::shared_ptr<std::string> messageException(new std::string(e.what()));
        boost::shared_ptr<std::string> message(
            new std::string("Error during http request: " + (*messageException)));

        OnHttpResponse()->Invoke(true, message);
    }

    try {
        client->Shutdown();
    } catch (exception e) {
        boost::shared_ptr<std::string> messageException(new std::string(e.what()));
        boost::shared_ptr<std::string> message(new std::string(
            "Error during http scocket shutdown: " + (*messageException)));

        // OnHttpResponse()->Invoke(true,  message);
    }
}

// -------------------------------------------------------------------
// OnHttpResponse
// -------------------------------------------------------------------
boost::shared_ptr<HttpResponseDelegate> SFSWebClient::OnHttpResponse() {
    return onHttpResponse;
}

// -------------------------------------------------------------------
// OnHttpResponse
// -------------------------------------------------------------------
void SFSWebClient::OnHttpResponse(
    boost::shared_ptr<HttpResponseDelegate> onHttpResponse) {
    this->onHttpResponse = onHttpResponse;
}

} // namespace Http
} // namespace Sfs2X
