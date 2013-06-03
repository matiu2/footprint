#pragma once
#include "Session.hpp"
#include "base_db/base_db.hpp"

#include <stdexcept>
#include <memory>

#include <Wt/Dbo/SqlConnection>
#include <Wt/Auth/Dbo/UserDatabase>
#include <Wt/Auth/Login>

#include "User.hpp"

namespace wittyPlus {

namespace db {
  typedef Wt::Auth::Dbo::UserDatabase<AuthInfo> UserDatabase;
}

struct Session::Impl {
    std::unique_ptr<dbo::SqlConnection> connection;
    dbo::Session& session;
    db::UserDatabase users;
    Wt::Auth::Login login;
    Impl(dbo::Session& session, const std::string& db) : session(session), connection(makeConnection(db)), users(session) {
        session.setConnection(*connection);
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
