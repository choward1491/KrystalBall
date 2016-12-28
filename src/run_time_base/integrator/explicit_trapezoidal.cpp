//
//  explicit_trapezoidal.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/27/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include <run_time_base/integrator/explicit_trapezoidal.hpp>

namespace integrate {
    
    template<typename T>
    explicit_trapezoidal<T>::explicit_trapezoidal():butcher<T>(){
        this->btable.resize(2);
        this->btable.c(0) = 0.0; this->btable.a(0, 0) = 0.0;
        this->btable.c(1) = 1.0; this->btable.a(1,0)  = 1.0;
        this->btable.b(0,0) = 0.5;
        this->btable.b(0,1) = 0.5;
    }
    
    template class explicit_trapezoidal<float>;
    template class explicit_trapezoidal<double>;
    
}
