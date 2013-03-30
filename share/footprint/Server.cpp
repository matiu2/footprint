#include "Server.hpp"
#include "Server_auth.hpp"

namespace footprint {

Server::Server(int argc, char** argv) : Wt::WServer(argv[0]) {
    setServerConfiguration(argc, argv);
    _auth.reset(new Auth());
}

Server::~Server() {}

}
