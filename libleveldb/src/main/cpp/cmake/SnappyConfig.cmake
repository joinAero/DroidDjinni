if(NOT SNAPPY_DIR)
  message(FATAL_ERROR "SNAPPY_DIR not set.")
endif()

include(TestBigEndian)
test_big_endian(SNAPPY_IS_BIG_ENDIAN)

include(CheckIncludeFile)
check_include_file("byteswap.h" HAVE_BYTESWAP_H)
check_include_file("stddef.h" HAVE_STDDEF_H)
check_include_file("stdint.h" HAVE_STDINT_H)
check_include_file("sys/endian.h" HAVE_SYS_ENDIAN_H)
check_include_file("sys/mman.h" HAVE_SYS_MMAN_H)
check_include_file("sys/resource.h" HAVE_SYS_RESOURCE_H)
check_include_file("sys/time.h" HAVE_SYS_TIME_H)
check_include_file("sys/uio.h" HAVE_SYS_UIO_H)
check_include_file("unistd.h" HAVE_UNISTD_H)
check_include_file("windows.h" HAVE_WINDOWS_H)

include(CheckLibraryExists)
check_library_exists(z zlibVersion "" HAVE_LIBZ)
check_library_exists(lzo2 lzo1x_1_15_compress "" HAVE_LIBLZO2)

include(CheckCXXSourceCompiles)
check_cxx_source_compiles(
    "int main(void) { return __builtin_expect(0, 1); }" HAVE_BUILTIN_EXPECT)

check_cxx_source_compiles(
    "int main(void) { return __builtin_ctzll(0); }" HAVE_BUILTIN_CTZ)

include(CheckSymbolExists)
check_symbol_exists("mmap" "sys/mman.h" HAVE_FUNC_MMAP)
check_symbol_exists("sysconf" "unistd.h" HAVE_FUNC_SYSCONF)

find_package(GTest QUIET)
if(GTEST_FOUND)
  set(HAVE_GTEST 1)
endif(GTEST_FOUND)

find_package(Gflags QUIET)
if(GFLAGS_FOUND)
  set(HAVE_GFLAGS 1)
endif(GFLAGS_FOUND)

configure_file(
  "${SNAPPY_DIR}/cmake/config.h.in"
  "${SNAPPY_DIR}/config.h"
)

# We don't want to define HAVE_ macros in public headers. Instead, we use
# CMake's variable substitution with 0/1 variables, which will be seen by the
# preprocessor as constants.
set(HAVE_STDINT_H_01  ${HAVE_STDINT_H})
set(HAVE_STDDEF_H_01  ${HAVE_STDDEF_H})
set(HAVE_SYS_UIO_H_01 ${HAVE_SYS_UIO_H})
if(NOT HAVE_STDINT_H_01)
  set(HAVE_STDINT_H_01 0)
endif(NOT HAVE_STDINT_H_01)
if(NOT HAVE_STDDEF_H_01)
  set(HAVE_STDDEF_H_01 0)
endif(NOT HAVE_STDDEF_H_01)
if(NOT HAVE_SYS_UIO_H_01)
  set(HAVE_SYS_UIO_H_01 0)
endif(NOT HAVE_SYS_UIO_H_01)

configure_file(
  "${SNAPPY_DIR}/snappy-stubs-public.h.in"
  "${SNAPPY_DIR}/snappy-stubs-public.h")