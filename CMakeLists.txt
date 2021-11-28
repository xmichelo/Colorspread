cmake_minimum_required(VERSION 3.10)

project(Colorspread)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (NOT DEFINED ENV{QTDIR})
   message(FATAL_ERROR "QTDIR needs to be defined and point to the root of your Qt folder. (e.g. /Users/MyName/Qt/5.10.1/clang_64).")
endif()

set(CMAKE_PREFIX_PATH  ${CMAKE_PREFIX_PATH} $ENV{QTDIR})
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

find_package(Qt6Core)
find_package(Qt6Gui)
find_package(Qt6Widgets)
find_package(Qt6OpenGL)
find_package(Qt6OpenGLWidgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC_MOC_OPTIONS "-bstdafx.h")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_definitions(-DUNICODE -D_UNICODE)

add_executable(Colorspread
   Constants.cpp
   Constants.h
   GameBoard.cpp
   GameBoard.h
   GameEngine.cpp
   GameEngine.h
   Globals.cpp
   Globals.h
   GlWidget.cpp
   GlWidget.h
   main.cpp
   MainWindow.cpp
   MainWindow.h
   MainWindow.ui
   SeedDialog.cpp
   SeedDialog.h
   SeedDialog.ui
   stdafx.cpp
   stdafx.h
   Utils.cpp
   Utils.h
)

target_precompile_headers(Colorspread PUBLIC stdafx.h)

target_link_libraries(Colorspread Qt6::Core)
target_link_libraries(Colorspread Qt6::Gui)
target_link_libraries(Colorspread Qt6::Widgets)
target_link_libraries(Colorspread Qt6::OpenGL)
target_link_libraries(Colorspread Qt6::OpenGLWidgets)
