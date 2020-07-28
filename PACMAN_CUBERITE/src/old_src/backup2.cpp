#undef UNICODE
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

#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#define NBT_IMPLEMENTATION
//#define NBT_OWN_ZLIB
#include "nbt.hpp"
//#define NBT_BUFFER_SIZE 100000
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
using namespace std;
extern void kiki();
extern int monitor_off;


SYSTEMTIME stime;
LARGE_INTEGER sys_freq;

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
    static int kcount=0;
    kcount++;
    if (kcount>10000) {
        kiki();
        monitor_off=1;
        kcount=0;
    }
  return fread(data, 1, size, (FILE*)userdata);
}

static size_t writer_write(void* userdata, uint8_t* data, size_t size) {
    static int kcount=0;
    kcount++;
    if (kcount>10000) {
        kiki();
        monitor_off=1;
        kcount=0;
    }
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
    static int kcount=0;
    kcount++;
    if (kcount>100) {
        kiki();
        monitor_off=1;
        kcount=0;
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
            for (size_t i = 0; i < tag->tag_byte_array.size; i++) fprintf(file," %hhd", tag->tag_byte_array.value[i]-1); fprintf(file,"\r\n");

            break; }
        case NBT_TYPE_INT_ARRAY: {
            fprintf(file,"[int array](%d) \"%s\"",tag->tag_int_array.size,tag->name);
            for (size_t i = 0; i < tag->tag_int_array.size; i++) fprintf(file," %d", tag->tag_int_array.value[i]-1); fprintf(file,"\r\n");
            break; }
        case NBT_TYPE_LONG_ARRAY: {
            fprintf(file,"[long array](%d) \"%s\"",tag->tag_long_array.size,tag->name);
            for (size_t i = 0; i < tag->tag_long_array.size; i++) fprintf(file," %lld", tag->tag_long_array.value[i]-1); fprintf(file,"\r\n");
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
    kcount++;
    if (kcount>10000) {
        kiki();
        monitor_off=1;
        kcount=0;
    }
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
//    printf("Here 1\n");
    static size_t total_size[100];
    static size_t current_position[100];
    static int kcount=0;
//    printf("Here 2\n");
    kcount++;
    if (kcount>10000) {
        kiki();
        monitor_off=1;
        kcount=0;
    }
    if (data==NULL) {
//        printf("Here 3\n");
        if (size==1) {
            total_size[(size_t) userdata]=NBT_BUFFER_SIZE;
            intern[(size_t) userdata]=NULL;                              /* in case not freed, pointer to previous address invallid, maybe in use.....so, new memory allocated, old not changed... */
            intern[(size_t) userdata] = (uint8_t*)NBT_MALLOC(total_size[(size_t) userdata]);
            current_position[(size_t) userdata]=0;
//            printf("Here 4\n");
            return 0;
        } else {
            intern[(size_t) userdata] = (uint8_t*)NBT_REALLOC(intern[(size_t) userdata], current_position[(size_t) userdata]);  /* adjust to real size... */
//            printf("Here 5\n");
            return(current_position[(size_t) userdata]);
        }
    }
//    printf("Here 6\n");
    if (size==0) return 0;
//    printf("Here 7\n");

    if (current_position[(size_t) userdata]+size>=total_size[(size_t) userdata]) {
//        printf("Here 8\n");
        total_size[(size_t) userdata]*=2;
        intern[(size_t) userdata] = (uint8_t*)NBT_REALLOC(intern[(size_t) userdata], total_size[(size_t) userdata]);
//        printf("Here 9\n");
    }
//    printf("Here 10\n");
    NBT_MEMCPY(intern[(size_t) userdata]+current_position[(size_t) userdata],data,size);
//    printf("Here 11\n");
    current_position[(size_t) userdata]+=size;
//    printf("Here 12\n");
    return size;
}

//location=write_nbt_to_memory(tag_in, NBT_PARSE_FLAG_USE_RAW, &length);

uint8_t* write_nbt_to_memory(nbt_tag_t* tag, int flags, uint8_t* size)
{
//    printf("hi");
    uint8_t* location=NULL;
    static uint8_t* depth=NULL;
    depth++;

//    printf("write_nbt_to_memory, depth=%lld\n",depth);

    nbt_writer_t writer;

    writer.write = writer_write_to_memory;
    location=depth;
    writer.userdata = location;

    /* init */
//    printf("Calling writer_write_to_memory, init\n");
    writer_write_to_memory(depth, NULL, 1);
//    printf("Here\n");
//    printf("intern[%lld]=%lld\n",depth, intern[(size_t)depth]);

//    printf("Calling nbt_write\n");
    nbt_write(writer, tag, flags);
//    printf("Back from nbt_write\n");
//    printf("intern[%lld]=%lld\n",(size_t)depth, intern[(size_t)depth]);

//    printf("Calling writer_write_to_memory, getting size\n");
    *size=writer_write_to_memory(depth,NULL,2);
//    printf("Called writer_write_to_memory, getting size=%lld\n",size);

    depth--;
    return (intern[(size_t)depth+1]); /* NBT_FREE returned pointer after use.... */
}

void test_write_to_and_read_from_memory() {

    uint8_t* location=NULL;

    uint8_t length=0;


    for (int t=0; t<30; t++) {
        kiki();
        monitor_off=1;
        sf::sleep(sf::seconds(0.1));
    }

//    printf("Reading file r.0.0/0.nbt\n");
    nbt_tag_t* tag_in = read_nbt_file("r.0.0/0.nbt", NBT_PARSE_FLAG_USE_RAW);
//    printf("Read    file r.0.0/0.nbt\n");

//    printf("Writing r.0.0/Original 0.nbt\n");
    write_nbt_file("r.0.0/Original 0.nbt", tag_in, NBT_PARSE_FLAG_USE_RAW);
//    printf("Written r.0.0/Original 0.nbt\n");
//    printf("\n");




//    printf("Writing to memory.....\n");
    location=write_nbt_to_memory(tag_in, NBT_PARSE_FLAG_USE_RAW, &length);
//    printf("Written to memory....., length=%lld\n",&length);
//    printf("\n");

//    printf("Reading back from memory.....\n");
    nbt_tag_t* tag_back = read_nbt_from_memory((uint8_t*) location, length, NBT_PARSE_FLAG_USE_RAW);
//    printf("Read    back from memory.....\n");
//    printf("\n");




//    printf("Writing r.0.0/Copy to and from mem of 0.nbt\n");
    write_nbt_file("r.0.0/Copy to and from mem of 0.nbt", tag_back, NBT_PARSE_FLAG_USE_RAW);
//    printf("Written r.0.0/Copy to and from mem of 0.nbt\n");
//    printf("\n");

//    printf("Freeing tag_in\n");
    nbt_free_tag(tag_in);
//    printf("No Problemo\n");
//    printf("Freeing tag_back\n");
    nbt_free_tag(tag_back);
//    printf("No Problemo\n");
//    printf("Freeing memory\n");
    NBT_FREE(location);
//    printf("No Problemo\n");
//    printf("Laterz....\n");
}

int main_nbt_one(char* filename_in, char* out_file, int nbt_type);

int main_nbt()
{

    for (int t=0; t<30; t++) {
        kiki();
        monitor_off=1;
        sf::sleep(sf::seconds(0.1));
    }

/*
    if (mkdir("r.0.0.test_raw") != 0) {
        if (errno != EEXIST) {
            fprintf(stderr, "FATAL ERROR: unable to create the destination directory r.0.0.test_raw Reason: %s\n",  sys_errlist[errno]);
            exit(3);
        }
    }
*/

    if (mkdir("r.0.0.test_zlib") != 0) {
        if (errno != EEXIST) {
            fprintf(stderr, "FATAL ERROR: unable to create the destination directory r.0.0.test_zlib Reason: %s\n",  sys_errlist[errno]);
            exit(3);
        }
    }

     struct stat stat_buffer;

//    printf("****************************************************************************************************************************\n");
//    printf("Testing raw from r.0.0/#.nbt\n");
/*

     for (int t=0; t<1024; t++)
    {
        kiki();
        monitor_off=1;

        char filename[100];

        sprintf(filename,"r.0.0/%d.nbt",t);
        if (stat(filename,&stat_buffer)==0)
        {
            nbt_tag_t* tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_RAW);

            printf("%d %s",t,filename);
            sprintf(filename,"r.0.0/%d.txt",t);
            FILE *textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }

            sprintf(filename,"r.0.0.test_raw/%d.nbt",t);
            write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_RAW);
            printf(" %s",filename);

            sprintf(filename,"r.0.0.test_raw/%d.gzip.nbt",t);
            write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_GZIP);
            printf(" %s",filename);

            sprintf(filename,"r.0.0.test_raw/%d.zlib.nbt",t);
            write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_ZLIB);
            printf(" %s",filename);
            nbt_free_tag(tag);

            sprintf(filename,"r.0.0.test_raw/%d.nbt",t);
            tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_RAW);
            sprintf(filename,"r.0.0.test_raw/%d.txt",t);
            textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }
            nbt_free_tag(tag);

            sprintf(filename,"r.0.0.test_raw/%d.gzip.nbt",t);
            tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_GZIP);
            sprintf(filename,"r.0.0.test_raw/%d.gzip.txt",t);
            textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }
            nbt_free_tag(tag);

            sprintf(filename,"r.0.0.test_raw/%d.zlib.nbt",t);
            tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_ZLIB);
            sprintf(filename,"r.0.0.test_raw/%d.zlib.txt",t);
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



//            print_nbt_tree(tag, 2);
        }
    }
*/

//  printf("****************************************************************************************************************************\n");
     printf("Testing zlib from r.0.0/#.zlib.nbt\n");

     for (int t=0; t<1024; t++)
    {
        kiki();
        monitor_off=1;

        char filename[100];

        sprintf(filename,"r.0.0/%d.zlib.nbt",t);
        if (stat(filename,&stat_buffer)==0)
        {
            nbt_tag_t* tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_ZLIB);

            printf("%d %s",t,filename);

            sprintf(filename,"r.0.0/%d.zlib.txt",t);
            FILE *textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }

            sprintf(filename,"r.0.0.test_zlib/%d.nbt",t);
            write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_RAW);
            printf(" %s",filename);

            sprintf(filename,"r.0.0.test_zlib/%d.gzip.nbt",t);
            write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_GZIP);
            printf(" %s",filename);

            sprintf(filename,"r.0.0.test_zlib/%d.zlib.nbt",t);
            write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_ZLIB);
            printf(" %s",filename);
            nbt_free_tag(tag);

            sprintf(filename,"r.0.0.test_zlib/%d.nbt",t);
            tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_RAW);
            sprintf(filename,"r.0.0.test_zlib/%d.txt",t);
            textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }
            nbt_free_tag(tag);

            sprintf(filename,"r.0.0.test_zlib/%d.gzip.nbt",t);
            tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_GZIP);
            sprintf(filename,"r.0.0.test_zlib/%d.gzip.txt",t);
            textfile=fopen(filename,"wb");
            if (!textfile==NULL) {
                print_nbt_tree_to_file(tag, 0, textfile);
                fclose(textfile);
                printf(" %s",filename);
            } else {
                printf("ERROR: %s",filename);
            }
            nbt_free_tag(tag);

            sprintf(filename,"r.0.0.test_zlib/%d.zlib.nbt",t);
            tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_ZLIB);
            sprintf(filename,"r.0.0.test_zlib/%d.zlib.txt",t);
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
//            print_nbt_tree(tag, 2);
        }
    }

//  nbt_tag_t* tag = read_nbt_file("r.0.0/0.nbt", NBT_PARSE_FLAG_USE_RAW);
//  nbt_tag_t* tag = read_nbt_file("r.0.0/0.nbt.zlib", NBT_PARSE_FLAG_USE_ZLIB);
//  nbt_tag_t* tag = read_nbt_file("r.0.0/0.nbt", NBT_PARSE_FLAG_USE_RAW);


//  main_nbt();

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











/*
extern "C" {
	#include <stdio.h>
}

extern "C" FILE* fmemopen(void*, size_t, const char*);

extern "C" void app_main()
{
    auto f = fmemopen(nullptr, 32, "w");
	fclose(f);
}
*/
#include <dirent.h>



nbt_tag_t* main_mca2nbt(int argc, char *argv[]);

int skippy=1;

void do_one() {
    skippy=0;
    char *m_argv[2];
    char arg1[20]="ik";
    char arg2[20]="r.0.0.mca";
    m_argv[0]=arg1;
    m_argv[1]=arg2;
    nbt_free_tag(main_mca2nbt(2,m_argv));
    main_nbt();
    skippy=1;
}
int num_chunks=0;
void do_world(char* filename) {
    num_chunks=0;
    skippy=1;
    char name[1000];
    char *m_argv[2];
    char arg1[20]="ik";
    char arg2[1000];
    m_argv[0]=arg1;

    for (int t=0; t<35; t++) {
        kiki();
        monitor_off=1;
        sf::sleep(sf::seconds(0.1));
    }

    printf("World: %s\n",filename);
    char dir[1000];
    char naam[1000];
    sprintf(dir, "%s/region",filename);
    printf("Dir: %s\n",dir);
    sprintf(naam,"%s",dir);
    DIR *dr = opendir(naam);

    nbt_tag_t* tag_region;
    nbt_tag_t* tag_world = nbt_new_tag_compound();
    nbt_set_tag_name(tag_world, filename, strlen(filename));

    double tied=0;
    double tied_total=0;
    PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter();
    StartCounter();

    struct dirent *de;
    while ((de = readdir(dr)) != NULL) {
        if ((strstr(de->d_name, ".mca")) != NULL) {
            printf(de->d_name);
            printf(" ");
        }
    }
    printf("\n");
    closedir(dr);
    dr = opendir(naam);
    while ((de = readdir(dr)) != NULL) {
        if ((strstr(de->d_name, ".mca")) != NULL) {
            sprintf(arg2,"%s/%s",dir,de->d_name);
            m_argv[1]=arg2;
//            printf("Region: %s\n",m_argv[1]);
            tag_region=main_mca2nbt(2,m_argv);
            nbt_tag_compound_append(tag_world, tag_region);
        } else {
            sprintf(arg2,"Skipping: %s\n",de->d_name);
        }
    }
    closedir(dr);

    printf("\n");
    FILE* file;
    tied=GetCounterNanoseconds();
    printf("Total: %9.3f chunks read: %d\r\n",tied,num_chunks);
    PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter();

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

    nbt_free_tag(tag_world);

    tied=GetCounterNanoseconds(); StartCounter(); tied_total=tied_total+tied;
    printf("Total: %9.3f Time: %9.6f file tag_world freed\r\n",tied_total,tied);
}

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
		if ((header_output_file = fopen(header_output_file_path, "w")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing header\n", header_output_file_path); exit(6); }
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
        static double tied=0;
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
            kiki();
            monitor_off=1;
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
				else if (header_chunk.compression_type == COMPRESSION_TYPE_GZIP) { fprintf(stderr, "FATAL ERROR: chunk #%d is compressed with gzip, that this program doesn't support, in \"%s\"\n", i, argv[region]); exit(12); }

				/* read the rest of the chunk */
				/******************************/
				if ((chunk = (char*) malloc(length - 1)) == NULL) { fprintf(stderr, "FATAL ERROR: unable to alloc %u bytes of memory to read chunk #%d in \"%s\"\n", length, i, argv[region]); exit(13); }
				if (fread(chunk, length - 1, 1, input_file) != 1) { fprintf(stderr, "FATAL ERROR: unable to read chunk #%d data in \"%s\"\n", i, argv[region]); free(chunk); exit(14); }

//				/* write the chunk as an individual deflated NBT file */
//				/******************************************************/

                if (skippy==0) {
                    sprintf(deflated_output_file_path, "%s/%d.zlib.nbt", output_directory_name, i);
                    if ((deflated_output_file = fopen(deflated_output_file_path, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing chunk #%d\n", deflated_output_file_path, i); free(chunk); exit(15); }
                    if (fwrite(chunk, length - 1, 1, deflated_output_file) != 1) { fprintf(stderr, "FATAL ERROR: unable to write chunk #%d data to file \"%s\"\n", i, deflated_output_file_path);free(chunk);exit(16);}
                    fclose(deflated_output_file);
                }

                //bling bling

                tag_chunk=NULL;
                tag_chunk = read_nbt_from_memory((uint8_t*) chunk, length-1, NBT_PARSE_FLAG_USE_ZLIB);

                nbt_tag_t* tag_n = nbt_new_tag_short(i);            nbt_set_tag_name(tag_n, "chunk",    strlen("chunk"));
                nbt_tag_t* tag_x = nbt_new_tag_short(i%32);         nbt_set_tag_name(tag_x, "x",        strlen("x"));
                nbt_tag_t* tag_z = nbt_new_tag_short((int)(i/32));  nbt_set_tag_name(tag_z, "z",        strlen("z"));
                nbt_tag_compound_append(tag_chunk, tag_n);
                nbt_tag_compound_append(tag_chunk, tag_x);
                nbt_tag_compound_append(tag_chunk, tag_z);
                tag_n=NULL;tag_x=NULL;tag_z=NULL;

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

