// ===================================================================
//
// Description		
//		Contains the implementation of SetMMOItemVariables
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#include "SetMMOItemVariables.h"

namespace Sfs2X {
namespace Requests {
namespace MMO {

boost::shared_ptr<std::string> SetMMOItemVariables::KEY_ROOM_ID (new std::string("r"));
boost::shared_ptr<std::string> SetMMOItemVariables::KEY_ITEM_ID (new std::string("i"));
boost::shared_ptr<std::string> SetMMOItemVariables::KEY_VAR_LIST (new std::string("v"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SetMMOItemVariables::SetMMOItemVariables()
{
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SetMMOItemVariables::~SetMMOItemVariables()
{
}

}	// namespace MMO
}	// namespace Requests
}	// namespace Sfs2X


