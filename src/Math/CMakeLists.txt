set(Component "Math")

file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(${Component}
  ${HEADERS}
  ${SOURCES}
)

target_link_libraries(${Component}
PUBLIC
  MathEvaluator
)

target_include_directories(${Component}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/${Component}
    ${Boost_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}::${Component} ALIAS ${Component})
