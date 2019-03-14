// ===================================================================
//
// Description
//        Contains the definition of SFSBuddyManager
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __SFSBuddyManager__
#define __SFSBuddyManager__

#include "IBuddyManager.h"
#include "../../SmartFox.h"
#include "../SFSBuddy.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <map>    // STL library: map object
#include <vector> // STL library: vector object
#include <string> // STL library: string object

namespace Sfs2X {
namespace Entities {
using namespace Variables;

namespace Managers {

/// <summary>
/// The class manages the current User's Buddy List
/// </summary>
class DLLImportExport SFSBuddyManager : public IBuddyManager {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------
    SFSBuddyManager(boost::shared_ptr<SmartFox> sfs);

    virtual ~SFSBuddyManager() override;

    virtual void Dispose() override;

    virtual bool Inited() override;
    virtual void Inited(bool value) override;

    virtual void AddBuddy(const boost::shared_ptr<Buddy>& buddy) override;

    virtual void ClearAll() override;

    virtual boost::shared_ptr<Buddy> RemoveBuddyById(int id) override;

    virtual boost::shared_ptr<Buddy>
    RemoveBuddyByName(const std::string& name) override;

    virtual boost::shared_ptr<Buddy> GetBuddyById(int id) override;

    virtual bool ContainsBuddy(const std::string& name) override;

    virtual boost::shared_ptr<Buddy>
    GetBuddyByName(const std::string& name) override;

    virtual boost::shared_ptr<Buddy>
    GetBuddyByNickName(const std::string& nickName) override;

    virtual boost::shared_ptr<std::vector<boost::shared_ptr<Buddy>>>
    OfflineBuddies() override;

    virtual boost::shared_ptr<std::vector<boost::shared_ptr<Buddy>>>
    OnlineBuddies() override;

    virtual boost::shared_ptr<std::vector<boost::shared_ptr<Buddy>>>
    BuddyList() override;

    virtual boost::shared_ptr<BuddyVariable>
    GetMyVariable(const std::string& varName) override;

    virtual boost::shared_ptr<BuddyVariable>
    GetMyVariable(const boost::shared_ptr<std::string>& varName) override;

    virtual boost::shared_ptr<std::vector<boost::shared_ptr<BuddyVariable>>>
    MyVariables() override;

    virtual void MyVariables(
        const boost::shared_ptr<std::vector<boost::shared_ptr<BuddyVariable>>>&
            value) override;

    virtual bool MyOnlineState() override;

    virtual void MyOnlineState(bool value) override;

    virtual boost::shared_ptr<std::string> MyNickName() override;

    virtual void MyNickName(const std::string& value) override;

    virtual boost::shared_ptr<std::string> MyState() override;

    virtual void MyState(const std::string& value) override;

    virtual boost::shared_ptr<std::vector<std::string>> BuddyStates() override;

    virtual void BuddyStates(
        const boost::shared_ptr<std::vector<std::string>>& value) override;

    virtual void
    SetMyVariable(const boost::shared_ptr<BuddyVariable>& bVar) override;

    // -------------------------------------------------------------------
    // Public members
    // -------------------------------------------------------------------

protected:
    // -------------------------------------------------------------------
    // Protected methods
    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    // Protected members
    // -------------------------------------------------------------------
    boost::shared_ptr<std::map<std::string, boost::shared_ptr<Buddy>>>
        buddiesByName;
    boost::shared_ptr<std::map<std::string, boost::shared_ptr<BuddyVariable>>>
        myVariables;
    bool myOnlineState;
    bool inited;

private:
    // -------------------------------------------------------------------
    // Private methods
    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------
    boost::shared_ptr<std::vector<std::string>> buddyStates;
    boost::shared_ptr<SmartFox> sfs;
    boost::recursive_mutex lockBuddiesByName;
    boost::recursive_mutex lockMyVariables;
};
} // namespace Managers
} // namespace Entities
} // namespace Sfs2X

#endif
