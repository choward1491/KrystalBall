//
//  history_printer.cpp
//  KrystalBall
//
//  Created by Christian J Howard on 11/13/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//


#include <vector>
#include <string>
#include <run_time_base/printer/history_printer.hpp>
#include <fraction/fraction.hpp>
#include <shared/FileWrap.hpp>

namespace print {
#define HEADER template<typename T>
#define HISTORY history<T>
    
    HEADER
    struct HISTORY::Data {
        std::vector<fraction*>  fr_vars;
        std::vector<int*>       i_vars;
        std::vector<float*>     f_vars;
        std::vector<double*>    df_vars;
        std::vector<bool*>      b_vars;
        std::vector<std::string>fr_names;
        std::vector<std::string>i_names;
        std::vector<std::string>f_names;
        std::vector<std::string>df_names;
        std::vector<std::string>b_names;
        wrap::file              file;
        std::string             outFile;
        bool                    hasHeader;
    };

    HEADER
    HISTORY::history() {
        data = new Data();
    }
    
    HEADER
    HISTORY::~history() {
        if( data ){ delete data; data = 0; }
    }
    
    HEADER
    std::string HISTORY::name() const {
        return "time_history_printer";
    }
    
    HEADER
    void HISTORY::init() {
        if( !data->file.isOpen() ){
            data->file.close();
            data->file.openFile(data->outFile,wrap::file::Write);
        }else{
            fprintf(data->file, "\n");
        }
    }
    
    HEADER
    void HISTORY::addEmptyLine() {
        if( data->file.isOpen() ){ fprintf(data->file, "\n"); }
    }
    
    HEADER
    void HISTORY::update() {
        if( !data->file.isOpen() ){ data->file.openFile(data->outFile, wrap::file::Write); }
        
        if( !data->hasHeader ){
            if( data->file.isOpen() ){
                writeNameHeader( data->file );
                writeDataToFile( data->file );
                data->hasHeader = true;
            }
        }else{
            if( data->file.isOpen() ){
                writeDataToFile( data->file );
            }
        }
    }
    
    HEADER
    void HISTORY::reset() {
        data->hasHeader = false;
    }
    
    HEADER
    void HISTORY::setFileToWriteTo( const std::string & file ) {
        data->outFile = file;
    }
    

#define printNumList(listname,file) for(int i = 0; i < data->listname.size(); ++i){\
                                fprintf(file,"%-25.15lf ",static_cast<double>(*data->listname[i]));\
                                }
#define printNameList(varname,file) for(int i = 0; i < data->varname.size(); ++i){\
                                    fprintf(file,"%-25s ",data->varname[i].c_str());\
                                    }
    
    HEADER
    void HISTORY::writeDataToFile( FILE* file ) const{
        printNumList(fr_vars, file)
        printNumList(i_vars, file)
        printNumList(f_vars, file)
        printNumList(df_vars, file)
        printNumList(b_vars, file)
        fprintf(file, "\n");
    }
    
    HEADER
    void HISTORY::writeNameHeader( FILE* file) const{
        printNameList(fr_names, file)
        printNameList(i_names, file)
        printNameList(f_names, file)
        printNameList(df_names, file)
        printNameList(b_names, file)
        fprintf(file,"\n");
    }

    
    template<>
    template<>
    void history<float>::addVariableToPrint( fraction & var, const std::string & name ) {
        data->fr_vars.push_back(&var);
        data->fr_names.push_back(name);
    }
    
    template<>
    template<>
    void history<double>::addVariableToPrint( fraction & var, const std::string & name ) {
        data->fr_vars.push_back(&var);
        data->fr_names.push_back(name);
    }
    
    
    template<>
    template<>
    void history<float>::addVariableToPrint( double & var, const std::string & name ) {
        data->df_vars.push_back(&var);
        data->df_names.push_back(name);
    }
    
    template<>
    template<>
    void history<double>::addVariableToPrint( double & var, const std::string & name ) {
        data->df_vars.push_back(&var);
        data->df_names.push_back(name);
    }
    
    template<>
    template<>
    void history<float>::addVariableToPrint( float & var, const std::string & name ) {
        data->f_vars.push_back(&var);
        data->f_names.push_back(name);
    }
    
    template<>
    template<>
    void history<double>::addVariableToPrint( float & var, const std::string & name ) {
        data->f_vars.push_back(&var);
        data->f_names.push_back(name);
    }
    
    template<>
    template<>
    void history<float>::addVariableToPrint( int & var, const std::string & name ) {
        data->i_vars.push_back(&var);
        data->i_names.push_back(name);
    }
    
    template<>
    template<>
    void history<double>::addVariableToPrint( int & var, const std::string & name ) {
        data->i_vars.push_back(&var);
        data->i_names.push_back(name);
    }
    
    template<>
    template<>
    void history<float>::addVariableToPrint( bool & var, const std::string & name ) {
        data->b_vars.push_back(&var);
        data->b_names.push_back(name);
    }
    
    template<>
    template<>
    void history<double>::addVariableToPrint( bool & var, const std::string & name ) {
        data->b_vars.push_back(&var);
        data->b_names.push_back(name);
    }
    
    template class history<float>;
    template class history<double>;
}
