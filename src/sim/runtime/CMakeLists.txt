add_library(sim_runtime discrete_model.cpp)
target_sources(sim_runtime PUBLIC
               differential_model.h
               discrete_model.h
               discrete_simulator.h
               simulator.h
               simulator.cpp)
target_link_libraries(sim_runtime PRIVATE absl::status absl::statusor status_macros sim_util)