cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(TextOut)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src)

# Find includes in corresponding build directories
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUSING_GL11")

find_package(BBCascades REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}
    /Applications/Momentics.app/target_10_2_0_1155/qnx6/usr/include/freetype2
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#include_directories( ${CMAKE_SOURCE_DIR}/../src )

set(TextOut_SRCS
    ../src/main.cpp
    ../src/textoutapp.h
    ../src/textoutapp.cpp
)

#set(HEADER_FILES ${PROJECT_SOURCE_DIR}/textoutapp.h)

execute_process(COMMAND rm -rf Device-Debug; mkdir Device-Debug)

#message(STATUS ${PROJECT_SOURCE_DIR})

add_executable(TextOut ${TextOut_SRCS})

target_link_libraries(
    TextOut

    freetype
    ${QT_QTCORE_LIBRARY}
    ${QT_QTNETWORK_LIBRARY}
    ${QT_QTXML_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTDECLARATIVE_LIBRARY}

    ${BBCASCADES_LIBRARY}
)
