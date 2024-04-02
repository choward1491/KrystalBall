add_library(sim_monte_carlo_models)
target_sources(sim_monte_carlo_models PUBLIC
               monte_carlo_interface.h
               fixed_monte_carlo_model.h
               fixed_monte_carlo_model.cpp)
target_link_libraries(sim_monte_carlo_models PRIVATE absl::status)

# add executable for testing
add_executable(sim_monte_carlo_models_test)
target_sources(sim_monte_carlo_models_test PRIVATE fixed_monte_carlo_model_test.cpp)
target_link_libraries(sim_monte_carlo_models_test PRIVATE gtest_main gmock sim_monte_carlo_models absl::status)
add_test(NAME SimMonteCarloModelsTest COMMAND sim_monte_carlo_models_test )