# CMake minimum version dependency
cmake_minimum_required( VERSION 3.0.0 FATAL_ERROR )

# Project name
project( "ESys" )

# Compiler and linker flags
set( CPP_COMPILE_FLAGS "-g -Wall -std=c++11" )
set( CPP_LINK_FLAGS "-pthread" )

# Header files locations
include_directories( include )

# Main project library
add_library( esys STATIC
    src/app/SimpleApp.cpp
    src/app/AppContext.cpp
    src/sys/SystemInfo.cpp
    src/sys/VersionInfo.cpp
    src/sys/AbstractThread.cpp
    src/sys/StopWatch.cpp
    src/net/UdpSocket.cpp
    src/net/Datagram.cpp
    src/net/Address.cpp
)

# Demo application: sources
add_executable( esys-demo
    example/main.cpp
)

# Demo application: required libraries
target_link_libraries( esys-demo
    esys
)

# Set the compiler and linker flags for particular targets
set_target_properties( esys PROPERTIES COMPILE_FLAGS ${CPP_COMPILE_FLAGS} )
set_target_properties( esys-demo PROPERTIES COMPILE_FLAGS ${CPP_COMPILE_FLAGS} )
set_target_properties( esys-demo PROPERTIES LINK_FLAGS ${CPP_LINK_FLAGS} )

# Target install
install( TARGETS esys-demo DESTINATION bin )
install( TARGETS esys DESTINATION lib )
install( DIRECTORY 
    include/ DESTINATION include/${CMAKE_PROJECT_NAME}
    FILES_MATCHING PATTERN "*.h" 
)
