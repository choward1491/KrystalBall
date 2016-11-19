//
//  main.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 8/1/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include <iostream>
#include "PendulumSim.hpp"
#include "dynamic_model.hpp"
#include "discrete_model.hpp"
#include "sim_state.hpp"
#include "history_printer.hpp"
#include "sim_base.hpp"
#include "uniform_sim.hpp"

template<typename T>
class RK4 {
public:
    RK4() = default;
    void setNumDimensions(int i){}
};


class SampleSim : public sim::uniform<float, RK4> {
public:
    SampleSim() = default;
    ~SampleSim()= default;
private:
    bool isMonteCarloDone() { return true; }
    bool finishedSimulation(){ return true; }      // method to return whether the sim has finished
    void finalizeMonteCarloRun(){ printf("Finalize MC Run\n"); }   // method to finalize a monte carlo run
    void finalize(){ printf("Sim is Finishing\n"); }             // method to finalize the whole completed simulation
    void buildTotalDynamicState(){ this->getState().allocate(10); }  // method to construct the total data associated with dynamic models
};

int main(int argc, const char * argv[]) {
    
    SampleSim sim;
    sim.run();
    
    return 0;
}
