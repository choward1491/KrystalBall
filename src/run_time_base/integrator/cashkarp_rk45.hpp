//
//  cashkarp_rk45.hpp
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

#ifndef cashkarp_rk45_hpp
#define cashkarp_rk45_hpp

#include "butcher_integrator.hpp"

namespace integrate {
    
    template<typename T>
    class cashkarp_rk45 : public butcher<T> {
    public:
        typedef T num_type;
        cashkarp_rk45();
    private:
        num_type newStepSize( num_type dt, num_type error );
    };
    
}

#endif /* cashkarp_rk45_hpp */
