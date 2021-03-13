#include <stdio.h> //first for fast console output.
#include <conio.h>

#include <windows.h>
#include <sys/stat.h>
#include <map>
#include <string>
#include <dirent.h>
#include <vector>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>

#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SFML/OpenGL.hpp>

sf::RenderTexture MinecraftTexture;
sf::Sprite MinecraftSprite;

using namespace std;

extern bool file_exists(const char* filename);

extern int replace_str(char* str, char* orig, char* rep);

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s)
{
    return rtrim(ltrim(s));
}

struct json_list {
//    std::string parent;
    std::vector<std::string> texture_kind;
    std::vector<std::string> texture_block;
    int num_used=0;
    std::vector<int> block_or_item; // 0=blocks 1=items
};

struct model_list {
    std::map<std::string, int> models;
};

struct block_list {
    std::string Item;
    std::string Description;
    std::string IDName;
    int ID;
    int DataValue;
    std::map<std::string, struct model_list> variant;

    bool operator < (const block_list &B) const
    {
        if (ID != B.ID) return ID < B.ID;
        return DataValue < B.DataValue;
    }
};


struct IdDataColor_list {
    int r;
    int g;
    int b;
    int tc_x;
    int tc_y;
    std::string texture_name;
};

std::map<int, struct IdDataColor_list> IdDataColor_map;
std::map<int, struct IdDataColor_list> item_IdDataColor_map;

void make_colors_from_blocks()
{
    FILE* names;
    std::vector<struct block_list> names_list;
    if ((names = fopen("../minecraft/names.txt","r"))!=NULL)
    {
        char line[200];
        struct block_list one_block;
        int l=1;
        while (fgets(line,200,names)!=NULL)
        {
            char Item[100];
            char Description[100];
            char IDName[100];
            int ID;
            int DataValue;
            int num=sscanf(line, "\"%100[^\"]\",\"%199[^\"]\",\"%199[^\"]\",\"%d\",\"%d\"", Item, Description, IDName, &ID, &DataValue);
            if (num!=5)
                printf("Error/Warning: line %d : %s\n",l,line);
            replace_str(Item,(char*)"light gray",(char*)"silver");
            replace_str(Item,(char*)"polished",(char*)"smooth");
            one_block.Item=Item;
            one_block.Description=Description;
            one_block.IDName=IDName;
            one_block.ID=ID;
            one_block.DataValue=DataValue;
            names_list.push_back(one_block);
            l++;
        }
        fclose(names);
    }
    else
    {
        printf("Can not open %s\n","../minecraft/names.txt");
    }
    sort(names_list.begin(), names_list.end());

//    FILE* HOPPA=fopen("names.srt","w");
    for (auto u : names_list)
    {
//        printf("ID=\"%d\",DataValue=\"%d\",Item=\"%s\",Description=\"%s\",IDName=\"%s\"\n",u.ID,u.DataValue,u.Item.c_str(),u.Description.c_str(),u.IDName.c_str());
//        fprintf(HOPPA,"\"%s\",\"%s\",\"%s\",\"%d\",\"%d\"\n",u.Item.c_str(),u.Description.c_str(),u.IDName.c_str(),u.ID,u.DataValue);
//        printf("\"%s\",\"%s\",\"%s\",\"%d\",\"%d\"\n",u.Item.c_str(),u.Description.c_str(),u.IDName.c_str(),u.ID,u.DataValue);
    }
//    fclose(HOPPA);

    DIR* dr2;
    struct dirent *de2;

    std::map<std::string,int> texture_block_map;
    std::map<std::string,int>::iterator it_texture_block_map;

    dr2 = opendir("../minecraft/blocks");
    std::string filename;
    std::string block;
    std::string extension;

    while ((de2 = readdir(dr2)) != NULL)
    {
        filename=de2->d_name;
        if (filename.find_last_of(".") != std::string::npos)
            block=filename.substr(0,filename.find_last_of("."));
        else
            block="";
        std::string::size_type idx=filename.rfind('.');
        if(idx != std::string::npos)
            extension = filename.substr(idx+1);
        else
            extension="";
        for(auto& c : extension)
            c = tolower(c);
        if (extension=="png")
        {
//            texture_block.push_back(filename);
            texture_block_map.insert(std::make_pair(block,0));
        }
    }
    closedir(dr2);
//    for (auto u : texture_block_map) {
//        printf("../minecraft/blocks/%s\n",u.first.c_str());
//    }

    std::map<std::string,int> texture_item_map;
    std::map<std::string,int>::iterator it_texture_item_map;

    dr2 = opendir("../minecraft/items");
    std::string item;

    while ((de2 = readdir(dr2)) != NULL)
    {
        filename=de2->d_name;
        if (filename.find_last_of(".") != std::string::npos)
            item=filename.substr(0,filename.find_last_of("."));
        else
            item="";
        std::string::size_type idx=filename.rfind('.');
        if(idx != std::string::npos)
            extension = filename.substr(idx+1);
        else
            extension="";
        for(auto& c : extension)
            c = tolower(c);
        if (extension=="png")
        {
//            texture_block.push_back(filename);
            texture_item_map.insert(std::make_pair(item,0));
        }
    }
    closedir(dr2);
//    for (auto u : texture_item_map) {
//        printf("../minecraft/items/%s\n",u.first.c_str());
//    }




    std::vector<struct block_list>::iterator it_names_list;

    std::map<std::string, int> model_variants_map;
    std::map<std::string, int>::iterator it;


    std::map<std::string, int> block_filenames_map;

    for (it_names_list = names_list.begin(); it_names_list != names_list.end(); it_names_list++)
    {
        char Item[100];
        strcpy(Item,it_names_list->Item.c_str());
        while (replace_str(Item,(char*)" ",(char*)"_"));
        it_names_list->Item=Item;
        bool exists=false;
        std::string blockstates_filename="../minecraft/blockstates/" + it_names_list->Item + ".json";
        std::string filename;
        if (file_exists(blockstates_filename.c_str()))
        {
//            printf("ID=\"%d\",DataValue=\"%d\",Item=\"%s\",IDName=\"%s\"\n",it_names_list->ID,it_names_list->DataValue,it_names_list->Item.c_str(),it_names_list->IDName.c_str());
//            printf("\tBLOCKSTATES= \"%s\" exists\n",blockstates_filename.c_str());
            exists=true;
            filename=it_names_list->Item;
        }
        else
        {
            char IDName[100];

            int num=sscanf(it_names_list->IDName.c_str(), "(minecraft:%100[^)])",IDName);
            if (num==1)
            {
                blockstates_filename="../minecraft/blockstates/" + std::string()+IDName + ".json";
                if (file_exists(blockstates_filename.c_str()))
                {
//                    printf("ID=\"%d\",DataValue=\"%d\",Item=\"%s\",IDName=\"%s\"\n",it_names_list->ID,it_names_list->DataValue,it_names_list->Item.c_str(),it_names_list->IDName.c_str());
//                    printf("\tBLOCKSTATES= \"%s\" exists\n",blockstates_filename.c_str());
                    exists=true;
                    filename=std::string()+IDName;
                }
                else
                {
//                    printf("\tBLOCKSTATES NOT FOUND\n",blockstates_filename.c_str());
                }
            }
            else
            {
                printf("Error in IDName : %s\n",it_names_list->IDName.c_str());
            }
        }
        if (exists)
        {
            FILE* json_file;
            if ((json_file = fopen(blockstates_filename.c_str(),"r"))!=NULL)
            {
                char line[200];
                while (fgets(line,200,json_file)!=NULL)
                {
//                    printf(line);
                    bool ready=false;
                    std::string strline=ltrim(line);
                    if (strline.find("\"variants\": {") != std::string::npos)
                    {
//                        printf("\tTEXTURES":)
                        while (fgets(line,200,json_file)!=NULL)
                        {
                            std::string strline=ltrim(line);
//                            printf(line);
                            if (strline.find("}") == 0)
                            {
//                                printf(line);
                                ready=true;
                                break;
                            }
                            else
                            {
                                if (strline.find(": [") != std::string::npos)
                                {
                                    char variant[200];

                                    sscanf(strline.c_str(), "\"%199[^\"]\": [", variant );
                                    while (fgets(line,200,json_file)!=NULL)
                                    {
                                        std::string strline=ltrim(line);
                                        if (strline.find("]") == 0)
                                        {
                                            //                                printf(line);
//                                            ready=true;
                                            break;
                                        }
                                        else
                                        {
                                            if (strline.find("\{ \"model\": ") != std::string::npos)
                                            {
                                                char block_filename[200];
                                                sscanf(strline.c_str(), "{ \"model\": \"%199[^\"]\"", block_filename );

                                                std::map<std::string, struct model_list>::iterator it_variant;
                                                it_variant = it_names_list->variant.find(variant);
                                                if ( it_variant == it_names_list->variant.end() )
                                                {
//                                                    printf("\t\t \"VARIANT='%s'\"\n",variant,block_filename);

                                                    struct model_list one_model_list;
                                                    one_model_list.models.insert(std::make_pair(block_filename,1));
                                                    it_names_list->variant.insert(std::make_pair(variant,one_model_list));
//                                                    printf("\t\t\t MODEL=\"%s.json\"\n",block_filename);

                                                }
                                                else
                                                {
                                                    std::map<std::string, int>::iterator it_model_list;
//hoe
                                                    it_model_list = it_variant->second.models.find(block_filename);
                                                    if ( it_model_list == it_variant->second.models.end() )
                                                    {
                                                        it_variant->second.models.insert(std::make_pair(block_filename,1));
//                                                        printf("\t\t\t MODEL=\"%s.json\"\n",block_filename);
                                                    }
                                                    else
                                                    {
                                                        it_model_list->second++;
                                                    }
                                                }

                                                it = model_variants_map.find(std::string()+variant);
                                                if ( it != model_variants_map.end() )
                                                {
                                                    it->second++;
                                                }
                                                else
                                                {
                                                    model_variants_map.insert(std::make_pair(std::string()+variant,1));
                                                }

                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    if (strline.find("{ \"model\": ") != std::string::npos)
                                    {
                                        char block_filename[200];
                                        char variant[200];
                                        sscanf(strline.c_str(), "\"%199[^\"]\": { \"model\": \"%199[^\"]\"", variant, block_filename );
                                        //                                    printf("\t\t variant=%s TEXTURE=%s\n",variant,block_filename);
                                        //                                long csize = std::remove(line, line + strlen(line), '\n') - line;
                                        //                                line[csize] = 0; // optional

                                        //                                printf("\t\t%s (TEXTURE)\n",line);
                                        //                                printf("\t\t variant=%s\t\tFILENAME=%s\n",variant,block_filename);


                                        it = block_filenames_map.find(block_filename);
                                        if ( it != block_filenames_map.end() )
                                        {
                                            it->second++;
                                        }
                                        else
                                        {
                                            block_filenames_map.insert(std::make_pair(block_filename,1));
                                        }

                                        std::map<std::string, struct model_list>::iterator it_variant;
                                        it_variant = it_names_list->variant.find(variant);
                                        if ( it_variant == it_names_list->variant.end() )
                                        {
//                                            printf("\t\t \"VARIANT='%s'\"\n",variant,block_filename);

                                            struct model_list one_model_list;
                                            one_model_list.models.insert(std::make_pair(block_filename,1));
                                            it_names_list->variant.insert(std::make_pair(variant,one_model_list));
//                                            printf("\t\t\t MODEL=\"%s.json\"\n",block_filename);

                                        }
                                        else
                                        {
                                            std::map<std::string, int>::iterator it_model_list;

                                            it_model_list = it_variant->second.models.find(block_filename);
                                            if ( it_model_list == it_variant->second.models.end() )
                                            {
                                                it_variant->second.models.insert(std::make_pair(block_filename,1));
//                                                printf("\t\t\t MODEL=\"%s.json\"\n",block_filename);
                                            }
                                            else
                                            {
                                                it_model_list->second++;
                                            }
                                        }
                                        it = model_variants_map.find(std::string()+variant);
                                        if ( it != model_variants_map.end() )
                                        {
                                            it->second++;
                                        }
                                        else
                                        {
                                            model_variants_map.insert(std::make_pair(std::string()+variant,1));
                                        }
                                    }
                                }
                            }
                        }
                        if (ready)
                            break;
                    }
                }
                fclose(json_file);
//                json_texture_list.push_back(one_json);
            }
            else
            {
                printf("Can not open file %s\n",filename.c_str());
            }
        }
    }

    std::map<std::string, int> texture_types_map;

    std::map<std::string, struct json_list> json_texture_map;

    dr2 = opendir("../minecraft/block"); // models/block...
//    struct dirent *de2;
    struct json_list one_json;
//    std::string extension;
//    std::string block;

    while ((de2 = readdir(dr2)) != NULL)
    {
        filename=de2->d_name;
//        printf("FILE: minecraft/block/%s\n",filename.c_str());
        if (filename.find_last_of(".") != std::string::npos)
            block=filename.substr(0,filename.find_last_of("."));
        std::string::size_type idx=filename.rfind('.');
        if(idx != std::string::npos)
            extension = filename.substr(idx+1);
        for(auto& c : extension)
            c = tolower(c);
        if (extension=="json")
        {
//            printf("JSONNAME=%s\n",block.c_str());
            FILE* json_file;
            filename="../minecraft/block/" + filename;
//            one_json.parent=""; //who needs parents?
            if ((json_file = fopen(filename.c_str(),"r"))!=NULL)
            {
//                one_json.name=block;
                char line[200];
                bool found_parent=false;
                while (fgets(line,200,json_file)!=NULL)
                {
//                    printf(line);
                    bool ready=false;
                    std::string strline=ltrim(line);

                    if (strline.find("{   \"parent\": \"") != std::string::npos)
                    {
//                        char parent[200];
//                        sscanf(strline.c_str(), "{   \"parent\": \"block/%199[^\"]\"", parent);
//                        one_json.parent=parent;
//                        printf("file=%s  parent=%s  line=%s\n",filename.c_str(),parent,line );
                        found_parent=true;
                    }
                    else if (strline.find("\"parent\": \"") != std::string::npos)
                    {
//                        char parent[200];
//                        sscanf(strline.c_str(), "\"parent\": \"block/%199[^\"]\"", parent);
//                        one_json.parent=parent;
                        found_parent=true;
//                        printf("file=%s  parent=%s  line=%s\n",filename.c_str(),parent,line );
                    }
                    if (strline.find("\"textures\": {") != std::string::npos)
                    {
//                        if (!found_parent) { //no parent found, so = parent...
//                            ready=true;
//                            break;
//                        }
//                        printf("\tTEXTURES":)
                        while (fgets(line,200,json_file)!=NULL)
                        {
                            std::string strline=ltrim(line);
                            if (strline.find("}") != std::string::npos)
                            {
//                                printf(line);
                                ready=true;
                                break;
                            }
                            else
                            {
                                char block_filename[200];
                                char kind[200];
                                char blocks[200];
//                                sscanf(strline.c_str(), "\"%199[^\"]\": \"blocks/%199[^\"]\"", kind, block_filename );
                                sscanf(strline.c_str(), "\"%199[^\"]\": \"%199[^/]/%199[^\"]\"", kind, blocks, block_filename );
//                                long csize = std::remove(line, line + strlen(line), '\n') - line;
//                                line[csize] = 0; // optional

//                                printf("\t\t%s (TEXTURE)\n",line);
//                                printf("\t\t KIND=%s\t\tFILENAME=%s\n",kind,block_filename);
//                                printf(blocks);
//                                if (strcmp(blocks,"items")) printf("FOUND ITEMS IN BLOCK !!!!!!!!!!!!!!!!!!!!!!!!\n");
                                if (strcmp(blocks,"blocks")==0 || strcmp(blocks,"items")==0)
                                {

                                    it = texture_types_map.find(kind);
                                    if ( it != texture_types_map.end() )
                                    {
                                        it->second++;
                                    }
                                    else
                                    {
                                        texture_types_map.insert(std::make_pair(kind,1));
                                    }

//jojo
/*
                                    it = block_filenames_map.find(block_filename);
                                    if ( it != block_filenames_map.end() )
                                    {
                                        it->second++;
                                    }
                                    else
                                    {
                                        block_filenames_map.insert(std::make_pair(block_filename,1));
                                    }
*/
                                    one_json.texture_kind.push_back(std::string()+kind);
                                    one_json.texture_block.push_back(std::string()+block_filename);
                                    if (strcmp(blocks,"blocks")==0)
                                        one_json.block_or_item.push_back(0);
                                    else
                                        one_json.block_or_item.push_back(1);

                                    it_texture_block_map=texture_block_map.find(std::string()+block_filename);
                                    if ( it_texture_block_map != texture_block_map.end() )
                                    {
                                        it_texture_block_map->second++;
                                    }
                                }// else printf(strline.c_str());
                            }
                        }
                        if (ready)
                            break;
                    }
                }
                fclose(json_file);
//                json_texture_list.push_back(one_json);

//                if (found_parent)
                json_texture_map.insert(std::make_pair(block,one_json));

                one_json.texture_kind.clear();
                one_json.texture_block.clear();
            }
            else
            {
                printf("Can not open file %s\n",filename.c_str());
            }
        }
    }
    closedir(dr2);


//    for (auto u : json_texture_map) {
//        std::string name=u.first;

////        std::string parent=u.second.parent;

//  //      printf("\t\t\t\t\t\t\t\t\t\t\tPARENT=\"../minecraft/block/%s\"\r", parent.c_str());
//        printf("MODEL= \"../minecraft/block/%s\"\n", name.c_str());
//        size_t text_len=u.second.texture_kind.size();
//        for (int n=0; n<text_len;n++) {
//            std::string block_filename;
//            std::string kind;
//            kind = u.second.texture_kind[n];
//            block_filename = u.second.texture_block[n];
//            printf("\t\t\t\tTEXTURE=\"../minecraft/blocks/%s.png\"\r",block_filename.c_str());
//            printf("\tTYPE='%s'\n",kind.c_str());
//        }
//    }




    std::map<std::string, struct json_list> item_texture_map;

    dr2 = opendir("../minecraft/item"); // models/block...
//    struct dirent *de2;
//    struct json_list one_json;
//    std::string extension;
//    std::string block;

    while ((de2 = readdir(dr2)) != NULL)
    {
        filename=de2->d_name;
//        printf("FILE: minecraft/item/%s\n",filename.c_str());
        if (filename.find_last_of(".") != std::string::npos)
            item=filename.substr(0,filename.find_last_of("."));
        std::string::size_type idx=filename.rfind('.');
        if(idx != std::string::npos)
            extension = filename.substr(idx+1);
        for(auto& c : extension)
            c = tolower(c);
        if (extension=="json")
        {
//            printf("JSONNAME=%s\n",block.c_str());
            FILE* json_file;
            filename="../minecraft/item/" + filename;
//            one_json.parent=""; //who needs parents?
            if ((json_file = fopen(filename.c_str(),"r"))!=NULL)
            {
//                one_json.name=block;
                char line[200];
                bool found_parent=false;
                while (fgets(line,200,json_file)!=NULL)
                {
//                    printf(line);
                    bool ready=false;
                    std::string strline=ltrim(line);

                    if (strline.find("{   \"parent\": \"") != std::string::npos)
                    {
//                        char parent[200];
//                        sscanf(strline.c_str(), "{   \"parent\": \"block/%199[^\"]\"", parent);
//                        one_json.parent=parent;
//                        printf("file=%s  parent=%s  line=%s\n",filename.c_str(),parent,line );
                        found_parent=true;
                    }
                    else if (strline.find("\"parent\": \"") != std::string::npos)
                    {
//                        char parent[200];
//                        sscanf(strline.c_str(), "\"parent\": \"block/%199[^\"]\"", parent);
//                        one_json.parent=parent;
                        found_parent=true;
//                        printf("file=%s  parent=%s  line=%s\n",filename.c_str(),parent,line );
                    }
                    if (strline.find("\"textures\": {") != std::string::npos)
                    {
//                        if (!found_parent) { //no parent found, so = parent...
//                            ready=true;
//                            break;
//                        }
//                        printf("\tTEXTURES":)
                        while (fgets(line,200,json_file)!=NULL)
                        {
                            std::string strline=ltrim(line);
                            if (strline.find("}") != std::string::npos)
                            {
//                                printf(line);
                                ready=true;
                                break;
                            }
                            else
                            {
                                char item_filename[200];
                                char kind[200];
                                char items[200];
//                                sscanf(strline.c_str(), "\"%199[^\"]\": \"blocks/%199[^\"]\"", kind, block_filename );
                                sscanf(strline.c_str(), "\"%199[^\"]\": \"%199[^/]/%199[^\"]\"", kind, items, item_filename );
//                                long csize = std::remove(line, line + strlen(line), '\n') - line;
//                                line[csize] = 0; // optional

//                                printf("\t\t%s (TEXTURE)\n",line);
//                                printf("\t\t KIND=%s\t\tFILENAME=%s\n",kind,block_filename);
//                                printf(blocks);
                                if (strcmp(items,"items")==0 || strcmp(items,"blocks")==0)
                                {

                                    it = texture_types_map.find(kind);
                                    if ( it != texture_types_map.end() )
                                    {
                                        it->second++;
                                    }
                                    else
                                    {
                                        texture_types_map.insert(std::make_pair(kind,1));
                                    }

                                    one_json.texture_kind.push_back(std::string()+kind);
                                    one_json.texture_block.push_back(std::string()+item_filename);
                                    if (strcmp(items,"blocks")==0)
                                        one_json.block_or_item.push_back(0);
                                    else
                                        one_json.block_or_item.push_back(1);

                                    it_texture_item_map=texture_item_map.find(std::string()+item_filename);
                                    if ( it_texture_item_map != texture_item_map.end() )
                                    {
                                        it_texture_item_map->second++;
                                    }
                                }// else printf(strline.c_str());
                            }
                        }
                        if (ready)
                            break;
                    }
                }
                fclose(json_file);

                item_texture_map.insert(std::make_pair(item,one_json));

                one_json.texture_kind.clear();
                one_json.texture_block.clear();
            }
            else
            {
                printf("Can not open file %s\n",filename.c_str());
            }
        }
    }
    closedir(dr2);


//    for (auto u : json_texture_map) {
//        std::string name=u.first;

////        std::string parent=u.second.parent;

//  //      printf("\t\t\t\t\t\t\t\t\t\t\tPARENT=\"../minecraft/block/%s\"\r", parent.c_str());
//        printf("MODEL= \"../minecraft/block/%s\"\n", name.c_str());
//        size_t text_len=u.second.texture_kind.size();
//        for (int n=0; n<text_len;n++) {
//            std::string block_filename;
//            std::string kind;
//            kind = u.second.texture_kind[n];
//            block_filename = u.second.texture_block[n];
//            printf("\t\t\t\tTEXTURE=\"../minecraft/blocks/%s.png\"\r",block_filename.c_str());
//            printf("\tTYPE='%s'\n",kind.c_str());
//        }
//    }





    bool shut_up=true;

    std::map<std::string, struct json_list>::iterator it_json_texture_map;
    std::map<std::string, struct json_list>::iterator it_item_texture_map;
    IdDataColor_map.clear();
    item_IdDataColor_map.clear();
    FILE* best_colors=fopen("best_colors.txt","w");
    FILE* blockstates=fopen("blockstates.txt","w");
    for (it_names_list = names_list.begin(); it_names_list != names_list.end(); it_names_list++)
    {
        std::string blockstates_filename="../minecraft/blockstates/" + it_names_list->Item + ".json";
        std::string by_Item_filename="";
        std::string item_by_Item_filename="";
        bool by_Item=false;
        bool item_by_Item=false;
        if (!shut_up) printf("ID=\"%d\",DataValue=\"%d\",Item=\"%s\",Description=\"%s\",IDName=\"%s\"\n",it_names_list->ID,it_names_list->DataValue,it_names_list->Item.c_str(),it_names_list->Description.c_str(),it_names_list->IDName.c_str());
        fprintf(blockstates,"ID=\"%d\",DataValue=\"%d\",Item=\"%s\",Description=\"%s\",IDName=\"%s\"\n",it_names_list->ID,it_names_list->DataValue,it_names_list->Item.c_str(),it_names_list->Description.c_str(),it_names_list->IDName.c_str());

        int best_block_or_item=0;
        int item_best_block_or_item=0;

        if (file_exists(blockstates_filename.c_str()))
        {
            if (!shut_up) printf("BLOCKSTATES= \"%s\" exists\n",blockstates_filename.c_str());
            fprintf(blockstates,"BLOCKSTATES= \"%s\" exists\n",blockstates_filename.c_str());
        }
        else
        {
            char IDName[100];
            int num=sscanf(it_names_list->IDName.c_str(), "(minecraft:%100[^)])",IDName);
            if (num==1)
            {
                blockstates_filename="../minecraft/blockstates/" + std::string()+IDName + ".json";
                if (file_exists(blockstates_filename.c_str()))
                {
                    if (!shut_up) printf("BLOCKSTATES= \"%s\" exists (by IDName %s)\n",blockstates_filename.c_str(),it_names_list->IDName.c_str());
                    fprintf(blockstates,"BLOCKSTATES= \"%s\" exists (by IDName %s)\n",blockstates_filename.c_str(),it_names_list->IDName.c_str());
                }
                else
                {
                    it = texture_block_map.find(it_names_list->Item);
                    if ( it != texture_block_map.end() )
                    {
                        if (!shut_up) printf("BLOCKSTATES= \"%s\" DOES NOT exist (also not by IDName %s)\n",blockstates_filename.c_str(),it_names_list->IDName.c_str());
                        fprintf(blockstates,"BLOCKSTATES= \"%s\" DOES NOT exist (also not by IDName %s)\n",blockstates_filename.c_str(),it_names_list->IDName.c_str());
                        if (!shut_up) printf("\t\t\t TEXTURE=\"../minecraft/blocks/%s.png\" (FOUND BY Item in (model/)block %s)\n",it->first.c_str(),it->first.c_str());
                        fprintf(blockstates,"\t\t\t TEXTURE=\"../minecraft/blocks/%s.png\" (FOUND BY Item  in (model/)block %s)\n",it->first.c_str(),it->first.c_str());
                        by_Item_filename=it->first.c_str(); by_Item=true;
                        best_block_or_item=0;
                    }

                    it = texture_item_map.find(it_names_list->Item);
                    if ( it != texture_item_map.end() )
                    {
                        if (!shut_up) printf("BLOCKSTATES= \"%s\" DOES NOT exist (also not by IDName %s)\n",blockstates_filename.c_str(),it_names_list->IDName.c_str());
                        fprintf(blockstates,"BLOCKSTATES= \"%s\" DOES NOT exist (also not by IDName %s)\n",blockstates_filename.c_str(),it_names_list->IDName.c_str());
                        if (!shut_up) printf("\t\t\t TEXTURE=\"../minecraft/items/%s.png\" (FOUND BY Item in (model/)item %s)\n",it->first.c_str(),it->first.c_str());
                        fprintf(blockstates,"\t\t\t TEXTURE=\"../minecraft/items/%s.png\" (FOUND BY Item  in (model/)item %s)\n",it->first.c_str(),it->first.c_str());
                        item_by_Item_filename=it->first.c_str(); item_by_Item=true;
                        item_best_block_or_item=1;
                    }

                    if (!by_Item && !item_by_Item)
                    {
                        if (!shut_up) printf("BLOCKSTATES= \"%s\" DOES NOT exist (also not by IDName %s or Item %s)\n",blockstates_filename.c_str(),it_names_list->IDName.c_str(),it_names_list->Item.c_str());
                        fprintf(blockstates,"BLOCKSTATES= \"%s\" DOES NOT exist (also not by IDName %s or Item %s)\n",blockstates_filename.c_str(),it_names_list->IDName.c_str(),it_names_list->Item.c_str());
                    }
                }
            }
            else
            {
                if (!shut_up) printf("Error in IDName : %s\n",it_names_list->IDName.c_str());
                fprintf(blockstates,"Error in IDName : %s\n",it_names_list->IDName.c_str());
            }
        }
        std::map<std::string, struct model_list>::iterator it_variant;

        int variant_weight=0;
        std::string best_variant="";
        std::string best_type="";
        int best_tot=-1;
        std::string best_texture="";

        int item_variant_weight=0;
        std::string item_best_variant="";
        std::string item_best_type="";
        int item_best_tot=-1;
        std::string item_best_texture="";

        if (!by_Item && !item_by_Item) {
            for (it_variant = it_names_list->variant.begin(); it_variant != it_names_list->variant.end(); it_variant++)
            {
                std::string variant=it_variant->first;
                if (variant=="normal")                                  { variant_weight=9; }
                else if (variant=="facing=up"   && variant_weight<8)    { variant_weight=8; }
                else if (variant=="snowy=false" && variant_weight<7)    { variant_weight=7; }
                else if (variant=="axis=none"   && variant_weight<6)    { variant_weight=6; }
                else if (variant=="half=top"    && variant_weight<5)    { variant_weight=5; }
                else if (variant=="cross"       && variant_weight<4)    { variant_weight=4; }

                int type_weight=0;

                if (!shut_up) printf("\t VARIANT=\"%s\"\n",variant.c_str());
                fprintf(blockstates,"\t VARIANT=\"%s\"\n",variant.c_str());
                std::map<std::string, int>::iterator it_model_list;
                for (it_model_list = it_variant->second.models.begin(); it_model_list != it_variant->second.models.end(); it_model_list++)
                {

                    bool no_block_found=false;
                    it_json_texture_map = json_texture_map.find(it_model_list->first);
                    if ( it_json_texture_map != json_texture_map.end() )
                    {
                        if (!shut_up) printf("\t MODEL=\"../minecraft/block/%s.json\" (%dx)",it_model_list->first.c_str(),it_model_list->second);
                        fprintf(blockstates,"\t MODEL=\"../minecraft/block/%s.json\" (%dx)",it_model_list->first.c_str(),it_model_list->second);

                        if (!shut_up) printf(" model/block found ");
                        fprintf(blockstates,"  model/block found ");
                        it = block_filenames_map.find(it_model_list->first);
                        if ( it != block_filenames_map.end() ) {
                            if (!shut_up) printf("(Tot %dx)",it->second);
                            fprintf(blockstates,"(Tot %dx)",it->second);
                        }
                        if (!shut_up) printf(" \n");
                        fprintf(blockstates," \n");

                        size_t text_len=it_json_texture_map->second.texture_kind.size();
                        for (size_t n=0; n<text_len; n++)
                        {
                            std::string block_filename;
                            std::string kind;
                            int block_or_item;
                            block_or_item=it_json_texture_map->second.block_or_item[n];
                            kind = it_json_texture_map->second.texture_kind[n];
                            block_filename = it_json_texture_map->second.texture_block[n];

                            if (kind=="all") type_weight=9;
                            else if (kind=="top"     && type_weight<8) { type_weight=8; }
                            else if (kind=="up"      && type_weight<7) { type_weight=7; }
                            else if (kind=="end"     && type_weight<6) { type_weight=6; }
                            else if (kind=="overlay" && type_weight<5) { type_weight=5; }
                            else if (kind=="texture" && type_weight<4) { type_weight=4; }
                            else if (kind=="cross"   && type_weight<3) { type_weight=3; }

                            int t=strlen(kind.c_str());
                            if (!shut_up) printf("\t\t (TYPE=\"%s\")",kind.c_str());
                            fprintf(blockstates,"\t\t (TYPE=\"%s\")",kind.c_str());
                            if (!shut_up) for (int i=0; i<15-t; i++) putchar(' ');
                            for (int i=0; i<15-t; i++) fputc(' ',blockstates);
                            if (block_or_item==0) {
                                if (!shut_up) printf(" TEXTURE=\"../minecraft/blocks/%s.png\"",block_filename.c_str());
                                fprintf(blockstates," TEXTURE=\"../minecraft/blocks/%s.png\"",block_filename.c_str());
                                it_texture_block_map=texture_block_map.find(block_filename);
                                if ( it_texture_block_map != texture_block_map.end() )
                                {
                                    if (!shut_up) printf(" (exists, used %dx)",it_texture_block_map->second);
                                    fprintf(blockstates," (exists, used %dx)",it_texture_block_map->second);
                                    if (it_texture_block_map->second > best_tot) {
                                        best_tot=it_texture_block_map->second;
                                        best_variant=variant;
                                        best_type=kind;
                                        best_texture=block_filename;
                                        best_block_or_item=0;
                                    }
                                }
                            } else {
                                if (!shut_up) printf(" TEXTURE=\"../minecraft/items/%s.png\"",block_filename.c_str());
                                fprintf(blockstates," TEXTURE=\"../minecraft/items/%s.png\"",block_filename.c_str());
                                it_texture_item_map=texture_item_map.find(block_filename);
                                if ( it_texture_item_map != texture_item_map.end() )
                                {
                                    if (!shut_up) printf(" (exists, used %dx)",it_texture_item_map->second);
                                    fprintf(blockstates," (exists, used %dx)",it_texture_item_map->second);
                                    if (it_texture_item_map->second > best_tot) {
                                        best_tot=it_texture_item_map->second;
                                        best_variant=variant;
                                        best_type=kind;
                                        best_texture=block_filename;
                                        best_block_or_item=1;
                                    }
                                }
                            }

//                            if (variant_weight + type_weight > best_tot) {
//                                best_tot=variant_weight + type_weight;
//                                best_variant=variant;
//                                best_type=kind;
//                                best_texture=block_filename;
//                            }

                            if (!shut_up) printf("\n");
                            fprintf(blockstates,"\n");
                        }
                    }
                    else
                    {
                        no_block_found=true;
                        if (!shut_up) printf(" NOT FOUND!\n");
                        fprintf(blockstates," NOT FOUND!\n");
                    }
                }
            }
        } else {
            if (by_Item) best_texture=by_Item_filename;
//            if (item_by_Item) item_best_texture=item_by_Item_filename;
        }

        if (!shut_up) printf("\n");
        fprintf(blockstates,"\n");
        if (best_texture!="") {
            if (best_block_or_item==0)
                fprintf(best_colors,"BLOCK: ID=\"%d\",DataValue=\"%d\",Item=\"%s\",Description=\"%s\",IDName=\"%s\",VARIANT=\"%s\",TYPE=\"%s\",TEXTURE=\"blocks\\%s.png\"\n",
                        it_names_list->ID,it_names_list->DataValue,it_names_list->Item.c_str(),it_names_list->Description.c_str(),it_names_list->IDName.c_str(),
                        best_variant.c_str(), best_type.c_str(),best_texture.c_str());
            else
                fprintf(best_colors,"BLOCK: ID=\"%d\",DataValue=\"%d\",Item=\"%s\",Description=\"%s\",IDName=\"%s\",VARIANT=\"%s\",TYPE=\"%s\",TEXTURE=\"items\\%s.png\"\n",
                        it_names_list->ID,it_names_list->DataValue,it_names_list->Item.c_str(),it_names_list->Description.c_str(),it_names_list->IDName.c_str(),
                        best_variant.c_str(), best_type.c_str(),best_texture.c_str());
        }
/*
        if (item_best_texture!="") {
            if (item_best_block_or_item==0) fprintf(best_colors,"ITEM:  ID=\"%d\",DataValue=\"%d\",Item=\"%s\",Description=\"%s\",IDName=\"%s\",VARIANT=\"%s\",TYPE=\"%s\",TEXTURE=\"blocks\%s.png\"\n",
                    it_names_list->ID,it_names_list->DataValue,it_names_list->Item.c_str(),it_names_list->Description.c_str(),it_names_list->IDName.c_str(),
                    best_variant.c_str(), best_type.c_str(),best_texture.c_str());
            else
                fprintf(best_colors,"ITEM:  ID=\"%d\",DataValue=\"%d\",Item=\"%s\",Description=\"%s\",IDName=\"%s\",VARIANT=\"%s\",TYPE=\"%s\",TEXTURE=\"items\%s.png\"\n",
                        it_names_list->ID,it_names_list->DataValue,it_names_list->Item.c_str(),it_names_list->Description.c_str(),it_names_list->IDName.c_str(),
                        best_variant.c_str(), best_type.c_str(),best_texture.c_str());
        }
*/
        struct IdDataColor_list one_IdDataColor;

        if (best_texture!="") {
            if (best_block_or_item==0) {
                one_IdDataColor.texture_name="blocks/"+best_texture;
                IdDataColor_map.insert( std::make_pair( it_names_list->ID*16 + it_names_list->DataValue , one_IdDataColor ) );
            } else {
                one_IdDataColor.texture_name="items/"+best_texture;
                IdDataColor_map.insert( std::make_pair( it_names_list->ID*16 + it_names_list->DataValue , one_IdDataColor ) );
            }
        }
/*
        if (item_best_texture!="") {
            if (item_best_block_or_item==0) {
                one_IdDataColor.texture_name="blocks/"+best_texture;
                item_IdDataColor_map.insert( std::make_pair( it_names_list->ID*16 + it_names_list->DataValue , one_IdDataColor ) );
            } else {
                one_IdDataColor.texture_name="items/"+best_texture;
                item_IdDataColor_map.insert( std::make_pair( it_names_list->ID*16 + it_names_list->DataValue , one_IdDataColor ) );
            }
        }
*/
    }

    fclose(best_colors);
    if (!shut_up) {
        printf("MODELS:\n");
        for (it = block_filenames_map.begin(); it != block_filenames_map.end(); it++)
        {
            printf("\"block/%s.json\" (%d)\n",it->first.c_str(),it->second);
        }
        printf("\n");

        printf("BLOCK TEXTURES:\n");
        for (it = texture_block_map.begin(); it != texture_block_map.end(); it++)
        {
            printf("\"blocks/%s.png\" (%d)\n",it->first.c_str(),it->second);
        }
        printf("\n");

        printf("ITEM TEXTURES:\n");
        for (it = texture_item_map.begin(); it != texture_item_map.end(); it++)
        {
            printf("\"items/%s.png\" (%d)\n",it->first.c_str(),it->second);
        }
        printf("\n");

        printf("MODEL VARIANTS:\n");
        for (it = model_variants_map.begin(); it != model_variants_map.end(); it++)
        {
            printf("'%s' (%d)\n",it->first.c_str(),it->second);
        }
        printf("\n");

        printf("MODEL TEXTURE TYPES:\n");
        for (it = texture_types_map.begin(); it != texture_types_map.end(); it++)
        {
            printf("'%s' (%d)\n",it->first.c_str(),it->second);
        }
        printf("\n");
        printf("#include <stdio.h> first\n");
    }

    fprintf(blockstates,"MODELS:\n");
    for (it = block_filenames_map.begin(); it != block_filenames_map.end(); it++)
    {
        fprintf(blockstates,"\"block/%s.json\" (%d)\n",it->first.c_str(),it->second);
    }
    fprintf(blockstates,"\n");

    fprintf(blockstates,"BLOCK TEXTURES:\n");
    for (it = texture_block_map.begin(); it != texture_block_map.end(); it++)
    {
        fprintf(blockstates,"\"blocks/%s.png\" (%d)\n",it->first.c_str(),it->second);
    }
    fprintf(blockstates,"\n");

    fprintf(blockstates,"ITEM TEXTURES:\n");
    for (it = texture_item_map.begin(); it != texture_item_map.end(); it++)
    {
        fprintf(blockstates,"\"items/%s.png\" (%d)\n",it->first.c_str(),it->second);
    }
    fprintf(blockstates,"\n");

    fprintf(blockstates,"MODEL VARIANTS:\n");
    for (it = model_variants_map.begin(); it != model_variants_map.end(); it++)
    {
        fprintf(blockstates,"'%s' (%d)\n",it->first.c_str(),it->second);
    }
    fprintf(blockstates,"\n");

    fprintf(blockstates,"\nMODEL TEXTURE TYPES:\n");
    for (it = texture_types_map.begin(); it != texture_types_map.end(); it++)
    {
        fprintf(blockstates,"'%s' (%d)\n",it->first.c_str(),it->second);
    }
    fprintf(blockstates,"\n");
    fprintf(blockstates,"#include <stdio.h> first\n");

    fclose(blockstates);

    sf::Image construct;

    if (!shut_up) printf("Building map for all block textures max 64x64\n");

    int grid[64][64];
    for (int y=0; y<64; y++)
        for (int x=0; x<64; x++)
            grid[x][y]=0;
    sf::Image m_image;
    sf::Image blocks_image;

extern bool setShape(HWND hWnd, const sf::Image& image);
extern setTransparency(HWND hWnd, unsigned char alpha);

    blocks_image.create(1024,1024,sf::Color(0,255,255,255));
    sf::ContextSettings contextSettings(0,0,2,3,0);
    sf::RenderWindow window;
    sf::Event event;
    contextSettings.antialiasingLevel=2;
//    window.create(sf::VideoMode(blocks_image.getSize().x, blocks_image.getSize().y, 32), "BLOCKSTATES",  sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close , contextSettings);
    window.create(sf::VideoMode(blocks_image.getSize().x, blocks_image.getSize().y, 32), "Blockstates", sf::Style::None ,contextSettings);
    window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width - blocks_image.getSize().x) / 2,
                                    (sf::VideoMode::getDesktopMode().height - blocks_image.getSize().y) / 2));
    setShape(window.getSystemHandle(), blocks_image);
    setTransparency(window.getSystemHandle(), 255);
    window.setVerticalSyncEnabled(false);
    window.requestFocus();
//    sf::RenderTexture MinecraftTexture;
//    sf::Sprite MinecraftSprite;
    sf::Texture blocktexture;
    sf::Sprite blocksprite;

    MinecraftTexture.create(1024,1024);
    MinecraftTexture.clear(sf::Color(255,0,0,0));
    MinecraftSprite.setTexture(MinecraftTexture.getTexture(),true);
    MinecraftSprite.setPosition(0,0);

    HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    COORD homeCoords = { 0, 0 };
    if (!shut_up) system("CLS");
    bool first=true;



/*


    for (it_texture_block_map = texture_block_map.begin(); it_texture_block_map != texture_block_map.end(); it_texture_block_map++) {
//        std::string block_filename=it_texture_block_map->first;
        std::string filename="../minecraft/blocks/" + it_texture_block_map->first + ".png";
        bool empty_spot=false;
        if (file_exists(filename.c_str())) {
            if (m_image.loadFromFile(filename.c_str())) {




                int index_x=0;
                int index_y=0;
                bool special=false;
                bool water=false;
                int p_x=m_image.getSize().x;
                int p_y=m_image.getSize().y;
                int t_x=p_x/16;
                int t_y=p_y/16;
                if (p_x!=t_x*16 || p_y!=t_y*16) {
                    printf("Unknown texture size: %d x %d Must be dividable by 16 pixels\n", p_x, p_y);
                }

                if (!shut_up) SetConsoleCursorPosition( hStdOut, homeCoords );
                if (!shut_up) printf("Loaded %s - placing in texture map pixels=(%2d x %2d) tiles=(%d x %d)               \n",filename.c_str(),p_x,p_y,t_x,t_y);
                if (t_y>4 || t_x>1) special=true;
                if (t_y==64) water=true; //preserve first 2 columns for it

                empty_spot=false;
                while (!empty_spot) {
                    empty_spot=true;
                    if (grid[index_x][index_y]==0) {
                        if (water) {
                            if (index_x!=0 || index_y!=0) {
                                printf("Error, tiles for water taken?\n");
                                empty_spot=false;
                            } // else found col 0+1 row 0-63 for water tile
                        } else if (!special && index_x<8) {
                            empty_spot=false; //reserved for tiles width>1, length>4
                        } else if (special && (index_x>=8 || index_x<2)) {  //reserved for these (tiles width==1, length<=4)
                            empty_spot=false;
                        } else if (!special && index_x>=8) {
//                            grid[index_x][index_y]=1; // gets filled
                            break;
                        } else { //special && index_x<6
                            if (index_x<2) empty_spot=false;
                            else if (index_x==7 && t_x==2) empty_spot=false;
                            else if (t_x==2 && grid[index_x+1][index_y]!=0) empty_spot=false;
                            if (index_y + t_y > 64) empty_spot=false;
                            //empty spot! -> end loop
                        }
                    } else if (empty_spot) empty_spot=false;
                    if (empty_spot) break;
                    index_x++;
                    if (index_x==64) {
                        index_x=0;
                        index_y++;
                        if (index_y==64) {
                            empty_spot=false;
                            break;
                        }
                    }
                }
                if (empty_spot) {
                    while (window.pollEvent(event)) {
                    }
                    blocktexture.loadFromImage(m_image);
                    blocksprite.setTexture(blocktexture,true);
                    blocksprite.setPosition(index_x*16,index_y*16);
                    window.draw(blocksprite);
                    MinecraftTexture.draw(blocksprite);
                    window.display();

                    if (first) {
                        if (!shut_up) printf("col    0000000000111111111122222222223333333333444444444455555555556666\n");
                        if (!shut_up) printf("       0123456789012345678901234567890123456789012345678901234567890123\n");
                        first=false;
                    } else {
                        if (!shut_up) printf("\n\n");
                    }
                    static char c='A';
                    c++; if (c>'Z') c='A';
                    for (int y=0; y<64; y++) {
                        bool end_y=true;
                        if (y<index_y || y>=index_y+t_y) {
                            if (!shut_up) printf("\n");
                            continue;
                        }
                        if (!shut_up) printf("row %2d ",y);
                        for (int x=0; x<64; x++) {
                            if (x>=index_x+t_x) continue;
                            if (x>=index_x && x<index_x+t_x && y>=index_y && y<index_y+t_y) { //gets filled, new
                                if (grid[x][y]!=0) {
                                    if (!shut_up) printf("E"); // error...
                                } else {
                                    if (!shut_up) printf("%c",c);
                                    grid[x][y]=c;
                                }
                                end_y=false;
                            } else if (grid[x][y]==0) {
                                if (!shut_up) printf("."); //empty
                            } else {
                                if (!shut_up) printf("%c",grid[x][y]); //filled
                                end_y=false;
                            }
                        }
                        if (!shut_up) printf("\n");
                        if (end_y) break;
                    }
                    if (!shut_up) printf("Empty spot at x=%2d,y=%2d\n",index_x,index_y);
//                    getch();
                } else {
                    printf("Out of texture space? (64x64 tiles x 16x16 pixels / tile = 1024 x 1024 pixels)\n");
                    break;
                }

            } else {
                printf("Loading %s failed\n",filename.c_str());
            }
        } else {
            printf("File %s does not exist\n",filename.c_str());
        }
        if (!empty_spot) {
            printf("Error, aborting building texture map\n");
        }
//        it_texture_block_map->second=-1;
    }

*/



    if (!shut_up) printf("Getting average color from textures\n");
    best_colors=fopen("colors_index.txt","w");

    std::map<int, struct IdDataColor_list>::iterator it_IdDataColor_map;
    for (it_IdDataColor_map = IdDataColor_map.begin(); it_IdDataColor_map != IdDataColor_map.end(); it_IdDataColor_map++) {
//        sf::Image m_image;
        std::string filename="../minecraft/" + it_IdDataColor_map->second.texture_name + ".png";

        double llui_r=0;
        double llui_g=0;
        double llui_b=0;
        double llui_a=0;

        if (file_exists(filename.c_str())) {
            int id=it_IdDataColor_map->first >> 4;
            int data=it_IdDataColor_map->first & 15;
            if (!shut_up) printf("ID=%d DATA=%d LOADING %s",id,data,filename.c_str());

            bool empty_spot=false;

            if (m_image.loadFromFile(filename.c_str())) {




                int index_x=0;
                int index_y=0;
                bool special=false;
                bool water=false;
                int p_x=m_image.getSize().x;
                int p_y=m_image.getSize().y;
                int t_x=p_x/16;
                int t_y=p_y/16;
                if (p_x!=t_x*16 || p_y!=t_y*16) {
                    printf("Unknown texture size: %d x %d Must be dividable by 16 pixels\n", p_x, p_y);
                }

                if (!shut_up) SetConsoleCursorPosition( hStdOut, homeCoords );
                if (!shut_up) printf("Loaded %s - placing in texture map pixels=(%2d x %2d) tiles=(%d x %d)               \n",filename.c_str(),p_x,p_y,t_x,t_y);
                if (t_y>4 || t_x>1) special=true;
                if (t_y==64) water=true; //preserve first 2 columns for it

                empty_spot=false;
                while (!empty_spot) {
                    empty_spot=true;
                    if (grid[index_x][index_y]==0) {
                        if (water) {
                            if (index_x!=0 || index_y!=0) {
                                printf("Error, tiles for water taken?\n");
                                empty_spot=false;
                            } // else found col 0+1 row 0-63 for water tile
                        } else if (!special && index_x<8) {
                            empty_spot=false; //reserved for tiles width>1, length>4
                        } else if (special && (index_x>=8 || index_x<2)) {  //reserved for these (tiles width==1, length<=4)
                            empty_spot=false;
                        } else if (!special && index_x>=8) {
//                            grid[index_x][index_y]=1; // gets filled
                            break;
                        } else { //special && index_x<6
                            if (index_x<2) empty_spot=false;
                            else if (index_x==7 && t_x==2) empty_spot=false;
                            else if (t_x==2 && grid[index_x+1][index_y]!=0) empty_spot=false;
                            if (index_y + t_y > 64) empty_spot=false;
                            //empty spot! -> end loop
                        }
                    } else if (empty_spot) empty_spot=false;
                    if (empty_spot) break;
                    index_x++;
                    if (index_x==64) {
                        index_x=0;
                        index_y++;
                        if (index_y==64) {
                            empty_spot=false;
                            break;
                        }
                    }
                }
                if (empty_spot) {
                    while (window.pollEvent(event)) {
                    }
                    blocktexture.loadFromImage(m_image);
                    blocksprite.setTexture(blocktexture,true);
                    blocksprite.setPosition(index_x*16,index_y*16);
                    window.draw(blocksprite);
                    MinecraftTexture.draw(blocksprite);
                    window.display();

                    if (first) {
                        if (!shut_up) printf("col    0000000000111111111122222222223333333333444444444455555555556666\n");
                        if (!shut_up) printf("       0123456789012345678901234567890123456789012345678901234567890123\n");
                        first=false;
                    } else {
                        if (!shut_up) printf("\n\n");
                    }
                    static char c='A';
                    c++; if (c>'Z') c='A';
                    for (int y=0; y<64; y++) {
                        bool end_y=true;
                        if (y<index_y || y>=index_y+t_y) {
                            if (!shut_up) printf("\n");
                            continue;
                        }
                        if (!shut_up) printf("row %2d ",y);
                        for (int x=0; x<64; x++) {
                            if (x>=index_x+t_x) continue;
                            if (x>=index_x && x<index_x+t_x && y>=index_y && y<index_y+t_y) { //gets filled, new
                                if (grid[x][y]!=0) {
                                    if (!shut_up) printf("E"); // error...
                                } else {
                                    if (!shut_up) printf("%c",c);
                                    grid[x][y]=c;
                                }
                                end_y=false;
                            } else if (grid[x][y]==0) {
                                if (!shut_up) printf("."); //empty
                            } else {
                                if (!shut_up) printf("%c",grid[x][y]); //filled
                                end_y=false;
                            }
                        }
                        if (!shut_up) printf("\n");
                        if (end_y) break;
                    }
                    if (!shut_up) printf("Empty spot at x=%2d,y=%2d\n",index_x,index_y);
//                    getch();
                } else {
                    printf("Out of texture space? (64x64 tiles x 16x16 pixels / tile = 1024 x 1024 pixels)\n");
                    break;
                }




                int x_m=m_image.getSize().x;
                int y_m=m_image.getSize().y;
                if (!shut_up) printf(" SIZE(%d x %d)",x_m,y_m);
                sf::Color m_color;
                for (int y=0; y<y_m; y++) {
                    for (int x=0; x<x_m; x++) {
                        m_color=m_image.getPixel(x,y);
//                        printf("\npixel color(%d,%d) = (%d,%d,%d,%d)",x,y,m_color.r,m_color.g,m_color.b,m_color.a);
                        llui_r+=(float)m_color.r*(float)m_color.a;
                        llui_g+=(float)m_color.g*(float)m_color.a;
                        llui_b+=(float)m_color.b*(float)m_color.a;
                        llui_a+=(float)m_color.a;
                    }
                }
                if (llui_a!=0) {
                    llui_r/=llui_a;
                    llui_g/=llui_a;
                    llui_b/=llui_a;
                    if (llui_r>=256) printf("Err.");
                    if (llui_g>=256) printf("Err.");
                    if (llui_b>=256) printf("Err.");
                }

                it_IdDataColor_map->second.r=(int)llui_r;
                it_IdDataColor_map->second.g=(int)llui_g;
                it_IdDataColor_map->second.b=(int)llui_b;
                if (empty_spot) {
                    it_IdDataColor_map->second.tc_x=index_x;
                    it_IdDataColor_map->second.tc_y=index_y;
                } else {
                    it_IdDataColor_map->second.tc_x=-1;
                    it_IdDataColor_map->second.tc_y=-1;
                }
            } else {
                printf("Loading %s failed\n",filename.c_str());
                it_IdDataColor_map->second.r=(int)255;
                it_IdDataColor_map->second.g=128;
                it_IdDataColor_map->second.b=0;
            }


            fprintf(best_colors,"ID=%3d DATA=%2d texture_index(%d,%d) color=rgb(%d,%d,%d) (%s)\n",
                    id,data,
                    it_IdDataColor_map->second.tc_x,
                    it_IdDataColor_map->second.tc_y,
                    it_IdDataColor_map->second.r,it_IdDataColor_map->second.g,it_IdDataColor_map->second.b,
                     filename.c_str());

        } else {
            printf("File %s does not exist\n",filename.c_str());
        }
        if (!shut_up) printf(" Average color=rgb(%d,%d,%d)\n",(int)llui_r,(int)llui_g,(int)llui_b);
        if (( it_texture_block_map=texture_block_map.find(filename)) == texture_block_map.end() ) {
            if (!shut_up) printf("filling texture coords for %s\n",filename.c_str());
        } else {
            if (!shut_up) printf("Error: not found -> filling texture coords for %s\n",filename.c_str());

        }
    }
    fclose(best_colors);
    float tt;
    MinecraftSprite.setOrigin(512,512);
    MinecraftTexture.display();
    MinecraftSprite.setPosition(512,512);
    MinecraftTexture.setSmooth(true);

    window.setVerticalSyncEnabled(true);

    bool out=false;
    int tm=0;
    while (window.pollEvent(event) || !out) {
//        window.clear(sf::Color(128+sin(tt*1.3)*127,128+sin(tt*1.6)*127,128+sin(tt*1.5)*127,0));
        window.clear(sf::Color::Transparent);
//        MinecraftSprite.setPosition(512+sin(tt)*100,512+cos(tt)*100);
//        MinecraftSprite.setRotation(tt*2);
        window.draw(MinecraftSprite);
        window.display();
        tt+=0.05;
        tm++;
        if (event.type == sf::Event::KeyPressed || tm>300) {
            out=true;
        }
    }
    window.close();

//    MinecraftTexture.display();
    MinecraftTexture.getTexture().copyToImage().saveToFile("resources/minecraft.png");
/*
    for (it_IdDataColor_map = IdDataColor_map.begin(); it_IdDataColor_map != IdDataColor_map.end(); it_IdDataColor_map++) {
        int id=it_IdDataColor_map->first >> 4;
        int data=it_IdDataColor_map->first & 15;
        printf("ID=%3d DATA=%2d color=rgb(%d,%d,%d) (%s)\n",id,data,it_IdDataColor_map->second.r,it_IdDataColor_map->second.g,it_IdDataColor_map->second.b, it_IdDataColor_map->second.texture_name.c_str());
    }
*/
/*
    it_IdDataColor_map=IdDataColor_map.find(127*16);
    if ( it_IdDataColor_map != IdDataColor_map.end() ) {
        int id=it_IdDataColor_map->first >> 4;
        int data=it_IdDataColor_map->first & 15;
        printf("FOUND cocoa!!!\n");
        printf("ID=%3d DATA=%2d color=rgb(%d,%d,%d) (%s)\n",id,data,it_IdDataColor_map->second.r,it_IdDataColor_map->second.g,it_IdDataColor_map->second.b, it_IdDataColor_map->second.texture_name.c_str());
    } else {
        printf("FOUND NO cocoa!!!\n");
    }
    it_IdDataColor_map=IdDataColor_map.find(8*16);
    if ( it_IdDataColor_map != IdDataColor_map.end() ) {
        int id=it_IdDataColor_map->first >> 4;
        int data=it_IdDataColor_map->first & 15;
        printf("FOUND water!!!\n");
        printf("ID=%3d DATA=%2d color=rgb(%d,%d,%d) (%s)\n",id,data,it_IdDataColor_map->second.r,it_IdDataColor_map->second.g,it_IdDataColor_map->second.b, it_IdDataColor_map->second.texture_name.c_str());
    } else {
        printf("FOUND NO water!!!\n");
    }
*/
}
