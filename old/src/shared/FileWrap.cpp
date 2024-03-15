//
//  FileWrap.cpp
//  TechInterviewPractice
//
//  Created by Christian J Howard on 12/12/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "FileWrap.hpp"

//FILE* fp;
//enum AccessMode { Read=0, Write, Append, ReadUpdate, WriteUpdate, AppendUpdate };

namespace wrap {

    file::file(){
        fp = 0;
    }
    file::file( const char* filename , AccessMode mode ):fp(0){
        openFile(filename, mode);
    }
    file::file( const std::string & filename, AccessMode mode ):fp(0){
        openFile(filename, mode);
    }
    void file::clear(){
        if( isOpen() ){ fclose(fp); }
    }

    file::~file(){
        clear();
    }

    bool file::isOpen() const{
        return (fp != 0);
    }
    
    void file::close() { clear(); }
    
    void file::openFile( const char* filename, AccessMode mode ){
        clear();
        
        char m[3] = {'r','\0','\0'};
        
        switch (mode) {
            case AccessMode::Read:
                break;
            case AccessMode::Write:
                m[0] = 'w';
                break;
            case AccessMode::Append:
                m[0] = 'a';
                break;
            case AccessMode::ReadUpdate:
                m[1] = '+';
                break;
            case AccessMode::WriteUpdate:
                m[0] = 'w'; m[1] = '+';
                break;
                
            case AccessMode::AppendUpdate:
                m[0] = 'a'; m[1] = '+';
                break;
        }
        
        fp = fopen(filename, &m[0]);
    }
    void file::openFile( const std::string & filename, AccessMode mode ){
        openFile(filename.c_str(), mode);
    }
    void file::resetFile(){
        if( isOpen() ){ rewind(fp); }
    }

    FILE*  file::ref() const { return fp; }

    file::operator FILE* () const {
        return fp;
    }

}
