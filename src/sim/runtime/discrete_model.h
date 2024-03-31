/*
** Created by Christian Howard on 3/14/24.
*/
#ifndef KRYSTALBALL_SRC_SIM_RUNTIME_DISCRETE_MODEL_H_
#define KRYSTALBALL_SRC_SIM_RUNTIME_DISCRETE_MODEL_H_

#include <cstdint>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

namespace runtime {

class DiscreteModel {
 public:
  using StateType_t = double;
  using StateNamePair_t = std::pair<std::string_view, StateType_t>;

  // default constructors/destructors
  DiscreteModel() = default;
  virtual ~DiscreteModel() = default;

  // method for initializing the model to a base case
  virtual absl::Status Initialize() = 0;

  // method for returning name for the model
  virtual std::string GetModelName() const = 0;

  // returns number of states in model
  virtual std::size_t NumStates() const = 0;

  // allows for setting the state of a particular index
  virtual absl::Status SetState(int index) = 0;

  // grab the state name at a particular index
  virtual absl::StatusOr<std::string_view> GetStateName(int index) const = 0;

  // grab the state value at a particular index
  virtual absl::StatusOr<StateType_t> GetState(int index) const = 0;

  // given the discrete dynamics are of the form x(i+1) = f(i, x(i)),
  // computes x(i+1) using the current information the model may be dependent on
  // but does not update the internal state to x(i+1)
  virtual absl::Status ComputeNewStates(std::uint64_t current_time) = 0;

  // updates the internal state from x(i) to x(i+1), executed after calling `ComputeNewStates`
  virtual absl::Status UpdateStates() = 0;

  // using the current time, specifies when the model will need to be updated again.
  virtual absl::StatusOr<std::uint64_t> GetNextTimeUpdate(std::uint64_t current_time) = 0;

  // if the model wants to broadcast information y(i) that is a function of x(i),
  // this method ensures the model can append that information to list `state_name_list` for
  // printing to a data stream
  virtual absl::Status ExtractDataStreamInfo(std::vector<StateNamePair_t> &state_name_list) const = 0;

};

}

#endif //KRYSTALBALL_SRC_SIM_RUNTIME_DISCRETE_MODEL_H_
