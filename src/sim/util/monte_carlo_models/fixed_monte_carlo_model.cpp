/*
** Created by Christian Howard on 3/17/24.
*/
#include <random>

#include "sim/util/monte_carlo_models/fixed_monte_carlo_model.h"

namespace sim::util::mc_models {

FixedMonteCarloModel::FixedMonteCarloModel() : max_mc_runs_(1), num_mc_runs_completed_(0), eng(17) {

}

// interface from Monte Carlo Model concept
void FixedMonteCarloModel::ResetMonteCarloProgress() {
  num_mc_runs_completed_ = 0;
}
[[nodiscard]] bool FixedMonteCarloModel::AllMonteCarloSimsDone() const {
  return num_mc_runs_completed_ >= max_mc_runs_;
}
void FixedMonteCarloModel::UpdateMonteCarloProgress() {
  num_mc_runs_completed_++;
}

void FixedMonteCarloModel::SetMaxMonteCarloRuns(std::int64_t max_mc_runs) {
  max_mc_runs_ = max_mc_runs;
}

std::int64_t FixedMonteCarloModel::GetMaxMonteCarloRuns() const {
  return max_mc_runs_;
}
void FixedMonteCarloModel::SetSeed(std::int32_t seed) {
  eng = std::default_random_engine(seed);
}
double FixedMonteCarloModel::UnifRealSample(double a, double b) {
  std::uniform_real_distribution<double> U(a, b);
  return U(eng);
}
std::int64_t FixedMonteCarloModel::UnifIntSample(std::int64_t a, std::int64_t b) {
  std::uniform_int_distribution<std::int64_t> U(a, b);
  return U(eng);
}

}