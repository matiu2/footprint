#include "SubDivided.hpp"

namespace wittyPlus {

template class Part<std::string>;
template class DelimitedPart<std::string>;

bool operator !=(const char* a, const StringPart& b) { return !(b == a); }
bool operator !=(const std::string& a, const StringPart& b) { return !(b == a); }
bool operator ==(const std::string& a, const StringPart& b) { return b == a; }

}
