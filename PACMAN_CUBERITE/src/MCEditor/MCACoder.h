#ifndef MCACoder_h
#define MCACoder_h

#include <string>
#include <cstdlib>
#include "NBTCoder.h"
#include "BlockEntity.h"

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

    BlockInfo getBlock(int x, int z, int y);

    void removeBlockEntity(const Pos &position);

    void insertBlockEntity(const Pos &position, BlockEntity* entity);

    void insertEntity(const Pos &position, MobEntity* entity);

    void setHeightMap(int x, int z, int y);

    void writeMCA();

    int loadMCA(const std::string &file_name_MCA);

    std::string current_filename_mca;

private:
    NBTCoder nbt_coder;

    bool modification_saved;

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
