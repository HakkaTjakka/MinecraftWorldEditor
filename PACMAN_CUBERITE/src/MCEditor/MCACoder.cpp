#include "MCACoder.h"
//#include "MCEditor.h"
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include "globals.h"
using namespace std;

string file_name_MCA;
int region_x_old=0,region_z_old=0;
extern int region_xxx,region_zzz;
int first_MCEDIT=1;

extern void toggle2();
extern void toggle3();
extern int lookup_counter1;
extern int lookup_counter2;
extern int lookup_counter3;
extern int lookup_counter4;
extern int lookup_counter5;
extern int lookup_counter6;
extern int addnew_counter;

string MCAFileNameXZ(int x, int z)
{
    char tmp[256];
    int len = sprintf(tmp, "/Saves/Test/region/r.%d.%d.mca", x, z);
    if (len < 0)
    {
        fprintf(stderr, "Buffer overflow when generating mca file name.\n");
        exit(0);
    }
    string res = tmp;
    return res;
}


//hoppa
void MCACoder::saveModification()
{
    current_filename_mca=file_name_MCA;
    if (!modification_saved)
        writeMCA();
    for (int i = 0; i < K1; i++)
    {
        nbt_coder.Clear(Chunk[i]);
        Chunk[i] = 0;
    }
    current_filename_mca = "";
    modification_saved = true;
}

void MCACoder::clearModification()
{
//    current_filename_mca=file_name_MCA;
 //   if (!modification_saved)
//        writeMCA();
    for (int i = 0; i < K1; i++)
    {
        nbt_coder.Clear(Chunk[i]);
        Chunk[i] = 0;
    }
    current_filename_mca = "";
    modification_saved = true;
}

extern toggle();

int old_idx=0;
int old_sec_no=0;
node *old_T=0;
node *old_sec_root=0;

extern int chunk_offsetx;
extern int chunk_offsetz;

void MCACoder::setPOSITIONS() {
    for (int x=0; x<32; x++) {
        for (int z=0; z<32; z++) {
            node *chunk_root = Chunk[x+z*32];
            if (!(chunk_root==0)) {
                node *level_root = chunk_root->childWithName("Level");
                if (!(level_root==0)) {
                    node *pos=level_root->childWithName("xPos");
                    if (!(pos==0)) {
                        pos->tag.vi=chunk_offsetx+x;
                    }
                    pos=level_root->childWithName("zPos");
                    if (!(pos==0)) {
                        pos->tag.vi=chunk_offsetz+z;
                    }
                }
            }
        }
    }
}

void MCACoder::setBlock(const Pos &position, const BlockInfo &info)
{

    //fprintf(stderr, "Setting (%d, %d, %d).\n", x, y, z);
    int x = position.x, z = position.z, y = position.y;

    int chunk_x = x >> 4, chunk_z = z >> 4;
    int region_x = chunk_x >> 5, region_z = chunk_z >> 5;

//    static string file_name_MCA;
//    static int region_x_old=0,region_z_old=0;
//    static int first_MCEDIT=1;
    if (first_MCEDIT==1 || region_x_old!=region_x || region_z_old!=region_z) {
//        printf("setblock: region_x=%d region_z=%d region_x_old=%d region_z_old=%d\n",region_x,region_z,region_x_old,region_z_old);
        region_x_old=region_x;
        region_z_old=region_z;
        first_MCEDIT=0;
        file_name_MCA = MCAFileNameXZ(region_x, region_z);
        if (loadMCA(file_name_MCA) == -1) { fprintf(stderr, "File %s that contains block (%d, %d, %d) does not exists.\n", file_name_MCA.c_str(), x, y, z); return; }
        old_idx=0;
        old_sec_no=0;
        old_T=0;
        old_sec_root=0;
    }

    int idx = (chunk_x & 31) + 32 * (chunk_z & 31);
    node *chunk_root = Chunk[idx];

    if (!chunk_root) { /* fprintf(stderr, "1) Chunk that contains (%d, %d, %d) not initialized\n", x, y, z);*/ return; }

    modification_saved = false;

    int sec_no = y >> 4;

    node *level_root;
    node *sec_root;
    node *T;

    if (old_idx==idx && old_sec_no==sec_no && !old_T==0 && !old_sec_root==0) {
        sec_root=old_sec_root;
        T=old_T;
    } else {
        if (!(old_sec_root==0) && idx==old_idx) {
            sec_root=old_sec_root;
        } else {
            level_root = chunk_root->childWithName("Level");
            sec_root = level_root->childWithName("Sections");
            lookup_counter1++;
//            printf("region_x=%2d  region_z=%2d  idx=%4d  chunk_x=%2d  chunk_z=%2d  sec_no=%2d  x=%4d  z=%4d  y=%2d\n", region_x, region_z, idx, chunk_x, chunk_z, sec_no, x, z, y);
        }
        if (old_idx==idx && old_sec_root==sec_root && sec_no==old_sec_no && (!(old_T==0)))
            T = old_T;
        else
            T = sectionNodeWithY(sec_root, sec_no);
    }

    if (!T) { T = newSectionNodeWithY(sec_no); sec_root->addChild(T); }
        /*fprintf(stderr, "Section at Y = %d not initialized.\n", sec_no); return;*/

    node *u;
    int block_x = (x & 15), block_z = (z & 15), block_y = (y & 15);
    int block_pos = block_y * 16 * 16 + block_z * 16 + block_x;

    static node *old_u_blocks=0;

    if (old_T==T && !(old_u_blocks==0)) {
        u=old_u_blocks;
    } else {
        u = T->childWithName("Blocks");
        lookup_counter2++;
        old_u_blocks=u;
    }
    //set Blocks
    nbt_coder.setByteInArrayContent(u, block_pos, (uc)info.id);

    static node *old_u_add=0;

    if (!(old_T==T)) {
        lookup_counter3++;
        u = T->childWithName("Add");
        old_u_add=u;
//        if (u) printf("Found Add tag!: %p  info.add=%d   x=%d, z=%d, y=%d \n",u,info.add, x,z,y);
//        else printf("old_T!=T: Add tag not found: %p  info.add=%d   x=%d, z=%d, y=%d \n",u,info.add, x,z,y);
//        else printf("Add tag not found: %p  info.add=%d   x=%d, z=%d, y=%d \n",u,info.add, x,z,y);
//        printf("region_x=%2d  region_z=%2d  idx=%4d  chunk_x=%2d  chunk_z=%2d  sec_no=%2d  x=%4d  z=%4d  y=%2d  u=%d\n", region_x, region_z, idx, chunk_x, chunk_z, sec_no, x, z, y, u);
    } else {
        u=old_u_add;
    }

//    if (old_T==T && !(old_u_add==0)) {
//        u=old_u_add;
//    } else {
//        lookup_counter3++;
//        u = T->childWithName("Add");
//        old_u_add=u;
//    }

    //set Add
//    if (info.add>0) printf("Hier 4: info.add=%d   x=%d, z=%d, y=%d \n",info.add, x,z,y);
//    else printf("info.add==0\n");
    if (u || info.add)
    {
        if (!u)
        {
//            printf("Adding new Add tag\n",u,info.add);
//            printf("u || info.add -> u=%p info.add=%d   x=%d, z=%d, y=%d \n",u,info.add, x,z,y);
            addnew_counter++;
            u = new node(TAG_BYTE_ARRAY, "Add");
            u->tag.va.resize(K2);
            T->addChild(u);
            old_u_add=u;
        }
        nbt_coder.setHalfByteInArrayContent(u, block_pos, info.add);
    }
//    toggle3();

    static node *old_u_data=0;

    if (old_T==T && !(old_u_data==0)) {
        u=old_u_data;
    } else {
        lookup_counter4++;
        u = T->childWithName("Data");
        old_u_data=u;
    }
    //set BlockData
    nbt_coder.setHalfByteInArrayContent(u, block_pos, info.data);

    static node *old_u_blocklight=0;

    if (old_T==T && !(old_u_blocklight==0)) {
        u=old_u_blocklight;
    } else {
        lookup_counter5++;
        u = T->childWithName("BlockLight");
        old_u_blocklight=u;
    }
    //set BlockLight
    nbt_coder.setHalfByteInArrayContent(u, block_pos, info.block_light);

    static node *old_u_skylight=0;

    if (old_T==T && !(old_u_skylight==0)) {
        u=old_u_skylight;
    } else {
        lookup_counter6++;
        u = T->childWithName("SkyLight");
        old_u_skylight=u;
    }
    //set SkyLight
    nbt_coder.setHalfByteInArrayContent(u, block_pos, info.sky_light);

    old_idx=idx;
    old_sec_no=sec_no;
    old_T=T;
    old_sec_root=sec_root;
}

int getblock_old_idx=0;
int getblock_old_sec_no=0;
node *getblock_old_T=0;
node *getblock_old_sec_root=0;

void reset_block() {
    getblock_old_idx=0;
    getblock_old_sec_no=0;
    getblock_old_T=0;
    getblock_old_sec_root=0;
}

BlockInfo MCACoder::getBlock(int x, int z, int y)
{
    int chunk_x = x >> 4, chunk_z = z >> 4;
    int region_x = chunk_x >> 5, region_z = chunk_z >> 5;

    if (first_MCEDIT==1 || region_x_old!=region_x || region_z_old!=region_z) {
//        printf("setblock: region_x=%d region_z=%d region_x_old=%d region_z_old=%d\n",region_x,region_z,region_x_old,region_z_old);
        region_x_old=region_x;
        region_z_old=region_z;
        first_MCEDIT=0;
        file_name_MCA = MCAFileNameXZ(region_x, region_z);
        if (loadMCA(file_name_MCA) == -1) { fprintf(stderr, "File %s that contains block (%d, %d, %d) does not exists.\n", file_name_MCA.c_str(), x, y, z); return BlockInfo(); }
        getblock_old_idx=0;
        getblock_old_sec_no=0;
        getblock_old_T=0;
        getblock_old_sec_root=0;
    }

    int idx = (chunk_x & 31) + 32 * (chunk_z & 31);
//    node *T = Chunk[idx];
    node *T;
    node *chunk_root = Chunk[idx];
    node *level_root;
    node *sec_root;

    if (!chunk_root) { /* fprintf(stderr, "2) Chunk that contains (%d, %d, %d) not initialized\n", x, z, y); */ return BlockInfo();  }
//    if (!T) { fprintf(stderr, "2) Chunk that contains (%d, %d, %d) not initialized\n", x, z, y); return BlockInfo();  }

    int sec_no = y >> 4;

    if (getblock_old_idx==idx && getblock_old_sec_no==sec_no && !getblock_old_T==0 && !getblock_old_sec_root==0) {
        sec_root=getblock_old_sec_root;
        T=getblock_old_T;
    } else {
        if (!(getblock_old_sec_root==0) && idx==getblock_old_idx) {
            sec_root=getblock_old_sec_root;
        } else {
            level_root = chunk_root->childWithName("Level");
            sec_root = level_root->childWithName("Sections");
            lookup_counter1++;
//            printf("region_x=%2d  region_z=%2d  idx=%4d  chunk_x=%2d  chunk_z=%2d  sec_no=%2d  x=%4d  z=%4d  y=%2d\n", region_x, region_z, idx, chunk_x, chunk_z, sec_no, x, z, y);
        }
        if (getblock_old_idx==idx && getblock_old_sec_root==sec_root && sec_no==getblock_old_sec_no && (!(getblock_old_T==0)))
            T = getblock_old_T;
        else
            T = sectionNodeWithY(sec_root, sec_no);
    }

    //T = T->childWithName("Level");
//    T = T->childWithName("Sections");
//    T = sectionNodeWithY(T, sec_no);

    if (!T) { return BlockInfo(); }
        /*fprintf(stderr, "Section at Y = %d not initialized.\n", sec_no);*/


    node *u;
    int block_x = (x & 15), block_z = (z & 15), block_y = (y & 15);
    int block_pos = block_y * 16 * 16 + block_z * 16 + block_x;

    static node *old_u_blocks=0;

    if (getblock_old_T==T) {
        u=old_u_blocks;
    } else {
        lookup_counter2++;
        u = T->childWithName("Blocks");
        old_u_blocks=u;
    }
//    u = T->childWithName("Blocks");
    int id = nbt_coder.getByteInArrayContent(u, block_pos);

    static node *old_u_add=0;

    if (getblock_old_T==T) {
        u=old_u_add;
    } else {
        lookup_counter3++;
        u = T->childWithName("Add");
        old_u_add=u;
    }
//    u = T->childWithName("Add");
    int add = u ? nbt_coder.getHalfByteInArrayContent(u, block_pos) : 0;


    static node *old_u_data=0;

    if (getblock_old_T==T) {
        u=old_u_data;
    } else {
        lookup_counter4++;
        u = T->childWithName("Data");
        old_u_data=u;
    }
//    u = T->childWithName("Data");
    int data = u ? nbt_coder.getHalfByteInArrayContent(u, block_pos) : 0;


    static node *old_u_blocklight=0;

    if (getblock_old_T==T) {
        u=old_u_blocklight;
    } else {
        lookup_counter5++;
        u = T->childWithName("BlockLight");
        old_u_blocklight=u;
    }
//    u = T->childWithName("BlockLight");
    int block_light = nbt_coder.getHalfByteInArrayContent(u, block_pos);

    static node *old_u_skylight=0;

    if (getblock_old_T==T) {
        u=old_u_skylight;
    } else {
        lookup_counter6++;
        u = T->childWithName("SkyLight");
        old_u_skylight=u;
    }
//    u = T->childWithName("SkyLight");
    int sky_light = nbt_coder.getHalfByteInArrayContent(u, block_pos);

    getblock_old_idx=idx;
    getblock_old_sec_no=sec_no;
    getblock_old_T=T;
    getblock_old_sec_root=sec_root;
//    toggle2();
    return BlockInfo(id, add, data, block_light, sky_light);
}

void MCACoder::removeBlockEntity(const Pos &position)
{
    int x = position.x, z = position.z, y = position.y;

    int chunk_x = x >> 4, chunk_z = z >> 4;
    int region_x = chunk_x >> 5, region_z = chunk_z >> 5;

    int idx = (chunk_x & 31) + 32 * (chunk_z & 31);
    node *chunk_root = Chunk[idx];
    if (!chunk_root) return;

    node *level_root = chunk_root->childWithName("Level");
    node *T = level_root->childWithName("TileEntities");

    int totx=region_xxx*512;
    int totz=region_zzz*512;

    for (auto it = T->ch.begin(); it != T->ch.end(); it++)
    {
        node *u = *it;
        if (u->ch.empty()) continue;

        node *v;
        v = u->childWithName("x");
        int x = v->tag.vi;
        v = u->childWithName("z");
        int z = v->tag.vi;
        v = u->childWithName("y");
        int y = v->tag.vi;
//watch region...check
//        if (!(position == Pos(x, z, y))) {
//        if (!(position == Pos(x+region_xxx*512, z+region_zzz*512, y))) {
//      only remove tileentities on same position?
        if (!(position == Pos(x-totx, z-totz, y))) {
//            printf("\b.");
//            if (!(rand()%1000)) {
//                printf("Pos(%d,%d,%d) != x,z,y=(%d,%d,%d)  (%d,%d,%d)\n",position.x,position.z,position.y,x,z,y,x-region_xxx*512, z-region_zzz*512, y);
//            }
//            printf("Hier 10, not deleted...check\n");
            continue;
        }

//        printf("Hier 11, deleting not deleted...check\n");
//        printf("\bo");
        delete u;
        it = T->ch.erase(it);
        modification_saved = false;
        break;
    }
}

//joehoe
void MCACoder::insertEntity(const Pos &position, MobEntity *entity)
{
    if (!entity)
        return;

    int x = position.x, z = position.z, y = position.y;

    node *chunk_root = chunkWithXZ(x, z);
    if (!chunk_root) {  fprintf(stderr,"3) Chunk that contains (%d, ?, %d) is not initialized\n",x, z); return;  }

    node *level_root = chunk_root->childWithName("Level");
    node *T = level_root->childWithName("Entities");
    if (!T) { /* fprintf(stderr,"TileEntities does not exits (%d, %d, %d)\n", x, y, z);*/ return; }

    T->tag.ch_type = TAG_COMPOUND;
    T->addChild(newEntityNode(entity));
    modification_saved = false;
}


void MCACoder::insertBlockEntity(const Pos &position, BlockEntity *entity)
{
    if (!entity)
        return;

    int x = position.x, z = position.z, y = position.y;

    node *chunk_root = chunkWithXZ(x, z);
    if (!chunk_root) {  fprintf(stderr,"3) Chunk that contains (%d, ?, %d) is not initialized\n",x, z); return;  }

    node *level_root = chunk_root->childWithName("Level");
    node *T = level_root->childWithName("TileEntities");
    if (!T) { /* fprintf(stderr,"TileEntities does not exits (%d, %d, %d)\n", x, y, z);*/ return; }

    T->tag.ch_type = TAG_COMPOUND;
    T->addChild(newBlockEntityNode(entity));
    modification_saved = false;
}

void MCACoder::setHeightMap(int x, int z, int y)
{
    node *chunk_root = chunkWithXZ(x, z);
    if (!chunk_root) { /*  fprintf(stderr,"4) Chunk that contains (%d, ?, %d) is unintialized", x, z); */
        return;
    }

    node *level_root = chunk_root->childWithName("Level");
    node *T = level_root->childWithName("HeightMap");

    int block_x = (x & 15), block_z = (z & 15);
    int col_pos = block_z * 16 + block_x;
    int h = min((int)nbt_coder.getByteInArrayContent(T, col_pos), y);
    nbt_coder.setByteInArrayContent(T, col_pos, 0);
}

//////////////////////////////////PRIVATE/////////////////////////////////////

int MCACoder::loadMCA(const string &file_name_MCA)
{
    if (current_filename_mca == file_name_MCA) return 0;

    printf("Loading %s ", file_name_MCA.c_str());

    if (current_filename_mca != "") saveModification();

    FILE *handle = fopen(file_name_MCA.c_str(), "rb");
    if (!handle) return -1;

    current_filename_mca = file_name_MCA;

    fread(buffer, 1, K4, handle);
    for (int i = 0; i < K4; i += 4)  location[i >> 2] = K4 * byteToInt(buffer, i, 3);

    fread(buffer, 1, K4, handle);

//timetime
    for (int i = 0; i < K4; i += 4) timestamp[i >> 2] = byteToInt(buffer, i, 4);
//    for (int i = 0; i < K4; i += 4) timestamp[i >> 2] = K4 * byteToInt(buffer, i, 4);

    for (int i = 0; i < K1; i++) {
        if (location[i]) {
            fseek(handle, location[i], SEEK_SET);

            fread(buffer, 1, 4, handle);
            int chunk_len = (int)byteToInt(buffer, 0, 4);
            chunk_len--;

            fread(buffer, 1, 1, handle);
            int cmpr_type = byteToInt(buffer, 0, 1);

            if (cmpr_type != 2)
            {
                fprintf(stderr, "Decompression Type Error: %d.\n", cmpr_type);
                exit(0);
            }

            chunk_len = fread(buffer, 1, chunk_len, handle);

            decompress(chunk_buffer, sizeof(chunk_buffer), buffer, chunk_len);

            Chunk[i] = nbt_coder.Decode(chunk_buffer);

            //debug::
            //string name = "chunk"; name += to_string(i);
            //freopen(name.c_str(), "w", stdout);
            //nbt_coder.Print(Chunk[i]);
        } else {
            Chunk[i] = 0;
        }
    }

    fclose(handle);

    return 0;
}

void MCACoder::writeMCA()
{
    printf("- Saving %s",current_filename_mca.c_str());
    memset(buffer, 0, sizeof(buffer));

    ull offset = K4 << 1;
    for (int i = 0; i < K1; i++)
    {
        if (!Chunk[i])
        {
            intToByte(0, buffer, i << 2, 3);
            intToByte(0, buffer, (i << 2) + 3, 1);
            continue;
        }

        intToByte(offset / K4, buffer, i << 2, 3);

        ull chunk_len = nbt_coder.Encode(Chunk[i], chunk_buffer);
        ull cmpr_len = compress(buffer + offset + 5, sizeof(buffer) - (offset + 5),
                                chunk_buffer, chunk_len);

        cmpr_len++;
        intToByte(cmpr_len, buffer, offset, 4);
        cmpr_len += 4;
        intToByte(2, buffer, offset + 4, 1);
        //offset will be updated later

        ull sector_cnt = 0;
        if (cmpr_len % K4 == 0)
            sector_cnt = cmpr_len / K4;
        else
            sector_cnt = cmpr_len / K4 + 1;

        intToByte(sector_cnt, buffer, (i << 2) + 3, 1);
        cmpr_len = sector_cnt * K4; //Pad to a multiple of K4
        offset += cmpr_len;
        toggle2();
    }

    for (int i = 0; i < K1; i++) {
        intToByte(timestamp[i], buffer, K4 + (i << 2), 4);
        toggle2();
    }

    remove(current_filename_mca.c_str());
    FILE *handle = fopen(current_filename_mca.c_str(), "wb");
    fwrite(buffer, 1, offset, handle);
    fclose(handle);
    printf("\n");
}

node *MCACoder::chunkWithXZ(int x, int z)
{
    int chunk_x = x >> 4, chunk_z = z >> 4;
    int region_x = chunk_x >> 5, region_z = chunk_z >> 5;

    if (first_MCEDIT==1 || region_x_old!=region_x || region_z_old!=region_z) {
//        printf("setblock: region_x=%d region_z=%d region_x_old=%d region_z_old=%d\n",region_x,region_z,region_x_old,region_z_old);
        region_x_old=region_x;
        region_z_old=region_z;
        first_MCEDIT=0;
        file_name_MCA = MCAFileNameXZ(region_x, region_z);
        if (loadMCA(file_name_MCA) == -1) { fprintf(stderr, "File %s that contains block (%d, ?, %d) does not exists.\n", file_name_MCA.c_str(), x, z); return 0; }
    }
/*
    string file_name_MCA = MCAFileNameXZ(region_x, region_z);

    if (loadMCA(file_name_MCA) == -1)
    {
        fprintf(stderr, "File %s that contains block (%d, ?, %d) does not exists.\n",
                file_name_MCA.c_str(), x, z);
        return 0;
    }
*/
    int idx = (chunk_x & 31) + 32 * (chunk_z & 31);
    return Chunk[idx];
}

node *MCACoder::sectionNodeWithY(node *T, int y)
{
    for (node *u : T->ch)
    {
        node *v = u->childWithName("Y");
        if (v->tag.vi == y)
            return u;
    }
    return 0; //newSectionWithY(y);
}

node *MCACoder::newSectionNodeWithY(int y)
{
    node *u;
    node *T = new node(TAG_COMPOUND, "none");

    u = new node(TAG_BYTE, "Y");
    u->tag.vi = y;
    T->addChild(u);

    u = new node(TAG_BYTE_ARRAY, "Blocks");
    u->tag.va.resize(K4, 0);
    T->addChild(u);

    /*  u = new node(TAG_BYTE_ARRAY, "Add");
    u->tag.va.resize(K2, 0);
    T->addChild(u);
    */

    u = new node(TAG_BYTE_ARRAY, "Data");
    u->tag.va.resize(K2, 0);
    T->addChild(u);

    u = new node(TAG_BYTE_ARRAY, "BlockLight");
    u->tag.va.resize(K2, 0);
    T->addChild(u);

    u = new node(TAG_BYTE_ARRAY, "SkyLight");
    u->tag.va.resize(K2, 0xFF);
    T->addChild(u);

    return T;
}

node *MCACoder::newBlockEntityNode(BlockEntity *entity)
{
    node *u;

    //Tags common to all block entities
    node *T = new node(TAG_COMPOUND, "none");

    u = new node(TAG_STRING, "id");
    u->tag.vs = entity->entity_id;
    T->addChild(u);

    u = new node(TAG_INT, "x");
    u->tag.vi = entity->position.x;
    T->addChild(u);

    u = new node(TAG_INT, "y");
    u->tag.vi = entity->position.y;
    T->addChild(u);

    u = new node(TAG_INT, "z");
    u->tag.vi = entity->position.z;
    T->addChild(u);

    //Tags special to each block entity
    if (entity->entity_id == "minecraft:noteblock")
    {
        BlockEntityNote *noteblock = (BlockEntityNote *)entity;

        u = new node(TAG_BYTE, "note");
        u->tag.vi = noteblock->note;
        T->addChild(u);

        u = new node(TAG_BYTE, "powered");
        u->tag.vi = noteblock->powered;
        T->addChild(u);
    }

    if (entity->entity_id == "minecraft:command_block")
    {
        BlockEntityCommand *cmdblock = (BlockEntityCommand*)entity;

        u = new node(TAG_STRING, "Command");
        u->tag.vs = cmdblock->command;
        T->addChild(u);

        u = new node(TAG_INT, "SuccessCount");
        u->tag.vi = 0;
        T->addChild(u);

        u = new node(TAG_STRING, "LastOutput");
        u->tag.vs = "";
        T->addChild(u);

        u = new node(TAG_BYTE, "TrackOutput");
        u->tag.vi = 0;
        T->addChild(u);

        u = new node(TAG_BYTE, "powered");
//        u->tag.vi = 0;
        u->tag.vi = cmdblock->powered;
        T->addChild(u);

        u = new node(TAG_BYTE, "auto");
//        u->tag.vi = 0;
        u->tag.vi = cmdblock->automatic;
        T->addChild(u);

        u = new node(TAG_BYTE, "conditionMet");
        u->tag.vi = 1;
        T->addChild(u);

        u = new node(TAG_BYTE, "UpdateLastExecution");
        u->tag.vi = 1;
        T->addChild(u);

        u = new node(TAG_LONG, "LastExecution");
        u->tag.vi = 0;
        T->addChild(u);
    }

    //TODO

    return T;
}

/*
 |  |   |  [ 0](1)[compound] "Brain"
 |  |   |   |  [0](0)[compound] "memories"
 |  |   |  [ 1][int] "HurtByTimestamp" 0
 |  |   |  [ 2](7)[list] "Attributes"
 |  |   |   |  [0](2)[compound] "(null)"
 |  |   |   |   | [0][double] "Base" 3,000000000000000000000e+000
 |  |   |   |   | [1][string](17) "Name" generic.maxHealth
 |  |   |   |  [1](2)[compound] "(null)"
 |  |   |   |   | [0][double] "Base" 0,000000000000000000000e+000
 |  |   |   |   | [1][string](27) "Name" generic.knockbackResistance
 |  |   |   |  [2](2)[compound] "(null)"
 |  |   |   |   | [0][double] "Base" 6,999999880790710400000e-001
 |  |   |   |   | [1][string](21) "Name" generic.movementSpeed
 |  |   |   |  [3](2)[compound] "(null)"
 |  |   |   |   | [0][double] "Base" 0,000000000000000000000e+000
 |  |   |   |   | [1][string](13) "Name" generic.armor
 |  |   |   |  [4](2)[compound] "(null)"
 |  |   |   |   | [0][double] "Base" 0,000000000000000000000e+000
 |  |   |   |   | [1][string](22) "Name" generic.armorToughness
 |  |   |   |  [5](3)[compound] "(null)"
 |  |   |   |   | [0][double] "Base" 1,600000000000000000000e+001
 |  |   |   |   | [1](1)[list] "Modifiers"
 |  |   |   |   |  | [0](5)[compound] "(null)"
 |  |   |   |   |  |  | [0][long] "UUIDMost" -5509840330306793966
 |  |   |   |   |  |  | [1][long] "UUIDLeast" -6387563857175199172
 |  |   |   |   |  |  | [2][double] "Amount" -1,867192294953659200000e-002
 |  |   |   |   |  |  | [3][int] "Operation" 1
 |  |   |   |   |  |  | [4][string](18) "Name" Random spawn bonus
 |  |   |   |   | [2][string](19) "Name" generic.followRange
 |  |   |   |  [6](2)[compound] "(null)"
 |  |   |   |   | [0][double] "Base" 0,000000000000000000000e+000
 |  |   |   |   | [1][string](23) "Name" generic.attackKnockback
 |  |   |  [ 3][byte] "Invulnerable" 0
 |  |   |  [ 4][byte] "FallFlying" 0
 |  |   |  [ 5][int] "PortalCooldown" 0
 |  |   |  [ 6][float] "AbsorptionAmount" 0,000000
 |  |   |  [ 7][float] "FallDistance" 0,000000
 |  |   |  [ 8][short] "DeathTime" 0
 |  |   |  [ 9](2)[list] "HandDropChances"
 |  |   |   |  [0][float] "(null)" 0,085000
 |  |   |   |  [1][float] "(null)" 0,085000
 |  |   |  [10][byte] "PersistenceRequired" 0
 |  |   |  [11][string](23) "id" minecraft:tropical_fish
 |  |   |  [12](3)[list] "Motion"
 |  |   |   |  [0][double] "(null)" -1,960886042814250200000e-003
 |  |   |   |  [1][double] "(null)" 6,832217274102234100000e-002
 |  |   |   |  [2][double] "(null)" 3,907316882209944200000e-002
 |  |   |  [13][byte] "FromBucket" 0
 |  |   |  [14][long] "UUIDLeast" -8688881655459444538
 |  |   |  [15][float] "Health" 3,000000
 |  |   |  [16][byte] "LeftHanded" 0
 |  |   |  [17][short] "Air" 300
 |  |   |  [18][byte] "OnGround" 0
 |  |   |  [19][int] "Dimension" 0
 |  |   |  [20](2)[list] "Rotation"
 |  |   |   |  [0][float] "(null)" 19,987465
 |  |   |   |  [1][float] "(null)" 0,000000
 |  |   |  [21](2)[list] "HandItems"
 |  |   |   |  [0](0)[compound] "(null)"
 |  |   |   |  [1](0)[compound] "(null)"
 |  |   |  [22][int] "Variant" 65536
 |  |   |  [23](4)[list] "ArmorDropChances"
 |  |   |   |  [0][float] "(null)" 0,085000
 |  |   |   |  [1][float] "(null)" 0,085000
 |  |   |   |  [2][float] "(null)" 0,085000
 |  |   |   |  [3][float] "(null)" 0,085000
 |  |   |  [24][long] "UUIDMost" 275805242025984402
 |  |   |  [25](3)[list] "Pos"
 |  |   |   |  [0][double] "(null)" 5,109609436596980500000e+002
 |  |   |   |  [1][double] "(null)" 3,504687589415618600000e+000
 |  |   |   |  [2][double] "(null)" 5,102701384931809800000e+002
 |  |   |  [26][short] "Fire" -1
 |  |   |  [27](4)[list] "ArmorItems"
 |  |   |   |  [0](0)[compound] "(null)"
 |  |   |   |  [1](0)[compound] "(null)"
 |  |   |   |  [2](0)[compound] "(null)"
 |  |   |   |  [3](0)[compound] "(null)"
 |  |   |  [28][byte] "CanPickUpLoot" 0
 |  |   |  [29][short] "HurtTime" 0
*/

static ll UUIDLeast=0;

node *MCACoder::newEntityNode(MobEntity *entity)
{
    node *u;
    node *u_sub;
    node *T = new node(TAG_COMPOUND, "none");


        u = new node(TAG_STRING, "id");
        u->tag.vs = entity->entity_id;
        T->addChild(u);


        u = new node(TAG_LIST, "Pos");
        u->tag.ch_type=TAG_DOUBLE;
            u_sub = new node(TAG_DOUBLE,"none");
            u_sub->tag.vf = (double)entity->position.x;
            u->addChild(u_sub);

            u_sub = new node(TAG_DOUBLE,"none");
            u_sub->tag.vf = (double)entity->position.y;
            u->addChild(u_sub);

            u_sub = new node(TAG_DOUBLE,"none");
            u_sub->tag.vf = (double)entity->position.z;
            u->addChild(u_sub);
        T->addChild(u);


        u = new node(TAG_LIST, "Motion");
        u->tag.ch_type=TAG_DOUBLE;
            u_sub = new node(TAG_DOUBLE,"none");
            u_sub->tag.vf = 0.0;
            u->addChild(u_sub);

            u_sub = new node(TAG_DOUBLE,"none");
            u_sub->tag.vf = 0.0;
            u->addChild(u_sub);

            u_sub = new node(TAG_DOUBLE,"none");
            u_sub->tag.vf = 0.0;
            u->addChild(u_sub);
        T->addChild(u);


        u = new node(TAG_LIST, "Rotation");
        u->tag.ch_type=TAG_FLOAT;
            u_sub = new node(TAG_FLOAT,"none");
            u_sub->tag.vf = 0.0;
            u->addChild(u_sub);

            u_sub = new node(TAG_FLOAT,"none");
            u_sub->tag.vf = 0.0;
            u->addChild(u_sub);
        T->addChild(u);


        u = new node(TAG_FLOAT, "FallDistance");
        u->tag.vf = 0.0;
        T->addChild(u);


        u = new node(TAG_SHORT, "Fire");
        u->tag.vi = 0;
        T->addChild(u);


        u = new node(TAG_SHORT, "Air");
        u->tag.vi = 300;
        T->addChild(u);


        u = new node(TAG_BYTE, "OnGround");
        u->tag.vi = 0;
        T->addChild(u);


        u = new node(TAG_INT, "Dimension");
        u->tag.vi = 0;
        T->addChild(u);


        u = new node(TAG_BYTE, "Invulnerable");
        u->tag.vi = 0;
        T->addChild(u);


        u = new node(TAG_INT, "PortalCooldown");
        u->tag.vi = 0;
        T->addChild(u);


        u = new node(TAG_LONG, "UUIDMost");
        u->tag.vi = region_xxx+region_zzz*1024;
        T->addChild(u);

        u = new node(TAG_LONG, "UUIDLeast");
        u->tag.vi = UUIDLeast++;
        T->addChild(u);

        u = new node(TAG_STRING, "CustomName");
//        u->tag.vs = "Pacman_Graphics";
//        u->tag.vs = "{\"text\":\"Pacman_Graphics\"}";
        char name[100];
        if (entity->entity_id == "minecraft:tropical_fish") {
            int large=0;
            if ((rand()%11)<9) large=1;
            unsigned int Var=(unsigned int) ((large) | ( (rand()%7)*256) | ((rand()%15)*256*256) | ((rand()%15)*256*256*256));
            sprintf(name,"{\"text\":\"Variant_%d\"}",Var);
            u->tag.vs = name;
            T->addChild(u);

            u = new node(TAG_INT, "Variant");
            u->tag.vi = Var;
            T->addChild(u);
        } else {
            sprintf(name,"{\"text\":\"Pacman_Graphics_%d_%d_%d\"}",entity->position.x,entity->position.y,entity->position.z);
            u->tag.vs = name;
            T->addChild(u);
        }
/*
Variant: A 4-byte integer.
The least significant byte has a value of either 0 for a small fish, or 1 for a large fish. Values above 1 result in an invisible fish.
The next byte has a value from 0–5, representing the pattern on the fish. Values above 5 result in a fish with no pattern.
The next byte has a value from 0–14, representing the color of the fish's body.
The most significant byte has a value from 0–14, representing the color of the fish's pattern.
*/

    return T;
}


/*
void MCACoder::getBlock_FAST(const MCRegion &region) {

//    ui** AZ_skylight=skylight[3];

    int n=0;
    BlockInfo*** AX=region.A;
    int num_blocks=0;
    for (int x_outer = 0; x_outer < 512 ; x_outer+=16) {
        int chunk_x = x_outer >> 4;
        int region_x = chunk_x >> 5;
        for (int z_outer = 0; z_outer < 512 ; z_outer+=16) {
            int chunk_z = z_outer >> 4;
            int region_z = chunk_z >> 5;
            int idx = (chunk_x & 31) + 32 * (chunk_z & 31);
            node *chunk_root = Chunk[idx];
            if (!chunk_root) {
                for (int y_outer = 0; y_outer < 256; y_outer+=16) {
                    for (int x_inner = 0; x_inner < 16 ; x_inner++) {
                        int x=x_outer + x_inner;
                        BlockInfo** AZ=AX[x];
                        for (int z_inner = 0; z_inner < 16 ; z_inner++) {
                            int z=z_outer + z_inner;
                            BlockInfo* AY=AZ[z];
                            if (!(n++&31)) toggle2();
                            for (int y_inner = 0; y_inner < 16 ; y_inner++) {
                                int y=y_outer + y_inner;
                                AY[y]=BlockInfo();
                            }
                        }
                    }
                }
                continue;
            }
            node *level_root = chunk_root->childWithName("Level");
            node *sec_root = level_root->childWithName("Sections");
            for (int y_outer = 0; y_outer < 256; y_outer+=16) {
                int sec_no = y_outer >> 4;
                node *T = sectionNodeWithY(sec_root, sec_no);
                if (!T) {
                    for (int x_inner = 0; x_inner < 16 ; x_inner++) {
                        int x=x_outer + x_inner;
                        BlockInfo** AZ=AX[x];
                        for (int z_inner = 0; z_inner < 16 ; z_inner++) {
                            int z=z_outer + z_inner;
                            BlockInfo* AY=AZ[z];
                            if (!(n++&31)) toggle2();
                            for (int y_inner = 0; y_inner < 16 ; y_inner++) {
                                int y=y_outer + y_inner;
                                AY[y]=BlockInfo();
                            }
                        }
                    }
                    continue;
                }
                node *u;

                node *old_u_blocks = T->childWithName("Blocks");
                node *old_u_add = T->childWithName("Add");
                node *old_u_data = T->childWithName("Data");
                node *old_u_blocklight=T->childWithName("BlockLight");
                node *old_u_skylight = T->childWithName("SkyLight");

                for (int x_inner = 0; x_inner < 16 ; x_inner++) {
                    int x=x_outer + x_inner;
                    BlockInfo** AZ=AX[x];
                    for (int z_inner = 0; z_inner < 16 ; z_inner++) {
                        int z=z_outer + z_inner;
                        BlockInfo* AY=AZ[z];
                        if (!(n++&31)) toggle2();

                        for (int y_inner = 0; y_inner < 16 ; y_inner++) {
                            int y=y_outer + y_inner;
                            int block_pos = y_inner * 256 + z_inner * 16 + x_inner;


                            int id= old_u_blocks->tag.va[block_pos];

                            uc res;
                            int add;
                            if (old_u_add) {
                                res = old_u_add->tag.va[block_pos >> 1];
                                add = (block_pos & 1) ? ((res >> 4) & 0xF): (res & 0xF);
                            } else add=0;

                            int data;
                            if (old_u_data) {
                                res = old_u_data->tag.va[block_pos >> 1];
                                data = (block_pos & 1) ? ((res >> 4) & 0xF): (res & 0xF);
                            } else data=0;

                            res = old_u_blocklight->tag.va[block_pos >> 1];
                            int block_light = (block_pos & 1) ? ((res >> 4) & 0xF): (res & 0xF);

                            res = old_u_skylight->tag.va[block_pos >> 1];
                            int sky_light = (block_pos & 1) ? ((res >> 4) & 0xF): (res & 0xF);

                            if (id!=0) {
                                num_blocks++;
                                AY[y]=BlockInfo(id,add,data,block_light,sky_light);
                            } else {
                                AY[y]=BlockInfo();
                            }
                        }
                    }
                }
            }
        }
    }
}
*/
