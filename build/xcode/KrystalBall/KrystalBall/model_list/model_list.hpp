//
//  model_list.hpp
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

#ifndef model_list_hpp
#define model_list_hpp

#include <stdio.h>
#include <vector>
#include <memory>

namespace discrete {
    template<typename T> class model;
}

namespace dynamic {
    template<typename T> class model;
}

namespace sim {
    template<typename T> class state;
}


namespace models {
    template<typename T = double>
    class list {
    public:
        typedef dynamic::model<T>       dyn_m;
        typedef discrete::model<T>      dscrt_m;
        typedef std::vector<dyn_m*>     DynamicList ;
        typedef std::vector<dscrt_m*>   DiscreteList;
        typedef T num_type;
        
        list();
        ~list();
        void init();
        void addDynamicModel ( dyn_m & model );
        void addDiscreteModel( dscrt_m & model);
        void setCentralSimState( sim::state<T> & cs );
        void updateChangesToSimState();
        int  getTotalNumberStates() const;
        void updateDynamicModels();
        sim::state<T> & getSimState();
        const DynamicList & getDynamicList() const;
        const DiscreteList& getDiscreteList() const;
        DynamicList & getDynamicList() ;
        DiscreteList& getDiscreteList() ;
        
    private:
        struct Data;
        Data* data;
    };
}





#endif /* model_list_hpp */
