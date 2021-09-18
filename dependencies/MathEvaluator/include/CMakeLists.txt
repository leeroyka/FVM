set(Component "MathEvaluator")

file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(${Component}
  ${HEADERS}
  ${SOURCES}
)

target_link_libraries(${Component}
  PUBLIC
)

target_include_directories(${Component}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/${Component}
    ${Boost_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}::${Component} ALIAS ${Component})