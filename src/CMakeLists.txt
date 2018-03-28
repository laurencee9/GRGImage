cmake_minimum_required (VERSION 2.6)
project (GRGImage)


# ~~~~~~~~~~~~~~~~~~~~~~~~~
# Check for functionalities 
# ~~~~~~~~~~~~~~~~~~~~~~~~~

# Check for C++ 11 with CMAKE v.2.8 
# Note: there exists a cleaner method in CMAKE 3.1+ [target_compile_features()]
#       but stable Debian distributions tend to distribute CMAKE 2.8 as the default.
#
# Solution found @ http://stackoverflow.com/a/25836953/1851837.

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


add_executable(GRGImage main.cpp)


# Boost
find_package( Boost 1.40 REQUIRED COMPONENTS program_options )
target_link_libraries(GRGImage ${Boost_LIBRARIES})

# Threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(GRGImage Threads::Threads)


# Check for X11 to include CImg.h
# Solution found @ https://stackoverflow.com/questions/38903996/cimg-x11-linking-error-using-clion-and-cmake
message(STATUS "Looking for X11...")
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
target_link_libraries(GRGImage ${X11_LIBRARIES})
SET(CIMG_FLAGS "-lm -lpthread")


find_package(JPEG REQUIRED)
include_directories(${JPEG_INCLUDE_DIR})
target_link_libraries (GRGImage ${JPEG_LIBRARY})
target_compile_definitions(GRGImage PRIVATE cimg_use_jpeg=1)



# ~~~~~~~~~~~~~~~~~~~~~~~~~
# Options
# ~~~~~~~~~~~~~~~~~~~~~~~~~
option(LOGGING 
        "Log input information to std::clog." ON)
# Defaults
set (LOGGING 1)
if (!LOGGING)
  set (LOGGING 0)
endif()

