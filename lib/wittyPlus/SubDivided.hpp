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
struct Part {
    typedef typename T::const_iterator const_iterator;
    typedef typename T::value_type value_type;
    typedef std::pair<const_iterator, const_iterator> range_type;

    range_type range;

    Part(range_type range) : range(range) {}
    Part(const_iterator a, const_iterator b) : range{a, b} {}
    Part() : range{const_iterator(), const_iterator()} {}

    const_iterator begin() const { return range.first; }
    const_iterator end() const { return range.second; }

    operator bool() {
        return range != make_pair(const_iterator(), const_iterator());
    }

    template<typename T2>
    bool operator ==(const T2* other) const {
        /// Compares against pointer types, useful for pchar
        const T2* last = other;
        while (*last++) {} // Find the end (eg. '\0' for char*)
        auto result = std::mismatch(begin(), end(), other);
        return result == make_pair(end(), last-1);
    }
    template<typename T2>
    bool operator ==(const T2& other) const {
        auto result = std::mismatch(begin(), end(), other.begin());
        return result == make_pair(end(), other.end());
    }
    template<typename T2>
    bool operator !=(const T& other) const { return !((*this) == other); }

    bool operator !=(const T& other) const { return !((*this) == other); }
    bool operator !=(const T* other) const { return !((*this) == other); }

    template<typename T2>
    bool operator <(const T2& other) const {
        return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
    }
    bool operator <(const T* other) const {
        T* last = other;
        while (*last++) {} // Find the end (eg. '\0' for char*)
        return std::lexicographical_compare(begin(), end(), other, last-1, [](T a, T b){return a <= b;});
    }

    /*
    bool operator >(const T& other) const { return !((*this < other)); }
    bool operator >(const T* other) const { return !((*this < other)); }

    bool operator <=(const T& other) const { return !((*this > other)); }
    bool operator <=(const T* other) const { return !((*this > other)); }

    bool operator >=(const T& other) const { return compare(other, [](value_type a, typename value_type b){ return a >= b; }); }
    bool operator >=(const T* other) const { return compare(other, [](value_type a, T b){ return a >= b; }); }
    */
};

bool operator !=(const char* a, const Part<std::string>& b) { return !(b == a); }
bool operator !=(const std::string& a, const Part<std::string>& b) { return !(b == a); }
template <typename T>
bool operator !=(const Part<T>& a, const Part<T>& b) { return !(b == a); }

template <typename T>
struct DelimitedPart : public Part<T> {
    typedef typename Part<T>::const_iterator const_iterator;
    typedef typename Part<T>::value_type value_type;
    typedef typename Part<T>::range_type range_type;

    value_type delimeter;
    range_type maxRange;

    DelimitedPart(range_type aMaxRange, value_type delim)
        : Part<T>(aMaxRange), maxRange(aMaxRange), delimeter(delim)
    {
        Part<T>::range = get_next(aMaxRange.first);
    }

    range_type get_next(const_iterator start=const_iterator()) const {
        auto next = start == const_iterator() ? Part<T>::end() : start,
             last = next;
        do {
            next = std::find(last, maxRange.second, delimeter);
            // Only push non-empty references
            if (last != next)
                return make_pair(last, next);
            last = next+1;
        } while (next != maxRange.second);
        return make_pair(const_iterator(), const_iterator());
    }
    DelimitedPart<T>& operator++() {
        Part<T>::range = get_next();
        return *this;
    }
    DelimitedPart<T> operator++(int) {
        DelimitedPart<T> result(*this);
        ++(*this);
        return result;
    }
};

template <typename T>
std::ostream& operator <<(std::ostream& out, const Part<T>& s) {
    auto i = s.begin();
    while (i != s.end())
        out << *(i++);
    return out;
}

template <typename T>
DelimitedPart<T> split(const T& whole, typename T::value_type delimeter) {
    return DelimitedPart<T>(make_pair(whole.begin(), whole.end()), delimeter);
}


}
