//
//  cashkarp_rk45.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/27/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include <run_time_base/integrator/cashkarp_rk45.hpp>
#include <cmath>

namespace integrate {
    
    template<typename T>
    cashkarp_rk45<T>::cashkarp_rk45(){
        this->btable.resize(6,2);
        this->btable.c(0) = 0.0;
        this->btable.c(1) = 0.2;
        this->btable.c(2) = 0.3;
        this->btable.c(3) = 0.6;
        this->btable.c(4) = 1.0;
        this->btable.c(5) = 7.0/8.0;
        
        this->btable.a(0,0) = 0.0;
        this->btable.a(1,0) = 0.2;
        this->btable.a(2,0) = 3.0/40.0;
        this->btable.a(2,1) = 9.0/40.0;
        this->btable.a(3,0) = 0.3;
        this->btable.a(3,1) = -0.9;
        this->btable.a(3,2) = 1.2;
        this->btable.a(4,0) = -11/54.0;
        this->btable.a(4,1) = 2.5;
        this->btable.a(4,2) = -70.0/27.0;
        this->btable.a(4,3) = 35.0/27.0;
        this->btable.a(5,0) = 1631.0 / 55296.0;
        this->btable.a(5,1) = 175.0/512.0;
        this->btable.a(5,2) = 575.0/13824.0;
        this->btable.a(5,3) = 44275.0/110592.0;
        this->btable.a(5,4) = 253.0/4096.0;
        
        this->btable.b(0,0) = 2825.0/27648.0;
        this->btable.b(0,1) = 0.0;
        this->btable.b(0,2) = 18575.0/48384.0;
        this->btable.b(0,3) = 13525.0/55296.0;
        this->btable.b(0,4) = 277.0/14336.0;
        this->btable.b(0,5) = 0.25;
        
        this->btable.b(1,0) = 37.0/378.0;
        this->btable.b(1,1) = 0.0;
        this->btable.b(1,2) = 250.0/621.0;
        this->btable.b(1,3) = 125.0/594.0;
        this->btable.b(1,4) = 0.0;
        this->btable.b(1,5) = 512.0/1771.0;
    }
    
    template<typename T>
    T cashkarp_rk45<T>::newStepSize( num_type dt, num_type error ) {
        if( error != 0 ){
            return 0.9 * dt * std::pow(std::abs( this->getTolerance() /error),0.2);
        }else{ return dt; }
    }
    
    template class cashkarp_rk45<float>;
    template class cashkarp_rk45<double>;
    
}
