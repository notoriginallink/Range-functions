#pragma once

#include <iostream>
#include <concepts>

template<class Container>
concept IterableContainer = requires (Container c)
        { c.begin(); c.end(); std::convertible_to<typename std::iterator_traits<typename Container::iterator>::iterator_category, std::input_iterator_tag>;};

template<IterableContainer Container1, IterableContainer Container2>
class ZIP {
public:
    using T = Container1::value_type;
    using U = Container2::value_type;

    class Iterator : std::iterator<std::input_iterator_tag, std::pair<T, U>> {
    public:
        using value_type = std::pair<T, U>;
        using reference = std::pair<T,U>&;
        using pointer = std::pair<T, U>*;
        using iterator1 = Container1::iterator;
        using iterator2 = Container2::iterator;

        Iterator() = delete;
        Iterator(iterator1 p1, iterator2 p2) : ptr1_(p1), ptr2_(p2) {}
        Iterator(const Iterator& other) = default;
        Iterator& operator=(const Iterator& other) = default;

        Iterator& operator++() {
            ++ptr1_;
            ++ptr2_;

            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);

            return tmp;
        }

        value_type operator*() {
            T temp1 = *ptr1_;
            U temp2 = *ptr2_;

            return std::pair<T, U>{temp1, temp2};
        }

        bool operator==(const Iterator& other) { return ptr1_ == other.ptr1_ || ptr2_ == other.ptr2_; }
        bool operator!=(const Iterator& other) { return !(*this == other); }
    private:
        iterator1 ptr1_;
        iterator2 ptr2_;
    };

    ZIP() = delete;
    ZIP(Container1& c1, Container2& c2) : ptr1_(&c1), ptr2_(&c2) {}

    Iterator begin() { return Iterator(ptr1_->begin(), ptr2_->begin()); }

    Iterator end() { return Iterator(ptr1_->end(), ptr2_->end()); }

    template<class C1, class C2>
    friend ZIP<C1, C2> zip(C1& container1, C2& container2);
private:
    Container1* ptr1_;
    Container2* ptr2_;
};

template<class C1, class C2>
ZIP<C1, C2> zip(C1& container1, C2& container2) { return ZIP<C1, C2>(container1, container2); }
