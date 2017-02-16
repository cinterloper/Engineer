file(GLOB TARGETS ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
FOREACH(TARGET ${TARGETS})
   string(REGEX REPLACE "\\.[^.]*$" "" LABEL ${TARGET})

   get_filename_component(TARGET ${LABEL} NAME_WE)

   # Add the current Engineer Component Module as a compile target.
   add_library(${TARGET} MODULE
      ${TARGET}.c
      ../engineer_module.c
   )

   # The only external lib our Component Modules should need from
   #    Engineer is the primary lib itself.
   target_link_libraries(${TARGET}
      Engineer
   )

ENDFOREACH(TARGET)
