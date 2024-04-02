/*
** Created by Christian Howard on 4/1/24.
*/

#include "sim/runtime/discrete_model.h"

namespace runtime {

DiscreteModel::DiscreteModel():mc_model_(nullptr) {

}
void DiscreteModel::SetMonteCarloModel(::sim::util::mc_models::MonteCarloModelInterface *mc_model) {
  mc_model_ = mc_model;
}
::sim::util::mc_models::MonteCarloModelInterface *DiscreteModel::GetMonteCarloModel() {
  return mc_model_;
}
}