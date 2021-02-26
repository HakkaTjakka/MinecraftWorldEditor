#ifndef NBT_DEFS_HPP
#define NBT_DEFS_HPP

#define NBT_IMPLEMENTATION

#ifndef NBT_H
#define NBT_H

#define LIBNBT_VERSION 10
#define LIBNBT_NBT_VERSION 19133

#include <stddef.h>
#include <sys/stat.h>

#ifndef NBT_NO_STDLIB
#include <stdlib.h>
#include <string.h>

void* my_xmalloc(size_t size);
void* my_xrealloc(void* pointer,size_t size);
void my_xfree(void* pointer);

#ifdef XALLOC

extern size_t CNT_XMALLOC;
extern size_t CNT_XREALLOC;
extern size_t CNT_XFREE;

#define NBT_MALLOC xmalloc
#define NBT_REALLOC xrealloc
#define NBT_FREE xfree
#else
#define NBT_MALLOC malloc
#define NBT_REALLOC realloc
#define NBT_FREE free
#endif // XALLOC

#define NBT_MEMCPY memcpy
#endif


#ifndef NBT_NO_STDINT
#include <stdint.h>
#endif

#define NBT_OWN_ZLIB

//rotzak
//#define __x86_64__

#ifdef NBT_OWN_ZLIB
#include "zlib.h"
#else
#include "miniz.h"
#endif

#ifndef Z_DEFAULT_WINDOW_BITS
#define Z_DEFAULT_WINDOW_BITS 15
#endif

//rotzak
#ifndef NBT_BUFFER_SIZE
#define NBT_BUFFER_SIZE 32768
//#define NBT_BUFFER_SIZE 1048576
#endif

#define NBT_COMPRESSION_LEVEL 2



typedef enum
{
    NBT_TYPE_END,
    NBT_TYPE_BYTE,
    NBT_TYPE_SHORT,
    NBT_TYPE_INT,
    NBT_TYPE_LONG,
    NBT_TYPE_FLOAT,
    NBT_TYPE_DOUBLE,
    NBT_TYPE_BYTE_ARRAY,
    NBT_TYPE_STRING,
    NBT_TYPE_LIST,
    NBT_TYPE_COMPOUND,
    NBT_TYPE_INT_ARRAY,
    NBT_TYPE_LONG_ARRAY,
    NBT_NO_OVERRIDE, // Only used internally.
    NBT_TYPE_FLOAT_ARRAY,
    NBT_TYPE_DOUBLE_ARRAY

} nbt_tag_type_t;

typedef struct nbt_tag_t nbt_tag_t;

struct nbt_tag_t
{

    nbt_tag_type_t type;

    char* name;
    size_t name_size;

    union
    {
        struct
        {
            int8_t value;
        } tag_byte;
        struct
        {
            int16_t value;
        } tag_short;
        struct
        {
            int32_t value;
        } tag_int;
        struct
        {
            int64_t value;
        } tag_long;
        struct
        {
            float value;
        } tag_float;
        struct
        {
            double value;
        } tag_double;
        struct
        {
            int8_t* value;
            size_t size;
        } tag_byte_array;
        struct
        {
            char* value;
            size_t size;
        } tag_string;
        struct
        {
            nbt_tag_t** value;
            nbt_tag_type_t type;
            size_t size;
        } tag_list;
        struct
        {
            nbt_tag_t** value;
            size_t size;
        } tag_compound;
        struct
        {
            int32_t* value;
            size_t size;
        } tag_int_array;
        struct
        {
            int64_t* value;
            size_t size;
        } tag_long_array;
        struct
        {
            float* value;
            size_t size;
        } tag_float_array;
        struct
        {
            double* value;
            size_t size;
        } tag_double_array;
    };
};

typedef struct
{
    size_t (*read)(void* userdata, uint8_t* data, size_t size);
    void* userdata;
} nbt_reader_t;

typedef struct
{
    size_t (*write)(void* userdata, uint8_t* data, size_t size);
    void* userdata;
} nbt_writer_t;

typedef enum
{
    NBT_PARSE_FLAG_USE_GZIP = 1,
    NBT_PARSE_FLAG_USE_ZLIB = 2,
    NBT_PARSE_FLAG_USE_RAW = 3,
} nbt_parse_flags_t;

typedef enum
{
    NBT_WRITE_FLAG_USE_GZIP = 1,
    NBT_WRITE_FLAG_USE_ZLIB = 2,
    NBT_WRITE_FLAG_USE_RAW = 3
} nbt_write_flags_t;

#define DEFAULT_NBT_WRITE_FLAG NBT_WRITE_FLAG_USE_ZLIB

nbt_tag_t* nbt_parse(nbt_reader_t reader, int parse_flags);
void nbt_write(nbt_writer_t writer, nbt_tag_t* tag, int write_flags);

nbt_tag_t* nbt_new_tag_byte(int8_t value);
nbt_tag_t* nbt_new_tag_short(int16_t value);
nbt_tag_t* nbt_new_tag_int(int32_t value);
nbt_tag_t* nbt_new_tag_long(int64_t value);
nbt_tag_t* nbt_new_tag_float(float value);
nbt_tag_t* nbt_new_tag_double(double value);
nbt_tag_t* nbt_new_tag_byte_array(int8_t* value, size_t size);
nbt_tag_t* nbt_new_tag_string(char* value, size_t size);
nbt_tag_t* nbt_new_tag_list(nbt_tag_type_t type);
nbt_tag_t* nbt_new_tag_compound(void);
nbt_tag_t* nbt_new_tag_int_array(int32_t* value, size_t size);
nbt_tag_t* nbt_new_tag_long_array(int64_t* value, size_t size);
nbt_tag_t* nbt_new_tag_float_array(float* value, size_t size);
nbt_tag_t* nbt_new_tag_double_array(double* value, size_t size);
uint8_t* write_nbt_to_memory(nbt_tag_t* tag, int flags, size_t* size);

void nbt_set_tag_name(nbt_tag_t* tag, char* name, size_t size);

void nbt_tag_list_append(nbt_tag_t* list, nbt_tag_t* value);
void nbt_tag_compound_append(nbt_tag_t* compound, nbt_tag_t* value);

void nbt_free_tag(nbt_tag_t* tag);

#endif

#ifdef NBT_IMPLEMENTATION

typedef struct
{
    uint8_t* buffer;
    size_t buffer_offset;
} nbt__read_stream_t;




#endif // NBT_DEFS_HPP


#endif // NBT_HPP_INCLUDED
