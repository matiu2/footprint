#include "Session.hpp"
#include "Session_impl.hpp"

#include <Wt/WLogger>

namespace footprint {

Session::Session(const std::string& db) : _impl(new Impl(*this, db)) {
}

} // namespace footprint
