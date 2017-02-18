# We need to make a list of our library global code file paths.
FILE(GLOB_RECURSE ENGINEER_GLOBAL_CODE global/*.c)

# Set up our Eolian based compile targets.
SET(EOCLASSES
   engineer_node
   engineer_scene
   engineer_viewport
)
FOREACH(EOCLASS ${EOCLASSES})
   LIST(APPEND EOSOURCES ${EOCLASS}.c)
   LIST(APPEND EOHOUTPUT ${EOCLASS}.eo.h)
   LIST(APPEND EOCOUTPUT ${EOCLASS}.eo.c)
   add_custom_command(
      OUTPUT ${EOCLASS}.eo.h ${EOCLASS}.eo.c
      COMMAND eolian_gen `pkg-config --variable=eolian_flags ecore eo evas efl` ${CMAKE_CURRENT_SOURCE_DIR}/${EOCLASS}.eo
      COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/${EOCLASS}.eo.* ${CMAKE_BINARY_DIR}/bin
      COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/${EOCLASS}.eo.* ${CMAKE_BINARY_DIR}/lib
   )
ENDFOREACH(EOCLASS)

add_custom_target(eolian DEPENDS ${EOHOUTPUT} ${EOCOUTPUT})

# Add the Engineer.so library as a compile target.
add_library(Engineer SHARED
   ${ENGINEER_GLOBAL_CODE}
   ${EOSOURCES}
    engineer.c
)

add_dependencies(Engineer
   eolian
)

target_include_directories(Engineer PRIVATE
   ${CMAKE_CURRENT_BINARY_DIR}
)

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

