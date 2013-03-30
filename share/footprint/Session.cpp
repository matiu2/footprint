#include "Session.hpp"

#include <Wt/Dbo/backend/Postgres>
#include <Wt/Auth/Dbo/UserDatabase>
#include <Wt/Auth/Login>
#include <Wt/WLogger>

#include "db/User.hpp"

namespace footprint {

typedef Wt::Auth::Dbo::UserDatabase<db::AuthInfo> UserDatabase;

struct Session::Impl {
    dbo::Session& _session;
    dbo::backend::Postgres _connection;
    UserDatabase _users;
    Wt::Auth::Login _login;
    Impl(dbo::Session& session, const std::string& db) : _session(session), _connection(db), _users(session) {
        mapClasses();
        syncDatabase();
    }
    void mapClasses() {
        _session.mapClass<db::User>("user");
        _session.mapClass<db::AuthInfo>("auth_info");
        _session.mapClass<db::AuthInfo::AuthIdentityType>("auth_identity");
        _session.mapClass<db::AuthInfo::AuthTokenType>("auth_token");
    }

    void syncDatabase() {
        try {
            _session.createTables();
            Wt::log("info") << "Created database.";
        } catch (std::exception& e) {
            Wt::log("info") << e.what();
            Wt::log("info") << "Using existing database";
        }
    }

};

Session::Session(const std::string& db) : _impl(new Impl(*this, db)) {
    setConnection(_impl->_connection);
}

} // namespace footprint
