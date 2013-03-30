#ifndef FOOTPRINT_SESSION_HPP
#define FOOTPRINT_SESSION_HPP

#include <Wt/Dbo/Session>
#include <Wt/Dbo/backend/Postgres>
#include <Wt/Auth/Dbo/UserDatabase>
#include <Wt/Auth/Login>

#include "db/User.hpp"

namespace footprint {

namespace dbo = Wt::Dbo;

typedef Wt::Auth::Dbo::UserDatabase<db::AuthInfo> UserDatabase;

class Session : public dbo::Session {
private:
    dbo::backend::Postgres _connection;
    UserDatabase _users;
    Wt::Auth::Login _login;
    void mapClasses();
    void syncDatabase();
public:
    Session(const std::string& db);

    Wt::Auth::AbstractUserDatabase& users();
    Wt::Auth::Login& login() { return _login; }
};

} // namespace footprint

#endif // FOOTPRINT_SESSION_HPP
