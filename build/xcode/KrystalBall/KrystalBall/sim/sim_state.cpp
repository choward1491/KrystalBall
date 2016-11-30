//
//  sim_state.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/13/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "sim_state.hpp"
#include "sim_scheduler.hpp"
#include "history_printer.hpp"
#include "PreciseTime.h"
#include "Parser.hpp"
#include <vector>
#include "RandomNumberGenerator.hpp"

typedef RandomNumberGenerator RNG;

namespace sim {
    
#define HEADER template<typename T>
#define STATE state<T>
#define ITEM(func,out_type) HEADER\
            out_type STATE::func
    
    HEADER
    struct STATE::Data {
        Data():safety_ref(nullptr),dyn_state(nullptr){}
        num_type* safety_ref;
        num_type* dyn_state;
        int num_state = 0;
        Time time = 0.0;
        scheduler<T> scheduler;
        print::history<T> data_writer;
        bool doWriteData = false;
        num_type writeRate = 1;
        Parser parser;
        RNG rng;
    };
    
    HEADER
    print::history<T> & STATE::getPrinter() {
        return data->data_writer;
    }
    
    HEADER
    const print::history<T> & STATE::getPrinter() const {
        return data->data_writer;
    }
    
    HEADER
    void STATE::setRNGSeed( int seed ) {
        data->rng.setSeed(seed);
    }
    
    HEADER
    double STATE::rand() { return data->rng.rand(); }
    
    HEADER
    uint64_t STATE::randInt() { return data->rng.randInt(); }
    
    HEADER
    double STATE::gaussRand( double mean, double sig ) {
        return data->rng.gaussRand(mean,sig);
    }
    
    HEADER
    void STATE::willWriteHistory( bool trueOrFalse ){
        data->doWriteData = trueOrFalse;
    }
    
    ITEM(isWritingHistory() const, bool){
        return data->doWriteData;
    }
    
    HEADER
    void STATE::writeHistoryAtRate( double rateHz ) {
        data->writeRate = rateHz;
    }
    
    HEADER
    void STATE::addHistoryWriterToScheduler(){
        if( data->doWriteData ){
            addDiscreteModelToScheduler(data->writeRate, data->data_writer);
            data->data_writer.addVariableToPrint( data->time, "Time" );
        }
    }
    
    HEADER
    void STATE::setSimHistoryFile( const std::string & filename ) {
        data->data_writer.setFileToWriteTo(filename);
    }
    
    HEADER
    void STATE::addDiscreteModelToScheduler( num_type rateHz, discrete::model<T> & model) {
        model.setUpdateRate( rateHz );
        data->scheduler.addNewModel( model.getDt(), &model );
    }
    
    HEADER
    STATE::state(){
        data = new Data();
    }
    
    HEADER
    typename STATE::num_type** STATE::getStateRef(){
        return &data->dyn_state;
    }
    
    HEADER
    STATE::~state() {
        if( data ){
            data->dyn_state = nullptr;
            if( data->safety_ref ){ delete [] data->safety_ref; data->safety_ref = nullptr;}
            delete data; data = nullptr;
        }
    }
    
    HEADER
    int STATE::size() const {
        return data->num_state;
    }
    
    HEADER
    void STATE::allocate(int num_state_) {
        data->num_state = num_state_;
        if( data->safety_ref ){ delete [] data->safety_ref; data->safety_ref = data->dyn_state = nullptr; }
        data->safety_ref = new num_type[data->num_state];
        data->dyn_state = data->safety_ref;
    }
    
    HEADER
    void STATE::setStateRef( num_type* ref ){
        data->dyn_state = ref;
    }
    
    HEADER
    typename STATE::num_type STATE::getCurrentTime() const{
        return static_cast<num_type>(data->time);
    }
    
    HEADER
    void STATE::setCurrentTime( const num_type & t ){
        data->time = t;
    }
    
    HEADER
    void STATE::setCurrentTime( const Time & t) {
        data->time = t;
    }
    
    HEADER
    Time & STATE::getTime() {
        return data->time;
    }
    
    HEADER
    const Time & STATE::getTime() const {
        return data->time;
    }
    
    HEADER
    scheduler<T> & STATE::getScheduler() {
        return data->scheduler;
    }
    
    HEADER
    const scheduler<T> & STATE::getScheduler() const {
        return data->scheduler;
    }
    
    HEADER
    void STATE::addConfigFile( const std::string & file ) {
        data->parser.parse(file.c_str());
    }
    
    HEADER
    void STATE::addConfigFile( const char * file ) {
        data->parser.parse(file);
    }
    
    template<>
    template<>
    int state<float>::get(const std::string & param) {
        return data->parser.getValueFrom<double>( param );
    }
    
    template<>
    template<>
    float state<float>::get(const std::string & param) {
        return data->parser.getValueFrom<double>( param );
    }
    
    template<>
    template<>
    bool state<float>::get(const std::string & param) {
        return data->parser.getValueFrom<bool>( param );
    }
    
    template<>
    template<>
    std::vector<double> state<float>::get(const std::string & param) {
        return data->parser.getValueFrom< std::vector<double> >( param );
    }
    
    template<>
    template<>
    std::string state<float>::get(const std::string & param) {
        return data->parser.getValueFrom< std::string >( param );
    }
    
    template<>
    template<>
    int state<double>::get(const std::string & param) {
        return data->parser.getValueFrom<double>( param );
    }
    
    template<>
    template<>
    float state<double>::get(const std::string & param) {
        return data->parser.getValueFrom<double>( param );
    }
    
    template<>
    template<>
    bool state<double>::get(const std::string & param) {
        return data->parser.getValueFrom<bool>( param );
    }
    
    template<>
    template<>
    std::vector<double> state<double>::get(const std::string & param) {
        return data->parser.getValueFrom< std::vector<double> >( param );
    }
    
    template<>
    template<>
    std::string state<double>::get(const std::string & param) {
        return data->parser.getValueFrom< std::string >( param );
    }
    
    template class state<float>;
    template class state<double>;
    
}
