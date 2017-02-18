# Set up our project's cmake global configuration.
cmake_minimum_required(VERSION 3.6)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})

# Remember to update the version number after a significant update!
set(CURRENT_VERSION 0.2.0)
set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR}/../build)
project(Engineer VERSION ${CURRENT_VERSION})

# Find the location(s) of our project's prerequisite library files.
find_package(PkgConfig REQUIRED)
find_package(BerkeleyDB REQUIRED)
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
find_package(Edi REQUIRED)

include_directories(
   ${OpenCl_INCLUDE_DIR}
   ${DB_INLCUDE_DIRS}
   ${EINA_INCLUDE_DIRS}
   ${EVAS_INCLUDE_DIRS}
   ${EFL_INCLUDE_DIRS}
   ${EIO_INCLUDE_DIRS}
   ${EO_INCLUDE_DIRS}
   ${EET_INCLUDE_DIRS}
   ${EFREET_INCLUDE_DIRS}
   ${ECORE_INCLUDE_DIRS}
   ${ELEMENTARY_INCLUDE_DIRS}
   ${EDI_INCLUDE_DIRS}
   )

# Compilation Configuration.
add_definitions(-DEFL_EO_API_SUPPORT=1 -DEFL_BETA_API_SUPPORT=1)
add_definitions(-DPACKAGE_VERSION="${CURRENT_VERSION}")
add_definitions("-g -Wall -Wextra -Wshadow -std=gnu99")

# First we assemble the core library and it's toolbox.
add_subdirectory(lib)

# Now that the main lib has been compiled, lets build all of the Modules in the modules subdir.
#add_subdirectory(modules)

# All of our binary targets are in another castle.
add_subdirectory(bin)

