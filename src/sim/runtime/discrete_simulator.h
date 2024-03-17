/*
** Created by Christian Howard on 3/16/24.
*/
#ifndef KRYSTALBALL_SRC_SIM_RUNTIME_DISCRETE_SIMULATOR_H_
#define KRYSTALBALL_SRC_SIM_RUNTIME_DISCRETE_SIMULATOR_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "absl/strings/substitute.h"
#include "status_macros/status_macros.h"

#include "sim/runtime/discrete_model.h"
#include "sim/util/monte_carlo_concept.h"
#include "sim/util/scheduler_concept.h"

namespace runtime {

template<
    ::util::DiscreteScheduler Scheduler,
    ::util::MonteCarloModeler MonteCarloModel,
    typename Implementation>
class DiscreteSimulator {
 public:

  DiscreteSimulator() = default;
  ~DiscreteSimulator() = default;

  absl::Status SetInitialTime(std::int64_t init_time) {
    init_sim_time_ = init_time;
  }

  Scheduler &GetScheduler() {
    return scheduler_;
  }
  const Scheduler &GetScheduler() const {
    return scheduler_;
  }

  MonteCarloModel &GetMonteCarloModel() {
    return mc_model_;
  }
  const MonteCarloModel &GetMonteCarloModel() const {
    return mc_model_;
  }

  absl::Status Run() {

    // Reset the Monte Carlo model in case we have
    // called Run multiple times
    mc_model_.ResetMonteCarloProgress();

    // Initialize models within sim
    RETURN_IF_ERROR(AddAndConnectModels());

    // Run all monte carlo sims until
    // the Monte Carlo model says we are done
    int mc_run = 0;
    InitializeSimRunInfo();
    while (!mc_model_.AllMonteCarloSimsDone()) {
      RETURN_IF_ERROR(InitializeModels()).SetAppend()
                << absl::Substitute("| Error initializing models for MC run number $0", mc_run);
      RETURN_IF_ERROR(RunSingleMonteCarloSim()).SetAppend()
                << absl::Substitute("| Error running MC run number $0", mc_run);
      RETURN_IF_ERROR(FinalizeMonteCarloSim()).SetAppend()
                << absl::Substitute("| Error finalizing MC run number $0", mc_run);
      mc_model_.UpdateMonteCarloProgress();
      UpdateSimulationStatus();
    }

    // Finalize anything related to the sim
    RETURN_IF_ERROR(FinalizeSim());
  }

 protected:

  [[nodiscard]] std::int64_t GetSimTime() const {
    return sim_time_;
  }

  absl::Status AddModel(DiscreteModel *model) {
    if (model==nullptr) {
      return absl::InvalidArgumentError("DiscreteSimulator::AddModel Error: model is null");
    }
    models_.push_back(model);
    return absl::OkStatus();
  }

 private:
  std::int64_t init_sim_time_;
  std::int64_t sim_time_;
  Scheduler scheduler_;
  MonteCarloModel mc_model_;
  std::vector<DiscreteModel *> models_;
  std::vector<DiscreteModel *> models_to_update_;

  absl::Status AddAndConnectModels() {
    RETURN_IF_ERROR(AddModelsToSim());
    RETURN_IF_ERROR(ConnectModels());
    models_to_update_.reserve(models_.size());
  }

  absl::Status AddModelsToSim() {
    return static_cast<Implementation *>(this)->AddModelsToSim_Impl();
  }
  absl::Status InitializeModels() {
    for (DiscreteModel *model : models_) {
      RETURN_IF_ERROR(model->Initialize()).SetPrepend()
                << absl::Substitute("Error initializing model $0", model->GetModelName());
    }
  }
  absl::Status ConnectModels() {
    return static_cast<Implementation *>(this)->ConnectModels_Impl();
  }
  bool FinishedMonteCarloSim() {
    return static_cast<Implementation *>(this)->FinishedMonteCarloSim_Impl();
  }
  absl::Status FinalizeMonteCarloSim() {
    return static_cast<Implementation *>(this)->FinalizeMonteCarloSim_Impl();
  }
  absl::Status FinalizeSim() {
    return static_cast<Implementation *>(this)->FinalizeSim_Impl();
  }
  absl::Status InitializeSimRunInfo() {
    return static_cast<Implementation *>(this)->InitializeSimRunInfo_Impl();
  }
  void UpdateSimulationStatus() {
    return static_cast<Implementation *>(this)->UpdateSimulationStatus_Impl();
  }

  absl::Status RunSingleMonteCarloSim() {

    // initialize time
    sim_time_ = init_sim_time_;

    // run sim until completion
    while (!FinishedMonteCarloSim()) {

      // get next event time
      ASSIGN_OR_RETURN(std::int64_t next_time, scheduler_.GetNextEventTime());

      // extract and update all models that are being updated at time `next_time`
      models_to_update_.clear();
      RETURN_IF_ERROR(scheduler_.GetAndRemoveEventsAtTime(next_time, models_to_update_));
      for (DiscreteModel *model : models_to_update_) {
        RETURN_IF_ERROR(model->ComputeNewStates(next_time));
      }
      for (DiscreteModel *model : models_to_update_) {
        RETURN_IF_ERROR(model->UpdateStates());
        RETURN_IF_ERROR(scheduler_.AddEventTimeWithModel(model->GetNextTimeUpdate(next_time), model));
      }

      // update the simulation time
      sim_time_ = next_time;
    }
    RETURN_IF_ERROR(FinalizeMonteCarloSim());
  }

};

}

#endif //KRYSTALBALL_SRC_SIM_RUNTIME_DISCRETE_SIMULATOR_H_
