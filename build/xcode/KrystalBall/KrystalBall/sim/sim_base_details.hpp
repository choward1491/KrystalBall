//
//  sim_base_details.hpp
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

#ifndef sim_base_details_h
#define sim_base_details_h

#include "sim_base.hpp"

namespace sim {
    
#define HEADER template<typename Sim, typename T>
#define BASE base<Sim,T>
#define CRTP(func) static_cast<typename Sim::type*>(this)->func
#define CRTP_Time(func) static_cast<Sim*>(this)->func
    
    HEADER
    BASE::base():numCompleteMC(0),didSetup(false) {
        
    }
    
    HEADER
    BASE::~base() {
        
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
        CRTP(finalize());
    }
    
    HEADER
    void BASE::initialize(){
        
        if( !didSetup ){
            state.addHistoryWriterToScheduler();
            CRTP(linkModelsToSim());          // add other models to sim
            CRTP(buildTotalDynamicState());   // build dynamic state array
            CRTP_Time(setupTimeIntegration());     // initialize integration
            model_list.setCentralSimState(state);
            setupSimHistory();                // add variables that will be printed
            CRTP(connectModelsTogether());    // connect models together if needed
            didSetup = true;
        }
        
    }
    
    
    
    HEADER
    void BASE::initializeModels() {
        model_list.init();
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
        while( !CRTP(isMonteCarloDone()) ) {    // loop through all monte carlo draws
            MonteCarloSetup(numCompleteMC);     // setup iMCth monte carlo sim
            runIndividualSim();                 // run an individual sim
            CRTP(finalizeMonteCarloRun());      // finalize latest individual sim
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
        
        if( state.isWritingHistory() ){       // if writing a sim history,
            state.getPrinter().update();    // update output sim history
        }                                   // file with initial condition
    }
    
    HEADER
    void BASE::runIndividualSim() {
        while( !CRTP(finishedSimulation()) ){
            runTimeStep();
        }
    }
    
    HEADER
    void BASE::runTimeStep() {
        printf("hi there\n");
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
    typename BASE::num_type BASE::getTime() const {
        return state.getCurrentTime();
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
    
    /*
        state<T> state;
        models::list<T> model_list;
     */
#undef HEADER
#undef BASE
    
}

#endif /* sim_base_details_h */
