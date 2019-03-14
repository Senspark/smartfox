// ===================================================================
//
// Description
//        Contains the definition of ISFSDataSerializer interface
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __ISFSDataSerializer__
#define __ISFSDataSerializer__

#include "../../Util/ByteArray.h"
#include "../../Entities/Data/ISFSArray.h"
#include "../../Entities/Data/ISFSObject.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

namespace Sfs2X {
namespace Protocol {
namespace Serialization {
using namespace Sfs2X::Entities::Data;
using namespace Sfs2X::Util;

class ISFSDataSerializer {
public:
    virtual ~ISFSDataSerializer() = default;

    virtual boost::shared_ptr<ByteArray>
    Object2Binary(const boost::shared_ptr<ISFSObject>& obj) const = 0;

    virtual boost::shared_ptr<ByteArray>
    Array2Binary(const boost::shared_ptr<ISFSArray>& array) const = 0;

    virtual boost::shared_ptr<ISFSObject>
    Binary2Object(const boost::shared_ptr<ByteArray>& data) const = 0;

    virtual boost::shared_ptr<ISFSArray>
    Binary2Array(const boost::shared_ptr<ByteArray>& data) const = 0;
};
} // namespace Serialization
} // namespace Protocol
} // namespace Sfs2X

#endif
