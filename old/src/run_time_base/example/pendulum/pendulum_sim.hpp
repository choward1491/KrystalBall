//
//  pendulum_sim.hpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/27/16.
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

#ifndef pendulum_sim_hpp
#define pendulum_sim_hpp

#include "uniform_sim.hpp"
#include "explicit_euler.hpp"
#include "runge_kutta4.hpp"
#include "cashkarp_rk45.hpp"
#include "bogacki_shampine23.hpp"
#include "pendulum_model.hpp"
#include "Timer.hpp"
#include "time_step.hpp"

namespace pendulum {
    
    typedef double type;
    
    class simulation : public sim::uniform<type,integrate::cashkarp_rk45> {
    public:
        simulation();
        ~simulation() = default;
        
    private:
        pendulum::model pm;
        time_step<type> ts;
        Timer timer;
        bool isMonteCarloDone();
        void linkModelsToSim();         // method to link models to sim
        bool finishedSimulation();      // method to return whether the sim has finished
        void finalizeMonteCarloRun();   // method to finalize a monte carlo run
        void finalize();
    };
    
    
}

#endif /* pendulum_sim_hpp */
