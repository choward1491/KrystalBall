/*
** Created by Christian Howard on 3/17/24.
*/
#ifndef KRYSTALBALL_SRC_SIM_UTIL_MONTE_CARLO_MODELS_FIXED_MONTE_CARLO_MODEL_H_
#define KRYSTALBALL_SRC_SIM_UTIL_MONTE_CARLO_MODELS_FIXED_MONTE_CARLO_MODEL_H_

#include <cstdint>
#include <random>

#include "sim/util/monte_carlo_models/monte_carlo_interface.h"

namespace sim::util::mc_models {

// implements the Monte Carlo Model concept
class FixedMonteCarloModel : public MonteCarloModelInterface {
 public:

  FixedMonteCarloModel();
  ~FixedMonteCarloModel() override = default;

  // interface from Monte Carlo Model concept
  void ResetMonteCarloProgress() override;
  [[nodiscard]] bool AllMonteCarloSimsDone() const override;
  void UpdateMonteCarloProgress() override;
  void SetSeed(std::int32_t) override;
  double UnifRealSample(double a, double b) override;
  std::int64_t UnifIntSample(std::int64_t a, std::int64_t b) override;

  // other important methods
  void SetMaxMonteCarloRuns(std::int64_t max_mc_runs);
  [[nodiscard]] std::int64_t GetMaxMonteCarloRuns() const;

 private:
  std::int64_t num_mc_runs_completed_;
  std::int64_t max_mc_runs_;
  std::default_random_engine eng;

};

}

#endif //KRYSTALBALL_SRC_SIM_UTIL_MONTE_CARLO_MODELS_FIXED_MONTE_CARLO_MODEL_H_
