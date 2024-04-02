/*
** Created by Christian Howard on 4/1/24.
*/
#ifndef KRYSTALBALL_SRC_SIM_UTIL_MONTE_CARLO_MODELS_MONTE_CARLO_INTERFACE_H_
#define KRYSTALBALL_SRC_SIM_UTIL_MONTE_CARLO_MODELS_MONTE_CARLO_INTERFACE_H_

#include <cstdint>

namespace sim::util::mc_models {

// implements the Monte Carlo Model concept
class MonteCarloModelInterface {
 public:
  MonteCarloModelInterface() = default;
  virtual ~MonteCarloModelInterface() = default;

  // interface from Monte Carlo Model concept
  virtual void ResetMonteCarloProgress() = 0;
  [[nodiscard]] virtual bool AllMonteCarloSimsDone() const = 0;
  virtual void UpdateMonteCarloProgress() = 0;
  virtual void SetSeed(std::int32_t) = 0;
  virtual double UnifRealSample(double a, double b) = 0;
  virtual std::int64_t UnifIntSample(std::int64_t a, std::int64_t b) = 0;

};

}

#endif //KRYSTALBALL_SRC_SIM_UTIL_MONTE_CARLO_MODELS_MONTE_CARLO_INTERFACE_H_
