// ===================================================================
//
// Description		
//		Contains the implementation of BBEvent
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "BBEvent.h"

namespace Sfs2X {
namespace Bitswarm {
namespace BBox {

boost::shared_ptr<std::string> BBEvent::CONNECT (new std::string("bb-connect"));
boost::shared_ptr<std::string> BBEvent::DISCONNECT (new std::string("bb-disconnect"));
boost::shared_ptr<std::string> BBEvent::DATA (new std::string("bb-data"));
boost::shared_ptr<std::string> BBEvent::IO_ERROR (new std::string("bb-ioError"));
boost::shared_ptr<std::string> BBEvent::SECURITY_ERROR (new std::string("bb-securityError"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BBEvent::BBEvent(const boost::shared_ptr<std::string>& type)
	: BaseEvent (type, boost::shared_ptr<map<string, boost::shared_ptr<void> > >())
{
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BBEvent::BBEvent(const boost::shared_ptr<std::string>& type, boost::shared_ptr<map<string, boost::shared_ptr<void> > > arguments)
	: BaseEvent (type, arguments)
{
}

}	// namespace BBox
}	// namespace Bitswarm
}	// namespace Sfs2X


