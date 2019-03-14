// ===================================================================
//
// Description		
//		Contains the implementation of ManualDisconnectionRequest
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "ManualDisconnectionRequest.h"

namespace Sfs2X {
namespace Requests {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
ManualDisconnectionRequest::ManualDisconnectionRequest()
	: BaseRequest (RequestType_ManualDisconnection)
{
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
ManualDisconnectionRequest::~ManualDisconnectionRequest()
{
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void ManualDisconnectionRequest::Validate(const boost::shared_ptr<SmartFox>& sfs)
{
	// Nothing to validate
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void ManualDisconnectionRequest::Execute(const boost::shared_ptr<SmartFox>& sfs)
{
	// No data needed
}

		
}	// namespace Requests
}	// namespace Sfs2X

