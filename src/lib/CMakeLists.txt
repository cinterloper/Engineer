# We need to make a list of our library global code file paths.
FILE(GLOB_RECURSE ENGINEER_GLOBAL_CODE global/*.c)

# Set up our Eolian based compile targets.
SET(EOCLASSES
   engineer_node
   engineer_scene
   engineer_viewport
)
FOREACH(EOCLASS ${EOCLASSES})

   LIST(APPEND EOSOURCES ${CMAKE_CURRENT_BINARY_DIR}/${EOCLASS}.eo.h)
   LIST(APPEND EOSOURCES ${CMAKE_CURRENT_BINARY_DIR}/${EOCLASS}.eo.c)
   LIST(APPEND EOSOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${EOCLASS}.c)
   add_custom_command(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${EOCLASS}.eo.h ${CMAKE_CURRENT_BINARY_DIR}/${EOCLASS}.eo.c
      COMMAND eolian_gen `pkg-config --variable=eolian_flags ecore eo evas efl` ${CMAKE_CURRENT_SOURCE_DIR}/${EOCLASS}.eo
      COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/${EOCLASS}.eo.* ${CMAKE_CURRENT_BINARY_DIR}
   )
ENDFOREACH(EOCLASS)

# Add the Engineer.so library as a compile target.
add_library(Engineer SHARED
   ${ENGINEER_GLOBAL_CODE}
   engineer.c
   ${EOSOURCES}
)

#target_include_directories(Engineer PRIVATE
#   ${CMAKE_CURRENT_BINARY_DIR}
#   ${EINA_INCLUDE_DIRS}
#   ${EVAS_INCLUDE_DIRS}
#   ${EFL_INCLUDE_DIRS}
#   ${EIO_INCLUDE_DIRS}
#   ${EO_INCLUDE_DIRS}
#   ${ECORE_INCLUDE_DIRS}
#)

# Link the external libraries needed to run Engineer.
target_link_libraries(Engineer
   m
   ${DB_LIBRARIES}
   ${EIO_LIBRARIES}
   ${EINA_LIBRARIES}
   ${EET_LIBRARIES}
   ${ECORE_LIBRARIES}
   ${ECORE_FILE_LIBRARIES}
   ${EO_LIBRARIES}
   ${EVAS_LIBRARIES}
   ${EFL_LIBRARIES}
   ${EFREET_LIBRARIES}
   ${EFREET_TRASH_LIBRARIES}
   ${ELEMENTARY_LIBRARIES}
)

