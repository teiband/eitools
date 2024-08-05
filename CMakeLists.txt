cmake_minimum_required(VERSION 3.5)

# CMake instructions to make the static lib

ADD_LIBRARY( EiTools STATIC
             eitools.cpp
             datautils.cpp
             signalfilters.cpp)


# CMake instructions to test using the static lib

SET( APP_EXE StaticTest )

ADD_EXECUTABLE( ${APP_EXE}
                main.cpp )

SET( EITOOLS_LIB_PATH ${CMAKE_SOURCE_DIR}/build/)
LINK_DIRECTORIES( EITOOLS_LIB_PATH)

TARGET_LINK_LIBRARIES( ${APP_EXE}
                       EiTools )
