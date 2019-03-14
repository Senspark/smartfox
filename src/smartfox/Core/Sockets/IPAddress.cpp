// ===================================================================
//
// Description		
//		Contains the implementation for the IP address entity
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "IPAddress.h"

namespace Sfs2X {
namespace Core {
namespace Sockets {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
IPAddress::IPAddress(const std::string& address)
{
	// Preserve input parameters into class members
	this->address = boost::shared_ptr<std::string>(new std::string(address));
}

// -------------------------------------------------------------------
// Address
// -------------------------------------------------------------------
boost::shared_ptr<std::string> IPAddress::Address()
{
	// Return the ip address value
	return address; 
}

}	// namespace Sockets
}	// namespace Core
}	// namespace Sfs2X
