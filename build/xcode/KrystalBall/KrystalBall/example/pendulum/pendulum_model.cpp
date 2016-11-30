//
//  pendulum_model.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/27/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "pendulum_model.hpp"
#include "history_printer.hpp"
#include "model_state.hpp"
#include <math.h>

namespace pendulum {
    
    enum state_names {
        theta = 0,
        theta_d
    };

    std::string model::name() const {
        return "pendulum";
    }
    
    void model::init() {
        ModelState & s = this->getLocalState();
        m = 1.0;
        c = 1;
        l = 15;
        s[0] = M_PI/6.0;
        s[1] = 0;
    }
    void model::update() {
        
    }
    int  model::numDims() const {
        return 2;
    }
    void model::operator()( num_type & time, ModelState & dqdt ) {
        ModelState & s = this->getLocalState();
        const num_type gravity = 9.81;
        dqdt[theta]     = s[theta_d];
        dqdt[theta_d]   = -(c*s[theta_d]/m + gravity*sin(s[theta])/l);
    }
    void model::setupPrintData( Printer & p ) {
        p.addVariableToPrint(this->stateAt(0), "theta");
        p.addVariableToPrint(this->stateAt(1), "theta_dot");
        p.addVariableToPrint(m, "Mass");
        p.addVariableToPrint(c, "Dampening");
        p.addVariableToPrint(l, "Length");
    }


}
