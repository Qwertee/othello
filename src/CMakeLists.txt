set(SRC_FILES
  main.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(EXECUTABLE_NAME othello)

add_executable(${EXECUTABLE_NAME} ${SRC_FILES})

target_link_libraries(${EXECUTABLE_NAME} allegro allegro_primitives)
