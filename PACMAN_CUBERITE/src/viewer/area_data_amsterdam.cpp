#include <string>
#include <algorithm>
#include <string>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>

extern FileExists(const std::string& abs_filename);
extern std::string *extra_octants_belong_to_string_pointer;
extern int extra_octants_belong_to_string_pointer_x;
extern int extra_octants;
extern std::string latitude_longditude;
extern bool on_hold;
extern bool burn;
extern std::vector<glm::ivec2> to_load_extra;
extern int BITMAPSX;
extern int BITMAPSY;
extern bool load_extra;
extern int select_from_list2(char* filename, char* path, int next);
extern int replace_str(char* str, char* orig, char* rep);


extern char EARTH_ROOT1[];
extern char EARTH_ROOT2[];
extern char EARTH_ROOT3[];
extern char MODELS[];
extern std::string return_root;
extern std::string area;
//extern GET_OCTANT_LIST(std::string area_name, std::string **octants, std::string **lat_lon, int num_lats, int num_lons, int num_extra);

bool GET_OCTANT_LIST(std::string area_name, std::string **octants, std::string **lat_lon, int x, int y, int num_extra) {
    FILE* area_file;
    area_name=std::string()+"OCTANTS/"+area_name+".txt";


    if ((area_file = fopen (area_name.c_str(), "r"))!=NULL) {
        char line[200000];
        char comp[200000];
        char array_line[200000];
        char what[20];
        int index;
        int array_size;
        int line_number=0;
        int lat_lon_line_count=0;
        int octant_line_count=0;
        while (fgets (line,200000, area_file)!=NULL ) {
            line_number++;
            printf("line_number=%d\n",line_number);
            sscanf(line, "%20[^[][%d]=new std::string[%d] {%200000[^}];\n", what, &index, &array_size, array_line );
            sprintf(comp,"%s[%d]=new std::string[%d] {%s};\n", what, index, array_size, array_line);
//            printf("%s[%d]=new std::string[%d] {%s};\n", what, index, array_size, array_line);
            if (strcmp(line,comp)!=0) {
                printf("ORIG(%d):%s",strlen(line), line);
                printf("READ(%d):%s",strlen(comp), comp);
                printf("Error loading line %d from %s : %s\n", line_number, area_name.c_str(), line);
                return false;
            }
//            printf("READ(%d):%s",strlen(comp), comp);
            int item;
            if (strcmp(what,"octants")==0) {
                octants[index]=new std::string[array_size];
                item=0;
                octant_line_count++;
            } else if (strcmp(what,"lat_lon")==0) {
                lat_lon[index]=new std::string[array_size];
                item=1;
                lat_lon_line_count++;
            } else if (strcmp(line,"")==0) {
                printf("Empty line at %d in %s\n",line_number, area_name.c_str());
                continue;
            } else {
                printf("Error loading line %d from %s : %s\n", line_number, area_name.c_str(), line);
                return false;
            }

            std::string str("\"");
            std::string array_line_str = array_line;
//            std::string str2(",");
            int item_count=0;
            std::size_t found_begin = array_line_str.find(str);
            while (found_begin != std::string::npos) {
//                printf("found_begin=%d\n",found_begin);
                std::size_t found_end = array_line_str.find(str,found_begin+2);
                if (found_end!=std::string::npos) {
//                    printf("found_end=%d\n",found_end);
                    std::string string_found=array_line_str.substr(found_begin+1,found_end-found_begin-1);
                    if (item==0) {
//                        printf("found  octant[%d/%d][%d/%d]=%s\n", octant_line_count-1, x, item_count, y, string_found.c_str());
                        if (octant_line_count-1 >= x) {
//                        if (octant_line_count-1 >= array_size) {
                            printf("size out of bound : line %d\n",line_number);
                            printf("octant[%d/%d][%d/%d]=%s\n", octant_line_count-1, x, item_count, y, string_found.c_str());
                            return false;
                        } else {
                            octants[index][item_count]=string_found;
                        }
                    } else {
//                        printf("found lat_lon[%d/%d][%d/%d]=%s\n", lat_lon_line_count-1, x, item_count, y, string_found.c_str());
                        if (lat_lon_line_count-1 >= x) {
//                        if (lat_lon_line_count-1 >= array_size) {
                            printf("size out of bound : line %d\n",line_number);
                            printf("lat_lon[%d/%d][%d/%d]=%s\n", lat_lon_line_count-1, x, item_count, y, string_found.c_str());
                            return false;
                        } else {
                            lat_lon[index][item_count]=string_found;
                        }

//                         printf("lat_lon[%d/%d][%d/%d]=%s\n", lat_lon_line_count-1, x, item_count, y, string_found.c_str());

                    }
                    found_begin=array_line_str.find(str,found_end+2);
                } else {
                    printf("Error at line %d : %s\n",line_number,line);
                    return false;
                }
                item_count++;
            }
        }
        if (line_number==0) {
            printf("Error loading %s\n", area_name.c_str());
        }
        fclose(area_file);
    } else {
        printf("Cannot open %s\n",area_name.c_str());
        return false;
    }

    return true;
}

std::string get_octant_AMSTERDAM(int &x, int &y) {
	static std::string *octants[88];
	static std::string *lat_lon[88];
	static int first_do=1;
	if  (first_do==1) {
		first_do=0;
        printf("LOADING OCTANTS/AMSTERDAM.TXT\n");
        if (!GET_OCTANT_LIST("AMSTERDAM", octants, lat_lon, 88, 202, 0)) {
            printf("Error reading OCTANTS/AMSTERDAM.TXT\n");
            return "";
        }
	}
	extra_octants=0;
	if (x<0 || y<0) {
		x=88;y=202;
		return "";
	}
	bool OK=false;
	if (x>=88 || y>=202) printf("Out of bound: %s X=%d Y=%d\n",area.c_str(),x,y);
	else OK=true;
	if (!OK) return "";
	latitude_longditude=lat_lon[x][y];
	std::string subdir=octants[x][y].substr(0,14)+"/";
	return_root = std::string()+EARTH_ROOT1+"/AMSTERDAM/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/AMSTERDAM/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/AMSTERDAM/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/AMSTERDAM/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/AMSTERDAM/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/AMSTERDAM/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/AMSTERDAM/"+"nbt/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/AMSTERDAM/"+"nbt/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/AMSTERDAM/"+"nbt/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/AMSTERDAM/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/AMSTERDAM/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/AMSTERDAM/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/AMSTERDAM/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/AMSTERDAM/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/AMSTERDAM/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/AMSTERDAM/"+"obj/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/AMSTERDAM/"+"obj/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/AMSTERDAM/"+"obj/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	printf("Directory not found on search paths: %s-21\n",octants[x][y].c_str());
	return "";
}

std::string get_octant_UTRECHT(int &x, int &y) {
	static std::string *octants[145];
	static std::string *lat_lon[144];
	static int first_do=1;
	if  (first_do==1) {
		first_do=0;
        printf("LOADING OCTANTS/UTRECHT.TXT\n");
        if (!GET_OCTANT_LIST("UTRECHT", octants, lat_lon, 145, 144, 336)) {
            printf("Error reading OCTANTS/UTRECHT.TXT\n");
            return "";
        }
	}
	extra_octants=336;
	extra_octants_belong_to_string_pointer=octants[144];
	extra_octants_belong_to_string_pointer_x=143;
	if (x<0 || y<0) {
		x=143;y=145;
		return "";
	}
	bool OK=false;
	if (x>=143 && y>335) printf("Out of bound: %s X=%d Y=%d\n",area.c_str(),x,y);
	else if (!(x>=143) && (x>143 || y>144)) printf("Out of bound: %s X=%d Y=%d\n",area.c_str(),x,y);
	else OK=true;
	if (!OK) return "";
	if (!(x>143)) latitude_longditude=lat_lon[x][y];
	else latitude_longditude="";

	std::string subdir=octants[x][y].substr(0,14)+"/";
	return_root = std::string()+EARTH_ROOT1+"/UTRECHT/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/UTRECHT/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/UTRECHT/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/UTRECHT/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/UTRECHT/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/UTRECHT/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/UTRECHT/"+"nbt/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/UTRECHT/"+"nbt/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/UTRECHT/"+"nbt/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/UTRECHT/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/UTRECHT/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/UTRECHT/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/UTRECHT/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/UTRECHT/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/UTRECHT/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/UTRECHT/"+"obj/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/UTRECHT/"+"obj/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/UTRECHT/"+"obj/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	printf("Directory not found on search paths: %s-21\n",octants[x][y].c_str());
	return "";
}


std::string get_octant_RIO(int &x, int &y) {
	static std::string *octants[178];
	static std::string *lat_lon[177];
	static int first_do=1;
	if  (first_do==1) {
		first_do=0;
        printf("LOADING OCTANTS/RIO.TXT\n");
        if (!GET_OCTANT_LIST("RIO", octants, lat_lon, 178, 55, 1842)) {
            printf("Error reading OCTANTS/RIO.TXT\n");
            return "";
        }
	}
	extra_octants=1842;
	extra_octants_belong_to_string_pointer=octants[177];
	extra_octants_belong_to_string_pointer_x=176;
	if (x<0 || y<0) {
		x=176;y=55;
		return "";
	}
	bool OK=false;
	if (x>=176 && y>1841) printf("Out of bound: %s X=%d Y=%d\n",area.c_str(),x,y);
	else if (!(x>=176) && (x>176 || y>54)) printf("Out of bound: %s X=%d Y=%d\n",area.c_str(),x,y);
	else OK=true;
	if (!OK) return "";
	if (!(x>176)) latitude_longditude=lat_lon[x][y];
	else latitude_longditude="";
	std::string subdir=octants[x][y].substr(0,14)+"/";
	return_root = std::string()+EARTH_ROOT1+"/RIO/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/RIO/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/RIO/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/RIO/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/RIO/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/RIO/"+subdir+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/RIO/"+"nbt/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/RIO/"+"nbt/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/RIO/"+"nbt/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/RIO/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/RIO/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/RIO/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/"+octants[x][y]+"-21/"+octants[x][y]+".nbt";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/RIO/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/RIO/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/RIO/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/RIO/"+"obj/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/RIO/"+"obj/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/RIO/"+"obj/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT1+"/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT2+"/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	return_root = std::string()+EARTH_ROOT3+"/"+octants[x][y]+"-21/"+octants[x][y]+".obj";  if (FileExists(return_root.c_str())) return return_root;
	printf("Directory not found on search paths: %s-21\n",octants[x][y].c_str());
	return "";
}
