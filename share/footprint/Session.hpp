#ifndef FOOTPRINT_SESSION_HPP
#define FOOTPRINT_SESSION_HPP

#include <memory>

#include <Wt/Dbo/Session>

namespace footprint {

namespace dbo = Wt::Dbo;

class Session : public dbo::Session {
public:
    struct Impl;
private:
    std::unique_ptr<Impl> _impl;
    void mapClasses();
    void syncDatabase();
public:
    Session(const std::string& db);
    Impl* impl() { return _impl.get(); } // Only used by Auth.cpp
};

} // namespace footprint

#endif // FOOTPRINT_SESSION_HPP
