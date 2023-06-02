include(FetchContent)
FETCHCONTENT_DECLARE(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

#For Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable( Test test.cpp )
target_link_libraries( Test PRIVATE Algo GTest::gtest_main )
target_include_directories(Test PUBLIC ${PROJECT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(Test)