#undef UNICODE
#include "debug_memory.hpp"
#include "MCA-NBT-EDIT.HPP"
#include "stdafx.h"
#include "xallocator.h"
#include "Fault.h"
#include <new>

#ifdef SFML_ONBOARD
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/Network/IpAddress.hpp>
#endif
//#undef UNICODE
#include <winsock2.h>
#include <psapi.h>
#include <stdlib.h>
//#include <windows.h>
#include <stdio.h>
#define NBT_IMPLEMENTATION
#define NBT_OWN_ZLIB
//#define NBT_BUFFER_SIZE 100000
#include "nbt.hpp"
#include <sys/stat.h>
#include <errno.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <sys/types.h>
#include "minecraft.h"
#include <direct.h>
#include <sstream> // for std::stringstream
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <dirent.h>

using namespace std;
#ifdef SFML_ONBOARD
extern void kiki();
extern int monitor_off;
#endif
extern PROCESS_MEMORY_COUNTERS check_memory_tofile(char* name);
PROCESS_MEMORY_COUNTERS check_memory2();
//void do_world(char* filename);
extern int shut_up;
int ONLY_ONE_REGION=0;
extern bool file_exists(const char * filename);
extern void blitter2();
extern void blitter(char * line,int mode);
extern int ESCAPE_PRESSED;

void READ_WORLD_TO_DIRS(char* filename);
void READ_WORLD_TO_GZIPS(char* filename);

nbt_tag_t* main_mca2nbt_adapted(int argc, char *argv[], char* out_dir);
uint8_t* main_nbt2mca(nbt_tag_t* region_tag, size_t* size);
void nbt_to_textfile(nbt_tag_t* tag, char* filename);
void nbt_to_textfile(nbt_tag_t* tag, char* filename);
nbt_tag_t* header_to_tag(uint8_t* regionfile);
uint8_t* load_region_file(char* filename, size_t* size);
void MAKE_MCA_FROM_WORLD_NBT_GZIPS(char* worldname);
void READ_REGION(char* filename);
void WRITE_WORLD_TO_MCA(char* filename);
void WRITE_ALL_REGIONS(char* worldname);

void READ_WORLD(char* filename);
void WRITE_WORLD(nbt_tag_t* tag_world);

nbt_tag_t* GET_REGION(nbt_tag_t* WORLD, int X, int Z);
nbt_tag_t* GET_COLUMN(nbt_tag_t* REGION, int X, int Z);
nbt_tag_t* GET_COLUMN(nbt_tag_t* REGION, int XxZ);
void WRITE_WORLD(nbt_tag_t* tag_world);

SYSTEMTIME stime;
LARGE_INTEGER sys_freq;

char* pretty_number(const long long int input_val)
{
    static char output[100];
    char input[100];
    sprintf(input,"%lld",input_val);

    int iInputLen = strlen(input);
    int iOutputBufferPos = 0;
    for(int i = 0; i < iInputLen; i++)
    {
        if((iInputLen-i) % 3 == 0 && i != 0)
        {
            output[iOutputBufferPos++] = ',';
        }

        output[iOutputBufferPos++] = input[i];
    }

    output[iOutputBufferPos] = '\0';
    return output;
}

double    tikker1=0;
double    tikker2=0;
double    tikker3=0;
double    tikker4=0;
double    tikker5=0;
double    tikker6=0;
double    tikker7=0;


double    rtikker1=0;
double    rtikker2=0;
double    rtikker3=0;
double    rtikker4=0;
double    rtikker5=0;
double    rtikker6=0;
double    rtikker7=0;

extern int file_first1;
extern int file_first2;
extern int file_first3;
int set_quiet=0;

double PCFreq = 0.0;
__int64 CounterStart = 0;

bool StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))return false;

	PCFreq = double(li.QuadPart);

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounterNanoseconds()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

double GetCounterMilliseconds()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq * 1000.f;
}

static size_t reader_read(void* userdata, uint8_t* data, size_t size) {
    rtikker1++;
#ifdef SFML_ONBOARD
/*
    static int kcount=0;
    kcount++;
    if (kcount>10000) {
        monitor_off=1;
        kiki();
        kcount=0;
    }
*/
#endif

  return fread(data, 1, size, (FILE*)userdata);
}

static size_t writer_write(void* userdata, uint8_t* data, size_t size) {
    tikker1++;
#ifdef SFML_ONBOARD
/*
    static int kcount=0;
    kcount++;
    monitor_off=1;
    if (kcount>10000) {
        kiki();
        kcount=0;
    }
*/
#endif
   return fwrite(data, 1, size, (FILE*)userdata);
}

/*
static size_t reader_read(void* userdata, uint8_t* data, size_t size)
{
    return fread(data, 1, size, userdata);
}

static size_t writer_write(void* userdata, uint8_t* data, size_t size)
{
    return fwrite(data, 1, size, userdata);
}
*/

int len_int(int in) {
    char in_str[20];
    sprintf(in_str,"%d",in);
    return strlen(in_str);
}

int print_format=1;

static void print_nbt_tree_to_file(nbt_tag_t* tag, int i, FILE * file)
{
    static int depth=0;
    static int indent=0;
    static char in[1000];
    static int size[100];
    static int pos[100];

#ifdef SFML_ONBOARD
/*
    static int kcount=0;
    kcount++;
    monitor_off=1;
    if (kcount>10000) {
        kiki();
        kcount=0;
    }
*/
#endif

    if (print_format==0) {
        for (int tt=1; tt<depth; tt++) {
            fprintf(file,"[");
            int len=len_int(pos[tt])-1;
            if (tt>0) for (int t=0; t<len_int(size[tt-1])-1-len; t++) fputs(" ",file);
            fprintf(file,"%d]",pos[tt]);
        }
    } else {
        for (int t=1; t<depth; t++) {
            fputs(" | ",file);
            for (int tt=0; tt<len_int(size[t-1])-1; tt++) {
                fputs(" ",file);
            }
        }
    }


    if (depth>0) {
        fprintf(file,"[");
        int len=len_int(i)-1;
        for (int t=0; t<len_int(size[depth-1])-1-len; t++) fputs(" ",file);
        fprintf(file,"%d]",i);
    }
    switch (tag->type)
    {
        case NBT_TYPE_LIST: {
            sprintf(in,"(%d)[list] \"%s\" " ,tag->tag_list.size, tag->name);
            fprintf(file,"%s\r\n" ,in);
            size[depth]=tag->tag_list.size;
            pos[depth]=i;
            depth++;
            for (size_t i = 0; i < tag->tag_list.size; i++) {
                print_nbt_tree_to_file(tag->tag_list.value[i], i ,file);
            }
            depth--;
            break; }
        case NBT_TYPE_COMPOUND: {
            sprintf(in,"(%d)[compound] \"%s\" " ,tag->tag_compound.size,tag->name);
            fprintf(file,"%s\r\n" ,in);
            size[depth]=tag->tag_compound.size;
            pos[depth]=i;
            depth++;
            for (size_t i = 0; i < tag->tag_compound.size; i++) {
                if (tag->tag_compound.value[i]!=0)
                    print_nbt_tree_to_file(tag->tag_compound.value[i], i ,file);
            }
            depth--;
            break; }

        case NBT_TYPE_BYTE: {
            fprintf(file,"[byte] \"%s\" %hhd\r\n",tag->name, tag->tag_byte.value);
            break; }
        case NBT_TYPE_SHORT: {
            fprintf(file,"[short] \"%s\" %hd\r\n",tag->name, tag->tag_short.value);
            break; }
        case NBT_TYPE_INT: {
            fprintf(file,"[int] \"%s\" %d\r\n",tag->name, tag->tag_int.value);
            break; }
        case NBT_TYPE_LONG: {
            fprintf(file,"[long] \"%s\" %lld\r\n",tag->name, tag->tag_long.value);
            break; }
        case NBT_TYPE_FLOAT: {
            fprintf(file,"[float] \"%s\" %f\r\n",tag->name, tag->tag_float.value);
            break; }
        case NBT_TYPE_DOUBLE: {
            fprintf(file,"[double] \"%s\" %.*e\r\n",tag->name, DECIMAL_DIG, tag->tag_double.value);
            break; }
        case NBT_TYPE_STRING: {
            fprintf(file,"[string](%d) \"%s\" %s\r\n",tag->tag_string.size, tag->name , tag->tag_string.value);
            break; }
        case NBT_TYPE_BYTE_ARRAY: {
            fprintf(file,"[byte array](%d) \"%s\"",tag->tag_byte_array.size,tag->name);
            for (size_t i = 0; i < tag->tag_byte_array.size; i++) fprintf(file," %hhd", tag->tag_byte_array.value[i]); fprintf(file,"\r\n");
            break; }
        case NBT_TYPE_INT_ARRAY: {
            fprintf(file,"[int array](%d) \"%s\"",tag->tag_int_array.size,tag->name);
            for (size_t i = 0; i < tag->tag_int_array.size; i++) fprintf(file," %d", tag->tag_int_array.value[i]); fprintf(file,"\r\n");
            break; }
        case NBT_TYPE_LONG_ARRAY: {
            fprintf(file,"[long array](%d) \"%s\"",tag->tag_long_array.size,tag->name);
            for (size_t i = 0; i < tag->tag_long_array.size; i++) fprintf(file," %lld", tag->tag_long_array.value[i]); fprintf(file,"\r\n");
            break; }

        case NBT_TYPE_END: {
            fprintf(file,"[end]"); fprintf(file,"\r\n");
            break; }

        default: {
            fprintf(file,"[error]"); fprintf(file,"\r\n");
        }
    }
//    depth--;
}

/*

static void print_nbt_tree_to_file(nbt_tag_t* tag, int indentation, FILE * file)
{
//    printf("Hallo 1\n");
    static int no_ident=0;
    static int num=-1;
    int is_set=0;
    int is_what_printed=0;
//  printf("TAG TYPE=%d,(SHORT=%d)\n",tag->type,NBT_TYPE_SHORT);
    if (tag->name_size>0)
    {
        if (is_set==0)
        {
            if (no_ident==0) for (int i = 0; i < indentation; i++) fprintf(file," ");
            is_set=1;
            if (num!=-1) {

                fprintf(file,"[%d]", num);
            }
        }
        fprintf(file,"%s:", tag->name);
        is_what_printed=1;
    } else {
        if (is_set==0)
        {
            if (no_ident==0) for (int i = 0; i < indentation; i++) fprintf(file," ");
            is_set=1;
            if (num!=-1) fprintf(file,"[%d]", num);
        }
        indentation+=7;
        fprintf(file,"Entries:");
        is_what_printed=1;
    }
    switch (tag->type)
    {
    case NBT_TYPE_END:
    {
        if (is_set==0)
        {
            for (int i = 0; i < indentation; i++)
                fprintf(file," ");
            is_set=1;
            if (num!=-1) fprintf(file,"(%d)", num);
        }
        fprintf(file," [end]");
        is_what_printed=1;
        break;
    }
    case NBT_TYPE_BYTE:
    {
        if (is_set==0)
        {
            for (int i = 0; i < indentation; i++)
                fprintf(file," ");
            is_set=1;
            if (num!=-1) fprintf(file,"(%d)", num);
        }
        fprintf(file," [byte/%d]",sizeof(tag->tag_byte.value));
        fprintf(file," %hhd", tag->tag_byte.value);
        is_what_printed=1;
        break;
    }
    case NBT_TYPE_SHORT:
    {
//        fprintf(file,"%hx", tag->tag_short.value);
//        fprintf(file,"%d", tag->tag_short.value);
//        fprintf(file,"Hallo 2\n");
        if (is_set==0)
        {
            for (int i = 0; i < indentation; i++)
                fprintf(file," ");
            is_set=1;
            if (num!=-1) fprintf(file,"(%d)", num);
        }
        fprintf(file," [short/%d]",sizeof(tag->tag_short.value));
        fprintf(file," %hd", tag->tag_short.value);
        is_what_printed=1;
        break;
    }
    case NBT_TYPE_INT:
    {
        if (is_set==0)
        {
            for (int i = 0; i < indentation; i++)
                fprintf(file," ");
            is_set=1;
            if (num!=-1) fprintf(file,"(%d)", num);
        }
        fprintf(file," [int/%d]",sizeof(tag->tag_int.value));
        fprintf(file," %d", tag->tag_int.value);
        is_what_printed=1;
        break;
    }
    case NBT_TYPE_LONG:
    {
//        fprintf(file,"%llx", tag->tag_long.value);
        if (is_set==0)
        {
            for (int i = 0; i < indentation; i++)
                fprintf(file," ");
            is_set=1;
            if (num!=-1) fprintf(file,"(%d)", num);
        }
        fprintf(file," [long/%d]",sizeof(tag->tag_long.value));
        fprintf(file," %lld", tag->tag_long.value);
        is_what_printed=1;
        break;
    }
    case NBT_TYPE_FLOAT:
    {
        if (is_set==0)
        {
            for (int i = 0; i < indentation; i++)
                fprintf(file," ");
            is_set=1;
            if (num!=-1) fprintf(file,"(%d)", num);
        }
        fprintf(file," [float/%d]",sizeof(tag->tag_float.value));
        fprintf(file," %f", tag->tag_float.value);
        is_what_printed=1;
        break;
    }
    case NBT_TYPE_DOUBLE:
    {
        if (is_set==0)
        {
            for (int i = 0; i < indentation; i++)
                fprintf(file," ");
            is_set=1;
            if (num!=-1) fprintf(file,"(%d)", num);
        }
        fprintf(file," [double/%d]",sizeof(tag->tag_double.value));
        fprintf(file," %.*e", DECIMAL_DIG, tag->tag_double.value);

//        fprintf(file," %20f", tag->tag_double.value);
        is_what_printed=1;
        break;
    }
    case NBT_TYPE_BYTE_ARRAY:
    {
        if (is_set==0)
        {
            for (int i = 0; i < indentation; i++)
                fprintf(file," ");
            is_set=1;
            if (num!=-1) fprintf(file,"(%d)", num);
        }
        fprintf(file," [byte array](%d)",tag->tag_byte_array.size);
//      break;
        for (size_t i = 0; i < tag->tag_byte_array.size; i++)
        {
            fprintf(file," %hhd", tag->tag_byte_array.value[i]);
        }
        is_what_printed=1;
        break;
    }
    case NBT_TYPE_STRING:
    {
//      fprintf(file,"NBT_TYPE_STRING: tag->tag_string.value=\n");
//      fprintf(file,"%s\n",tag->tag_string.value);
        if (is_set==0)
        {
            for (int i = 0; i < indentation; i++)
                fprintf(file," ");
            is_set=1;
            if (num!=-1) fprintf(file,"(%d)", num);
        }
        fprintf(file," [string/%d]",tag->tag_string.size);
        fprintf(file," %s", tag->tag_string.value);
        is_what_printed=1;
        break;
    }
    case NBT_TYPE_LIST:
    {
        char val[20];
        int extra;
        if (is_what_printed)
        {
            fprintf(file,"(%d)\r\n",tag->tag_list.size);
            sprintf(val,"%d",num); extra=strlen(val)-1;
            is_what_printed=0;
        }
        sprintf(val,"%d",tag->tag_list.size);
        int len=strlen(val);
        for (size_t i = 0; i < tag->tag_list.size; i++) {
            sprintf(val,"%d",i);
            num=i;
            print_nbt_tree_to_file(tag->tag_list.value[i], indentation + tag->name_size + 4 + len-strlen(val)+extra,file);
        }
        break;
    }
    case NBT_TYPE_COMPOUND:
    {
        char val[20];
        int extra;
        if (is_what_printed)
        {
            fprintf(file,"(%d)\r\n",tag->tag_compound.size);
            sprintf(val,"%d",num); extra=strlen(val)-1;
            is_what_printed=0;
        }
        sprintf(val,"%d",tag->tag_compound.size);
        int len=strlen(val);
        for (size_t i = 0; i < tag->tag_compound.size; i++)
        {
            sprintf(val,"%d",i);
            num=i;
            print_nbt_tree_to_file(tag->tag_compound.value[i], indentation + tag->name_size + 4 + len-strlen(val)+extra,file);
        }
        break;
    }
    case NBT_TYPE_INT_ARRAY:
    {
        if (is_set==0)
        {
            for (int i = 0; i < indentation; i++)
                fprintf(file," ");
            is_set=1;
//            if (num!=-1) fprintf(file,"(%d)", num);
        }
        fprintf(file," [int array](%d)",tag->tag_int_array.size);
//      break;
        for (size_t i = 0; i < tag->tag_int_array.size; i++)
        {
            fprintf(file," %d", tag->tag_int_array.value[i]);
        }
        is_what_printed=1;
        break;
    }
    case NBT_TYPE_LONG_ARRAY:
    {
        if (is_set==0)
        {
            for (int i = 0; i < indentation; i++)
                fprintf(file," ");
            is_set=1;
            if (num!=-1) fprintf(file,"(%d)", num);
        }
        fprintf(file," [long array](%d)",tag->tag_long_array.size);
//      break;
        for (size_t i = 0; i < tag->tag_long_array.size; i++)
        {
            fprintf(file," %lld", tag->tag_long_array.value[i]);
        }
        is_what_printed=1;
        break;
    }
    default:
    {
        if (is_set==0)
        {
            for (int i = 0; i < indentation; i++)
                fprintf(file," ");
            is_set=1;
        }
        fprintf(file," [error]");
        is_what_printed=1;
    }
    }
//    { fprintf(file,"\r\n"); is_what_printed=0; }
    if (is_what_printed)
    {
        fprintf(file,"\r\n");
        is_what_printed=0;
    }
//    fprintf(file,"\n");
    num=-1;
}

*/


static void print_nbt_tree(nbt_tag_t* tag, int indentation)
{
//    printf("Hallo 1\n");
    if (tag==NULL) return;
    for (int i = 0; i < indentation; i++)
    {
        printf(" ");
    }

//  printf("TAG TYPE=%d,(SHORT=%d)\n",tag->type,NBT_TYPE_SHORT);
    if (tag->name)
    {
        printf("%s: ", tag->name);
    }

    switch (tag->type)
    {
    case NBT_TYPE_END:
    {
        printf("[end]");
        break;
    }
    case NBT_TYPE_BYTE:
    {
        printf("%hhd", tag->tag_byte.value);
        break;
    }
    case NBT_TYPE_SHORT:
    {
//        printf("%hx", tag->tag_short.value);
//        printf("%d", tag->tag_short.value);
//        printf("Hallo 2\n");
        printf("%hd", tag->tag_short.value);
        break;
    }
    case NBT_TYPE_INT:
    {
        printf("%d", tag->tag_int.value);
        break;
    }
    case NBT_TYPE_LONG:
    {
//        printf("%llx", tag->tag_long.value);
        printf("%lld", tag->tag_long.value);
        break;
    }
    case NBT_TYPE_FLOAT:
    {
        printf("%f", tag->tag_float.value);
        break;
    }
    case NBT_TYPE_DOUBLE:
    {
        printf(" %.*e", DECIMAL_DIG, tag->tag_double.value);
//        printf("%.20f", tag->tag_double.value);
        break;
    }
    case NBT_TYPE_BYTE_ARRAY:
    {
        printf("[byte array]");
//      break;
        for (size_t i = 0; i < tag->tag_byte_array.size; i++)
        {
            printf("%hhd ", tag->tag_byte_array.value[i]);
        }
        break;
    }
    case NBT_TYPE_STRING:
    {
//      printf("NBT_TYPE_STRING: tag->tag_string.value=\n");
//      printf("%s\n",tag->tag_string.value);
        printf("%s", tag->tag_string.value);
        break;
    }
    case NBT_TYPE_LIST:
    {
        printf("\n");
        for (size_t i = 0; i < tag->tag_list.size; i++)
        {
            if (tag->tag_list.value[i]!=NULL) print_nbt_tree(tag->tag_list.value[i], indentation + tag->name_size + 2);
        }
        break;
    }
    case NBT_TYPE_COMPOUND:
    {
        printf("\n");
//      printf("NBT_TYPE_COMPOUNT: tag->tag_compound.size=%d\n",tag->tag_compound.size);

        for (size_t i = 0; i < tag->tag_compound.size; i++)
        {
            if (tag->tag_compound.value[i]!=NULL) print_nbt_tree(tag->tag_compound.value[i], indentation + tag->name_size + 2);
        }
        break;
    }
    case NBT_TYPE_INT_ARRAY:
    {
        printf("[int array]");
//      break;
        for (size_t i = 0; i < tag->tag_int_array.size; i++)
        {
            printf("%d ", tag->tag_int_array.value[i]);
        }
        break;
    }
    case NBT_TYPE_LONG_ARRAY:
    {
        printf("[long array]");
//      break;
        for (size_t i = 0; i < tag->tag_long_array.size; i++)
        {
            printf("%lld ", tag->tag_long_array.value[i]);
        }
        break;
    }
    default:
    {
        printf("[error]");
    }
    }

    printf("\n");
}

/**************************************************/

nbt_tag_t* read_nbt_file(const char* name, int flags)
{

    FILE* file = fopen(name, "rb");

    nbt_reader_t reader;

    reader.read = reader_read;
    reader.userdata = file;

    nbt_tag_t* tag = nbt_parse(reader, flags);

    fclose(file);

    return tag;
}

static size_t reader_read_from_memory(void* userdata, uint8_t* data, size_t size) {
    static size_t total_size;
    static size_t current_position;
    static int kcount=0;
    rtikker2++;
/*
    kcount++;
    if (kcount>10000) {
        kiki();
        monitor_off=1;
        kcount=0;
    }
*/
    if (userdata==NULL && data==NULL) {
        total_size=size;
        current_position=0;
        return 0;
    }
    if (total_size==0) return 0;
    if (size>total_size) {
        NBT_MEMCPY(data, userdata+current_position, total_size);
        size_t ret=total_size;
        current_position+=total_size;
        total_size=0;
        return ret;
    } else {
        NBT_MEMCPY(data, userdata+current_position, size);
        total_size-=size;
        current_position+=size;
        return size;
    }
}

nbt_tag_t* read_nbt_from_memory(uint8_t* location, size_t size, int flags)
{
    rtikker3++;
    nbt_reader_t reader;

    reader.read = reader_read_from_memory;
    reader.userdata = location;
    reader.read(NULL, NULL, size);

    nbt_tag_t* tag = nbt_parse(reader, flags);

    return tag;
}

/*****************************************************************************/


void write_nbt_file(const char* name, nbt_tag_t* tag, int flags)
{
    FILE* file = fopen(name, "wb");

    nbt_writer_t writer;

    writer.write = writer_write;
    writer.userdata = file;

    nbt_write(writer, tag, flags);

    fclose(file);
}

uint8_t* intern[100];    /* indexed, maybe for later use when using threads, like 4 simultanious (or 100) are active.... reader_read also needs this. could be slower thought..but could be passed by the efficiency of running more threads at same time...(like having a 256 core pentium...) */

static size_t writer_write_to_memory(void* userdata, uint8_t* data, size_t size) {
    //printf("Here 1\n");
    tikker2++;
    static size_t total_size[100];
    static size_t current_position[100];
    static int kcount=0;
    //printf("Here 2\n");
    //printf( "intern[(size_t) %lld]=%016llx\n" , userdata , intern[ (size_t) userdata] );
    //printf( "current_position[(size_t) %d]=%lld\n" , (size_t) userdata , current_position[(size_t) userdata] );
#ifdef SFML_ONBOARD
    kcount++;
    //printf("size=%lld\n",size);
    if (kcount>10000) {
        kiki();
        monitor_off=1;
        kcount=0;
    }
#endif
    if (data==NULL) {
        //printf("Here 3\n");
        if (size==1) {

//            if (intern[(size_t) userdata]!=NULL) {
//                current_position[(size_t) userdata]=0;
//                return 0;
//            }
            total_size[(size_t) userdata]=NBT_BUFFER_SIZE;

            //printf("NBT_BUFFER_SIZE=%d\n",NBT_BUFFER_SIZE);

            intern[(size_t) userdata]=NULL;                              /* in case not freed, pointer to previous address invallid, maybe in use.....so, new memory allocated, old not changed... */

            //printf( "intern[(size_t) %lld]=%016llx\n" , userdata , intern[ (size_t) userdata] );

            //printf( "total_size[(size_t) %lld]=%lld\n"  ,  userdata  ,  total_size[(size_t) userdata]);

            intern[(size_t) userdata] = (uint8_t*)NBT_MALLOC(   total_size[ (size_t) userdata ]  );
            tikker4++;
            //printf( "intern[(size_t) %lld]=%016llx\n" , userdata , intern[ (size_t) userdata] );

//            printf( "sizeof(*intern[(size_t) %lld])=%lld\n" , (size_t) userdata , sizeof( *intern[(size_t) userdata]) );

            current_position[(size_t) userdata]=0;

            //printf( "current_position[(size_t) %d]=%lld\n" , (size_t) userdata , current_position[(size_t) userdata] );

            //printf("Here 4\n");
            return 0;
        } else {
            //printf("Here 5.0\n");

            //printf( "intern[(size_t) %lld]=%016llx\n" , userdata , intern[ (size_t) userdata] );

            //printf( "total_size[(size_t) %lld]=%lld\n"  ,  userdata  ,  total_size[(size_t) userdata]);

//            printf( "sizeof(*intern[(size_t) %lld])=%lld\n" , (size_t) userdata , sizeof( *intern[(size_t) userdata]) );

//            intern[(size_t) userdata] = (uint8_t*)NBT_REALLOC(intern[(size_t) userdata], current_position[(size_t) userdata]);  /* adjust to real size... */

            //printf("Here 5.1\n");

            //printf( "total_size[(size_t) %lld]=%lld\n"  ,  userdata  ,  total_size[(size_t) userdata]);

            //printf( "intern[(size_t) %lld]=%016llx" , userdata , intern[ (size_t) userdata] );

//            printf( "sizeof(*intern[(size_t) %lld])=%lld\n" , (size_t) userdata , sizeof( *intern[(size_t) userdata]) );

            //printf( "current_position[(size_t) %d]=%lld\n" , (size_t) userdata , current_position[(size_t) userdata] );

            return(current_position[(size_t) userdata]);
        }
    }
    //printf("Here 6\n");
    if (size==0) return 0;
    //printf("Here 7\n");

        //printf( "total_size[(size_t) %lld]=%lld\n"  ,  userdata  ,  total_size[(size_t) userdata]);

        //printf( "intern[(size_t) %lld]=%016llx\n" , userdata , intern[ (size_t) userdata] );

//        printf( "sizeof(*intern[(size_t) %lld])=%lld\n" , (size_t) userdata , sizeof( *intern[(size_t) userdata]) );

        //printf( "current_position[(size_t) %d]=%lld\n" , (size_t) userdata , current_position[(size_t) userdata] );

    if (current_position[(size_t) userdata]+size>=total_size[(size_t) userdata]) {

        //printf("Here 8\n");

        //printf( "total_size[(size_t) %lld]=%lld\n"  ,  userdata  ,  total_size[(size_t) userdata]);

        while (current_position[(size_t) userdata]+size>=total_size[(size_t) userdata]) total_size[(size_t) userdata]=total_size[(size_t) userdata]*2;

        //printf( "total_size[(size_t) %lld]=%lld\n"  ,  userdata  ,  total_size[(size_t) userdata]);

        //printf( "intern[(size_t) %lld]=%016llx\n" , userdata , intern[ (size_t) userdata] );

        intern[(size_t) userdata] = (uint8_t*) NBT_REALLOC( intern[(size_t) userdata] , total_size[(size_t) userdata] );
        tikker5++;

        //printf( "intern[(size_t) %lld]=%016llx\n" , userdata , intern[ (size_t) userdata] );

//        printf( "sizeof(*intern[(size_t) %lld])=%lld\n" , (size_t) userdata , sizeof( *intern[(size_t) userdata]) );

        //printf("Here 9\n");
    }

    //printf("Here 10\n");

    NBT_MEMCPY(intern[(size_t) userdata]+current_position[(size_t) userdata],data,size);

    //printf("Here 11\n");

    //printf( "total_size[(size_t) %lld]=%lld\n"  ,  userdata  ,  total_size[(size_t) userdata]);

    //printf( "intern[(size_t) %lld]=%016llx" , userdata , intern[ (size_t) userdata] );

//    printf( "sizeof(*intern[(size_t) %lld])=%lld\n" , (size_t) userdata , sizeof( *intern[(size_t) userdata]) );

    //printf( "current_position[(size_t) %d]=%lld\n" , (size_t) userdata , current_position[(size_t) userdata] );

    current_position[(size_t) userdata]+=size;

    //printf( "current_position[(size_t) %d]=%lld\n" , (size_t) userdata , current_position[(size_t) userdata] );

    //printf("Here 12\n");

    return size;
}

//location=write_nbt_to_memory(tag_in, NBT_PARSE_FLAG_USE_RAW, &length);

uint8_t* write_nbt_to_memory(nbt_tag_t* tag, int flags, size_t* size)
{
    //printf("hi\n");
//    uint8_t* location=NULL; must be mutexed when used by threads.... for using the indexed memory pointers. All before and after the nbt_write()
    tikker3++;
    static uint8_t* depth=NULL;
    depth++;

    //printf("write_nbt_to_memory, depth=%lld\n",depth);

    nbt_writer_t writer;

    writer.write = writer_write_to_memory;
//    location=depth;
    writer.userdata = depth;
//    writer.userdata = location;

    /* init */

    //printf("Calling writer_write_to_memory, init\n");

//        *length=2;        // free pointer yourself
//        *length=1;        // means reset ((keep existing pointer, not freed) otherwise previous...so plus, (also 0))
//        *lenght=0;          // means not used NBT_FREE(), overwrite and use previous memory location.
//    if (*size==0) intern[(size_t)depth+1]=NULL;
//    if (*size==1) intern[(size_t)depth+1]=NULL;
//    if (*size==2) NBT_FREE(intern[(size_t)depth+1]);

    writer_write_to_memory(depth, NULL, 1);

    //printf("Here\n");
    //printf("intern[%lld]=%016llx\n",depth, intern[(size_t)depth]);

    //printf("Calling nbt_write\n");

    nbt_write(writer, tag, flags);

    //printf("Back from nbt_write\n");

    //printf("intern[%lld]=%016llx\n",(size_t)depth, intern[(size_t)depth]);



    //printf("Calling writer_write_to_memory, getting size\n");

    *size=writer_write_to_memory(depth,NULL,2);

    //printf("Called writer_write_to_memory, getting size=%lld\n",*size);



    depth--;
    return (intern[(size_t)depth+1]); /* NBT_FREE returned pointer after use.... */
}

double tied=0;
double tied_total=0;
size_t mem_start=0;
size_t mem_now=0;
size_t mem_was=0;
long long int mem_dif=0;
long long int mem_tot_dif1=0;
long long int mem_tot_dif2=0;
size_t mem_first=0;

CONSOLE_SCREEN_BUFFER_INFO coninfo;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int go_go_go=0;

PROCESS_MEMORY_COUNTERS memory;
int flopperdeflop=0;
int set_display_memory=0;

int loop=0;
long long unsigned int call=0;
double tied_total_total=0;
long long int total_count=0;
long long unsigned int total_call=0;
int count_loops=0;

int no_print=0;

void disp_memory_usage() {
    coninfo.dwCursorPosition.Y = 0; coninfo.dwCursorPosition.X = 0; SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);
    if (no_print==0) printf("loop %d/%d\n",loop,total_count);
    call++;
    total_call++;
    memory=check_memory2();
    check_memory_tofile("");
    blitter("Memory Leak Detector Running",0);
//    check_memory_tofile("(Inside call)");
    mem_was = mem_now;
    mem_now = memory.WorkingSetSize;
    mem_dif = mem_now-mem_was;
    if (no_print==0) printf("\n");
    if (no_print==0) printf("                                                                                           \r");
    if (no_print==0) printf("MEMORY FIRST     =%20u\n",mem_first);
    if (no_print==0) printf("                                                                                           \r");
    if (no_print==0) printf("MEMORY START     =%20u\n",mem_start);
    if (no_print==0) printf("                                                                                           \r");
    if (no_print==0) printf("MEMORY NOW       =%20u\n",mem_now);
    if (no_print==0) printf("                                                                                           \r");
    if (no_print==0) printf("DIFFERENCE       =%20lld\n",mem_dif);
    mem_tot_dif1+=mem_dif;
    mem_tot_dif2=mem_now-mem_first;
    if (no_print==0) printf("                                                                                           \r");
    if (no_print==0) printf("TOTAL DIFF. START=%20lld\n",mem_tot_dif1);
    if (no_print==0) printf("                                                                                           \r");
    if (call!=0)
        if (no_print==0) printf("AVERAGE START    =%20lld (%d)\n",mem_tot_dif1/(long long int)call, call);
        else if (no_print==0) printf("\n");
    if (no_print==0) printf("TOTAL DIFF. FIRST=%20lld\n",mem_tot_dif2);
    if (no_print==0) printf("                                                                                           \r");
    if (total_call!=0)
        if (no_print==0) printf("AVERAGE FIRST    =%20lld (%d)\n",mem_tot_dif2/(long long int)total_call,total_call);
    else if (no_print==0) printf("\n");

    if (no_print==0) printf("\n");
    flopperdeflop=(flopperdeflop+1)%2;

    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied; tied_total_total+=tied;

    if (no_print==0) printf("Total: %9.3f  Total loop: %9.3f  Time: %9.6f\n",tied_total_total,tied_total,tied);
    if (no_print==0) printf("\n");
    if (total_count>0) {
        if (no_print==0) printf("write tikker1=%20f read tikker1=%20f   %20f   %20f\n",tikker1,   rtikker1,   tikker1/total_count,   rtikker1/total_count);
        if (no_print==0) printf("write tikker2=%20f read tikker2=%20f   %20f   %20f\n",tikker2,   rtikker2,   tikker2/total_count,   rtikker2/total_count);
        if (no_print==0) printf("write tikker3=%20f read tikker3=%20f   %20f   %20f\n",tikker3,   rtikker3,   tikker3/total_count,   rtikker3/total_count);
        if (no_print==0) printf("write tikker4=%20f read tikker4=%20f   %20f   %20f\n",tikker4,   rtikker4,   tikker4/total_count,   rtikker4/total_count);
        if (no_print==0) printf("write tikker5=%20f read tikker5=%20f   %20f   %20f\n",tikker5,   rtikker5,   tikker5/total_count,   rtikker5/total_count);
        if (no_print==0) printf("write tikker6=%20f read tikker6=%20f   %20f   %20f\n",tikker6,   rtikker6,   tikker6/total_count,   rtikker6/total_count);
    } else if (no_print==0) printf("\n\n\n\n\n\n");
    if (no_print==0) printf("\n");
#ifdef XALLOC
    xalloc_stats();
#endif
    if (no_print==0) printf("\n");
    go_go_go=1;
}

int leak = 5;
extern int first_mem;

void test_write_to_and_read_from_memory() {
    static int first_round=1;
    static int first_call=1;
    call=0;
//    xalloc_stats();
//    system("timeout 5");
//DEBUG_MEM
#ifdef DEBUG_MEMORY
    file_malloc=fopen("nbt_malloc.txt","w");
    file_realloc=fopen("nbt_realloc.txt","w");
    file_free=fopen("nbt_free.txt","w");
    system("del xmalloc.txt");
    system("del xfree.txt");
    system("del xrealloc.txt");
#endif

#ifdef XALLOC
    system("type xalloc.txt >> xalloc.log");
    system("del xalloc.txt");
    system("timeout 1");
    xalloc_stats_to_file("Before read:");
#endif
    PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter();
    tied=0;
    tied_total=0;

    if (first_round==1) {
        GetConsoleScreenBufferInfo(hConsole, &coninfo);
    }

    mem_dif = 0;
    mem_tot_dif1 = 0;

    GetProcessMemoryInfo(GetCurrentProcess(), &memory, sizeof(memory));
//    memory=check_memory2();
/*
    no_print=1;
    disp_memory_usage();
    no_print=0;
*/

//    mem_tot_dif2 = 0;
    mem_start = memory.WorkingSetSize;
    if (!file_exists("memory.txt")) {
        mem_first=mem_now;
    }
    if (first_round==2) {     //reset first round data.....more reliable to check memory usage (first round there is lots of initial allocations who never will be freed i guess).
        mem_start = memory.WorkingSetSize;
        mem_now = memory.WorkingSetSize;
        mem_was = memory.WorkingSetSize;
        mem_first=memory.WorkingSetSize;
        first_round++;
        tied=0;
        tied_total=0;
        mem_dif=0;
        mem_tot_dif1=0;
        mem_tot_dif2=0;
        call=0;
        total_call=0;
        count_loops=0;
        total_count=0;
        disp_memory_usage();
    }
    if (first_round==1) {

        mem_start = memory.WorkingSetSize;
        mem_now = mem_start;
        mem_was = mem_start;
        mem_first=mem_now;
        first_round++;
        GetConsoleScreenBufferInfo(hConsole, &coninfo);
    }


    system("cls");

    if (first_call==1) {
        first_call=0;
        system("type memory.txt >> memory.log");
        system("del memory.txt");
        system("time /t >> memory.txt");
    }
//koekoek
//    memory=check_memory_tofile("(Before init)");

    system("cls");

    uint8_t* location=NULL;

    size_t length1=0;
    size_t length2=0;

    //printf("sizeof(lenght)=%d\n",sizeof(length));

#ifdef SFML_ONBOARD
/*
    for (int t=0; t<30; t++) {
        kiki();
        monitor_off=1;
        sf::sleep(sf::seconds(0.1));
    }
*/
#endif
//    tikker1=0; rtikker1=0;
//    tikker2=0; rtikker2=0;
//    tikker3=0; rtikker3=0;
//    tikker4=0; rtikker4=0;
//    tikker5=0; rtikker5=0;
//    tikker6=0; rtikker6=0;

    nbt_tag_t* tag_out;
    nbt_tag_t* tag_in;
    nbt_tag_t* tag_longtest;
    nbt_tag_t* tag_shorttest;
    nbt_tag_t* tag_stringtest;
    nbt_tag_t* tag_doubletest;

    uint8_t* location1=NULL;
    uint8_t* location2=NULL;



//    CONSOLE_SCREEN_BUFFER_INFO coninfo;
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    FILE *textfile;

    if (leak==1 || leak==3) {
        printf("Reading file r.0.0/0.nbt\n");
        tag_in = read_nbt_file("r.0.0/0.nbt", NBT_PARSE_FLAG_USE_RAW);
        printf("file read\n");

        textfile=fopen("r.0.0/0.org.txt","wb");
        printf("file opened\n");
        if (!textfile==NULL) {  printf("Printing file r.0.0/0.org.txt\n"); print_nbt_tree_to_file(tag_in, 0, textfile); fclose(textfile); }

        else {   printf("ERROR: %s","r.0.0/0.org.txt");  }
    } else if (leak==2) {
    } else if (leak==4) {
    } else if (leak==5) {
    } else if (leak==6) {
    } else if (leak==7) {
    } else if (leak==8) {
    } else if (leak==9) {
    } else if (leak==10) {
    }

#ifdef XALLOC
    xalloc_stats_to_file("After read/before loops:");
#endif
//koekoek
//    check_memory_tofile("(After init/before loops)");

//    printf("Writing to memory r.0.0/0.nbt\n");
//    location1=write_nbt_to_memory(tag_in, NBT_PARSE_FLAG_USE_RAW, &length1);

    coninfo.dwCursorPosition.Y = 0; coninfo.dwCursorPosition.X = 0; SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);

    //torture memory allocator heavy pain sector
    go_go_go=0;
    count_loops=3+1;
    set_display_memory=1;
    for (int x=1; x<count_loops; x++) {
            total_count++;
//        if ((x%500-1)==0) {
#ifdef SFML_ONBOARD
        monitor_off=1;
#endif
//        if ((x%100)==0) {

        if ((x%1)==0 || x==count_loops-1) {
            loop=x;
            disp_memory_usage();
            check_memory_tofile("");
            if (x==1) { printf("\n"); system("type memory.txt"); }
//            check_memory_tofile("(Inside loop)");
        }
//        if (go_go_go==1)
            if ((x%20)==0) {
                if (flopperdeflop) printf("."); else printf("x");
            }

//        length=2;        // free pointer yourself
//        length=1;        // means reset ((keep existing pointer, not freed) otherwise previous...so plus, (also 0))
//        length1=0;          // means not used NBT_FREE(), overwrite and use previous memory location.

//        location1= write_nbt_to_memory(tag_in, NBT_PARSE_FLAG_USE_RAW, &length);
//        tag_out = read_nbt_from_memory((uint8_t*) location1, length, NBT_PARSE_FLAG_USE_RAW);


        if (leak==1) {
            nbt_free_tag(tag_in);
//            xalloc_stats_to_file("After free/inside loop:");
//            check_memory_tofile("After free/inside loop:        ");
            tag_in = read_nbt_file("r.0.0/0.nbt", NBT_PARSE_FLAG_USE_RAW);
//            nbt_free_tag(tag_in);
//            xalloc_stats_to_file("After read/inside loop:");
//            check_memory_tofile("After read/inside loop:        ");
            location1=write_nbt_to_memory(tag_in, NBT_PARSE_FLAG_USE_RAW, &length1);
            tag_out=read_nbt_from_memory(location1,length1, NBT_PARSE_FLAG_USE_RAW);

            location2=write_nbt_to_memory(tag_out, NBT_PARSE_FLAG_USE_RAW, &length2);
            NBT_FREE(location1);
            nbt_free_tag(tag_in);
            nbt_free_tag(tag_out);
            tag_in=read_nbt_from_memory(location2,length2,NBT_PARSE_FLAG_USE_RAW);
            NBT_FREE(location2);
        } else if (leak==2) {
        } else if (leak==3) {
            write_nbt_file("r.0.0/0.copy.nbt", tag_in, NBT_PARSE_FLAG_USE_RAW);
        } else if (leak==4) {
            if (!first_round) nbt_free_tag(tag_in);
            tag_in = nbt_new_tag_compound();
            nbt_set_tag_name(tag_in, (char*)"Level", strlen("Level"));

            tag_longtest = nbt_new_tag_long(0x7fffffffffffffff);
            nbt_set_tag_name(tag_longtest, "longTest", strlen("longTest"));

            tag_shorttest = nbt_new_tag_short(0x7fff);
            nbt_set_tag_name(tag_shorttest, "shortTest", strlen("shortTest"));

            tag_stringtest = nbt_new_tag_string("HELLO WORLD THIS IS A TEST STRING!", strlen("HELLO WORLD THIS IS A TEST STRING!"));
            nbt_set_tag_name(tag_stringtest, "stringTest", strlen("stringTest"));

            tag_doubletest = nbt_new_tag_double(987654321.1234567890123456789);
            nbt_set_tag_name(tag_doubletest, "doubleTest", strlen("doubleTest"));

            nbt_tag_compound_append(tag_in, tag_shorttest);
            nbt_tag_compound_append(tag_in, tag_stringtest);
            nbt_tag_compound_append(tag_in, tag_longtest);
            nbt_tag_compound_append(tag_in, tag_doubletest);

        } else if (leak==5) {
            set_quiet=1;
            READ_WORLD_TO_GZIPS("World");
//            WRITE_WORLD_TO_MCA("World/nbt/world.gzip.nbt");
//            if (!ESCAPE_PRESSED) WRITE_ALL_REGIONS("World");
//            READ_WORLD("World");
//            MAKE_MCA_FROM_WORLD_NBT_GZIPS("World");
            set_quiet=0;
        } else if (leak==6) {
            set_quiet=1;
            MAKE_MCA_FROM_WORLD_NBT_GZIPS("World");
            set_quiet=0;
        } else if (leak==7) {
        } else if (leak==8) {
        } else if (leak==9) {
        } else if (leak==10) {
        }
//        nbt_free_tag(tag_in);
//        tag_in = read_nbt_from_memory((uint8_t*) location1, length1, NBT_PARSE_FLAG_USE_RAW);

//        length=2;        // free pointer yourself
//        length=1;        // means reset ((keep existing pointer, not freed) otherwise previous...so plus, (also 0))
//        length=0;          // means not used NBT_FREE(), overwrite and use previous memory location.

//        location2=write_nbt_to_memory(tag_out, NBT_PARSE_FLAG_USE_RAW, &length);
//        tag_in = read_nbt_from_memory((uint8_t*) location2, length, NBT_PARSE_FLAG_USE_RAW);
//        nbt_free_tag(tag_out);
//        NBT_FREE(location1); //location1=NULL;
//        NBT_FREE(location2); //location2=NULL;
//        first_round=0;
        if (ESCAPE_PRESSED) { x=count_loops; break; }
    }
    printf("\n");
    set_display_memory=0;
    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied; tied_total_total=tied_total_total+tied;

    if (leak==1) { // write tortured n
        printf("Total: %9.3f Time: %9.6f\r\n",tied_total,tied);
        printf("Writing r.0.0/0.copy.nbt\n");  write_nbt_file("r.0.0/0.copy.nbt", tag_in, NBT_PARSE_FLAG_USE_RAW);    printf("Written r.0.0/0.copy.nbt\n");
        textfile=fopen("r.0.0/0.copy.txt","wb");    if (!textfile==NULL) {  printf("Printing file r.0.0/0.copy.txt\n");  print_nbt_tree_to_file(tag_in, 0, textfile); fclose(textfile); }
        else { printf("ERROR: %s","r.0.0/0.copy.txt");  }
        nbt_free_tag(tag_in);
    } else if (leak==2) {
    } else if (leak==3) {
        nbt_free_tag(tag_in);
    } else if (leak==4) {
//            nbt_free_tag(tag_shorttest);
//            nbt_free_tag(tag_longtest);
//            nbt_free_tag(tag_doubletest);
//            nbt_free_tag(tag_stringtest);
        nbt_free_tag(tag_in);
    } else if (leak==5) {
    } else if (leak==6) {
    } else if (leak==7) {
    } else if (leak==8) {
    } else if (leak==9) {
    } else if (leak==10) {
    }

#ifdef XALLOC
    xalloc_stats_to_file("After loops:");
#endif
    memory=check_memory_tofile("(After loops)");
    system("type memory.txt");

//    system("echo try to reset xallocator.....");

    system("timeout 5");

//    xalloc_reset();

//    xalloc_init();

//    system("echo reset xalloc> xalloc.txt");
//    system("echo reset xalloc> memory.txt");

//    printf("GLOBAL MEMORY FIRST=%llu\n",mem_first);
//    printf("GLOBAL MEMORY START=%llu\n",mem_start);
//    printf("GLOBAL MEMORY NOW=  %llu\n",mem_now);

#ifdef XALLOC
    xalloc_stats_to_file("After no reset:");
#endif
//    check_memory_tofile("After no reset:                ");
//    system("timeout 2");
#ifdef XALLOC
    system("echo xalloc.txt:");
    system("type xalloc.txt");
    system("timeout 2");

    printf("\n");
    xalloc_stats();
    system("timeout 2");
#endif
//    printf("GLOBAL MEMORY FIRST=%llu\n",mem_first);
//    printf("GLOBAL MEMORY START=%llu\n",mem_start);
//    printf("GLOBAL MEMORY NOW=  %llu\n",mem_now);
#ifdef DEBUG_MEMORY
    file_first1=3; xmalloc(0);
    file_first2=3; xrealloc(0,0);
    file_first3=3; xfree(0);
    fclose(file_malloc);
    fclose(file_realloc);
    fclose(file_free);
    system("timeout 2");
    system("time /t >> xmalloc.txt");
    system("time /t >> xrealloc.txt");
    system("time /t >> xfree.txt");
    system("time /t >> nbt_malloc.txt");
    system("time /t >> nbt_realloc.txt");
    system("time /t >> nbt_free.txt");

    system("time /t >> xalloc.txt");
    system("time /t >> memory.txt");

    system("timeout 2");

    system("type xmalloc.txt > XADDRESS.TXT");
    system("type xrealloc.txt >> XADDRESS.TXT");
    system("type xfree.txt >> XADDRESS.TXT");
    system("sort XADDRESS.TXT /O XADDRESS_SORTED.TXT");
    system("type nbt_malloc.txt > NBT_ADDRESS.TXT");
    system("type nbt_realloc.txt >> NBT_ADDRESS.TXT");
    system("type nbt_free.txt >> NBT_ADDRESS.TXT");
    system("sort NBT_ADDRESS.TXT /O NBT_ADDRESS_SORTED.TXT");

    system("type NBT_ADDRESS_SORTED.TXT > TOTAL.TXT");
    system("type XADDRESS_SORTED.TXT >> TOTAL.TXT");
    system("SORT /L C TOTAL.TXT /O TOTAL_SORTED.TXT");
#endif
    if (ESCAPE_PRESSED) {
        first_round=1;
        first_call=1;
        tied=0;
        tied_total=0;
        mem_start=0;
        mem_now=0;
        mem_was=0;
        mem_dif=0;
        mem_tot_dif1=0;
        mem_tot_dif2=0;
        mem_first=0;
        go_go_go=0;
        flopperdeflop=0;
        set_display_memory=0;
        loop=0;
        call=0;
        tied_total_total=0;
        total_count=0;
        total_call=0;
        count_loops=0;
    }
extern int testing;
    if (ESCAPE_PRESSED) testing=-1;
}

int main_nbt_one(char* filename_in, char* out_file, int nbt_type);

int main_nbt(char* regionname)
{
    char dir[1024];
    char filename[1024];

#ifdef SFML_ONBOARD
/*
    for (int t=0; t<30; t++) {
        kiki();
        monitor_off=1;
        sf::sleep(sf::seconds(0.1));
    }
*/
#endif



     struct stat stat_buffer;

//    printf("****************************************************************************************************************************\n");
/*
    printf("Testing raw from r.0.0/#.nbt\n");

    sprintf(dir,"%s.test",regionname);
    if (mkdir(dir) != 0) {
        if (errno != EEXIST) {
            fprintf(stderr, "FATAL ERROR: unable to create the destination directory %s Reason: %s\n", dir,  sys_errlist[errno]);
            exit(3);
        }
    }


     for (int t=0; t<1024; t++)
    {
        char filename[100];

        sprintf(filename,"%s/%d.nbt",regionname,t);
        if (stat(filename,&stat_buffer)==0)
        {
            nbt_tag_t* tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_ZLIB);

            printf("%d %s",t,filename);

            sprintf(filename,"%s/%d.txt",regionname,t);
            FILE *textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }

            sprintf(filename,"%s/%d.nbt",dir,t);
            write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_RAW);
            printf(" %s",filename);

            sprintf(filename,"%s/%d.gzip.nbt",dir,t);
            write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_GZIP);
            printf(" %s",filename);

            sprintf(filename,"%s/%d.zlib.nbt",dir,t);
            write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_ZLIB);
            printf(" %s",filename);
            nbt_free_tag(tag);

            sprintf(filename,"%s/%d.nbt",dir,t);
            tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_RAW);
            sprintf(filename,"%s/%d.txt",dir,t);
            textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }
            nbt_free_tag(tag);

            sprintf(filename,"%s/%d.gzip.nbt",dir,t);
            tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_GZIP);
            sprintf(filename,"%s/%d.gzip.txt",dir,t);
            textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }
            nbt_free_tag(tag);

            sprintf(filename,"%s/%d.zlib.nbt",dir,t);
            tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_ZLIB);
            sprintf(filename,"%s/%d.zlib.txt",dir,t);
            textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }
            nbt_free_tag(tag);


            printf("\n");
        }
*/

//  printf("****************************************************************************************************************************\n");
/*


     printf("Testing zlib from r.0.0/#.zlib.nbt\n");

    sprintf(dir,"%s.test.zlib",regionname);
    if (mkdir(dir) != 0) {
        if (errno != EEXIST) {
            fprintf(stderr, "FATAL ERROR: unable to create the destination directory %s Reason: %s\n", dir,  sys_errlist[errno]);
            exit(3);
        }
    }


     for (int t=0; t<1024; t++)
    {
        char filename[100];

        sprintf(filename,"%s/%d.zlib.nbt",regionname,t);
        if (stat(filename,&stat_buffer)==0)
        {
            nbt_tag_t* tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_ZLIB);

            printf("%d %s",t,filename);

            sprintf(filename,"%s/%d.zlib.txt",regionname,t);
            FILE *textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }

            sprintf(filename,"%s/%d.nbt",dir,t);
            write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_RAW);
            printf(" %s",filename);

            sprintf(filename,"%s/%d.gzip.nbt",dir,t);
            write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_GZIP);
            printf(" %s",filename);

            sprintf(filename,"%s/%d.zlib.nbt",dir,t);
            write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_ZLIB);
            printf(" %s",filename);
            nbt_free_tag(tag);

            sprintf(filename,"%s/%d.nbt",dir,t);
            tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_RAW);
            sprintf(filename,"%s/%d.txt",dir,t);
            textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }
            nbt_free_tag(tag);

            sprintf(filename,"%s/%d.gzip.nbt",dir,t);
            tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_GZIP);
            sprintf(filename,"%s/%d.gzip.txt",dir,t);
            textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }
            nbt_free_tag(tag);

            sprintf(filename,"%s/%d.zlib.nbt",dir,t);
            tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_ZLIB);
            sprintf(filename,"%s/%d.zlib.txt",dir,t);
            textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }
            nbt_free_tag(tag);


            printf("\n");
        }

*/

/*

     printf("Testing gzip from r.0.0/#.gzip.nbt\n");

    sprintf(dir,"%s.test.gzip",regionname);
    if (mkdir(dir) != 0) {
        if (errno != EEXIST) {
            fprintf(stderr, "FATAL ERROR: unable to create the destination directory %s Reason: %s\n", dir,  sys_errlist[errno]);
            exit(3);
        }
    }


     for (int t=0; t<1024; t++)
    {
        char filename[100];

        sprintf(filename,"%s/%d.gzip.nbt",regionname,t);
        if (stat(filename,&stat_buffer)==0)
        {
            nbt_tag_t* tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_GZIP);

            printf("%d %s",t,filename);

            sprintf(filename,"%s/%d.gzip.txt",regionname,t);
            FILE *textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }

            sprintf(filename,"%s/%d.nbt",dir,t);
            write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_RAW);
            printf(" %s",filename);

            sprintf(filename,"%s/%d.gzip.nbt",dir,t);
            write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_GZIP);
            printf(" %s",filename);

            sprintf(filename,"%s/%d.zlib.nbt",dir,t);
            write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_ZLIB);
            printf(" %s",filename);
            nbt_free_tag(tag);

            sprintf(filename,"%s/%d.nbt",dir,t);
            tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_RAW);
            sprintf(filename,"%s/%d.txt",dir,t);
            textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }
            nbt_free_tag(tag);

            sprintf(filename,"%s/%d.gzip.nbt",dir,t);
            tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_GZIP);
            sprintf(filename,"%s/%d.gzip.txt",dir,t);
            textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }
            nbt_free_tag(tag);

            sprintf(filename,"%s/%d.zlib.nbt",dir,t);
            tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_ZLIB);
            sprintf(filename,"%s/%d.zlib.txt",dir,t);
            textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }
            nbt_free_tag(tag);


            printf("\n");
        }

    }
*/


/*
    for (int p=0; p<5; p++) {
        printf("Testing load .nbt to mem, read_nbt_from_mem %s/#.nbt\n",regionname);

        sprintf(filename,"%s.nbt",regionname);
        printf("Loading file to mem: %s\n",filename);
        size_t size;
        uint8_t* region_file=load_region_file(filename,&size);

        printf("Loading tag_region from mem\n");
        nbt_tag_t* tag_region=read_nbt_from_memory(region_file,size, NBT_PARSE_FLAG_USE_RAW);
        NBT_FREE(region_file);

        tied=0;
        tied_total=0;
        PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter();

        ONLY_ONE_REGION=1;
        WRITE_WORLD(tag_region);
        ONLY_ONE_REGION=0;

        nbt_free_tag(tag_region);
    }
*/


/*
    printf("Testing combine from %s/#.nbt\n",regionname);

    sprintf(filename,"%s.mca",regionname);
    nbt_tag_t* tag_region=nbt_new_tag_compound();
    nbt_set_tag_name(tag_region,filename,strlen(filename));

    static int32_t index[1024];
    nbt_tag_t* tag_index = nbt_new_tag_int_array(index,1024);
    nbt_set_tag_name(tag_index,(char*)"index",strlen("index"));
    nbt_tag_compound_append(tag_region,tag_index);
    int chunk_count=0;
     for (int t=0; t<1024; t++)
    {

        sprintf(filename,"%s/%d.nbt",regionname,t);
        if (stat(filename,&stat_buffer)==0)
        {
            tag_index->tag_int_array.value[t]=chunk_count+1;
            chunk_count++;
            nbt_tag_t* tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_RAW);

            printf(".");

            nbt_tag_compound_append(tag_region,tag);

        }
    }

    printf("\n");

    tied=0;
    tied_total=0;
    PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter();

    ONLY_ONE_REGION=1;
    WRITE_WORLD(tag_region);
    ONLY_ONE_REGION=0;

    nbt_free_tag(tag_region);

*/

//    printf("Testing combine gzip from %s/#.gzip.nbt\n",regionname);


    sprintf(filename,"%s.mca",regionname);
    nbt_tag_t* tag_region=nbt_new_tag_compound();
    nbt_set_tag_name(tag_region,filename,strlen(filename));

    static int32_t index[1024];
    nbt_tag_t* tag_index = nbt_new_tag_int_array(index,1024);
    nbt_set_tag_name(tag_index,(char*)"index",strlen("index"));
    nbt_tag_compound_append(tag_region,tag_index);
    int chunk_count=0;
     for (int t=0; t<1024; t++)
    {

        sprintf(filename,"%s/%d.gzip.nbt",regionname,t);
        if (stat(filename,&stat_buffer)==0)
        {
            tag_index->tag_int_array.value[t]=chunk_count+1;
            chunk_count++;
            nbt_tag_t* tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_GZIP);

//            printf(".");

            nbt_tag_compound_append(tag_region,tag);

        }
    }

    printf("\n");

    tied=0;
    tied_total=0;
    PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter();

    ONLY_ONE_REGION=1;
    WRITE_WORLD(tag_region);
    ONLY_ONE_REGION=0;

    nbt_free_tag(tag_region);


/*
    printf("Testing combine zlib from %s/#.gzip.nbt\n",regionname);


    sprintf(filename,"%s.mca",regionname);
    nbt_tag_t* tag_region=nbt_new_tag_compound();
    nbt_set_tag_name(tag_region,filename,strlen(filename));

    static int32_t index[1024];
    nbt_tag_t* tag_index = nbt_new_tag_int_array(index,1024);
    nbt_set_tag_name(tag_index,(char*)"index",strlen("index"));
    nbt_tag_compound_append(tag_region,tag_index);
    int chunk_count=0;
     for (int t=0; t<1024; t++)
    {

        sprintf(filename,"%s/%d.zlib.nbt",regionname,t);
        if (stat(filename,&stat_buffer)==0)
        {
            tag_index->tag_int_array.value[t]=chunk_count+1;
            chunk_count++;
            nbt_tag_t* tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_ZLIB);

            printf(".");

            nbt_tag_compound_append(tag_region,tag);

        }
    }

    printf("\n");

    tied=0;
    tied_total=0;
    PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter();

    ONLY_ONE_REGION=1;
    WRITE_WORLD(tag_region);
    ONLY_ONE_REGION=0;

    nbt_free_tag(tag_region);
*/




//  nbt_tag_t* tag = read_nbt_file("r.0.0/0.nbt", NBT_PARSE_FLAG_USE_RAW);
//  nbt_tag_t* tag = read_nbt_file("r.0.0/0.nbt.zlib", NBT_PARSE_FLAG_USE_ZLIB);
//  nbt_tag_t* tag = read_nbt_file("r.0.0/0.nbt", NBT_PARSE_FLAG_USE_RAW);


//  main_nbt();

/*
    printf("Append Example:\n");
    nbt_tag_t* tag_level = nbt_new_tag_compound();
    nbt_set_tag_name(tag_level, (char*)"Level", strlen("Level"));

    nbt_tag_t* tag_longtest = nbt_new_tag_long(0x7fffffffffffffff);
    nbt_set_tag_name(tag_longtest, "longTest", strlen("longTest"));

    nbt_tag_t* tag_shorttest = nbt_new_tag_short(0x7fff);
    nbt_set_tag_name(tag_shorttest, "shortTest", strlen("shortTest"));

    nbt_tag_t* tag_stringtest = nbt_new_tag_string("HELLO WORLD THIS IS A TEST STRING!", strlen("HELLO WORLD THIS IS A TEST STRING!"));
    nbt_set_tag_name(tag_stringtest, "stringTest", strlen("stringTest"));

    nbt_tag_t* tag_doubletest = nbt_new_tag_double(987654321.1234567890123456789);
    nbt_set_tag_name(tag_doubletest, "doubleTest", strlen("doubleTest"));

    nbt_tag_compound_append(tag_level, tag_shorttest);
    nbt_tag_compound_append(tag_level, tag_stringtest);
    nbt_tag_compound_append(tag_level, tag_longtest);
    nbt_tag_compound_append(tag_level, tag_doubletest);
    print_nbt_tree(tag_level, 2);

    printf("Writing Example 1:\n");
    write_nbt_file("write_test_raw.nbt", tag_level, NBT_WRITE_FLAG_USE_RAW);
    nbt_tag_t* read_test_1 = read_nbt_file("write_test_raw.nbt", NBT_PARSE_FLAG_USE_RAW);
    print_nbt_tree(read_test_1, 2);


    printf("Writing Example 2:\n");
    write_nbt_file("write_test_gzip.nbt", tag_level, NBT_WRITE_FLAG_USE_GZIP);
    nbt_tag_t* read_test_3 = read_nbt_file("write_test_gzip.nbt", NBT_PARSE_FLAG_USE_GZIP);
    print_nbt_tree(read_test_3, 2);

    printf("Writing Example 3:\n");
    write_nbt_file("write_test_zlib.nbt", tag_level, NBT_WRITE_FLAG_USE_ZLIB);
    nbt_tag_t* read_test_2 = read_nbt_file("write_test_zlib.nbt", NBT_PARSE_FLAG_USE_ZLIB);
    print_nbt_tree(read_test_2, 2);

    main_nbt_one("write_test_raw.nbt",    "write_test_raw.txt",   NBT_WRITE_FLAG_USE_RAW);
    main_nbt_one("write_test_gzip.nbt",   "write_test_gzip.txt",   NBT_WRITE_FLAG_USE_GZIP);
    main_nbt_one("write_test_zlib.nbt",   "write_test_zlib.txt",   NBT_WRITE_FLAG_USE_ZLIB);
*/

/*
    main_nbt_one("r.0.0.test/0.nbt",         "r.0.0.test/0.txt",        NBT_WRITE_FLAG_USE_RAW);
    main_nbt_one("r.0.0.test/0.gzip.nbt",    "r.0.0.test/0.gzip.txt",   NBT_WRITE_FLAG_USE_GZIP);
    main_nbt_one("r.0.0.test/0.zlib.nbt",    "r.0.0.test/0.zlib.txt",       NBT_WRITE_FLAG_USE_ZLIB);
*/

    return 0;
}


int main_nbt_one(char* filename_in, char* out_file, int nbt_type)
{
    struct stat stat_buffer;
    if (stat(filename_in,&stat_buffer)==0)
    {
        nbt_tag_t* tag = read_nbt_file(filename_in, nbt_type);

        FILE *textfile=fopen(out_file,"wb");
        if (!textfile==NULL) {
            print_nbt_tree_to_file(tag, 0, textfile);
            fclose(textfile);
        }
        nbt_free_tag(tag);
    }
    return 0;
}

/***************************************************************************************/


nbt_tag_t* main_mca2nbt(int argc, char *argv[]);
nbt_tag_t* main_mca2nbt_adapted(int argc, char *argv[]);

int skippy=1;

void WRITE_REGION_FROM_DIRS(char* regionname) {
    struct stat stat_buffer;
    char filename[1024];
    sprintf(filename,"%s.mca",regionname);
    nbt_tag_t* tag_region=nbt_new_tag_compound();
    nbt_set_tag_name(tag_region,filename,strlen(filename));

    static int32_t index[1024];
    nbt_tag_t* tag_index = nbt_new_tag_int_array(index,1024);
    nbt_set_tag_name(tag_index,(char*)"index",strlen("index"));
    nbt_tag_compound_append(tag_region,tag_index);
    int chunk_count=0;
     for (int t=0; t<1024; t++)
    {

        sprintf(filename,"%s/%d.gzip.nbt",regionname,t);
        if (stat(filename,&stat_buffer)==0)
        {
            tag_index->tag_int_array.value[t]=chunk_count+1;
            chunk_count++;
            nbt_tag_t* tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_GZIP);

//            printf(".");

            nbt_tag_compound_append(tag_region,tag);

        }
    }

    printf("\n");

    tied=0;
    tied_total=0;
    PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter();

    ONLY_ONE_REGION=1;
    WRITE_WORLD(tag_region);
    ONLY_ONE_REGION=0;

    nbt_free_tag(tag_region);
}

/*
void do_one(char* filename) {
    skippy=0;
    char *m_argv[2];
    char arg1[20]="ik";
//    char arg2[20]="r.0.0.mca";
    m_argv[0]=arg1;
    m_argv[1]=filename;
    nbt_free_tag(main_mca2nbt(2,m_argv));
//    main_nbt();
    skippy=1;
}
*/
int num_chunks=0;

/*
void do_world(char* filename) {
    num_chunks=0;
    skippy=1;
    char name[1000];
    char *m_argv[2];
    char arg1[20]="ik";
    char arg2[1000];
    m_argv[0]=arg1;

#ifdef SFML_ONBOARD

//    for (int t=0; t<35; t++) {
//        kiki();
//        monitor_off=1;
//        sf::sleep(sf::seconds(0.1));
//    }

#endif
//    printf("World: %s\n",filename);
    char dir[1000];
    char naam[1000];
    sprintf(dir, "%s/region",filename);
//    printf("Dir: %s\n",dir);
    sprintf(naam,"%s",dir);
    DIR *dr = opendir(naam);

    nbt_tag_t* tag_region;
    nbt_tag_t* tag_world = nbt_new_tag_compound();
    nbt_set_tag_name(tag_world, filename, strlen(filename));

    double tied=0;
    double tied_total=0;
    PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter();

    struct dirent *de;
    printf("TO DO: ");
    while ((de = readdir(dr)) != NULL) {
        if ((strstr(de->d_name, ".mca")) != NULL) {
            printf(de->d_name);
            printf(" ");
        }
    }
//    printf("\n");
    closedir(dr);
    dr = opendir(naam);
    int teller=0;
    char file_in[1000];
    char file_out[1000];
    while (((de = readdir(dr)) != NULL)) {
        teller++;
        char* offset=0;
        if ( ((offset=strstr(de->d_name, ".mca")) != NULL) && ((strstr(de->d_name, ".gzip")) == NULL) ) {
            sprintf(arg2,"%s/%s",dir,de->d_name);
            strcpy(file_in,arg2);
            printf("Total: %9.3f Time: %9.6f written %s\r\n",tied_total,tied,name);
            printf("Reading: %s",file_in);
            m_argv[1]=arg2;
//            printf("Region: %s\n",m_argv[1]);
            tag_region=main_mca2nbt(2,m_argv);
            tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;

            m_argv[1]=arg2;
            arg2[0]='\0';
//            offset[0]='\0';
            strcat(arg2,".gzip.nbt");
            printf(" Saving to: %s\n",arg2);

            write_nbt_file(arg2, tag_region, NBT_WRITE_FLAG_USE_GZIP);

            nbt_tag_compound_append(tag_world, tag_region);

        } else {
            sprintf(arg2,"Skipping: %s\n",de->d_name);
        }
    }
    closedir(dr);
    printf("Total: %9.3f Time: %9.6f Total number of chunks read: %d\n",tied_total,tied,num_chunks);

    FILE* file;
    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;

    sprintf(name,"%s/region/%s.nbt",filename,filename);
    write_nbt_file(name, tag_world, NBT_WRITE_FLAG_USE_RAW);
    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
    printf("Total: %9.3f Time: %9.6f written %s\r\n",tied_total,tied,name);
//    cout << " Total: " << tied_total << " Time: " << tied << " written " << name << "\r\n";

    sprintf(name,"%s/region/%s.zlib.nbt",filename,filename);
    write_nbt_file(name, tag_world, NBT_WRITE_FLAG_USE_ZLIB);
    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
    printf("Total: %9.3f Time: %9.6f written %s\r\n",tied_total,tied,name);


    sprintf(name,"%s/region/%s.gzip.nbt",filename,filename);
    write_nbt_file(name, tag_world, NBT_WRITE_FLAG_USE_GZIP);
    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
    printf("Total: %9.3f Time: %9.6f written %s\r\n",tied_total,tied,name);


    sprintf(name,"%s/region/%s.txt",filename,filename);
    if ((file = fopen(name, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing world text file\n", name);
        nbt_free_tag(tag_world); exit(15);
    }
    print_nbt_tree_to_file(tag_world, 0, file);
    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
    printf("Total: %9.3f Time: %9.3f written %s\r\n",tied_total,tied,name);
    fclose(file);

    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
    printf("Total: %9.3f Time: %9.3f file closed %f\r\n",tied_total,tied);
    printf("\n");

    nbt_free_tag(tag_world);

    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
//    printf("Total: %9.3f Time: %9.6f file tag_world freed\r\n",tied_total,tied);
}
*/

extern int zpipe(FILE *in, FILE *out);

static const char VersionId[] = "@(#) mca2nbt v1.00 (2014-05-05) / Hubert Tournier";

nbt_tag_t* main_mca2nbt(int argc, char *argv[])
{
	int	region;

    char name[1000];

//    printf("I am here\n");
	if (argc < 2)
	{
		fprintf(stderr, "%s\n", &VersionId[5]);
		fprintf(stderr, "Usage: %s file.mca ...\n", argv[0]);
		exit(1);
	}
//    printf("I am here 20\n");

/*
    for (int t=0; t<35; t++) {
        kiki();
        monitor_off=1;
        sf::sleep(sf::seconds(0.1));
    }
*/
    nbt_tag_t* tag;

	for (region = 1; region < argc; region++)
	{
		FILE 			*input_file,*header_output_file;
		char			output_directory_name[1024],
                        header_output_file_path[1024],
                        *p_file_extension,
                        *p_file;
		RegionFileHeader	header;
		int			i;

//        printf("I am here 21 - %d\n",region);
//        printf("I am here 21 - %s\n",argv[region]);

		/* make a directory to receive the chunk files for this region */
		/***************************************************************/
		strcpy(output_directory_name, argv[region]);
//        printf("I am here 22\n");
		if ((p_file_extension = strstr(output_directory_name, ".mca")) == NULL)
		{
			fprintf(stderr, "FATAL ERROR: file name \"%s\" has no .mca extension\n", argv[region]);
//            printf("I am here 2\n");
			exit(2);
		}
		else
		{
			*p_file_extension = 0;
//            printf("I am here 3\n");
		}
//        printf("I am here 23\n");
		if (mkdir(output_directory_name) != 0)
//		if (_mkdir(output_directory_name, "0755") != 0)
		{
//            printf("I am here 4\n");
			if (errno != EEXIST)
			{
//                printf("I am here 5\n");
				fprintf(stderr, "FATAL ERROR: unable to create the destination directory \"%s\"\nReason: %s\n", argv[region], sys_errlist[errno]);
				exit(3);
			}
		}


		/* read the region file header */
		/*******************************/
		if ((input_file = fopen(argv[region], "rb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open \"%s\"\n", argv[region]); exit(4); }

		int res;
		res=fread(&header, sizeof(RegionFileHeader), 1, input_file);

		if ( res != 1) { fprintf(stderr, "FATAL ERROR: unable to read the region file header for \"%s\"\n", argv[region]); exit(5); }

		/* write the region file header to a file                                            */
		/* (in case someone would want to reconstruct the MCA file from the directory files) */
		/*************************************************************************************/
//        printf("I am here 10\n");

		sprintf(header_output_file_path, "%s/header.bin", output_directory_name);
		if ((header_output_file = fopen(header_output_file_path, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing header\n", header_output_file_path); exit(6); }
		if (fwrite(&header, sizeof(RegionFileHeader), 1, header_output_file) != 1) { fprintf(stderr, "FATAL ERROR: unable to write header to file \"%s\"\n", header_output_file_path); exit(7); }
		fclose(header_output_file);

//        printf("I am here 12\n");

		/* for each chunk entry... */
		/***************************/
/*
        if (mkdir("r.0.0.from_mem") != 0) {
            if (errno != EEXIST) {
                fprintf(stderr, "FATAL ERROR: unable to create the destination directory r.0.0.from_mem Reason: %s\n",  sys_errlist[errno]);
                exit(3);
            }
        }
*/
   		if ((p_file = strstr(output_directory_name, "/r.")) != NULL) {
                p_file++;
   		} else p_file=argv[region];

        nbt_tag_t* tag_region = nbt_new_tag_compound();
        nbt_set_tag_name(tag_region, (char*)p_file, strlen(p_file));

        nbt_tag_t* tag_chunk;
        double tied=0;
        char out[200];
        int cnt;
        cnt=0;
        sprintf(out,"%9.6lf %s",tied,argv[region]);
        printf(out); cnt=strlen(out);
//        printf("Chunks:");
        tied=GetCounterNanoseconds();
        int chunk_count=0;
		for (i = 0; i < CHUNKS_PER_REGION; i++)
		{
            FILE* file;
#ifdef SFML_ONBOARD
            if ((i%16)==0) kiki();
            monitor_off=1;
#endif
			unsigned int	offset,					length;
			ChunkDataHeader	header_chunk;

			offset = (65536 * header.locations[i].offset[0]) + (256 * header.locations[i].offset[1]) + header.locations[i].offset[2];
//            printf("header.locations[%d].sector_count=%d\n",i, header.locations[i].sector_count);

			if (offset != 0)
			{
                chunk_count++;
				char	*chunk;
				FILE	*deflated_output_file,					*uncompressed_output_file;
				char	deflated_output_file_path[1024], 		uncompressed_output_file_path[1024];

				/* read the chunk header */
				/*************************/
				if (fseek(input_file, offset * 4096, SEEK_SET) == -1) {	fprintf(stderr, "FATAL ERROR: unable to seek to chunk #d in \"%s\"\n", i, argv[region]); exit(8); }
				if (fread(&header_chunk, sizeof(ChunkDataHeader), 1, input_file) != 1) { fprintf(stderr, "FATAL ERROR: unable to read chunk #%d header in \"%s\"\n", i, argv[region]); exit(9); }
				length = (16777216 * header_chunk.length[0]) + (65536 * header_chunk.length[1]) + (256 * header_chunk.length[2]) + header_chunk.length[3];

				/* verify structure */
				/********************/
				if (length > 4096 * header.locations[i].sector_count) { fprintf(stderr, "FATAL ERROR: chunk #%d is bigger than expected (%u bytes vs %u) in \"%s\"\n", i, length, 4096 * header.locations[i].sector_count, argv[region]); exit(10); }
				if (header_chunk.compression_type != COMPRESSION_TYPE_GZIP && header_chunk.compression_type != COMPRESSION_TYPE_ZLIB) { fprintf(stderr, "FATAL ERROR: chunk #%d has unknown compression type (%u) in \"%s\"\n", i, header_chunk.compression_type, argv[region]); exit(11); }

//				else if (header_chunk.compression_type == COMPRESSION_TYPE_GZIP) { fprintf(stderr, "FATAL ERROR: chunk #%d is compressed with gzip, that this program doesn't support, in \"%s\"\n", i, argv[region]); exit(12); }

				/* read the rest of the chunk */
				/******************************/
				if ((chunk = (char*) malloc(length - 1)) == NULL) { fprintf(stderr, "FATAL ERROR: unable to alloc %u bytes of memory to read chunk #%d in \"%s\"\n", length, i, argv[region]); exit(13); }
				if (fread(chunk, length - 1, 1, input_file) != 1) { fprintf(stderr, "FATAL ERROR: unable to read chunk #%d data in \"%s\"\n", i, argv[region]); free(chunk); exit(14); }

//				/* write the chunk as an individual deflated NBT file */
//				/******************************************************/

                if (skippy==0) {
                    if (header_chunk.compression_type == COMPRESSION_TYPE_GZIP) {
                        sprintf(deflated_output_file_path, "%s/%d.gzip.nbt", output_directory_name, i);
                        if ((deflated_output_file = fopen(deflated_output_file_path, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing chunk #%d\n", deflated_output_file_path, i); free(chunk); exit(15); }
                        if (fwrite(chunk, length - 1, 1, deflated_output_file) != 1) { fprintf(stderr, "FATAL ERROR: unable to write chunk #%d data to file \"%s\"\n", i, deflated_output_file_path);free(chunk);exit(16);}
                        fclose(deflated_output_file);
                    } else {
                        sprintf(deflated_output_file_path, "%s/%d.zlib.nbt", output_directory_name, i);
                        if ((deflated_output_file = fopen(deflated_output_file_path, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing chunk #%d\n", deflated_output_file_path, i); free(chunk); exit(15); }
                        if (fwrite(chunk, length - 1, 1, deflated_output_file) != 1) { fprintf(stderr, "FATAL ERROR: unable to write chunk #%d data to file \"%s\"\n", i, deflated_output_file_path);free(chunk);exit(16);}
                        fclose(deflated_output_file);
                    }
                }

                //bling bling

                tag_chunk=NULL;
                if (header_chunk.compression_type == COMPRESSION_TYPE_ZLIB) {
                    tag_chunk = read_nbt_from_memory((uint8_t*) chunk, length-1, NBT_PARSE_FLAG_USE_ZLIB);
                } else {
                    tag_chunk = read_nbt_from_memory((uint8_t*) chunk, length-1, NBT_PARSE_FLAG_USE_GZIP);
                }

                nbt_tag_t* tag_n = nbt_new_tag_short(i);            nbt_set_tag_name(tag_n, "chunk",    strlen("chunk"));
                nbt_tag_t* tag_x = nbt_new_tag_short(i%32);         nbt_set_tag_name(tag_x, "x",        strlen("x"));
                nbt_tag_t* tag_z = nbt_new_tag_short((int)(i/32));  nbt_set_tag_name(tag_z, "z",        strlen("z"));
                nbt_tag_compound_append(tag_chunk, tag_n);
                nbt_tag_compound_append(tag_chunk, tag_x);
                nbt_tag_compound_append(tag_chunk, tag_z);
                tag_n=NULL;tag_x=NULL;tag_z=NULL;

                nbt_tag_t* tag_timestamp = nbt_new_tag_long((int64_t)header.timestamps[i].timestamp);
                nbt_set_tag_name(tag_timestamp, "timestamp" , strlen("timestamp"));
                nbt_tag_compound_append(tag_chunk,tag_timestamp);

                sprintf(name,"chunk %d",i);
                nbt_set_tag_name(tag_chunk, (char*)name, strlen(name));
                nbt_tag_compound_append(tag_region, tag_chunk);

                if (skippy==0) {
                    sprintf(name, "%s/%d.gzip.nbt", output_directory_name, i);
                    write_nbt_file(name, tag_chunk, NBT_WRITE_FLAG_USE_GZIP);

                    sprintf(name, "%s/%d.nbt", output_directory_name, i);
                    write_nbt_file(name, tag_chunk, NBT_WRITE_FLAG_USE_RAW);


                    sprintf(name,"%s/%d.txt",output_directory_name,i);
                    if ((file = fopen(name, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing region #%d text file\n", name, region); nbt_free_tag(tag_region); exit(15); }
                    print_nbt_tree_to_file(tag_chunk, 0, file);
                    fclose(file);
                }


                if ((i%32)==0) { printf("."); cnt++; }
/*
				if ((deflated_output_file = fopen(deflated_output_file_path, "rb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for reading deflated\n", deflated_output_file_path); exit(17); }
				sprintf(uncompressed_output_file_path, "%s/%d.nbt", output_directory_name, i);
				if ((uncompressed_output_file = fopen(uncompressed_output_file_path, "wb")) == NULL) { fclose(deflated_output_file); fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing uncompressed output\n", uncompressed_output_file_path); exit(18); }

				zpipe(deflated_output_file,uncompressed_output_file);

                fclose(deflated_output_file);
                fclose(uncompressed_output_file);
                printf(" %s\n",uncompressed_output_file_path);
*/

				free(chunk);

			}
		}

        while (cnt<70) { printf("."); cnt++; }
        cnt=0;
        printf("%d chunks\n",chunk_count);
        num_chunks+=chunk_count;
//        double tied=0;
//        double tied_total=0;
        FILE* file;

//        tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
//        cout << " Total: " << tied_total << " Time: " << tied << "  chunks\r\n";

   		if ((p_file = strstr(output_directory_name, "r.")) != NULL) {
            argv[region]=p_file;
//            printf("argv[region]=%s\n",argv[region]);
   		}
/*
   		if ((p_file = strstr(output_directory_name, "/region/")) != NULL) {
            *(p_file+7)=0;
            printf("output_directory_name=%s\n",output_directory_name);
   		}
*/

/*
		sprintf(name,"%s/%s.nbt",output_directory_name,argv[region]);
		printf("name=%s\n",name);
        write_nbt_file(name, tag_region, NBT_WRITE_FLAG_USE_RAW);
        tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
        cout << " Total: " << tied_total << " Time: " << tied << " written " << name << "\r\n";


		sprintf(name,"%s/%s.zlib.nbt",output_directory_name,argv[region]);
        write_nbt_file(name, tag_region, NBT_WRITE_FLAG_USE_ZLIB);
        tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
        cout << " Total: " << tied_total << " Time: " << tied << " written" << name << "\r\n";


		sprintf(name,"%s/%s.gzip.nbt",output_directory_name,argv[region]);
        write_nbt_file(name, tag_region, NBT_WRITE_FLAG_USE_GZIP);
        cout << name << "\r\n";
        tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
        cout << " Total: " << tied_total << " Time: " << tied << " written " << name << "\r\n";



		sprintf(name,"%s/%s.txt",output_directory_name,argv[region]);
        if ((file = fopen(name, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing region #%d text file\n", name, region); nbt_free_tag(tag_region); exit(15); }
        print_nbt_tree_to_file(tag_region, 0, file);
        tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
        cout << " Total: " << tied_total << " Time: " << tied << " written" << name << "\r\n";
        fclose(file);
        tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
        cout << " Total: " << tied_total << " Time: " << tied << " output_file closed: " << "\r\n";

*/

		fclose(input_file);
//        tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
//        cout << " Total: " << tied_total << " Time: " << tied << " input_file closed"  << "\r\n";

//        tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
//        cout << " Total: " << tied_total << " Time: " << tied << " tag_region freed" << "\r\n";

//        nbt_tag_compound_append(tag_world, tag_region);
        tag=tag_region;
	}

    return tag;
/*
    printf("\n");
    double tied=0;
    double tied_total=0;
    FILE* file;

    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
    cout << " Total: " << tied_total << " Time: " << tied << "  chunks\r\n";

    sprintf(name,"world.nbt");
    write_nbt_file(name, tag_world, NBT_WRITE_FLAG_USE_RAW);
    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
    cout << " Total: " << tied_total << " Time: " << tied << " written" << name << "\r\n";

    sprintf(name,"world.zlib.nbt");
    write_nbt_file(name, tag_world, NBT_WRITE_FLAG_USE_ZLIB);
    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
    cout << " Total: " << tied_total << " Time: " << tied << " written" << name << "\r\n";

    sprintf(name,"world.gzip.nbt");
    write_nbt_file(name, tag_world, NBT_WRITE_FLAG_USE_GZIP);
    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
    cout << " Total: " << tied_total << " Time: " << tied << " written" << name << "\r\n";

    sprintf(name,"world.txt");
    if ((file = fopen(name, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing world #%d text file\n", name, region); nbt_free_tag(tag_world); exit(15); }
    print_nbt_tree_to_file(tag_world, 0, file);
    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
    cout << " Total: " << tied_total << " Time: " << tied << " written" << name << "\r\n";

    fclose(file);
    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
    cout << " Total: " << tied_total << " Time: " << tied << " output_file closed: " << "\r\n";

    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
    cout << " Total: " << tied_total << " Time: " << tied << " tag_world freed" << "\r\n";

    nbt_free_tag(tag_world);
*/
}


/*int main()
{
    QueryPerformanceFrequency(&sys_freq);

    StartCounter(); Sleep(xxxx); cout << GetCounterNanoseconds();

    return 0;
}
*/
extern int fast;

void region_header(char* filename);

int TO_DIRS=0;
int TO_GZIPS=0;

void READ_WORLD_TO_DIRS(char* filename) {
    TO_DIRS=1;
    READ_WORLD(filename);
    TO_DIRS=0;
}

void READ_WORLD_TO_GZIPS(char* filename) {
    TO_GZIPS=1;
    READ_WORLD(filename);
    TO_GZIPS=0;
}

void READ_REGION_TO_DIR(char* filename) {
    if (!file_exists(filename)) { printf("Can not read file %s\n",filename); return; }
    TO_DIRS=1;
    READ_REGION(filename);
    TO_DIRS=0;
}

void READ_REGION_TO_GZIP(char* filename) {
    TO_GZIPS=1;
    READ_REGION(filename);
    TO_GZIPS=0;
}


void READ_REGION(char* filename) {
#ifdef SFML_ONBOARD
    fast=1;
#endif // SFML_ONBOARD

//    skippy=0;
    ONLY_ONE_REGION=1;
    READ_WORLD(filename);
    ONLY_ONE_REGION=0;
//    skippy=1;

#ifdef SFML_ONBOARD
    fast=1;
#endif // SFML_ONBOARD
}

void READ_WORLD(char* filename) {
//    double tied=0;
//    double tied_total=0;
    tied=0;
    tied_total=0;
    if (!set_quiet) { PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter(); }

    num_chunks=0;
    if (!ONLY_ONE_REGION) {
        skippy=1;
//        check_memory_tofile("READ_WORLD:");
    }
//hoppa
//    skippy=0;
    shut_up=1;
    char name[1000];
    char *m_argv[2];
    char arg1[20]="ik";
    char arg2[1000];
    m_argv[0]=arg1;

#ifdef SFML_ONBOARD
/*
    if (fast==0)
        if (!(set_display_memory && set_quiet)) {
            for (int t=0; t<35; t++) {
                kiki();
                monitor_off=1;
                sf::sleep(sf::seconds(0.1));
            }
        }
*/
#endif
//    printf("World: %s\n",filename);
    char dir[1000];
    char naam[1000];
    char out[1000];
    char* p_file;

    nbt_tag_t* tag_region;
    nbt_tag_t* tag_world;
    DIR* dr;
    struct dirent *de;
    int maxlen=0;

    if (!ONLY_ONE_REGION) {
        tag_world = nbt_new_tag_compound();
        nbt_set_tag_name(tag_world, filename, strlen(filename));
        sprintf(out, "%s/nbt",filename);
        if (mkdir(out) != 0) { if (errno != EEXIST) { fprintf(stderr, "FATAL ERROR: unable to create the destination directory \"%s\"\nReason: %s\n", out, sys_errlist[errno]); exit(3); } }
        sprintf(dir, "%s/region",filename);
        if (!set_quiet) printf("%7.3f -%7.3f ",tied_total,tied);
        if (!set_quiet) printf("Dir: %s\n",dir);
        sprintf(naam,"%s",dir);
        dr = opendir(naam);

        if (!set_quiet) printf("TO DO: ");
        while ((de = readdir(dr)) != NULL) {
            if ( (p_file=strstr(de->d_name, ".mca"))!= NULL ) {
                if (strlen(p_file)==4) {
                    if (!set_quiet) printf(de->d_name);
                    if (!set_quiet) printf(" ");
//                    if (de->d_namlen>maxlen) maxlen=de->d_namlen;
                }
            }
        }
//        maxlen-=4;
        if (!set_quiet) printf("\n");
        closedir(dr);
        dr = opendir(naam);
    }
    maxlen=15;
    int teller=0;
    char file_in[1000];
    char file_out[1000];
    while (!ESCAPE_PRESSED) {
//        if (!ONLY_ONE_REGION)
//            check_memory_tofile("          :");
        char* offset=0;
        char region_file[100];

        if (!ONLY_ONE_REGION) {
            if ((de = readdir(dr)) == NULL) break;
            if ( (p_file=strstr(de->d_name, ".mca"))==NULL ) continue;
            if ( strlen(p_file)!=4) continue;
            teller++;
            sprintf(arg2,"%s/%s",dir,de->d_name);
        } else {
            strcpy(arg2,filename);
            if (skippy==0)
                strcpy(out,"nbt");
            else
                strcpy(out,".");
            if (mkdir(out) != 0) { if (errno != EEXIST) { fprintf(stderr, "FATAL ERROR: unable to create the destination directory \"%s\"\nReason: %s\n", out, sys_errlist[errno]); exit(3); } }
//            if ((p_file = strstr(out, "/r.")) != NULL) {
//                *p_file=0;
//            } else {
//                strcpy(out,"nbt");
//            }
//            sprintf(out, "%s/nbt",filename);

        }
//        printf("filename=%s, out=%s \n",filename,out);
//        printf("file: %s/%s\n",dir,de->d_name);

//        printf("arg2=%s\n",arg2);
        if ( ((offset=strstr(arg2, ".mca")) != NULL) ) {

//            region_header(arg2);

            if (!ONLY_ONE_REGION) {
                strcpy(region_file,de->d_name); // with .mca in name...
            } else {
                strcpy(region_file,filename);
            }

            if ((p_file = strstr(region_file, ".mca")) != NULL) { *p_file = 0; }  // cut off .mca
//            if (!set_quiet) printf("region_file=%s\n",region_file);
            if ((p_file = strstr(region_file, "r.")) != NULL) { } //p_file point to filename without .mca extension
            else { printf("error filename region file...\n"); return; }

            strcpy(file_in,arg2); strcat(file_in,"\0");

            if (!set_quiet) { tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied; }
            if (!set_quiet) printf("%7.3f -%7.3f ",tied_total,0.0);

//            if (!set_quiet) printf("Reading: %s",de->d_name);
            if (!set_quiet) printf("Reading: %s.mca",region_file);
//            if (!set_quiet) printf("Reading: %s",p_file);
            if (!set_quiet) if (strlen(p_file)<maxlen) for (int p=0; p<(maxlen-strlen(p_file)); p++) printf(".");
            m_argv[1]=arg2;

//            printf("main_mca2nbt_adapted(2,\"%s\",\"%s\");",m_argv[1],out);

            tag_region=main_mca2nbt_adapted(2,m_argv,out);

            if (tag_region==0) {
                printf("\nError tag_region==NULL\n");
                return;
            }

            sprintf(arg2,"%s/%s",out,p_file);
            m_argv[1]=arg2;  //reset if moved by main_mca2nbt_adapted
            if (!set_quiet) printf(" Columns ");
            if (TO_GZIPS==1) {
                if (!set_quiet) printf("-> %s/%s.gzip.nbt ",out,p_file);
                strcpy(file_out,arg2); strcat(file_out,".gzip.nbt");
                write_nbt_file(file_out, tag_region, NBT_WRITE_FLAG_USE_GZIP);
                if (!set_quiet) if (strlen(p_file)<maxlen) for (int p=0; p<(maxlen-strlen(p_file)); p++) printf(" ");
            }
            if (skippy==0) {
                if (!set_quiet) printf("-> %s/%s/*.zlib ",out,p_file);

                if (!set_quiet) if (strlen(p_file)<maxlen) for (int p=0; p<(maxlen-strlen(p_file)); p++) printf(" ");
                if (!set_quiet) printf("-> %s/%s.gzip.nbt ",out,p_file);
                strcpy(file_out,arg2); strcat(file_out,".gzip.nbt");
                write_nbt_file(file_out, tag_region, NBT_WRITE_FLAG_USE_GZIP);

                if (!set_quiet) if (strlen(p_file)<maxlen) for (int p=0; p<(maxlen-strlen(p_file)); p++) printf(" ");
                if (!set_quiet) printf("-> %s/%s.zlib.nbt ",out,p_file);
                strcpy(file_out,arg2); strcat(file_out,".zlib.nbt");
                write_nbt_file(file_out, tag_region, NBT_WRITE_FLAG_USE_ZLIB);

                if (!set_quiet) if (strlen(p_file)<maxlen) for (int p=0; p<(maxlen-strlen(p_file)); p++) printf(" ");
                if (!set_quiet) printf("-> %s/%s.nbt ",out,p_file);
                strcpy(file_out,arg2); strcat(file_out,".nbt");
                write_nbt_file(file_out, tag_region, NBT_WRITE_FLAG_USE_RAW);

                if (!set_quiet) if (strlen(p_file)<maxlen) for (int p=0; p<(maxlen-strlen(p_file)); p++) printf(" ");
                if (!set_quiet) printf("-> %s/%s.txt ",out,p_file);
                strcpy(file_out,arg2); strcat(file_out,".txt");
                nbt_to_textfile(tag_region , file_out);

            }

//            printf("\nTESTING %s\n",file_out);                  //arge nbt files are to slow to read..... columns nbt's needed????????????? f*k!
//            nbt_tag_t* test=read_nbt_file(file_out,NBT_WRITE_FLAG_USE_RAW);
//            printf("\nTESTING OK!!!!!\n");
//            nbt_free_tag(test);

            if (!ONLY_ONE_REGION) {
                if (TO_DIRS)
                    if (!set_quiet) printf("-> Written to %s/%s",out,p_file);
//                if (!set_quiet) printf("-> Freeing tag");
                if (!set_quiet) printf("-> Appending");
//                int regx,regz;
//                sscanf(p_file,"r.%d.%d",&regx,&regz);

//                nbt_tag_t* tag_x = nbt_new_tag_int(regx);  nbt_set_tag_name(tag_x, "x",        strlen("x"));
//                nbt_tag_t* tag_z = nbt_new_tag_int(regz);  nbt_set_tag_name(tag_z, "z",        strlen("z"));
//                nbt_tag_compound_append(tag_region, tag_x);
//                nbt_tag_compound_append(tag_region, tag_z);

//ALERT, CREATING WORLD FILE SET TO OFF HOPPA JOEPIE HITLER

                nbt_tag_compound_append(tag_world, tag_region);

//                nbt_free_tag(tag_region);
// TEST
//                nbt_tag_t* column=GET_COLUMN(tag_region,33%32,(int)(33/32));
//                if (column!=0) printf("\ncolumn=%s\n",column->name);
//                column=GET_COLUMN(tag_region,1023);
//                if (column!=0) printf("\ncolumn=%s\n",column->name);
            }
            if (ONLY_ONE_REGION) {
                if (TO_DIRS)
                    if (!set_quiet) printf("-> Written to %s/%s",out,p_file);
                nbt_free_tag(tag_region);
                break;
            }
            if (!set_quiet) { tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied; }
            if (!set_quiet) printf("\r");
            if (!set_quiet) printf("%7.3f -%7.3f\n",tied_total,tied);

        } else {
            sprintf(arg2,"Skipping: %s\n",de->d_name);
        }
    }
    if (!ONLY_ONE_REGION) {
        closedir(dr);
    }
    if (!set_quiet) { tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied; }
    if (!ONLY_ONE_REGION)
        if (!set_quiet) printf("%7.3f -%7.3f Total number of column files written: %d\n",tied_total,tied,num_chunks);

    if (!ONLY_ONE_REGION) {

        FILE* file;

/*
        sprintf(name,"%s/%s.nbt",out,filename);
        if (!set_quiet) printf("%7.3f -%7.3f Writing %s\r",tied_total,0.0,name);
        write_nbt_file(name, tag_world, NBT_WRITE_FLAG_USE_RAW);
        tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
        if (!set_quiet) printf("%7.3f -%7.3f\n",tied_total,tied);


        sprintf(name,"%s/%s.zlib.nbt",out,filename);
        if (!set_quiet) printf("%7.3f -%7.3f Writing %s\r",tied_total,0.0,name);
        write_nbt_file(name, tag_world, NBT_WRITE_FLAG_USE_ZLIB);
        tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
        if (!set_quiet) printf("%7.3f -%7.3f\n",tied_total,tied);
*/

        if (TO_GZIPS) {
            sprintf(name,"%s/%s.gzip.nbt",out,filename);
            if (!set_quiet) printf("%7.3f -%7.3f Writing %s\r",tied_total,0.0,name);
            write_nbt_file(name, tag_world, NBT_WRITE_FLAG_USE_GZIP);
            tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
            if (!set_quiet) printf("%7.3f -%7.3f\n",tied_total,tied);
        }


/*
        sprintf(name,"%s/%s.txt",out,filename);
        if (!set_quiet) printf("%7.3f -%7.3f Writing %s\r",tied_total,0.0,name);
        if ((file = fopen(name, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing world text file\n", name);
            nbt_free_tag(tag_world); exit(15);
        }
        print_nbt_tree_to_file(tag_world, 0, file);
        fclose(file);
        tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
        if (!set_quiet) printf("%7.3f -%7.3f\n",tied_total,tied);
*/


// TEST
//        for (int i=0; i<1000; i++) {
//            nbt_tag_t* reg=GET_REGION(tag_world,rand()%7-3,rand()%7-3);
//            if (reg!=0) printf("%s ",reg->name);
//            if (reg!=0) printf("region test = %s\n",reg->name);
//        }



//        if (!set_quiet) printf("%7.3f -%7.3f Writing world\n",tied_total,0.0);

//test
//        WRITE_WORLD(tag_world);


    //    do_one("World/region/r.0.0.mca");

        if (!set_quiet) { tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied; }
//        if (!set_quiet) printf("%7.3f -%7.3f\n",tied_total,tied);

//        if (!set_quiet) printf("%7.3f -%7.3f Freeing tag_world\r",tied_total,0.0);
        nbt_free_tag(tag_world);

//        tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
//        if (!set_quiet) printf("%7.3f -%7.3f\n",tied_total,tied);
    }

//    if (!set_quiet) printf("%Ready\n");
    shut_up=0;
    skippy=0;
}

nbt_tag_t* main_mca2nbt_adapted(int argc, char *argv[], char* out_dir)
{
	int	region;

    char name[1000];

	if (argc < 2)
	{
		fprintf(stderr, "%s\n", &VersionId[5]);
		fprintf(stderr, "Usage: %s file.mca ...\n", argv[0]);
		exit(1);
	}

    nbt_tag_t* tag;

	for (region = 1; region < argc; region++)
	{
        printf("                                          \r");printf(argv[region]);
        FILE 			*input_file,*header_output_file;
		char			output_directory_name[1024],
                        header_output_file_path[1024],
                        *p_file_extension,
                        *p_file,
                        name[100];

		RegionFileHeader	header;
		int			i;

		strcpy(output_directory_name, argv[region]);
		if ((p_file_extension = strstr(output_directory_name, ".mca")) == NULL)	{
                fprintf(stderr, "FATAL ERROR: file name \"%s\" has no .mca extension\n", argv[region]); exit(2);
        } else { *p_file_extension = 0; }

   		if ((p_file = strstr(output_directory_name, "r.")) != NULL) {
//                p_file++;
   		} else p_file=argv[region];

        sprintf(name,"%s",p_file);
        sprintf(output_directory_name,"%s/%s",out_dir,name);
        strcat(name,".mca");

		if ((input_file = fopen(argv[region], "rb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open \"%s\"\n", argv[region]); return(0); }

		int res;
		res=fread(&header, sizeof(RegionFileHeader), 1, input_file);
		if ( res != 1) { fprintf(stderr, "FATAL ERROR: unable to read the region file header for \"%s\"\n", argv[region]); exit(5); }

        if (skippy==0) {
            if (mkdir(output_directory_name) != 0) { if (errno != EEXIST) { fprintf(stderr, "FATAL ERROR: unable to create the destination directory \"%s\"\nReason: %s\n", argv[region], sys_errlist[errno]); exit(3); } }

    		sprintf(header_output_file_path, "%s/header.bin", output_directory_name);
    		if ((header_output_file = fopen(header_output_file_path, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing header\n", header_output_file_path); exit(6); }
    		if (fwrite(&header, sizeof(RegionFileHeader), 1, header_output_file) != 1) { fprintf(stderr, "FATAL ERROR: unable to write header to file \"%s\"\n", header_output_file_path); exit(7); }
    		fclose(header_output_file);

        }

        nbt_tag_t* tag_region;
        tag_region=NULL;
        tag_region = nbt_new_tag_compound();
        nbt_set_tag_name(tag_region, (char*)name, strlen(name));

        int32_t index[1024];
        nbt_tag_t* tag_index = nbt_new_tag_int_array(index,1024);
        nbt_set_tag_name(tag_index,(char*)"index",strlen("index"));
        nbt_tag_compound_append(tag_region,tag_index);

        nbt_tag_t* tag_chunk;
        double tied=0;
        char out[200];
        int cnt;
        cnt=0;
        sprintf(out,"%9.6lf %s",tied,argv[region]);
        tied=GetCounterNanoseconds();
        int32_t chunk_count=0;
		for (i = 0; i < CHUNKS_PER_REGION; i++)
		{
            FILE* file;
#ifdef SFML_ONBOARD
            if ((i%16)==0) kiki();

            monitor_off=1;
#endif
			unsigned int	offset,					length;
			ChunkDataHeader	header_chunk;

			offset = (65536 * header.locations[i].offset[0]) + (256 * header.locations[i].offset[1]) + header.locations[i].offset[2];
//            printf("header.locations[%d].sector_count=%d\n",i, header.locations[i].sector_count);

			if (offset != 0)
			{
                tag_index->tag_int_array.value[i]=chunk_count+1;
                chunk_count++;
				char	*chunk;
				FILE	*deflated_output_file,					*uncompressed_output_file;
				char	deflated_output_file_path[1024], 		uncompressed_output_file_path[1024];

				if (fseek(input_file, offset * 4096, SEEK_SET) == -1) {	fprintf(stderr, "FATAL ERROR: unable to seek to chunk %d in \"%s\"\n", i, argv[region]); exit(8); }
				if (fread(&header_chunk, sizeof(ChunkDataHeader), 1, input_file) != 1) { fprintf(stderr, "FATAL ERROR: unable to read chunk #%d header in \"%s\"\n", i, argv[region]); exit(9); }
				length = (16777216 * header_chunk.length[0]) + (65536 * header_chunk.length[1]) + (256 * header_chunk.length[2]) + header_chunk.length[3];

				if (length > 4096 * header.locations[i].sector_count) { fprintf(stderr, "FATAL ERROR: chunk #%d is bigger than expected (%u bytes vs %u) in \"%s\"\n", i, length, 4096 * header.locations[i].sector_count, argv[region]); exit(10); }
				if (header_chunk.compression_type != COMPRESSION_TYPE_GZIP && header_chunk.compression_type != COMPRESSION_TYPE_ZLIB) { fprintf(stderr, "FATAL ERROR: chunk #%d has unknown compression type (%u) in \"%s\"\n", i, header_chunk.compression_type, argv[region]); exit(11); }

//                printf("\nmain_mca2nbt_adapted(): i=%d  offset=%u  *4096=%u  sector_count=%u",i,offset,offset*4096,header.locations[i].sector_count);
//                printf("  length=%u  compr.type=%d   ",length, header_chunk.compression_type);

				if ((chunk = (char*) malloc(length - 1)) == NULL) { fprintf(stderr, "FATAL ERROR: unable to alloc %u bytes of memory to read chunk #%d in \"%s\"\n", length, i, argv[region]); exit(13); }
				if (fread(chunk, length - 1, 1, input_file) != 1) { fprintf(stderr, "FATAL ERROR: unable to read chunk #%d data in \"%s\"\n", i, argv[region]); free(chunk); exit(14); }

//test zlib
                if (skippy==0) {
                    if (mkdir(output_directory_name) != 0) { if (errno != EEXIST) { fprintf(stderr, "FATAL ERROR: unable to create the destination directory \"%s\"\nReason: %s\n", argv[region], sys_errlist[errno]); exit(3); } }
                    if (header_chunk.compression_type == COMPRESSION_TYPE_GZIP) {
                        sprintf(deflated_output_file_path, "%s/%d.gzip.nbt", output_directory_name, i);
                        if ((deflated_output_file = fopen(deflated_output_file_path, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing chunk #%d\n", deflated_output_file_path, i); free(chunk); exit(15); }
                        if (fwrite(chunk, length - 1, 1, deflated_output_file) != 1) { fprintf(stderr, "FATAL ERROR: unable to write chunk #%d data to file \"%s\"\n", i, deflated_output_file_path);free(chunk);exit(16);}
                        fclose(deflated_output_file);
                    } else {
                        sprintf(deflated_output_file_path, "%s/%d.zlib.nbt", output_directory_name, i);
                        if ((deflated_output_file = fopen(deflated_output_file_path, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing chunk #%d\n", deflated_output_file_path, i); free(chunk); exit(15); }
                        if (fwrite(chunk, length - 1, 1, deflated_output_file) != 1) { fprintf(stderr, "FATAL ERROR: unable to write chunk #%d data to file \"%s\"\n", i, deflated_output_file_path);free(chunk);exit(16);}
                        fclose(deflated_output_file);
                    }
                }

                tag_chunk=NULL;
                if (header_chunk.compression_type == COMPRESSION_TYPE_ZLIB) {
                    tag_chunk = read_nbt_from_memory((uint8_t*) chunk, length-1, NBT_PARSE_FLAG_USE_ZLIB);
                } else {
                    tag_chunk = read_nbt_from_memory((uint8_t*) chunk, length-1, NBT_PARSE_FLAG_USE_GZIP);
                }


//                nbt_tag_t* tag_n = nbt_new_tag_short(i);            nbt_set_tag_name(tag_n, "column",    strlen("column"));
//                nbt_tag_t* tag_x = nbt_new_tag_short(i%32);         nbt_set_tag_name(tag_x, "x",        strlen("x"));
//                nbt_tag_t* tag_z = nbt_new_tag_short((int)(i/32));  nbt_set_tag_name(tag_z, "z",        strlen("z"));
//                nbt_tag_compound_append(tag_chunk, tag_n);
//                nbt_tag_compound_append(tag_chunk, tag_x);
//                nbt_tag_compound_append(tag_chunk, tag_z);

//make shure this is the last one appended. When writing to .mca the last tag is removed...
                nbt_tag_t* tag_timestamp = nbt_new_tag_long((int64_t)header.timestamps[i].timestamp);
                nbt_set_tag_name(tag_timestamp, "timestamp" , strlen("timestamp"));
                nbt_tag_compound_append(tag_chunk,tag_timestamp);

//                tag_n=NULL;tag_x=NULL;tag_z=NULL;

//hoppa
                int regx,regz;
                sscanf(name,"r.%d.%d.mca",&regx,&regz);
                sprintf(name,"Chunk [%d, %d]   in world at (%d, %d)",i%32,(int)(i/32), regx*32+i%32, regz*32+(int)(i/32));
//                sprintf(name,"column %d",i);
                nbt_set_tag_name(tag_chunk, (char*)name, strlen(name));

                nbt_tag_compound_append(tag_region, tag_chunk);

//using gzip compr. file (with timestamp in it)
//hoppa important include when using mcaworld command....

                if (TO_DIRS==1) {
                    if (mkdir(output_directory_name) != 0) { if (errno != EEXIST) { fprintf(stderr, "FATAL ERROR: unable to create the destination directory \"%s\"\nReason: %s\n", argv[region], sys_errlist[errno]); exit(3); } }
                    sprintf(name, "%s/%d.gzip.nbt", output_directory_name, i);
                    write_nbt_file(name, tag_chunk, NBT_WRITE_FLAG_USE_GZIP);
                }

                if (skippy==0) {
                    nbt_tag_t* tag_timestamp = nbt_new_tag_long((int64_t)header.timestamps[i].timestamp);
                    nbt_set_tag_name(tag_timestamp, "timestamp" , strlen("timestamp"));
                    nbt_tag_compound_append(tag_chunk,tag_timestamp);

                    sprintf(name, "%s/%d.nbt", output_directory_name, i);
                    write_nbt_file(name, tag_chunk, NBT_WRITE_FLAG_USE_RAW);

                    sprintf(name,"%s/%d.txt",output_directory_name,i);
                    if ((file = fopen(name, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing region #%d text file\n", name, region); nbt_free_tag(tag_region); exit(15); }
                    print_nbt_tree_to_file(tag_chunk, 0, file);
                    fclose(file);
                }

/*
				if ((deflated_output_file = fopen(deflated_output_file_path, "rb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for reading deflated\n", deflated_output_file_path); exit(17); }
				sprintf(uncompressed_output_file_path, "%s/%d.nbt", output_directory_name, i);
				if ((uncompressed_output_file = fopen(uncompressed_output_file_path, "wb")) == NULL) { fclose(deflated_output_file); fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing uncompressed output\n", uncompressed_output_file_path); exit(18); }

				zpipe(deflated_output_file,uncompressed_output_file);

                fclose(deflated_output_file);
                fclose(uncompressed_output_file);
                printf(" %s\n",uncompressed_output_file_path);
*/

				free(chunk);
			} else {
                tag_index->tag_int_array.value[i]=-1;
			}
            if (!set_quiet) if ((i%64)==0) { printf("."); cnt++; }
		}
//test
//        printf("column 5 at compound position %d    ->    ", tag_index->tag_int_array.value[5] );
//        if (tag_index->tag_int_array.value[5]>0) printf("test: %s\n",tag_region->tag_compound.value[ tag_index->tag_int_array.value[5] ]->name);
//        if (tag_index->tag_int_array.value[5]>0) printf("test: %s\n",tag_region->tag_compound.value[ tag_region->tag_compound.value[0]->tag_int_array.value[5] ]->name);
//        printf("\nfirst column=%s  ",tag_region->tag_compound.value[1]->name);
//        printf("last column=%s  ",tag_region->tag_compound.value[tag_region->tag_compound.size-1]->name);
//        printf("number=%d ",tag_region->tag_compound.size);

        if (!set_quiet) while (cnt<32) { printf("."); cnt++; }
        cnt=0;
        if (!set_quiet) printf("%4d",chunk_count);
        num_chunks+=chunk_count;

//        FILE* file;

		fclose(input_file);

/*
        nbt_tag_t* tag_timestamps = nbt_new_tag_int_array((int32_t*)header.timestamps,1024);
        nbt_set_tag_name(tag_timestamps, "timestamps" , strlen("timestamps"));
        nbt_tag_compound_append(tag_region,tag_timestamps);
*/
        tag=tag_region;

	}
    if (set_display_memory) { disp_memory_usage(); }

    return tag;
}
int PUT_LOCAL=0;

char world_nbt_filename[1024];



void WRITE_WORLD_TO_MCA(char* filename) {
#ifdef SFML_ONBOARD
    fast=1;
#endif // SFML_ONBOARD
    tied=0;
    tied_total=0;
    if (!set_quiet) { PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter(); }

//    skippy=0;
    if (!set_quiet) printf("%7.3f -%7.3f ",tied_total,tied);
    int type=NBT_PARSE_FLAG_USE_RAW;
    if ((strstr(filename, ".nbt")) == NULL) { printf("Specify .nbt file\n"); }
    if ((strstr(filename, ".gzip.")) != NULL ) {
        if (!set_quiet) printf("Reading GZIP file: %s\r",filename);
        type=NBT_PARSE_FLAG_USE_GZIP;
    } else if ((strstr(filename, ".zlib.")) != NULL ) {
        if (!set_quiet) printf("Reading ZLIB file: %s\r",filename);
        type=NBT_PARSE_FLAG_USE_ZLIB;
    } else if (!set_quiet) printf("Reading RAW file: %s\r",filename);

    if (!set_quiet) { tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied; }
    if (!set_quiet) printf("%7.3f -%7.3f\r",tied_total,tied);

    strcpy(world_nbt_filename,filename);
    nbt_tag_t* tag_world=read_nbt_file(filename,type);
    if (!set_quiet) { tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied; }
    if (!set_quiet) printf("%7.3f -%7.3f\n",tied_total,tied);
    PUT_LOCAL=1;
    WRITE_WORLD(tag_world);
    PUT_LOCAL=0;
    nbt_free_tag(tag_world);
//    skippy=1;

#ifdef SFML_ONBOARD
    fast=1;
#endif // SFML_ONBOARD
}
void WRITE_REGION(char* filename);


//todo
void WRITE_ALL_REGIONS(char* worldname) {
    char dir[1024];
    char sourcedir[1024];
    char filename[1024];
    char regionname[1024];
    sprintf(dir,"%s/nbt",worldname);
//    printf(dir);

    int num_regions=0;

    tied=0;
    tied_total=0;
    if (!set_quiet) { PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter(); }

    if (!set_quiet) printf("%7.3f -%7.3f ",tied_total,tied);
    if (!set_quiet) printf("Dir: %s\n",dir);

    struct stat s;
    struct dirent *de;
    printf("TO DO: ");
    DIR *dr;
    dr=opendir(dir);
    while ((de = readdir(dr)) != NULL) {
        if ( (strstr(de->d_name, ".nbt")) != NULL  &&   (strstr(de->d_name, "r.")) != NULL ) {
//            printf("de->d_name=%s\n",de->d_name);
            sprintf(filename,"%s/%s",dir,de->d_name);
            if (!set_quiet) printf(de->d_name);
            if (!set_quiet) printf(" ");
        }
    }
    closedir(dr);
    if (!set_quiet) printf("\n");

    dr=opendir(dir);
    while ((de = readdir(dr)) != NULL && !ESCAPE_PRESSED) {
        if ( (strstr(de->d_name, ".nbt")) != NULL  &&   (strstr(de->d_name, "r.")) != NULL ) {
            sprintf(filename,"%s/%s",dir,de->d_name);
            strcpy(regionname,de->d_name);
            sprintf(sourcedir,"%s/%s",dir,de->d_name);
            WRITE_REGION(filename);
            num_regions++;
        }
    }
    closedir(dr);
    if (!set_quiet) printf("%7.3f -%7.3f Total number of region files written: %d\n",tied_total,tied,num_regions);
}

void WRITE_REGION(char* filename) {
#ifdef SFML_ONBOARD
    fast=1;
#endif // SFML_ONBOARD
    tied=0;
    tied_total=0;
    if (!set_quiet) { PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter(); }

//    skippy=0;
    ONLY_ONE_REGION=1;
    nbt_tag_t* tag_region;

    int type;
    if (!set_quiet) printf("%7.3f -%7.3f ",tied_total,tied);

    if ((strstr(filename, ".nbt")) == NULL) { printf("Specify .nbt file\n"); }

    if ((strstr(filename, ".gzip.")) != NULL ) {

        type=NBT_PARSE_FLAG_USE_GZIP;

//        if (!set_quiet) printf("Reading GZIP file to mem: %s\n",filename);
        size_t size;

        uint8_t* region_file=load_region_file(filename, &size);

        if (!set_quiet) printf("Reading GZIP file: %s\r",filename);
        tag_region=read_nbt_from_memory(region_file,size,type);
        NBT_FREE(region_file);

//        tag_region=read_nbt_file(filename, type);

    } else if ((strstr(filename, ".zlib.")) != NULL ) {

        type=NBT_PARSE_FLAG_USE_ZLIB;
        if (!set_quiet) printf("Reading ZLIB file: %s\r",filename);
        tag_region=read_nbt_file(filename, type);

    } else {

        type=NBT_PARSE_FLAG_USE_RAW;
        if (!set_quiet) printf("Reading RAW file: %s\r",filename);
        tag_region=read_nbt_file(filename, type);
    }
    if (!set_quiet) { tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied; }
    if (!set_quiet) printf("%7.3f -%7.3f\n",tied_total,tied);

    strcpy(world_nbt_filename,filename);

//    printf("Writing region file\n");
    WRITE_WORLD(tag_region);

    nbt_free_tag(tag_region);
    ONLY_ONE_REGION=0;
//    skippy=1;

#ifdef SFML_ONBOARD
    fast=1;
#endif // SFML_ONBOARD
}

int OVERRIDE_SUBDIR=0;
char OVERRIDE_SUBDIRNAME[1024];

void WRITE_WORLD(nbt_tag_t* tag_world) {
    if (tag_world==0) { printf("tag_world=0, WRITE_WORLD()\n"); return ; }
//    double tied=0;
//    double tied_total=0;
//    PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter();

    if (!ONLY_ONE_REGION) {
//        check_memory_tofile("WRITE_WORLD:");
        num_chunks=0;
    }
    skippy=1;
    shut_up=1;
    char name[1000];
    char filename[1000];
    char *m_argv[2];
    char arg1[20]="ik";
    char arg2[1000];
    m_argv[0]=arg1;
/*
#ifdef SFML_ONBOARD
    if (!(set_display_memory && set_quiet)) {
        for (int t=0; t<35; t++) {
            kiki();
            monitor_off=1;
            sf::sleep(sf::seconds(0.1));
        }
    }
#endif
*/
//    printf("World: %s\n",filename);
    char dir[1000];
    char naam[1000];
    char out[1000];
//    sprintf(out, "%s/nbt",filename);
//    if (mkdir(out) != 0) { if (errno != EEXIST) { fprintf(stderr, "FATAL ERROR: unable to create the destination directory \"%s\"\nReason: %s\n", out, sys_errlist[errno]); exit(3); } }

//    sprintf(dir, "%s/region",filename);
    strcpy(filename,tag_world->name);

    if (!ONLY_ONE_REGION) {
        sprintf(dir, "%s/nbt",filename);

        if (!set_quiet) printf("%7.3f -%7.3f ",tied_total,tied);
        if (!set_quiet) printf("Dir: %s\n",dir);
        sprintf(naam,"%s",dir);
    } else {
//        sprintf(dir, "%s",filename);
        if (OVERRIDE_SUBDIR==1) {
            sprintf(dir,"%s",OVERRIDE_SUBDIRNAME);
        }
        else
            sprintf(dir, ".");
        sprintf(naam,"%s",dir);
    }

    nbt_tag_t* tag_region;
//    nbt_tag_t* tag_world = nbt_new_tag_compound();
//    nbt_set_tag_name(tag_world, filename, strlen(filename));

    int maxlen=0;
    if (!ONLY_ONE_REGION) {
        if (!set_quiet) printf("TO DO: ");
        for (int i=0; i<tag_world->tag_compound.size; i++ ) {
            if (tag_world->tag_compound.value[i]!=0) {
                if (!set_quiet) printf(tag_world->tag_compound.value[i]->name);
                if (!set_quiet) printf(" ");
//                if (tag_world->tag_compound.value[i]->name_size>maxlen) maxlen=tag_world->tag_compound.value[i]->name_size;
            }
        }
        if (!set_quiet) printf("\n");
    } else {
//        maxlen=tag_world->name_size;
        tag_region=tag_world;
        tag_world=nbt_new_tag_compound();
        nbt_tag_compound_append(tag_world,tag_region);
    }
    maxlen=19;
   for (int i=0; i<tag_world->tag_compound.size; i++ ) {
        if (tag_world->tag_compound.value[i]!=0) {

            size_t size;
            strcpy(naam,tag_world->tag_compound.value[i]->name);
            if (!set_quiet) printf("%7.3f -%7.3f ",tied_total,0.0);
            char* p_file;
            if ((p_file=strstr(filename, ".mca")) != NULL) *p_file=0;
            if (PUT_LOCAL==1) {
                if (!set_quiet) printf("Reading: %s",world_nbt_filename);
            }
            else {
                if (!ONLY_ONE_REGION) {
                    if (!set_quiet) printf("Reading: %s/%s",dir,filename);
                    if (!set_quiet) if (strlen(naam)<maxlen) for (int p=0; p<(maxlen-strlen(naam)); p++) printf(".");
                }
                else {
                    if (!set_quiet) printf("Reading: %s",world_nbt_filename);
                }
            }
//            printf(filename);

            uint8_t* region_ram=main_nbt2mca(tag_world->tag_compound.value[i],&size);

            if (!set_quiet) printf(" Columns ");
            if (PUT_LOCAL==1) {
                sprintf(out,"%s",naam);
            }
            else {
                sprintf(out,"%s/%s",dir,naam);
            }
            FILE *file;
            if ((file = fopen(out, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing region\n", out); exit(6); }
            if (fwrite(region_ram, size, 1, file) != 1) { fprintf(stderr, "FATAL ERROR: unable to write region to file \"%s\"\n", file); exit(7); }
            fclose(file);

//            nbt_tag_t* header_tag=header_to_tag(region_ram);
            NBT_FREE(region_ram);

//            sprintf(out,"%s/%s.header.gzip.nbt",dir,naam);
//            write_nbt_file(out,header_tag,NBT_PARSE_FLAG_USE_GZIP);
//            nbt_to_textfile(header_tag, out);
//            nbt_free_tag(header_tag);

            if (!set_quiet) printf("-> Written to %s\r",out);
            if (!set_quiet) { tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied; }
            if (!set_quiet) printf("%7.3f -%7.3f\n",tied_total,tied);
        }
    }
    if (!set_quiet) { tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied; }
    if (!ONLY_ONE_REGION) if (!set_quiet) printf("%7.3f -%7.3f Total number of column files read: %d\n",tied_total,tied,num_chunks);
}


uint8_t* main_nbt2mca(nbt_tag_t* tag_region, size_t* size)
{
	if (tag_region==0) { printf("tag_region=0, main_nbt2mca()\n"); return 0;}
	int	region;
    uint8_t* pointer_to_mem;
    char name[1000];
    strcpy(name,tag_region->name);
    printf("                                          \r");printf(name);

//    printf("\ntag_region->name=%s\n",name);
	for (region = 1; region < 2; region++)
	{

		RegionFileHeader	header;
		int			i;
        size_t length;

        int chunk_count=0;
        int cnt;
        cnt=0;
        uint8_t* chunks[1024];
        ChunkDataHeader	header_chunk[1024];
        unsigned int	offset_block=0;
        unsigned int	offset;
        int32_t* index;
//        int32_t* timestamps;
        index=tag_region->tag_compound.value[0]->tag_int_array.value; // index to columns, quick & sorted

//        timestamps=tag_region->tag_compound.value[tag_region->tag_compound.size-1]->tag_int_array.value;

		for (i = 0; i < CHUNKS_PER_REGION; i++)
		{
            int32_t column_number=index[i];
            size_t size=0;
//            printf("\ni=%d  column_number=%d\n",i,column_number);
            if (column_number>0) {
                unsigned char sector_count;
                chunk_count++;

                nbt_tag_t* tag_column=tag_region->tag_compound.value[column_number];
                int MINUS_ONE=0;
                for (int x=0; x<tag_column->tag_compound.size; x++) {
                    if ( strcmp(tag_column->tag_compound.value[x]->name,"timestamp")==0 ) {
                        header.timestamps[i].timestamp=(uint32_t)tag_column->tag_compound.value[x]->tag_long.value;
                        tag_column->tag_compound.size--; // set last tag off, make shure timestamp is last tag on chunk tag.
                        MINUS_ONE=1;
                        break;
                    }
                }


//joepie

//                printf("tag_column->name=%s\n",tag_column->name);
//                NBT_FREE(tag_column->name);
//                tag_column->name_size=0;
                chunks[i]=write_nbt_to_memory(tag_column, NBT_WRITE_FLAG_USE_ZLIB, &size);
                sector_count= (unsigned char)((size-1+sizeof(ChunkDataHeader))/4096)  +1;            //beep beep

                if (MINUS_ONE==1) tag_column->tag_compound.size++; // Draw back, don't destruct tag when used laterz....

                header_chunk[i].compression_type = COMPRESSION_TYPE_ZLIB;
//                header_chunk[i].length[0] = (uint8_t)(size_t & 0xFF000000
//                header_chunk[i].length = size+1;
                header_chunk[i].length[0]= (((size+1) & 0xFF000000) >> 24) & 0xFF;   //+1, means 0=empty and size=length -1 ???
                header_chunk[i].length[1]= (((size+1) & 0x00FF0000) >> 16) & 0xFF;   // so length = size + 1 ???
                header_chunk[i].length[2]= (((size+1) & 0x0000FF00) >>  8) & 0xFF;
                header_chunk[i].length[3]= (((size+1) & 0x000000FF)      ) & 0xFF;
                header.locations[i].offset[0]=(((2 + offset_block) & 0x00FF0000) >> 16) & 0xFF;
                header.locations[i].offset[1]=(((2 + offset_block) & 0x0000FF00) >> 8) & 0xFF;
                header.locations[i].offset[2]=(2 + offset_block) & 0xFF;
                header.locations[i].sector_count=sector_count;
//                header.timestamps[i].timestamp=timestamps[i];

                length = (16777216 * header_chunk[i].length[0]) + (65536 * header_chunk[i].length[1]) + (256 * header_chunk[i].length[2]) + header_chunk[i].length[3];
                offset = (65536 * header.locations[i].offset[0]) + (256 * header.locations[i].offset[1]) + header.locations[i].offset[2];

                offset_block+=sector_count;

            } else {
                header_chunk[i].length[0]=0;
                header_chunk[i].length[1]=0;
                header_chunk[i].length[2]=0;
                header_chunk[i].length[3]=0;
                header.locations[i].offset[0]=0;
                header.locations[i].offset[1]=0;
                header.locations[i].offset[2]=0;
                header.locations[i].sector_count=0;
                header.timestamps[i].timestamp=0;
                header_chunk[i].compression_type = 0;
                length = (16777216 * header_chunk[i].length[0]) + (65536 * header_chunk[i].length[1]) + (256 * header_chunk[i].length[2]) + header_chunk[i].length[3];
                offset = (65536 * header.locations[i].offset[0]) + (256 * header.locations[i].offset[1]) + header.locations[i].offset[2];
            }
//            printf("i=%4d  size=%llu  lenght=%llu  offset_block=%u  offset=%u\n" , i , size , length , offset_block+2, offset );

//            if (!set_quiet) if ((i%64)==0) { printf("."); cnt++; }
            if (!set_quiet) if ((i%128)==0) { printf("."); cnt++; }

		} // i

        pointer_to_mem=(uint8_t*) NBT_MALLOC(sizeof(RegionFileHeader) + (offset_block)*4096);

//        printf("malloc=%u\n",sizeof(RegionFileHeader) + offset_block*4096);

        NBT_MEMCPY(pointer_to_mem , &header, sizeof(RegionFileHeader));
        *size=sizeof(header);

		for (i = 0; i < CHUNKS_PER_REGION; i++)
		{
			offset = (65536 * header.locations[i].offset[0]) + (256 * header.locations[i].offset[1]) + header.locations[i].offset[2];
            length = (16777216 * header_chunk[i].length[0]) + (65536 * header_chunk[i].length[1]) + (256 * header_chunk[i].length[2]) + header_chunk[i].length[3];
            if (offset+length>(offset_block+2)*4096) {
                printf("error: offset+length>offset_block*4096\n");
                printf("error: offset+length=%d\n",offset+length);
                printf("error: offset_block*4096=%d\n",offset_block*4096);
            }
            if (offset!=0) {
//                if (mkdir(output_directory_name) != 0) { if (errno != EEXIST) { fprintf(stderr, "FATAL ERROR: unable to create the destination directory \"%s\"\nReason: %s\n", argv[region], sys_errlist[errno]); exit(3); } }
                NBT_MEMCPY(pointer_to_mem+offset*4096 , &header_chunk[i] , sizeof(ChunkDataHeader) );
                NBT_MEMCPY(pointer_to_mem+offset*4096 + sizeof(ChunkDataHeader) , chunks[i] , length  );
                NBT_FREE(chunks[i]);
                *size=offset*4096 + ((int)((sizeof(ChunkDataHeader) + length)/4096) + 1)*4096;      // -1 +1 get nuts!!!
//                *size=offset*4096 +sizeof(ChunkDataHeader) + length ;      // -1 +1 get nuts!!!
            }
//            printf("i=%4d  size=%u   lenght=%llu  offset=%u  *4096=%d  size-offset*4096=%d\n" , i , *size,  length , offset, offset*4096, *size-offset*4096);
            if (!set_quiet) if ((i%128)==0) { printf("."); cnt++; }
//            NBT_FREE(chunks[i]);
		}
//        printf("i=%4d  size=%u   lenght=%llu  offset=%u  *4096=%d  size-offset*4096=%d\n" , i , *size,  length , offset, offset*4096, *size-offset*4096);
//        printf("malloc=%u\n",sizeof(RegionFileHeader) + offset_block*4096);

        if (!set_quiet) while (cnt<32) { printf("."); cnt++; }
        cnt=0;
        if (!set_quiet) printf("%4d",chunk_count);
        num_chunks+=chunk_count;
	}

//		res=fread(&header, sizeof(RegionFileHeader), 1, input_file);
    if (set_display_memory)  { disp_memory_usage(); }

    return pointer_to_mem;
}


nbt_tag_t* GET_REGION(nbt_tag_t* WORLD, int X, int Z) {
//    static char world_name[100];
//    strcpy(world_name,WORLD->name);
    nbt_tag_t** world_compound=WORLD->tag_compound.value;
    size_t world_size=WORLD->tag_compound.size;
    if (world_size>0) {
        for (int r=0; r<world_size; r++) {
            static char region_name[100];
            sprintf(region_name,"r.%d.%d.mca",X,Z);
            if ( strcmp(region_name,world_compound[r]->name) == 0 ) return world_compound[r];
        }
    }
    return 0;
}

nbt_tag_t* GET_COLUMN(nbt_tag_t* REGION, int X, int Z) {
    nbt_tag_t** region_compound=REGION->tag_compound.value;
    size_t region_size=REGION->tag_compound.size;
    nbt_tag_t* tag_index=region_compound[0];
    int32_t i=tag_index->tag_int_array.value[X+32*Z];
//    if (i>0) printf("name=%s\n",region_compound[i]->name);
    if (i>0)
        return region_compound[i];
    else
        return 0;
}

nbt_tag_t* GET_COLUMN(nbt_tag_t* REGION, int XxZ) {
    nbt_tag_t** region_compound=REGION->tag_compound.value;
    size_t region_size=REGION->tag_compound.size;
    nbt_tag_t* tag_index=region_compound[0];
    int32_t i=tag_index->tag_int_array.value[XxZ];
//    if (i>0) printf("name=%s\n",region_compound[i]->name);
    if (i>0)
        return region_compound[i];
    else
        return 0;
}

void nbt_to_textfile(nbt_tag_t* tag, char* filename) {
    FILE* file;
    if ((file = fopen(filename, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing world text file\n", filename); }
    print_nbt_tree_to_file(tag, 0, file);
    fclose(file);
}


void region_header(char* filename) {
//    printf("region_header(): load_region_file(\"%s\")\n",filename);
    size_t size;
    uint8_t* region_memory=load_region_file(filename, &size);
//    printf("region_header(): header_memory=%u\n",header_memory);
    if (region_memory!=0) {

//        printf("region_header(): header_to_tag(%u)\n",header_memory);
        nbt_tag_t* nbt_tag_header=header_to_tag(region_memory);

//        printf("region_header(): nbt_tag_header=%u\n",nbt_tag_header);
//        printf("region_header(): NBT_FREE(%u)\n",header_memory);
        NBT_FREE(region_memory);
        if (nbt_tag_header!=0) {
            char out[1000];
            sprintf(out,"%s.header.gzip.nbt",filename);
//            printf("region_header(): write_nbt_file(\"%s\",nbt_tag_header,NBT_PARSE_FLAG_USE_GZIP)\n",out,header_memory);
            write_nbt_file(out,nbt_tag_header,NBT_PARSE_FLAG_USE_GZIP);
            sprintf(out,"%s.header.txt",filename);
//            printf("region_header(): nbt_to_textfile(nbt_tag_header,\"%s\")\n",out);
            nbt_to_textfile(nbt_tag_header,out);
            nbt_free_tag(nbt_tag_header);
        }
    }
}


uint8_t* load_region_file(char* filename, size_t* size) {
    struct stat filestatus;
    stat(filename, &filestatus );
    size_t file_size=filestatus.st_size;
    *size=file_size;
    FILE* file=fopen(filename,"rb");
    uint8_t* pointer_to_mem;
    if (filename!=NULL) {
        pointer_to_mem=(uint8_t*) NBT_MALLOC(file_size);
        if (fread(pointer_to_mem, file_size, 1, file) != 1) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for reading\n", filename);return 0; }
        fclose(file);
        return pointer_to_mem;
    } else { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for reading\n", filename); return 0;}
}

nbt_tag_t* header_to_tag(uint8_t* regionfile) {
//    printf("header_to_tag(%u)\n", regionfile);
    if (regionfile==0) return 0;
    RegionFileHeader* region_header=(RegionFileHeader*) regionfile;
    int	i;

//    printf("header_to_tag(): 1\n");

    nbt_tag_t* tag_region = nbt_new_tag_compound();
    nbt_set_tag_name(tag_region, (char*)"region", strlen("region"));

//    printf("header_to_tag(): 2\n");

    nbt_tag_t* tag_locations = nbt_new_tag_byte_array((int8_t*)region_header->locations,4096);
    nbt_set_tag_name(tag_locations, "locations" , strlen("locations"));
    nbt_tag_compound_append(tag_region,tag_locations);

//    printf("header_to_tag(): 3\n");

    nbt_tag_t* tag_timestamps = nbt_new_tag_byte_array((int8_t*)region_header->timestamps,4096);
    nbt_set_tag_name(tag_timestamps, "timestamps" , strlen("timestamps"));
    nbt_tag_compound_append(tag_region,tag_timestamps);

//    printf("header_to_tag(): 4\n");

    for (i = 0; i < CHUNKS_PER_REGION; i++)
    {
//        printf("header_to_tag(): i=%d\n",i);

        nbt_tag_t* tag_column = nbt_new_tag_compound();
        char column_name[20];
        sprintf(column_name,"column %4d",i);
        nbt_set_tag_name(tag_column, column_name , strlen(column_name));
        nbt_tag_compound_append(tag_region,tag_column);

//        printf("header_to_tag(): 6\n");

        nbt_tag_t* tag_offset = nbt_new_tag_byte_array((int8_t*) (region_header->locations[i].offset),3);
        nbt_set_tag_name(tag_offset, "offset" , strlen("offset"));
        nbt_tag_compound_append(tag_column,tag_offset);

//        printf("header_to_tag(): 7\n");

        nbt_tag_t* tag_sector_count = nbt_new_tag_byte(region_header->locations[i].sector_count);
        nbt_set_tag_name(tag_sector_count, "sector count" , strlen("sector count"));
        nbt_tag_compound_append(tag_column,tag_sector_count);

//        printf("header_to_tag(): 8\n");

        nbt_tag_t* tag_timestamp = nbt_new_tag_long((int64_t)region_header->timestamps[i].timestamp);
        nbt_set_tag_name(tag_timestamp, "timestamp" , strlen("timestamp"));
        nbt_tag_compound_append(tag_column,tag_timestamp);

//        printf("header_to_tag(): 9\n");

        unsigned int offset = (65536 * (uint8_t)(region_header->locations[i].offset[0]))
                            + (256   * (uint8_t)(region_header->locations[i].offset[1]))
                            +          (uint8_t)(region_header->locations[i].offset[2]);
        unsigned char sector_count=(uint8_t)region_header->locations[i].sector_count;


//        printf("header_to_tag(): 10\n");

        nbt_tag_t* tag_offset2 = nbt_new_tag_int(offset);
        nbt_set_tag_name(tag_offset2, "offset" , strlen("offset"));
        nbt_tag_compound_append(tag_column,tag_offset2);

//        printf("header_to_tag(): 11\n");

        if (offset!=0) {
            ChunkDataHeader* chunk_header=(ChunkDataHeader*) (regionfile+4096*offset);

            unsigned int length = (16777216 * (uint8_t)chunk_header->length[0]) + (65536 * (uint8_t)chunk_header->length[1]) + (256 *(uint8_t)chunk_header->length[2]) + chunk_header->length[3];

            if (length > 4096 * sector_count) { fprintf(stderr, "\n\nFATAL ERROR: chunk #%d is bigger than expected (%u bytes vs %u)\n", i, length, 4096 * sector_count); }

            unsigned char compression_type=chunk_header->compression_type;

//            printf("\nheader_to_tag(): i=%d  offset=%u  *4096=%u  sector_count=%u",i,offset,offset*4096,sector_count);
//            printf("  length=%u  compr.type=%d   ",length,compression_type);


//            printf("header_to_tag(): 12\n");

            nbt_tag_t* tag_length = nbt_new_tag_byte_array((int8_t*)chunk_header->length,4);
            nbt_set_tag_name(tag_length, "length" , strlen("length"));
            nbt_tag_compound_append(tag_column,tag_length);

//            printf("13 ");

            nbt_tag_t* tag_length2 = nbt_new_tag_int(length);
            nbt_set_tag_name(tag_length2, "length2" , strlen("length2"));
            nbt_tag_compound_append(tag_column,tag_length2);

//            printf("14 ");

            nbt_tag_t* tag_compression_type = nbt_new_tag_byte(chunk_header->compression_type);
            nbt_set_tag_name(tag_compression_type, "compression type" , strlen("compression type"));
            nbt_tag_compound_append(tag_column,tag_compression_type);

//            printf("15 ");

            nbt_tag_t* tag_binary = nbt_new_tag_byte_array((int8_t*)chunk_header+sizeof(ChunkDataHeader),length); //hoppa
            nbt_set_tag_name(tag_binary, "binary" , strlen("binary"));
            nbt_tag_compound_append(tag_column,tag_binary);

            nbt_tag_t* tag_nbt;

//            printf("16 \n");

            if (compression_type == COMPRESSION_TYPE_ZLIB) {
//                printf("header_to_tag(): 17\n");
                tag_nbt = read_nbt_from_memory((uint8_t*)chunk_header+sizeof(ChunkDataHeader), length, NBT_PARSE_FLAG_USE_ZLIB);  //hoppa
            } else if (compression_type == COMPRESSION_TYPE_GZIP) {
//                printf("header_to_tag(): 18\n");
                tag_nbt = read_nbt_from_memory((uint8_t*)chunk_header+sizeof(ChunkDataHeader), length, NBT_PARSE_FLAG_USE_GZIP);
            } else {
                printf("Unknown compression type\n");
            }

//            printf("header_to_tag(): 19\n");

            nbt_set_tag_name(tag_nbt, "nbt" , strlen("nbt"));
            nbt_tag_compound_append(tag_column,tag_nbt);
        }
//        printf("header_to_tag(): 20\n");
    }
    return tag_region;
}

void MAKE_MCA_FROM_WORLD_NBT_GZIPS(char* worldname) {
    char dir[1024];
    char sourcedir[1024];
    char filename[1024];
    char regionname[1024];
    sprintf(dir,"%s/nbt",worldname);
//    printf(dir);

    num_chunks=0;

    tied=0;
    tied_total=0;
    if (!set_quiet) { PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter(); }

    if (!set_quiet) printf("%7.3f -%7.3f ",tied_total,tied);
    if (!set_quiet) printf("Dir: %s\n",dir);

    struct stat s;
    struct dirent *de;
    printf("TO DO: ");
    DIR *dr;
    dr=opendir(dir);
    while ((de = readdir(dr)) != NULL) {
        if ((strstr(de->d_name, "r.")) != NULL) {
//            printf("de->d_name=%s\n",de->d_name);
            sprintf(filename,"%s/%s",dir,de->d_name);
            if( stat(filename,&s) == 0 ) {
                if( s.st_mode & S_IFDIR )  { // if( s.st_mode & S_IFREG  for file....
                    if (!set_quiet) printf(de->d_name);
                    if (!set_quiet) printf(" ");
                }
            }
        }
    }
    closedir(dr);
    if (!set_quiet) printf("\n");

    dr=opendir(dir);
    while ((de = readdir(dr)) != NULL) {
        if ((strstr(de->d_name, "r.")) != NULL) {
            sprintf(filename,"%s/%s",dir,de->d_name);
            if( stat(filename,&s) == 0 ) {
                if( s.st_mode & S_IFDIR )  { // if( s.st_mode & S_IFREG  for file....
                    strcpy(regionname,de->d_name);
                    sprintf(sourcedir,"%s/%s",dir,de->d_name);


                    sprintf(filename,"%s.mca",regionname);
                    nbt_tag_t* tag_region=nbt_new_tag_compound();
                    nbt_set_tag_name(tag_region,filename,strlen(filename));

                    static int32_t index[1024];
                    nbt_tag_t* tag_index = nbt_new_tag_int_array(index,1024);
                    nbt_set_tag_name(tag_index,(char*)"index",strlen("index"));
                    nbt_tag_compound_append(tag_region,tag_index);
                    int chunk_count=0;
                    for (int t=0; t<1024; t++)
                    {
                        sprintf(filename,"%s/%d.gzip.nbt",sourcedir,t);
                        if (stat(filename,&s)==0)
                        {
                            tag_index->tag_int_array.value[t]=chunk_count+1;
                            chunk_count++;
                            nbt_tag_t* tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_GZIP);
                            nbt_tag_compound_append(tag_region,tag);
                        }
                    }

                    ONLY_ONE_REGION=1;
                    OVERRIDE_SUBDIR=1;
                    sprintf(OVERRIDE_SUBDIRNAME,"%s",dir);

                    WRITE_WORLD(tag_region);
                    OVERRIDE_SUBDIR=0;
                    ONLY_ONE_REGION=0;

                    nbt_free_tag(tag_region);
                }
            }
        }
    }
    closedir(dr);
    if (!set_quiet) printf("%7.3f -%7.3f Total number of columns written: %d\n",tied_total,tied,num_chunks);
}

