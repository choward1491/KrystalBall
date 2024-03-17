/*
** Created by Christian Howard on 3/17/24.
*/
#include "fixed_monte_carlo_model.h"

namespace sim::util::mc_models {

FixedMonteCarloModel::FixedMonteCarloModel() : max_mc_runs_(1), num_mc_runs_completed_(0) {

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

}