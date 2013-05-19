#include "Server.hpp"
#include "Server_auth.hpp"

namespace wittyPlus {

Server::Server(int argc, char** argv) : Wt::WServer(argv[0]) {
    auth.reset(new Auth());
}

Server::~Server() {}

}
