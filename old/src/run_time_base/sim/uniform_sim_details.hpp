//
//  uniform_sim_details.hpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/17/16.
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

#ifndef uniform_sim_details_h
#define uniform_sim_details_h

#include "uniform_sim.hpp"
#include "PreciseTime.h"

namespace sim {
    
    template<typename T, template<typename> class Integrator>
    void uniform<T,Integrator>::setupTimeIntegration() {
        integ.setNumDimensions( this->getState().size() );
        integ.setCentralSimState( this->getState() );
    }

    template<typename T, template<typename> class Integrator>
    Integrator<T> & uniform<T,Integrator>::getIntegrator() {
        return integ;
    }
    
    template<typename T, template<typename> class Integrator>
    void uniform<T,Integrator>::simulateTimeStep( typename base<T>::num_type dt ) {
        integ.integrate( static_cast<num_type>(this->getState().getTime()), dt,
                         this->getModelList().getDynamicList() );
    }
    
    template<typename T, template<typename> class Integrator>
    void uniform<T,Integrator>::buildTotalDynamicState() {
        sim::state<T> & s = this->getState();
        models::list<T> & ml = this->getModelList();
        if( s.size() == 0 ){
            s.allocate( ml.getTotalNumberStates() );
            ml.setCentralSimState(s);
        }
        
    }
    
}


#endif /* uniform_sim_details_h */
