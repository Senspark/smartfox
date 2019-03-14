// ===================================================================
//
// Description		
//		Contains the implementation of BaseEvent
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "BaseEvent.h"

namespace Sfs2X {
namespace Core {

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
boost::shared_ptr<std::string> BaseEvent::Type()
{
	return type;
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
void BaseEvent::Type(const boost::shared_ptr<std::string>& value)
{
	type = value;
}

// -------------------------------------------------------------------
// Params
// -------------------------------------------------------------------
boost::shared_ptr<map<string, boost::shared_ptr<void> > > BaseEvent::Params()
{
	return arguments;
}

// -------------------------------------------------------------------
// Params
// -------------------------------------------------------------------
void BaseEvent::Params(boost::shared_ptr<map<string, boost::shared_ptr<void> > > value)
{
	arguments = value;
}

// -------------------------------------------------------------------
// Target
// -------------------------------------------------------------------
boost::shared_ptr<void> BaseEvent::Target()
{
	return target;
}

// -------------------------------------------------------------------
// Target
// -------------------------------------------------------------------
void BaseEvent::Target(boost::shared_ptr<void> value)
{
	target = value;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<std::string> BaseEvent::ToString()
{
	boost::shared_ptr<std::string> log;

	if (target == NULL)
	{
		char buffer[100];
		sprintf (buffer, "%s [ null]", type->c_str());

		log = boost::shared_ptr<std::string>(new std::string(buffer));
	}
	else
	{
		char buffer[100];
		sprintf (buffer, "%s [%ld]", type->c_str(), (unsigned long int*)target.get());

		log = boost::shared_ptr<std::string>(new std::string(buffer));
	}

	return log;
}

// -------------------------------------------------------------------
// Clone
// -------------------------------------------------------------------
boost::shared_ptr<BaseEvent> BaseEvent::Clone()
{
	return boost::shared_ptr<BaseEvent>(new BaseEvent(type, arguments));
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BaseEvent::BaseEvent()
{
	type = boost::shared_ptr<std::string>();
	arguments = boost::shared_ptr<map<string, boost::shared_ptr<void> > >();
	target = boost::shared_ptr<void>();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BaseEvent::BaseEvent(const boost::shared_ptr<std::string>& type)
{
	this->target = boost::shared_ptr<void>();
	this->type = type;
	this->arguments = boost::shared_ptr<map<string, boost::shared_ptr<void> > >(new map<string, boost::shared_ptr<void> >());
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BaseEvent::BaseEvent(const boost::shared_ptr<std::string>& type, boost::shared_ptr<map<string, boost::shared_ptr<void> > > args)
{
	this->target = boost::shared_ptr<void>();
	this->type = type;
	arguments = args;
	if (this->arguments == NULL)
	{
		this->arguments = boost::shared_ptr<map<string, boost::shared_ptr<void> > >(new map<string, boost::shared_ptr<void> >());
	}
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
BaseEvent::~BaseEvent()
{
	if (arguments != NULL)
	{
		// Elements contained into arguments are released in derived classes
		// Here we release only the "container" arguments
		arguments->clear();

		arguments = boost::shared_ptr<map<string, boost::shared_ptr<void> > >();
	}
}


}	// namespace Core
}	// namespace Sfs2X
