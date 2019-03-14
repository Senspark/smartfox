// ===================================================================
//
// Description		
//		Contains the implementation of SubscribeRoomGroupRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SubscribeRoomGroupRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<std::string> SubscribeRoomGroupRequest::KEY_GROUP_ID (new std::string("g"));
boost::shared_ptr<std::string> SubscribeRoomGroupRequest::KEY_ROOM_LIST (new std::string("rl"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SubscribeRoomGroupRequest::SubscribeRoomGroupRequest(const std::string& groupId)
	: BaseRequest (RequestType_SubscribeRoomGroup)
{
	this->groupId = boost::shared_ptr<std::string> (new std::string(groupId));
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SubscribeRoomGroupRequest::~SubscribeRoomGroupRequest()
{
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void SubscribeRoomGroupRequest::Validate(const boost::shared_ptr<SmartFox>& sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	// no validation needed
	if (groupId == NULL || groupId->size() == 0)
		errors->push_back("Invalid groupId. Must be a string with at least 1 character.");

	if (errors->size() > 0)
	{
		boost::shared_ptr<std::string> message (new std::string("SubscribeGroup request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void SubscribeRoomGroupRequest::Execute(const boost::shared_ptr<SmartFox>& sfs)
{
	sfso->PutUtfString(KEY_GROUP_ID, groupId);
}

}	// namespace Requests
}	// namespace Sfs2X


