/*
** Created by Christian Howard on 3/17/24.
*/
#ifndef KRYSTALBALL_SRC_SIM_UTIL_MONTE_CARLO_MODELS_FIXED_MONTE_CARLO_MODEL_H_
#define KRYSTALBALL_SRC_SIM_UTIL_MONTE_CARLO_MODELS_FIXED_MONTE_CARLO_MODEL_H_

#include <cstdint>

namespace sim::util::mc_models {

// implements the Monte Carlo Model concept
class FixedMonteCarloModel {
 public:

  FixedMonteCarloModel();
  ~FixedMonteCarloModel() = default;

  // interface from Monte Carlo Model concept
  void ResetMonteCarloProgress();
  [[nodiscard]] bool AllMonteCarloSimsDone() const;
  void UpdateMonteCarloProgress();

  // other important methods
  void SetMaxMonteCarloRuns(std::int64_t max_mc_runs);
  std::int64_t GetMaxMonteCarloRuns() const;

 private:
  std::int64_t num_mc_runs_completed_;
  std::int64_t max_mc_runs_;

};

}

#endif //KRYSTALBALL_SRC_SIM_UTIL_MONTE_CARLO_MODELS_FIXED_MONTE_CARLO_MODEL_H_
