cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For IntelliSense in VS Code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(RecordManagementSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Explicitly list sources so CMake always sees them
set(SOURCES
    src/main.cpp
    src/Book.cpp
    src/FileStorage.cpp
    src/RecordManager.cpp
    src/Menu.cpp
    src/Utils.cpp
)

add_executable(RecordManagementSystem ${SOURCES})

target_include_directories(RecordManagementSystem PRIVATE src)

# Optional: if you use VS (or just for reference), set working dir to project root
set_property(TARGET RecordManagementSystem PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
