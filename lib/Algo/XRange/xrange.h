#pragma once

#include <iostream>
#include <concepts>

template<typename T>
concept RangeIterable = requires (T item, T x) { ++item; item + x; item > x; item == x; item > 0; item < 0; };

template<RangeIterable T>
    requires std::copyable<T>
class XRange {
public:
    class Iterator : public std::iterator<std::input_iterator_tag, T> {
    public:
        using value_type = T;
        using reference = typename std::iterator_traits<Iterator>::reference;
        using pointer = typename std::iterator_traits<Iterator>::pointer;
        using difference_type = typename std::iterator_traits<Iterator>::difference_type;

        Iterator() = delete;
        Iterator(const value_type& current, const value_type& end, const value_type& step) : current_(current), end_(end), step_(step) {
            if ((end_ > current_ && step_ < 0) || (end_ < current_ && step_ > 0))
                current_ = end_;
        }

        Iterator& operator++() {
            if (step_ == 1)
                ++current_;
            else
                current_ += step_;
            if ((step_ > 0 && current_ >= end_) || (step_ < 0 && current_ <= end_))
                current_ = end_;

            return *this;
        }

        Iterator operator++(int) const {
            Iterator tmp = *this;
            ++(*this);

            return tmp;
        }

        reference operator*() { return current_; }
        pointer operator->() { return *this; }

        bool operator==(const Iterator& other) const {
            return end_ == other.end_ && step_ == other.step_ && current_ == other.current_;
        }
        bool operator!=(const Iterator& other) { return !(*this == other); }

    private:
        value_type end_;
        value_type step_;
        value_type current_;
    };
    using value_type = T;
    using iterator = Iterator;

    XRange() = delete;
    XRange(T start, T end, T step) : start_(start), end_(end), step_(step) {}

    Iterator begin() { return Iterator(start_, end_, step_); }
    Iterator end() { return Iterator(end_, end_, step_); }

    template<RangeIterable U1, RangeIterable U2, RangeIterable U3>
    friend XRange<std::common_type_t<U1, U2, U3>> xrange(U1 start, U2 end, U3 step);

    template<RangeIterable U1, RangeIterable U2>
    friend XRange<std::common_type_t<U1, U2>> xrange(U1 start, U2 end);

    template<RangeIterable U>
    friend XRange<U> xrange(U end);
private:
    T start_;
    T end_;
    T step_;
};

template<RangeIterable U1, RangeIterable U2, RangeIterable U3>
XRange<std::common_type_t<U1, U2, U3>> xrange(U1 start, U2 end, U3 step) { return XRange<std::common_type_t<U1, U2, U3>>(start, end, step); }

template<RangeIterable U1, RangeIterable U2>
XRange<std::common_type_t<U1, U2>> xrange(U1 start, U2 end) { return XRange<std::common_type_t<U1, U2>>(start, end, static_cast<std::common_type_t<U1, U2>>(1)); }

template<RangeIterable U>
XRange<U> xrange(U end) { return XRange<U>(static_cast<U>(0), end, static_cast<U>(1)); }
