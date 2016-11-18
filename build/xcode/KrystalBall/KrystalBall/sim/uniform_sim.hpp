//
//  uniform_sim.hpp
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

#ifndef uniform_sim_h
#define uniform_sim_h

#include "sim_base.hpp"

namespace sim {
    
    
    
    template<class Sim,typename T, template<typename> class Integrator>
    class uniform : public base<uniform<Sim, T, Integrator>,T> {
    public:
        typedef Sim type;
        typedef base<uniform<Sim, T, Integrator>,T> base;
        uniform() = default;
        Integrator<T> & getIntegrator();
        
    private:
        friend base;
        Integrator<T> integ;
        void setupTimeIntegration();    // method to setup any time integration stuff
        
        // CRTP functions to implement
        /*
        bool isMonteCarloDone();
        void linkModelsToSim();         // method to link models to sim
        void connectModelsTogether();   // method to connect models together, if necessary
        bool finishedSimulation();      // method to return whether the sim has finished
        void finalizeMonteCarloRun();   // method to finalize a monte carlo run
        void finalize();                // method to finalize the whole completed simulation
        void buildTotalDynamicState();  // method to construct the total data associated with dynamic models
         */
    };
    
}

#include "uniform_sim_details.hpp"

#endif /* uniform_sim_h */
