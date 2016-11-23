#Specify the version being used as well as the language
cmake_minimum_required(VERSION 2.6)

project(Engineer)

add_definitions("-Wall -Wextra -fvisibility=hidden -std=gnu99 -g -Wshadow")
add_definitions(-DPACKAGE_VERSION="0.1.0")

set (CMAKE_SHARED_LINKER_FLAGS "-lm -ldb")

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

include(FindBerkeleyDB.cmake)

pkg_check_modules(Mount mount)
pkg_check_modules(Check REQUIRED check)
pkg_check_modules(Enlightenment REQUIRED enlightenment)
pkg_check_modules(Edi REQUIRED edi)

include_directories(
   ${EINA_INCLUDE_DIRS}
   ${EVAS_INCLUDE_DIRS}
   ${EFL_INCLUDE_DIRS}
   ${EIO_INCLUDE_DIRS}
   ${EET_INCLUDE_DIRS}
   ${EFREET_INCLUDE_DIRS}
   ${ECORE_INCLUDE_DIRS}
   ${ELEMENTARY_INCLUDE_DIRS}
   ${Edi_INCLUDE_DIRS}
   ${DB_INLCUDE_DIR}
   #../lib/efm
   #../widgets/
   ../headers
   )

add_subdirectory(bin)
add_subdirectory(lib)


