#pragma once

#include <memory>

#include <Wt/WServer>

namespace wittyPlus {

class Server : public Wt::WServer {
public:
    struct Auth;
private:
    std::unique_ptr<Auth> auth;
    friend class Auth;
public:
    Server(const std::string& path, const std::string& configFileName);
    ~Server();
    static Server* instance() { return dynamic_cast<Server*>(Wt::WServer::instance()); }
};

}
