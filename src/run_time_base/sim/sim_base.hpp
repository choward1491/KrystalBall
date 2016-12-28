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

#include <run_time_base/model_list/model_list.hpp>
#include <run_time_base/sim/sim_state.hpp>
#include <run_time_base/model/discrete_model.hpp>
#include <run_time_base/model/dynamic_model.hpp>

class fraction;
typedef fraction Time;

namespace sim {
    
    
    template<typename T = double >
    class base {
    public:
        typedef T num_type;
        typedef state<T> State;
        
        base();
        virtual ~base() = default;
        void run();
        void addConfigFile( const char * filename );
        void addConfigFile( const std::string & filename );
        Time getTime() const;
        int getCompletedMC() const;
        void addDynamics( dynamic::model<T> & model );
        void addDiscrete( discrete::model<T> & model , num_type computationFrequency );
        void setSimHistoryPath( const std::string & filepath );
        void willWriteSimHistory( bool trueOrFalse );
        void setSimHistoryRate( double printRateHz );
        
        template<typename U>
        U get(const std::string & param) { return state.get(param); }
        
    protected:
        
        State & getState();
        models::list<T> & getModelList();
        const State & getState() const;
        const models::list<T> & getModelList() const;
        int getNumCompleteMonteCarlo() const;
        
    private:
        
        struct ModelQueue {
            typedef discrete::model<num_type> d_model;
            ModelQueue();
            void addModel( d_model* model );
            d_model* popModel();
            int numModels() const;
            
        private:
            std::vector< d_model* > d_queue;
            int num_used;
        };
        
        
        state<T> state;
        models::list<T> model_list;
        ModelQueue m_queue;
        int numCompleteMC;
        bool didSetup;
        
        void initialize();              // Method to initialize everything before running a simulation
        void initializeModels();        // method to initialize models
        void setupSimHistory();         // method to setup sim history
        void MonteCarloSetup( int monteCarloCount ); // method to setup ith monte carlo draws
        void runIndividualSim();        // method to run an individual simulation
        void runTimeStep();
        void runMonteCarloSim();        // method to run a whole Monte Carlo sim (calls runIndividualSim)
        
        // polymorphic functions to be defined in subclassed simulations
        virtual bool isMonteCarloDone();
        virtual void linkModelsToSim();         // method to link models to sim
        virtual void connectModelsTogether();   // method to connect models together, if necessary
        virtual bool finishedSimulation();      // method to return whether the sim has finished
        virtual void finalizeMonteCarloRun();   // method to finalize a monte carlo run
        virtual void finalize();                // method to finalize the whole completed simulation
        virtual void buildTotalDynamicState();  // method to construct the total data associated with dynamic models
        virtual void setupTimeIntegration();    // method to setup any time integration stuff
        virtual void simulateTimeStep( num_type dt ); // method to do single simulation integration step for all dynamic models
        
    };
    
    
}



#endif /* sim_base_h */
