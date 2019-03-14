// ===================================================================
//
// Description
//        Contains the implementation of InvitationReplyRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "InvitationReplyRequest.h"

namespace Sfs2X {
namespace Requests {
namespace Game {

boost::shared_ptr<std::string>
    InvitationReplyRequest::KEY_INVITATION_ID(new std::string("i"));
boost::shared_ptr<std::string>
    InvitationReplyRequest::KEY_INVITATION_REPLY(new std::string("r"));
boost::shared_ptr<std::string>
    InvitationReplyRequest::KEY_INVITATION_PARAMS(new std::string("p"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
InvitationReplyRequest::InvitationReplyRequest(
    boost::shared_ptr<Sfs2X::Entities::Invitation::Invitation> invitation,
    boost::shared_ptr<InvitationReply> reply)
    : BaseRequest(RequestType_InvitationReply) {
    Init(invitation, reply, boost::shared_ptr<ISFSObject>());
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
InvitationReplyRequest::InvitationReplyRequest(
    boost::shared_ptr<Sfs2X::Entities::Invitation::Invitation> invitation,
    boost::shared_ptr<InvitationReply> reply,
    boost::shared_ptr<ISFSObject> parameters)
    : BaseRequest(RequestType_InvitationReply) {
    Init(invitation, reply, parameters);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
InvitationReplyRequest::~InvitationReplyRequest() {}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void InvitationReplyRequest::Init(
    boost::shared_ptr<Sfs2X::Entities::Invitation::Invitation> invitation,
    boost::shared_ptr<InvitationReply> reply,
    boost::shared_ptr<ISFSObject> parameters) {
    this->invitation = invitation;
    this->reply = reply;
    this->parameters = parameters;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void InvitationReplyRequest::Validate(const boost::shared_ptr<SmartFox>& sfs) {
    boost::shared_ptr<list<string>> errors(new list<string>());

    if (invitation == NULL)
        errors->push_back("Missing invitation object");

    if (errors->size() > 0) {
        boost::shared_ptr<std::string> message(
            new std::string("InvitationReply request error"));
        boost::shared_ptr<SFSValidationError> exception(
            new SFSValidationError(message, errors));
        throw exception;
    }
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void InvitationReplyRequest::Execute(const boost::shared_ptr<SmartFox>& sfs) {
    sfso->PutInt(KEY_INVITATION_ID,
                 static_cast<std::int32_t>(invitation->Id()));

    auto valueReply =
        boost::make_shared<unsigned char>((unsigned char)(*reply));
    sfso->PutByte(KEY_INVITATION_REPLY, valueReply);

    if (parameters != NULL)
        sfso->PutSFSObject(KEY_INVITATION_PARAMS, parameters);
}
} // namespace Game
} // namespace Requests
} // namespace Sfs2X
