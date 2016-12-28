//
//  explicit_euler.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/26/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include <run_time_base/integrator/explicit_euler.hpp>

namespace integrate {
    
    template<typename T>
    explicit_euler<T>::explicit_euler():butcher<T>(){
        this->btable.resize(1);
        this->btable.c(0) = 0.0;
        this->btable.b(0,0) = 1.0;
        this->btable.a(0, 0) = 0;
    }
    
    template class explicit_euler<float>;
    template class explicit_euler<double>;
    
}
