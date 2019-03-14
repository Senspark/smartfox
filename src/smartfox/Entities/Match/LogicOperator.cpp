// ===================================================================
//
// Description
//        Contains the implementation of LogicOperator
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "LogicOperator.h"

#include <boost/make_shared.hpp>

namespace Sfs2X {
namespace Entities {
namespace Match {
using Self = LogicOperator;

boost::shared_ptr<Self>
    Self::AND(new Self(boost::make_shared<std::string>("AND")));

boost::shared_ptr<Self>
    Self::OR(new Self(boost::make_shared<std::string>("OR")));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::LogicOperator(const boost::shared_ptr<std::string>& id) {
    this->id = id;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::LogicOperator(const std::string& id) {
    this->id = boost::shared_ptr<std::string>(new std::string(id));
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
boost::shared_ptr<std::string> Self::Id() {
    return id;
}
} // namespace Match
} // namespace Entities
} // namespace Sfs2X
