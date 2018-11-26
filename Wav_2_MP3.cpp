
/*************************************************************************

 Copyright (C) 2018-2019 by Amir Tosson.
 All rights reserved.

 By copying, distributing or modifying the Program (or any work
 based on the Program) you indicate your acceptance of this statement,
 and all its terms.

This code converts the .wav file to .mp3 file with the default frq.
It has to options - manual in which the user has to write the file name
                  - automatic in which the prog. finds and converts all .wav files in the directory

A very simple make_file is included.

for more details <tosson@physik.uni-siegen.de>

*************************************************************************/


#include <iostream>
#include <stdio.h>
#include "con.h"

void msgWrongArg(){

 printf("The program is closing. Please enter the arguments as following: \n"
        "<the programname> <Directory path> <Conversion setting (-a, -m or -o)> \n"
        "or for help menu\n"
        "<the programname> -h\n");

}

void msgHelpMenu(){

 printf("help: \n"
        "-a  Automatically finding and converting all .wav files in the predefined dir.\n"
        "-m  Manually finding and converting .wav file/s in the predefined dir.\n"
        "ex: ./wav_2_mp3 /home/my_dir/my_dir2 -a");

}

int main(int argc, char *argv[])
{
unsigned int files_count;
bool file_found=true;


if (argc==3 && std::string(argv[2])=="-a"){
   con file;
  file_found= file.auto_files_conversion(argv,&files_count);
   if( file_found){printf("converted files= %d\n",files_count );}
   else{printf("No .wav files in this directory\n");}
      return 0;}

if (argc==3 && std::string(argv[2])=="-m"){
   con file;
   std::string str_user;

do{
   std::cout<<"Please enter the file name or q to quite \n ";
   std::cin>>str_user;
    if(str_user.substr(str_user.find_last_of(".") + 1) == "wav") {file_found=file.one_file_conversion(argv,str_user);}
    else if(str_user=="q"){break;}
    else{printf("Wrong file extension\n");}

  }while(str_user!="q" && file_found==true);
      return 0;}


if (argc==2 && std::string(argv[1])=="-h" ){
msgHelpMenu();
   return 0;}

else{
    msgWrongArg();
    return 0;
}


}

