// ===================================================================
//
// Description		
//		Contains the implementation of SFSBuddyEvent
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSBuddyEvent.h"

namespace Sfs2X {
namespace Core {

boost::shared_ptr<std::string> SFSBuddyEvent::BUDDY_LIST_INIT (new std::string("buddyListInit"));
boost::shared_ptr<std::string> SFSBuddyEvent::BUDDY_ADD (new std::string("buddyAdd"));
boost::shared_ptr<std::string> SFSBuddyEvent::BUDDY_REMOVE (new std::string("buddyRemove"));
boost::shared_ptr<std::string> SFSBuddyEvent::BUDDY_BLOCK (new std::string("buddyBlock"));
boost::shared_ptr<std::string> SFSBuddyEvent::BUDDY_ERROR (new std::string("buddyError"));
boost::shared_ptr<std::string> SFSBuddyEvent::BUDDY_ONLINE_STATE_UPDATE (new std::string("buddyOnlineStateChange"));
boost::shared_ptr<std::string> SFSBuddyEvent::BUDDY_VARIABLES_UPDATE (new std::string("buddyVariablesUpdate"));
boost::shared_ptr<std::string> SFSBuddyEvent::BUDDY_MESSAGE (new std::string("buddyMessage"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSBuddyEvent::SFSBuddyEvent(const boost::shared_ptr<std::string>& type)
	: BaseEvent (type, boost::shared_ptr<map<string, boost::shared_ptr<void> > >())
{
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSBuddyEvent::SFSBuddyEvent(const boost::shared_ptr<std::string>& type, boost::shared_ptr<map<string, boost::shared_ptr<void> > > args)
	: BaseEvent (type, args)
{
}

}	// namespace Core
}	// namespace Sfs2X

