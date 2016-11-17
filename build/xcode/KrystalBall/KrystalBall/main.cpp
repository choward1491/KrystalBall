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

typedef sim::base<double> TestSim;

int main(int argc, const char * argv[]) {
    //PendulumSim sim;
    //sim.runSim();
    
    TestSim sim;
    
    discrete::model<double> dmodel;
    dynamic::model<float> fmodel;
    sim::state<float> a;
    print::history<float> hprint;
    double hi = 0.0;
    hprint.addVariableToPrint(hi,"somevar");
    
    //NBodySim sim2;
    //sim2.runSim();
    return 0;
}
