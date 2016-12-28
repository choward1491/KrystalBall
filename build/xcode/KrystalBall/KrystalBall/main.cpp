//
//  main.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 8/1/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "PendulumSim.hpp"
#include "pendulum_sim.hpp"


int main(int argc, const char * argv[]) {
    PendulumSim psim2;
    psim2.runSim();
    
    pendulum::simulation psim;
    psim.willWriteSimHistory(false);
    psim.run();
    
    return 0;
}
