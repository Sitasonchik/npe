#pragma once
#include <fstream>
#include "data.hpp"

data file_read(char * file_name){
    std::ifstream file(file_name);
    file.seekg(0, std::ios::end); 
    auto tmp = file.tellg();
    auto datafile = new char[tmp];
    file.clear(); 
    file.seekg(0); 
    file.read(datafile, tmp);
    file.close();
    data readed_file(tmp, reinterpret_cast<unsigned char*>(datafile));
    return readed_file;    
}

void file_write(char * file_name, data d){
    std::fstream data_file;
    data_file.open(file_name,std::fstream::out); 

    data_file.write(reinterpret_cast<char *>(d.text),d.size);    
    data_file.close();
}
