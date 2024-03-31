//
//  ModelState.cpp
//  Spektr
//
//  Created by Christian J Howard on 3/15/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "ModelState.hpp"
#include "SimExceptions.hpp"
/*
double * ref;
size_t ndim;
 */

ModelState::ModelState():ref(0),ndim(0){
    
}
ModelState::ModelState(double ** address, int numDims, int offset_ ){
    try {
        ref = address;
        ndim = numDims;
        offset = offset_;
        data = &(*ref)[offset];
        if( !ref ){ throw sim::exception("Invalid Model State Address"); }
        if( ndim == 0 ){ throw sim::exception("Model State of Invalid Size 0"); }
        
    } catch (std::exception & e) {
        printf("Error. Msg = '%s'\n",e.what());
    }
    
}

double & ModelState::operator[](int i){
    //printf("i = %i, ndim = %i\n",(int)i,ndim);
    return data[(i%ndim)];
}
const double & ModelState::operator[](int i) const{
    //printf("i = %i, ndim = %i\n",(int)i,ndim);
    return data[(i%ndim)];
}

void ModelState::setAddress( double ** address ){
    ref = address;
    data = &(*ref)[offset];
}
void ModelState::setNumDims( int numDims ){
    ndim = numDims;
}

void ModelState::setOffset( int offset_ ){
    offset = offset_;
    data = &(*ref)[offset];
}

    
