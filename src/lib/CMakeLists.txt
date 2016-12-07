# Add library: Engineer.so
add_library(Engineer SHARED
   engineer.c
   engineer_type.c
   engineer_math.c
   engineer_game.c
   engineer_scene.c
   )

target_link_libraries(Engineer
   m
   ${DB_LIBRARIES}
   ${EINA_LIBRARIES}
   ${EVAS_LIBRARIES}
   ${EFL_LIBRARIES}
   ${EIO_LIBRARIES}
   ${EO_LIBRARIES}
   ${EFREET_LIBRARIES}
   ${EFREET_TRASH_LIBRARIES}
   ${ECORE_LIBRARIES}
   ${ECORE_FILE_LIBRARIES}
   ${EET_LIBRARIES}
   ${ELEMENTARY_LIBRARIES}
   )
