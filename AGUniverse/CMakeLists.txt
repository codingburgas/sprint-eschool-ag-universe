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

    presentationLayer/exams.cpp
    presentationLayer/exams.h
    presentationLayer/exams.ui

    presentationLayer/maths.cpp
    presentationLayer/maths.h
    presentationLayer/maths.ui

    presentationLayer/geometry.cpp
    presentationLayer/geometry.h
    presentationLayer/geometry.ui

    presentationLayer/algebra.cpp
    presentationLayer/algebra.h
    presentationLayer/algebra.ui

    presentationLayer/algebraExam1.cpp
    presentationLayer/algebraExam1.h
    presentationLayer/algebraExam1.ui

    presentationLayer/algebraExam2.cpp
    presentationLayer/algebraExam2.h
    presentationLayer/algebraExam2.ui

    presentationLayer/algebraExam3.cpp
    presentationLayer/algebraExam3.h
    presentationLayer/algebraExam3.ui

    presentationLayer/geometryExam1.cpp
    presentationLayer/geometryExam1.h
    presentationLayer/geometryExam1.ui

    presentationLayer/geometryExam2.cpp
    presentationLayer/geometryExam2.h
    presentationLayer/geometryExam2.ui

    presentationLayer/geometryExam3.cpp
    presentationLayer/geometryExam3.h
    presentationLayer/geometryExam3.ui

    presentationLayer/english.cpp
    presentationLayer/english.h
    presentationLayer/english.ui

    presentationLayer/grammar.cpp
    presentationLayer/grammar.h
    presentationLayer/grammar.ui

    presentationLayer/grammarExam1.cpp
    presentationLayer/grammarExam1.h
    presentationLayer/grammarExam1.ui

    presentationLayer/grammarExam2.cpp
    presentationLayer/grammarExam2.h
    presentationLayer/grammarExam2.ui

    presentationLayer/grammarExam3.cpp
    presentationLayer/grammarExam3.h
    presentationLayer/grammarExam3.ui

    presentationLayer/vocabulary.cpp
    presentationLayer/vocabulary.h
    presentationLayer/vocabulary.ui

    presentationLayer/vocabularyExam1.cpp
    presentationLayer/vocabularyExam1.h
    presentationLayer/vocabularyExam1.ui

    presentationLayer/vocabularyExam2.cpp
    presentationLayer/vocabularyExam2.h
    presentationLayer/vocabularyExam2.ui

    presentationLayer/vocabularyExam3.cpp
    presentationLayer/vocabularyExam3.h
    presentationLayer/vocabularyExam3.ui

    presentationLayer/biology.cpp
    presentationLayer/biology.h
    presentationLayer/biology.ui

    presentationLayer/cellBiology.cpp
    presentationLayer/cellBiology.h
    presentationLayer/cellBiology.ui

    presentationLayer/cellBiologyExam1.cpp
    presentationLayer/cellBiologyExam1.h
    presentationLayer/cellBiologyExam1.ui

    presentationLayer/cellBiologyExam2.cpp
    presentationLayer/cellBiologyExam2.h
    presentationLayer/cellBiologyExam2.ui

    presentationLayer/cellBiologyExam3.cpp
    presentationLayer/cellBiologyExam3.h
    presentationLayer/cellBiologyExam3.ui

    presentationLayer/genetics.cpp
    presentationLayer/genetics.h
    presentationLayer/genetics.ui

    presentationLayer/geneticsExam1.cpp
    presentationLayer/geneticsExam1.h
    presentationLayer/geneticsExam1.ui

    presentationLayer/geneticsExam2.cpp
    presentationLayer/geneticsExam2.h
    presentationLayer/geneticsExam2.ui

    presentationLayer/geneticsExam3.cpp
    presentationLayer/geneticsExam3.h
    presentationLayer/geneticsExam3.ui

    presentationLayer/profile.cpp
    presentationLayer/profile.h
    presentationLayer/profile.ui

    presentationLayer/results.cpp
    presentationLayer/results.h
    presentationLayer/results.ui

    presentationLayer/mathsResults.cpp
    presentationLayer/mathsResults.h
    presentationLayer/mathsResults.ui

    presentationLayer/englishResults.cpp
    presentationLayer/englishResults.h
    presentationLayer/englishResults.ui

    presentationLayer/biologyResults.cpp
    presentationLayer/biologyResults.h
    presentationLayer/biologyResults.ui

    presentationLayer/program.cpp
    presentationLayer/program.h
    presentationLayer/program.ui

    presentationLayer/inbox.cpp
    presentationLayer/inbox.h
    presentationLayer/inbox.ui

    presentationLayer/feedback.cpp
    presentationLayer/feedback.h
    presentationLayer/feedback.ui

    presentationLayer/lessons.cpp
    presentationLayer/lessons.h
    presentationLayer/lessons.ui

    presentationLayer/fontutils.cpp
    presentationLayer/fontutils.h

    presentationLayer/questionStructure.h

    # Data Access Layer
    dataAccessLayer/database.cpp
    dataAccessLayer/database.h
    dataAccessLayer/users.txt
    dataAccessLayer/feedback.txt
    dataAccessLayer/math_results.txt
    dataAccessLayer/biology_results.txt
    dataAccessLayer/english_results.txt

    dataAccessLayer/userSession.cpp
    dataAccessLayer/userSession.h

    resources.qrc
    presentationLayer/test.ui

)

install(FILES dataAccessLayer/users.txt DESTINATION ${CMAKE_INSTALL_BINDIR})

target_link_libraries(AGUniverse
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

set(AGUniverse_resource_files
    # Images
    "assets/images/exams_icon.png"
    "assets/images/results_icon.png"
    "assets/images/program_icon.png"
    "assets/images/inbox_icon.png"
    "assets/images/lessons_icon.png"
    "assets/images/profile.icon.png"
    "assets/images/log_out_icon.png"
    "assets/images/Test_logo_2.png"
    "assets/images/Logo1.png"
    "assets/images/profile_picture.png"
    "assets/images/math_icon.png"
    "assets/images/english_icon.png"
    "assets/images/biology_icon.png"
    "assets/images/geometry_icon.png"
    "assets/images/algebra_icon.png"
    "assets/images/grammar_icon.png"
    "assets/images/vocabulary_icon.png"
    "assets/images/cell_biology_and_metabolism_icon.png"
    "assets/images/genetics_and_heredity_icon.png"
    "assets/images/table.png"
    "assets/images/file-icon.png"


    # Fonts
    "assets/fonts/Aura Regular.ttf"
    "assets/fonts/CrimsonText-SemiBold.ttf"
    "assets/fonts/Allerta-Regular.ttf"

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
