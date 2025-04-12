cmake_minimum_required(VERSION 3.14)
project(SqlLoginApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Ustaw standard C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Znajdź pakiety Qt
find_package(Qt5 COMPONENTS Core Gui Widgets Sql REQUIRED)

# Pliki źródłowe
set(SOURCES
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/GroupsWindow.cpp
        ${CMAKE_SOURCE_DIR}/src/LoginWindow.cpp
)

# Pliki nagłówkowe
set(HEADERS
        ${CMAKE_SOURCE_DIR}/inc/GroupsWindow.h
        ${CMAKE_SOURCE_DIR}/inc/LoginWindow.h
)

# Dodaj aplikację
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Podlinkuj biblioteki Qt
target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
)

# Dodaj katalogi nagłówków
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/inc)
