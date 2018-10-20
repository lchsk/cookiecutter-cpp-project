CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Name of the project
project({{ cookiecutter.project_name }})

# Set default build type to Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the build type (Debug or Release)" FORCE)
endif()

message(STATUS "CMake build type: " ${CMAKE_BUILD_TYPE})

# Version of the project
set(PROJECT_VERSION "1.0.0")

# If build type is Debug, generate debugging information and don't optimise
if (CMAKE_BUILD_TYPE STREQUAL Debug)
  add_definitions(-O0)
  set(CMAKE_C_FLAGS "-g -Wall -pedantic")
else()
  add_definitions(-O3)
  set(CMAKE_C_FLAGS "-Wall -pedantic")
endif()

{% if cookiecutter.use_cpack == 'y' -%}
# CPack

set(CPACK_PACKAGE_CONTACT "{{ cookiecutter.author_email }}")
set(CPACK_GENERATOR "DEB;RPM;ZIP;TGZ")
set(CPACK_PACKAGE_DESCRIPTION, "{{ cookiecutter.project_short_description }}")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

# DEB package
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "<project website>")

# DEB package dependencies e.g. libncurses5 (>= 5.0), libglib2.0-0 (>= 2.0)
# List of dependencies for a DEB package
# E.g.: libncurses5 (>= 5.0), libglib2.0-0 (>= 2.0)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "")

# RPM package
set(CPACK_RPM_PACKAGE_LICENSE "{{ cookiecutter.license}}")
set(CPACK_RPM_PACKAGE_URL "<project website>")
set(CPACK_RPM_PACKAGE_DESCRIPTION "{{ cookiecutter.project_short_description }}")

# List of dependencies for an RPM package
# E.g.: ncurses >= 5.0, glib2 >= 2.0
set(CPACK_RPM_PACKAGE_REQUIRES "")

include(CPack)

# End CPack
{% endif -%}

# C standard for the compiler to use
set(CMAKE_CXX_STANDARD {{ cookiecutter.cpp_standard }})

# Source code files, all .hpp and .cpp files from src/ directory are included
file(GLOB SOURCES "src/*.hpp" "src/*.cpp")

# Executable name
add_executable(${PROJECT_NAME} ${SOURCES})


############################################
#                                          #
#              Dependencies                #
#                                          #
############################################

find_package(PkgConfig)

pkg_check_modules(PKG_CONFIG "pkg-config")

{% if cookiecutter.add_boost == 'y' -%}
find_package(Boost REQUIRED)
{% endif -%}

{% if cookiecutter.add_sfml == 'y' -%}
pkg_check_modules(SFML sfml-all REQUIRED)
{% endif -%}

include_directories(
  {% if cookiecutter.add_boost == 'y' -%}
  ${BOOST_INCLUDE_DIRS}
  {% endif -%}

  {% if cookiecutter.add_sfml == 'y' -%}
  ${SFML_INCLUDE_DIRS}
  {% endif -%}
  )

link_directories(
  {% if cookiecutter.add_boost == 'y' -%}
  ${BOOST_LIBRARY_DIRS}
  {% endif -%}

  {% if cookiecutter.add_sfml == 'y' -%}
  ${SFML_LIBRARY_DIRS}
  {% endif -%}
  )

add_definitions(
  {% if cookiecutter.add_boost == 'y' -%}
  ${BOOST_CFLAGS_OTHER}
  {% endif -%}

  {% if cookiecutter.add_sfml == 'y' -%}
  ${SFML_CXXFLAGS_OTHER}
  {% endif -%}
  )

target_link_libraries(${PROJECT_NAME}
  {% if cookiecutter.add_boost == 'y' -%}
  ${BOOST_LIBRARIES}
  {% endif -%}

  {% if cookiecutter.add_sfml == 'y' -%}
  ${SFML_LIBRARIES}
  {% endif -%}
  )


############################################
#                                          #
#                  Tests                   #
#                                          #
############################################

{% if cookiecutter.add_google_test == 'y' -%}
pkg_check_modules(GTEST "gtest")

enable_testing()

add_executable(test_{{ cookiecutter.project_name|lower }}
  tests/test_{{ cookiecutter.project_name|lower }}.cpp
  )

add_test(NAME
  test_{{ cookiecutter.project_name|lower }}
  COMMAND ./test_{{ cookiecutter.project_name|lower }}
  )

target_link_libraries(test_{{ cookiecutter.project_name|lower }}
  ${GTEST_LIBRARIES}
  # Link libraries needed in this test
  )

{% endif -%}


############################################
#                                          #
#              Installation                #
#                                          #
############################################

{% if cookiecutter.add_installation == 'y' -%}
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

install(FILES {{ cookiecutter.project_name|lower}}.1 DESTINATION share/man/man1)
{% endif -%}
