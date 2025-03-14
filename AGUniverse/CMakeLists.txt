cmake_minimum_required(VERSION 3.19)
project(AGUniverse LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(AGUniverse
    WIN32 MACOSX_BUNDLE

    # Source files in the root folder
    main.cpp

    # Presentation Layer
    presentationLayer/login.cpp
    presentationLayer/login.h
    presentationLayer/login.ui

    presentationLayer/registerpage.cpp
    presentationLayer/registerpage.h
    presentationLayer/registerpage.ui

    presentationLayer/main_menu.cpp
    presentationLayer/main_menu.h
    presentationLayer/main_menu.ui

    presentationLayer/profile.cpp
    presentationLayer/profile.h
    presentationLayer/profile.ui

    # Data Access Layer
    dataAccessLayer/database.cpp
    dataAccessLayer/database.h
    dataAccessLayer/users.txt
    resources.qrc
    presentationLayer/exams.ui
    presentationLayer/exams.cpp
)

install(FILES dataAccessLayer/users.txt DESTINATION ${CMAKE_INSTALL_BINDIR})

target_link_libraries(AGUniverse
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

set(AGUniverse_resource_files
    "assets/images/exams_icon.png"
    "assets/images/results_icon.png"
    "assets/images/program_icon.png"
    "assets/images/inbox_icon.png"
    "assets/images/profile.icon.png"
    "assets/images/log_out_icon.png"
    "assets/images/Test_logo_2.png"
    "assets/images/Logo1.png"
)

qt_add_resources(AGUniverse "AGUniverse"
    PREFIX
        "/"
    FILES
        ${AGUniverse_resource_files}
)

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
