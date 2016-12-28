//
//  butcher_integrator.hpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/24/16.
//
//  The MIT License (MIT)
//    Copyright © 2016 Christian Howard. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
//

#ifndef butcher_integrator_hpp
#define butcher_integrator_hpp

#include <run_time_base/integrator/butcher_table.hpp>
#include <run_time_base/model/dynamic_model.hpp>
#include <vector>

namespace sim   { template<typename T> class state; }

namespace integrate {
    
    template<typename T>
    class butcher {
    public:
        typedef T num_type;
        typedef dynamic::model<T>       dyn_m;
        typedef std::vector<dyn_m*>     DynamicList;
        
        butcher();
        ~butcher();
        void setNumDimensions( int numDimensions );
        void integrate( num_type time, num_type dt, DynamicList & list);
        void setTolerance( num_type tol );
        void setCentralSimState( sim::state<T> & cs );
        num_type getTolerance() const;
        
    protected:
        table::butcher<num_type> btable;
        
    private:
        num_type tol;
        int numDims;
        virtual num_type newStepSize( num_type dt, num_type error ){ return dt; }
        void computeNewStep( num_type * y0, num_type* dydt, num_type dt, num_type * out);
        void computeDerivatives( num_type time, num_type * dqdt, DynamicList & list );
        void adaptiveIntegration( num_type time, num_type dt , num_type* inOutState, DynamicList & list );
        void nominalIntegration( num_type time, num_type dt , num_type* inOutState, DynamicList & list );
        std::vector<num_type*> K;
        num_type *tmp;
        num_type *y1, *y2; // for adaptive stuff
        sim::state<T> * sim_state;
        std::vector<bool>    hasComputed;
        
    };
    
}

#endif /* butcher_integrator_hpp */
