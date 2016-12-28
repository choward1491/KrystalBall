//
//  pendulum_sim.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/27/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include <run_time_base/example/pendulum/pendulum_sim.hpp>
#include <shared/PreciseTime.h>

namespace pendulum {
    
    simulation::simulation() {
        timer.start();
        this->setSimHistoryRate(10);
        this->setSimHistoryPath("test_history.txt");
        this->getIntegrator().setTolerance(1e-10);
    }
    bool simulation::isMonteCarloDone() {
        return (this->getCompletedMC() == 10000);
    }
    void simulation::linkModelsToSim() {
        this->addDynamics(pm);
        this->addDiscrete(ts, 100.0);
    }
    bool simulation::finishedSimulation(){
        return static_cast<double>(getTime()) >= 20.0;
    }
    void simulation::finalizeMonteCarloRun(){
        //printf("Finished the %i Monte Carlo Run!\n",this->getCompletedMC()+1);
    }
    void simulation::finalize(){
        timer.stop();
        printf("The simulation has completed!\n");
        printf("The simulation took %0.8lf seconds\n",timer.getDuration());
    }
    
}
