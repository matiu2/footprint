#ifndef URLS_IMPL_HPP
#define URLS_IMPL_HPP

#include "Urls.hpp"
#include "SubDivided.hpp"

#include <map>

#include "exceptions.hpp"

namespace wittyPlus {

class UrlTreeBranch;

typedef std::function<void(const std::string&)> path_handler;
typedef std::map<std::string, UrlTreeBranch*> handler_map;

struct UrlTreeBranch {
    path_handler onSelected = nullptr;
    handler_map children;
    ~UrlTreeBranch() {
        auto child = children.end();
        while (child != children.begin())
            delete (child--)->second;
        delete child->second;
    }
    bool canCall() { return onSelected == nullptr; }
};

struct Urls::Impl : public Wt::WObject {
    handler_map registry;
    Impl(Wt::WObject* parent, Wt::Signal<std::string>& internalPathChanged) : Wt::WObject(parent) {
        internalPathChanged.connect(this, &Impl::handleUrlChanged);
    }
    void handleUrlChanged(const std::string& path) {
        auto part = lazySplit(path, '/');
        const UrlTreeBranch* branch;
        {
            auto found = registry.find(part++);
            if (found == registry.end())
                throw NotFound(path);
            branch = found->second;
        }
        while (part) {
            auto found = branch->children.find(part++);
            if (found == branch->children.end())
                break;
            branch = found->second;
        }
        branch->onSelected(path);
    }
};

}

#endif // URLS_IMPL_HPP
