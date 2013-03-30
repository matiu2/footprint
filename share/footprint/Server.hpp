#ifndef SERVER_HPP
#define SERVER_HPP

#include <memory>

#include <Wt/WServer>

namespace footprint {

class Server : public Wt::WServer {
private:
    class Auth;
    std::unique_ptr<Auth> _auth;
public:
    Server(const std::string &wtApplicationPath=std::string(), const std::string &wtConfigurationFile=std::string());
    ~Server();
};

}

#endif // SERVER_HPP
