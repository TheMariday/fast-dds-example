cmake_minimum_required(VERSION 3.25)

project(skyframe_cli)

set(SKYFRAME_ROOT ../../..)

include(${SKYFRAME_ROOT}/src/common/CMake/common_dependencies.cmake)

file(GLOB SKYFRAME_STRING_MESSAGE_CXX "${SKYFRAME_ROOT}/src/message_types/string_message/*.cxx")


add_executable(${PROJECT_NAME} 
    main.cpp
    cli_node.cpp
    cli.cpp
    ${SKYFRAME_STRING_MESSAGE_CXX}
)

target_include_directories(${PROJECT_NAME} PRIVATE 
${SKYFRAME_ROOT}/src/message_types
${SKYFRAME_ROOT}/src/common
)

target_link_libraries(${PROJECT_NAME} fastdds fastcdr toml11::toml11 spdlog)

include(${SKYFRAME_ROOT}/src/common/CMake/install_node.cmake)
