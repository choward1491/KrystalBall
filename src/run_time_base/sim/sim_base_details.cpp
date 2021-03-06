//
//  sim_base_details.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/16/16.
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

#include "sim_base.hpp"
#include "history_printer.hpp"
#include "PreciseTime.h"
#include <math.h>

namespace sim {
    
#define HEADER template<typename T>
#define BASE base<T>
#define MQ BASE::ModelQueue
    
    HEADER
    MQ::ModelQueue():d_queue(20,nullptr),num_used(0) {
        
    }
    
    HEADER
    void MQ::addModel( d_model* model ) {
        if( num_used == d_queue.size() ){ d_queue.resize(num_used*2); }
        d_queue[num_used] = model; ++num_used;
    }
    
    HEADER
    typename MQ::d_model* MQ::popModel() {
        num_used = std::max(num_used-1,0);
        d_model* m = d_queue[num_used];
        d_queue[num_used] = nullptr;
        return m;
    }
    
    HEADER
    int MQ::numModels() const {
        return num_used;
    }
    
    
    HEADER
    BASE::base():numCompleteMC(0),didSetup(false),m_queue() {
        
    }
    
    HEADER
    state<T> & BASE::getState(){
        return state;
    }
    
    HEADER
    models::list<T> & BASE::getModelList() {
        return model_list;
    }
    
    HEADER
    const state<T> & BASE::getState() const {
        return state;
    }
    
    HEADER
    const models::list<T> & BASE::getModelList() const {
        return model_list;
    }
    
    HEADER
    int BASE::getNumCompleteMonteCarlo() const {
        return numCompleteMC;
    }
    
    HEADER
    void BASE::run() {
        initialize();
        runMonteCarloSim();
        finalize();
    }
    
    HEADER
    void BASE::initialize(){
        
        if( !didSetup ){
            state.addHistoryWriterToScheduler();
            linkModelsToSim();          // add other models to sim
            buildTotalDynamicState();   // build dynamic state array
            setupTimeIntegration();     // initialize integration
            model_list.setCentralSimState(state);
            setupSimHistory();          // add variables that will be printed
            connectModelsTogether();    // connect models together if needed
            didSetup = true;
        }
        
    }
    
    
    
    HEADER
    void BASE::initializeModels() {
        model_list.init();
        model_list.updateDynamicModels();
    }
    
    HEADER
    void BASE::setupSimHistory() {
        const typename models::list<T>::DynamicList & dyn_list = model_list.getDynamicList();
        const typename models::list<T>::DiscreteList & disc_list = model_list.getDiscreteList();
        print::history<T> & printer = state.getPrinter();
        
        for(int i = 0; i < dyn_list.size(); ++i ){
            dyn_list[i]->setupPrintData( printer );
        }
        
        for(int i = 0; i < disc_list.size(); ++i ){
            disc_list[i]->setupPrintData( printer );
        }
    }
    
    
    HEADER
    void BASE::runMonteCarloSim() {
        numCompleteMC = 0;
        while( !isMonteCarloDone() ) {    // loop through all monte carlo draws
            MonteCarloSetup(numCompleteMC);     // setup iMCth monte carlo sim
            runIndividualSim();                 // run an individual sim
            finalizeMonteCarloRun();      // finalize latest individual sim
            ++numCompleteMC;
        }
    }
    
    HEADER
    void BASE::MonteCarloSetup(int monteCarloCount ) {
        initializeModels();     // Initialize models for ith MC run
        
        if( monteCarloCount >= 0 ){     // If new monte carlo run, reset everything
            state.getScheduler().reset();
            state.setCurrentTime( num_type(0.0) );
            
            if( state.isWritingHistory() ){
                if( monteCarloCount != 0 ){
                    state.getPrinter().addEmptyLine();
                }else{
                    state.getPrinter().reset();
                }
            }
        }
        
        if( state.isWritingHistory() ){     // if writing a sim history,
            state.getPrinter().update();    // update output sim history
        }                                   // file with initial condition
    }
    
    HEADER
    void BASE::runIndividualSim() {
        while( !finishedSimulation() ){
            runTimeStep();
        }
    }
    
    HEADER
    void BASE::runTimeStep() {
        discrete::model<num_type> * d_ptr = nullptr;
        sim::scheduler<num_type> & s = state.getScheduler();
        Time & currentTime  = state.getTime();
        Time   nextTime     = s.getNextTime();
        
        
        // 1) get all discrete models that happen at time t_{i+1}
        while( s.size() > 0 && nextTime == s.getRootKey() ){
            m_queue.addModel(s.pop());
        }
        
        // 2) simulate up to time t_{i+1} and update auxilary vars
        num_type dt = static_cast<num_type>(nextTime) - static_cast<num_type>(currentTime);
        simulateTimeStep(dt);
        model_list.updateDynamicModels();
        
        // 3) update time to new time
        currentTime = nextTime;
        
        // 4) execute models in queue that must run at time t_{i+1}
        // 5) add models to scheduler based on their next runtime
        while( m_queue.numModels() != 0 ) {
            d_ptr = m_queue.popModel();
            d_ptr->update();
            s.addNewModel( d_ptr->getNextUpdateTime(nextTime), d_ptr);
        }
    }
    
    
    HEADER
    void BASE::addConfigFile( const char * filename ) {
        state.addConfigFile( filename );
    }
    
    HEADER
    void BASE::addConfigFile( const std::string & filename ) {
        state.addConfigFile(filename);
    }
    
    HEADER
    Time BASE::getTime() const {
        return state.getTime();
    }
    
    HEADER
    int BASE::getCompletedMC() const {
        return numCompleteMC;
    }
    
    HEADER
    void BASE::setSimHistoryPath( const std::string & filepath ) {
        state.setSimHistoryFile(filepath);
    }
    
    HEADER
    void BASE::addDynamics( dynamic::model<T> & model ) {
        model_list.addDynamicModel( model );
    }
    
    HEADER
    void BASE::addDiscrete( discrete::model<T> & model , num_type computationFrequency ) {
        model_list.addDiscreteModel( model );
        state.addDiscreteModelToScheduler( computationFrequency, model);
    }
    
    HEADER
    void BASE::willWriteSimHistory( bool trueOrFalse ) {
        state.willWriteHistory( trueOrFalse );
    }
    
    HEADER
    void BASE::setSimHistoryRate( double printRateHz ) {
        state.writeHistoryAtRate(printRateHz);
    }
    
    HEADER
    bool BASE::isMonteCarloDone() { return true; }
    
    HEADER
    void BASE::linkModelsToSim() {}
    
    HEADER
    void BASE::connectModelsTogether() {}
    
    HEADER
    bool BASE::finishedSimulation() { return true; }
    
    HEADER
    void BASE::finalizeMonteCarloRun() {}
    
    HEADER
    void BASE::finalize() {}
    
    HEADER
    void BASE::buildTotalDynamicState(){}
    
    HEADER
    void BASE::setupTimeIntegration() {}
    
    HEADER
    void BASE::simulateTimeStep( num_type dt ) {}
    
    
#undef HEADER
#undef BASE
    
}

template class sim::base<float>;
template class sim::base<double>;
