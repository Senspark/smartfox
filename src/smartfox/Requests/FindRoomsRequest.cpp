// ===================================================================
//
// Description		
//		Contains the implementation of FindRoomsRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "FindRoomsRequest.h"

namespace Sfs2X {
namespace Requests {

boost::shared_ptr<std::string> FindRoomsRequest::KEY_EXPRESSION (new std::string("e"));
boost::shared_ptr<std::string> FindRoomsRequest::KEY_GROUP (new std::string("g"));
boost::shared_ptr<std::string> FindRoomsRequest::KEY_LIMIT (new std::string("l"));
boost::shared_ptr<std::string> FindRoomsRequest::KEY_FILTERED_ROOMS (new std::string("fr"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
FindRoomsRequest::FindRoomsRequest(boost::shared_ptr<MatchExpression> expr)
	: BaseRequest (RequestType_FindRooms)
{
	Init(expr, "", 0);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
FindRoomsRequest::FindRoomsRequest(boost::shared_ptr<MatchExpression> expr, const std::string& groupId)
	: BaseRequest (RequestType_FindRooms)
{
	Init(expr, groupId, 0);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
FindRoomsRequest::FindRoomsRequest(boost::shared_ptr<MatchExpression> expr, const std::string& groupId, long int limit)
	: BaseRequest (RequestType_FindRooms)
{
	Init(expr, groupId, limit);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
FindRoomsRequest::~FindRoomsRequest()
{
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void FindRoomsRequest::Init(boost::shared_ptr<MatchExpression> expr, const std::string& groupId, long int limit)
{
	this->matchExpr = expr;
	this->groupId = boost::shared_ptr<std::string>(new std::string(groupId));
	this->limit = limit;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void FindRoomsRequest::Validate(const boost::shared_ptr<SmartFox>& sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());
			
	if (matchExpr == NULL)
		errors->push_back("Missing Match Expression");

	if (errors->size() > 0)
	{
		boost::shared_ptr<std::string> message (new std::string("FindRooms request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void FindRoomsRequest::Execute(const boost::shared_ptr<SmartFox>& sfs)
{
	sfso->PutSFSArray(KEY_EXPRESSION, matchExpr->ToSFSArray());
			
	if (groupId != NULL)
		sfso->PutUtfString(KEY_GROUP, groupId);
				
	// 2^15 is already too many Rooms :)
	if (limit > 0)
	{
		boost::shared_ptr<short int> valueLimit (new short int());
		*valueLimit = (short int)limit;
		sfso->PutShort(KEY_LIMIT, valueLimit);
	}
}

}	// namespace Requests
}	// namespace Sfs2X


