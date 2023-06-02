#include "lib/Algo/Algo.h"
#include "../labwork-8-notoriginallink/lib/CCircularBuffer/CCircularBuffer.h"

#include <gtest/gtest.h>

#include <vector>
#include <list>
#include <string>
#include <functional>

class TestSuiteSTL : public ::testing::Test {
protected:

    CCircularBuffer<int> v1{1, 2, 3, 4, 5, 6, 7};
    CCircularBuffer<double> l1{1.3, 3, -1.2, 6};
    CCircularBuffer<double> v2{3, 5, -7, 0, 1};
    CCircularBuffer<int> l2{2, -4, 6, -10, 8};
    CCircularBuffer<int> v3{1, 1, 1, 1};
    CCircularBuffer<int> v4{1, 2, 3, 2, 1};
    CCircularBuffer<double> l3{1, 1.4, -3, -2, -9.7};

    template<class T>
    struct PositiveNumber : public std::unary_function<T, bool> {
        bool operator()(const T& a) { return a > 0; }
    };

    template<class T>
    struct NegativeNumber : public std::unary_function<T, bool> {
        bool operator()(const T& a) { return a < 0; }
    };

    template<class T>
    struct Zero : public std::unary_function<T, bool> {
        bool operator()(const T& a) {return a == 0; }
    };

    template<class T>
    struct OddNumber : public std::unary_function<T, bool> {
        bool operator()(const T& a) { return (a % 2 == 1); }
    };

    template<class T>
    struct AreEqual : public std::binary_function<T, T, bool> {
        bool operator()(const T& a, const T& b) const { return a == b; }
    };

    template<class T>
    struct LessThan : public std::binary_function<T, T, bool> {
        bool operator()(const T& a, const T& b) { return a < b; }
    };
};

class XRangeSuite : public ::testing::Test {
protected:
    CCircularBuffer<int> v1{2, 4, 6, 8, 10, 12};
    CCircularBuffer<int> v2{7, 8, 9, 10};
    CCircularBuffer<int> v3{0, 1, 2, 3, 4};
    CCircularBuffer<int> v4{-5, -6, -7, -8, -9};
    CCircularBuffer<int> v5{-10, -9, -8, -7, -6};
    CCircularBuffer<int> v6{3, 2, 1, 0, -1, -2};
    CCircularBuffer<double> v7{1, 2, 3, 4, 5};
    CCircularBuffer<double> v8{1.3, 2.3, 3.3};
};

TEST_F(TestSuiteSTL, AllOf) {
    ASSERT_TRUE(algo::all_of(v1.begin(), v1.end(), PositiveNumber<int>()));
    ASSERT_FALSE(algo::all_of(v1.begin(), v1.end(), OddNumber<int>()));
}

TEST_F(TestSuiteSTL, AnyOf) {
    ASSERT_TRUE(algo::any_of(l1.begin(), l1.end(), NegativeNumber<double>()));
    ASSERT_FALSE(algo::any_of(v1.begin(), v1.end(), NegativeNumber<int>()));
}

TEST_F(TestSuiteSTL, NoneOf) {
    ASSERT_TRUE(algo::none_of(l1.begin(), l1.end(), Zero<double>()));
    ASSERT_FALSE(algo::none_of(v2.begin(), v2.end(), Zero<double>()));
}

TEST_F(TestSuiteSTL, OneOf) {
    ASSERT_TRUE(algo::one_of(l1.begin(), l1.end(), NegativeNumber<double>()));
    ASSERT_FALSE(algo::one_of(l2.begin(), l2.end(), NegativeNumber<int>()));
}

TEST_F(TestSuiteSTL, Sorted) {
    ASSERT_TRUE(algo::is_sorted(v1.begin(), v1.end(), std::less()));
    ASSERT_FALSE(algo::is_sorted(l1.begin(), l1.end(), std::less()));
}

TEST_F(TestSuiteSTL, Partioned) {
    ASSERT_TRUE(algo::is_partitioned(l3.begin(), l3.end(), NegativeNumber<double>()));
    ASSERT_FALSE(algo::is_partitioned(l2.begin(), l2.end(), NegativeNumber<int>()));
}

TEST_F(TestSuiteSTL, FindNot) {
    ASSERT_EQ(algo::find_not(v3.begin(), v3.end(), 1), v3.end());
    ASSERT_EQ(*algo::find_not(v2.begin(), v2.end(), 3), 5);
}

TEST_F(TestSuiteSTL, FindBackwards) {
    ASSERT_EQ(algo::find_backwards(l2.begin(), l2.end(), 5), l2.end());
    ASSERT_EQ(algo::find_backwards(v4.begin(), v4.end(), 2), v4.begin() + 3);
}

TEST_F(TestSuiteSTL, Palindrome) {
    ASSERT_TRUE(algo::is_palindrome(l2.begin(), l2.end(), PositiveNumber<int>()));
}

TEST_F(XRangeSuite, BasicCreation) {
    auto x1 = xrange(2, 13, 2);
    auto x2 = xrange(7, 11);
    auto x3 = xrange(5);
    ASSERT_TRUE(std::equal(v1.begin(), v1.end(), x1.begin(), x1.end()));
    ASSERT_TRUE(std::equal(v2.begin(), v2.end(), x2.begin(), x2.end()));
    ASSERT_TRUE(std::equal(v3.begin(), v3.end(), x3.begin(), x3.end()));
}

TEST_F(XRangeSuite, Negative) {
    auto x1 = xrange(-5, -10, -1);
    auto x2 = xrange(-5, -10);
    auto x3 = xrange(-10);
    auto x4 = xrange(-10, -5);
    auto x5 = xrange(3, -3, -1);
    ASSERT_TRUE(std::equal(v4.begin(), v4.end(), x1.begin(), x1.end()));
    ASSERT_EQ(std::distance(x2.begin(), x2.end()), 0);
    ASSERT_EQ(std::distance(x3.begin(), x3.end()), 0);
    ASSERT_TRUE(std::equal(v5.begin(), v5.end(), x4.begin(), x4.end()));
    ASSERT_TRUE(std::equal(v6.begin(), v6.end(), x5.begin(), x5.end()));
}

TEST_F(XRangeSuite, FloatingPoint) {
    auto x1 = xrange(1, 5.5);
    auto x2 = xrange(1.3, 4);
    auto x3 = xrange(0, 2, 0.6);
    ASSERT_TRUE(std::equal(v7.begin(), v7.end(), x1.begin(), x1.end()));
    ASSERT_TRUE(std::equal(v8.begin(), v8.end(), x2.begin(), x2.end()));
}

TEST(ZIPSuite, ZipTest) {
    std::string s = "help";
    CCircularBuffer<double> v{1.3, 8.5, 4};
    XRange<int> x = xrange(1, 7);
    std::string ans1;
    std::string ans2;

    for (auto p : zip(s, v))
        ans1 += p.first + std::to_string(p.second);
    for (auto p : zip(x, s))
        ans2 += std::to_string(p.first) + p.second;

    ASSERT_EQ(ans1, "h1.300000e8.500000l4.000000");
    ASSERT_EQ(ans2, "1h2e3l4p");
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}