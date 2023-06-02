#pragma once

#include <iostream>
#include <concepts>

namespace algo {
    template<class T>
    concept InputIteratorConcept = std::convertible_to<typename std::iterator_traits<T>::iterator_category, std::input_iterator_tag>;

    template<class T>
    concept ForwardIteratorConcept = std::convertible_to<typename std::iterator_traits<T>::iterator_category, std::forward_iterator_tag>;

    template<class T>
    concept BidirectionalIteratorConcept = std::convertible_to<typename std::iterator_traits<T>::iterator_category, std::bidirectional_iterator_tag>;

    template<InputIteratorConcept InputIter, class UnaryPredicate>
        requires std::predicate<UnaryPredicate, typename InputIter::value_type>
    bool all_of(InputIter start, InputIter end, UnaryPredicate predicate) {
        for (; start != end; ++start)
            if (!predicate(*start)) return false;

        return true;
    }

    template<InputIteratorConcept InputIter, typename UnaryPredicate>
        requires std::predicate<UnaryPredicate, typename InputIter::value_type>
    bool any_of(InputIter start, InputIter end, UnaryPredicate predicate) {
        for (; start != end; ++start)
            if (predicate(*start)) return true;

        return false;
    }

    template<InputIteratorConcept InputIter, typename UnaryPredicate>
        requires std::predicate<UnaryPredicate, typename InputIter::value_type>
    bool none_of(InputIter start, InputIter end, UnaryPredicate predicate) {
        return !algo::any_of(start, end, predicate);
    }

    template<InputIteratorConcept InputIter, typename UnaryPredicate>
        requires std::predicate<UnaryPredicate, typename InputIter::value_type>
    bool one_of(InputIter start, InputIter end, UnaryPredicate predicate) {
        int cnt = 0;
        for (; start != end && cnt < 2; ++start)
            if (predicate(*start)) cnt++;

        return cnt == 1;
    }

    template<ForwardIteratorConcept ForwardIterator, typename Compare>
        requires std::predicate<Compare, typename ForwardIterator::value_type, typename ForwardIterator::value_type>
    bool is_sorted(ForwardIterator start, ForwardIterator end, Compare comp) {
        auto first = start;
        ++start;
        for (; start != end; first = start, ++start)
            if (!comp(*first, *start)) return false;

        return true;
    }

    template<InputIteratorConcept InputIter, typename UnaryPredicate>
        requires std::predicate<UnaryPredicate, typename InputIter::value_type>
    bool is_partitioned(InputIter start, InputIter end, UnaryPredicate predicate) {
        bool fl = false;
        for (; start != end; ++start) {
            if (predicate(*start))
                fl = true;
            else
                if (fl) return false;
        }

        return fl;
    }

    template<InputIteratorConcept InputIter, typename T>
    InputIter find(InputIter start, InputIter end, const T& x) {
        for (; start != end; ++start) {
            if (*start == x)
                return start;
        }

        return end;
    }

    template<InputIteratorConcept InputIter, typename T>
    InputIter find_not(InputIter start, InputIter end, const T& x) {
        for (; start != end; ++start) {
            if (*start != x)
                return start;
        }

        return end;
    }

    template<BidirectionalIteratorConcept BidirectionalIter, typename T>
    BidirectionalIter find_backwards(BidirectionalIter start, BidirectionalIter end, const T& x) {
        for (BidirectionalIter cur = end; cur != start; --cur)
            if (*cur == x) return cur;

        return end;
    }

    template<BidirectionalIteratorConcept BidirectionalIter, typename UnaryPredicate>
        requires std::predicate<UnaryPredicate, typename BidirectionalIter::value_type>
    bool is_palindrome(BidirectionalIter start, BidirectionalIter end, UnaryPredicate predicate) {
        --end;
        for (BidirectionalIter end_ = end++; start != end; ++start, --end_)
            if (predicate(*start) != predicate(*end_)) return false;

        return true;
    }
}
