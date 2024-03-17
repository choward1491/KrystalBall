add_library(sim INTERFACE)

add_subdirectory(compile_time)
add_subdirectory(runtime)
add_subdirectory(util)

target_link_libraries(sim INTERFACE
                      sim_compile_time
                      sim_runtime
                      sim_util)