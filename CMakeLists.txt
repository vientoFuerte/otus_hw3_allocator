cmake_minimum_required(VERSION 3.12)


project(allocator)

option(WITH_BOOST_TEST "Whether to build Boost test" ON)


add_executable(allocator main.cpp)


set_target_properties(allocator PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)


endif()

if (MSVC)
    target_compile_options(allocator PRIVATE
        /W4
    )
    
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror -Wunused -Wunused-variable -Wunused-parameter
    )
endif()

target_compile_definitions(allocator PRIVATE 
    $<$<CONFIG:Debug>:ENABLE_DEBUG_LOGGING>
    $<$<CONFIG:RelWithDebInfo>:ENABLE_DEBUG_LOGGING>
)

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    #add_test(test_version test_version)
endif()
