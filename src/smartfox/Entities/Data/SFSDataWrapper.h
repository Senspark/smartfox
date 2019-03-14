// ===================================================================
//
// Description
//        Contains the definition of SFSDataWrapper
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __SFSDataWrapper__
#define __SFSDataWrapper__

#include "SFSDataType.h"
#include "../../Util/Common.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object
#include <map>    // STL library: map object
#include <vector> // STL library: vector object

namespace Sfs2X {
namespace Entities {
namespace Data {

/// <summary>
/// A wrapper object used by SFSObject and SFSArray to encapsulate data and
/// relative types
/// </summary>
class DLLImportExport SFSDataWrapper {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    explicit SFSDataWrapper(int type, const boost::shared_ptr<void>& data);
    explicit SFSDataWrapper(SFSDataType tp,
                            const boost::shared_ptr<void>& data);

    ~SFSDataWrapper();

    int Type() const;
    const boost::shared_ptr<void>& Data() const;

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

    int type;
    boost::shared_ptr<void> data;
};
} // namespace Data
} // namespace Entities
} // namespace Sfs2X

#endif
