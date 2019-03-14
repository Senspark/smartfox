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
#ifndef __SFSError__
#define __SFSError__

#include <boost/exception/exception.hpp> // Boost exception
#include <boost/shared_ptr.hpp>          // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object

namespace Sfs2X {
namespace Exceptions {
// -------------------------------------------------------------------
// Class SFSError
// -------------------------------------------------------------------
class SFSError : public boost::exception {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    explicit SFSError(const std::string& message);
    explicit SFSError(const boost::shared_ptr<std::string>& message);

    const char* what() { return message.get()->c_str(); }

    const boost::shared_ptr<std::string>& Message() { return message; }

    ~SFSError() throw() {}

    // -------------------------------------------------------------------
    // Public members
    // -------------------------------------------------------------------

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

    boost::shared_ptr<std::string> message;
};
} // namespace Exceptions
} // namespace Sfs2X

#endif
