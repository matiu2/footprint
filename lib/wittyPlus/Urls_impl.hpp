#pragma once

#include <map>

#include "Urls.hpp"
#include "SubDivided.hpp"

namespace wittyPlus {

struct UrlTreeBranch;

typedef std::unique_ptr<UrlTreeBranch> HandlerEntry;
typedef std::map<std::string, HandlerEntry> HandlerMap;
typedef std::function<UrlTreeBranch*(HandlerMap* leaves, DelimStringPart part)> WalkingFunc;

/** A linked-tree structure, that allows us to map a path of a url to a functor.
    For example, the tree could hold:
    \_person
      \_edit
    An incoming path for: person/mary
    would trigger the person callback.

    An incoming path of /person/edit or /person/edit/mary
    would trigger the 'edit' functor.

    An incoming path of /person/someting/else
    would also trigger the 'person' functor.
**/
struct UrlTreeBranch {
    PathHandler onSelected = nullptr;
    HandlerMap children;
    bool canCall() { return onSelected == nullptr; }
};

class Urls::Impl : public Wt::WObject {
private:
    /// The registry that maps urls to calls
    HandlerMap registry;
    /// Catches the signal for url changes and 
    void handleUrlChanged(const std::string& path);
    /// Walks the trees of the registry, and returns the best match for 'path'
    UrlTreeBranch* walkBranches(const std::string& path, WalkingFunc getNextBranch);
    /// Finds the next step in the path for a part
    static UrlTreeBranch* findSingle(HandlerMap* leaves, DelimStringPart part);
    /// Tries to find a single part of the path, then inserts it if it's not there
    static UrlTreeBranch* addSingle(HandlerMap* leaves, DelimStringPart part);
    /// Find a branch that matches path
    UrlTreeBranch* findBranch(const std::string& path);
public:
    /// @param internalPathChanged use the signal from Wt::WApplication::internalPathChanged
    Impl(Wt::WObject* parent, Wt::Signal<std::string>& internalPathChanged);
    /// Needed because we hold a unique_ptr inside of registry
    ~Impl();
    /// Add a handler for when the application path changes to 'url'
    void addHandler(const std::string& url, PathHandler handler);
};

}
