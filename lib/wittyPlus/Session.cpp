#include "Session.hpp"
#include "Session_impl.hpp"

#include <Wt/WLogger>

namespace wittyPlus {

Session::Session(const std::string& db) : _impl(new Impl(*this, db)) {
}

Session::~Session() {}

} // namespace wittyPlus
