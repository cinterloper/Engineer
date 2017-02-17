# Add binary: Engineer GDK
#add_executable(Engineer
#   Engineer/main.c
#   Engineer/tabber.c
#   Engineer/user.c
#   Engineer/project.c
#   Engineer/window.c
#   )

#target_link_libraries(Engineer
#   Engineer
#   ${EDI_LIBRARIES}
#   )


# Add binary: engineer_math_test
add_executable(engineer_math_test
   engineer_math_test/main.c
   )

target_link_libraries(engineer_math_test
   Engineer
   )


# Add binary: engineer_render_test
add_executable(engineer_render_test
   engineer_render_test/main.c
   )

target_link_libraries(engineer_render_test
   Engineer
   )
