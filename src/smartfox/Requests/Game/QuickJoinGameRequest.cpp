// ===================================================================
//
// Description
//        Contains the implementation of QuickJoinGameRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "QuickJoinGameRequest.h"

namespace Sfs2X {
namespace Requests {
namespace Game {

const long int QuickJoinGameRequest::MAX_ROOMS = 32;
boost::shared_ptr<std::string>
    QuickJoinGameRequest::KEY_ROOM_LIST(new std::string("rl"));
boost::shared_ptr<std::string>
    QuickJoinGameRequest::KEY_GROUP_LIST(new std::string("gl"));
boost::shared_ptr<std::string>
    QuickJoinGameRequest::KEY_ROOM_TO_LEAVE(new std::string("tl"));
boost::shared_ptr<std::string>
    QuickJoinGameRequest::KEY_MATCH_EXPRESSION(new std::string("me"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
QuickJoinGameRequest::QuickJoinGameRequest(
    boost::shared_ptr<MatchExpression> matchExpression,
    boost::shared_ptr<std::vector<std::string>> whereToSearch)
    : BaseRequest(RequestType_QuickJoinGame) {
    this->isSearchListString = false;
    this->isSearchListRoom = false;
    Init(matchExpression, whereToSearch, boost::shared_ptr<Room>());
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
QuickJoinGameRequest::QuickJoinGameRequest(
    boost::shared_ptr<MatchExpression> matchExpression,
    boost::shared_ptr<std::vector<std::string>> whereToSearch,
    boost::shared_ptr<Room> roomToLeave)
    : BaseRequest(RequestType_QuickJoinGame) {
    this->isSearchListString = false;
    this->isSearchListRoom = false;
    Init(matchExpression, whereToSearch, roomToLeave);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
QuickJoinGameRequest::QuickJoinGameRequest(
    boost::shared_ptr<MatchExpression> matchExpression,
    boost::shared_ptr<std::vector<boost::shared_ptr<Room>>> whereToSearch)
    : BaseRequest(RequestType_QuickJoinGame) {
    this->isSearchListString = false;
    this->isSearchListRoom = false;
    Init(matchExpression, whereToSearch, boost::shared_ptr<Room>());
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
QuickJoinGameRequest::QuickJoinGameRequest(
    boost::shared_ptr<MatchExpression> matchExpression,
    boost::shared_ptr<std::vector<boost::shared_ptr<Room>>> whereToSearch,
    boost::shared_ptr<Room> roomToLeave)
    : BaseRequest(RequestType_QuickJoinGame) {
    this->isSearchListString = false;
    this->isSearchListRoom = false;
    Init(matchExpression, whereToSearch, roomToLeave);
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
QuickJoinGameRequest::~QuickJoinGameRequest() {
    if (whereToSearchString != NULL) {
        whereToSearchString->clear();
        whereToSearchString = boost::shared_ptr<std::vector<std::string>>();
    }

    if (whereToSearchRoom != NULL) {
        whereToSearchRoom->clear();
        whereToSearchRoom =
            boost::shared_ptr<std::vector<boost::shared_ptr<Room>>>();
    }
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void QuickJoinGameRequest::Init(
    boost::shared_ptr<MatchExpression> matchExpression,
    boost::shared_ptr<std::vector<std::string>> whereToSearch,
    boost::shared_ptr<Room> roomToLeave) {
    this->matchExpression = matchExpression;
    this->whereToSearchString = whereToSearch;
    this->roomToLeave = roomToLeave;

    isSearchListString = true;
}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void QuickJoinGameRequest::Init(
    boost::shared_ptr<MatchExpression> matchExpression,
    boost::shared_ptr<std::vector<boost::shared_ptr<Room>>> whereToSearch,
    boost::shared_ptr<Room> roomToLeave) {
    this->matchExpression = matchExpression;
    this->whereToSearchRoom = whereToSearch;
    this->roomToLeave = roomToLeave;

    isSearchListRoom = true;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void QuickJoinGameRequest::Validate(const boost::shared_ptr<SmartFox>& sfs) {
    boost::shared_ptr<list<string>> errors(new list<string>());

    // NOTE: match expression can be null, in which case the first Room found is
    // going to be good
    if (isSearchListRoom) {
        if (whereToSearchRoom == NULL || whereToSearchRoom->size() < 1)
            errors->push_back("Missing whereToSearch parameter");

        else if (whereToSearchRoom->size() > MAX_ROOMS) {
            char buffer[512];
            sprintf(buffer,
                    "Too many Rooms specified in the whereToSearch parameter. "
                    "Client limit is: %ld",
                    MAX_ROOMS);
            string str = buffer;

            errors->push_back(str);
        }
    }
    if (isSearchListString) {
        if (whereToSearchString == NULL || whereToSearchString->size() < 1)
            errors->push_back("Missing whereToSearch parameter");

        else if (whereToSearchString->size() > MAX_ROOMS) {
            char buffer[512];
            sprintf(buffer,
                    "Too many Rooms specified in the whereToSearch parameter. "
                    "Client limit is: %ld",
                    MAX_ROOMS);
            string str = buffer;

            errors->push_back(str);
        }
    }

    if (errors->size() > 0) {
        boost::shared_ptr<std::string> message(
            new std::string("QuickJoinGame request error"));
        boost::shared_ptr<SFSValidationError> exception(
            new SFSValidationError(message, errors));
        throw exception;
    }
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void QuickJoinGameRequest::Execute(const boost::shared_ptr<SmartFox>& sfs) {
    // Auto detect whereToSearch types --->> string, GroupId
    if (isSearchListString)
        sfso->PutUtfStringArray(KEY_GROUP_LIST, whereToSearchString);

    // --->> Room
    else if (isSearchListRoom) {
        auto roomIds = boost::make_shared<std::vector<int>>();

        vector<boost::shared_ptr<Room>>::iterator iteratorRooms;
        for (iteratorRooms = whereToSearchRoom->begin();
             iteratorRooms != whereToSearchRoom->end(); iteratorRooms++) {
            roomIds->push_back((*iteratorRooms)->Id());
        }

        sfso->PutIntArray(KEY_ROOM_LIST, roomIds);
    }

    if (roomToLeave != NULL) {
        sfso->PutInt(KEY_ROOM_TO_LEAVE,
                     static_cast<std::int32_t>(roomToLeave->Id()));
    }

    if (matchExpression != NULL) {
        sfso->PutSFSArray(KEY_MATCH_EXPRESSION, matchExpression->ToSFSArray());
    }
}

} // namespace Game
} // namespace Requests
} // namespace Sfs2X
