//
//  sim_scheduler.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/16/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include <run_time_base/sim/sim_scheduler.hpp>
#include <shared/PreciseTime.h>

namespace sim {
    
    template<typename T>
    Time scheduler<T>::getNextTime(){ return parent::getRootKey(); }

    template<typename T>
    void scheduler<T>::addNewModel( Time runTime, discrete::model<T>* model ){
        parent::push(runTime, model);
    }

    template<typename T>
    void scheduler<T>::reset(){
        for (int i = 0; i < parent::size(); i++) {
            parent::setKeyAt(i, parent::getDataAt(i)->getDt());
        }
        parent::generateHeap();
    }
    
    template class scheduler<float>;
    template class scheduler<double>;
    
}
