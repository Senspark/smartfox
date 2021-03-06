// ===================================================================
//
// Description
//        Helper class for crypting
//
// Revision history
//        Date            Description
//        01-May-2015        First version
//
// ===================================================================
#include "CryptoKey.h"

namespace Sfs2X {
namespace Util {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
CryptoKey::CryptoKey(const boost::shared_ptr<ByteArray>& iv,
                     const boost::shared_ptr<ByteArray>& key) {
    this->iv = iv;
    this->key = key;
}

// -------------------------------------------------------------------
// IV
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> CryptoKey::IV() const {
    return iv;
}

// -------------------------------------------------------------------
// Key
// -------------------------------------------------------------------
boost::shared_ptr<ByteArray> CryptoKey::Key() const {
    return key;
}
} // namespace Util
} // namespace Sfs2X
