//
//  sim_base.hpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/15/16.
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

#ifndef sim_base_h
#define sim_base_h

#include "model_list.hpp"
#include "sim_state.hpp"
#include "discrete_model.hpp"
#include "dynamic_model.hpp"

namespace sim {
    
    
    template<typename Sim, typename T = double >
    class base {
    public:
        typedef T num_type;
        base();
        ~base();
        void run();
        void addConfigFile( const char * filename );
        void addConfigFile( const std::string & filename );
        num_type getTime() const;
        int getCompletedMC() const;
        void setSimHistoryPath( const std::string & filepath );
        void addDynamics( dynamic::model<T> & model );
        void addDiscrete( discrete::model<T> & model , num_type computationFrequency );
        void willWriteSimHistory( bool trueOrFalse );
        
        template<typename U>
        U get(const std::string & param) { return state.get(param); }
        
    protected:
        
        state<T> & getState();
        models::list<T> & getModelList();
        const state<T> & getState() const;
        const models::list<T> & getModelList() const;
        int getNumCompleteMonteCarlo() const;
        
    private:
        
        state<T> state;
        models::list<T> model_list;
        int numCompleteMC;
        bool didSetup;
        
        void initialize();              // Method to initialize everything before running a simulation
        void initializeModels();        // method to initialize models
        void setupSimHistory();         // method to setup sim history
        void MonteCarloSetup( int monteCarloCount ); // method to setup ith monte carlo draws
        void runIndividualSim();        // method to run an individual simulation
        void runTimeStep();
        void runMonteCarloSim();        // method to run a whole Monte Carlo sim (calls runIndividualSim)
        
        // CRTP methods to be implemented
        //bool isMonteCarloDone();
        //void linkModelsToSim();         // method to link models to sim
        //void connectModelsTogether();   // method to connect models together, if necessary
        //bool finishedSimulation();      // method to return whether the sim has finished
        //void finalizeMonteCarloRun();   // method to finalize a monte carlo run
        //void finalize();                // method to finalize the whole completed simulation
        //void buildTotalDynamicState();  // method to construct the total data associated with dynamic models
        //void setupTimeIntegration();    // method to setup any time integration stuff
        
    };
    
    
}


#include "sim_base_details.hpp"


#endif /* sim_base_h */
