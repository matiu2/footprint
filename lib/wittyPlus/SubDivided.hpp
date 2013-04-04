/**
 * Mimics a read-only string (or other container), but actually just uses two read-only iterators into another string by reference to save on copying.
 *
 **/
#pragma once

#include <functional>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <string>

namespace wittyPlus {

template<typename T>
struct SubDivided {
    typedef typename T::const_iterator const_iterator;
    typedef typename T::value_type value_type;
    const T* original=nullptr;
    value_type delimeter = value_type();
    std::pair<const_iterator, const_iterator> range;
    const_iterator begin() const { return range.first; }
    const_iterator end() const { return range.second; }
    SubDivided(const T& original, value_type delim)
        : original(&original), delimeter(delim),
          range(get_next(original.begin())) {}
    SubDivided() {}
    template <typename T2>
    bool compare(const T2* other, std::function<bool(value_type, T2)> pred) const {
        /// Compares until *other is false. Useful for comparing to char*
        auto first1 = begin();
        auto last1 = end();
        while ((first1 != last1) && (*other)) {
            if (!pred(*(first1++), *(other++)))
                return false;
        }
        return (first1 == end()) && ((bool)(*other) == false);
    }
    template <typename T2>
    bool compare(const T2& other, std::function<bool(value_type, typename T2::value_type)> pred) const {
        /// Compares against another container
        auto first1 = begin();
        auto last1 = end();
        auto first2 = other.begin();
        auto last2 = other.end();
        if (begin() == end())
            return other.begin() == other.end();
        while ((first1 != last1) && (first2 != last2)) {
            if (!pred(*(first1++), *(first2++)))
                return false;
        }
        return true;
    }
    std::pair<const_iterator, const_iterator> get_next(const_iterator start=const_iterator()) const {
        if (original != nullptr) {
            auto next = start == const_iterator() ? end() : start,
                 last = next;
            do {
                next = std::find(last, original->end(), delimeter);
                // Only push non-empty references
                if (last != next)
                    return make_pair(last, next);
                last = next+1;
            } while (next != original->end());
        }
        return make_pair(const_iterator(), const_iterator());
    }
    SubDivided<T>& operator++() {
        range = get_next();
        return *this;
    }
    SubDivided<T> operator++(int) {
        SubDivided<T> result(*this);
        ++(*this);
        return result;
    }
    operator bool() {
        return range != make_pair(const_iterator(), const_iterator());
    }
    bool operator ==(const SubDivided<T>& other) {
        return compare(other, [](value_type a, value_type b){ return a == b; });
    }
    bool operator !=(const SubDivided<T>& other) { return !(*this == other); }
    template <typename T2>
    bool operator ==(const T2& other) const { return compare(other, [](value_type a, typename T2::value_type b){ return a == b; }); }
    template <typename T2>
    bool operator ==(const T2* other) const { return compare<T2>(other, [](value_type a, T2 b){ return a == b; }); }

    template <typename T2>
    bool operator !=(const T2& other) const { return !((*this) == other); }
    template <typename T2>
    bool operator !=(const T2* other) const { return !compare<T2>(other, [](value_type a, T2 b){ return a == b; }); }

    template <typename T2>
    bool operator <(const T2& other) const { return compare(other, [](value_type a, typename T2::value_type b){ return a < b; }); }
    template <typename T2>
    bool operator <(const T2* other) const { return compare<T2>(other, [](value_type a, T2 b){ return a < b; }); }

    template <typename T2>
    bool operator >(const T2& other) const { return compare(other, [](value_type a, typename T2::value_type b){ return a > b; }); }
    template <typename T2>
    bool operator >(const T2* other) const { return compare<T2>(other, [](value_type a, T2 b){ return a > b; }); }
    
    template <typename T2>
    bool operator <=(const T2& other) const { return compare(other, [](value_type a, typename T2::value_type b){ return a <= b; }); }
    template <typename T2>
    bool operator <=(const T2* other) const { return compare<T2>(other, [](value_type a, T2 b){ return a <= b; }); }

    template <typename T2>
    bool operator >=(const T2& other) const { return compare(other, [](value_type a, typename T2::value_type b){ return a >= b; }); }
    template <typename T2>
    bool operator >=(const T2* other) const { return compare<T2>(other, [](value_type a, T2 b){ return a >= b; }); }
};

bool operator !=(const char* a, const SubDivided<std::string>& b) { return !(b == a); }
bool operator !=(std::string a, const SubDivided<std::string>& b) { return !(b == a); }

template <typename T>
std::ostream& operator <<(std::ostream& out, const SubDivided<T>& s) {
    auto i = s.begin();
    while (i != s.end())
        out << *(i++);
    return out;
}

typedef SubDivided<std::string> SubDividedString;

}
