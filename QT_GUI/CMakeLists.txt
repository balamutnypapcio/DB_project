cmake_minimum_required(VERSION 3.19)
project(bazy_danych_v3 LANGUAGES CXX)

# Dodaj moduł SQL do wymaganych komponentów Qt
# find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql)
find_package(Qt6 6.9 COMPONENTS Core Widgets Sql QUIET)

qt_standard_project_setup()

qt_add_executable(bazy_danych_v3
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    group.h
    group.cpp
    Database.h
    Database.cpp
    expensebutton.h
    balancebutton.h
)

target_link_libraries(bazy_danych_v3
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
)

include(GNUInstallDirs)

install(TARGETS bazy_danych_v3
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET bazy_danych_v3
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
