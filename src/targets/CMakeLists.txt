include_directories(main)

set(sources main/interface.cpp main/interface.hpp)

set(BUILD_TARGETS rematch)

set(BENCHMARK_TARGETS
    # test-onig
    # test-hscan
    # test-pcre
    # test-pcre2
    # test-boost
    # test-tre
    # force-all-re2
    # force-all-re2-timeout
    # force-all-re2-2vars
    # force-all-boost
    # force-all-pcre
    # force-suffix-re2
)

# set(REGEX_LIBS pcre2-8)

message("REmatch libs: ${REMATCH_LIBS}")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  link_directories(/opt/homebrew/lib)
endif()

foreach(target ${BUILD_TARGETS})
  add_executable(${target} ${CMAKE_CURRENT_SOURCE_DIR}/main/${target}.cpp
                           ${sources})
  target_link_libraries(${target} PUBLIC ${REMATCH_LIBS} PRIVATE CLI11::CLI11)
  target_compile_definitions(${target} PUBLIC NOPT_SEGMENT_RATIO)
endforeach(target ${BUILD_TARGETS})

if(REMATCH_BUILD_OPTIMIZATION_VERSIONS)

  add_executable(rematch_vanilla ${CMAKE_CURRENT_SOURCE_DIR}/main/rematch.cpp
                                 ${sources} ${REMATCH_SOURCES})
  target_compile_definitions(
    rematch_vanilla
    PUBLIC NOPT_MEMORY
    PUBLIC NOPT_ASCIIARRAY
    PUBLIC NOPT_OFFSET
    PUBLIC NOPT_EARLYOUTPUT
    PUBLIC NOPT_SEGMENT_RATIO)

  add_executable(rematch_memory ${CMAKE_CURRENT_SOURCE_DIR}/main/rematch.cpp
                                ${sources} ${REMATCH_SOURCES})
  target_compile_definitions(
    rematch_memory
    PUBLIC NOPT_ASCIIARRAY
    PUBLIC NOPT_OFFSET
    PUBLIC NOPT_EARLYOUTPUT
    PUBLIC NOPT_SEGMENT_RATIO)

  add_executable(
    rematch_ascii-array ${CMAKE_CURRENT_SOURCE_DIR}/main/rematch.cpp ${sources}
                        ${REMATCH_SOURCES})
  target_compile_definitions(
    rematch_ascii-array
    PUBLIC NOPT_OFFSET
    PUBLIC NOPT_EARLYOUTPUT
    PUBLIC NOPT_SEGMENT_RATIO)

  add_executable(rematch_offset ${CMAKE_CURRENT_SOURCE_DIR}/main/rematch.cpp
                                ${sources} ${REMATCH_SOURCES})
  target_compile_definitions(
    rematch_offset
    PUBLIC NOPT_EARLYOUTPUT
    PUBLIC NOPT_SEGMENT_RATIO)

  add_executable(
    rematch_early-output ${CMAKE_CURRENT_SOURCE_DIR}/main/rematch.cpp
                         ${sources} ${REMATCH_SOURCES})
  target_compile_definitions(rematch_early-output PUBLIC NOPT_SEGMENT_RATIO)

  add_executable(
    rematch_segment-ratio ${CMAKE_CURRENT_SOURCE_DIR}/main/rematch.cpp
                          ${sources} ${REMATCH_SOURCES})

  add_custom_target(rematch-opt-versions)
  add_dependencies(
    rematch-opt-versions
    rematch_vanilla
    rematch_memory
    rematch_ascii-array
    rematch_offset
    rematch_early-output
    rematch_segment-ratio)
endif()

if(REMATCH_BUILD_BENCHMARKS)
  find_package(oniguruma CONFIG REQUIRED)
  add_executable(test-onig ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/test-onig.cpp)
  target_link_libraries(test-onig PUBLIC ${REMATCH_LIBS} PRIVATE oniguruma::onig)

  find_package(re2 CONFIG REQUIRED)
  add_executable(test-re2 ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/test-re2.cpp)
  target_link_libraries(test-re2 PUBLIC ${REMATCH_LIBS} PRIVATE re2::re2)

  find_package(unofficial-pcre CONFIG REQUIRED)
  add_executable(test-pcre ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/test-pcre.cpp)
  target_link_libraries(test-pcre PUBLIC ${REMATCH_LIBS} PRIVATE unofficial::pcre::pcrecpp)

  add_executable(test-boost ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/test-boost.cpp)
  target_link_libraries(test-boost PUBLIC ${REMATCH_LIBS} PRIVATE Boost::regex)

  find_path(pcre2_INCLUDE_DIRS pcre2.h)
  find_library(pcre2_LIBRARIES pcre2-8)
  include_directories(${pcre2_INCLUDE_DIRS})
  add_executable(test-pcre2 ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/test-pcre2.cpp)
  target_link_libraries(test-pcre2 PUBLIC ${REMATCH_LIBS} PRIVATE ${pcre2_LIBRARIES})

  find_path(tre_INCLUDE_DIRS tre/tre.h)
  find_library(tre_LIBRARIES tre)
  include_directories(${tre_INCLUDE_DIRS})
  add_executable(test-tre ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/test-tre.cpp)
  target_link_libraries(test-tre PUBLIC ${REMATCH_LIBS} PRIVATE ${tre_LIBRARIES})
endif()
