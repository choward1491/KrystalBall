add_library(sim_schedulers)
target_sources(sim_schedulers PUBLIC
               scheduler_interface.h
              min_heap_scheduler.h
              min_heap_scheduler.cpp)
target_link_libraries(sim_schedulers PRIVATE absl::status absl::statusor status_macros)

add_executable(sim_schedulers_test)
target_sources(sim_schedulers_test PRIVATE min_heap_scheduler_test.cpp)
target_link_libraries(sim_schedulers_test PRIVATE gtest_main gmock sim_schedulers absl::status)
add_test(NAME SimSchedulersTest COMMAND sim_schedulers_test )