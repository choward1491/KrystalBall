//
//  dynamic.hpp
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

#ifndef dynamic_hpp
#define dynamic_hpp

#include <stdio.h>
#include <string>
#include <memory>

namespace local { template<typename T> class state; }
namespace sim   { template<typename T> class state; }
namespace print { template<typename T> class history; }

namespace dynamic {
    
    template<typename T = double>
    class model {
    public:
        typedef T num_type;
        typedef local::state<T> ModelState;
        
        model();
        virtual ~model();
        virtual std::string name() const;
        
        virtual void init();
        virtual void update();
        virtual int  numDims() const;
        virtual void operator()( num_type & time, ModelState & dqdt );
        
        virtual void setupPrintData( print::history<T> & p );
        void setCentralSimState( sim::state<T> & cs );
        
    protected:
        sim::state<T> & getCentralSimState();
        
    private:
        
        struct ModelData;
        std::unique_ptr<ModelData> data;
    };
    
}

#endif /* dynamic_hpp */
