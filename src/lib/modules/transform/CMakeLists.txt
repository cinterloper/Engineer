# Add the Engineer_Transform.so scene module as a compile target.
add_library(Engineer_Transform MODULE
   ${ENGINEER_GLOBAL_CODE}
   ../engineer_module.c
   ../engineer_module_subclass_autogen.c
   engineer_transform.c
   )

# Link the external libraries needed to run this Engineer module.
target_link_libraries(Engineer_Transform
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
