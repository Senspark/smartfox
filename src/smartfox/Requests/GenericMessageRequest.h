// ===================================================================
//
// Description
//        Contains the definition of GenericMessageRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __GenericMessageRequest__
#define __GenericMessageRequest__

#include "../Util/Common.h"
#include "BaseRequest.h"
#include "GenericMessageType.h"
#include "MessageRecipientMode.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object
#include <list>   // STL library: list object

namespace Sfs2X {
using namespace Entities::Data;
using namespace Exceptions;

namespace Requests {
// -------------------------------------------------------------------
// Class GenericMessageRequest
// -------------------------------------------------------------------
class DLLImportExport GenericMessageRequest : public BaseRequest {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------
    GenericMessageRequest();
    virtual ~GenericMessageRequest() override;

    /*
     * NOTE:
     * Validation is performed by the specific Message class, e.g.
     * PublicMessageRequest, PrivateMessageRequest, SendObjectRequest
     */
    virtual void Validate(const boost::shared_ptr<SmartFox>& sfs) override;
    virtual void Execute(const boost::shared_ptr<SmartFox>& sfs) override;

    // -------------------------------------------------------------------
    // Public members
    // -------------------------------------------------------------------

    static boost::shared_ptr<std::string> KEY_ROOM_ID; // The room id

    static boost::shared_ptr<std::string>
        KEY_USER_ID; // The sender ( ???????????????????????? )

    static boost::shared_ptr<std::string> KEY_MESSAGE; // The actual message

    static boost::shared_ptr<std::string> KEY_MESSAGE_TYPE; // The message type

    static boost::shared_ptr<std::string>
        KEY_RECIPIENT; // The recipient (for sendObject and sendPrivateMessage)

    static boost::shared_ptr<std::string> KEY_RECIPIENT_MODE; // For admin/mod
                                                         // messages, indicate
                                                         // toUser, toRoom,
                                                         // toGroup, toZone

    static boost::shared_ptr<std::string>
        KEY_XTRA_PARAMS; // Extra custom parameters (mandatory for sendObject)

    static boost::shared_ptr<std::string>
        KEY_SENDER_DATA; // The sender User data (when cross room message)

protected:
    // -------------------------------------------------------------------
    // Protected methods
    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    // Protected members
    // -------------------------------------------------------------------
    int type;
    boost::shared_ptr<Room> room;
    boost::shared_ptr<User> user;
    boost::shared_ptr<std::string> message;
    boost::shared_ptr<ISFSObject> parameters;
    boost::shared_ptr<User> recipientUser;
    boost::shared_ptr<Room> recipientRoom;
    boost::shared_ptr<std::string> recipientString;
    boost::shared_ptr<int> recipientInt;
    boost::shared_ptr<std::vector<boost::shared_ptr<User>>> recipientUsersCollection;
    int sendMode;

private:
    // -------------------------------------------------------------------
    // Private methods
    // -------------------------------------------------------------------

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // Specialized validators
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    void ValidatePublicMessage(boost::shared_ptr<SmartFox> sfs,
                               boost::shared_ptr<list<string>> errors);
    void ValidatePrivateMessage(boost::shared_ptr<SmartFox> sfs,
                                boost::shared_ptr<list<string>> errors);
    void ValidateObjectMessage(boost::shared_ptr<SmartFox> sfs,
                               boost::shared_ptr<list<string>> errors);
    void ValidateBuddyMessage(boost::shared_ptr<SmartFox> sfs,
                              boost::shared_ptr<list<string>> errors);
    void ValidateSuperUserMessage(boost::shared_ptr<SmartFox> sfs,
                                  boost::shared_ptr<list<string>> errors);

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // Specialized executors
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    void ExecutePublicMessage(boost::shared_ptr<SmartFox> sfs);
    void ExecutePrivateMessage(boost::shared_ptr<SmartFox> sfs);
    void ExecuteBuddyMessage(boost::shared_ptr<SmartFox> sfs);
    void ExecuteSuperUserMessage(boost::shared_ptr<SmartFox> sfs);
    void ExecuteObjectMessage(boost::shared_ptr<SmartFox> sfs);

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------
};
} // namespace Requests
} // namespace Sfs2X

#endif
