#ifndef CON_H
#define CON_H
#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include<fstream>
#include "lame/lame.h"
#include <pthread.h>
class con
{
public:
    con();
    bool auto_files_conversion(char **typ, unsigned int *file_num);
    bool one_file_conversion(char **typ, std::string file_name);
    void conversion_function(std::string file);
private:
    std::vector<std::string> file_list;

};

#endif // CON_H
