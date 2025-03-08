cmake_minimum_required(VERSION 3.19)
project(AGUniverse LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(AGUniverse
    WIN32 MACOSX_BUNDLE
    main.cpp
    login.cpp
    login.h
    login.ui

    registerpage.h registerpage.cpp registerpage.ui
    main_menu.ui
)

target_link_libraries(AGUniverse
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS AGUniverse
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET AGUniverse
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
