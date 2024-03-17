add_executable(misc_testing)
target_sources(misc_testing PRIVATE misc_testing.cpp)
target_include_directories(misc_testing PRIVATE ${ABSEIL_INCLUDE})
target_link_libraries(misc_testing PRIVATE sim_lib external)