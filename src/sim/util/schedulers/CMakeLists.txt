add_library(sim_schedulers)
target_sources(sim_schedulers PUBLIC
              min_heap_scheduler.h
              min_heap_scheduler.cpp
              min_heap_scheduler_test.cpp)
target_link_libraries(sim_schedulers PRIVATE abseil-cpp gtest gmock)