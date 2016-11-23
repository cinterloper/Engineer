add_library(Engineer
   engineer.c
   engineer_math.c
   engineer_game.c
   engineer_scene.c
   )


target_link_libraries(Engineer
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
   ${DB_LIBRARIES}
   m
   )
