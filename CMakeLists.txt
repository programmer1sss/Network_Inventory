cmake_minimum_required(VERSION 3.16)
project(NetworkInventory LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Опції ──
option(ENABLE_SANITIZERS "Build with ASan and UBSan" OFF)

# ── Спільні попередження ──
set(PROJECT_WARNINGS -Wall -Wextra -Wpedantic)

# ── Допоміжна функція ──
function(apply_warnings_and_sanitizers target)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target} PRIVATE ${PROJECT_WARNINGS} -g)
        if(ENABLE_SANITIZERS)
            target_compile_options(${target} PRIVATE
                -fsanitize=address,undefined
                -fno-omit-frame-pointer -g
            )
            target_link_options(${target} PRIVATE
                -fsanitize=address,undefined
            )
        endif()
    endif()
endfunction()

# ════════════════════════════════════════════════════════════════
#  ОСНОВНА ПРОГРАМА (Демо)
# ════════════════════════════════════════════════════════════════

# Головна програма (main.cpp + реалізації)
add_executable(network_inventory
    src/main.cpp
    src/Server.cpp
    src/ServiceList.cpp
)
target_include_directories(network_inventory PRIVATE src)
apply_warnings_and_sanitizers(network_inventory)


# ════════════════════════════════════════════════════════════════
#  ТЕСТИ (GoogleTest)
# ════════════════════════════════════════════════════════════════
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Тест ServiceList (Rule of Five)
add_executable(servicelist_test 
    tests/servicelist_test.cpp
    src/ServiceList.cpp
)
target_include_directories(servicelist_test PRIVATE src)
target_link_libraries(servicelist_test PRIVATE GTest::gtest_main)
apply_warnings_and_sanitizers(servicelist_test)

# Тест ServiceListV2 (Rule of Zero, header-only)
add_executable(servicelistv2_test 
    tests/servicelistv2_test.cpp
)
target_include_directories(servicelistv2_test PRIVATE src)
target_link_libraries(servicelistv2_test PRIVATE GTest::gtest_main)
apply_warnings_and_sanitizers(servicelistv2_test)

# Тест Server (вбудований ServiceList)
add_executable(server_test 
    tests/server_test.cpp
    src/Server.cpp
    src/ServiceList.cpp
)
target_include_directories(server_test PRIVATE src)
target_link_libraries(server_test PRIVATE GTest::gtest_main)
apply_warnings_and_sanitizers(server_test)

# Реєстрація тестів у CTest
include(GoogleTest)
gtest_discover_tests(servicelist_test)
gtest_discover_tests(servicelistv2_test)
gtest_discover_tests(server_test)