#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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

extern int zpipe(FILE *in, FILE *out);

static const char VersionId[] = "@(#) mca2nbt v1.00 (2014-05-05) / Hubert Tournier";

int main_mca2nbt(int argc, char *argv[])
{
	int	region;

//    printf("I am here\n");
	if (argc < 2)
	{
		fprintf(stderr, "%s\n", &VersionId[5]);
		fprintf(stderr, "Usage: %s file.mca ...\n", argv[0]);
		exit(1);
	}
//    printf("I am here 20\n");

	for (region = 1; region < argc; region++)
	{
		FILE 			*input_file,*header_output_file;
		char			output_directory_name[1024],
                        header_output_file_path[1024],
                        *p_file_extension;
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
		for (i = 0; i < CHUNKS_PER_REGION; i++)
		{
            extern void kiki();
            kiki();
            extern int monitor_off;
            monitor_off=1;
			unsigned int	offset,					length;
			ChunkDataHeader	header_chunk;

			offset = (65536 * header.locations[i].offset[0]) + (256 * header.locations[i].offset[1]) + header.locations[i].offset[2];
//            printf("header.locations[%d].sector_count=%d\n",i, header.locations[i].sector_count);

			if (offset != 0)
			{
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

				/* write the chunk as an individual deflated NBT file */
				/******************************************************/
				sprintf(deflated_output_file_path, "%s/%d.zlib.nbt", output_directory_name, i);
				if ((deflated_output_file = fopen(deflated_output_file_path, "wb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing chunk #%d\n", deflated_output_file_path, i); free(chunk); exit(15); }
				if (fwrite(chunk, length - 1, 1, deflated_output_file) != 1) { fprintf(stderr, "FATAL ERROR: unable to write chunk #%d data to file \"%s\"\n", i, deflated_output_file_path);free(chunk);exit(16);}
				fclose(deflated_output_file);

extern nbt_tag_t* read_nbt_from_memory(uint8_t* location, size_t size, int flags);


				free(chunk);
                printf("Chunk: %d %s",i,deflated_output_file_path);
//				free(chunk);

				/* (i could have used fmemopen instead of stdin, but i'm lazy tonight!) */
//                FILE *uut;
//                uut =   fmemopen(chunk, length - 1, "rb");
//				freopen(deflated_output_file_path, "rb", stdin);
//				sprintf(uncompressed_output_file_path, "%s/%d.nbt", output_directory_name, i);
//				freopen(uncompressed_output_file_path, "wb", stdout);

/*                static std::istream *currentReadStream;
//                from memory..
                  membuf sbuf(chunk, chunk + length - 1);
                  std::istream in(&sbuf);
                  currentReadStream = &in;
//                 or from file
                  std::ifstream file(filename, ios::binary);
                  currentReadStream = &file;

//                FILE* stream = fmemopen(chunk,length-1,"r");
//                fputs(stream.str(),uncompressed_output_file);

//                printf("I am here 16\n",i);
//				unlink(deflated_output_file_path);
//                printf("I am here 17\n",i);
*/
                // open compressed n.zlib.nbt output file for reading.
				if ((deflated_output_file = fopen(deflated_output_file_path, "rb")) == NULL) { fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for reading deflated\n", deflated_output_file_path); exit(17); }

                // open uncompressed n.nbt output file for writing.
				sprintf(uncompressed_output_file_path, "%s/%d.nbt", output_directory_name, i);
				if ((uncompressed_output_file = fopen(uncompressed_output_file_path, "wb")) == NULL) { fclose(deflated_output_file); fprintf(stderr, "FATAL ERROR: unable to open file \"%s\" for writing uncompressed output\n", uncompressed_output_file_path); exit(18); }

				zpipe(deflated_output_file,uncompressed_output_file);


                fclose(deflated_output_file);
                fclose(uncompressed_output_file);
                printf(" %s\n",uncompressed_output_file_path);
			}
		}
		fclose(input_file);
	}
}

