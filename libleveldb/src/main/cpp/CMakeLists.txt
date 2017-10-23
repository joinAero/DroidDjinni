cmake_minimum_required(VERSION 3.4.1)

get_filename_component(PRO_ROOT_DIR "${PROJECT_SOURCE_DIR}/../../../.." ABSOLUTE)
message(STATUS "PRO_ROOT_DIR: ${PRO_ROOT_DIR}")

set(DEPS_DIR "${PRO_ROOT_DIR}/deps")
set(DJINNI_DIR "${DEPS_DIR}/djinni")

# options

add_definitions(-DLOG_TAG=\"DroidDjinni\")
add_definitions(-DDEBUG)

# djinni_jni

include_directories(
  ${DJINNI_DIR}/support-lib/jni
)
add_library(djinni_jni STATIC
  ${DJINNI_DIR}/support-lib/jni/djinni_support.cpp
)

# snappy

set(SNAPPY_DIR "${DEPS_DIR}/snappy")
include("cmake/SnappyConfig.cmake")

include_directories(
  ${SNAPPY_DIR}
)
add_library(snappy STATIC
  ${SNAPPY_DIR}/snappy-c.cc
  ${SNAPPY_DIR}/snappy-sinksource.cc
  ${SNAPPY_DIR}/snappy-stubs-internal.cc
  ${SNAPPY_DIR}/snappy.cc
)
set_target_properties(snappy PROPERTIES
  COMPILE_FLAGS "-Wno-unused-parameter -Wno-sign-compare"
)

# leveldb

set(LEVELDB_DIR "${DEPS_DIR}/leveldb")
set(LEVELDB_FLAGS "-fno-builtin-memcmp -D_REENTRANT -DOS_ANDROID -DLEVELDB_PLATFORM_POSIX=1")
set(LEVELDB_FLAGS "${LEVELDB_FLAGS} -DLEVELDB_ATOMIC_PRESENT")
set(LEVELDB_FLAGS "${LEVELDB_FLAGS} -DHAVE_SNAPPY=1")

set(LEVELDB_SRCS
  ${LEVELDB_DIR}/port/port_posix.cc
)
foreach(__dir db util table)
  file(GLOB __srcs "${LEVELDB_DIR}/${__dir}/*.cc")
  foreach(__src ${__srcs})
    get_filename_component(__src_name ${__src} NAME_WE)
    string(REGEX MATCH ".*_(test|bench)$" __match "${__src_name}")
    if(__match)
      continue()
    endif()
    string(REGEX MATCH "^(testutil|testharness|leveldbutil)$" __match "${__src_name}")
    if(__match)
      continue()
    endif()
    list(APPEND LEVELDB_SRCS ${__src})
  endforeach()
endforeach()
#message(STATUS "LEVELDB_SRCS: ${LEVELDB_SRCS}")

include_directories(
  ${LEVELDB_DIR}
  ${LEVELDB_DIR}/include
)
add_library(leveldb STATIC ${LEVELDB_SRCS})
set_target_properties(leveldb PROPERTIES
  COMPILE_FLAGS "-Wno-unused-parameter -Wno-sign-compare ${LEVELDB_FLAGS}"
)
target_link_libraries(leveldb snappy)

# leveldb_jni

include_directories(
  base
  leveldb/cpp
  leveldb/impl
  leveldb/jni
)

set(LEVELDB_JNI_SRCS "")
foreach(__dir cpp impl jni)
  file(GLOB __srcs "leveldb/${__dir}/*.cpp")
  list(APPEND LEVELDB_JNI_SRCS ${__srcs})
endforeach()
#message(STATUS "LEVELDB_JNI_SRCS: ${LEVELDB_JNI_SRCS}")

add_library(leveldb_jni SHARED
  ${DJINNI_DIR}/support-lib/jni/djinni_main.cpp
  ${LEVELDB_JNI_SRCS}
)
set_target_properties(leveldb PROPERTIES
  LINK_FLAGS "-Wl,--build-id,--gc-sections,--exclude-libs,ALL"
)
target_link_libraries(leveldb_jni
  log djinni_jni leveldb
)
