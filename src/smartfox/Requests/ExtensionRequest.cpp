// ===================================================================
//
// Description
//        Contains the implementation of ExtensionRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "ExtensionRequest.h"

namespace Sfs2X {
namespace Requests {
using Self = ExtensionRequest;

boost::shared_ptr<std::string> Self::KEY_CMD(new std::string("c"));
boost::shared_ptr<std::string> Self::KEY_PARAMS(new std::string("p"));
boost::shared_ptr<std::string> Self::KEY_ROOM(new std::string("r"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::ExtensionRequest(const std::string& extCmd,
                       const boost::shared_ptr<ISFSObject>& parameters,
                       const boost::shared_ptr<Room>& room, bool useUDP)
    : BaseRequest(RequestType_CallExtension) {
    Init(extCmd, parameters, room, useUDP);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::ExtensionRequest(const std::string& extCmd,
                       const boost::shared_ptr<ISFSObject>& parameters,
                       const boost::shared_ptr<Room>& room)
    : BaseRequest(RequestType_CallExtension) {
    Init(extCmd, parameters, room, false);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::ExtensionRequest(const std::string& extCmd,
                       const boost::shared_ptr<ISFSObject>& parameters)
    : BaseRequest(RequestType_CallExtension) {
    Init(extCmd, parameters, boost::shared_ptr<Room>(), false);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
Self::~ExtensionRequest() {}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void Self::Init(const std::string& extCmd,
                const boost::shared_ptr<ISFSObject>& parameters,
                const boost::shared_ptr<Room>& room, bool useUDP) {
    targetController = 1;

    this->extCmd = boost::shared_ptr<std::string>(new std::string(extCmd));
    this->parameters = parameters;
    this->room = room;
    this->useUDP = useUDP;

    // New since 0.9.6
    if (parameters == NULL)
        this->parameters = boost::shared_ptr<ISFSObject>(new SFSObject());
}

// -------------------------------------------------------------------
// UseUDP
// -------------------------------------------------------------------
bool Self::UseUDP() const {
    return useUDP;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void Self::Validate(const boost::shared_ptr<SmartFox>& sfs) {
    boost::shared_ptr<list<string>> errors(new list<string>());

    if (extCmd == NULL || extCmd->size() == 0)
        errors->push_back("Missing extension command");

    if (parameters == NULL)
        errors->push_back("Missing extension parameters");

    if (errors->size() > 0) {
        boost::shared_ptr<std::string> message(
            new std::string("ExtensionCall request error"));
        boost::shared_ptr<SFSValidationError> exception(
            new SFSValidationError(message, errors));
        throw exception;
    }
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void ExtensionRequest::Execute(const boost::shared_ptr<SmartFox>& sfs) {
    sfso->PutUtfString(KEY_CMD, extCmd);
    sfso->PutInt(KEY_ROOM,
                 static_cast<std::int32_t>(room == nullptr ? -1 : room->Id()));
    sfso->PutSFSObject(KEY_PARAMS, parameters);
}
} // namespace Requests
} // namespace Sfs2X
