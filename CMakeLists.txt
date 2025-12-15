cmake_minimum_required( VERSION 3.16 )

if(ilo_included)
  return()
endif(ilo_included)
set(ilo_included true)

project(ilo
  VERSION 2.0.1
  DESCRIPTION "Fraunhofer IIS utility library"
  HOMEPAGE_URL "https://github.com/Fraunhofer-IIS/ilo"
  LANGUAGES CXX
)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(ilo_BUILD_DOC  OFF CACHE BOOL "Build doxygen doc")

include_directories(include)
add_subdirectory(src)

target_include_directories(ilo PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include
  $<INSTALL_INTERFACE:include>
)

if(ilo_BUILD_DOC)
  add_subdirectory(doc)
endif()

# Install
include(GNUInstallDirs)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ilo.pc.in ${CMAKE_CURRENT_BINARY_DIR}/ilo.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ilo.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)


