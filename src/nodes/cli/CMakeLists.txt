cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(skyframe_cli)

set(SKYFRAME_ROOT ../../..)
include(FetchContent)

include(FetchContent)
FetchContent_Declare(
  toml11
  GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
  GIT_TAG        v4.4.0
)
FetchContent_MakeAvailable(toml11)


FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog
  GIT_TAG        v1.15.3
)
FetchContent_MakeAvailable(spdlog)



if(NOT fastcdr_FOUND)
    find_package(fastcdr 2 REQUIRED)
endif()

if(NOT fastdds_FOUND)
    find_package(fastdds 3 REQUIRED)
endif()


file(GLOB SKYFRAME_STRING_MESSAGE_CXX "${SKYFRAME_ROOT}/src/message_types/string_message/*.cxx")

include(CheckCXXCompilerFlag)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    check_cxx_compiler_flag(-std=c++20 SUPPORTS_CXX20)
    if(NOT SUPPORTS_CXX20)
        message(FATAL_ERROR "Compiler doesn't support C++20")
    endif()
endif()

add_definitions(-DPROJECT_NAME=${PROJECT_NAME} )

add_executable(${PROJECT_NAME} 
    main.cpp
    cli_node.cpp
    cli.cpp
    ${SKYFRAME_STRING_MESSAGE_CXX}
    ${SKYFRAME_ROOT}/src/common/PubListener.cpp
    ${SKYFRAME_ROOT}/src/common/config.cpp

)

target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT_NAME_STRING=\"${PROJECT_NAME}\")

target_include_directories(${PROJECT_NAME} PRIVATE ${SKYFRAME_ROOT}/src/message_types)

target_link_libraries(${PROJECT_NAME} fastdds fastcdr toml11::toml11 spdlog)


# Needs a check here to see if linux :D

configure_file(${SKYFRAME_ROOT}/src/config/service_template.service ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}@.service)
configure_file(${SKYFRAME_ROOT}/src/config/service_template.service ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.service)

install(TARGETS ${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}@.service
        DESTINATION /etc/systemd/system)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.service
        DESTINATION /etc/systemd/system)

install(FILES skyframe_cli.toml
        RENAME default.toml
        DESTINATION /usr/local/etc/${PROJECT_NAME}/)
