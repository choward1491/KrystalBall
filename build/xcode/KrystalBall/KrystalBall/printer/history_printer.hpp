//
//  history_printer.hpp
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

#ifndef history_printer_hpp
#define history_printer_hpp

#include "discrete_model.hpp"
#include <string>

namespace print {
    
    template<typename T = double>
    class history : public discrete::model<T> {
    public:
        history();
        ~history();
        virtual std::string name() const;
        virtual void init();
        virtual void update();
        void setupNewMonteCarlo() const;
        
        template<typename U>
        void addVariableToPrint( U & var, const std::string & name );
        
    private:
        struct Data;
        Data* data;
        void writeDataToFile( FILE* file ) const;
        void writeNameHeader( FILE* file ) const;
    };
}

#endif /* history_printer_hpp */
