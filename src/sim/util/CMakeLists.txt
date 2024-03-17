add_library(sim_util INTERFACE monte_carlo_concept.h scheduler_concept.h)
target_link_libraries(sim_util INTERFACE abseil-cpp)