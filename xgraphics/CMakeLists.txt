cmake_minimum_required(VERSION 3.10)
project(discomplexity)

include_directories(./src/core
                    ./homeworld2/core)

# set(CMAKE_CXX_FLAGS "-Wall -Wextra")
# set(CMAKE_CXX_FLAGS_DEBUG "-O3")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/core)
add_subdirectory(homeworld2/core)
add_subdirectory(xSpace/core)

# add_subdirectory(sample/core)
