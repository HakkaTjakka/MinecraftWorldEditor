#include <stdio.h> //first for fast console output.
#include <sys/stat.h>
#include <map>
#include <string>
#include <dirent.h>
#include <vector>
#include <algorithm>
#include <vector>
#include <string>

#define SFML_STATIC
#include <SFML/Graphics/Image.hpp>

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
    std::string texture_name;
};

std::map<int, struct IdDataColor_list> IdDataColor_map;

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

    std::map<std::string,int> texture_block_map;
    std::map<std::string,int>::iterator it_texture_block_map;

    DIR* dr2 = opendir("../minecraft/blocks");
    struct dirent *de2;
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

    std::vector<struct block_list>::iterator it_names_list;

    std::map<std::string, int> model_variants_map;
    std::map<std::string, int>::iterator it;

    std::map<std::string, int> block_filenames_map;

    for (it_names_list = names_list.begin(); it_names_list != names_list.end(); it_names_list++)
    {
//    for (auto u : names_list) {
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


    std::map<std::string, struct json_list> json_texture_map;
    std::map<std::string, int> texture_types_map;

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
                                if (strcmp(blocks,"blocks")==0)
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


    bool shut_up=true;

    std::map<std::string, struct json_list>::iterator it_json_texture_map;
    IdDataColor_map.clear();
    FILE* best_colors=fopen("best_colors.txt","w");
    for (it_names_list = names_list.begin(); it_names_list != names_list.end(); it_names_list++)
    {
        std::string blockstates_filename="../minecraft/blockstates/" + it_names_list->Item + ".json";
        std::string by_Item_filename="";
        bool by_Item=false;
        if (!shut_up) printf("ID=\"%d\",DataValue=\"%d\",Item=\"%s\",Description=\"%s\",IDName=\"%s\"\n",it_names_list->ID,it_names_list->DataValue,it_names_list->Item.c_str(),it_names_list->Description.c_str(),it_names_list->IDName.c_str());
        if (file_exists(blockstates_filename.c_str()))
        {
            if (!shut_up) printf("BLOCKSTATES= \"%s\" exists\n",blockstates_filename.c_str());
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
                }
                else
                {
                    it = texture_block_map.find(it_names_list->Item);
                    if ( it != texture_block_map.end() )
                    {
                        if (!shut_up) printf("BLOCKSTATES= \"%s\" DOES NOT exist (also not by IDName %s)\n",blockstates_filename.c_str(),it_names_list->IDName.c_str());
                        if (!shut_up) printf("\t\t\t TEXTURE=\"../minecraft/blocks/%s.png\" (FOUND BY Item %s)\n",it->first.c_str(),it->first.c_str());
                        by_Item_filename=it->first.c_str(); by_Item=true;
                    }
                    else
                    {
                        if (!shut_up) printf("BLOCKSTATES= \"%s\" DOES NOT exist (also not by IDName %s or Item %s)\n",blockstates_filename.c_str(),it_names_list->IDName.c_str(),it_names_list->Item.c_str());
                    }
                }
            }
            else
            {
                if (!shut_up) printf("Error in IDName : %s\n",it_names_list->IDName.c_str());
            }
        }
        std::map<std::string, struct model_list>::iterator it_variant;
        int variant_weight=0;

        std::string best_variant="";
        std::string best_type="";
        int best_tot=0;
        std::string best_texture="";
        if (!by_Item) {
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
                std::map<std::string, int>::iterator it_model_list;
                for (it_model_list = it_variant->second.models.begin(); it_model_list != it_variant->second.models.end(); it_model_list++)
                {
                    if (!shut_up) printf("\t MODEL=\"../minecraft/block/%s.json\" (%dx)",it_model_list->first.c_str(),it_model_list->second);

                    it_json_texture_map = json_texture_map.find(it_model_list->first);
                    if ( it_json_texture_map != json_texture_map.end() )
                    {
                        if (!shut_up) printf(" found ");
                        it = block_filenames_map.find(it_model_list->first);
                        if ( it != block_filenames_map.end() ) {
                            if (!shut_up) printf("(Tot %dx)",it->second);
                        }
                        if (!shut_up) printf(" \n");

                        size_t text_len=it_json_texture_map->second.texture_kind.size();
                        for (size_t n=0; n<text_len; n++)
                        {
                            std::string block_filename;
                            std::string kind;
                            kind = it_json_texture_map->second.texture_kind[n];
                            block_filename = it_json_texture_map->second.texture_block[n];

                            if (kind=="all") type_weight=9;
                            else if (kind=="top"     && type_weight<8) { type_weight=8; }
                            else if (kind=="up"      && type_weight<7) { type_weight=7; }
                            else if (kind=="end"     && type_weight<6) { type_weight=6; }
                            else if (kind=="overlay" && type_weight<5) { type_weight=5; }
                            else if (kind=="texture" && type_weight<4) { type_weight=4; }
                            else if (kind=="cross"   && type_weight<3) { type_weight=3; }

                            if (variant_weight + type_weight > best_tot) {
                                best_tot=variant_weight + type_weight;
                                best_variant=variant;
                                best_type=kind;
                                best_texture=block_filename;
                            }

                            int t=strlen(kind.c_str());
                            if (!shut_up) printf("\t\t (TYPE=\"%s\")",kind.c_str());
                            if (!shut_up) for (int i=0; i<15-t; i++) putchar(' ');
                            if (!shut_up) printf(" TEXTURE=\"../minecraft/blocks/%s.png\"",block_filename.c_str());
                            it_texture_block_map=texture_block_map.find(block_filename);
                            if ( it_texture_block_map != texture_block_map.end() )
                            {
                                if (!shut_up) printf(" (exists, used %dx)",it_texture_block_map->second);
                            }
                            if (!shut_up) printf("\n");
                        }
                    }
                    else
                    {
                        if (!shut_up) printf(" NOT FOUND!\n");
                    }
                }
            }
        } else {
            best_texture=by_Item_filename;
        }
        if (!shut_up) printf("\n");
        fprintf(best_colors,"ID=\"%d\",DataValue=\"%d\",Item=\"%s\",Description=\"%s\",IDName=\"%s\",VARIANT=\"%s\",TYPE=\"%s\",TEXTURE=\"%s.png\"\n",
                it_names_list->ID,it_names_list->DataValue,it_names_list->Item.c_str(),it_names_list->Description.c_str(),it_names_list->IDName.c_str(),
                best_variant.c_str(), best_type.c_str(),best_texture.c_str());

        if (best_texture!="") {
            struct IdDataColor_list one_IdDataColor;

            one_IdDataColor.texture_name=best_texture;
            IdDataColor_map.insert( std::make_pair( it_names_list->ID*16 + it_names_list->DataValue , one_IdDataColor ) );
        }
    }

    fclose(best_colors);
    if (!shut_up) {
        printf("USED MODELS:\n");
        for (it = block_filenames_map.begin(); it != block_filenames_map.end(); it++)
        {
            printf("\"block/%s.json\" (%d)\n",it->first.c_str(),it->second);
        }
        printf("\n");

        printf("USED TEXTURES:\n");
        for (it = texture_block_map.begin(); it != texture_block_map.end(); it++)
        {
            printf("\"blocks/%s.png\" (%d)\n",it->first.c_str(),it->second);
        }
        printf("\n");

        printf("USED MODEL VARIANTS:\n");
        for (it = model_variants_map.begin(); it != model_variants_map.end(); it++)
        {
            printf("'%s' (%d)\n",it->first.c_str(),it->second);
        }
        printf("\n");

        printf("\nUSED MODEL TEXTURE TYPES:\n");
        for (it = texture_types_map.begin(); it != texture_types_map.end(); it++)
        {
            printf("'%s' (%d)\n",it->first.c_str(),it->second);
        }
        printf("\n");
        printf("#include <stdio.h> first\n");
    }

    printf("Getting average color from textures\n");

    best_colors=fopen("colors_index.txt","w");

    std::map<int, struct IdDataColor_list>::iterator it_IdDataColor_map;
    for (it_IdDataColor_map = IdDataColor_map.begin(); it_IdDataColor_map != IdDataColor_map.end(); it_IdDataColor_map++) {
        sf::Image m_image;
        std::string filename="../minecraft/blocks/" + it_IdDataColor_map->second.texture_name + ".png";

        double llui_r=0;
        double llui_g=0;
        double llui_b=0;
        double llui_a=0;

        if (file_exists(filename.c_str())) {
            int id=it_IdDataColor_map->first >> 4;
            int data=it_IdDataColor_map->first & 15;
            printf("ID=%d DATA=%d LOADING %s",id,data,filename.c_str());

            if (m_image.loadFromFile(filename.c_str())) {
                int x_m=m_image.getSize().x;
                int y_m=m_image.getSize().y;
                printf(" SIZE(%d x %d)",x_m,y_m);
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

            } else {
                printf("Loading %s failed\n",filename.c_str());
            }
            it_IdDataColor_map->second.r=(int)llui_r;
            it_IdDataColor_map->second.g=(int)llui_g;
            it_IdDataColor_map->second.b=(int)llui_b;

            fprintf(best_colors,"ID=%3d DATA=%2d color=rgb(%d,%d,%d) (%s)\n",id,data,it_IdDataColor_map->second.r,it_IdDataColor_map->second.g,it_IdDataColor_map->second.b, filename.c_str());

        } else {
            printf("File %s does not exist\n",filename.c_str());
        }
        printf(" Average color=rgb(%d,%d,%d)\n",(int)llui_r,(int)llui_g,(int)llui_b);

    }
    fclose(best_colors);
/*
    for (it_IdDataColor_map = IdDataColor_map.begin(); it_IdDataColor_map != IdDataColor_map.end(); it_IdDataColor_map++) {
        int id=it_IdDataColor_map->first >> 4;
        int data=it_IdDataColor_map->first & 15;
        printf("ID=%3d DATA=%2d color=rgb(%d,%d,%d) (%s)\n",id,data,it_IdDataColor_map->second.r,it_IdDataColor_map->second.g,it_IdDataColor_map->second.b, it_IdDataColor_map->second.texture_name.c_str());
    }

    it_IdDataColor_map=IdDataColor_map.find(9*16);
    if ( it_IdDataColor_map != IdDataColor_map.end() ) {
        int id=it_IdDataColor_map->first >> 4;
        int data=it_IdDataColor_map->first & 15;
        printf("FOUND WATER!!!\n");
        printf("ID=%3d DATA=%2d color=rgb(%d,%d,%d) (%s)\n",id,data,it_IdDataColor_map->second.r,it_IdDataColor_map->second.g,it_IdDataColor_map->second.b, it_IdDataColor_map->second.texture_name.c_str());
    } else {
        printf("FOUND NO WATER!!!\n");
    }
*/
}
