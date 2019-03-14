// ===================================================================
//
// Description		
//		Contains the implementation of SFSEvent
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSEvent.h"

using namespace Sfs2X::Core;

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <map>							// STL library: map object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Core {

boost::shared_ptr<std::string> SFSEvent::HANDSHAKE (new std::string("handshake"));
boost::shared_ptr<std::string> SFSEvent::UDP_INIT (new std::string("udpInit"));
boost::shared_ptr<std::string> SFSEvent::CONNECTION (new std::string("connection"));
boost::shared_ptr<std::string> SFSEvent::PING_PONG (new std::string("pingPong"));
boost::shared_ptr<std::string> SFSEvent::SFS_SOCKET_ERROR (new std::string("socketError"));
boost::shared_ptr<std::string> SFSEvent::CONNECTION_LOST (new std::string("connectionLost"));
boost::shared_ptr<std::string> SFSEvent::CONNECTION_RETRY (new std::string("connectionRetry"));
boost::shared_ptr<std::string> SFSEvent::CONNECTION_RESUME (new std::string("connectionResume"));
boost::shared_ptr<std::string> SFSEvent::CONNECTION_ATTEMPT_HTTP (new std::string("connectionAttemptHttp"));
boost::shared_ptr<std::string> SFSEvent::CONFIG_LOAD_SUCCESS (new std::string("configLoadSuccess"));
boost::shared_ptr<std::string> SFSEvent::CONFIG_LOAD_FAILURE (new std::string("configLoadFailure"));
boost::shared_ptr<std::string> SFSEvent::LOGIN (new std::string("login"));
boost::shared_ptr<std::string> SFSEvent::LOGIN_ERROR (new std::string("loginError"));
boost::shared_ptr<std::string> SFSEvent::LOGOUT (new std::string("logout"));
boost::shared_ptr<std::string> SFSEvent::ROOM_ADD (new std::string("roomAdd"));
boost::shared_ptr<std::string> SFSEvent::ROOM_REMOVE (new std::string("roomRemove"));
boost::shared_ptr<std::string> SFSEvent::ROOM_CREATION_ERROR (new std::string("roomCreationError"));
boost::shared_ptr<std::string> SFSEvent::ROOM_JOIN (new std::string("roomJoin"));
boost::shared_ptr<std::string> SFSEvent::ROOM_JOIN_ERROR (new std::string("roomJoinError"));
boost::shared_ptr<std::string> SFSEvent::USER_ENTER_ROOM (new std::string("userEnterRoom"));
boost::shared_ptr<std::string> SFSEvent::USER_EXIT_ROOM (new std::string("userExitRoom"));
boost::shared_ptr<std::string> SFSEvent::USER_COUNT_CHANGE (new std::string("userCountChange"));
boost::shared_ptr<std::string> SFSEvent::PUBLIC_MESSAGE (new std::string("publicMessage"));
boost::shared_ptr<std::string> SFSEvent::PRIVATE_MESSAGE (new std::string("privateMessage"));
boost::shared_ptr<std::string> SFSEvent::MODERATOR_MESSAGE (new std::string("moderatorMessage"));
boost::shared_ptr<std::string> SFSEvent::ADMIN_MESSAGE (new std::string("adminMessage"));
boost::shared_ptr<std::string> SFSEvent::OBJECT_MESSAGE (new std::string("objectMessage"));
boost::shared_ptr<std::string> SFSEvent::EXTENSION_RESPONSE (new std::string("extensionResponse"));
boost::shared_ptr<std::string> SFSEvent::ROOM_VARIABLES_UPDATE (new std::string("roomVariablesUpdate"));
boost::shared_ptr<std::string> SFSEvent::USER_VARIABLES_UPDATE (new std::string("userVariablesUpdate"));
boost::shared_ptr<std::string> SFSEvent::ROOM_GROUP_SUBSCRIBE (new std::string("roomGroupSubscribe"));
boost::shared_ptr<std::string> SFSEvent::ROOM_GROUP_UNSUBSCRIBE (new std::string("roomGroupUnsubscribe"));
boost::shared_ptr<std::string> SFSEvent::ROOM_GROUP_SUBSCRIBE_ERROR (new std::string("roomGroupSubscribeError"));
boost::shared_ptr<std::string> SFSEvent::ROOM_GROUP_UNSUBSCRIBE_ERROR (new std::string("roomGroupUnsubscribeError"));
boost::shared_ptr<std::string> SFSEvent::SPECTATOR_TO_PLAYER (new std::string("spectatorToPlayer"));
boost::shared_ptr<std::string> SFSEvent::PLAYER_TO_SPECTATOR (new std::string("playerToSpectator"));
boost::shared_ptr<std::string> SFSEvent::SPECTATOR_TO_PLAYER_ERROR (new std::string("spectatorToPlayerError"));
boost::shared_ptr<std::string> SFSEvent::PLAYER_TO_SPECTATOR_ERROR (new std::string("playerToSpectatorError"));
boost::shared_ptr<std::string> SFSEvent::ROOM_NAME_CHANGE (new std::string("roomNameChange"));
boost::shared_ptr<std::string> SFSEvent::ROOM_NAME_CHANGE_ERROR (new std::string("roomNameChangeError"));
boost::shared_ptr<std::string> SFSEvent::ROOM_PASSWORD_STATE_CHANGE (new std::string("roomPasswordStateChange"));
boost::shared_ptr<std::string> SFSEvent::ROOM_PASSWORD_STATE_CHANGE_ERROR (new std::string("roomPasswordStateChangeError"));
boost::shared_ptr<std::string> SFSEvent::ROOM_CAPACITY_CHANGE (new std::string("roomCapacityChange"));
boost::shared_ptr<std::string> SFSEvent::ROOM_CAPACITY_CHANGE_ERROR (new std::string("roomCapacityChangeError"));
boost::shared_ptr<std::string> SFSEvent::ROOM_FIND_RESULT (new std::string("roomFindResult"));
boost::shared_ptr<std::string> SFSEvent::USER_FIND_RESULT (new std::string("userFindResult"));
boost::shared_ptr<std::string> SFSEvent::INVITATION (new std::string("invitation"));
boost::shared_ptr<std::string> SFSEvent::INVITATION_REPLY (new std::string("invitationReply"));
boost::shared_ptr<std::string> SFSEvent::INVITATION_REPLY_ERROR (new std::string("invitationReplyError"));
boost::shared_ptr<std::string> SFSEvent::DEBUG_MESSAGE (new std::string("debugMessage"));
boost::shared_ptr<std::string> SFSEvent::PROXIMITY_LIST_UPDATE (new std::string("proximityListUpdate"));
boost::shared_ptr<std::string> SFSEvent::MMOITEM_VARIABLES_UPDATE (new std::string("mmoItemVariablesUpdate"));
boost::shared_ptr<std::string> SFSEvent::CRYPTO_INIT (new std::string("cryptoInit"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSEvent::SFSEvent(const boost::shared_ptr<std::string>& type)
	: BaseEvent (type, boost::shared_ptr<map<string, boost::shared_ptr<void> > >())
{
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSEvent::SFSEvent(const boost::shared_ptr<std::string>& type, boost::shared_ptr<map<string, boost::shared_ptr<void> > > data)
	: BaseEvent (type, data)
{
}

}	// namespace Core
}	// namespace Sfs2X
