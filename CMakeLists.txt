cmake_minimum_required(VERSION 3.5.0)
project(run VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(run main.cpp)
target_link_libraries(
    run PUBLIC
    /usr/lib/libglut.so.3
    /usr/lib/libOpenGL.so.0
    /usr/lib/libglfw.so.3.3
    /usr/lib/libGLEW.so.2.2
    /usr/lib/libdecor/plugins-1/libdecor-gtk.so
)
################################################
set(INCLUDE_ROOT_FOLDER "/usr/include")

target_include_directories(
    run PUBLIC
    ${INCLUDE_ROOT_FOLDER}/GL
    ${INCLUDE_ROOT_FOLDER}/GLFW
    ${INCLUDE_ROOT_FOLDER}/libdecor-0
    ${INCLUDE_ROOT_FOLDER}
)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
