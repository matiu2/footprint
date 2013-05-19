#pragma once

#include <functional>
#include <string>

#include <Wt/WWidget>
#include <Wt/WSignal>

namespace wittyPlus {

typedef std::function<void(const std::string&)> PathHandler;

class Urls : Wt::WObject {
public:
    struct Impl;
    Impl* _impl;
public:
    Urls(Wt::WObject* parent, Wt::Signal<std::string>& internalPath);
    static Urls* instance();
    void addPath(const std::string& url, PathHandler callMe);
    void addPath(const std::string& url, Wt::WWidget* widget);
};

} // namespace wittyPlus
