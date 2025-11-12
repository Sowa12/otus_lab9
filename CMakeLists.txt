cmake_minimum_required(VERSION 3.10.0)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch Version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(async VERSION ${PROJECT_VERSION} LANGUAGES C CXX)
project(async_bin VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

option(WITH_GTEST_TEST "Whether to build GTEST test" ON)

configure_file(version.h.in version.h)

add_library(async SHARED
    src/bulk.cpp
    src/printer.cpp
    src/parser.cpp
    src/async.cpp
    src/parsermanager.cpp
    src/printerdispatcher.cpp
)

target_include_directories(async PUBLIC include/)

add_executable(async_bin
    src/main.cpp
)

target_link_libraries(async_bin PRIVATE async)
target_include_directories(async_bin PUBLIC include/)

if(WITH_GTEST_TEST) 
    find_package(GTest REQUIRED)
    
    add_executable(async_test 
        tests/bulk_test.cpp
        #src/main.cpp
    )

    target_include_directories(async_test PUBLIC
        include/
    )

    set_target_properties(async_test PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(async_test GTest::GTest async)

    find_package(GTest REQUIRED)
endif()

if (MSVC)
    target_compile_options(async PRIVATE
        /W4
    )

else ()
    target_compile_options(async PRIVATE
        -Wall -Wextra -pedantic -Werror
    )

    if(WITH_GTEST_TEST)
    target_compile_options(async_test PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    endif()
endif()

install(TARGETS async LIBRARY DESTINATION usr/lib)
install(TARGETS async_bin LIBRARY DESTINATION usr/bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_GTEST_TEST)
    enable_testing()
    add_test(async_test async_test)
endif()