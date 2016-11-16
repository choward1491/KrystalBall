//
//  dynamic.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/13/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "dynamic_model.hpp"
#include "model_state.hpp"
#include "sim_state.hpp"

namespace dynamic {
    
#define HEADER template<typename T>
#define MODEL model<T>
    
    //std::unique_ptr<ModelData> data;

    HEADER
    struct MODEL::ModelData {
        ModelData():sim_state(nullptr){}
        sim::state<T> * sim_state;
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
    
    
    template class model<double>;
    template class model<float>;
    
#undef HEADER
#undef MODEL
    
}
