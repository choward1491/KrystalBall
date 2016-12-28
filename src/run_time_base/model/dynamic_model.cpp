//
//  dynamic.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/13/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include <run_time_base/model/dynamic_model.hpp>
#include <run_time_base/model/model_state.hpp>
#include <run_time_base/sim/sim_state.hpp>

namespace dynamic {
    
#define HEADER template<typename T>
#define MODEL model<T>
    
    //std::unique_ptr<ModelData> data;

    HEADER
    struct MODEL::ModelData {
        ModelData():sim_state(nullptr){}
        sim::state<T> * sim_state;
        local::state<T> state;
    };
    
    HEADER
    MODEL::model():data(new ModelData()) {
        
    }
    
    HEADER
    MODEL::~model() {
        
    }
    
    HEADER
    std::string MODEL::name() const {
        return "dynamic_model";
    }
    
    HEADER
    void MODEL::init() {
        
    }
    
    HEADER
    void MODEL::update() {
        
    }
    
    HEADER
    int  MODEL::numDims() const {
        return 0;
    }
    
    HEADER
    void MODEL::operator()( num_type & time, ModelState & dqdt ) {
        
    }
    
    HEADER
    void MODEL::setupPrintData( print::history<T> & p ) {
        
    }
    
    HEADER
    void MODEL::setCentralSimState( sim::state<T> & cs ) {
        data->sim_state = &cs;
    }
    
    HEADER
    sim::state<T> & MODEL::getCentralSimState() {
        return *data->sim_state;
    }
    
    HEADER
    void MODEL::initLocalState() {
        data->state.setReferenceAddress(data->sim_state->getStateRef());
        data->state.setNumDims(numDims());
        data->state.setDataAddress();
    }
    
    HEADER
    void MODEL::setLocalStateStartIndex(int idx ) {
        data->state.setStartIndex(idx);
    }
    
    HEADER
    local::state<T> & MODEL::getLocalState() {
        return data->state;
    }
    
    HEADER
    T & MODEL::stateAt(int idx) {
        return data->state[idx];
    }
    
    template class model<double>;
    template class model<float>;
    
#undef HEADER
#undef MODEL
    
}
