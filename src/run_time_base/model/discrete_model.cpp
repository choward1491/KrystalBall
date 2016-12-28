//
//  discrete.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/13/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include <run_time_base/model/discrete_model.hpp>
#include <run_time_base/model/model_state.hpp>
#include <run_time_base/sim/sim_state.hpp>
#include <shared/PreciseTime.h>


namespace discrete {
    
#define HEADER template<typename T>
#define MODEL model<T>
    
    //std::unique_ptr<ModelData> data;
    
    HEADER
    struct MODEL::ModelData {
        ModelData():sim_state(nullptr),updateRate(1){}
        sim::state<T> * sim_state;
        Time updateRate;
        Time dt;
    };
        
    HEADER
    MODEL::model():data(new ModelData()) {
        
    }
    
    HEADER
    MODEL::~model(){
        
    }
    
    HEADER
    std::string MODEL::name() const{
        return "discrete_model";
    }
    
    HEADER
    void MODEL::init() {
        
    }
    
    HEADER
    void MODEL::update() {
        
    }
    
    HEADER
    void MODEL::setupPrintData( print::history<T> & p ) {
        
    }
    
    HEADER
    void MODEL::setCentralSimState( sim::state<T> & cs ) {
        data->sim_state = &cs;
    }
    
    HEADER
    void MODEL::setUpdateRate( num_type rateHz ) {
        data->updateRate = rateHz;
        data->dt = 1.0/rateHz;
    }
    
    HEADER
    Time MODEL::getUpdateRate() const {
        return data->updateRate;
    }
    
    HEADER
    Time MODEL::getDt() const {
        return data->dt;
    }
    
    HEADER
    Time MODEL::getNextUpdateTime( Time currentTime ) {
        return currentTime + data->dt;
    }
    
    HEADER
    sim::state<T> & MODEL::getCentralSimState() {
        return *data->sim_state;
    }
    
    
    template class model<double>;
    template class model<float>;
    
#undef HEADER
#undef MODEL
    
}
