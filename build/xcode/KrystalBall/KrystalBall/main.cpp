//
//  main.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 8/1/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include <iostream>
#include "PendulumSim.hpp"
#include "NBodySim.hpp"

int main(int argc, const char * argv[]) {
    PendulumSim sim;
    sim.runSim();
    
    //NBodySim sim2;
    //sim2.runSim();
    return 0;
}
