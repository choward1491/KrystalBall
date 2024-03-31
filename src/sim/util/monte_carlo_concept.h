/*
** Created by Christian Howard on 3/17/24.
*/
#ifndef KRYSTALBALL_SRC_SIM_UTIL_MONTE_CARLO_CONCEPT_H_
#define KRYSTALBALL_SRC_SIM_UTIL_MONTE_CARLO_CONCEPT_H_

#include <cstdint>
#include <concepts>
#include <vector>

#include "absl/status/statusor.h"

#include "sim/runtime/discrete_model.h"

namespace util {

template<typename T>
concept MonteCarloModeler = requires(T a)
{
  a.ResetMonteCarloProgress();
  {a.AllMonteCarloSimsDone} -> std::same_as<bool>;
  a.UpdateMonteCarloProgress();
};

}

#endif //KRYSTALBALL_SRC_SIM_UTIL_MONTE_CARLO_CONCEPT_H_
