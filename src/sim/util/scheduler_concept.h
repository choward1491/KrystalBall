/*
** Created by Christian Howard on 3/17/24.
*/
#ifndef KRYSTALBALL_SRC_SIM_UTIL_SCHEDULER_CONCEPT_H_
#define KRYSTALBALL_SRC_SIM_UTIL_SCHEDULER_CONCEPT_H_

#include <cstdint>
#include <concepts>
#include <vector>

#include "absl/status/statusor.h"

#include "sim/runtime/discrete_model.h"

namespace util {

template<typename T>
concept DiscreteScheduler = requires(T a, std::vector<::runtime::DiscreteModel*> models, ::runtime::DiscreteModel* model)
{
  {a.GetNextTimeEvent()} -> std::same_as<absl::StatusOr<std::int64_t>>;
  {a.GetAndRemoveEventsAtTime(std::int64_t(1), models)} -> std::same_as<absl::Status>;
  {a.AddEventTimeWithModel(model->GetNextTimeUpdate(std::int64_t(1)), model)} -> std::same_as<absl::Status>;
};

}

#endif //KRYSTALBALL_SRC_SIM_UTIL_SCHEDULER_CONCEPT_H_
