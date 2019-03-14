// ===================================================================
//
// Description
//        Contains the implementation of SFSBuddyManager
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#include "SFSBuddyManager.h"
#include "../Variables/ReservedBuddyVariables.h"
#include "../Variables/SFSBuddyVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Managers {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSBuddyManager::SFSBuddyManager(boost::shared_ptr<SmartFox> sfs) {
    this->sfs = sfs;
    buddiesByName = boost::shared_ptr<map<string, boost::shared_ptr<Buddy>>>(
        new map<string, boost::shared_ptr<Buddy>>());
    myVariables =
        boost::shared_ptr<map<string, boost::shared_ptr<BuddyVariable>>>(
            new map<string, boost::shared_ptr<BuddyVariable>>());
    inited = false;
    buddyStates = boost::shared_ptr<std::vector<std::string>>();
}

// -------------------------------------------------------------------
// Dispose
// -------------------------------------------------------------------
void SFSBuddyManager::Dispose() {
    this->sfs = boost::shared_ptr<SmartFox>();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSBuddyManager::~SFSBuddyManager() {
    buddiesByName->clear();
    buddiesByName = boost::shared_ptr<map<string, boost::shared_ptr<Buddy>>>();
    myVariables->clear();
    myVariables =
        boost::shared_ptr<map<string, boost::shared_ptr<BuddyVariable>>>();
}

// -------------------------------------------------------------------
// Inited
// -------------------------------------------------------------------
bool SFSBuddyManager::Inited() {
    return inited;
}

// -------------------------------------------------------------------
// Inited
// -------------------------------------------------------------------
void SFSBuddyManager::Inited(bool value) {
    inited = value;
}

// -------------------------------------------------------------------
// AddBuddy
// -------------------------------------------------------------------
void SFSBuddyManager::AddBuddy(const boost::shared_ptr<Buddy>& buddy) {
    auto guard = boost::make_lock_guard(lockBuddiesByName);
    buddiesByName->emplace(*buddy->Name(), buddy);
}

// -------------------------------------------------------------------
// ClearAll
// -------------------------------------------------------------------
void SFSBuddyManager::ClearAll() {
    auto guard = boost::make_lock_guard(lockBuddiesByName);
    buddiesByName->clear();
}

// -------------------------------------------------------------------
// RemoveBuddyById
// -------------------------------------------------------------------
boost::shared_ptr<Buddy> SFSBuddyManager::RemoveBuddyById(int id) {
    auto buddy = GetBuddyById(id);
    if (buddy != NULL) {
        auto itrBuddy = buddiesByName->find(*buddy->Name());
        if (itrBuddy != buddiesByName->end()) {
            auto guard = boost::make_lock_guard(lockBuddiesByName);
            buddiesByName->erase(itrBuddy);
        }
    }
    return buddy;
}

// -------------------------------------------------------------------
// RemoveBuddyByName
// -------------------------------------------------------------------
boost::shared_ptr<Buddy>
SFSBuddyManager::RemoveBuddyByName(const std::string& name) {
    auto buddy = GetBuddyByName(name);
    if (buddy != NULL) {
        auto itrBuddy = buddiesByName->find(name);
        if (itrBuddy != buddiesByName->end()) {
            auto guard = boost::make_lock_guard(lockBuddiesByName);
            buddiesByName->erase(itrBuddy);
        }
    }
    return buddy;
}

// -------------------------------------------------------------------
// GetBuddyById
// -------------------------------------------------------------------
boost::shared_ptr<Buddy> SFSBuddyManager::GetBuddyById(int id) {
    if (id > -1) {
        auto guard = boost::make_lock_guard(lockBuddiesByName);
        for (auto iteratorBuddies = buddiesByName->begin();
             iteratorBuddies != buddiesByName->end(); iteratorBuddies++) {
            boost::shared_ptr<Buddy> buddy = iteratorBuddies->second;
            if (buddy->Id() == id) {
                return buddy;
            }
        }
    }
    return boost::shared_ptr<Buddy>();
}

// -------------------------------------------------------------------
// ContainsBuddy
// -------------------------------------------------------------------
bool SFSBuddyManager::ContainsBuddy(const std::string& name) {
    auto guard = boost::make_lock_guard(lockBuddiesByName);
    auto iterator = buddiesByName->find(name);
    if (iterator != buddiesByName->end()) {
        return true;
    }
    return false;
}

// -------------------------------------------------------------------
// GetBuddyByName
// -------------------------------------------------------------------
boost::shared_ptr<Buddy>
SFSBuddyManager::GetBuddyByName(const std::string& name) {
    auto guard = boost::make_lock_guard(lockBuddiesByName);
    auto iterator = buddiesByName->find(name);
    if (iterator != buddiesByName->end()) {
        return iterator->second;
    }
    return boost::shared_ptr<Buddy>();
}

// -------------------------------------------------------------------
// GetBuddyByNickName
// -------------------------------------------------------------------
boost::shared_ptr<Buddy>
SFSBuddyManager::GetBuddyByNickName(const std::string& nickName) {
    auto guard = boost::make_lock_guard(lockBuddiesByName);
    for (auto iteratorBuddies = buddiesByName->begin();
         iteratorBuddies != buddiesByName->end(); iteratorBuddies++) {
        boost::shared_ptr<Buddy> buddy = iteratorBuddies->second;
        if (*(buddy->NickName()) == nickName) {
            return buddy;
        }
    }
    return boost::shared_ptr<Buddy>();
}

// -------------------------------------------------------------------
// OfflineBuddies
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<boost::shared_ptr<Buddy>>>
SFSBuddyManager::OfflineBuddies() {
    boost::shared_ptr<std::vector<boost::shared_ptr<Buddy>>> buddies(
        new vector<boost::shared_ptr<Buddy>>());

    for (auto iteratorBuddies = buddiesByName->begin();
         iteratorBuddies != buddiesByName->end(); iteratorBuddies++) {
        boost::shared_ptr<Buddy> buddy = iteratorBuddies->second;
        if (!buddy->IsOnline())
            buddies->push_back(buddy);
    }

    return buddies;
}

// -------------------------------------------------------------------
// OnlineBuddies
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<boost::shared_ptr<Buddy>>>
SFSBuddyManager::OnlineBuddies() {
    boost::shared_ptr<std::vector<boost::shared_ptr<Buddy>>> buddies(
        new vector<boost::shared_ptr<Buddy>>());

    auto guard = boost::make_lock_guard(lockBuddiesByName);
    for (auto iteratorBuddies = buddiesByName->begin();
         iteratorBuddies != buddiesByName->end(); iteratorBuddies++) {
        boost::shared_ptr<Buddy> buddy = iteratorBuddies->second;
        if (buddy->IsOnline())
            buddies->push_back(buddy);
    }
    return buddies;
}

// -------------------------------------------------------------------
// BuddyList
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<boost::shared_ptr<Buddy>>>
SFSBuddyManager::BuddyList() {
    boost::shared_ptr<std::vector<boost::shared_ptr<Buddy>>> buddies(
        new vector<boost::shared_ptr<Buddy>>());

    auto guard = boost::make_lock_guard(lockBuddiesByName);
    for (auto iteratorBuddies = buddiesByName->begin();
         iteratorBuddies != buddiesByName->end(); iteratorBuddies++) {
        boost::shared_ptr<Buddy> buddy = iteratorBuddies->second;
        buddies->push_back(buddy);
    }
    return buddies;
}

// -------------------------------------------------------------------
// GetMyVariable
// -------------------------------------------------------------------
boost::shared_ptr<BuddyVariable>
SFSBuddyManager::GetMyVariable(const std::string& varName) {
    auto guard = boost::make_lock_guard(lockBuddiesByName);
    auto iterator = myVariables->find(varName);
    if (iterator != myVariables->end()) {
        return iterator->second;
    }
    return boost::shared_ptr<BuddyVariable>();
}

// -------------------------------------------------------------------
// GetMyVariable
// -------------------------------------------------------------------
boost::shared_ptr<BuddyVariable>
SFSBuddyManager::GetMyVariable(const boost::shared_ptr<std::string>& varName) {
    return SFSBuddyManager::GetMyVariable(*varName);
}

// -------------------------------------------------------------------
// MyVariables
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<boost::shared_ptr<BuddyVariable>>>
SFSBuddyManager::MyVariables() {
    boost::shared_ptr<std::vector<boost::shared_ptr<BuddyVariable>>> variables(
        new vector<boost::shared_ptr<BuddyVariable>>());

    lockMyVariables.lock();

    std::map<string, boost::shared_ptr<BuddyVariable>>::iterator iterator;
    for (iterator = myVariables->begin(); iterator != myVariables->end();
         iterator++) {
        boost::shared_ptr<BuddyVariable> variable = iterator->second;
        variables->push_back(variable);
    }

    lockMyVariables.unlock();

    return variables;
}

// -------------------------------------------------------------------
// MyVariables
// -------------------------------------------------------------------
void SFSBuddyManager::MyVariables(
    const boost::shared_ptr<std::vector<boost::shared_ptr<BuddyVariable>>>&
        value) {
    for (auto iterator = value->begin(); iterator != value->end(); iterator++) {
        SetMyVariable(*iterator);
    }
}

// -------------------------------------------------------------------
// MyOnlineState
// -------------------------------------------------------------------
bool SFSBuddyManager::MyOnlineState() {
    // Manager not inited, we're offline
    if (!inited)
        return false;

    // If the online var is not defined we take it as online=true (default)
    bool onlineState = true;
    boost::shared_ptr<BuddyVariable> onlineVar =
        GetMyVariable(ReservedBuddyVariables::BV_ONLINE);

    if (onlineVar != NULL)
        onlineState = *(onlineVar->GetBoolValue());

    return onlineState;
}

// -------------------------------------------------------------------
// MyOnlineState
// -------------------------------------------------------------------
void SFSBuddyManager::MyOnlineState(bool value) {
    boost::shared_ptr<bool> pvalue(new bool());
    *pvalue = value;
    boost::shared_ptr<BuddyVariable> variable(new SFSBuddyVariable(
        ReservedBuddyVariables::BV_ONLINE, pvalue, VARIABLETYPE_BOOL));
    SetMyVariable(variable);
}

// -------------------------------------------------------------------
// MyNickName
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSBuddyManager::MyNickName() {
    boost::shared_ptr<BuddyVariable> nickNameVar =
        GetMyVariable(ReservedBuddyVariables::BV_NICKNAME);
    return (nickNameVar != NULL) ? nickNameVar->GetStringValue()
                                 : boost::shared_ptr<std::string>();
}

// -------------------------------------------------------------------
// MyNickName
// -------------------------------------------------------------------
void SFSBuddyManager::MyNickName(const std::string& value) {
    boost::shared_ptr<std::string> variableValue(new std::string(value));
    boost::shared_ptr<BuddyVariable> variable(
        new SFSBuddyVariable(ReservedBuddyVariables::BV_NICKNAME, variableValue,
                             VARIABLETYPE_STRING));
    SetMyVariable(variable);
}

// -------------------------------------------------------------------
// MyState
// -------------------------------------------------------------------
boost::shared_ptr<std::string> SFSBuddyManager::MyState() {
    boost::shared_ptr<BuddyVariable> stateVar =
        GetMyVariable(ReservedBuddyVariables::BV_STATE);
    return (stateVar != NULL) ? stateVar->GetStringValue()
                              : boost::shared_ptr<std::string>();
}

// -------------------------------------------------------------------
// MyState
// -------------------------------------------------------------------
void SFSBuddyManager::MyState(const std::string& value) {
    boost::shared_ptr<std::string> variableValue(new std::string(value));
    boost::shared_ptr<BuddyVariable> variable(new SFSBuddyVariable(
        ReservedBuddyVariables::BV_STATE, variableValue, VARIABLETYPE_STRING)),
        SetMyVariable(variable);
}

// -------------------------------------------------------------------
// BuddyStates
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<std::string>> SFSBuddyManager::BuddyStates() {
    return buddyStates;
}

// -------------------------------------------------------------------
// BuddyStates
// -------------------------------------------------------------------
void SFSBuddyManager::BuddyStates(
    const boost::shared_ptr<std::vector<std::string>>& value) {
    buddyStates = value;
}

// -------------------------------------------------------------------
// SetMyVariable
// -------------------------------------------------------------------
void SFSBuddyManager::SetMyVariable(
    const boost::shared_ptr<BuddyVariable>& bVar) {
    auto guard = boost::make_lock_guard(lockMyVariables);
    auto iterator = myVariables->find(*bVar->Name());
    if (iterator != myVariables->end()) {
        iterator->second = bVar;
    } else {
        myVariables->emplace(*bVar->Name(), bVar);
    }
}
} // namespace Managers
} // namespace Entities
} // namespace Sfs2X
