/**
 * Mimics a read-only string (or other container), but actually just uses two read-only iterators into another string by reference to save on copying.
 *
 **/
#pragma once

#include <functional>
#include <algorithm>
#include <vector>

namespace wittyPlus {

template<typename T>
struct SubDivided {
    typedef typename T::const_iterator const_iterator;
    typedef typename T::value_type value_type;
    const T& original;
    typename T::const_iterator _begin,
                               _end;
    const_iterator begin() const { return _begin; }
    const_iterator end() const { return _end; }
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
        while ((first1 != last1) && (first2 != last2)) {
            if (!pred(*(first1++), *(first2++)))
                return false;
        }
        return true;
    }
    template <typename T2>
    bool operator ==(const T2& other) const { return compare(other, [](value_type a, typename T2::value_type b){ return a == b; }); }
    template <typename T2>
    bool operator ==(const T2* other) const { return compare<T2>(other, [](value_type a, T2 b){ return a == b; }); }

    template <typename T2>
    bool operator !=(const T2& other) const { return compare(other, [](value_type a, typename T2::value_type b){ return a != b; }); }
    template <typename T2>
    bool operator !=(const T2* other) const { return compare<T2>(other, [](value_type a, T2 b){ return a != b; }); }

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

bool operator !=(const char* a, const SubDivided<std::string>& b) {
    return !(b == a);
}

template <typename T>
std::ostream& operator <<(std::ostream& out, const SubDivided<T>& s) {
    auto i = s.begin();
    while (i != s.end())
        out << *(i++);
    return out;
}

template<typename T>
std::vector<SubDivided<T>> split(const T& input, typename T::value_type delimeter) {
    /// Turns "/path/to/somewhere" into {"path", "to", "somewhere"}
    std::vector<SubDivided<T>> result;
    auto last = input.begin();
    decltype(last) next;
    do {
        next = std::find(last, input.end(), delimeter);
        // Only push non-empty references
        if (last != next)
            result.push_back(SubDivided<T>{input, last, next});
        last = next+1;
    } while (next != input.end());
    return result;
}

}
