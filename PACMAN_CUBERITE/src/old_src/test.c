#define SFML_STATIC
#undef UNICODE
#include <errno.h>

#include <stdio.h>
#define NBT_IMPLEMENTATION
//#define NBT_OWN_ZLIB
#include "nbt.h"
#define NBT_BUFFER_SIZE 100000
#include <float.h>




static size_t reader_read(void* userdata, uint8_t* data, size_t size)
{
    return fread(data, 1, size, userdata);
}

static size_t writer_write(void* userdata, uint8_t* data, size_t size)
{
    return fwrite(data, 1, size, userdata);
}

static void print_nbt_tree_to_file(nbt_tag_t* tag, int indentation, FILE * file)
{
//    printf("Hallo 1\n");
    static int num=-1;
    int is_set=0;
    int is_what_printed=0;
//  printf("TAG TYPE=%d,(SHORT=%d)\n",tag->type,NBT_TYPE_SHORT);
    if (tag->name)
    {
        if (is_set==0)
        {
            for (int i = 0; i < indentation; i++) fprintf(file," ");
            is_set=1;
            if (num!=-1) fprintf(file,"(%d)", num);
        }
        fprintf(file,"%s:", tag->name);
        is_what_printed=1;
    } else {
        if (is_set==0)
        {
            for (int i = 0; i < indentation; i++) fprintf(file," ");
            is_set=1;
            if (num!=-1) fprintf(file,"(%d)", num);
        }
        indentation+=7;
        fprintf(file,"Entries:", tag->name);
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
        fprintf(file," %.*e\n", DBL_DECIMAL_DIG, tag->tag_double.value);
//        fprintf(file," %f", tag->tag_double.value);
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
        if (is_what_printed)
        {
            fprintf(file,"(%d)\r\n",tag->tag_list.size);
            is_what_printed=0;
//            if (num!=-1) fprintf(file,"(%d)", num);
        }
        for (size_t i = 0; i < tag->tag_list.size; i++)
        {
            num=i;
            char val[20];
            sprintf(val,"%d",tag->tag_list.size);
            int len=strlen(val);
            sprintf(val,"%d",i);
            len=len-strlen(val);
            print_nbt_tree_to_file(tag->tag_list.value[i], indentation + tag->name_size + 4 +len,file);
//            print_nbt_tree_to_file(tag->tag_list.value[i], indentation + tag->name_size + 2,file);
        }
        break;
    }
    case NBT_TYPE_COMPOUND:
    {
        if (is_what_printed)
        {
            fprintf(file,"(%d)\r\n",tag->tag_compound.size);
            is_what_printed=0;
//            if (num!=-1) fprintf(file,"(%d)", num);
        }

        for (size_t i = 0; i < tag->tag_compound.size; i++)
        {
            num=i;
            char val[20];
            sprintf(val,"%d",tag->tag_compound.size);
            int len=strlen(val);
            sprintf(val,"%d",i);
            len=len-strlen(val);
            print_nbt_tree_to_file(tag->tag_compound.value[i], indentation + tag->name_size + 4 +len,file);
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
        printf(" %.*e\n", DBL_DECIMAL_DIG, tag->tag_double.value);
//        printf("%f", tag->tag_double.value);
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

void write_nbt_file(const char* name, nbt_tag_t* tag, int flags)
{

    FILE* file = fopen(name, "wb");

    nbt_writer_t writer;

    writer.write = writer_write;
    writer.userdata = file;

    nbt_write(writer, tag, flags);

    fclose(file);
}

extern struct stat stat_buffer;

int main_nbt_one(char* filename_in, char* out_file, int nbt_type);

int main_nbt()
{

    // Example 1: Loading an NBT file from disk.

//1    printf("Reading Example 1:\n");

//  nbt_tag_t* tag = read_nbt_file("0.nbt.zlib", NBT_PARSE_FLAG_USE_ZLIB);
//  nbt_tag_t* tag = read_nbt_file("0.nbt", NBT_PARSE_FLAG_USE_RAW);
//  nbt_tag_t* tag = read_nbt_file("0.nbt.zlib", NBT_PARSE_FLAG_USE_ZLIB);
//  nbt_tag_t* tag = read_nbt_file("bigtest_gzip.nbt", NBT_PARSE_FLAG_USE_GZIP);


        if (mkdir("r.0.0.test") != 0)
        {
            if (errno != EEXIST)
            {
                fprintf(stderr, "FATAL ERROR: unable to create the destination directory r.0.0.test Reason: %s\n",  sys_errlist[errno]);
                exit(3);
            }
        }
         for (int t=0; t<1024; t++)
        {
            char filename[100];
//            sprintf(filename,"r.0.0/%d.nbt",t);
            sprintf(filename,"r.0.0/%d.zlib.nbt",t);

            if (stat(filename,&stat_buffer)==0)
            {
//                nbt_tag_t* tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_RAW);
                nbt_tag_t* tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_ZLIB);

                sprintf(filename,"r.0.0.test/%d.nbt",t);
                write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_RAW);

                sprintf(filename,"r.0.0.test/%d.gzip.nbt",t);
                write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_GZIP);

                sprintf(filename,"r.0.0.test/%d.zlib.nbt",t);
                write_nbt_file(filename, tag, NBT_WRITE_FLAG_USE_ZLIB);

                sprintf(filename,"r.0.0/%d.txt",t);
                FILE *textfile=fopen(filename,"wb");
                if (!textfile==NULL) {
                    print_nbt_tree_to_file(tag, 0, textfile);
                    fclose(textfile);
                }
                nbt_free_tag(tag);

                sprintf(filename,"r.0.0/%d.zlib.nbt",t);
                tag = read_nbt_file(filename, NBT_PARSE_FLAG_USE_ZLIB);
                sprintf(filename,"r.0.0/%d.zlib.txt",t);
                textfile=fopen(filename,"wb");
                if (!textfile==NULL) {
                    print_nbt_tree_to_file(tag, 0, textfile);
                    fclose(textfile);
                }
                nbt_free_tag(tag);

    //            free(tag);
    //            print_nbt_tree(tag, 2);
            }
        }



//  nbt_tag_t* tag = read_nbt_file("r.0.0/0.nbt", NBT_PARSE_FLAG_USE_RAW);
//  nbt_tag_t* tag = read_nbt_file("r.0.0/0.nbt.zlib", NBT_PARSE_FLAG_USE_ZLIB);
//  nbt_tag_t* tag = read_nbt_file("r.0.0/0.nbt", NBT_PARSE_FLAG_USE_RAW);


    printf("Append Example:\n");
    nbt_tag_t* tag_level = nbt_new_tag_compound();
    nbt_set_tag_name(tag_level, (char*)"Level", strlen("Level"));

    nbt_tag_t* tag_longtest = nbt_new_tag_long(0x7fffffffffffffff);
    nbt_set_tag_name(tag_longtest, "longTest", strlen("longTest"));

    nbt_tag_t* tag_shorttest = nbt_new_tag_short(0x7fff);
    nbt_set_tag_name(tag_shorttest, "shortTest", strlen("shortTest"));

    nbt_tag_t* tag_stringtest = nbt_new_tag_string("HELLO WORLD THIS IS A TEST STRING!", strlen("HELLO WORLD THIS IS A TEST STRING!"));
    nbt_set_tag_name(tag_stringtest, "stringTest", strlen("stringTest"));

    nbt_tag_t* tag_doubletest = nbt_new_tag_double(0.12345678901234);
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

    main_nbt_one("r.0.0.test/0.nbt",         "r.0.0.test/0.txt",        NBT_WRITE_FLAG_USE_RAW);
    main_nbt_one("r.0.0.test/0.gzip.nbt",    "r.0.0.test/0.gzip.txt",   NBT_WRITE_FLAG_USE_GZIP);
    main_nbt_one("r.0.0.test/0.zlib.nbt",    "r.0.0.test/0.zlib.txt",       NBT_WRITE_FLAG_USE_ZLIB);

    return 0;
}


int main_nbt_one(char* filename_in, char* out_file, int nbt_type)
{
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
