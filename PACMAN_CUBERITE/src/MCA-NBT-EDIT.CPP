#include "MCA-NBT-EDIT.HPP"
#include <winsock2.h>


WORLD_STRUCT world;
int RESET_TIME=1;
size_t tot_chunks_written_to_regionfiles=0;
size_t tot_chunks_written=0;
size_t tot_chunks_appended=0;

int SILENT=0;
extern double tied_total_total;
int MCA_MODE=0;

size_t XALLOC_MEM_START;

extern double PCFreq;
extern LARGE_INTEGER sys_freq;
extern int MC_running;
void test_tha_shit2();

void test_tha_shit(int n) {
    PCFreq = 0.0;  QueryPerformanceFrequency(&sys_freq);StartCounter();
    system("cls");
    for (int t=0; t<n; t++) test_tha_shit2();
}


void test_tha_shit2() {
    tied=0.0;tied_total=0.0;
    tot_chunks_written_to_regionfiles=0;
    tot_chunks_written=0;
#ifdef SFML_ONBOARD
//    for (int t=0; t<30; t++) {
//        kiki();
//        monitor_off=1;
//        sf::sleep(sf::seconds(0.1));
//    }
#endif
//    xalloc_stats_quiet=1;
//    xalloc_stats();

    xalloc_get_tot_mem();
    XALLOC_MEM_START=memory_total;
    printf("memory_total=%u\n",memory_total);

//    MCA_MODE|=LOAD_CHUNKS;
//    MCA_MODE|=LOAD_BINARY;
//    MCA_MODE|=LOAD_NBT;


/*
    for (int n=0; n<7; n++) {
        if (n==0) {
            MCA_MODE=LOAD_BINARY;
        } else if (n==1) {
            MCA_MODE=LOAD_CHUNKS;
        } else if (n==2) {
            MCA_MODE=LOAD_NBT;
        } else if (n==3) {
            MCA_MODE=LOAD_BINARY|LOAD_CHUNKS;
        } else if (n==4) {
            MCA_MODE=LOAD_BINARY|LOAD_NBT;
        } else if (n==5) {
            MCA_MODE=LOAD_NBT|LOAD_CHUNKS;
        } else if (n==6) {
            MCA_MODE=LOAD_BINARY|LOAD_NBT|LOAD_CHUNKS;
        }
*/
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
        printf("LOADING: ");
        if ((MCA_MODE&LOAD_BINARY)==LOAD_BINARY)    printf("MCA ");
        if ((MCA_MODE&LOAD_CHUNKS)==LOAD_CHUNKS)    printf("CHUNKS ");
        if ((MCA_MODE&LOAD_NBT)==LOAD_NBT)          printf("NBT ");
        xalloc_get_tot_mem();
        printf("Memory start=%s ",pretty_number(XALLOC_MEM_START));
        printf("Memory used=%s\n",pretty_number(memory_total-XALLOC_MEM_START));  //must be 0
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");


//        do_something_with_all("Synra/region");
//        void test1(); test1();
//        void test2(); test2();
        void test1(); test1();

/*
        do_something_with_all("Synra/region");
        erase_regions();
        destroy(&world);
        list_world(world,0);
*/

/*
        MCA_MODE=LOAD_CHUNKS;
        append_regions("Synra/region");
        chunks_to_mca();
        erase_chunks();
        save_mcas();
        erase_regions();
        destroy(&world);
        append_regions("Synra/region/new");
        chunks_to_mca();
        save_mcas();
        erase_regions();
        destroy(&world);
        append_regions("Synra/region/new/new");
        chunks_to_mca();
        erase_chunks();
        save_mcas();
        erase_regions();
        destroy(&world);
*/

/*
        MCA_MODE=LOAD_CHUNKS;

        append_regions("Synra/region");

        print_chunks("txt");

        erase_chunks();

        destroy(&world);

        MCA_MODE=LOAD_CHUNKS;

        append_regions("Synra/region");

        chunks_to_tags_erase_chunks_tags_to_chunks();

        chunks_to_mca();

        erase_chunks();

        save_mcas();

        erase_regions();

        destroy(&world);

        append_regions("Synra/region/new");

        print_chunks("txt");

        compare("Synra/region/new/txt","Synra/region/txt"); //proof of same nbt tags

        erase_chunks();

        destroy(&world);

*/


/* append and erase and destroy all. program.exe shit <#runs>
        append_regions();

        list_world(world,0);
        system("timeout 2 >nul");

        erase_regions();

        list_world(world,0);
        system("timeout 2 >nul");

        append_regions();

        list_world(world,0);
        system("timeout 2 >nul");

        erase_regions();

        list_world(world,0);
        system("timeout 2 >nul");
*/


/*
        MCA_MODE=LOAD_NBT|LOAD_BINARY;

        append_regions("Synra/region");

        print_tags("txt");

        save_mcas();

//        destroy(&world);
        erase_regions();                            //erase whatever

        MCA_MODE=LOAD_CHUNKS;

        append_regions("Synra/region/new");

        print_chunks("txt");

        compare("Synra/region/new/txt","Synra/region/txt"); //proof of same nbt tags, NEEDS WORLD.REGIONS[] FILLED FOR FILENAMES.... :P REMOVE FRONT PATH... :P

        erase_regions();                            //erase whatever

        destroy(&world);
*/


//save original chunks extracted from region binaries and unzipped from chunks to nbt tags to region nbt tag text file to disk.

/*

        list_world(world,0);

        MCA_MODE=LOAD_NBT;

        append_regions("Synra/region");

        print_tags("txt");

        erase_tags();

        destroy(&world);

//now flip flop little bit around.
//1) First load binary region .mca files into binary mem, with gaps between chunks.
//2) Extract chunks from .mca region binaries. (Can also been done while append_regions(), then or (|) MCA_MODE with flags, LOAD_NBT for nbt tags, LOAD_CHUNKS for chunks, LOAD_MCA for keeping binary, otherwise it will be deleted after extracting chunks and/or nbt's
//3) Erase the mca binaries (so we need the chunks)
//4) Extract nbt tags from chunks. Same story as above...
//5) Erase the chunks.
//6) Zip nbt tags back to chunks, when all deleted, all will be rezipped. If chunks are still there, and nbt not changed (see struct.), no update... for performance. But need to set change flags correctly when changing nbt tags
//7) Erase the tags.
//8) Pack chunks back into mca region binaries.
//9) Save .mca files back to disk, (into dir directory_path/new, next to region dir.)
//10) Erase the mca region binaries.
//11) Append saved mca region binaries back to nbt tags for printing
//12) Print them.
//13) Delete all region compounds, nbt's, chunks, mca's (only nbt's left...)
//14) Destroy world



        list_world(world,0);

        MCA_MODE=LOAD_BINARY;

        append_regions("Synra/region");

        mca_to_chunks();

        erase_mcas();

        chunks_to_tags();

        erase_chunks();

        tags_to_chunks();

        erase_tags();

        chunks_to_mca();

        erase_chunks();

        save_mcas();

        erase_mcas();

        destroy(&world);  //clean for sure. No left pointers etc.

        MCA_MODE=LOAD_CHUNKS;

        append_regions("Synra/region/new");         //test, load mingled region files. (Mostly smaller, sometimes some large gaps in .mca files gone...)

        print_chunks("txt");                        //only chunks loaded this time, convert the to region nbt tags for printing. (also testing other print routine).
                                                    //will end up in Sunra/region/new/txt/r.*.*.txt ???
        compare("Synra/region/new/txt","Synra/region/txt"); //proof of same nbt tags

        erase_regions();                            //erase whatever

        list_world(world,0);                        //show erased

        destroy(&world);

        list_world(world,0);                        //show destroyed. (whole pointer index freed again.) (erase leaves empty region_struct for re-use) (need code). (many...)

*/


    return;  //use program.exe test <#loops>
}

int save_region_binary_to_file(REGION_STRUCT* region_struct) {
    if (region_struct==0) { printf("Pointer to region_struct=0\n"); return 0; }
    if (region_struct->free==1) { printf("Pointer to not used, but empty, reseted, and free\n"); return 0; }
    if (region_struct->region_file_header==0) { printf("Pointer to region_file_header=0 file: %s\n",region_struct->filename); return 0; }
    char* filename=region_struct->filename;
    char directory_path[1024];
    strcpy(directory_path,region_struct->directory_path);
    strcat(directory_path,"../region.new");
    if (mkdir(directory_path) != 0)
        if (errno != EEXIST) { printf("Directory does not exist or can not create: %s\n",directory_path); return 0; }

    char filename_write[1024];
    sprintf(filename_write,"%s/%s",directory_path,filename);
    if (!SILENT) printf("\r%6.1f %6.3f Saving: %s",tied_total,tied,filename_write);
    size_t size=region_struct->size;
    FILE *file;
    if ((file = fopen(filename_write, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing region\n", filename_write); return 0; }
    if (fwrite(region_struct->region_file_header, size, 1, file) != 1) { fprintf(stderr, "FATAL ERROR: unable to write region to file \"%s\"\n", filename_write); return 0; }
    fclose(file);
    strcpy(region_struct->status,"Saved");
    list_region(region_struct);
    return 1;
}

int print_region_from_chunks(REGION_STRUCT* region_struct,char* print_directory) {
    if (region_struct==0) { printf("Pointer to region_struct=0\n"); return 0; }
    if (region_struct->free==1) { printf("Pointer to not used, but empty, reseted, and free\n"); return 0; }
    char* filename=region_struct->filename;
    int ok=0;
    for (int i = 0; i < CHUNKS_PER_REGION; i++) {
        if (!(region_struct->columns_binary[i]==0)) { ok=1; break; }
    }
    if (ok==0) { printf("No binary chunks detected\n"); return 0; }

    nbt_tag_t* tag_region=NULL;
    tag_region = nbt_new_tag_compound();
    nbt_set_tag_name(tag_region,region_struct->filename,strlen(region_struct->filename));

    int32_t index[1024]={0};
    nbt_tag_t* tag_index=NULL;
    tag_index = nbt_new_tag_int_array(index,1024);
    nbt_set_tag_name(tag_index,(char*)"index",strlen("index"));
    nbt_tag_compound_append(tag_region,tag_index);
    char name[100];

    int chunk_count=0;
    for (int i = 0; i < CHUNKS_PER_REGION; i++) {
        if (region_struct->columns_binary[i]==0) {
            tag_index->tag_int_array.value[i]=-1;
        } else {
            char *chunk;
            tag_index->tag_int_array.value[i]=chunk_count+1;
            chunk_count++;

            RegionFileHeader* region_header=&(region_struct->region_header);
            ChunkDataHeader* header_chunk=region_struct->header_chunk;
            chunk=(char*)region_struct->columns_binary[i];
            size_t length=region_struct->columns_binary_lenght[i];
            unsigned char compression_type=header_chunk[i].compression_type;

            nbt_tag_t* tag_chunk;
            tag_chunk=NULL;
            if (compression_type == COMPRESSION_TYPE_ZLIB) {
                tag_chunk = read_nbt_from_memory((uint8_t*) chunk, length, NBT_PARSE_FLAG_USE_ZLIB);
            } else if (compression_type == COMPRESSION_TYPE_GZIP) {
                tag_chunk = read_nbt_from_memory((uint8_t*) chunk, length, NBT_PARSE_FLAG_USE_GZIP);
            } else {
                tag_chunk = read_nbt_from_memory((uint8_t*) chunk, length, NBT_PARSE_FLAG_USE_RAW);
            }

            nbt_tag_t* tag_timestamp = nbt_new_tag_long((int64_t)region_header->timestamps[i].timestamp);
            nbt_set_tag_name(tag_timestamp, "timestamp" , strlen("timestamp"));
            nbt_tag_compound_append(tag_chunk,tag_timestamp);

            int regx,regz;
            sscanf(region_struct->filename,"r.%d.%d.mca",&regx,&regz);
            sprintf(name,"Chunk [%d, %d]   in world at (%d, %d)",i%32,(int)(i/32), regx*32+i%32, regz*32+(int)(i/32));
            nbt_set_tag_name(tag_chunk, (char*)name, strlen(name));
            nbt_tag_compound_append(tag_region, tag_chunk);
            tot_chunks_written++;
            tied=GetCounterNanoseconds();
            sprintf(name,"%s%s: Chunk [%2d, %2d] in world at (%5d, %5d)",region_struct->directory_path,filename,i%32,(int)(i/32), regx*32+i%32, regz*32+(int)(i/32));
            printf("\r%6.1f %6.3f %s",tied_total,tied,name);
        }
    }

    char directory_path[1024];
    strcpy(directory_path,region_struct->directory_path);
    strcat(directory_path,print_directory);
    if (mkdir(directory_path) != 0)
        if (errno != EEXIST) { printf("Directory does not exist or can not create: %s\n",directory_path); return 0; }

    char filename_print[1024];
    sprintf(filename_print,"%s/%s.txt",directory_path,region_struct->filename);
    printf("\r%6.1f %6.3f Printing: %s                                             ",tied_total,tied,filename_print);
    printf("\r%6.1f %6.3f Printing: %s",tied_total,tied,filename_print);
    print_nbt(tag_region,filename_print);
    nbt_free_tag(tag_region);
    strcpy(region_struct->status,"Printed");
    list_region(region_struct);
    return 1;
}

int print_region_from_tags(REGION_STRUCT* region_struct,char* print_directory) {
    if (region_struct==0) { printf("Pointer to region_struct=0\n"); return 0; }
    if (region_struct->free==1) { printf("Pointer to not used, but empty, reseted, and free\n"); return 0; }
    if (region_struct->tag_region==0) {
        { printf("Tag region not loaded?\n"); return 0; }
    }
    char* filename=region_struct->filename;

    char directory_path[1024];
    strcpy(directory_path,region_struct->directory_path);
    strcat(directory_path,print_directory);
    if (mkdir(directory_path) != 0)
        if (errno != EEXIST) { printf("Directory does not exist or can not create: %s\n",directory_path); return 0; }

    char filename_print[1024];
    sprintf(filename_print,"%s/%s.txt",directory_path,region_struct->filename);
    printf("\r%6.1f %6.3f Printing: %s                                             ",tied_total,tied,filename_print);
    printf("\r%6.1f %6.3f Printing: %s",tied_total,tied,filename_print);
    print_nbt(region_struct->tag_region,filename_print);
    strcpy(region_struct->status,"Printed");
    list_region(region_struct);
    return 1;
}

void print_nbt(nbt_tag_t* tag,char* filename) {
    FILE *textfile=fopen(filename,"wb");
    if (!textfile==NULL) {
        print_nbt_tree_to_file(tag, 0, textfile);
        fclose(textfile);
    } else { printf("print_nbt_to_file(): Can not open %s for writing\n"); }
    return;
}

uint8_t* load_region_file_to_memory(char* filename, size_t* size) {
    struct stat filestatus;
    stat(filename, &filestatus );
    size_t file_size=filestatus.st_size;
    *size=file_size;
    FILE* file=fopen(filename,"rb");
    uint8_t* pointer_to_mem;
    if (filename!=NULL) {
//        pointer_to_mem=new uint8_t [file_size];
//hoppa
        pointer_to_mem=(uint8_t*) NBT_MALLOC(file_size);
        if (fread(pointer_to_mem, file_size, 1, file) != 1) { printf("FATAL ERROR: unable to open file \"%s\" for reading\n", filename); return 0; }
        fclose(file);
        return pointer_to_mem;
    } else { printf("FATAL ERROR: unable to open file \"%s\" for reading\n", filename); return 0;}
}

REGION_STRUCT* append_mca_file_to_world(char* directorypath, char* file_name) {
    char region_file_name[1024]="";
    strcat(region_file_name,directorypath);  //directory_path ... directorypath... otherway around as filename... but hey!, there are comments.
    strcat(region_file_name,"/");
    strcat(region_file_name,file_name);  // filename ... file_name fix when get back from vacation...

    REGION_STRUCT* region_struct;
    RegionFileHeader* region_file_header;
//    uint8_t* region_file_header;
    size_t size;

    if ((strstr(region_file_name, ".mca")) != NULL) {}
    else { printf("No valid region filename (t.x.z.mca): %s\n" , region_file_name); return 0; }

    if ((strstr(region_file_name, "r.")) != NULL) {}
    else { printf("No valid region filename (r.x.z.mca): %s\n" , region_file_name); return 0; }

    if (file_exists(region_file_name)) {}
    else { printf("Region file %s does not exist\n",region_file_name); return 0; }

    char* p_file;

    char filename[100];
    char directory_path[1024];

    p_file=strstr(region_file_name, "r.");
    strcpy(filename,p_file);
    strcpy(directory_path,region_file_name);
    p_file=strstr(directory_path, "r.");
    *p_file=0;
    int new_region=1;
    int load_region=1;

//changed.....
    int l;
    for (l=0; l<world.number_of_regions; l++) {
        if (!(world.regions[l]==0)) {
            if ( strcmp(world.regions[l]->filename,filename)==0 && strcmp(world.regions[l]->directory_path,directory_path)==0 ) {
                if (world.regions[l]->free==0) {  //not free, in use, maybe erased, re-use
                    if (world.regions[l]->region_file_header==0) { load_region=1; }   //load again....no binary.
                    else { load_region=0; } //still active, test if region binary exists, when so, re-use it. (not erased...),
                } else {                    //freed, empty, erased, but structure still there, not freed, reuse
                    load_region=1;
                }
                new_region=0; //found region structure matching old used one and/or still filled one....
                break;
            } //otherwise make new region structure inside world
        } else {   //world.regions[l] freed (destroyed, not erased). new_region==1
        }
    }

    xalloc_get_tot_mem();
    long long int md=0;
    if (load_region==1) {
        if ( (region_file_header=(RegionFileHeader*) load_region_file_to_memory(region_file_name , &size)) !=0 ) {
            xalloc_get_tot_mem();
            md=memory_difference;
        }
        else { printf("Can not read region file %s\n",region_file_name); return 0; }
    }
    if (new_region==1) {

//KOEKOEK
//        region_struct = NBT_MALLOC(sizeof(REGION_STRUCT*));
        region_struct = (REGION_STRUCT*)NBT_MALLOC(sizeof(REGION_STRUCT));
        for (uint8_t* m=(uint8_t*)region_struct; m<((uint8_t*)region_struct+sizeof(REGION_STRUCT)); m++) *m=0;   //erase the memory???? what does the allocaoto do? Erase mem? So functions can steal re-used allocated data used by other functions/pointers....security thingy when used.
//        region_struct = new REGION_STRUCT;
        region_struct->free=0;
        strcpy(region_struct->status,"Loaded");
        xalloc_get_tot_mem();
        world.world_total_memory_alloc+=memory_difference;
    } else {
        region_struct = world.regions[l];
        if (region_struct==0) {    // can not be 0 ... but...used, but now history...changed code above...
            printf("Error\n");
            region_struct = (REGION_STRUCT*)NBT_MALLOC(sizeof(REGION_STRUCT));  //nbt_freed when destroyed.....not when erased....struct then exists.
            for (uint8_t* m=(uint8_t*)region_struct; m<((uint8_t*)region_struct+sizeof(REGION_STRUCT)); m++) *m=0;   //erase the memory???? what does the allocaoto do? Erase mem? So functions can steal re-used allocated data used by other functions/pointers....security thingy when used.
            xalloc_get_tot_mem();
            world.world_total_memory_alloc+=memory_difference;
        }
        strcpy(region_struct->status,"Reloaded");
    }
    region_struct->binary_memory_alloc=md;
    region_struct->binary_memory_freed=0;
    region_struct->columns_total_binary_memory_freed=0;
    region_struct->binary_changed=0;
    if (load_region==1) {
        region_struct->region_file_header=region_file_header;
        region_struct->size=size;
        strcpy(region_struct->filename,filename);
        strcpy(region_struct->directory_path,directory_path);
    }

    for (int c=0; c<1024; c++) {
        region_struct->columns_binary[c]=0;
        region_struct->columns_binary_lenght[c]=0;
        region_struct->header_chunk[c].compression_type=0;
        region_struct->header_chunk[c].length[0]=0;
        region_struct->header_chunk[c].length[1]=0;
        region_struct->header_chunk[c].length[2]=0;
        region_struct->header_chunk[c].length[3]=0;
        region_struct->region_header.timestamps[c].timestamp=0;
        region_struct->region_header.locations[c].offset[0]=0;
        region_struct->region_header.locations[c].offset[1]=0;
        region_struct->region_header.locations[c].offset[2]=0;
        region_struct->region_header.locations[c].sector_count=0;
    }


    if ( ((MCA_MODE&LOAD_NBT)==LOAD_NBT) || ((MCA_MODE&LOAD_CHUNKS)==LOAD_CHUNKS) ) {
        nbt_tag_t* tag_region;
//        xalloc_get_tot_mem();
        if ((tag_region=memory_mca_to_region_tag(region_struct)) != 0 ) {}
        else {
            if (!((MCA_MODE&LOAD_CHUNKS)==LOAD_CHUNKS)) {
                printf("Can not convert region file %s to nbt\n",region_file_name); //error....
//hoppa
//                delete[] region_file_header;
                NBT_FREE(region_file_header);
                region_file_header=0;

                delete region_struct;
                region_struct=0;
//                NBT_FREE(region_struct);
                return 0;
            }
        }
//        xalloc_get_tot_mem();
        if ((MCA_MODE&LOAD_NBT)==LOAD_NBT) {
            region_struct->tag_region=tag_region;
            nbt_set_tag_name(tag_region,region_struct->filename,strlen(region_struct->filename));
//            region_struct->nbt_tag_memory_alloc=memory_difference;
        }
    }
    if (!((MCA_MODE&LOAD_BINARY)==LOAD_BINARY)) {
        xalloc_get_tot_mem();
//hoppa
//        delete[] region_struct->region_file_header;
        NBT_FREE(region_struct->region_file_header);
        region_struct->region_file_header=0;
        xalloc_get_tot_mem();
        region_struct->binary_memory_freed=-memory_difference;
//        region_struct->binary_memory_alloc=0;
        region_struct->size=0;
    }

    if (new_region==1) {
        xalloc_get_tot_mem();
        world.regions=(REGION_STRUCT**)NBT_REALLOC( world.regions , (sizeof(REGION_STRUCT*) * (world.number_of_regions + 1) ) );
        world.regions[world.number_of_regions]=region_struct;
        world.regions[world.number_of_regions]->free=0;
        world.regions[world.number_of_regions]->index_num=world.number_of_regions;
        world.number_of_regions++;
        xalloc_get_tot_mem();
        world.world_total_memory_alloc+=memory_difference;
    }
    if (!SILENT) tied_total=tied_total+tied;
    if (!SILENT) list_world(world,1);
//    list_region(region_struct);
    return region_struct;
}

REGION_STRUCT* list_struct_pointer=0;
REGION_STRUCT* erase_struct_pointer=0;

void list_region(REGION_STRUCT* region_struct) {
    if (region_struct==0) { printf("list_region(): region_struct=0\n"); return; }
    list_struct_pointer=region_struct;
    list_world(world,-3);
}

int print_header=1;

void list_world(WORLD_STRUCT world, int last) {
    int setting=0;
    if (last==-5) {
        last=0;
        setting=1;
    }
    if (SILENT) return;
//    tied=0.0; //tied_total=0.0;//print_header=1;
    if (!setting) printf("\r");
    tied=GetCounterNanoseconds();
//    tied_total+=tied;
    StartCounter();
    size_t allocated_total=0;
    size_t binary_size_total=0;
    size_t binary_malloc_total=0;
    size_t binary_freed_total=0;
    size_t nbt_malloc_total=0;
    size_t nbt_freed_total=0;
    size_t chunks_total=0;
    size_t chunks_size_total=0;
    size_t chunks_freed_total=0;
    size_t chunks_malloc_total=0;
    if (last==0 ) {
        printf("%6.1f %6.3f ",tied_total,tied);
        printf("LISTING WORLD: %d entries",world.number_of_regions);
    }
    if (world.regions==0) {
        printf(" No world, must be destroyed.\n");
        if (last==0) printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
        return;
    }
    if (last==0) {
        printf("\n");
    }
    if (last!=-3 || print_header==1 && setting==0) {
        if (last==0 || print_header) {
                print_header=0;
                printf("%6.1f %6.3f ",tied_total,tied);
                printf("Index:  Free:   Address binary:      Binary size:    Binary malloc:      Binary free:      Address nbt:       Nbt malloc:         Nbt free:  Chunks:     Memory chunks:    Malloc chunks:      Chunks free:     Total malloc:  Filename:\n");
        }
    }
    int number_of_regions=world.number_of_regions;
    for (int i=0; i<number_of_regions; i++) {
        int num_columns;
        num_columns=0;
        size_t allocated_total_columns;     allocated_total_columns=0;
        size_t allocated_region;            allocated_region=0;
        size_t chunks_freed;                chunks_freed=0;
        size_t chunks_malloc;               chunks_malloc=0;
        REGION_STRUCT* region_struct;
        if (last!=-3) region_struct=world.regions[i];
        else region_struct=list_struct_pointer;
        if (  ((!(last<0)  ) && region_struct->free==0 ) || last==0 || last==-3 || last==-1) {
//        if (!(last<0 && region_struct->free==1) || last==-3 || last==0) {
            if (region_struct!=0) {

                if (!(region_struct->region_file_header==0)) {
                    allocated_region+=region_struct->binary_memory_alloc;
                    allocated_total+= region_struct->binary_memory_alloc;
                    binary_size_total+=region_struct->size;
                }
                binary_malloc_total+=region_struct->binary_memory_alloc;
                binary_freed_total+=region_struct->binary_memory_freed;

                if (!(region_struct->tag_region==0)) {
                    allocated_region+=region_struct->nbt_tag_memory_alloc;
                    allocated_total+= region_struct->nbt_tag_memory_alloc;
                }
                nbt_malloc_total+=region_struct->nbt_tag_memory_alloc;
                nbt_freed_total+=region_struct->nbt_tag_memory_freed;

                chunks_freed=region_struct->columns_total_binary_memory_freed;
                chunks_malloc=region_struct->columns_total_binary_memory_alloc;


                for (int c=0; c<1024; c++) {
                    allocated_total_columns+=(size_t) region_struct->columns_binary_lenght[c];
                    if (region_struct->columns_binary_lenght[c]>0) { num_columns++; chunks_total++; }
                }
                if (num_columns>0) {            // must be all allocated....
                    allocated_region+=chunks_malloc;
                    allocated_total+=chunks_malloc;
                    chunks_size_total+=allocated_total_columns;
                }

                chunks_freed_total+=chunks_freed;
                chunks_malloc_total+=chunks_malloc;
            }

//                allocated_region+=allocated_total_columns;
//                allocated_total+=allocated_total_columns;

            if ( (last==1 && i==world.number_of_regions - 1) || last==0 || last==-2 || last==-3) {
                printf("\r%6.1f %6.3f ",tied_total,tied);
                printf("%6d  ",     region_struct->index_num );
                printf("%5d  ",     region_struct->free );
                printf("%16p",      region_struct->region_file_header ); if (region_struct->binary_changed) printf("* "); else printf("  ");
                printf("%16s  ",    pretty_number( region_struct->size ) );
                printf("%16s  ",    pretty_number( region_struct->binary_memory_alloc) );
                printf("%16s  ",    pretty_number( region_struct->binary_memory_freed) );
                printf("%16p",      region_struct->tag_region ); if (region_struct->one_or_more_columns_tag_changed) printf("* "); else printf("  ");
                printf("%16s  ",    pretty_number( region_struct->nbt_tag_memory_alloc ) );
                printf("%16s  ",    pretty_number( region_struct->nbt_tag_memory_freed ) );
                printf("   %4d",     num_columns ); if (region_struct->one_or_more_columns_binary_changed) printf("*  "); else printf("   ");
                printf("%16s  ",    pretty_number( allocated_total_columns ) );
                printf("%16s  ",    pretty_number( chunks_malloc ) );
                printf("%16s  ",    pretty_number( chunks_freed ) );
                printf("%16s  ",    pretty_number( allocated_region ) );
                if (strlen(region_struct->filename)==0 && strlen(region_struct->directory_path)==0)
                    printf("%s\n" , region_struct->status);  //saving one space and 2 printing conversions, but costs two compares by pointer...
                else
                    printf("%s%s %s\n", region_struct->directory_path , region_struct->filename , region_struct->status);
                printf("%6.1f %6.3f ",tied_total,tied);
            }
            if (last==-3) break;
        }
    }
    if (last==-3) { return; }
    //         printf("\nIndex:  Free:   Address binary:      Binary size:    Binary malloc:      Binary free:      Address nbt:       Nbt malloc:         Nbt free:  Chunks:     Memory chunks:    Malloc chunks:      Chunks free:     Total malloc:  Filename:\n");
    if (last!=0) printf("              ");
    if (last<=0) printf("                                 ----------------  ----------------  ----------------                    ----------------  ----------------  -------   ----------------  ----------------  ----------------  ----------------\n");
//    else printf("                                                                                                                                                                                         \r");
//    printf("%6.3f %6.3f\n",tied_total,tied);
//   if (last==1)
//        printf("%6.3f %6.3f ",tied_total,tied);
//    if (last!=0) printf("");
    if (last!=1){
        printf("                            ");
    }
    printf("         ");    printf("          ");
    printf("%16s  ",    pretty_number( binary_size_total ) );
    printf("%16s  ",    pretty_number( binary_malloc_total) );
    printf("%16s  ",    pretty_number( binary_freed_total) );
    printf("                  ");
    printf("%16s  ",    pretty_number( nbt_malloc_total ) );
    printf("%16s  ",    pretty_number( nbt_freed_total ) );
    printf("%7d   ",      chunks_total );
    printf("%16s  ",    pretty_number( chunks_size_total ) );
    printf("%16s  ",    pretty_number( chunks_malloc_total ) );
    printf("%16s  ",    pretty_number( chunks_freed_total ) );
    printf("%16s" , pretty_number( allocated_total ) );
    if (last!=1 ) printf(" (=TOTAL REGIONS MEMORY ALLOCATED)"  );
    if (last==0 || last==-1) printf("\n"); else printf("\r");
    xalloc_get_tot_mem();
    if (last==0 || last==-1) {
            char world_used[100];   strcpy(world_used ,     pretty_number(world.world_total_memory_alloc-world.world_total_memory_freed)   );
            char regions_used[100]; strcpy(regions_used,    pretty_number(memory_total - XALLOC_MEM_START - (size_t)world.world_total_memory_alloc + (size_t)world.world_total_memory_freed )   );
            char start_used[100];   strcpy(start_used,      pretty_number(XALLOC_MEM_START )   );
            char total_used[100];   strcpy(total_used,      pretty_number(memory_total )   );

//            printf("                                                                                                                                             ");
            char tot_string[200];
            if (allocated_total==memory_total - XALLOC_MEM_START - (size_t)world.world_total_memory_alloc + (size_t)world.world_total_memory_freed)
                sprintf(tot_string,"MATCH! <IDidMakeThat> %s (TOTAL) - %s (START) - %s (WORLD) = %s (REGIONS)", total_used, start_used, world_used, regions_used );
            else
                sprintf(tot_string,"!!! MEMORY LEAK !!! %s (TOTAL) - %s (START) - %s (WORLD) = %s (REGIONS)", total_used, start_used, world_used, regions_used );
            int len=245-strlen(tot_string);
            for (int stripe=0; stripe<len; stripe++) printf(" ");
            printf(tot_string); // printf("\n");
//            printf("                                                                                                                                                                                                                           ");
//            printf("%16s (REGIONS USED)\n", regions_used );
//            printf("                                                                                                                                                                                                                           ");
//            printf("%16s (WORLD USED)\n", world_used );
    }
    int xsqo;
    if (last==0 || last==-1) { xsqo=xalloc_stats_quiet; xalloc_stats_quiet=1; }
    if (last==0 || last==-1) xalloc_stats();
    if (last==0 || last==-1) xalloc_stats_quiet=xsqo;
//    if (last==0 || last==-1) printf("                                                                                                                                                                                                                           %16s (XALLOC NOW)\n",
//           pretty_number( xalloc_total_memory ) );
    if (last<=0) {
        print_header=1;
    }
    if (last==0) printf("\n___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
    return;
}

void erase_tag(REGION_STRUCT* region_struct) {
    if (region_struct==0) { printf("erase_region(): region_struct=0\n"); return; }
    erase_struct_pointer=region_struct;
    strcpy(region_struct->status,"Erased");
    erase_all_tags(world);
    erase_struct_pointer=0;
}

void erase_all_tags(WORLD_STRUCT world) {
    for (int i=0; i<world.number_of_regions; i++) {
        REGION_STRUCT* region_struct;
        if (!(erase_struct_pointer==0)) region_struct=erase_struct_pointer;
        else region_struct=world.regions[i];
        if (region_struct->free==0) {
            region_struct->nbt_tag_memory_alloc=0;
            if (region_struct->tag_region!=0) {
                xalloc_get_tot_mem();
                nbt_free_tag(region_struct->tag_region);
                region_struct->tag_region=0;
                xalloc_get_tot_mem();
                region_struct->nbt_tag_memory_freed=-memory_difference;
                for (int c=0; c<1024; c++) {
                    region_struct->nbt_columns_tag_changed[c]=0;
                }
                region_struct->one_or_more_columns_tag_changed=0;
            }
            tied_total=tied_total+tied;
        }
        if (erase_struct_pointer!=0) break;
    }
    return;
}

void erase_chunk(REGION_STRUCT* region_struct) {
    if (region_struct==0) { printf("erase_region(): region_struct=0\n"); return; }
    erase_struct_pointer=region_struct;
    erase_all_chunks(world);
    erase_struct_pointer=0;
}

void erase_all_chunks(WORLD_STRUCT world) {
    for (int i=0; i<world.number_of_regions; i++) {
        REGION_STRUCT* region_struct;
        if (!(erase_struct_pointer==0)) region_struct=erase_struct_pointer;
        else region_struct=world.regions[i];
        if (region_struct!=0) {
            if (region_struct->free==0) {
                xalloc_get_tot_mem();
                region_struct->columns_total_binary_memory_alloc=0;
                int hit=0;
                for (int c=0; c<1024; c++) {
                    if (!(region_struct->columns_binary[c]==0)) {  hit=1; NBT_FREE(region_struct->columns_binary[c]); }
                    region_struct->columns_binary[c]=0;
                    region_struct->columns_binary_lenght[c]=0;
                    region_struct->header_chunk[c].length[0]=0;
                    region_struct->header_chunk[c].length[1]=0;
                    region_struct->header_chunk[c].length[2]=0;
                    region_struct->header_chunk[c].length[3]=0;
                    region_struct->header_chunk[c].compression_type=0;
                    region_struct->columns_binary_changed[c]=0;
                    region_struct->region_header.locations[c].offset[0]=0;
                    region_struct->region_header.locations[c].offset[1]=0;
                    region_struct->region_header.locations[c].offset[2]=0;
                    region_struct->region_header.locations[c].sector_count=0;
                    region_struct->region_header.timestamps[c].timestamp=0;
                    region_struct->columns_binary_changed[c]=0;
                }
                region_struct->one_or_more_columns_binary_changed;
                if (hit==1) {
                    xalloc_get_tot_mem();
                    region_struct->columns_total_binary_memory_freed=-memory_difference;
                }

            }
            tied_total=tied_total+tied;
        }
        if (erase_struct_pointer!=0) break;
    }
    return;
}

void erase_mca(REGION_STRUCT* region_struct) {
    if (region_struct==0) { printf("erase_region(): region_struct=0\n"); return; }
    erase_struct_pointer=region_struct;
    erase_all_mcas(world);
    erase_struct_pointer=0;
}

void erase_all_mcas(WORLD_STRUCT world) {
    for (int i=0; i<world.number_of_regions; i++) {
        REGION_STRUCT* region_struct;
        if (!(erase_struct_pointer==0)) region_struct=erase_struct_pointer;
        else region_struct=world.regions[i];
        if (region_struct->free==0) {
            region_struct->binary_memory_alloc=0;
            if (region_struct->region_file_header!=0) {
                xalloc_get_tot_mem();
                NBT_FREE(region_struct->region_file_header);
                region_struct->region_file_header=0;
                xalloc_get_tot_mem();
                region_struct->binary_memory_freed=-memory_difference;
                region_struct->size=0;
                region_struct->binary_changed=0;
            }
            tied_total=tied_total+tied;
        }
        if (erase_struct_pointer!=0) break;
    }
    return;
}

void erase_region(REGION_STRUCT* region_struct) {
    if (region_struct==0) { printf("erase_region(): region_struct=0\n"); return; }
    erase_struct_pointer=region_struct;
    erase_world(world);
    erase_struct_pointer=0;
}

void erase_world(WORLD_STRUCT world) {
    for (int i=0; i<world.number_of_regions; i++) {
        REGION_STRUCT* region_struct;
        if (!(erase_struct_pointer==0)) region_struct=erase_struct_pointer;
        else region_struct=world.regions[i];
        if (region_struct!=0) {
            if (region_struct->free==0) {
                region_struct->binary_memory_alloc=0;
                if (!(region_struct->region_file_header==0)) {
                    NBT_FREE(region_struct->region_file_header);
                    region_struct->region_file_header=0;
                    xalloc_get_tot_mem();
                    region_struct->binary_memory_freed=-memory_difference;
                    region_struct->size=0;
                    region_struct->binary_changed=0;
                }

                xalloc_get_tot_mem();
                region_struct->columns_total_binary_memory_alloc=0;
                int hit=0;
                for (int c=0; c<1024; c++) {
                    if (!(region_struct->columns_binary[c]==0)) {  hit=1; NBT_FREE(region_struct->columns_binary[c]); }
                    region_struct->columns_binary[c]=0;
                    region_struct->columns_binary_lenght[c]=0;
                    region_struct->header_chunk[c].length[0]=0;
                    region_struct->header_chunk[c].length[1]=0;
                    region_struct->header_chunk[c].length[2]=0;
                    region_struct->header_chunk[c].length[3]=0;
                    region_struct->header_chunk[c].compression_type=0;
                    region_struct->columns_binary_changed[c]=0;
                    region_struct->region_header.locations[c].offset[0]=0;
                    region_struct->region_header.locations[c].offset[1]=0;
                    region_struct->region_header.locations[c].offset[2]=0;
                    region_struct->region_header.locations[c].sector_count=0;
                    region_struct->region_header.timestamps[c].timestamp=0;
                    region_struct->columns_binary_changed[c]=0;
                }
                region_struct->one_or_more_columns_binary_changed;
                if (hit==1) {
                    xalloc_get_tot_mem();
                    region_struct->columns_total_binary_memory_freed=-memory_difference;
                }

                region_struct->nbt_tag_memory_alloc=0;
                if (region_struct->tag_region!=0) {
                    xalloc_get_tot_mem();
                    nbt_free_tag(region_struct->tag_region);
                    region_struct->tag_region=0;
                    xalloc_get_tot_mem();
                    region_struct->nbt_tag_memory_freed=-memory_difference;
                    for (int c=0; c<1024; c++) {
                        region_struct->nbt_columns_tag_changed[c]=0;
                    }
                    region_struct->one_or_more_columns_tag_changed=0;
                }
            }

            region_struct->free=1;
            tied_total=tied_total+tied;
        }
//        for (uint8_t* m=(uint8_t*)region_struct; m<((uint8_t*)region_struct+sizeof(REGION_STRUCT)); m++) *m=0; // kill it. For later use....
        if (erase_struct_pointer!=0) break;
    }
    return;
}

nbt_tag_t* memory_mca_to_region_tag(REGION_STRUCT* region_struct)
{
    if (region_struct==0) { printf("Pointer to region_struct=0\n"); return 0; }
//    if (region_struct->free==1) { printf("Pointer to not used, but empty, reseted, and free\n"); return 0; }
    if (region_struct->tag_region!=0) {
        { printf("Nbt tag not empty. Delete first\n"); return 0; }
    }

    char* filename=region_struct->filename;
    RegionFileHeader* region_file_header=(RegionFileHeader*) region_struct->region_file_header;
    RegionFileHeader* region_header=&(region_struct->region_header);

    if (region_file_header==0) { printf("Pointer to region_file_header=0 file: %s\n",filename); return 0; }

    for (int i = 0; i < CHUNKS_PER_REGION; i++) {
        if (region_struct->columns_binary[i]!=0) { printf("Columns allocated. Not empty. Delete 'chunks' first\n"); return 0; }
    }

    int	i;
    int32_t index[1024]={0};

    nbt_tag_t* tag_region;
    nbt_tag_t* tag_index;

    if ((MCA_MODE&LOAD_NBT)==LOAD_NBT) {
        xalloc_get_tot_mem();
        region_struct->nbt_tag_memory_alloc=0;
        tag_region=NULL;
        tag_region = nbt_new_tag_compound();
        nbt_set_tag_name(tag_region,region_struct->filename,strlen(region_struct->filename));

        tag_index = nbt_new_tag_int_array(index,1024);
        nbt_set_tag_name(tag_index,(char*)"index",strlen("index"));
        nbt_tag_compound_append(tag_region,tag_index);
        xalloc_get_tot_mem();
        region_struct->nbt_tag_memory_alloc=memory_difference;
    }

    nbt_tag_t* tag_chunk;

    int32_t chunk_count=0;
    xalloc_get_tot_mem();

    if ((MCA_MODE&LOAD_CHUNKS)==LOAD_CHUNKS) {
        region_struct->columns_total_binary_memory_alloc=0;
        for (i = 0; i < CHUNKS_PER_REGION; i++)
        {
            unsigned int offset, length;
            ChunkDataHeader* header_chunk;

            offset = (65536 * region_file_header->locations[i].offset[0]) + (256 * region_file_header->locations[i].offset[1]) + region_file_header->locations[i].offset[2];

            if (offset == 0) {
//                if ((MCA_MODE&LOAD_NBT)==LOAD_NBT) {
//                    tag_index->tag_int_array.value[i]=-1;
//                }
                region_struct->columns_binary[i]=0;
                region_struct->columns_binary_lenght[i]=0;
                region_struct->header_chunk[i].length[0]=0;
                region_struct->header_chunk[i].length[1]=0;
                region_struct->header_chunk[i].length[2]=0;
                region_struct->header_chunk[i].length[3]=0;
                region_struct->header_chunk[i].compression_type=(char)0;
                region_struct->columns_binary_changed[i]=0;
                region_header->locations[i].offset[0]=0;
                region_header->locations[i].offset[1]=0;
                region_header->locations[i].offset[2]=0;
                region_header->locations[i].sector_count=0;
                region_header->timestamps[i].timestamp=0;
            } else {
                chunk_count++;
                char *chunk;

                header_chunk=(ChunkDataHeader*) ((uint8_t*)region_file_header+(size_t)offset*4096);
                length = (16777216 * header_chunk->length[0]) + (65536 * header_chunk->length[1]) + (256 * header_chunk->length[2]) + header_chunk->length[3];
                if (length > 4096 * region_file_header->locations[i].sector_count) { printf("FATAL ERROR: chunk #%d is bigger than expected (%u bytes vs %u)\n", i, length, 4096 * region_file_header->locations[i].sector_count ); return(0); }
                if (header_chunk->compression_type != COMPRESSION_TYPE_GZIP && header_chunk->compression_type != COMPRESSION_TYPE_ZLIB) { printf("FATAL ERROR: chunk #%d has unknown compression type (%u)\n", i, header_chunk->compression_type); return(0); }
                chunk = (char*) header_chunk+sizeof(ChunkDataHeader) ;

//hoppa
//                region_struct->columns_binary[i] = new uint8_t [length-1];
                if (length<1) printf("Error\n");
                region_struct->columns_binary[i]=(uint8_t*) NBT_MALLOC(length-1);
                NBT_MEMCPY(region_struct->columns_binary[i],chunk, length-1);
                region_struct->columns_binary_lenght[i]=length-1;
//whooo                NBT_MEMCPY(&(region_struct->header_chunk[i]),header_chunk,sizeof(chunk_data_header));

                region_struct->header_chunk[i].length[0]= (((length) & 0xFF000000) >> 24) & 0xFF;   //+1, means 0=empty and size=length -1 ???
                region_struct->header_chunk[i].length[1]= (((length) & 0x00FF0000) >> 16) & 0xFF;   // so length = size + 1 ???
                region_struct->header_chunk[i].length[2]= (((length) & 0x0000FF00) >>  8) & 0xFF;
                region_struct->header_chunk[i].length[3]= (((length) & 0x000000FF)      ) & 0xFF;
                region_struct->header_chunk[i].compression_type=header_chunk->compression_type;
                region_struct->columns_binary_changed[i]=0;
                region_struct->region_header.locations[i].offset[0]=0;
                region_struct->region_header.locations[i].offset[1]=0;
                region_struct->region_header.locations[i].offset[2]=0;
                unsigned char sector_count= (unsigned char)((length-1+sizeof(ChunkDataHeader))/4096)  +1;
                region_struct->region_header.locations[i].sector_count=sector_count;
                region_struct->region_header.timestamps[i].timestamp=region_file_header->timestamps[i].timestamp;

//                NBT_MEMCPY(&(region_struct->header_chunk[i]), header_chunk, sizeof(ChunkDataHeader)); //nono
            }
        }
        xalloc_get_tot_mem();
        region_struct->columns_total_binary_memory_alloc+=memory_difference;
    }
    if ((MCA_MODE&LOAD_NBT)==LOAD_NBT) {
        chunk_count=0;
        xalloc_get_tot_mem();
        for (i = 0; i < CHUNKS_PER_REGION; i++) {
            unsigned int offset, length;
            ChunkDataHeader* header_chunk;

            offset = (65536 * region_file_header->locations[i].offset[0]) + (256 * region_file_header->locations[i].offset[1]) + region_file_header->locations[i].offset[2];

            if (offset == 0) {
                tag_index->tag_int_array.value[i]=-1;

                region_struct->columns_binary[i]=0;
                region_struct->columns_binary_lenght[i]=0;
                region_struct->header_chunk[i].length[0]=0;
                region_struct->header_chunk[i].length[1]=0;
                region_struct->header_chunk[i].length[2]=0;
                region_struct->header_chunk[i].length[3]=0;
                region_struct->header_chunk[i].compression_type=(char)0;
                region_struct->columns_binary_changed[i]=0;
                region_struct->region_header.locations[i].offset[0]=0;
                region_struct->region_header.locations[i].offset[1]=0;
                region_struct->region_header.locations[i].offset[2]=0;
                region_struct->region_header.locations[i].sector_count=0;
                region_struct->region_header.timestamps[i].timestamp=0;
            } else {
                tag_index->tag_int_array.value[i]=chunk_count+1;
                chunk_count++;
                char *chunk;

                header_chunk=(ChunkDataHeader*) ((uint8_t*)region_file_header+(size_t)offset*4096);
                length = (16777216 * header_chunk->length[0]) + (65536 * header_chunk->length[1]) + (256 * header_chunk->length[2]) + header_chunk->length[3];
                if (length > 4096 * region_file_header->locations[i].sector_count) { printf("FATAL ERROR: chunk #%d is bigger than expected (%u bytes vs %u)\n", i, length, 4096 * region_file_header->locations[i].sector_count ); return(0); }
                if (header_chunk->compression_type != COMPRESSION_TYPE_GZIP && header_chunk->compression_type != COMPRESSION_TYPE_ZLIB) { printf("FATAL ERROR: chunk #%d has unknown compression type (%u)\n", i, header_chunk->compression_type); return(0); }
                chunk = (char*) header_chunk+sizeof(ChunkDataHeader) ;

                tag_chunk=NULL;

                if (header_chunk->compression_type == COMPRESSION_TYPE_ZLIB) {
                    tag_chunk = read_nbt_from_memory((uint8_t*) chunk, length-1, NBT_PARSE_FLAG_USE_ZLIB);
                } else if (header_chunk->compression_type == COMPRESSION_TYPE_GZIP) {
                    tag_chunk = read_nbt_from_memory((uint8_t*) chunk, length-1, NBT_PARSE_FLAG_USE_GZIP);
                } else {
                    tag_chunk = read_nbt_from_memory((uint8_t*) chunk, length-1, NBT_PARSE_FLAG_USE_RAW);
                }

                nbt_tag_t* tag_timestamp = nbt_new_tag_long((int64_t)region_file_header->timestamps[i].timestamp);
                nbt_set_tag_name(tag_timestamp, "timestamp" , strlen("timestamp"));
                nbt_tag_compound_append(tag_chunk,tag_timestamp);

                int regx,regz;
                char name[100];
                sscanf(filename,"r.%d.%d.mca",&regx,&regz);
                sprintf(name,"Chunk [%d, %d]   in world at (%d, %d)",i%32,(int)(i/32), regx*32+i%32, regz*32+(int)(i/32));
                nbt_set_tag_name(tag_chunk, (char*)name, strlen(name));
                nbt_tag_compound_append(tag_region, tag_chunk);
                region_struct->nbt_columns_tag_changed[i]=0;

                if (!((MCA_MODE&LOAD_CHUNKS)==LOAD_CHUNKS)) {
                    region_struct->nbt_columns_tag_changed[i]=1;
                    region_struct->one_or_more_columns_tag_changed=1;
//memo
                    if (region_struct->columns_binary[i]!=0) printf("Error\n");
                    region_struct->columns_binary[i]=0;
                    region_struct->columns_binary_lenght[i]=0;
                    region_struct->header_chunk[i].length[0]=0;
                    region_struct->header_chunk[i].length[1]=0;
                    region_struct->header_chunk[i].length[2]=0;
                    region_struct->header_chunk[i].length[3]=0;
                    region_struct->header_chunk[i].compression_type=(char)0;
                    region_struct->columns_binary_changed[i]=0;
                    region_struct->region_header.locations[i].offset[0]=0;
                    region_struct->region_header.locations[i].offset[1]=0;
                    region_struct->region_header.locations[i].offset[2]=0;
                    region_struct->region_header.locations[i].sector_count=0;
                    region_struct->region_header.timestamps[i].timestamp=0;

                }
            }
        }
        xalloc_get_tot_mem();
        region_struct->nbt_tag_memory_alloc+=memory_difference;
    }
//    NBT_MEMCPY(region_header, region_file_header, sizeof(RegionFileHeader) );
    tot_chunks_appended+=chunk_count;
    num_chunks+=chunk_count;
    return tag_region;
}

int chunks_to_tag(REGION_STRUCT* region_struct)
{
    if (region_struct==0) { printf("Pointer to region_struct=0\n"); return 0; }
    if (region_struct->free==1) { printf("Pointer to not used, but empty, reseted, and free\n"); return 0; }
//    if (region_struct->tag_region!=0) {                                 // overwrite existing....
//        { printf("Nbt tag not empty. Delete first\n"); return 0; }
//    }

    char* filename=region_struct->filename;
    RegionFileHeader* region_file_header=(RegionFileHeader*) region_struct->region_file_header;
    RegionFileHeader* region_header=&(region_struct->region_header);
    uint8_t** columns_binary=(uint8_t**)region_struct->columns_binary;
    ChunkDataHeader* header_chunk=region_struct->header_chunk;

//    if (region_file_header==0) { printf("Pointer to region_file_header=0 file: %s\n",filename); return 0; }

    for (int i = 0; i < CHUNKS_PER_REGION; i++) {
        if (columns_binary[i]!=0) break;
        else if (i==CHUNKS_PER_REGION) { printf("No columns %s%s\n",region_struct->directory_path,filename); return 0; }
    }

    nbt_tag_t* tag_region=region_struct->tag_region;
    xalloc_get_tot_mem();
    if (tag_region!=0) {
        nbt_free_tag(tag_region);
        tag_region=0;
        region_struct->tag_region=0;
        xalloc_get_tot_mem();
        region_struct->nbt_tag_memory_freed-=memory_difference;
    }
    int	i;
    int32_t index[1024]={0};

    region_struct->nbt_tag_memory_alloc=0;
    tag_region=NULL;
    tag_region = nbt_new_tag_compound();
    nbt_set_tag_name(tag_region,region_struct->filename,strlen(region_struct->filename));

    nbt_tag_t* tag_index = nbt_new_tag_int_array(index,1024);
    nbt_set_tag_name(tag_index,(char*)"index",strlen("index"));
    nbt_tag_compound_append(tag_region,tag_index);
    xalloc_get_tot_mem();
    region_struct->nbt_tag_memory_alloc=memory_difference;

    nbt_tag_t* tag_chunk;

    int32_t chunk_count=0;

    ChunkTimestamp* timestamps=region_header->timestamps;                       //region_file_header is pointer to binary region file inside mem. (pointer to start whole file in mem)
    ChunkLocation* locations=region_header->locations;                          //region_header is region_file_header structure.
    unsigned char* nbt_columns_tag_changed=region_struct->nbt_columns_tag_changed;

    for (i = 0; i < CHUNKS_PER_REGION; i++) {
        unsigned int offset, length;
        ChunkDataHeader* header_chunk;

        if (columns_binary[i]!=0) {
            tag_index->tag_int_array.value[i]=chunk_count+1;
            chunk_count++;

            unsigned char compression_type=region_struct->header_chunk[i].compression_type;
            size_t length = (16777216 * region_struct->header_chunk[i].length[0]) + (65536 * region_struct->header_chunk[i].length[1]) + (256 * region_struct->header_chunk[i].length[2]) + region_struct->header_chunk[i].length[3];
            int64_t timestamp=timestamps[i].timestamp;


            tag_chunk=NULL;

            if (compression_type == COMPRESSION_TYPE_ZLIB) {
                tag_chunk = read_nbt_from_memory((uint8_t*) columns_binary[i], length, NBT_PARSE_FLAG_USE_ZLIB);
            } else if (compression_type == COMPRESSION_TYPE_GZIP) {
                tag_chunk = read_nbt_from_memory((uint8_t*) columns_binary[i], length, NBT_PARSE_FLAG_USE_GZIP);
            } else {
                tag_chunk = read_nbt_from_memory((uint8_t*) columns_binary[i], length, NBT_PARSE_FLAG_USE_RAW);
            }

            nbt_tag_t* tag_timestamp = nbt_new_tag_long(timestamp);
            nbt_set_tag_name(tag_timestamp, "timestamp" , strlen("timestamp"));
            nbt_tag_compound_append(tag_chunk,tag_timestamp);

            int regx,regz;
            char name[100];
            sscanf(filename,"r.%d.%d.mca",&regx,&regz);
            sprintf(name,"Chunk [%d, %d]   in world at (%d, %d)",i%32,(int)(i/32), regx*32+i%32, regz*32+(int)(i/32));
            nbt_set_tag_name(tag_chunk, (char*)name, strlen(name));
            nbt_tag_compound_append(tag_region, tag_chunk);
            region_struct->nbt_columns_tag_changed[i]=0;
        }
    }
    xalloc_get_tot_mem();
    region_struct->nbt_tag_memory_alloc+=memory_difference;

    num_chunks+=chunk_count;
    tot_chunks_appended+=chunk_count;
    region_struct->tag_region=tag_region;  // or make tag_region nbt_tag_t** tag_region, and address it with *tag_region->....
    list_region(region_struct);
    return 1;
}


void update_or_create_chunks_from_region_tags(REGION_STRUCT* region_struct) {
    if (region_struct==0) { printf("Pointer to region_struct=0\n"); return; }
    if (region_struct->free==1) { printf("Pointer to not used, but free\n"); return; }
    if (region_struct->tag_region==0) {
        { printf("Tag region not loaded?\n"); return; }
    }
    nbt_tag_t* tag_region=region_struct->tag_region;
    uint8_t** columns_binary=(uint8_t**)region_struct->columns_binary;
    unsigned char* nbt_columns_tag_changed=region_struct->nbt_columns_tag_changed;
    unsigned char* columns_binary_changed=region_struct->columns_binary_changed;
    unsigned int* columns_binary_lenght=region_struct->columns_binary_lenght;
    ChunkDataHeader* header_chunk=region_struct->header_chunk;

    RegionFileHeader* region_header=&(region_struct->region_header);            // different from RegionFileHeader region_header=(region_struct->region_header); ?? makes/copies new structure.???
    RegionFileHeader* region_file_header=region_struct->region_file_header;     // different from RegionFileHeader region_header=(region_struct->region_header); ?? makes/copies new structure.???

    ChunkTimestamp* timestamps=region_header->timestamps;                       //region_file_header is pointer to binary region file inside mem. (pointer to start whole file in mem)
    ChunkLocation* locations=region_header->locations;                          //region_header is region_file_header structure.

    nbt_tag_t* tag_index;
    tag_index=(nbt_tag_t*)tag_region->tag_compound.value[0];//->tag_int_array.value;
    int32_t* index={0};
    index=tag_index->tag_int_array.value; // index to columns, quick & sorted

//    tag_index->tag_int_array.value[i]=-1;

    for (int i=0; i<CHUNKS_PER_REGION; i++) {
//        ChunkDataHeader* one_chunk_header=region_struct->header_chunk+(sizeof(ChunkDataHeader*))*i;
        ChunkDataHeader* one_chunk_header=&(header_chunk[i]);
        if (nbt_columns_tag_changed[i]==1 || columns_binary[i]==0) {      //column changed, or new....update 'chunk'(column)
            if (tag_region==0) {                            //whole region deleted?
            } else {
                if (columns_binary[i]!=0) {                 //changed, not empty, delete
                    xalloc_get_tot_mem();
                    NBT_FREE((uint8_t*)columns_binary[i]);
                    columns_binary[i]=0;
                    xalloc_get_tot_mem();
                    region_struct->columns_total_binary_memory_freed-=memory_difference;
//                    region_struct->columns_total_binary_memory_alloc+=memory_difference;
                    region_struct->one_or_more_columns_binary_changed=1;
                } else {
                    one_chunk_header->compression_type = DEFAULT_NBT_WRITE_FLAG;            //zlib -> NBT_WRITE_FLAG_USE_ZLIB
                }
                int32_t column_num=index[i];
                size_t length=0;
                columns_binary_changed[i]=1;
                if (column_num>0) {
                    region_struct->one_or_more_columns_binary_changed=1;
                    nbt_tag_t* tag_column=tag_region->tag_compound.value[column_num];

                    if (one_chunk_header->compression_type == 0) one_chunk_header->compression_type = DEFAULT_NBT_WRITE_FLAG;   //never now...
                    int MINUS_ONE=0;
                    for (int x=0; x<tag_column->tag_compound.size; x++) {
                        if ( strcmp(tag_column->tag_compound.value[x]->name,"timestamp")==0 ) {
                            timestamps[i].timestamp=(uint32_t)tag_column->tag_compound.value[x]->tag_long.value;
                            tag_column->tag_compound.size--; // set last tag off, make sure timestamp is last tag on chunk tag.
                            MINUS_ONE=1;
                            break;
                        }
                    }

                    xalloc_get_tot_mem();
                    if (one_chunk_header->compression_type == COMPRESSION_TYPE_ZLIB) {
                        columns_binary[i]=write_nbt_to_memory(tag_column, NBT_WRITE_FLAG_USE_ZLIB, &length);
                    } else if (one_chunk_header->compression_type == COMPRESSION_TYPE_GZIP) {
                        columns_binary[i]=write_nbt_to_memory(tag_column, NBT_WRITE_FLAG_USE_GZIP, &length);
                    } else if (one_chunk_header->compression_type == NBT_WRITE_FLAG_USE_RAW) {
                        columns_binary[i]=write_nbt_to_memory(tag_column, NBT_WRITE_FLAG_USE_RAW, &length);  //who knows...
                    }

                    xalloc_get_tot_mem();
                    region_struct->columns_total_binary_memory_alloc+=memory_difference;
//                    printf("\nzipping, length=%u,  diff=%lld  columns_total_binary_memory_alloc=%u\n",length,memory_difference,region_struct->columns_total_binary_memory_alloc);

                    unsigned char sector_count= (unsigned char)((length-1+sizeof(ChunkDataHeader))/4096)  +1;
                    if (MINUS_ONE==1) tag_column->tag_compound.size++;      // Draw back, don't destruct tag when used laterz....

                    one_chunk_header->length[0]= (((length+1) & 0xFF000000) >> 24) & 0xFF;   //+1, means 0=empty and size=length -1 ???
                    one_chunk_header->length[1]= (((length+1) & 0x00FF0000) >> 16) & 0xFF;   // so length = size + 1 ???
                    one_chunk_header->length[2]= (((length+1) & 0x0000FF00) >>  8) & 0xFF;
                    one_chunk_header->length[3]= (((length+1) & 0x000000FF)      ) & 0xFF;
                    locations[i].sector_count=sector_count;
                    columns_binary_changed[i]=1;
                    columns_binary_lenght[i]=length;
                    tot_chunks_written++;

                } //else nothing to update.....nothing there, no column, make first. Or, deleted. ???
                else {
                    columns_binary_lenght[i]=0;
                    one_chunk_header->length[0]=0;
                    one_chunk_header->length[1]=0;
                    one_chunk_header->length[2]=0;
                    one_chunk_header->length[3]=0;
                    one_chunk_header->compression_type=0;
                    columns_binary_changed[i]=1;
                    locations[i].offset[0]=0;
                    locations[i].offset[1]=0;
                    locations[i].offset[2]=0;
                    locations[i].sector_count=0;
                    timestamps[i].timestamp=0;
                }
                nbt_columns_tag_changed[i]=0;
            }
        }
    }
    region_struct->one_or_more_columns_tag_changed=0;
    tied_total=tied_total+tied;
    list_region(region_struct);
}

/*****************/

//asume's region_struct->columns_binary is empty. Create from region_struct->region_struct->tag_region. Bypass struct->columns.....
void nbt_to_chunks_to_memory_mca(REGION_STRUCT* region_struct) {

    if (region_struct==0) { printf("Pointer to region_struct=0\n"); return; }
    if (region_struct->free==1) { printf("Pointer to not used, but free\n"); return; }

//    if (region_struct->tag_region!=0 && region_struct->one_or_more_columns_tag_changed==1) {
//        update_or_create_chunks_from_region_tags(region_struct);
//    }

    xalloc_get_tot_mem();
    if (region_struct->region_file_header!=0) {
//hoppa
//        delete[] region_struct->region_file_header;
        NBT_FREE(region_struct->region_file_header);
        region_struct->region_file_header=0;
        xalloc_get_tot_mem();
        region_struct->binary_memory_freed-=memory_difference;
    }

    nbt_tag_t* tag_region=region_struct->tag_region;
    if (tag_region==0) {
        //delete or keep as header, what info is in it? level->??? push changed files into separate directory, then you can overwrite (a copy off) the original directory, with the saved/changed files. Leaving the ones not changed...So you only have a directory with changed files. Then when overwriting the originals, the change is permanent. So keep original copy.
        printf("Region tag=0 region: %s%s\n",region_struct->directory_path,region_struct->filename); return;
    }
    uint8_t** columns_binary=(uint8_t**)region_struct->columns_binary;
    unsigned char* nbt_columns_tag_changed=region_struct->nbt_columns_tag_changed;
    unsigned char* columns_binary_changed=region_struct->columns_binary_changed;
    unsigned int* columns_binary_lenght=region_struct->columns_binary_lenght;
    ChunkDataHeader* header_chunk=region_struct->header_chunk;

    RegionFileHeader* region_header=&(region_struct->region_header);

    ChunkTimestamp* timestamps=region_header->timestamps;
    ChunkLocation* locations=region_header->locations;
    size_t size;

//    if (region_file_header!=0) // if not region_file_header (no region binary file in mem) make it.
//        if (!(region_struct->one_or_more_columns_binary_changed || region_struct->one_or_more_columns_tag_changed)) return;  //nothing changed. Leave..

	int	region;
    uint8_t* pointer_to_mem;
    char name[1000];
    strcpy(name,tag_region->name);

//    RegionFileHeader	header;
    int			i;
    size_t length;

    int chunk_count=0;
    int cnt;
    cnt=0;
    uint8_t* chunks[1024]={0};
    unsigned int	offset_block=0;
    unsigned int	offset;
    int32_t* index;
    index=tag_region->tag_compound.value[0]->tag_int_array.value; // close index to columns, quick & sorted

//        timestamps=tag_region->tag_compound.value[tag_region->tag_compound.size-1]->tag_int_array.value;

    for (i = 0; i < CHUNKS_PER_REGION; i++)
    {
        int32_t column_number=index[i];
        size_t size=0;
        if (column_number>0) {
            unsigned char sector_count;
            chunk_count++;

            nbt_tag_t* tag_column=tag_region->tag_compound.value[column_number];
            int MINUS_ONE=0;
            for (int x=0; x<tag_column->tag_compound.size; x++) {
                if ( strcmp(tag_column->tag_compound.value[x]->name,"timestamp")==0 ) {
                    region_header->timestamps[i].timestamp=(uint32_t)tag_column->tag_compound.value[x]->tag_long.value;
                    tag_column->tag_compound.size--; // set last tag off, make shure timestamp is last tag on chunk tag.
                    MINUS_ONE=1;
                    break;
                }
            }

            chunks[i]=write_nbt_to_memory(tag_column, NBT_WRITE_FLAG_USE_ZLIB, &size);
            sector_count= (unsigned char)((size-1+sizeof(ChunkDataHeader))/4096)  +1;            //beep beep

            if (MINUS_ONE==1) tag_column->tag_compound.size++; // Draw back, don't destruct tag when used laterz....

            header_chunk[i].compression_type = COMPRESSION_TYPE_ZLIB;
            header_chunk[i].length[0]= (((size+1) & 0xFF000000) >> 24) & 0xFF;   //+1, means 0=empty and size=length -1 ???
            header_chunk[i].length[1]= (((size+1) & 0x00FF0000) >> 16) & 0xFF;   // so length = size + 1 ???
            header_chunk[i].length[2]= (((size+1) & 0x0000FF00) >>  8) & 0xFF;
            header_chunk[i].length[3]= (((size+1) & 0x000000FF)      ) & 0xFF;
            region_header->locations[i].offset[0]=(((2 + offset_block) & 0x00FF0000) >> 16) & 0xFF;
            region_header->locations[i].offset[1]=(((2 + offset_block) & 0x0000FF00) >> 8) & 0xFF;
            region_header->locations[i].offset[2]=(2 + offset_block) & 0xFF;
            region_header->locations[i].sector_count=sector_count;
//                region_header->timestamps[i].timestamp=timestamps[i];

            length = (16777216 * header_chunk[i].length[0]) + (65536 * header_chunk[i].length[1]) + (256 * header_chunk[i].length[2]) + header_chunk[i].length[3];
            offset = (65536 * region_header->locations[i].offset[0]) + (256 * region_header->locations[i].offset[1]) + region_header->locations[i].offset[2];

            offset_block+=sector_count;

        } else {
            header_chunk[i].length[0]=0;
            header_chunk[i].length[1]=0;
            header_chunk[i].length[2]=0;
            header_chunk[i].length[3]=0;
            region_header->locations[i].offset[0]=0;
            region_header->locations[i].offset[1]=0;
            region_header->locations[i].offset[2]=0;
            region_header->locations[i].sector_count=0;
            region_header->timestamps[i].timestamp=0;
            header_chunk[i].compression_type = 0;
            length = (16777216 * header_chunk[i].length[0]) + (65536 * header_chunk[i].length[1]) + (256 * header_chunk[i].length[2]) + header_chunk[i].length[3];
            offset = (65536 * region_header->locations[i].offset[0]) + (256 * region_header->locations[i].offset[1]) + region_header->locations[i].offset[2];
        }
    } // i

/*
    xalloc_get_tot_mem();
    if (region_struct->region_file_header!=0) {
        NBT_FREE(region_struct->region_file_header);
        region_struct->region_file_header=0;
        region_struct->binary_memory_freed-=memory_difference;
    }
*/
//hoppa
//    pointer_to_mem= new uint8_t [sizeof(RegionFileHeader) + (offset_block)*4096];
    xalloc_get_tot_mem();
    pointer_to_mem=(uint8_t*) NBT_MALLOC(sizeof(RegionFileHeader) + (offset_block)*4096);
    xalloc_get_tot_mem();
    region_struct->binary_memory_alloc=memory_difference;
    region_struct->region_file_header=(RegionFileHeader*) pointer_to_mem;

    NBT_MEMCPY(pointer_to_mem , region_header, sizeof(RegionFileHeader));
    size=sizeof(RegionFileHeader);

    for (i = 0; i < CHUNKS_PER_REGION; i++)
    {
        offset = (65536 * region_header->locations[i].offset[0]) + (256 * region_header->locations[i].offset[1]) + region_header->locations[i].offset[2];
        length = (16777216 * header_chunk[i].length[0]) + (65536 * header_chunk[i].length[1]) + (256 * header_chunk[i].length[2]) + header_chunk[i].length[3];
        if (offset+length>(offset_block+2)*4096) {
            printf("error: offset+length>offset_block*4096\n");
            printf("error: offset+length=%d\n",offset+length);
            printf("error: offset_block*4096=%d\n",offset_block*4096);
        }
        if (offset!=0) {
            NBT_MEMCPY(pointer_to_mem+offset*4096 , &header_chunk[i] , sizeof(ChunkDataHeader) );
            NBT_MEMCPY(pointer_to_mem+offset*4096 + sizeof(ChunkDataHeader) , chunks[i] , length  );
//hoppa
//            delete[] chunks[i];
            NBT_FREE(chunks[i]);
            chunks[i]=0;
            size=offset*4096 + ((int)((sizeof(ChunkDataHeader) + length)/4096) + 1)*4096;      // -1 +1 get nuts!!!
        }
    }
    region_struct->size=size;
    cnt=0;
    num_chunks+=chunk_count;
    region_struct->binary_changed=1;
    strcpy(region_struct->status,"changed");
    tied_total=tied_total+tied;
    list_region(region_struct);
}


//creates from region_struct->region_struct->columns_binary, assumes region_struct->header_chunk already filled from updater and/or load.
void chunks_to_memory_mca(REGION_STRUCT* region_struct) {
    if (region_struct==0) { printf("Pointer to region_struct=0\n"); return; }
    if (region_struct->free==1) { printf("Pointer to not used, but free\n"); return; }

//    if (region_struct->tag_region!=0) { update_or_create_chunks_from_region_tags(region_struct); }  //update and/or create chunks from nbt tree if exists....

    if (region_struct->region_file_header!=0) {      //binary region file in memory. Check if something changed. If not return. If no binary region file in mem, create.
        if (!(region_struct->one_or_more_columns_binary_changed)) {
            printf("Not changed\n");
            return;  //nothing changed. Leave..
        }
    }
//    int region_freed=0;
    if (region_struct->region_file_header!=0) {
//hoppa
        xalloc_get_tot_mem();
//        delete[] region_struct->region_file_header;
        NBT_FREE(region_struct->region_file_header);
        region_struct->region_file_header=0;
//        region_freed=1;
        xalloc_get_tot_mem();
        region_struct->binary_memory_freed=-memory_difference;
        strcpy(region_struct->status,"Updated");
    } else {
        strcpy(region_struct->status,"New");
    }

    uint8_t** columns_binary=(uint8_t**)region_struct->columns_binary;
    unsigned char* nbt_columns_tag_changed=region_struct->nbt_columns_tag_changed;
    unsigned char* columns_binary_changed=region_struct->columns_binary_changed;
    unsigned int* columns_binary_lenght=region_struct->columns_binary_lenght;
    ChunkDataHeader* header_chunk=region_struct->header_chunk;
    RegionFileHeader* region_header=&(region_struct->region_header);
    ChunkTimestamp* timestamps=region_header->timestamps;
    ChunkLocation* locations=region_header->locations;
    size_t size;

	int	region;
    uint8_t* pointer_to_mem;

    RegionFileHeader* header=&(region_struct->region_header);
    int			i;
    size_t length;

    int chunk_count=0;
    int cnt;
    cnt=0;
    unsigned int	offset_block=0;
    unsigned int	offset;

    for (i = 0; i < CHUNKS_PER_REGION; i++)
    {
//        size_t size=0;

        if (columns_binary[i]!=0) {
            unsigned char sector_count;
            chunk_count++;

            sector_count=locations[i].sector_count;

            header->locations[i].offset[0]=(((2 + offset_block) & 0x00FF0000) >> 16) & 0xFF;
            header->locations[i].offset[1]=(((2 + offset_block) & 0x0000FF00) >> 8) & 0xFF;
            header->locations[i].offset[2]=(2 + offset_block) & 0xFF;
            header->locations[i].sector_count=sector_count;

            offset_block+=sector_count;

        } else {
            header_chunk[i].length[0]=0;
            header_chunk[i].length[1]=0;
            header_chunk[i].length[2]=0;
            header_chunk[i].length[3]=0;
            header->locations[i].offset[0]=0;
            header->locations[i].offset[1]=0;
            header->locations[i].offset[2]=0;
            header->locations[i].sector_count=0;
            header->timestamps[i].timestamp=0;
            header_chunk[i].compression_type = 0;
        }
    } // i



//hoppa
    xalloc_get_tot_mem();

//    pointer_to_mem = new uint8_t [sizeof(RegionFileHeader) + (offset_block)*4096];
    pointer_to_mem=(uint8_t*) NBT_MALLOC(sizeof(RegionFileHeader) + (offset_block)*4096);
    for (uint8_t* m=(uint8_t*)pointer_to_mem; m<(uint8_t*)(sizeof(RegionFileHeader) + (offset_block)*4096); m++) *m=0;
    region_struct->region_file_header=(RegionFileHeader*)pointer_to_mem;
    xalloc_get_tot_mem();

    region_struct->binary_memory_alloc=memory_difference;

    NBT_MEMCPY(pointer_to_mem , header, sizeof(RegionFileHeader));
    size=sizeof(header);

    for (i = 0; i < CHUNKS_PER_REGION; i++)
    {
        offset = (65536 * header->locations[i].offset[0]) + (256 * header->locations[i].offset[1]) + header->locations[i].offset[2];
        length = (16777216 * header_chunk[i].length[0]) + (65536 * header_chunk[i].length[1]) + (256 * header_chunk[i].length[2]) + header_chunk[i].length[3];
        if (offset+length>(offset_block+2)*4096) {
            printf("error: offset+length>offset_block*4096\n");
            printf("error: offset+length=%d\n",offset+length);
            printf("error: offset_block*4096=%d\n",offset_block*4096);
        }
        if (offset!=0) {
            NBT_MEMCPY(pointer_to_mem+offset*4096 , &(header_chunk[i]) , sizeof(ChunkDataHeader) );
            NBT_MEMCPY(pointer_to_mem+offset*4096 + sizeof(ChunkDataHeader) , columns_binary[i] , length -1 );  ////????????????????
            size=offset*4096 + ((int)((sizeof(ChunkDataHeader) + length)/4096) + 1)*4096;      // -1 +1 get nuts!!!
            tot_chunks_written_to_regionfiles++;
        }
    }
    num_chunks+=chunk_count;
//    region_struct->region_file_header=(RegionFileHeader*)pointer_to_mem;
    region_struct->size=size;
    region_struct->one_or_more_columns_binary_changed=0;
    region_struct->binary_changed=1;
    tied_total=tied_total+tied;
    list_region(region_struct);
}

int replace_string(char *str, char *orig, char *rep)
{
    char buffer[strlen(str)+1000];
    char *p;
    if(!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
        return false;
    strncpy(buffer, str, p-str); // Copy characters from 'str' start to 'orig' st$
    buffer[p-str] = '\0';
    sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));
    strcpy(str,buffer);
    return true;
}

void print_tags(char* directory) {
        if (RESET_TIME) { tied=0.0;tied_total=0.0; }
        print_header=1;
        StartCounter();
        printf("%6.1f %6.3f ",tied_total,0.0);
        printf("PRINT NBT(S) TO TXT:\n");
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            if (region_struct->free==0) {
                tied=GetCounterNanoseconds();
                print_region_from_tags(region_struct,directory);
                tied_total=tied_total+tied;
            }
        }
        tied=GetCounterNanoseconds();
        tied_total=tied_total+tied;
        list_world(world,-1);
        printf("\r%6.1f %6.3f ",tied_total,tied);
        printf("PRINTED\n");
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
//        system("timeout 3 >nul");
}


// create nbt.txt file from region set of chunks
void print_chunks(char* directory) {
        if (RESET_TIME) { tied=0.0;tied_total=0.0; }
        print_header=1;
        StartCounter();
        tot_chunks_written=0;
        printf("%6.1f %6.3f ",tied_total,tied);
        printf("PRINT REGION NBT(S) MADE FROM REGION CHUNKS TO TXT:\n");
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            if (region_struct->free==0) {
                tied=GetCounterNanoseconds();
                print_region_from_chunks(region_struct,directory);
                tied_total=tied_total+tied;
            }
        }
        tied=GetCounterNanoseconds();
        tied_total=tied_total+tied;
        list_world(world,-1);
        printf("\r%6.1f %6.3f ",tied_total,tied);
        printf("PRINTED: ");
        printf("Total number of chunks printed=%u\n",tot_chunks_written);
        tot_chunks_written=0;
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
//        system("timeout 3 >nul");
}

void tags_to_chunks() {
        if (RESET_TIME) { tied=0.0;tied_total=0.0; }
        print_header=1;
        StartCounter();
        printf("%6.1f %6.3f ",tied_total,tied);
        printf("UPDATING CHUNKS FROM NBT TAG(S):\n");
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            if (region_struct->free==0) {
                if (region_struct->tag_region!=0 && (rand()%2)==0) {  //change halve region files
                    int r1=rand()%32;                                   //change 1, 2 or all columns
                    for (int c=0; c<1024; c++) {
                        if (region_struct->tag_region->tag_compound.value[0]->tag_int_array.value[c]>0) {
                            if ((rand()%r1)==0) {
                                region_struct->nbt_columns_tag_changed[c]=1;
                                region_struct->one_or_more_columns_binary_changed=1;
                            }
                        }
                    }

                }
            }
        }
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            if (region_struct->free==0) {
                tied=GetCounterNanoseconds();
                update_or_create_chunks_from_region_tags(region_struct);
                tied_total=tied_total+tied;
            }
        }
        list_world(world,-1);
        tied=GetCounterNanoseconds();
        tied_total=tied_total+tied;
        xalloc_stats_quiet=1;
        xalloc_stats();
        printf("\r%6.1f %6.3f ",tied_total,tied);
        printf("UPDATED: ");
        printf("Total number of chunks written=%u\n",tot_chunks_written);
        tot_chunks_written=0;
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
//        system("timeout 3 >nul");
}

void chunks_to_tags() {
        if (RESET_TIME) { tied=0.0;tied_total=0.0; }
        print_header=1;
        tot_chunks_appended=0;
        StartCounter();
        printf("%6.1f %6.3f ",tied_total,tied);
        printf("UPDATING NBT TAG(S) FROM CHUNK(S):\n");
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            if (region_struct->free==0) {
                tied=GetCounterNanoseconds();
                chunks_to_tag(region_struct);
                tied_total=tied_total+tied;
            }
        }
        list_world(world,-1);
        tied=GetCounterNanoseconds();
        tied_total=tied_total+tied;
        xalloc_stats_quiet=1;
        xalloc_stats();
        printf("\r%6.1f %6.3f ",tied_total,tied);
        printf("UPDATED: ");
        printf("Total number of tags extracted=%u\n",tot_chunks_appended);
        tot_chunks_written=0;
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
//        system("timeout 3 >nul");
}



void chunks_to_mca() {
        if (RESET_TIME) { tied=0.0;tied_total=0.0; }
        print_header=1;
        printf("%6.1f %6.3f ",tied_total,tied);
        printf("CREATING REGION MCA FILE(S) FROM CHUNKS:\n");
        tot_chunks_written_to_regionfiles=0;
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            if (region_struct->free==0) {
                region_struct->one_or_more_columns_binary_changed=1;
            }
        }
        StartCounter();
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            if (region_struct->free==0) {
                tied=GetCounterNanoseconds();
                chunks_to_memory_mca(region_struct);
                tied_total=tied_total+tied;
            }
        }
        list_world(world,-1);
        tied=GetCounterNanoseconds();
        tied_total=tied_total+tied;
        xalloc_stats_quiet=1;
        xalloc_stats();
        printf("\r%6.1f %6.3f ",tied_total,tied);
        printf("UPDATED: ");
        printf("Total number of chunks written=%u\n",tot_chunks_written_to_regionfiles);
        tot_chunks_written_to_regionfiles=0;
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
//        system("timeout 3 >nul");
}

void  tags_to_mca() {
        if (RESET_TIME) { tied=0.0;tied_total=0.0; }
        print_header=1;
        StartCounter();
        printf("%6.1f %6.3f ",tied_total,tied);
        printf("CREATE REGION MCA FILE FROM NBT TAGS:\n");
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            if (region_struct->free==0) {
                tied=GetCounterNanoseconds();
                nbt_to_chunks_to_memory_mca(region_struct);
                tied_total=tied_total+tied;
            }
        }
        tied=GetCounterNanoseconds();
        tied_total=tied_total+tied;
        xalloc_stats_quiet=0;
        xalloc_stats();
        printf("\r%6.1f %6.3f ",tied_total,tied);
        printf("CREATED:\n");
        printf("Total number of chunks written=%u\n",tot_chunks_written);
        tot_chunks_written=0;
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
//        system("timeout 3 >nul");
}

void save_mcas() {
        if (RESET_TIME) { tied=0.0;tied_total=0.0; }
        print_header=1;
        StartCounter();
        tot_chunks_written=0;
        printf("%6.1f %6.3f ",tied_total,tied);
        printf("SAVING REGION .MCA FILE TO DISK:\n");
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            if (region_struct->free==0) {
                tied=GetCounterNanoseconds();
                save_region_binary_to_file(region_struct);
                tied_total=tied_total+tied;
            }
        }
        list_world(world,-1);
        tied=GetCounterNanoseconds();
        tied_total=tied_total+tied;
        xalloc_stats_quiet=1;
        xalloc_stats();
        printf("\r%6.1f %6.3f ",tied_total,tied);
        printf("SAVED\n");
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
        tot_chunks_written=0;
//        system("timeout 3 >nul");
}

void mca_to_chunks() {
        if (RESET_TIME) { tied=0.0;tied_total=0.0; }
        print_header=1;
        StartCounter();
        tot_chunks_written=0;
        printf("%6.1f %6.3f ",tied_total,tied);
        printf("EXTRACTING CHUNKS FROM REGION MCA FILE:\n");
        xalloc_get_tot_mem();
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            if (region_struct->free==0) {
                tied=GetCounterNanoseconds();
                int MCA_MODE_OLD=MCA_MODE;
                MCA_MODE=LOAD_CHUNKS|LOAD_BINARY;
                memory_mca_to_region_tag(region_struct);
                MCA_MODE=MCA_MODE_OLD;
                tied_total=tied_total+tied;
                xalloc_get_tot_mem();
                region_struct->columns_total_binary_memory_alloc+=memory_difference;
                list_region(region_struct);
            }
        }
        list_world(world,-1);
        tied=GetCounterNanoseconds();
        tied_total=tied_total+tied;
        xalloc_stats_quiet=1;
        xalloc_stats();
        printf("\r%6.1f %6.3f ",tied_total,tied);
        printf("EXTRACTED\n");
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
        tot_chunks_written=0;
//        system("timeout 3 >nul");
}

void erase_regions() {
        if (RESET_TIME) { tied=0.0;tied_total=0.0; }
        print_header=1;
        StartCounter();
        printf("%6.1f %6.3f ",tied_total,tied);
        printf("ERASE REGION(S) FROM WORLD:\n");
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            if (region_struct->free==0) {
                tied=GetCounterNanoseconds();StartCounter();
                erase_region(region_struct);
                list_region(region_struct);
                tied_total=tied_total+tied;
                xalloc_get_tot_mem();
                region_struct->columns_total_binary_memory_alloc+=memory_difference;
            }
        }
        list_world(world,-1);
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            int index_num=region_struct->index_num;
            for (uint8_t* m=(uint8_t*)region_struct; m<((uint8_t*)region_struct+sizeof(REGION_STRUCT)); m++) *m=0;
            region_struct->index_num=index_num;
            region_struct->free=1;
            strcpy(region_struct->status,"Empty, free");
        }

        tied=GetCounterNanoseconds();StartCounter();
        tied_total=tied_total+tied;
        xalloc_stats_quiet=1;
        xalloc_stats();
        printf("\r%6.1f %6.3f ",tied_total,tied);
        printf("REGION(S) ERASED\n");
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
        tot_chunks_written=0;
//        system("timeout 3 >nul");
}

void erase_chunks() {
        if (RESET_TIME) { tied=0.0;tied_total=0.0; }
        print_header=1;
        StartCounter();
        printf("%6.1f %6.3f ",tied_total,tied);
        printf("ERASE CHUNKS FROM WORLD:\n");
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            if (region_struct->free==0) {
                tied=GetCounterNanoseconds();
                erase_chunk(region_struct);      //erase_chunk() ... erase_chunks() .... see diff?
                list_region(region_struct);
                tied_total=tied_total+tied;
                xalloc_get_tot_mem();
                region_struct->columns_total_binary_memory_alloc+=memory_difference;
            }
        }
        list_world(world,-1);

        tied=GetCounterNanoseconds();
        tied_total=tied_total+tied;
        xalloc_stats_quiet=1;
        xalloc_stats();
        printf("\r%6.1f %6.3f ",tied_total,tied);
        printf("CHUNKS ERASED\n");
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
        tot_chunks_written=0;
//        system("timeout 3 >nul");
}

void erase_mcas() {
        if (RESET_TIME) { tied=0.0;tied_total=0.0; }
        print_header=1;
        StartCounter();
        printf("%6.1f %6.3f ",tied_total,tied);
        printf("ERASE MCA REGION BINARIES FROM WORLD:\n");
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            if (region_struct->free==0) {
                tied=GetCounterNanoseconds();
                erase_mca(region_struct);      //erase_mca() ... erase_mcas() .... see diff?
                list_region(region_struct);
                tied_total=tied_total+tied;
                xalloc_get_tot_mem();
                region_struct->columns_total_binary_memory_alloc+=memory_difference;
            }
        }
        list_world(world,-1);

        tied=GetCounterNanoseconds();
        tied_total=tied_total+tied;
        xalloc_stats_quiet=1;
        xalloc_stats();
        printf("\r%6.1f %6.3f ",tied_total,tied);
        printf("MCA REGION BINARIES ERASED\n");
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
        tot_chunks_written=0;
//        system("timeout 3 >nul");
}

void erase_tags() {
        if (RESET_TIME) { tied=0.0;tied_total=0.0; }
        print_header=1;
        StartCounter();
        printf("%6.1f %6.3f ",tied_total,tied);
        printf("ERASE NBT TAGS FROM WORLD:\n");
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            if (region_struct->free==0) {
                tied=GetCounterNanoseconds();
                erase_tag(region_struct);      //erase_tag() ... erase_tags() .... see diff? like erase_region() ... erase_world() (erase_regions(), could be renamed for beauty commission.
                list_region(region_struct);
                tied_total=tied_total+tied;
                xalloc_get_tot_mem();
                region_struct->columns_total_binary_memory_alloc+=memory_difference;
            }
        }
        list_world(world,-1);

        tied=GetCounterNanoseconds();
        tied_total=tied_total+tied;
        xalloc_stats_quiet=1;
        xalloc_stats();
        printf("\r%6.1f %6.3f ",tied_total,tied);
        printf("NBT TAGS ERASED\n");
        printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
        tot_chunks_written=0;
//        system("timeout 3 >nul");
}

void compare(char* dir1,char* dir2) {
        if (RESET_TIME) { tied=0.0;tied_total=0.0; }
        print_header=1;
        StartCounter();
        tot_chunks_written=0;
        printf("%6.1f %6.3f ",tied_total,tied);
        printf("COMPARING TXT FILES: %s  <-->  %s\n",dir1,dir2);
        for (int r=0; r<world.number_of_regions; r++) {
            REGION_STRUCT* region_struct=world.regions[r];
            if (region_struct->free==0) {
                printf("%6.1f %6.3f ",tied_total,tied);
                tied=GetCounterNanoseconds();
                char orig[1024];       sprintf(orig,"%s/%s.txt",dir1,region_struct->filename);
                char changed[1024];    sprintf(changed,"%s/%s.txt",dir2,region_struct->filename);
                while (replace_string(orig,"/","\\"));
                while (replace_string(changed,"/","\\"));
                char system_command[2048];
                sprintf(system_command,"fc %s %s /b",orig,changed);
                FILE* pfile;
                char* cut;
                pfile=popen(system_command,"rb");
                char return_string[1024];
                while (!fgets(return_string,1024,pfile)==0) {
                    while ((cut=strstr(return_string, "\n")) != NULL) *cut=' ';
                    while ((cut=strstr(return_string, "\r")) != NULL) *cut=' ';
                    printf("%s ",return_string);
                }
                fclose(pfile);
//                printf(" (%s)",system_command);
                tied=GetCounterNanoseconds();
                tied_total=tied_total+tied;
                printf("\r%6.1f %6.3f\n",tied_total,tied);
            }
        }
        tied=GetCounterNanoseconds();
        tied_total=tied_total+tied;
        xalloc_stats_quiet=1;
        xalloc_stats();
        printf("%6.1f %6.3f ",tied_total,tied);
        printf("COMPARED\n");
        if (!SILENT) printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
//        system("timeout 3 >nul");
}

void destroy(WORLD_STRUCT* world) {
        if (RESET_TIME) { tied=0.0;tied_total=0.0; }
        print_header=1;
        if (!SILENT) printf("%6.1f %6.3f ",tied_total,tied);
        if (!SILENT) printf("DESTROYING WORLD:\n");
        StartCounter();
        erase_world(*world);

        tied=GetCounterNanoseconds();
        tied_total=tied_total+tied;

        if (!SILENT) list_world(*world,0);

        xalloc_get_tot_mem();
        for (int i=0; i<world->number_of_regions; i++) {
            NBT_FREE(world->regions[i]);
            world->regions[i]=0;
        }
        world->number_of_regions=0;

        NBT_FREE(world->regions);
        xalloc_get_tot_mem();
        world->world_total_memory_freed-=memory_difference;
        world->regions=0;
        xalloc_stats_quiet=1;
        xalloc_stats();
        world->number_of_regions=0;
        char str_start[100];
        char str_diff[100];
        xalloc_get_tot_mem();
        strcpy(str_start,pretty_number(XALLOC_MEM_START));              //use strcpy, returned pointer is static char* in pretty_number, and is overwritten after second calls
        strcpy(str_diff,pretty_number(memory_total-XALLOC_MEM_START));
//        printf("Memory used=%s\n",pretty_number(memory_total-XALLOC_MEM_START));  //must be 0
        if (!SILENT) {
            if (XALLOC_MEM_START!=memory_total)
                printf("\r%6.1f %6.3f Total memory used: %s <<< !!! MEMORY LEAK (difference=%s) !!! >>> Total memory used start: %s",
                       tied_total,tied,pretty_number(memory_total),str_diff,str_start);
            else
                printf("\r%6.1f %6.3f Total memory used: %s <<<IDidMakeThat>>> Total memory used start: %s Difference=%s!!! ",
                tied_total,tied,              pretty_number(memory_total),                         str_start,      str_diff);
        }
        if (!SILENT) printf("WORLD DESTROYED\n");
        if (!SILENT) printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
//        system("timeout 3 >nul");
}

void append_regions(char* worldregiondir) {
    tied=0.0;tied_total=0.0;print_header=1;
    printf("%6.1f %6.3f ",tied_total,tied);
    printf("APENDING REGIONS:\n");


    DIR* dr = opendir(worldregiondir);
    struct dirent *de;

    printf("TO DO: ");
    while ((de = readdir(dr)) != NULL) {
        if ((strstr(de->d_name, ".mca")) != NULL) {
            printf(de->d_name);
        }
    }
    closedir(dr);
    dr = opendir(worldregiondir);
    while ((de = readdir(dr)) != NULL) {
        if ((strstr(de->d_name, ".mca")) != NULL) {
            append_mca_file_to_world(worldregiondir,de->d_name);
            if (!MC_running) kiki();
        }
    }
    closedir(dr);

    list_world(world,-1);
    printf(" %d Regions\r",world.number_of_regions);

    tied=GetCounterNanoseconds();
    tied_total=tied_total+tied;

    xalloc_stats_quiet=1;
    xalloc_stats();

    printf("%6.1f %6.3f END APPENDING: ",tied_total,tied);
    printf("Total chunks read=%u\n",tot_chunks_appended);
    tot_chunks_appended=0;
    printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
//    system("timeout 3 >nul");
//    tied_total=0;

}

long long signed int get_leak(WORLD_STRUCT world, int last) {
    size_t allocated_total=0;
    size_t binary_size_total=0;
    size_t binary_malloc_total=0;
    size_t binary_freed_total=0;
    size_t nbt_malloc_total=0;
    size_t nbt_freed_total=0;
    size_t chunks_total=0;
    size_t chunks_size_total=0;
    size_t chunks_freed_total=0;
    size_t chunks_malloc_total=0;
    if (world.regions==0) {
 //       printf(" No world, must be destroyed.\n");
        return 0;
    }
    int number_of_regions=world.number_of_regions;
    for (int i=0; i<number_of_regions; i++) {
        int num_columns;
        num_columns=0;
        size_t allocated_total_columns;     allocated_total_columns=0;
        size_t allocated_region;            allocated_region=0;
        size_t chunks_freed;                chunks_freed=0;
        size_t chunks_malloc;               chunks_malloc=0;
        REGION_STRUCT* region_struct;
        if (last!=-3) region_struct=world.regions[i];
        else region_struct=list_struct_pointer;
        if (  ((!(last<0)  ) && region_struct->free==0 ) || last==0 || last==-3 || last==-1) {
            if (region_struct!=0) {

                if (!(region_struct->region_file_header==0)) {
                    allocated_region+=region_struct->binary_memory_alloc;
                    allocated_total+= region_struct->binary_memory_alloc;
                    binary_size_total+=region_struct->size;
                }
                binary_malloc_total+=region_struct->binary_memory_alloc;
                binary_freed_total+=region_struct->binary_memory_freed;

                if (!(region_struct->tag_region==0)) {
                    allocated_region+=region_struct->nbt_tag_memory_alloc;
                    allocated_total+= region_struct->nbt_tag_memory_alloc;
                }
                nbt_malloc_total+=region_struct->nbt_tag_memory_alloc;
                nbt_freed_total+=region_struct->nbt_tag_memory_freed;

                chunks_freed=region_struct->columns_total_binary_memory_freed;
                chunks_malloc=region_struct->columns_total_binary_memory_alloc;


                for (int c=0; c<1024; c++) {
                    allocated_total_columns+=(size_t) region_struct->columns_binary_lenght[c];
                    if (region_struct->columns_binary_lenght[c]>0) { num_columns++; chunks_total++; }
                }
                if (num_columns>0) {            // must be all allocated....
                    allocated_region+=chunks_malloc;
                    allocated_total+=chunks_malloc;
                    chunks_size_total+=allocated_total_columns;
                }

                chunks_freed_total+=chunks_freed;
                chunks_malloc_total+=chunks_malloc;
            }
//                allocated_region+=allocated_total_columns;
//                allocated_total+=allocated_total_columns;
        }
    }
    if (last==0) {
        char world_used[100];   strcpy(world_used ,     pretty_number(world.world_total_memory_alloc-world.world_total_memory_freed)   );
        char regions_used[100]; strcpy(regions_used,    pretty_number(memory_total - XALLOC_MEM_START - (size_t)world.world_total_memory_alloc + (size_t)world.world_total_memory_freed )   );
        char start_used[100];   strcpy(start_used,      pretty_number(XALLOC_MEM_START )   );
        char total_used[100];   strcpy(total_used,      pretty_number(memory_total )   );

        char tot_string[200];
        if (allocated_total==memory_total - XALLOC_MEM_START - (size_t)world.world_total_memory_alloc + (size_t)world.world_total_memory_freed) {
            sprintf(tot_string,"MATCH! <IDidMakeThat> %s (TOTAL) - %s (START) - %s (WORLD) = %s (REGIONS)", total_used, start_used, world_used, regions_used );
            if (last==-1) {
                int len=245-strlen(tot_string);
                for (int stripe=0; stripe<len; stripe++) printf(" ");
                printf(tot_string); printf("\r");
            }
        }
        else
        {
            sprintf(tot_string,"\n\n!!! MEMORY LEAK !!! %s (TOTAL) - %s (START) - %s (WORLD) = %s (REGIONS)\n", total_used, start_used, world_used, regions_used );
            sprintf(tot_string,    "ALLOCATED TOTAL:    %s\n", pretty_number( allocated_total ));

            printf(tot_string); printf("\n");
            long long signed int LEAK = allocated_total - memory_total - XALLOC_MEM_START - (size_t)world.world_total_memory_alloc + (size_t)world.world_total_memory_freed;
            return LEAK;
        }
    }
    return 0;
}

void checkleak(char* message) {
    long long unsigned int leak=get_leak(world,0);
    if (leak!=0) {
        printf("\n");printf(message);printf("\n");
        system("timeout 500");
    }
}

void chunks_to_tags_erase_chunks_tags_to_chunks() {
    { tied=0.0;tied_total=0.0; }
    print_header=1;
    StartCounter();
    tot_chunks_written=0;
    printf("%6.1f %6.3f ",tied_total,tied);
    printf("EXTRACTING CHUNKS FROM REGION MCA FILE:\n");
    xalloc_get_tot_mem();
    for (int r=0; r<world.number_of_regions; r++) {
        REGION_STRUCT* region_struct=world.regions[r];
        if (region_struct->free==0) {
            tied=GetCounterNanoseconds();

            chunks_to_tag(region_struct);
            list_region(region_struct);

            erase_chunk(region_struct);
            list_region(region_struct);

            update_or_create_chunks_from_region_tags(region_struct);
            erase_tag(region_struct);
            checkleak("Aiaiaiai!!!");
            tied_total=tied_total+tied;
            xalloc_get_tot_mem();
            region_struct->columns_total_binary_memory_alloc+=memory_difference;
            list_region(region_struct);
        }
    }
    list_world(world,-1);
    tied=GetCounterNanoseconds();
    tied_total=tied_total+tied;
    xalloc_stats_quiet=1;
    xalloc_stats();
    printf("\r%6.1f %6.3f ",tied_total,tied);
    printf("EXTRACTED\n");
    printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
    tot_chunks_written=0;
//    system("timeout 3 >nul");
}

double mien_tied=0.0;
double mien_tied_total=0.0;

void DO_BATCH1(char* worldregiondir, char* filename) {

    StartCounter();

    SILENT=0;

    MCA_MODE=LOAD_NBT|LOAD_BINARY;

    REGION_STRUCT* region_struct=append_mca_file_to_world(worldregiondir,filename);

    print_region_from_tags(region_struct,"txt");

    printf("\r%6.1f %6.3f DO SOMETHING: ",tied_total,tied);
    printf(" WITH: %s%s ",region_struct->directory_path,region_struct->filename);

    nbt_to_chunks_to_memory_mca(region_struct);

    save_region_binary_to_file(region_struct);

    print_region_from_tags(region_struct,"txt");

    tied=GetCounterNanoseconds();
    tied_total+=tied;

//    list_world(world,1);
//    list_region(region_struct);
//    printf("\n");
//    SILENT=1;


    erase_region(region_struct);

    char newdir[1024];
    strcpy(newdir,worldregiondir);
    strcat(newdir,"/new");

    region_struct=append_mca_file_to_world(newdir,filename);

    print_region_from_tags(region_struct,"txt");

    char orgdir[1024];
    strcpy(orgdir,worldregiondir);
    strcat(orgdir,"/txt");

    strcat(newdir,"/txt");

    SILENT=1;
    compare(orgdir,newdir);
    SILENT=0;

//    list_region(region_struct);

//    chunks_to_tag(region_struct);

//    erase_chunk(region_struct);

//    update_or_create_chunks_from_region_tags(region_struct);


    checkleak("Aiaiaiai!!!");

//    list_world(world,-5);
    printf("\r%6.1f %6.3f ",tied_total,tied);
    printf("DID SOMETHING WITH: %s%s\n___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n",
           region_struct->directory_path,region_struct->filename);
    SILENT=1;
    print_header=0;
    erase_region(region_struct);
    destroy(&world);
    SILENT=0;
}

void DO_BATCH3(char* worldregiondir, char* filename) {

    StartCounter();

    SILENT=0;

    MCA_MODE=LOAD_NBT|LOAD_CHUNKS|LOAD_BINARY;

    REGION_STRUCT* region_struct=append_mca_file_to_world(worldregiondir,filename);

    printf("\r%6.1f %6.3f DO SOMETHING: ",tied_total,tied);
    printf(" WITH: %s%s ",region_struct->directory_path,region_struct->filename);

    nbt_to_chunks_to_memory_mca(region_struct);
    list_region(region_struct);

//    erase_chunk(region_struct);

    list_region(region_struct);

    save_region_binary_to_file(region_struct);

    tied=GetCounterNanoseconds();
    tied_total+=tied;

//    erase_region(region_struct);

    printf("\r%6.1f %6.3f ",tied_total,tied);
    print_header=0;
    erase_region(region_struct);
    SILENT=0;
    list_region(region_struct);
    SILENT=1;
    destroy(&world);
    SILENT=0;
    list_world(world,-1);
    printf("\n___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n"
           );
}

int fb=0;

void DO_BATCH2(char* worldregiondir, char* filename) {
    MCA_MODE=LOAD_CHUNKS;

    SILENT=0;
    if (fb==1) { print_header=1; fb=0; } else print_header=0;
    REGION_STRUCT* region_struct=append_mca_file_to_world(worldregiondir,filename);
    SILENT=1;

//    printf("\r%6.1f %6.3f DO SOMETHING: ",tied_total,tied);
//    printf(" WITH: %s%s ",region_struct->directory_path,region_struct->filename);

    chunks_to_memory_mca(region_struct);
    save_region_binary_to_file(region_struct);

//    checkleak("Aiaiaiai!!!");

//    get_leak(world, 0);
//    printf("\r%6.1f %6.3f ",tied_total,tied);
//    printf("DID SOMETHING WITH: %s%s\n___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n",
//           region_struct->directory_path,region_struct->filename);
    print_header=0;
    erase_region(region_struct);
//    destroy(&world);
    SILENT=0;
}


void DO_SOMETHING(char* worldregiondir, char* filename) {
    tot_chunks_written=0;
//    printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");

    DO_BATCH3(worldregiondir, filename);
//    DO_BATCH2(worldregiondir, filename);

}

void do_something_with_all(char* worldregiondir) {
    mien_tied=0.0;
    mien_tied_total=0.0;
    fb=1;

    tied=0.0;tied_total=0.0;print_header=1;
    printf("%6.1f %6.3f ",tied_total,tied);
    printf("1) DO SOMETHING WITH ALL:\n");

    DIR* dr = opendir(worldregiondir);
    struct dirent *de;

    printf("TO DO: ");
    while ((de = readdir(dr)) != NULL) {
        if ((strstr(de->d_name, ".mca")) != NULL) {
            printf(de->d_name);
        }
    }
    closedir(dr);
    dr = opendir(worldregiondir);
    while ((de = readdir(dr)) != NULL) {
        if ((strstr(de->d_name, ".mca")) != NULL) {
            DO_SOMETHING(worldregiondir,de->d_name);
            if (!MC_running) kiki();
        }
    }
    closedir(dr);


    SILENT=0;

    list_world(world,-1);
    printf(" %d Regions\r",world.number_of_regions);

    erase_regions();

    destroy(&world);

    tied=GetCounterNanoseconds();
    tied_total=tied_total+tied;

    xalloc_stats_quiet=1;
    xalloc_stats();

    printf("%6.1f %6.3f END DO SOMETHING: ",tied_total,tied);
    printf("Total chunks read=%u\n",tot_chunks_appended);
    tot_chunks_appended=0;
    printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
//    system("timeout 3 >nul");
    tied_total=0;

}

void test1() {

        do_something_with_all("/Saves/Test/region/done2");
//        do_something_with_all("Synra/region");
        SILENT=1;
        erase_regions();
        destroy(&world);
        SILENT=0;
//        list_world(world,0);
}


void test2() {
        MCA_MODE=LOAD_CHUNKS;

        append_regions("/Saves/Test/region");

//        append_regions("Synra/region");

        chunks_to_mca();
        tied_total_total+=tied_total;
        save_mcas();
        tied_total_total+=tied_total;

        RESET_TIME=1;
        SILENT=1;
        erase_regions();
        destroy(&world);
        SILENT=1;
        RESET_TIME=1;
        tied_total_total+=tied_total;
        printf("Total time=%8.2f\n",tied_total_total);
}

void test3() {
        MCA_MODE=LOAD_CHUNKS;

        append_regions("Synra/region");

        print_chunks("txt");

        erase_chunks();

        destroy(&world);

        MCA_MODE=LOAD_CHUNKS;

        append_regions("Synra/region");

        chunks_to_tags_erase_chunks_tags_to_chunks();

        chunks_to_mca();

        erase_chunks();

        save_mcas();

        erase_regions();

        destroy(&world);

        append_regions("Synra/region/new");

        print_chunks("txt");

        compare("Synra/region/new/txt","Synra/region/txt"); //proof of same nbt tags

        erase_chunks();

        destroy(&world);
}
