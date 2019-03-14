// ===================================================================
//
// Description		
//		Contains the implementation of StringMatch
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "StringMatch.h"

namespace Sfs2X {
namespace Entities {
namespace Match {

const long int StringMatch::TYPE_ID = 2;
boost::shared_ptr<StringMatch> StringMatch::EQUALS (new StringMatch(boost::shared_ptr<std::string>(new std::string("=="))));
boost::shared_ptr<StringMatch> StringMatch::NOT_EQUALS (new StringMatch(boost::shared_ptr<std::string>(new std::string("!="))));
boost::shared_ptr<StringMatch> StringMatch::CONTAINS (new StringMatch(boost::shared_ptr<std::string>(new std::string("contains"))));
boost::shared_ptr<StringMatch> StringMatch::STARTS_WITH (new StringMatch(boost::shared_ptr<std::string>(new std::string("startsWith"))));
boost::shared_ptr<StringMatch> StringMatch::ENDS_WITH (new StringMatch(boost::shared_ptr<std::string>(new std::string("endsWith"))));
		
// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
StringMatch::StringMatch(const boost::shared_ptr<std::string>& symbol)
{
	this->symbol = symbol;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
StringMatch::StringMatch(const std::string& symbol)
{
	this->symbol = boost::shared_ptr<std::string>(new std::string(symbol));
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
StringMatch::~StringMatch()
{
	// delete symbol;			Do not delete because it is a static string (one-time allocated string)
}

// -------------------------------------------------------------------
// Symbol
// -------------------------------------------------------------------
boost::shared_ptr<std::string> StringMatch::Symbol()
{
	return symbol;
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
long int StringMatch::Type()
{
	return TYPE_ID;
}


}	// namespace Match
}	// namespace Entities
}	// namespace Sfs2X


