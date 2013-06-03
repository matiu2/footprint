#include "Server.hpp"
#include "Server_auth.hpp"

namespace wittyPlus {

Server::Server(const std::string& path, const std::string& configFileName) : Wt::WServer(path, configFileName) {
    auth.reset(new Auth());
}

Server::~Server() {
    Wt::WServer::~WServer();
}

}
