cmake_minimum_required(VERSION 3.14.0)
set(CMAKE_CXX_STANDARD 17)

project(EasyLuaSample)

include(FetchContent)
include(CTest)

if(APPLE)
    SET(PROJECT_OS_MACOS TRUE BOOL INTERNAL)
    SET(BUILD_PLATFORM MACOS)
elseif(WIN32)
    SET(PROJECT_OS_WIN32 TRUE BOOL INTERNAL)
    SET(BUILD_PLATFORM WIN32)
elseif(ANDROID)
    SET(PROJECT_OS_ANDROID TRUE BOOL INTERNAL)
elseif(UNIX AND NOT APPLE)
    SET(PROJECT_OS_LINUX TRUE BOOL INTERNAL)
endif()

add_definitions (-DPROJECT_TARGET_OS_${BUILD_PLATFORM} )

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

file(GLOB_RECURSE PROJECT_LIB_SOURCES 
    ${PROJECT_SOURCE_DIR}/easyLuaLib/*.c
)

file(GLOB_RECURSE PROJECT_LIB_SOURCES_CPP
    ${PROJECT_SOURCE_DIR}/easyLuaLib/*.cpp
)

list(APPEND PROJECT_LIB_SOURCES ${PROJECT_LIB_SOURCES_CPP})

file(GLOB_RECURSE PROJECT_SAMPLE_SOURCES 
    ${PROJECT_SOURCE_DIR}/easyLuaSample/*.cpp
)

list(APPEND PROJECT_SAMPLE_SOURCES ${PROJECT_LIB_SOURCES})


set(EASY_LUA_HEADER_DIRS
easyLuaLib/sys
easyLuaLib/utils
easyLuaLib/wrapper
easyLuaLib/vendors/lua
easyLuaLib/vendors/eris
easyLuaLib/vendors/luaBridge)
foreach(DIR ${EASY_LUA_HEADER_DIRS})
    include_directories(${PROJECT_SOURCE_DIR}/${DIR})
endforeach(DIR)

if(PROJECT_OS_MACOS)
    list (APPEND PROJECT_SAMPLE_SOURCES ${PROJECT_SOURCE_DIR}/compat/mac/mac_fileManager.mm)
    list (APPEND PROJECT_SAMPLE_SOURCES ${PROJECT_SOURCE_DIR}/compat/mac/mac_fileManager.h)
    include_directories(${PROJECT_SOURCE_DIR}/compat/mac)
elseif(PROJECT_OS_WIN32)
    list (APPEND PROJECT_SAMPLE_SOURCES ${PROJECT_SOURCE_DIR}/compat/win/windows_fileManager.cpp)
    list (APPEND PROJECT_SAMPLE_SOURCES ${PROJECT_SOURCE_DIR}/compat/win/windows_fileManager.h)
    include_directories(${PROJECT_SOURCE_DIR}/compat/win)
elseif(PROJECT_OS_ANDROID)

elseif(PROJECT_OS_LINUX)

endif()


# setup targets
#add_library(easyLua STATIC ${PROJECT_LIB_SOURCES})
#target_compile_definitions(easyLua PRIVATE LUA_BUILD_AS_DLL)
#target_compile_definitions(easyLua PRIVATE LUA_CORE)


add_executable(${PROJECT_NAME} ${PROJECT_SAMPLE_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/easyLuaSample)

# copy files
macro(copy_files TARGET_NAME SRC_DIR DST_DIR)
    file(GLOB_RECURSE RESOURCE_FILES ${SRC_DIR}/* )

    unset(OUT_RESOURCE_FILES)
    foreach(RES_FILE ${RESOURCE_FILES})
        file(RELATIVE_PATH RES_FILE_RELPATH ${SRC_DIR} ${RES_FILE})
        set(OUT_RES_FILE ${DST_DIR}/${RES_FILE_RELPATH})
        add_custom_command( OUTPUT ${OUT_RES_FILE}
                            COMMAND ${CMAKE_COMMAND} -E copy ${RES_FILE} ${OUT_RES_FILE}
                            DEPENDS ${RES_FILE})
        list(APPEND OUT_RESOURCE_FILES ${OUT_RES_FILE})
    endforeach()

    add_custom_target(${TARGET_NAME} ALL DEPENDS ${OUT_RESOURCE_FILES})
endmacro()

copy_files(${PROJECT_NAME}_copy_data ${CMAKE_CURRENT_SOURCE_DIR}/easyLuaSample/Resources ${CMAKE_BINARY_DIR}/Resources)
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_copy_data)
