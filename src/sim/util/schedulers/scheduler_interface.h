/*
** Created by Christian Howard on 4/1/24.
*/
#ifndef KRYSTALBALL_SRC_SIM_UTIL_SCHEDULERS_SCHEDULER_INTERFACE_H_
#define KRYSTALBALL_SRC_SIM_UTIL_SCHEDULERS_SCHEDULER_INTERFACE_H_

#include <cstdint>
#include <queue>
#include <vector>

#include "sim/runtime/discrete_model.h"

namespace sim::util::schedulers {

class SchedulerInterface {
 public:
  SchedulerInterface() = default;
  virtual ~SchedulerInterface() = default;

  // required interface by ::util::DiscreteScheduler concept
  virtual absl::StatusOr<std::uint64_t> GetNextTimeEvent() = 0;
  virtual absl::Status GetAndRemoveEventsAtTime(std::vector<::runtime::DiscreteModel *> &model_list_to_append_to) = 0;
  virtual absl::Status AddEventTimeWithModel(std::uint64_t next_time, ::runtime::DiscreteModel *model) = 0;
};

}

#endif //KRYSTALBALL_SRC_SIM_UTIL_SCHEDULERS_SCHEDULER_INTERFACE_H_
