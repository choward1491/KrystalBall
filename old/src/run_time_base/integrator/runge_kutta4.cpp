//
//  runge_kutta4.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/27/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "runge_kutta4.hpp"

namespace integrate {
    
    template<typename T>
    rk4<T>::rk4() {
        this->btable.resize(4);
        this->btable.c(0) = 0.0; this->btable.a(0, 0) = 0;
        this->btable.c(1) = 0.5; this->btable.a(1,0)  = 0.5;
        this->btable.c(2) = 0.5; this->btable.a(2,1)  = 0.5;
        this->btable.c(3) = 1.0; this->btable.a(3,2)  = 1.0;
        this->btable.b(0,0) = 1.0/6.0;
        this->btable.b(0,1) = 1.0/3.0;
        this->btable.b(0,2) = 1.0/3.0;
        this->btable.b(0,3) = 1.0/6.0;
    }
    
    template class rk4<float>;
    template class rk4<double>;
    
}
