# Set up our project's cmake global configuration.
cmake_minimum_required(VERSION 3.6)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})

# Remember to update the version number after a significant update!
set(CURRENT_VERSION 0.2.0)
project(Engineer VERSION ${CURRENT_VERSION})

# Find the location(s) of our project's prerequisite library files.
find_package(PkgConfig REQUIRED)
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
   ${CMAKE_BINARY_DIR}/eolian
   )

# Compilation Configuration.
add_definitions(-DEFL_EO_API_SUPPORT=1 -DEFL_BETA_API_SUPPORT=1)
add_definitions(-DPACKAGE_VERSION="${CURRENT_VERSION}")
add_definitions("-g -Wall -Wextra -Wshadow -std=gnu99")

# Set up our Eolian generator to process *.eo files into *.eo.h/*.eo.c targets at compile time.
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/eolian)
file(GLOB_RECURSE EOCLASSES RELATIVE ${CMAKE_SOURCE_DIR} *.eo)
FOREACH(EOCLASS ${EOCLASSES})
   LIST(APPEND EOHOUT ${EOCLASS}.h)
   LIST(APPEND EOCOUT ${EOCLASS}.c)
   add_custom_command(
      OUTPUT ${EOCLASS}.h ${EOCLASS}.c
      COMMAND eolian_gen `pkg-config --variable=eolian_flags ecore eo evas efl` ${CMAKE_SOURCE_DIR}/${EOCLASS}
      COMMAND mv ${CMAKE_SOURCE_DIR}/${EOCLASS}.* ${CMAKE_BINARY_DIR}/eolian
   )
ENDFOREACH(EOCLASS)
add_custom_target(eolian_gen DEPENDS ${EOHOUT} ${EOCOUT})

# First we assemble the core library and it's toolbox.
add_subdirectory(lib)

# Now that the main lib has been compiled, lets build all of the Modules in the modules subdir.
#add_subdirectory(modules)

# All of our binary targets are in another castle.
add_subdirectory(bin)

