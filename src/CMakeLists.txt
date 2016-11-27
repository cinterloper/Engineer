cmake_minimum_required(VERSION 3.6)

# Remember to update the version number after a significant update!
set(CURRENT_VERSION 0.1.0)
project(Engineer VERSION ${CURRENT_VERSION})

# Dependencies
include(FindBerkeleyDB.cmake)

find_package(Eina REQUIRED)
find_package(Eo 1.18 REQUIRED)
find_package(Eolian 1.18 REQUIRED)
find_package(Eet REQUIRED)
find_package(Efl REQUIRED)
find_package(Eldbus REQUIRED)
find_package(Efreet COMPONENTS mime trash)
find_package(Eio REQUIRED)
find_package(Evas 1.18 REQUIRED)
find_package(Edje REQUIRED)
find_package(Ecore COMPONENTS file)
find_package(Elementary 1.18.0 REQUIRED)
find_package(LibArchive REQUIRED)
find_package(Threads REQUIRED)

pkg_check_modules(Mount mount)
pkg_check_modules(Check REQUIRED check)
pkg_check_modules(Enlightenment REQUIRED enlightenment)
pkg_check_modules(Edi REQUIRED edi)

# Compilation Configuration
add_definitions(-DPACKAGE_VERSION="${CURRENT_VERSION}")
add_definitions("-g -Wall -Wextra -Wshadow -std=gnu99")

include_directories(
   ${DB_INLCUDE_DIRS}
   ${EINA_INCLUDE_DIRS}
   ${EVAS_INCLUDE_DIRS}
   ${EFL_INCLUDE_DIRS}
   ${EIO_INCLUDE_DIRS}
   ${EET_INCLUDE_DIRS}
   ${EFREET_INCLUDE_DIRS}
   ${ECORE_INCLUDE_DIRS}
   ${ELEMENTARY_INCLUDE_DIRS}
   ${Edi_INCLUDE_DIRS}
   ${CMAKE_SOURCE_DIR}/headers
   )

add_subdirectory(bin)
add_subdirectory(lib)


