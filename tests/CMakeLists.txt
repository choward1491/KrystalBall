add_executable(misc_testing)
target_sources(misc_testing PRIVATE misc_testing.cpp)
target_link_libraries(misc_testing PRIVATE sim_lib absl::status absl::statusor)