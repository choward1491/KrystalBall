add_library(sim_runtime)
target_sources(sim_runtime PUBLIC
               differential_model.h
               discrete_model.h
               discrete_simulator.h
               simulator.h
               simulator.cpp)
target_link_libraries(sim_runtime PRIVATE abseil-cpp sim_util)