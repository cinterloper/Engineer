# Add binary: engineer
add_executable(engineer
   engineer_main.c
   engineer_tabber.c
   engineer_user.c
   engineer_project.c
   engineer_window.c
   )

target_link_libraries(engineer
   Engineer
   ${EDI_LIBRARIES}
   )

# Add binary: engineer_math_test
add_executable(engineer_math_test
   engineer_math_test_main.c
   )

target_link_libraries(engineer_math_test
   Engineer
   )

# Add binary: engineer_render_test
add_executable(engineer_render_test
   engineer_render_test_main.c
   )

target_link_libraries(engineer_render_test
   Engineer
   )
