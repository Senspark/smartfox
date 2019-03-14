// ===================================================================
//
// Description		
//		Contains the implementation of ReservedBuddyVariables
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "ReservedBuddyVariables.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {

boost::shared_ptr<std::string> ReservedBuddyVariables::BV_ONLINE (new std::string("$__BV_ONLINE__")); 
boost::shared_ptr<std::string> ReservedBuddyVariables::BV_STATE (new std::string("$__BV_STATE__")); 
boost::shared_ptr<std::string> ReservedBuddyVariables::BV_NICKNAME (new std::string("$__BV_NICKNAME__")); 

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X


