################################################### CPP ###################################################

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CheckCXXCompilerFlag)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    check_cxx_compiler_flag(-std=c++20 SUPPORTS_CXX20)
    if(NOT SUPPORTS_CXX20)
        message(FATAL_ERROR "Compiler doesn't support C++20")
    endif()
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

################################################### Fetch Content ###################################################

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


################################################### FASTDDS ###################################################

include(${SKYFRAME_ROOT}/src/common/CMake/external_foonathan_memory.cmake)
include(${SKYFRAME_ROOT}/src/common/CMake/external_fastdds.cmake)


#if(NOT fastcdr_FOUND)
#    find_package(fastcdr 2 REQUIRED)
#endif()

#if(NOT fastdds_FOUND)
#    find_package(fastdds 3 REQUIRED)
#endif()