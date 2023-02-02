file(GLOB fix_srcs
  ${CMAKE_CURRENT_SOURCE_DIR}/*.[ch]pp
)

file(GLOB_RECURSE glob_srcs
  ${CMAKE_CURRENT_SOURCE_DIR}/automata/*.[ch]pp
  ${CMAKE_CURRENT_SOURCE_DIR}/parse/*.[ch]pp
  ${CMAKE_CURRENT_SOURCE_DIR}/structs/*.[ch]pp
  ${CMAKE_CURRENT_SOURCE_DIR}/det/*.[ch]pp
  ${CMAKE_CURRENT_SOURCE_DIR}/factories/*.[ch]pp
  ${CMAKE_CURRENT_SOURCE_DIR}/parser_automata/*.[ch]pp
  ${CMAKE_CURRENT_SOURCE_DIR}/regex/*.[ch]pp
  ${CMAKE_CURRENT_SOURCE_DIR}/evaluation/*.[ch]pp
  ${CMAKE_CURRENT_SOURCE_DIR}/util/*.[ch]pp
)

set(REMATCH_SOURCES ${fix_srcs} ${glob_srcs})

set(project_LIB ${PROJECT_NAME}lib)

add_library(${project_LIB} ${REMATCH_SOURCES})
list(APPEND REMATCH_LIBS PUBLIC ${project_LIB})

# Pass the variable to parent
set(REMATCH_LIBS ${REMATCH_LIBS} PARENT_SCOPE)
set(REMATCH_SOURCES ${REMATCH_SOURCES} PARENT_SCOPE)

