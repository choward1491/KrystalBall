//
//  sim_state.hpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/13/16.
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

#ifndef sim_state_hpp_
#define sim_state_hpp_


#include <run_time_base/sim/sim_scheduler.hpp>
#include <run_time_base/model/discrete_model.hpp>
#include <string>
#include <stdint.h>

class fraction;
typedef fraction Time;

namespace print {
    template<typename T> class history;
}

namespace sim {
    
    template<typename T = double>
    class state {
    public:
        typedef T num_type;
        
        state();
        ~state();
        
        void allocate(int num_state);
        void setStateRef( num_type* ref );
        num_type** getStateRef();
        num_type getCurrentTime() const;
        int size() const;
        
        void setCurrentTime( const num_type & t );
        void setCurrentTime( const Time & t);
        Time & getTime();
        const Time & getTime() const;
        
        scheduler<T> & getScheduler();
        const scheduler<T> & getScheduler() const;
        
        print::history<T> & getPrinter();
        const print::history<T> & getPrinter() const;
        void willWriteHistory( bool trueOrFalse );
        bool isWritingHistory() const;
        void writeHistoryAtRate( double rateHz );
        void setSimHistoryFile( const std::string & filename );
        void addHistoryWriterToScheduler();
        
        void addDiscreteModelToScheduler( num_type rateHz, discrete::model<T> & model);
        
        void setRNGSeed( int seed = 17 );
        double rand();
        uint64_t randInt();
        double gaussRand( double mean = 0.0, double sig = 1.0 );
        
        
        template<typename U>
        U get(const std::string & param);
        void addConfigFile( const std::string & file );
        void addConfigFile( const char * file );
        
    private:
        struct Data;
        Data* data;
    };
    
}

#endif /* sim_state_hpp */
