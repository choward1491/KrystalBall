//
//  butcher_integrator.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/24/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include <run_time_base/integrator/butcher_integrator.hpp>
#include <run_time_base/model/model_state.hpp>
#include <run_time_base/sim/sim_state.hpp>
#include <cmath>

namespace integrate {
    #define HEADER template<typename T>
    #define BUTCHER butcher<T>


    HEADER
    void deleteVectorPointers( std::vector<T*> & vec ){
        if( vec.size() != 0 ){
            for(int i = 0; i < vec.size(); i++ ){
                if( vec[i] ){
                    delete [] vec[i];
                    vec[i] = 0;
                }
            }
        }
        
    }

    HEADER
    void allocVectorPointers( std::vector<T*> & vec , int num ){
        if( vec.size() != 0 ){
            
            //#pragma omp parallel for
            for(int i = 0; i < vec.size(); i++ ){
                vec[i] = new T[num]();
            }
        }
    }

    HEADER
    void BUTCHER::setTolerance( num_type tol_ ){
        tol = tol_;
    }
    
    HEADER
    typename BUTCHER::num_type BUTCHER::getTolerance() const {
        return tol;
    }

    HEADER
    BUTCHER::butcher():numDims(-1),tmp(0),y1(0),y2(0),tol(1e-5){
        
    }

    HEADER
    BUTCHER::~BUTCHER(){
        deleteVectorPointers(K);
        if( tmp ){delete [] tmp; tmp = 0;}
        if( y1 ){ delete [] y1; y1 = 0; }
        if( y2 ){ delete [] y2; y2 = 0; }
    }
        
    HEADER
    void BUTCHER::setNumDimensions( int numDimensions ){
        numDims = numDimensions;
        deleteVectorPointers(K);
        K.resize(btable.numSteps());
        
        //#pragma omp parallel for
        for(int i = 0; i < K.size(); i++ ){ K[i] = 0; }
        allocVectorPointers(K, numDims);
        if( tmp ){
            delete [] tmp; tmp = 0;
        }
        tmp = new num_type[numDims]();
        
        // allocate adaptive stuff if needed
        if( btable.isAdaptive() ){
            
            if( y1 ){ delete [] y1; y1 = 0; }
            y1 = new num_type[numDims]();
            
            if( y2 ){ delete [] y2; y2 = 0; }
            y2 = new num_type[numDims]();
        }
        
    }
    
    HEADER
    void BUTCHER::setCentralSimState( sim::state<T> & cs ){
        sim_state = &cs;
    }

    HEADER
    void BUTCHER::adaptiveIntegration( num_type time, num_type dt , num_type* inOutState, DynamicList & list ){
        num_type finalTime = time + dt;
        num_type newTime = time;
        num_type maxErr = 0.0;
        bool isNotDone = true;
        
        sim_state->setStateRef( tmp );
        for (int k = 0; k < list.size(); k++) {
            list[k]->initLocalState();
        }
        
        
        while( isNotDone ){
            maxErr = -1.0;
            newTime = time;
            
            
            //#pragma omp parallel for
            for(int i = 0; i < numDims; i++ ){
                y1[i] = inOutState[i];
                y2[i] = inOutState[i];
            }
            
            if( btable.isExplicit() ){
                
                for(int i = 0; i < btable.numSteps(); i++){
                    
                    // set tmp = y_n
                    //#pragma omp parallel for
                    for(int j = 0; j < numDims; j++ ){
                        tmp[j] = inOutState[j];
                    }
                    
                    // compute Y = y_n + sum_{j} a(i,j) K_j
                    for(int j = 0; j < i; j++ ){
                        if( btable.a(i,j) != 0.0 ){
                            
                            //#pragma omp parallel for
                            for(int k = 0; k < numDims; k++ ){
                                tmp[k] += (dt*btable.a(i, j))*K[j][k];
                            }
                        }
                    }
                    
                    if( i != 0 ){
                        
                        //#pragma omp parallel for
                        for (int k = 0; k < list.size(); k++) {
                            list[k]->update();
                        }
                    }
                    
                    // compute K_i = f( t + ci*dt, Y )
                    computeDerivatives( time + btable.c(i)*dt, K[i], list );
                }
            }
            
            
            // Compute y_{n+1} = y_{n} + sum_{l} b(l)*K_l
            for(int i = 0; i < numDims; i++ ){
                
                //#pragma omp parallel for
                for( int l = 0; l < btable.numSteps(); l++ ){
                    if( btable.b(0, l) != 0.0 ){
                        y1[i] += (dt*btable.b(0, l)*K[l][i]);
                    }
                    if( btable.b(1, l) != 0.0 ){
                        y2[i] += (dt*btable.b(1, l)*K[l][i]);
                    }
                }
                maxErr = fmax(fabs( (y2[i] - y1[i]) ),maxErr);
            }
            
            num_type new_dt = newStepSize(dt, maxErr);
            
            newTime += new_dt;
            if( new_dt >= dt ){
                if( time + dt >= finalTime ){
                    isNotDone = false;
                }
                
                //#pragma omp parallel for
                for(int i = 0; i < numDims; i++ ){
                    inOutState[i] = y2[i];
                }
                if( isNotDone ){
                    
                    //#pragma omp parallel for
                    for (int i = 0; i < list.size(); i++) {
                        (*list[i]).update();
                    }
                }
                time += dt;
            }
            
            dt = std::min(new_dt,finalTime - time);
        }
        
        // set result
        sim_state->setStateRef( inOutState );
        for (int k = 0; k < list.size(); k++) {
            list[k]->initLocalState();
        }
        
    }
        
    HEADER
    void BUTCHER::nominalIntegration( num_type time, num_type dt , num_type* inOutState, DynamicList & list ){
        
        if( btable.isExplicit() ){
            
            sim_state->setStateRef( tmp );
            for (int k = 0; k < list.size(); k++) {
                list[k]->initLocalState();
            }
            
            for(int i = 0; i < btable.numSteps(); i++){
                
                // set tmp = y_n
                //#pragma omp parallel for
                for(int j = 0; j < numDims; j++ ){
                    tmp[j] = inOutState[j];
                }
                
                // compute Y = y_n + sum_{j} a(i,j) K_j
                
                for(int j = 0; j < i; j++ ){
                    if( btable.a(i,j) != 0.0 ){
                        //#pragma omp parallel for
                        for(int k = 0; k < numDims; k++ ){
                            tmp[k] += (dt*btable.a(i, j))*K[j][k];
                        }
                    }
                }
                
                if( i != 0 ){
                    for (int k = 0; k < list.size(); k++) {
                        list[k]->update();
                    }
                }
                
                // compute K_i = f( t + ci*dt, Y )
                computeDerivatives( time + btable.c(i)*dt, K[i], list );
            }
        }else{
            
        }
        
        
        // Compute y_{n+1} = y_{n} + sum_{l} b(l)*K_l
        for( int l = 0; l < btable.numSteps(); l++ ){
            if( btable.b(0, l) != 0.0 ){
                for(int i = 0; i < numDims; i++ ){
                    inOutState[i] += (dt*btable.b(0, l)*K[l][i]);
                }
            }
        }
        
        // set result
        sim_state->setStateRef(inOutState);
        for (int k = 0; k < list.size(); k++) {
            list[k]->initLocalState();
        }
    }
        
    HEADER
    void BUTCHER::integrate( num_type time, num_type dt , DynamicList & list){
        if( btable.isAdaptive() ){
            adaptiveIntegration(time, dt, *sim_state->getStateRef(), list);
        }else{
            nominalIntegration(time, dt, *sim_state->getStateRef(), list);
        }
    }

    HEADER
    void BUTCHER::computeNewStep( num_type * y0, num_type* dydt, num_type dt, num_type * out){
        
        //#pragma omp parallel for
        for (int i = 0; i < numDims; i++) {
            out[i] = y0[i] + dt*dydt[i];
        }
    }

        
    HEADER
    void BUTCHER::computeDerivatives( num_type time, num_type * dqdt, DynamicList & list ){
        local::state<num_type> dqdt_;
        dqdt_.setReferenceAddress(&dqdt);
        int ndim, start_idx = 0;
        for (int i = 0; i < list.size(); i++) {
            ndim = list[i]->numDims();
            dqdt_.setNumDims(ndim);
            dqdt_.setStartIndex(start_idx);
            dqdt_.setDataAddress();
            (*list[i])(time, dqdt_);
            start_idx += ndim;
        }
    }
    
    
    template class butcher<float>;
    template class butcher<double>;

}
