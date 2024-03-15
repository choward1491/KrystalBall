//
//  butcher_table.hpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/24/16.
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

#ifndef butcher_table_hpp
#define butcher_table_hpp

#include <vector>

namespace integrate {
    namespace table {
        
        template<typename T>
        class butcher {
        public:
            typedef T num_type;
            
            butcher();
            butcher( int size, int num_compute = 1 );
            void resize( int size, int num_compute = 1 );
            
            num_type & c(int i);
            num_type & b(int row, int column);
            num_type & a(int row, int column);
            const num_type & c(int i) const;
            const num_type & b(int row, int column) const;
            const num_type & a(int row, int column) const;
            
            bool isImplicit() const;
            bool isExplicit() const;
            bool isAdaptive() const;
            
            int numSteps() const;
            int numEstimates() const;
            
        private:
            int dim;
            int num_estimates;
            std::vector<num_type> c_;
            std::vector<num_type> a_;
            std::vector<num_type> b_;
        };
    }
}

#endif /* butcher_table_hpp */
