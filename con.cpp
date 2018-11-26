#include "con.h"
#include "cstring"

con::con()
{

}


void *thread_task(void *th) {

std::string file = *reinterpret_cast<std::string*>(th);
int read, write;
char name[file.size()+1];
char name2[file.size()];
std::size_t lastindex = file.find_last_of(".");
std::string rawname = file.substr(0, lastindex);

strcpy(name,file.c_str());

strcpy(name2,rawname.c_str());


    FILE *pcm = fopen(name, "rb");
    FILE *mp3 = fopen(name2, "wb");

    const int wav_size = 8192;
    const int mp3_size = 8192;

    short int wav_buffer[wav_size*2];
    unsigned char mp3_buffer[mp3_size];
// parameters initialization !!
    lame_t lame = lame_init();
    lame_set_in_samplerate(lame, 44100);// normal frq.
    lame_set_VBR(lame, vbr_default);
    lame_init_params(lame);// using the default

    do {
        read = fread(wav_buffer, 2*sizeof(short int), wav_size, pcm);
        if (read == 0)
            write = lame_encode_flush(lame, mp3_buffer, mp3_size);
        else
            write = lame_encode_buffer_interleaved(lame, wav_buffer, read, mp3_buffer, mp3_size);
        fwrite(mp3_buffer, write, 1, mp3);
    } while (read != 0);

    lame_close(lame);
    fclose(mp3);
    fclose(pcm);

}

bool con::auto_files_conversion(char **typ, unsigned int *file_num) // searchs for all .wav files and converts them
{

    DIR *dir;
    struct dirent *ent_stream;
    dir =opendir(typ[1]);
    if (dir  != NULL) {//check the directory
     while ((ent_stream = readdir (dir)) != NULL) {
         if (strstr(ent_stream->d_name,".wav")){// only .wav extension
            file_list.push_back(ent_stream->d_name);
         }}
    closedir (dir);
    }
    else {
        perror ("");
        *file_num=0;
       return false;
    }

if(file_list.size()>=1){
*file_num=file_list.size();
}

const int Num_Threads=2; // could be changed
pthread_t threads[Num_Threads];

 pthread_attr_t attr; // the attribute declaration
 pthread_attr_init(&attr);
 pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  char *ptr;
for (int i=0;i<file_list.size();i+=Num_Threads){
            for (int id_th=0;id_th<Num_Threads;id_th++){
                if ((i+id_th)<=file_list.size()){ // to be sure that all launched threads have a task
 int ret =  pthread_create(&threads[id_th], NULL, thread_task,  &file_list[i+id_th]);
 pthread_join(threads[id_th],(void**)&ptr);
    if(ret != 0) {perror("pthread_create failed\n");}
                                                        }
                                                 }}
 pthread_attr_destroy(&attr);
return true;
}

bool con::one_file_conversion(char **typ, std::string file_name)//  converts one wav file
{
    DIR *dir;
    struct dirent *ent_stream;
    dir =opendir(typ[1]);
    if (dir  != NULL) { //check the directory
     while ((ent_stream = readdir (dir)) != NULL) {
         if ( ent_stream->d_name==file_name){//check the file name
             conversion_function(file_name);
            return true;
         }
        else {printf("No such a file in this directory\n");
         return true;
         }
     }

 closedir (dir);
    }
    else {
        perror ("");
       return false;
    }

}

void con::conversion_function(std::string file)// the main conversion function
{
    int read, write;
    char name[file.size()+1];
    char name2[file.size()];
    std::size_t lastindex = file.find_last_of(".");
    std::string rawname = file.substr(0, lastindex);
    strcpy(name,file.c_str());
    strcpy(name2,rawname.c_str());


        FILE *pcm = fopen(name, "rb");
        FILE *mp3 = fopen(name2, "wb");

        const int wav_size = 8192;// can be changed
        const int mp3_size = 8192;// can be changed

        short int wav_buffer[wav_size*2];
        unsigned char mp3_buffer[mp3_size];
    // parameters initialization !!
        lame_t lame = lame_init();
        lame_set_in_samplerate(lame, 44100);// .wav file standard frq.
        lame_set_VBR(lame, vbr_default); //Variable bitrate is the lame default and could be changed
        // many other setting can be changed ..!!
        lame_init_params(lame);// using the default for other intialization

        do {
            read = fread(wav_buffer, 2*sizeof(short int), wav_size, pcm);
            if (read == 0)
                write = lame_encode_flush(lame, mp3_buffer, mp3_size);
            else
                write = lame_encode_buffer_interleaved(lame,wav_buffer, read, mp3_buffer, mp3_size);
            fwrite(mp3_buffer, write, 1, mp3);
        } while (read != 0);

        lame_close(lame);
        fclose(mp3);
        fclose(pcm);
}
