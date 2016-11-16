//
//  sim_state.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/13/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "sim_state.hpp"
#include "Fraction.hpp"

namespace sim {
    
#define HEADER template<typename T>
#define STATE state<T>
    
    HEADER
    struct STATE::Data {
        Data():safety_ref(nullptr),dyn_state(nullptr){}
        num_type* safety_ref;
        num_type* dyn_state;
        Fraction time_precise;
    };
    
    HEADER
    STATE::state(){
        data = new Data();
    }
    
    HEADER
    typename STATE::num_type** STATE::getStateRef(){
        return &data->dyn_state;
    }
    
    HEADER
    STATE::~state() {
        if( data ){
            data->dyn_state = nullptr;
            if( data->safety_ref ){ delete [] data->safety_ref; data->safety_ref = nullptr;}
            delete data; data = nullptr;
        }
    }
    
    HEADER
    void STATE::allocate(int num_state) {
        if( data->safety_ref ){ delete [] data->safety_ref; data->safety_ref = data->dyn_state = nullptr; }
        data->safety_ref = new num_type[num_state];
        data->dyn_state = data->safety_ref;
    }
    
    HEADER
    void STATE::setStateRef( num_type* ref ){
        data->dyn_state = ref;
    }
    
    HEADER
    typename STATE::num_type STATE::getCurrentTime() const{
        return static_cast<num_type>(data->time_precise);
    }
    
    HEADER
    void STATE::setCurrentTime( const num_type & t ){
        data->time_precise = t;
    }
    
    
    template class state<float>;
    template class state<double>;
    
}
