cmake_minimum_required(VERSION 3.16)

project(DroneView VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGLWidgets MultimediaWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGLWidgets MultimediaWidgets)


# --- for GStreamer ---------------
find_package(PkgConfig REQUIRED)
pkg_check_modules(GST REQUIRED IMPORTED_TARGET gstreamer-1.0 gstreamer-video-1.0)
# ---------------------------------

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        aspectratiolabel.cpp
        aspectratiolabel.h
        videomanager.h
        videomanager.cpp
        gstvideowidget.h
        networkmanager.h
        networkmanager.cpp


)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DroneView
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DroneView APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DroneView SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DroneView
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DroneView PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
    Qt${QT_VERSION_MAJOR}::MultimediaWidgets
    PkgConfig::GST # for GStreamer
)

# <-- ${GST_INCLUDE_DIRS} for the headers of GStreamer
target_include_directories(DroneView PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GST_INCLUDE_DIRS}
)

target_include_directories(DroneView PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) # to find my.h files

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DroneView)
endif()
set_target_properties(DroneView PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DroneView
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DroneView)
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/wait_image.jpg DESTINATION ${CMAKE_CURRENT_BINARY_DIR}) # In order to show wait_image at wait screen
