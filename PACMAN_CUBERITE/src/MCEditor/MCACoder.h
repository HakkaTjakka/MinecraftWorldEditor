#ifndef MCACoder_h
#define MCACoder_h

#include <string>
#include <cstdlib>
#include "NBTCoder.h"
#include "BlockEntity.h"

class MCRegion
{
public:
    BlockInfo*** A;
    BlockEntity**** B;

    int x_len, z_len, y_len,
        x_ori, z_ori, y_ori;

    MCRegion() {};

    MCRegion(int x0, int z0, int y0,
             int xl, int zl, int yl);

    ~MCRegion();

    void delBlockEntity(BlockEntity* entity);
//private:
};

class MCACoder
{
public:
    MCACoder()
    : modification_saved(true), current_filename_mca("")
    {
        memset(Chunk, 0, sizeof(Chunk));
    }

    void setPOSITIONS();

    void saveModification();

    void clearModification();

    void setBlock(const Pos &position, const BlockInfo &info);
    void setBlock_old(const Pos &position, const BlockInfo &info);

    BlockInfo getBlock(int x, int z, int y);

    void getBlock_FAST(const MCRegion &region);

    void setBlock_FAST(const MCRegion &region);

    void removeBlockEntity(const Pos &position);

    void insertBlockEntity(const Pos &position, BlockEntity* entity);

    void insertEntity(const Pos &position, MobEntity* entity);

    void setHeightMap(int x, int z, int y);

    void writeMCA();

    int loadMCA(const std::string &file_name_MCA);

    std::string current_filename_mca;

    bool modification_saved;

private:
    NBTCoder nbt_coder;


    node* Chunk[K1];

//sometimes bigger is better....
//    uc buffer[M64], chunk_buffer[M1 << 1];
    uc buffer[M256], chunk_buffer[M1 << 1];

    int location[K1], timestamp[K1];

    node* chunkWithXZ(int x, int z);

    node* sectionNodeWithY(node* T, int y);

    node* newSectionNodeWithY(int y);

    node* newBlockEntityNode(BlockEntity* entity);

    node* newEntityNode(MobEntity* entity);
};

#endif /* MCACoder_h */
