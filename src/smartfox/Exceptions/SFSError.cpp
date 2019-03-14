// ===================================================================
//
// Description
//        Contains the definition of SFSError
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================

#include "SFSError.h"

#include <boost/make_shared.hpp>

namespace Sfs2X {
namespace Exceptions {
SFSError::SFSError(const std::string& message)
    : SFSError(boost::make_shared<std::string>(message)) {}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSError::SFSError(const boost::shared_ptr<std::string>& message) {
    this->message = message;
}
} // namespace Exceptions
} // namespace Sfs2X
