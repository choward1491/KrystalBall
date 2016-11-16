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

namespace models {
    template<typename T> class list;
}


namespace sim {
    
    template<typename T> class state;
    
    template<typename Sim, typename T = double >
    class base {
    public:
        
        base();
        ~base();
        void run();
        void addConfigFile( const char * filename );
        void addConfigFile( const std::string & filename );
        double getTime() const;
        int getCompletedMC() const;
        void setSimHistoryPath( const std::string & filepath );
        void addDynamics( DynamicModel * model );
        void addDiscrete( DiscreteModel * model , double computationFrequency );
        void willWriteSimHistory( bool trueOrFalse );
        
        template<typename T>
        T get(const std::string & param);
        
    protected:
        
    private:
        state<T> state;
        models::list<T> model_list;
    };
    
    
}

#endif /* sim_base_h */
