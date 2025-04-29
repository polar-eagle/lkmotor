cmake_minimum_required(VERSION 3.30)
project(lkmotor)

set(CMAKE_CXX_STANDARD 17)

add_executable(lkmotor src/main.cpp
        src/gcan.h
        src/gcan.cpp
        src/lkmotor.cpp
        src/lkmotor.h
        src/command.h)

# 设置包含目录 - 让编译器能找到头文件
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libs)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
# 设置库目录 - 让链接器能找到.lib文件
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libs)

# 链接库文件
target_link_libraries(${PROJECT_NAME} PRIVATE ECanVci64.lib)

# Windows平台特定设置：复制DLL到输出目录
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/libs/ECanVci64.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()