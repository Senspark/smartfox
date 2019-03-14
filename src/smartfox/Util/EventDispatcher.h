// ===================================================================
//
// Description
//        Contains the definition of EventDispatcher
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __EventDispatcher__
#define __EventDispatcher__

#include "DelegateOneArgument.h" // Delegate with one parameter
#include "../Core/BaseEvent.h"
#include "../Core/SFSEvent.h"

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object
#include <map>    // STL library: map object

namespace Sfs2X {
using namespace Core;

namespace Util {
typedef DelegateOneArgument<boost::shared_ptr<BaseEvent>> EventListenerDelegate;

// -------------------------------------------------------------------
// Class EventDispatcher
// -------------------------------------------------------------------
class EventDispatcher {
public:
    // -------------------------------------------------------------------
    // Public methods
    // -------------------------------------------------------------------

    EventDispatcher(const boost::shared_ptr<void>& target);

    void Dispose();
    void
    AddEventListener(const boost::shared_ptr<std::string>& eventType,
                     const boost::shared_ptr<EventListenerDelegate>& listener);

    void RemoveEventListener(
        const boost::shared_ptr<std::string>& eventType,
        const boost::shared_ptr<EventListenerDelegate>& listener);

    void DispatchEvent(const boost::shared_ptr<BaseEvent>& evt);
    void RemoveAll();

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
    bool FilterEvent(const boost::shared_ptr<BaseEvent>& evt);

    // -------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------

    boost::shared_ptr<void> target;
    std::map<string, boost::shared_ptr<EventListenerDelegate>> listeners;
    std::string lastDispatchedEvent;
};
} // namespace Util
} // namespace Sfs2X

#endif
