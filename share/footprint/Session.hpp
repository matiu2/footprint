#ifndef FOOTPRINT_SESSION_HPP
#define FOOTPRINT_SESSION_HPP

#include <memory>

#include <Wt/Dbo/Session>


namespace footprint {

namespace dbo = Wt::Dbo;


class Session : public dbo::Session {
private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
    void mapClasses();
    void syncDatabase();
public:
    Session(const std::string& db);
};

} // namespace footprint

#endif // FOOTPRINT_SESSION_HPP
