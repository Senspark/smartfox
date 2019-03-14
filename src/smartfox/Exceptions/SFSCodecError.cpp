// ===================================================================
//
// Description
//        Contains the implementation of SFSCodecError
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "SFSCodecError.h"

#include <boost/make_shared.hpp>

namespace Sfs2X {
namespace Exceptions {
// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSCodecError::SFSCodecError(const std::string& message)
    : SFSCodecError(boost::make_shared<std::string>(message)) {}

SFSCodecError::SFSCodecError(const boost::shared_ptr<std::string>& message) {
    this->message = message;
}
} // namespace Exceptions
} // namespace Sfs2X
