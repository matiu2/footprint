#ifndef SERVER_HPP
#define SERVER_HPP

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
    Server(int argc, char** argv);
    ~Server();
    static Server* instance() { return dynamic_cast<Server*>(Wt::WServer::instance()); }
};

}
#endif // SERVER_HPP
