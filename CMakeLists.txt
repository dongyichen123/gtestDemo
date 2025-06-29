# cmake_minimum_required(VERSION 3.10.0)
# project(maxDemo VERSION 0.1.0 LANGUAGES C CXX)


# # Debug 模式下的配置（包括覆盖率）
# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#     # 启用调试符号
#     add_compile_options(-g)

#     # 启用 gcov 覆盖率（仅 GCC/Clang）
#     if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#         add_compile_options(--coverage -fprofile-arcs -ftest-coverage)
#         add_link_options(--coverage)
#     endif()
# endif()


# add_executable(maxDemo main.cpp max.cpp)

# include(CTest)
# enable_testing()
# # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

# add_executable(test_max test_max.cpp max.cpp)
# add_subdirectory(googletest)
# target_link_libraries(test_max gtest_main)

cmake_minimum_required(VERSION 3.10.0)
project(maxDemo VERSION 0.1.0 LANGUAGES C CXX)

# 检查是否为 MinGW/GCC
if(WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(STATUS "MinGW/GCC detected - enabling gcov support")
    set(GCOV_SUPPORTED ON)
endif()

# Debug 模式下的配置
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g)
    if(GCOV_SUPPORTED)
        add_compile_options(--coverage -fprofile-arcs -ftest-coverage)
        add_link_options(--coverage)
    endif()
endif()

# 主程序
add_executable(maxDemo main.cpp max.cpp)

# 测试配置
include(CTest)
enable_testing()
add_executable(test_max test_max.cpp max.cpp)
add_subdirectory(googletest)
target_link_libraries(test_max gtest_main)

# 覆盖率报告目标（MinGW/GCC + Debug 模式下）
if(GCOV_SUPPORTED AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    find_program(GCOVR_PATH gcovr)
    if(GCOVR_PATH)
        add_custom_target(coverage
            COMMAND ${GCOVR_PATH}
                --root "${CMAKE_SOURCE_DIR}"
                --object-directory "${CMAKE_BINARY_DIR}/CMakeFiles/test_max.dir"
                --exclude ".*/googletest/.*"
                --html --html-details -o coverage_report.html
                --print-summary  # 可选：在终端显示摘要
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS test_max
            COMMENT "Generating HTML coverage report..."
        )
    endif()
endif()


