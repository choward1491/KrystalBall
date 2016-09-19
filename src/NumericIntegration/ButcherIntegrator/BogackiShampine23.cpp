//
//  BogackiShampine23.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 9/18/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "BogackiShampine23.hpp"
#include <math.h>

BogackiShampine23::BogackiShampine23():ButcherIntegrator(){
    btable.resize(4,2);
    btable.c(0) = 0.0;
    btable.c(1) = 0.5;
    btable.c(2) = 0.75;
    btable.c(3) = 1.0;
    
    btable.a(0, 0) = 0;
    btable.a(1, 0) = 0.5;
    btable.a(2, 0) = 0.0;
    btable.a(2, 1) = 0.75;
    btable.a(3, 0) = 2.0 / 9.0;
    btable.a(3, 1) = 1.0 / 3.0;
    btable.a(3, 2) = 4.0 / 9.0;
    
    btable.b(0,0) = 2.0/9.0;
    btable.b(0,1) = 1.0/3.0;
    btable.b(0,2) = 4.0/9.0;
    btable.b(0,3) = 0.0;
    
    btable.b(1,0) = 7.0/24.0;
    btable.b(1,1) = 1.0/4.0;
    btable.b(1,2) = 1.0/3.0;
    btable.b(1,3) = 1.0/8.0;
}

double BogackiShampine23::newStepSize( double dt, double error ) {
    return 0.9 * dt * pow(fabs(tol/error),0.25);
}
