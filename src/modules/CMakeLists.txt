# Add the Engineer.so library as a compile target.
file(GLOB MODULES *.c)

foreach(MODULE ${MODULES})
   get_filename_component(NAME ${MODULE} NAME_WE)

   add_library(${NAME} MODULE
      ${ENGINEER_GLOBAL_CODE}
      ${NAME}.c
      ${CMAKE_SOURCE_DIR}/src/lib/engineer_module.c
   )

   target_compile_definitions(${NAME}
      PRIVATE COMPONENT=${NAME}
   )

   target_include_directories(${NAME}
      PRIVATE ${CMAKE_SOURCE_DIR}/src/lib
      #PRIVATE ${CMAKE_SOURCE_DIR}/src/modules
   )

   # Link the external libraries needed to run Engineer.
   target_link_libraries(${NAME}
      Engineer
   )
endforeach(MODULE)

