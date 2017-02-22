# Add the Engineer.so library as a compile target.
add_library(Engineer SHARED
   ${ENGINEER_GLOBAL_CODE}
    engineer.c
    engineer_node.c
    engineer_scene.c
    engineer_viewport.c
)

add_dependencies(Engineer
   eolian_gen
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

