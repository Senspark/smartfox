// ===================================================================
//
// Description
//        Contains the implementation of CreateRoomRequest
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "CreateRoomRequest.h"

namespace Sfs2X {
namespace Requests {
using Self = CreateRoomRequest;

boost::shared_ptr<std::string> Self::KEY_ROOM(new std::string("r"));
boost::shared_ptr<std::string> Self::KEY_NAME(new std::string("n"));
boost::shared_ptr<std::string> Self::KEY_PASSWORD(new std::string("p"));
boost::shared_ptr<std::string> Self::KEY_GROUP_ID(new std::string("g"));
boost::shared_ptr<std::string> Self::KEY_ISGAME(new std::string("ig"));
boost::shared_ptr<std::string> Self::KEY_MAXUSERS(new std::string("mu"));
boost::shared_ptr<std::string> Self::KEY_MAXSPECTATORS(new std::string("ms"));
boost::shared_ptr<std::string> Self::KEY_MAXVARS(new std::string("mv"));
boost::shared_ptr<std::string> Self::KEY_ROOMVARS(new std::string("rv"));
boost::shared_ptr<std::string> Self::KEY_PERMISSIONS(new std::string("pm"));
boost::shared_ptr<std::string> Self::KEY_EVENTS(new std::string("ev"));
boost::shared_ptr<std::string> Self::KEY_EXTID(new std::string("xn"));
boost::shared_ptr<std::string> Self::KEY_EXTCLASS(new std::string("xc"));
boost::shared_ptr<std::string> Self::KEY_EXTPROP(new std::string("xp"));
boost::shared_ptr<std::string> Self::KEY_AUTOJOIN(new std::string("aj"));
boost::shared_ptr<std::string> Self::KEY_ROOM_TO_LEAVE(new std::string("rl"));
boost::shared_ptr<std::string>
    Self::KEY_ALLOW_JOIN_INVITATION_BY_OWNER(new std::string("aji"));
boost::shared_ptr<std::string>
    Self::KEY_MMO_DEFAULT_AOI(new std::string("maoi"));
boost::shared_ptr<std::string>
    Self::KEY_MMO_MAP_LOW_LIMIT(new std::string("mllm"));
boost::shared_ptr<std::string>
    Self::KEY_MMO_MAP_HIGH_LIMIT(new std::string("mlhm"));
boost::shared_ptr<std::string>
    Self::KEY_MMO_USER_MAX_LIMBO_SECONDS(new std::string("muls"));
boost::shared_ptr<std::string>
    Self::KEY_MMO_PROXIMITY_UPDATE_MILLIS(new std::string("mpum"));
boost::shared_ptr<std::string>
    Self::KEY_MMO_SEND_ENTRY_POINT(new std::string("msep"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::CreateRoomRequest(boost::shared_ptr<RoomSettings> settings, bool autoJoin,
                        boost::shared_ptr<Room> roomToLeave)
    : BaseRequest(RequestType_CreateRoom) {
    Init(settings, autoJoin, roomToLeave);
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::CreateRoomRequest(boost::shared_ptr<RoomSettings> settings, bool autoJoin)
    : BaseRequest(RequestType_CreateRoom) {
    Init(settings, autoJoin, boost::shared_ptr<Room>());
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Self::CreateRoomRequest(boost::shared_ptr<RoomSettings> settings)
    : BaseRequest(RequestType_CreateRoom) {
    Init(settings, false, boost::shared_ptr<Room>());
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
Self::~CreateRoomRequest() {}

// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------
void Self::Init(boost::shared_ptr<RoomSettings> settings, bool autoJoin,
                boost::shared_ptr<Room> roomToLeave) {
    this->settings = settings;
    this->autoJoin = autoJoin;
    this->roomToLeave = roomToLeave;
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void Self::Validate(const boost::shared_ptr<SmartFox>& sfs) {
    boost::shared_ptr<list<string>> errors(new list<string>());

    if (settings->Name()->empty() || settings->Name()->size() == 0)
        errors->push_back("Missing room name");

    if (settings->MaxUsers() <= 0)
        errors->push_back("maxUsers must be > 0");

    if (settings->Extension() != NULL) {
        if (settings->Extension()->ClassName() == NULL ||
            settings->Extension()->ClassName()->empty() ||
            settings->Extension()->ClassName()->size() == 0)
            errors->push_back("Missing Extension class name");

        if (settings->Extension()->Id() == NULL ||
            settings->Extension()->Id()->empty() ||
            settings->Extension()->Id()->size() == 0)
            errors->push_back("Missing Extension id");
    }

    if (dynamic_cast<MMORoomSettings*>(settings.get()) != NULL) {
        boost::shared_ptr<MMORoomSettings> mmoSettings =
            (boost::static_pointer_cast<MMORoomSettings>(settings));

        if (mmoSettings->DefaultAOI() == NULL)
            errors->push_back("Missing default AOI (area of interest)");

        if (mmoSettings->MapLimits() != NULL &&
            (mmoSettings->MapLimits()->LowerLimit() == NULL ||
             mmoSettings->MapLimits()->HigherLimit() == NULL))
            errors->push_back("Map limits must be both defined");
    }

    if (errors->size() > 0) {
        boost::shared_ptr<std::string> message(
            new std::string("CreateRoom request error"));
        boost::shared_ptr<SFSValidationError> exception(
            new SFSValidationError(message, errors));
        throw exception;
    }
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void Self::Execute(const boost::shared_ptr<SmartFox>& sfs) {
    sfso->PutUtfString(KEY_NAME, settings->Name());
    sfso->PutUtfString(KEY_GROUP_ID, settings->GroupId());
    sfso->PutUtfString(KEY_PASSWORD, settings->Password());

    auto valueIsGame = boost::make_shared<bool>(settings->IsGame());
    sfso->PutBool(KEY_ISGAME, valueIsGame);

    auto valueMaxUsers = boost::make_shared<std::int16_t>(settings->MaxUsers());
    sfso->PutShort(KEY_MAXUSERS, valueMaxUsers);

    auto valueMaxSpectators =
        boost::make_shared<std::int16_t>(settings->MaxSpectators());
    sfso->PutShort(KEY_MAXSPECTATORS, valueMaxSpectators);

    auto valueMaxVariables =
        boost::make_shared<std::int16_t>(settings->MaxVariables());
    sfso->PutShort(KEY_MAXVARS, valueMaxVariables);

    auto valueAllowJoinInvitationByOwner =
        boost::make_shared<bool>(settings->AllowOwnerOnlyInvitation());
    sfso->PutBool(KEY_ALLOW_JOIN_INVITATION_BY_OWNER,
                  valueAllowJoinInvitationByOwner);

    // Handle Room Variables
    if (settings->Variables() != NULL && settings->Variables()->size() > 0) {
        boost::shared_ptr<ISFSArray> roomVars = SFSArray::NewInstance();

        vector<boost::shared_ptr<RoomVariable>>::iterator iterator;
        for (iterator = settings->Variables()->begin();
             iterator != settings->Variables()->end(); iterator++) {
            boost::shared_ptr<RoomVariable> item = (*iterator);
            roomVars->AddSFSArray(item->ToSFSArray());
        }

        sfso->PutSFSArray(KEY_ROOMVARS, roomVars);
    }

    // Handle Permissions
    if (settings->Permissions() != NULL) {
        boost::shared_ptr<std::vector<bool>> sfsPermissions(new vector<bool>());

        sfsPermissions->push_back(settings->Permissions()->AllowNameChange());
        sfsPermissions->push_back(
            settings->Permissions()->AllowPasswordStateChange());
        sfsPermissions->push_back(
            settings->Permissions()->AllowPublicMessages());
        sfsPermissions->push_back(settings->Permissions()->AllowResizing());

        sfso->PutBoolArray(KEY_PERMISSIONS, sfsPermissions);
    }

    // Handle Events
    if (settings->Events() != NULL) {
        boost::shared_ptr<std::vector<bool>> sfsEvents(new vector<bool>());

        sfsEvents->push_back(settings->Events()->AllowUserEnter());
        sfsEvents->push_back(settings->Events()->AllowUserExit());
        sfsEvents->push_back(settings->Events()->AllowUserCountChange());
        sfsEvents->push_back(settings->Events()->AllowUserVariablesUpdate());

        sfso->PutBoolArray(KEY_EVENTS, sfsEvents);
    }

    // Handle Extension data
    if (settings->Extension() != NULL) {
        boost::shared_ptr<std::string> id(
            new std::string(*(settings->Extension()->Id())));
        sfso->PutUtfString(KEY_EXTID, id);

        boost::shared_ptr<std::string> name(
            new std::string(*(settings->Extension()->ClassName())));
        sfso->PutUtfString(KEY_EXTCLASS, name);

        // Send the properties file only if was specified
        if (settings->Extension()->PropertiesFile() != NULL &&
            !settings->Extension()->PropertiesFile()->empty() &&
            settings->Extension()->PropertiesFile()->size() > 0) {
            boost::shared_ptr<std::string> properties(
                new std::string(*(settings->Extension()->PropertiesFile())));
            sfso->PutUtfString(KEY_EXTPROP, properties);
        }
    }

    //--- MMO Rooms
    //------------------------------------------------------------------------
    if (dynamic_cast<MMORoomSettings*>(settings.get()) != NULL) {
        auto mmoSettings =
            (boost::static_pointer_cast<MMORoomSettings>(settings));
        bool useFloats = mmoSettings->DefaultAOI()->IsFloat();

        if (useFloats) {
            auto defaultAOI = mmoSettings->DefaultAOI()->ToFloatArray();
            sfso->PutFloatArray(KEY_MMO_DEFAULT_AOI, defaultAOI);

            if (mmoSettings->MapLimits() != NULL) {
                auto lowerLimit =
                    mmoSettings->MapLimits()->LowerLimit()->ToFloatArray();
                sfso->PutFloatArray(KEY_MMO_MAP_LOW_LIMIT, lowerLimit);

                /* ------------------------ */

                auto higherLimit =
                    mmoSettings->MapLimits()->HigherLimit()->ToFloatArray();
                sfso->PutFloatArray(KEY_MMO_MAP_HIGH_LIMIT, higherLimit);
            }
        } else {
            auto defaultAOI = mmoSettings->DefaultAOI()->ToIntArray();
            sfso->PutIntArray(KEY_MMO_DEFAULT_AOI, defaultAOI);

            if (mmoSettings->MapLimits() != NULL) {
                auto lowerLimit =
                    mmoSettings->MapLimits()->LowerLimit()->ToIntArray();
                sfso->PutIntArray(KEY_MMO_MAP_LOW_LIMIT, lowerLimit);

                /* ------------------------ */

                auto higherLimit =
                    mmoSettings->MapLimits()->HigherLimit()->ToIntArray();
                sfso->PutIntArray(KEY_MMO_MAP_HIGH_LIMIT, higherLimit);
            }
        }

        auto valueUserMaxLimboSeconds = boost::make_shared<std::int16_t>(
            (std::int16_t)mmoSettings->UserMaxLimboSeconds());
        sfso->PutShort(KEY_MMO_USER_MAX_LIMBO_SECONDS,
                       valueUserMaxLimboSeconds);

        auto valueProximityListUpdateMillis = boost::make_shared<std::int16_t>(
            (std::int16_t)mmoSettings->ProximityListUpdateMillis());
        sfso->PutShort(KEY_MMO_PROXIMITY_UPDATE_MILLIS,
                       valueProximityListUpdateMillis);
        sfso->PutBool(KEY_MMO_SEND_ENTRY_POINT,
                      mmoSettings->SendAOIEntryPoint());
    }

    // AutoJoin
    auto valueAutoJoin = boost::make_shared<bool>(autoJoin);
    sfso->PutBool(KEY_AUTOJOIN, valueAutoJoin);

    // Room to leave
    if (roomToLeave != NULL) {
        sfso->PutInt(KEY_ROOM_TO_LEAVE,
                     static_cast<std::int32_t>(roomToLeave->Id()));
    }
}
} // namespace Requests
} // namespace Sfs2X
