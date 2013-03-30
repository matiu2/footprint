#pragma once
#include "Session.hpp"

#include <stdexcept>

#include <Wt/Dbo/backend/Postgres>
#include <Wt/Auth/Dbo/UserDatabase>
#include <Wt/Auth/Login>

#include "User.hpp"

namespace wittyPlus {

typedef Wt::Auth::Dbo::UserDatabase<db::AuthInfo> UserDatabase;

struct Session::Impl {
    dbo::Session& _session;
    dbo::backend::Postgres _connection;
    UserDatabase _users;
    Wt::Auth::Login _login;
    Impl(dbo::Session& session, const std::string& db) : _session(session), _connection(db), _users(session) {
        if (_connection.connection() == nullptr)
            throw std::logic_error(std::string("Unable to connect to database: ") + db);
        session.setConnection(_connection);
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

}
