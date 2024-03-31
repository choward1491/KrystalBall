/*
** Created by Christian Howard on 3/17/24.
*/

#include <cstdint>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "status_macros/status_macros.h"

#include "sim/runtime/discrete_model.h"
#include "sim/util/schedulers/min_heap_scheduler.h"

namespace sim::util::schedulers {

absl::StatusOr<std::int64_t> MinHeapScheduler::GetNextTimeEvent() {
  if( min_heap_.empty() ){
    return absl::InternalError("No more events in scheduler, error");
  }
  return min_heap_.top().time;
}
absl::Status MinHeapScheduler::GetAndRemoveEventsAtTime(std::vector<::runtime::DiscreteModel *> &model_list_to_append_to) {
  ASSIGN_OR_RETURN(const std::int64_t smallest_time, GetNextTimeEvent());
  const size_t num_events = min_heap_.size();
  for(size_t i = 0; i < num_events; ++i){
    if( min_heap_.top().time != smallest_time ){
      break;
    }
    ::runtime::DiscreteModel* model = min_heap_.top().model;
    if( model == nullptr ){
      return absl::InternalError("Discrete model was incorrectly found to be null, error.");
    }
    model_list_to_append_to.push_back(model);
    min_heap_.pop();
  }
  return absl::OkStatus();
}
absl::Status MinHeapScheduler::AddEventTimeWithModel(std::int64_t next_time, ::runtime::DiscreteModel *model) {
  if( model ==nullptr ){
    return absl::InvalidArgumentError("Discrete model passed in is null, error.");
  }
  min_heap_.push(TimeModelPair{.time = next_time, .model = model});
  return absl::OkStatus();
}

}