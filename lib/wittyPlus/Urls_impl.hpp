#ifndef URLS_IMPL_HPP
#define URLS_IMPL_HPP

#include "Urls.hpp"
#include "SubDivided.hpp"

#include <map>
#include <memory>

#include "exceptions.hpp"

namespace wittyPlus {

class UrlTreeBranch;

typedef std::function<void(const std::string&)> PathHandler;
typedef std::unique_ptr<UrlTreeBranch> HandlerEntry;
typedef std::map<std::string, HandlerEntry> HandlerMap;

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

typedef std::function<UrlTreeBranch*(HandlerMap* leaves, DelimStringPart part)> WalkingFunc;

struct Urls::Impl : public Wt::WObject {
    HandlerMap registry;
    Impl(Wt::WObject* parent, Wt::Signal<std::string>& internalPathChanged) : Wt::WObject(parent) {
        internalPathChanged.connect(this, &Impl::handleUrlChanged);
    }
    void handleUrlChanged(const std::string& path) {
        UrlTreeBranch* branch = findBranch(path);
        // If we didn't find any branches to handle the request, this is a bad url
        if (branch == nullptr)
            throw NotFound(path);
        branch->onSelected(path);
    }
    UrlTreeBranch* addHandler(const std::string& url, PathHandler handler) {
        return  registry.insert(
            HandlerMap::value_type(
                        url,
                        HandlerEntry(new UrlTreeBranch())
            )
        ).first->second.get();
    }

    UrlTreeBranch* walkBranches(const std::string& path, WalkingFunc getNextBranch) {
        /** Follows path to the the UrlTreeBranch that it leads to**/
        auto part = lazySplit(path, '/');
        HandlerMap* leaves = &registry;
        UrlTreeBranch *branch = nullptr,
                      *last_branch = nullptr;
        while (part) {
            last_branch = branch;
            branch = getNextBranch(leaves, part++);
            if (branch == nullptr)
                return last_branch;
            leaves = &branch->children;
        }
        return branch;
    }

    static UrlTreeBranch* findSingle(HandlerMap* leaves, DelimStringPart part) {
        auto found = leaves->find(part++);
        if (found == leaves->end())
            return nullptr;
        else
            return found->second.get();
    }

    UrlTreeBranch* findBranch(const std::string& path) {
        return walkBranches(path, findSingle);
    }
};
}

#endif // URLS_IMPL_HPP
