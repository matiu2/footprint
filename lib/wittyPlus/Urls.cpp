#include "Urls_impl.hpp"

#include "App.hpp"

#include <Wt/WContainerWidget>

namespace wittyPlus {

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
