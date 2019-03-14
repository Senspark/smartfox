// ===================================================================
//
// Description		
//		Contains the implementation of RoomExtension
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "RoomExtension.h"

namespace Sfs2X {
namespace Requests {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
RoomExtension::RoomExtension(const std::string& id, const std::string& className)
{
	this->id = boost::shared_ptr<std::string>(new std::string(id));
	this->className = boost::shared_ptr<std::string>(new std::string(className));
	this->propertiesFile = boost::shared_ptr<std::string>();
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
boost::shared_ptr<std::string> RoomExtension::Id()
{
	return this->id;
}

// -------------------------------------------------------------------
// ClassName
// -------------------------------------------------------------------
boost::shared_ptr<std::string> RoomExtension::ClassName()
{
	return this->className;
}

// -------------------------------------------------------------------
// PropertiesFile
// -------------------------------------------------------------------
boost::shared_ptr<std::string> RoomExtension::PropertiesFile()
{
	return this->propertiesFile;
}

// -------------------------------------------------------------------
// PropertiesFile
// -------------------------------------------------------------------
void RoomExtension::PropertiesFile(const std::string& value)
{
	this->propertiesFile = boost::shared_ptr<std::string>(new std::string(value));
}

}	// namespace Requests
}	// namespace Sfs2X

