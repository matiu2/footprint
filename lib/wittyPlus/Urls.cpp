#include "Urls.hpp"

#include "App.hpp"
#include "exceptions.hpp"
#include "SubDivided.hpp"

#include <map>
#include <iterator>
#include <functional>
#include <memory>

#include <Wt/WContainerWidget>

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
            auto found = registry.find(part);
            if (found == registry.end())
                throw NotFound(path);
            branch = found->second;
        }
        while (part) {
            auto found = branch->children.find(part++);
            if (found == registry.end())
                break;
            branch = found->second;
        }
        branch->onSelected(path);
    }
};

Urls::Urls(Wt::WObject* parent, Wt::Signal<std::string>& internalPathChanged) : Wt::WObject(parent) {
    _impl = new Impl(this, internalPathChanged);
}

Urls* Urls::instance() {
    App* app = App::instance();
    return app->urls();
}

void Urls::addPath(const std::string& path, std::function<void(const std::string&)> callMe) {
    auto part = lazySplit(path, '/');
    UrlTreeBranch* branch = _impl->registry.insert(handler_map::value_type(part++, new UrlTreeBranch())).first->second;
    while (part)
        branch = branch->children.insert(handler_map::value_type(part++, new UrlTreeBranch())).first->second;
    branch->onSelected = callMe;
}

void Urls::addPath(const std::string& path, Wt::WWidget* widget) {
    auto callMe = [widget](const std::string& path){
        auto root = App::instance()->root();
        root->clear();
        root->addWidget(widget);
    };
    addPath(path, callMe);
}

} // namespace wittyPlus
