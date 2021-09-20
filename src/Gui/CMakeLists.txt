project(Gui LANGUAGES CXX)

find_package(Qt5 ${QT_REQUIRED_VERSION} COMPONENTS
  Core
  Qml
  Quick
  QuickControls2 REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.*pp")
file(GLOB QRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/resources/qml/*.qrc")

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES} ${RC_FILES} ${QRC_FILES})

target_link_libraries(${PROJECT_NAME}
PRIVATE
  Math
  Qt5::Core
  Qt5::Qml
  Qt5::Quick
  Qt5::QuickControls2
)

target_include_directories(${PROJECT_NAME}
PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Путь до корневого каталога со всеми QML-формами
set_target_properties(${PROJECT_NAME} PROPERTIES
  QML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources/qml")
