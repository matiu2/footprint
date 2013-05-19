#include <memory>
#include <string>

#include <Wt/Dbo/SqlConnection>

namespace wittyPlus {
    /// Returns a connected DB connection, or raises runtime_error
    std::unique_ptr<Wt::Dbo::SqlConnection> makeConnection(const std::string& db);
}
