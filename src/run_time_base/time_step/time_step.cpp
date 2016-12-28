//
//  time_step.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/27/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include <run_time_base/time_step/time_step.hpp>


template<typename T>
std::string time_step<T>::name() const {
    return "time_step";
}

template class time_step<double>;
template class time_step<float>;
