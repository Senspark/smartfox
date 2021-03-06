// ===================================================================
//
// Description		
//		Contains the definition of BBEvent
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __BBEvent__
#define __BBEvent__

#include "../../Core/BaseEvent.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

using namespace Sfs2X::Core;

namespace Sfs2X {
namespace Bitswarm {
namespace BBox {

	// -------------------------------------------------------------------
	// Class BBEvent
	// -------------------------------------------------------------------
	class BBEvent : public BaseEvent
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		BBEvent(const boost::shared_ptr<std::string>& type);
		BBEvent(const boost::shared_ptr<std::string>& type, boost::shared_ptr<map<string, boost::shared_ptr<void> > > arguments);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		
		static boost::shared_ptr<std::string> CONNECT;
		static boost::shared_ptr<std::string> DISCONNECT;
		static boost::shared_ptr<std::string> DATA;
		static boost::shared_ptr<std::string> IO_ERROR;
		static boost::shared_ptr<std::string> SECURITY_ERROR;

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
	};

}	// namespace BBox
}	// namespace Bitswarm
}	// namespace Sfs2X

#endif
