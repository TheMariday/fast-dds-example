cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(ps_test)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        pocketsphinx
        GIT_REPOSITORY https://github.com/themariday/pocketsphinx.git
)
FetchContent_MakeAvailable(pocketsphinx)

target_include_directories(pocketsphinx PUBLIC ${pocketsphinx_SOURCE_DIR}/src)
target_include_directories(pocketsphinx PUBLIC ${pocketsphinx_SOURCE_DIR}/include)
target_include_directories(pocketsphinx PUBLIC ${pocketsphinx_BINARY_DIR})
target_include_directories(pocketsphinx PUBLIC ${pocketsphinx_BINARY_DIR}/include)
target_include_directories(pocketsphinx PRIVATE ${pocketsphinx_SOURCE_DIR}/src/util)


add_executable(${PROJECT_NAME} simple.c)
target_link_libraries(${PROJECT_NAME} pocketsphinx)

target_compile_definitions(${PROJECT_NAME} PRIVATE MODELDIR_STRING=\"${pocketsphinx_SOURCE_DIR}/model/en-us/")
