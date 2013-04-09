#pragma once
#include "Session.hpp"

#include <stdexcept>


#ifdef POSTGRES
#include <Wt/Dbo/backend/Postgres>
#else
#include <Wt/Dbo/backend/Sqlite3>
#endif

#include <Wt/Auth/Dbo/UserDatabase>
#include <Wt/Auth/Login>

#include "User.hpp"

namespace wittyPlus {

typedef Wt::Auth::Dbo::UserDatabase<db::AuthInfo> UserDatabase;

struct Session::Impl {
    #ifdef POSTGRES
    dbo::backend::Postgres connection;
    #else
    dbo::backend::Sqlite3 connection;
    #endif
    dbo::Session& session;
    UserDatabase users;
    Wt::Auth::Login login;
    Impl(dbo::Session& session, const std::string& db) : session(session), connection(db), users(session) {
        if (connection.connection() == nullptr)
            throw std::logic_error(std::string("Unable to connect to database: ") + db);
        session.setConnection(connection);
        mapClasses();
        syncDatabase();
    }
    void mapClasses() {
        session.mapClass<db::User>("user");
        session.mapClass<db::AuthInfo>("auth_info");
        session.mapClass<db::AuthInfo::AuthIdentityType>("auth_identity");
        session.mapClass<db::AuthInfo::AuthTokenType>("auth_token");
    }

    void syncDatabase() {
        try {
            session.createTables();
            Wt::log("info") << "Created database.";
        } catch (std::exception& e) {
            Wt::log("info") << e.what();
            Wt::log("info") << "Using existing database";
        }
    }
};

}
