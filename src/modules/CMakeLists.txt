# Add the Engineer.so library as a compile target.
file(GLOB MODULES *.c)

foreach(MODULE ${MODULES})
   get_filename_component(NAME ${MODULE} NAME_WE)

   add_library(${NAME} MODULE
      ${NAME}.c
      ${CMAKE_SOURCE_DIR}/lib/engineer_module.c
   )

   target_include_directories(${NAME}
      PRIVATE ${CMAKE_SOURCE_DIR}/lib
   )

   # Link the external libraries needed to run Engineer.
   target_link_libraries(${NAME}
      Engineer
   )
endforeach(MODULE)

