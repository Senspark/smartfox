// ===================================================================
//
// Description
//        Contains the definition of MessageRecipientMode
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __MessageRecipientMode__
#define __MessageRecipientMode__

#include <boost/exception/exception.hpp>
#include <boost/exception/all.hpp>
#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#include "../Util/Common.h"
#include "../Entities/Room.h"
#include "../Entities/User.h"

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object

namespace Sfs2X {
namespace Requests {
enum MessageRecipientType {
    MESSAGERECIPIENTTYPE_TO_USER = 0,
    MESSAGERECIPIENTTYPE_TO_ROOM = 1,
    MESSAGERECIPIENTTYPE_TO_GROUP = 2,
    MESSAGERECIPIENTTYPE_TO_ZONE = 3
};

/// <summary>
/// This class is used to specify the recipient mode for Moderator Messages and
/// Administrator Message.
/// </summary>
/// <remarks>
/// There are 4 recipient modes:
/// <ul>
///         <li><b>TO_USER:</b> the message will be sent to the User (passed as
/// the <i>target</i> parameter)</li>         <li><b>TO_ROOM:</b> the message
/// will be sent to all Users in the Room (passed as the <i>target</i>
/// parameter)</li>         <li><b>TO_GROUP: </b> the message will be sent to
/// all Users in the Room Group (passed as a String in the <i>target</i>
/// parameter)</li>         <li><b>TO_ZONE: </b> the message will be sent to all
/// Users in the Zone (<i>target</i> is ignored)</li>
/// </ul>
/// </remarks>
/// <seealso cref="ModeratorMessageRequest"/>
/// <seealso cref="AdminMessageRequest"/>
class DLLImportExport MessageRecipientMode {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="mode">
    /// the recipient mode
    /// </param>
    /// <param name="target">
    /// the target, depending on the specified recipient mode, as explained in
    /// the Class overview
    /// </param>
    explicit MessageRecipientMode(int mode,
                                  const boost::shared_ptr<User>& target);

    explicit MessageRecipientMode(int mode,
                                  const boost::shared_ptr<Room>& target);

    explicit MessageRecipientMode(int mode, const std::string& target);

    virtual ~MessageRecipientMode();

    boost::shared_ptr<User> TargetUser() const;
    boost::shared_ptr<Room> TargetRoom() const;
    boost::shared_ptr<std::string> TargetString() const;
    int TargetInt() const;
    boost::shared_ptr<std::vector<boost::shared_ptr<User>>>
    TargetUsersCollection() const;

    int Mode() const;

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

private:
    // -------------------------------------------------------------------
    // Private methods
    // -------------------------------------------------------------------

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------
    boost::shared_ptr<User> targetUser;
    boost::shared_ptr<Room> targetRoom;
    boost::shared_ptr<std::string> targetString;
    boost::shared_ptr<int> targetInt;
    boost::shared_ptr<std::vector<boost::shared_ptr<User>>>
        targetUsersCollection;

    int mode;
};
} // namespace Requests
} // namespace Sfs2X

#endif
