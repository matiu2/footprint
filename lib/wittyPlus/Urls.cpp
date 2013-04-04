#include "Urls.hpp"

#include "App.hpp"
#include "SubDivided.hpp"

#include <map>
#include <iterator>

namespace wittyPlus {

struct Urls::Impl : public Wt::WObject {
    std::map<std::string, std::function<void(const std::string&)>> registry;
    bool amRegistered = false;
    void checkRegistered() {
        /// Hooks us up to the app onNavigate event handler
        if (!amRegistered) {
            App::instance()->internalPathChanged().connect(this, &Impl::handleUrlChanged);
        }
    }
    void handleUrlChanged(const std::string& path) {
        // Split the path by '/'
        StringBits parts = split(path, '/');
        // Search for the single part first
        auto start = std::lower_bound(registry.begin(), registry.end(), parts[0]);
        //
    }
};

Urls::Urls(Wt::WObject* parent) : Wt::WObject(parent) { _impl = new Impl(this); }

void Urls::register(const std::string& url, std::function<void(const std::string&)> callMe) {
    _impl->checkRegistered();
    _impl->registry[url] = callMe;
}

void Urls::register(const std::string& url, std::function<void()> callMe) {
    _impl->checkRegistered();
    _impl->registry[url] = [&callMe](const std::string& url){callMe();};
}

void Urls::register(const std::string& url, Wt::WWidget* widget) {
    _impl->checkRegistered();
    _impl->registry[url] = [widget](const std::string& url){
        auto root = App::instance()->root();
        root->clear();
        root->addWidget(widget);
    };
}

} // namespace wittyPlus
