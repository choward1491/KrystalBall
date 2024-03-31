add_library(sim_lib INTERFACE)

add_subdirectory(sim)
add_subdirectory(util)

target_link_libraries(sim_lib INTERFACE
                      sim
                      util)