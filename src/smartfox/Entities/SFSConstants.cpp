// ===================================================================
//
// Description		
//		Contains the implementation of SFSConstants
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSConstants.h"

namespace Sfs2X {
namespace Entities {

boost::shared_ptr<std::string> SFSConstants::DEFAULT_GROUP_ID (new std::string("default"));
boost::shared_ptr<std::string> SFSConstants::REQUEST_UDP_PACKET_ID (new std::string("$FS_REQUEST_UDP_TIMESTAMP"));

}	// namespace Entities
}	// namespace Sfs2X
