cmake_minimum_required(VERSION 3.12)

project(allocator)

option(WITH_TESTS "Build tests" ON)

add_executable(allocator main.cpp)

set_target_properties(allocator PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# 3. Тест (если файл test.cpp существует)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
    # Ищем установленный gtest
    find_package(GTest REQUIRED)
    
    # Тестовый исполняемый файл
    add_executable(allocator_tests test.cpp)

     # УСТАНОВКА СТАНДАРТА C++ для тестов тоже
    set_target_properties(allocator_tests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )
    
    # Линкуем с системным gtest
    target_link_libraries(allocator_tests PRIVATE GTest::gtest GTest::gtest_main)
    
    # Тесты
    enable_testing()
    add_test(NAME AllTests COMMAND allocator_tests)
else()
    message(WARNING "test.cpp not found, tests will not be built")
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


