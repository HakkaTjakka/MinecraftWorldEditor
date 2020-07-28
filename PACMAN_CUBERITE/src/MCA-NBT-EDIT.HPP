#ifndef MCA_NBT_EDIT_HPP
#define MCA_NBT_EDIT_HPP


#define LOAD_BINARY 1
#define LOAD_NBT 2
#define LOAD_CHUNKS 4

#include "stdafx.h"
#include "xallocator.h"
#include "debug_memory.hpp"
#include "Fault.h"
#include <new>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "minecraft.h"
#include <dirent.h>
#include "NBT_DEFS.HPP"
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
extern void kiki();
extern int monitor_off;
#endif

extern int MCA_MODE;
extern int print_header;
extern int RESET_TIME;
extern size_t tot_chunks_written_to_regionfiles;
extern size_t tot_chunks_written;
extern size_t tot_chunks_appended;

extern int SILENT;
extern double tied_total_total;
extern double mien_tied;
extern double mien_tied_total;



extern "C" void xalloc_get_tot_mem();
extern "C" void xalloc_stats();

extern size_t memory_last_total;
extern size_t memory_total;
extern long long signed int memory_difference;

extern size_t xalloc_total_memory;
extern int xalloc_stats_quiet;

extern double tied;
extern double tied_total;

extern int num_chunks;

typedef struct chunk_location
{
	unsigned char	offset[3];
	unsigned char	sector_count;
} ChunkLocation;

typedef struct chunk_timestamp
{
	unsigned int timestamp;
} ChunkTimestamp;

#define CHUNKS_PER_REGION 1024

typedef struct region_file_header
{
	ChunkLocation locations[CHUNKS_PER_REGION];
	ChunkTimestamp timestamps[CHUNKS_PER_REGION];
} RegionFileHeader;

typedef struct chunk_data_header
{
	unsigned char	length[4];
	unsigned char	compression_type;
} ChunkDataHeader;

#define COMPRESSION_TYPE_GZIP 1
#define COMPRESSION_TYPE_ZLIB 2

typedef struct
{
    RegionFileHeader* region_file_header=0;
    long long signed int binary_memory_alloc=0;
    long long signed int binary_memory_freed=0;
    size_t size=0;
    unsigned char binary_changed=0;
    RegionFileHeader region_header;
    uint8_t* columns_binary[1024];
    unsigned int columns_binary_lenght[1024];       //size+1
//    unsigned char compression_type[1024];
    ChunkDataHeader header_chunk[1024];
    long long signed int columns_total_binary_memory_alloc=0;
    long long signed int columns_total_binary_memory_freed=0;
    unsigned char columns_binary_changed[1024];
    unsigned char one_or_more_columns_binary_changed=0;

    nbt_tag_t* tag_region=0;
    long long signed int nbt_tag_memory_alloc=0;
    long long signed int nbt_tag_memory_freed=0;
    unsigned char nbt_columns_tag_changed[1024];
    unsigned char one_or_more_columns_tag_changed=0;

    char filename[100]="";
    char directory_path[1024]="";
    int free=1;
    char status[50]="";
    int index_num=0;
} REGION_STRUCT;



typedef struct
{
    REGION_STRUCT** regions=0;
    size_t number_of_regions=0;
    long long signed int world_total_memory_alloc=0;
    long long signed int world_total_memory_freed=0;
} WORLD_STRUCT;



extern bool file_exists(const char * filename);
extern nbt_tag_t* read_nbt_from_memory(uint8_t* location, size_t size, int flags);
extern char* pretty_number(const long long int input_val);
extern uint8_t* load_region_file_to_memory(char* filename, size_t* size);
extern REGION_STRUCT* append_mca_file_to_world(char* directorypath, char* file_name);
extern nbt_tag_t* memory_mca_to_region_tag(REGION_STRUCT* region_struct);
extern void list_world(WORLD_STRUCT world, int last);
extern void erase_world(WORLD_STRUCT world);
extern void update_chunks_from_region_tags(REGION_STRUCT* region_struct) ;
extern void update_or_create_chunks_from_region_tags(REGION_STRUCT* region_struct);
extern double GetCounterNanoseconds();
extern bool StartCounter();
extern void nbt_to_chunks_to_memory_mca(REGION_STRUCT* region_struct);
extern void chunks_to_memory_mca(REGION_STRUCT* region_struct);
extern int print_region_from_chunks(REGION_STRUCT* region_struct,char* print_directory);
extern void print_nbt_to_file(nbt_tag_t* tag,char* filename);
extern void list_region(REGION_STRUCT* region_struct);
extern void print_nbt(nbt_tag_t* tag,char* filename);
extern void print_nbt_tree_to_file(nbt_tag_t* tag, int i, FILE * file);
extern int save_region_binary_to_file(REGION_STRUCT* region_struct);
extern int replace_string(char *str, char *orig, char *rep);
extern int print_region_from_tags(REGION_STRUCT* region_struct,char* print_directory);
extern void write_nbt_file(const char* name, nbt_tag_t* tag, int flags);
extern void nbt_to_textfile(nbt_tag_t* tag, char* filename);
extern void chunks_to_tags();
extern int chunks_to_tag(REGION_STRUCT* region_struct);
extern void mca_to_chunks();

extern void erase_all_tags(WORLD_STRUCT world);
extern void erase_tags();
extern void erase_tag(REGION_STRUCT* region_struct);

extern void erase_all_chunks(WORLD_STRUCT world);
extern void erase_chunks();
extern void erase_chunk(REGION_STRUCT* region_struct);

extern void erase_all_mcas(WORLD_STRUCT world);
extern void erase_mcas();
extern void erase_mca(REGION_STRUCT* region_struct);

extern void erase_region(REGION_STRUCT* region_struct);
extern void erase_regions();

extern void append_regions(char* worldregiondir);
extern void print_tags(char* directory);
extern void print_chunks(char* directory);
extern void tags_to_chunks();
extern void chunks_to_mca();
extern void tags_to_mca();

extern void save_mcas();
extern void compare(char* dir1,char* dir2);
extern void destroy(WORLD_STRUCT *world);
extern long long signed int get_leak(WORLD_STRUCT world, int last);
extern void checkleak(char* message);
extern void chunks_to_tags_erase_chunks_tags_to_chunks();
extern void do_something_with_all(char* worldregiondir);


extern int SILENT;
extern void toggle();






#endif // MCA_NBT_EDIT_HPP

