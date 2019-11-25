# CMake instructions to make the static lib

ADD_LIBRARY( EiTools STATIC
             eitools.cpp
             datautils.cpp)


# CMake instructions to test using the static lib

SET( APP_EXE StaticTest )

ADD_EXECUTABLE( ${APP_EXE}
                main.cpp )

TARGET_LINK_LIBRARIES( ${APP_EXE}
                       EiTools )
