#ifndef GEO_THREAD_HPP
#define GEO_THREAD_HPP

#include <map>
#include <string>
#include <vector>

struct dvec2
{
    double x,z;
    dvec2():  x(0), z(0) {};
    dvec2( double x_, double z_ ) :  x(x_), z(z_) {};

};

struct ivec2
{
    int x,z;
    ivec2():  x(0), z(0) {};
    ivec2( int x_, int z_ ) :  x(x_), z(z_) {};

};

struct geo_octant_struct {
    long long int octant;
    std::map<long long int, struct geo_region_struct> regions;
    double lat_north,lon_west,lat_south,lon_east;
};

struct geo_region_struct {
    dvec2 coords;
    dvec2 geo_click;
    dvec2 geo_corners[4];
    ivec2 region;
    ivec2 offset;
    std::map<long long int, struct geo_octant_struct> octants;
};

void SEND_TO_GEO_PIPE(struct geo_region_struct& one_region_struct);
extern glm::ivec2 GET_LAT_LON4(std::string my_area, double lat, double lon);
extern std::string get_area_data(std::string area_name, int &x, int &y);
extern nbt_fast();
extern int crossing;
extern int mirror;
extern bool cubic;
extern bool MAKE_NBT;
extern bool MAKE_NBT_EXTERN;
extern bool repair_mca;
extern bool flushing_mode;
extern bool do_nbt_fast;
extern bool do_wuppie;
extern int region_floor;
extern sf::Image scan_image;
extern int MCEDITOR_running;
extern int main_mceditor6_fixed(int region_x, int region_z, unsigned char* mc);
extern bool plot_only;
extern int plotting;
extern unsigned char region_block[];
extern bool silence;
extern bool burn;
extern int ffmpeg_move;
extern int update_request;
extern int scan_x;
extern int scan_z;

#include <../VOXEL.HPP>
extern std::vector<hit_one_region> ready_regions;






#endif // GEO_THREAD_HPP
