// ===================================================================
//
// Description
//        Contains the implementation of SFSUserManager
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "SFSUserManager.h"

namespace Sfs2X {
namespace Entities {
namespace Managers {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSUserManager::SFSUserManager(const boost::shared_ptr<SmartFox>& sfs) {
    this->sfs = sfs;
    usersByName =
        boost::make_shared<std::map<std::string, boost::shared_ptr<User>>>();
    usersById =
        boost::make_shared<std::map<int, boost::shared_ptr<User>>>();
    room = nullptr;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSUserManager::SFSUserManager(const boost::shared_ptr<Room>& room) {
    this->sfs = nullptr;
    this->room = room;
    usersByName =
        boost::make_shared<std::map<std::string, boost::shared_ptr<User>>>();
    usersById =
        boost::make_shared<std::map<int, boost::shared_ptr<User>>>();
}

// -------------------------------------------------------------------
// Dispose
// -------------------------------------------------------------------
void SFSUserManager::Dispose() {
    this->sfs = nullptr;

    if (usersByName != nullptr) {
        for (auto iteratorByName = usersByName->begin();
             iteratorByName != usersByName->end(); iteratorByName++) {
            iteratorByName->second.reset();
        }
        usersByName->clear();
        usersByName.reset();
    }

    if (usersById != nullptr) {
        for (auto iteratorById = usersById->begin();
             iteratorById != usersById->end(); iteratorById++) {
            iteratorById->second.reset();
        }
        usersById->clear();
        usersById.reset();
    }
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSUserManager::~SFSUserManager() {}

// -------------------------------------------------------------------
// ContainsUserName
// -------------------------------------------------------------------
bool SFSUserManager::ContainsUserName(const std::string& userName) {
    auto guard = boost::make_lock_guard(lockUsersByName);
    auto iterator = usersByName->find(userName);
    bool returned = iterator == usersByName->end() ? false : true;
    return returned;
}

// -------------------------------------------------------------------
// ContainsUserId
// -------------------------------------------------------------------
bool SFSUserManager::ContainsUserId(int userId) {
    auto guard = boost::make_lock_guard(lockUsersById);
    auto iterator = usersById->find(userId);
    bool returned = iterator == usersById->end() ? false : true;
    return returned;
}

// -------------------------------------------------------------------
// ContainsUser
// -------------------------------------------------------------------
bool SFSUserManager::ContainsUser(const boost::shared_ptr<User>& user) {
    auto guard = boost::make_lock_guard(lockUsersByName);
    for (auto iterator = usersByName->begin(); iterator != usersByName->end();
         iterator++) {
        if (iterator->second == user) {
            return true;
        }
    }
    return false;
}

// -------------------------------------------------------------------
// GetUserByName
// -------------------------------------------------------------------
boost::shared_ptr<User>
SFSUserManager::GetUserByName(const std::string& userName) {
    if (usersByName == NULL)
        return boost::shared_ptr<User>();

    auto guard = boost::make_lock_guard(lockUsersByName);
    auto iterator = usersByName->find(userName);
    boost::shared_ptr<User> user = iterator == usersByName->end()
                                       ? boost::shared_ptr<User>()
                                       : iterator->second;
    return user;
}

// -------------------------------------------------------------------
// GetUserById
// -------------------------------------------------------------------
boost::shared_ptr<User> SFSUserManager::GetUserById(int userId) {
    if (usersById == NULL)
        return boost::shared_ptr<User>();

    auto guard = boost::make_lock_guard(lockUsersById);
    auto iterator = usersById->find(userId);
    boost::shared_ptr<User> user = iterator == usersById->end()
                                       ? boost::shared_ptr<User>()
                                       : iterator->second;
    return user;
}

// -------------------------------------------------------------------
// AddUser
// -------------------------------------------------------------------
void SFSUserManager::AddUser(const boost::shared_ptr<User>& user) {
    lockUsersById.lock();

    // Very defensive, no need to fire exception, however we keep it for
    // debugging
    auto iterator = usersById->find(user->Id());
    if (iterator != usersById->end()) {
        boost::shared_ptr<std::string> message(new std::string(
            "Unexpected: duplicate user in UserManager: " + (*user->Name())));
        LogWarn(message);
    }

    lockUsersById.unlock();
    AddUserInternal(user);
}

// -------------------------------------------------------------------
// RemoveUser
// -------------------------------------------------------------------
void SFSUserManager::RemoveUser(const boost::shared_ptr<User>& user) {
    {
        auto guard = boost::make_lock_guard(lockUsersById);
        auto iteratorById = usersById->find(user->Id());
        if (iteratorById != usersById->end()) {
            usersById->erase(iteratorById);
        }
    }
    {
        auto guard = boost::make_lock_guard(lockUsersByName);
        auto iteratorByName = usersByName->find(*user->Name());
        if (iteratorByName != usersByName->end()) {
            usersByName->erase(iteratorByName);
        }
    }
}

// -------------------------------------------------------------------
// RemoveUserById
// -------------------------------------------------------------------
void SFSUserManager::RemoveUserById(int id) {
    auto guard = boost::make_lock_guard(lockUsersById);
    auto iterator = usersById->find(id);
    if (iterator != usersById->end()) {
        RemoveUser(iterator->second);
    }
}

// -------------------------------------------------------------------
// UserCount
// -------------------------------------------------------------------
std::size_t SFSUserManager::UserCount() {
    return usersById->size();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
boost::shared_ptr<SmartFox> SFSUserManager::SmartFoxClient() {
    return sfs;
}

// -------------------------------------------------------------------
// GetUserList
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<boost::shared_ptr<User>>>
SFSUserManager::GetUserList() {
    auto guard = boost::make_lock_guard(lockUsersById);
    auto result = boost::make_shared<std::vector<boost::shared_ptr<User>>>();
    for (auto iterator = usersById->begin(); iterator != usersById->end();
         iterator++) {
        result->push_back(iterator->second);
    }
    return result;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
void SFSUserManager::ClearAll() {
    usersById->clear();
    usersByName->clear();
}

// -------------------------------------------------------------------
// LogWarn
// -------------------------------------------------------------------
void SFSUserManager::LogWarn(const boost::shared_ptr<std::string>& msg) {
    if (sfs != NULL) {
        boost::shared_ptr<std::vector<std::string>> messages(
            new vector<string>());
        messages->push_back(*msg);

        sfs->Log()->Warn(messages);
        return;
    }

    if (room != NULL && room->RoomManager() != NULL) {
        boost::shared_ptr<std::vector<std::string>> messages(
            new vector<string>());
        messages->push_back(*msg);

        room->RoomManager()->SmartFoxClient()->Log()->Warn(messages);
        return;
    }
}

// -------------------------------------------------------------------
// AddUserInternal
// -------------------------------------------------------------------
void SFSUserManager::AddUserInternal(const boost::shared_ptr<User>& user) {
    auto g0 = boost::make_lock_guard(lockUsersById);
    auto g1 = boost::make_lock_guard(lockUsersByName);

    usersById->emplace(user->Id(), user);
    usersByName->emplace(*user->Name(), user);
}
} // namespace Managers
} // namespace Entities
} // namespace Sfs2X
