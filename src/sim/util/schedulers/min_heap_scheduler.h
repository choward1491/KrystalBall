/*
** Created by Christian Howard on 3/17/24.
*/
#ifndef KRYSTALBALL_SRC_SIM_UTIL_SCHEDULERS_MIN_HEAP_SCHEDULER_H_
#define KRYSTALBALL_SRC_SIM_UTIL_SCHEDULERS_MIN_HEAP_SCHEDULER_H_

#include <cstdint>
#include <queue>
#include <vector>

#include "sim/runtime/discrete_model.h"
#include "sim/util/schedulers/scheduler_interface.h"

namespace sim::util::schedulers {

// must implement ::util::DiscreteScheduler concept
class MinHeapScheduler: public SchedulerInterface {
 public:

  MinHeapScheduler() = default;
  ~MinHeapScheduler() override = default;

  // required interface by ::util::DiscreteScheduler concept
  absl::StatusOr<std::uint64_t> GetNextTimeEvent() override;
  absl::Status GetAndRemoveEventsAtTime(std::vector<::runtime::DiscreteModel *> &model_list_to_append_to) override;
  absl::Status AddEventTimeWithModel(std::uint64_t next_time, ::runtime::DiscreteModel *model) override;

 private:
  struct TimeModelPair {
    std::uint64_t time;
    ::runtime::DiscreteModel *model;
    bool operator<(const TimeModelPair &pair) const {
      return pair.time < time;
    }
  };

  std::priority_queue<TimeModelPair> min_heap_;

};

}

#endif //KRYSTALBALL_SRC_SIM_UTIL_SCHEDULERS_MIN_HEAP_SCHEDULER_H_
