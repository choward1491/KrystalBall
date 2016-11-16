//
//  state.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/13/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "model_state.hpp"


namespace local {
    
#define HEADER template<typename T>
#define STATE  state<T>
    
    HEADER
    STATE::state():ref(nullptr),data(nullptr),ndims_(0),offset_(0) {
        
    }
    
    HEADER
    void STATE::setStartIndex(int idx) {
        offset_ = idx;
    }
    
    HEADER
    void STATE::setReferenceAddress( T** address ) {
        ref = address;
    }
    
    HEADER
    void STATE::setNumDims( int ndims ) {
        ndims_ = ndims;
    }
    
    HEADER
    void STATE::setDataAddress() {
        data = &(*ref)[offset_];
    }
    
    
    HEADER
    T & STATE::operator[](int i) {
        return data[i];
    }
    
    HEADER
    const T & STATE::operator[](int i) const {
        return data[i];
    }
    
    HEADER
    T & STATE::at(int i) {
        return data[i%ndims_];
    }
    
    HEADER
    const T & STATE::at(int i) const {
        return data[i%ndims_];
    }
    
    template class state<float>;
    template class state<double>;
    
}
