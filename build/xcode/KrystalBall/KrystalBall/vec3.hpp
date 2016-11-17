//
//  vec.hpp
//  Geom3
//
//  Created by Christian J Howard on 9/24/16.
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

#ifndef vec3_h
#define vec3_h

#include "math_bundle.hpp"

template<typename data_type >
class vec<3,data_type> {
public:
    static const int D = 3;
    
    vec(){
        d[0] = d[1] = d[2] = data_type();
    }
    
    vec( data_type x, data_type y, data_type z){
        d[0] = x;
        d[1] = y;
        d[2] = z;
    }
    
    vec cross( const vec & v ) const {
        vec out;
        out.d[0] = d[1]*v.d[2] - d[2]*v.d[1];
        out.d[1] = d[2]*v.d[0] - d[0]*v.d[2];
        out.d[2] = d[0]*v.d[1] - d[1]*v.d[0];
        return out;
    }
    void cross( const vec & v, vec & output) const {
        output.d[0] = d[1]*v.d[2] - d[2]*v.d[1];
        output.d[1] = d[2]*v.d[0] - d[0]*v.d[2];
        output.d[2] = d[0]*v.d[1] - d[1]*v.d[0];
        return output;
    }
    // specify accessor methods
    data_type & operator[](int idx){ return d[idx];}
    const data_type & operator[](int idx) const { return d[idx]; }
    
    // specify norm-like methods
    data_type dot( const vec & v ) const {
        return d[0]*v.d[0] + d[1]*v.d[1] + d[2]*v.d[2];
    }
    data_type magnitude() const {
        return sqrt(magnitudeSquared());
    }
    data_type magnitudeSquared() const{
        return d[0]*d[0] + d[1]*d[1] + d[2]*d[2];
    }
    void normalize() {
        data_type mag = magnitude();
        d[0] /= mag;
        d[1] /= mag;
        d[2] /= mag;
    }
    vec getNormal() const {
        data_type mag = magnitude();
        return vec(d[0]/mag,d[1]/mag,d[2]/mag);
    }
    
    void operator=( const data_type & s ) {
        d[0] = d[1] = d[2] = s;
    }
    
    vec operator+( const vec & v ) const {
        return vec(d[0] + v.d[0], d[1] + v.d[1], d[2] + v.d[2]);
    }
    vec operator-( const vec & v ) const {
        return vec(d[0] - v.d[0], d[1] - v.d[1], d[2] - v.d[2]);
    }
    vec operator*( const vec & v ) const {
        return vec(d[0] * v.d[0], d[1] * v.d[1], d[2] * v.d[2]);
    }
    vec operator/( const vec & v ) const {
        return vec(d[0] / v.d[0], d[1] / v.d[1], d[2] / v.d[2]);
    }
    vec operator+( const data_type & d_ ) const {
        return vec(d[0] + d_, d[1] + d_, d[2] + d_);
    }
    vec operator-( const data_type & d_ ) const {
        return vec(d[0] - d_, d[1] - d_, d[2] - d_);
    }
    vec operator*( const data_type & d_ ) const {
        return vec(d[0] * d_, d[1] * d_, d[2] * d_);
    }
    vec operator/( const data_type & d_ ) const {
        return vec(d[0] / d_, d[1] / d_, d[2] / d_);
    }
    
    
    // print method
    void print() const{
        printf("[ %lf, %lf, %lf ]\n",(double)d[0],(double)d[1],(double)d[2]);
    }
    
protected:
    data_type d[D];
};


#endif /* vec3_h */
