//
//  model_list.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/13/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "model_list.hpp"
#include "sim_state.hpp"
#include "dynamic_model.hpp"
#include "discrete_model.hpp"

namespace models {
#define HEADER template<typename T>
#define LIST list<T>
    //typedef dynamic::model<T>       dyn_m;
    //typedef discrete::model<T>      dscrt_m;
    //typedef std::vector<dyn_m*>     DynamicList ;
    //typedef std::vector<dscrt_m*>   DiscreteList;
    
    HEADER
    struct LIST::Data {
        DynamicList  dynamic_m;
        DiscreteList discrete_m;
        sim::state<T> * sim_state;
    };
    
    HEADER
    LIST::list():data(new Data()) { }
    
    HEADER
    void LIST::init(){
        for(int i = 0; i < data->dynamic_m.size(); ++i ){
            data->dynamic_m[i]->init();
        }
        for(int i = 0; i < data->dynamic_m.size(); ++i ){
            data->discrete_m[i]->init();
        }
    }
    
    HEADER
    void LIST::addDynamicModel ( dyn_m & model ){
        data->dynamic_m.push_back(&model);
    }
    
    HEADER
    void LIST::addDiscreteModel( dscrt_m & model, double freqHz ){
        data->discrete_m.push_back(&model);
        // add model to scheduler
    }
    
    HEADER
    void LIST::setCentralSimState( sim::state<T> & cs ){
        data->sim_state = &cs;
    }
    
    HEADER
    int LIST::getTotalNumberStates() const {
        int counter = 0;
        for(int i = 0; i < data->dynamic_m.size(); ++i ){
            counter += data->dynamic_m[i]->numDims();
        }
        return counter;
    }
    
    HEADER
    const typename LIST::DynamicList & LIST::getDynamicList() const {
        return data->dynamic_m;
    }
    
    HEADER
    const typename LIST::DiscreteList& LIST::getDiscreteList() const {
        return data->discrete_m;
    }
    
    
    template class list<float>;
    template class list<double>;
    
    
}
