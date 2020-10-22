#
#

cmake_minimum_required (VERSION 3.13)
project (qcamera-state-crash)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package (Threads)
find_package(Qt5
  REQUIRED COMPONENTS
  Core Gui Network WebEngine WebEngineWidgets Widgets Multimedia
  MultimediaWidgets)

add_executable (qcamera-state-crash
  main.cxx
  )
target_link_libraries(qcamera-state-crash
  Qt5::Gui
  Qt5::Core
  Qt5::Widgets
  Qt5::Multimedia
  Qt5::MultimediaWidgets
  Qt5::WebEngineCore
  Qt5::WebEngineWidgets
  )
