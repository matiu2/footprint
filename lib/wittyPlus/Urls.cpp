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
typedef std::map<std::string, std::unique_ptr<UrlTreeBranch>> handler_map;

struct UrlTreeBranch {
    path_handler onSelected;
    handler_map children;
};

struct Urls::Impl : public Wt::WObject {
    handler_map registry;
    bool amRegistered = false;
    Impl(Wt::WObject* parent=nullptr) : Wt::WObject(parent) {}
    void ensureMainHandler() {
        /// Hooks us up to the app onNavigate event handler
        if (!amRegistered) {
            App::instance()->internalPathChanged().connect(this, &Impl::handleUrlChanged);
        }
    }
    void handleUrlChanged(const std::string& path) {
        auto part = lazySplit(path, '/');
        const UrlTreeBranch* branch;
        {
            auto found = registry.find(part);
            if (found == registry.end())
                throw NotFound(path);
            branch = found->second.get();
        }
        while (part) {
            auto found = branch->children.find(part++);
            if (found == registry.end())
                break;
            branch = found->second.get();
        }
        branch->onSelected(path);
    }
};

Urls::Urls(Wt::WObject* parent) : Wt::WObject(parent) { _impl = new Impl(this); }

void Urls::addPath(const std::string& path, std::function<void(const std::string&)> callMe) {
    _impl->ensureMainHandler();
    auto part = lazySplit(path, '/');
    handler_map& registry = _impl->registry;
    std::unique_ptr<UrlTreeBranch> branch(new UrlTreeBranch{callMe});
    while (part) {
        auto added = registry.insert(handler_map::value_type(part++, std::unique_ptr<UrlTreeBranch>(new UrlTreeBranch{callMe})));
        registry = added.first->second.get()->children;
    }
}

void Urls::addPath(const std::string& path, Wt::WWidget* widget) {
    _impl->ensureMainHandler();
    auto callMe = [widget](const std::string& path){
        auto root = App::instance()->root();
        root->clear();
        root->addWidget(widget);
    };
    addPath(path, callMe);
}

} // namespace wittyPlus
