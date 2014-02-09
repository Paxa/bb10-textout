cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(TextOut)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

#set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUSING_GL11")

find_package(BBCascades REQUIRED)

set(MRUBY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/mruby)
set(MRUBY_BUILD ${CMAKE_CURRENT_SOURCE_DIR}/mruby/build/blackberry)

include_directories(
    ${PROJECT_SOURCE_DIR}
    /Applications/Momentics.app/target_10_2_0_1155/qnx6/usr/include/freetype2
    ${MRUBY_DIR}/include
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(TextOut_SRCS
    ../src/main.cpp
    ../src/textoutapp.h
    ../src/textoutapp.cpp
    ../src/mruby_runner.h
    ../src/mruby_runner.cpp
)

#execute_process(COMMAND rm -rf Device-Debug; mkdir Device-Debug)

add_executable(TextOut ${TextOut_SRCS})

message(STATUS ${MRUBY_DIR})

target_link_libraries(
    TextOut

    m
    freetype
    ${QT_QTCORE_LIBRARY}
    ${QT_QTNETWORK_LIBRARY}
    ${QT_QTXML_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTDECLARATIVE_LIBRARY}
    ${MRUBY_BUILD}/lib/libmruby.a
    ${MRUBY_BUILD}/lib/libmruby_core.a
    ${BBCASCADES_LIBRARY}
)
