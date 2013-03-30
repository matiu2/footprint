#include "Session.hpp"

#include <Wt/WLogger>

namespace footprint {

Session::Session(const std::string& db) : _connection(db), _users(*this) {
    setConnection(_connection);
    mapClasses();
    syncDatabase();
}

void Session::mapClasses() {
    mapClass<db::User>("user");
    mapClass<db::AuthInfo>("auth_info");
    mapClass<db::AuthInfo::AuthIdentityType>("auth_identity");
    mapClass<db::AuthInfo::AuthTokenType>("auth_token");
}

void Session::syncDatabase() {
    try {
      createTables();
      Wt::log("info") << "Created database.";
    } catch (std::exception& e) {
      Wt::log("info") << e.what();
      Wt::log("info") << "Using existing database";
    }
}

} // namespace footprint
