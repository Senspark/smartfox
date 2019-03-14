// ===================================================================
//
// Description		
//		Contains the implementation of RoomProperties
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "RoomProperties.h"
#include <boost/exception/exception.hpp>
#include <boost/exception/all.hpp>

namespace Sfs2X {
namespace Entities {
namespace Match {

boost::shared_ptr<std::string> RoomProperties::NAME (new std::string("${N}"));
boost::shared_ptr<std::string> RoomProperties::GROUP_ID (new std::string("${G}"));
boost::shared_ptr<std::string> RoomProperties::MAX_USERS (new std::string("${MXU}"));
boost::shared_ptr<std::string> RoomProperties::MAX_SPECTATORS (new std::string("${MXS}"));
boost::shared_ptr<std::string> RoomProperties::USER_COUNT (new std::string("${UC}"));
boost::shared_ptr<std::string> RoomProperties::SPECTATOR_COUNT (new std::string("${SC}"));
boost::shared_ptr<std::string> RoomProperties::IS_GAME (new std::string("${ISG}"));
boost::shared_ptr<std::string> RoomProperties::IS_PRIVATE (new std::string("${ISP}"));
boost::shared_ptr<std::string> RoomProperties::HAS_FREE_PLAYER_SLOTS (new std::string("${HFP}"));
boost::shared_ptr<std::string> RoomProperties::IS_TYPE_SFSGAME (new std::string("${IST}"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
RoomProperties::RoomProperties()
{
	boost::throw_exception(boost::enable_error_info (std::runtime_error("This class cannot be instantiated"))); 
}

}	// namespace Match
}	// namespace Entities
}	// namespace Sfs2X


