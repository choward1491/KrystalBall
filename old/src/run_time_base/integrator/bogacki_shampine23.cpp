//
//  bogacki_shampine23.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/27/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//


#include "bogacki_shampine23.hpp"
#include <cmath>

namespace integrate {
    
    template<typename T>
    bogacki_shampine23<T>::bogacki_shampine23() {
        this->btable.resize(4,2);
        this->btable.c(0) = 0.0;
        this->btable.c(1) = 0.5;
        this->btable.c(2) = 0.75;
        this->btable.c(3) = 1.0;
        
        this->btable.a(0, 0) = 0;
        this->btable.a(1, 0) = 0.5;
        this->btable.a(2, 0) = 0.0;
        this->btable.a(2, 1) = 0.75;
        this->btable.a(3, 0) = 2.0 / 9.0;
        this->btable.a(3, 1) = 1.0 / 3.0;
        this->btable.a(3, 2) = 4.0 / 9.0;
        
        this->btable.b(0,0) = 2.0/9.0;
        this->btable.b(0,1) = 1.0/3.0;
        this->btable.b(0,2) = 4.0/9.0;
        this->btable.b(0,3) = 0.0;
        
        this->btable.b(1,0) = 7.0/24.0;
        this->btable.b(1,1) = 1.0/4.0;
        this->btable.b(1,2) = 1.0/3.0;
        this->btable.b(1,3) = 1.0/8.0;
    }
    template<typename T>
    T bogacki_shampine23<T>::newStepSize( num_type dt, num_type error ) {
        return 0.9 * dt * std::pow(std::abs( this->getTolerance() /error),0.25);
    }
    
    template class bogacki_shampine23<float>;
    template class bogacki_shampine23<double>;
    
}
