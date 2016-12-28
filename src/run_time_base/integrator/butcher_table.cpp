//
//  butcher_table.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/24/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include <run_time_base/integrator/butcher_table.hpp>

namespace integrate {
    namespace table {
#define HEADER template<typename T>
#define BUTCHER butcher<T>
        
        HEADER
        BUTCHER::butcher(){
            
        }
        
        HEADER
        BUTCHER::butcher( int size, int num_compute ){
            resize(size,num_compute);
        }

        
        HEADER
        void BUTCHER::resize( int size, int num_compute ){
            dim = size;
            num_estimates = num_compute;
            c_.resize(size);
            a_.resize(size*size);
            b_.resize(num_compute*size);
        }
        
        HEADER
        int BUTCHER::numSteps() const {
            return dim;
        }
        
        HEADER
        int BUTCHER::numEstimates() const {
            return num_estimates;
        }
        
        HEADER
        typename BUTCHER::num_type & BUTCHER::c(int i){
            return c_[i];
        }
        
        HEADER
        typename BUTCHER::num_type & BUTCHER::b(int row, int column){
            return b_[column + row*dim];
        }
        
        HEADER
        typename BUTCHER::num_type & BUTCHER::a(int row, int column){
            return a_[column + row*dim];
        }
        
        HEADER
        const typename BUTCHER::num_type & BUTCHER::c(int i) const{
            return c_[i];
        }
        
        HEADER
        const typename BUTCHER::num_type & BUTCHER::b(int row, int column) const{
            return b_[column + row*dim];
        }
        
        HEADER
        const typename BUTCHER::num_type & BUTCHER::a(int row, int column) const{
            return a_[column + row*dim];
        }

        HEADER
        bool BUTCHER::isAdaptive() const{
            return num_estimates > 1;
        }

        HEADER
        bool BUTCHER::isImplicit() const{
            for(int i = 0; i < dim; i++ ){
                for(int j = i; j < dim; j++){
                    if( a(i,j) != 0.0 ){
                        return true;
                    }
                }
            }
            return false;
        }
        
        HEADER
        bool BUTCHER::isExplicit() const{
            return !isImplicit();
        }
        
        template class butcher<float>;
        template class butcher<double>;

    }
}
