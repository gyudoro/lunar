# Setup CMake.

cmake_minimum_required(VERSION 3.14...3.29)

project(
  lunar
  VERSION 0.1.0
  DESCRIPTION "An experimental GameCube emulator."
  LANGUAGES C)

# Configure the C compiler.

set(C_STANDARD 90)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create a target.

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build/)
add_executable(lunar ${sources})

# Add the base sources.

target_sources(lunar PRIVATE
  src/main.c
  src/debug/log.c)

target_include_directories(lunar PRIVATE include)

# Add arch-specific sources.

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64"
   OR CMAKE_SYSTEM_PROCESSOR STREQUAL "IA64")
  set(ARCH_X86_64 1)

elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86")
  set(ARCH_X86 1)

else()
  set(ARCH_GENERIC 1)

endif()

# Set compiler-specific variables and flags.

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(COMPILER_GCC 1)
  target_compile_options(lunar PRIVATE -Wall -Wextra -Wpedantic)

elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
  set(COMPILER_CLANG 1)
  target_compile_options(lunar PRIVATE -Wall -Wextra -Wpedantic)

elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
  set(COMPILER_MSVC 1)
  target_compile_options(lunar PRIVATE /W4 /WX)

endif()

# Look for 8-bit, 16-bit, and 32-bit types.

include(CheckTypeSize)

check_type_size("char" CHAR_SIZE)
check_type_size("short" SHORT_SIZE)
check_type_size("int" INT_SIZE)
check_type_size("long" LONG_SIZE)
check_type_size("long long" LONG_LONG_SIZE)

if(CHAR_SIZE EQUAL 1)
  set(INT8_TYPE char)
elseif(SHORT_SIZE EQUAL 1)
  set(INT8_TYPE short)
elseif(INT_SIZE EQUAL 1)
  set(INT8_TYPE int)
elseif(LONG_SIZE EQUAL 1)
  set(INT8_TYPE long)
elseif(LONG_LONG_SIZE EQUAL 1)
  set(INT8_TYPE long long)
else()
  message(FATAL_ERROR "Could not find an 8-bit type")
endif()

if(CHAR_SIZE EQUAL 2)
  set(INT16_TYPE char)
elseif(SHORT_SIZE EQUAL 2)
  set(INT16_TYPE short)
elseif(INT_SIZE EQUAL 2)
  set(INT16_TYPE int)
elseif(LONG_SIZE EQUAL 2)
  set(INT16_TYPE long)
elseif(LONG_LONG_SIZE EQUAL 2)
  set(INT16_TYPE long long)
else()
  message(FATAL_ERROR "Could not find a 16-bit type")
endif()

if(CHAR_SIZE EQUAL 4)
  set(INT32_TYPE char)
elseif(SHORT_SIZE EQUAL 4)
  set(INT32_TYPE short)
elseif(INT_SIZE EQUAL 4)
  set(INT32_TYPE int)
elseif(LONG_SIZE EQUAL 4)
  set(INT32_TYPE long)
elseif(LONG_LONG_SIZE EQUAL 4)
  set(INT32_TYPE long long)
else()
  message(FATAL_ERROR "Could not find a 32-bit type")
endif()

if(CHAR_SIZE EQUAL 8)
  set(INT64_TYPE char)
elseif(SHORT_SIZE EQUAL 8)
  set(INT64_TYPE short)
elseif(INT_SIZE EQUAL 8)
  set(INT64_TYPE int)
elseif(LONG_SIZE EQUAL 8)
  set(INT64_TYPE long)
elseif(LONG_LONG_SIZE EQUAL 8)
  set(INT64_TYPE long long)
else()
  message(FATAL_ERROR "Could not find a 64-bit type")
endif()

# Configure config.h.

configure_file(include/common/config.h.in include/common/config.h @ONLY)
