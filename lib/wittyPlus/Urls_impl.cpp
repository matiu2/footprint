
#include "Urls_impl.hpp"
#include "exceptions.hpp"

#include <memory>


namespace wittyPlus {

Urls::Impl::Impl(Wt::WObject* parent, Wt::Signal<std::string>& internalPathChanged) : Wt::WObject(parent) {
    internalPathChanged.connect(this, &Impl::handleUrlChanged);
}

Urls::Impl::~Impl() {}

void Urls::Impl::handleUrlChanged(const std::string& path) {
    UrlTreeBranch* branch = findBranch(path);
    // If we didn't find any branches to handle the request, this is a bad url
    if (branch == nullptr)
        throw NotFound(path);
    branch->onSelected(path);
}

UrlTreeBranch* Urls::Impl::addSingle(HandlerMap* leaves, DelimStringPart part) {
    auto inserted = leaves->insert(
        HandlerMap::value_type(
                    part++,
                    HandlerEntry(new UrlTreeBranch())
        )
    );
    return inserted.first->second.get();
}

void Urls::Impl::addHandler(const std::string& url, PathHandler handler) {
    UrlTreeBranch* branch = walkBranches(url, addSingle);
    branch->onSelected = handler;
}

UrlTreeBranch* Urls::Impl::walkBranches(const std::string& path, WalkingFunc getNextBranch) {
    // Follow path along the 'registry' tree
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

UrlTreeBranch* Urls::Impl::findSingle(HandlerMap* leaves, DelimStringPart part) {
    auto found = leaves->find(part++);
    if (found == leaves->end())
        return nullptr;
    else
        return found->second.get();
}

UrlTreeBranch* Urls::Impl::findBranch(const std::string& path) {
    return walkBranches(path, findSingle);
}
}
