################################################### CPP ###################################################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CheckCXXCompilerFlag)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    check_cxx_compiler_flag(-std=c++17 SUPPORTS_CXX17)
    if(NOT SUPPORTS_CXX17)
        message(FATAL_ERROR "Compiler doesn't support C++17")
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

# So, you //can// install fastdds via the following cmake files, however it's a complete PITA
# I'd just use the binaries you can install from fastdds
include(${SKYFRAME_ROOT}/src/common/CMake/external_foonathan_memory.cmake)
include(${SKYFRAME_ROOT}/src/common/CMake/external_fastdds.cmake)


#if(NOT fastcdr_FOUND)
#    find_package(fastcdr 2 REQUIRED)
#endif()
#
#if(NOT fastdds_FOUND)
#    find_package(fastdds 3 REQUIRED)
#endif()