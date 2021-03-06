// ===================================================================
//
// Description		
//		Contains the implementation of ClientDisconnectionReason
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
// 
// ===================================================================
#include "ClientDisconnectionReason.h"

using namespace std;

namespace Sfs2X {
namespace Util {

boost::shared_ptr<std::string> ClientDisconnectionReason::IDLE (new std::string("idle"));
boost::shared_ptr<std::string> ClientDisconnectionReason::KICK (new std::string("kick")); 
boost::shared_ptr<std::string> ClientDisconnectionReason::BAN (new std::string("ban")); 
boost::shared_ptr<std::string> ClientDisconnectionReason::MANUAL (new std::string("manual")); 
boost::shared_ptr<std::string> ClientDisconnectionReason::UNKNOWN (new std::string("unknown"));

string* ClientDisconnectionReason::reasons[] = 
{
	new std::string("idle"), 
	new std::string("kick"), 
	new std::string("ban")
};

// -------------------------------------------------------------------
// GetReason
// -------------------------------------------------------------------
boost::shared_ptr<std::string> ClientDisconnectionReason::GetReason(long int reasonId)
{
	return boost::shared_ptr<std::string>(new std::string(*(reasons[reasonId])));
}

// -------------------------------------------------------------------
// Dispose
// -------------------------------------------------------------------
void ClientDisconnectionReason::Dispose()
{
	for (long int code = 0; code < NUM_ENTRIES_reasons; code++)
	{
		delete reasons[code];
	}
}

}	// namespace Util
}	// namespace Sfs2X
