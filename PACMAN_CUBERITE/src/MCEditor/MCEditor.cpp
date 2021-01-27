#include "MCEditor.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <set>
#include <cstring>
#include "globals.h"


using namespace std;
extern int old_idx;
extern int old_sec_no;
extern node *old_T;
extern node *old_sec_root;
extern int remove_block_entities;

extern int first;
extern int toggle4();
extern int toggle3();
extern int toggle2();
inline bool in_region(int x, int z, int y,   int x1, int z1, int y1,  int x2, int z2, int y2) {
    return x1 <= x && x < x2 && z1 <= z && z < z2 && y1 <= y && y < y2;
}
int lookup_counter1=0;
int lookup_counter2=0;
int lookup_counter3=0;
int lookup_counter4=0;
int lookup_counter5=0;
int lookup_counter6=0;
int addnew_counter=0;

    /////////////////////////////////Region Member Functions////////////////////////

MCRegion::MCRegion(int x0, int z0, int y0,
                   int xl, int zl, int yl)
{
    A  	    =   (BlockInfo***)      calloc(xl ,	        sizeof(BlockInfo**));
    A[0]    =   (BlockInfo**)	    calloc(xl*zl,	    sizeof(BlockInfo*));
    for(int i=0; i<xl; i++)
        A[i] = (*A+zl*i);

    A[0][0] =   (BlockInfo*)        calloc(xl*zl*yl,	sizeof(BlockInfo));
    for(int i=0; i<xl; i++)
        for(int j=0; j<zl; j++) {
            A[i][j] = (*A[0]+zl*i*yl+yl*j);
            memset(A[i][j], 0, yl * sizeof(BlockInfo));
        }

    B  	    =   (BlockEntity****)   calloc(xl ,	        sizeof(BlockEntity***));
    B[0]    =   (BlockEntity***)	calloc(xl*zl,	    sizeof(BlockEntity**));
    for(int i=0; i<xl; i++)
        B[i] = (*B+zl*i);

    B[0][0] =   (BlockEntity**)     calloc(xl*zl*yl,	sizeof(BlockEntity*));
    memset(B[0][0], 0, xl*yl*zl*sizeof(BlockEntity*));
    for(int i=0; i<xl; i++) {
        for(int j=0; j<zl; j++) {
            B[i][j] = (*B[0]+zl*i*yl+yl*j);
            memset(B[i][j], 0, yl * sizeof(BlockEntity*));
        }
    }

    x_len = xl, z_len = zl, y_len = yl;
    x_ori = x0, z_ori = z0, y_ori = y0;
}

MCRegion::~MCRegion()
{
    free(A[0][0]);
    free(A[0]);
    free(A);
    for (int i = 0; i < x_len; i++)
        for (int j = 0; j < z_len; j++)
            for (int k = 0; k < y_len; k++)
                if (B[i][j][k]) delBlockEntity(B[i][j][k]);
    free(B[0][0]);
    free(B[0]);
    free(B);
}

/*
MCRegion::MCRegion(int x0, int z0, int y0,
                   int xl, int zl, int yl)
{
    A = new BlockInfo** [xl];
    for (int i = 0; i < xl; i++)
    {
        A[i] = new BlockInfo* [zl];
        for (int j = 0; j < zl; j++)
            A[i][j] = new BlockInfo [yl];
    }

    B = new BlockEntity*** [xl];
    for (int i = 0; i < xl; i++)
    {
        B[i] = new BlockEntity** [zl];
        for (int j = 0; j < zl; j++)
        {
            B[i][j] = new BlockEntity* [yl];
            memset(B[i][j], 0, yl * sizeof(BlockEntity*));
        }
    }

    x_len = xl, z_len = zl, y_len = yl;
    x_ori = x0, z_ori = z0, y_ori = y0;
}

MCRegion::~MCRegion()
{
    for (int i = 0; i < x_len; i++)
    {
        for (int j = 0; j < z_len; j++)
            delete [] A[i][j];
        delete [] A[i];
    }
    delete A;

    for (int i = 0; i < x_len; i++)
    {
        for (int j = 0; j < z_len; j++)
        {
            for (int k = 0; k < y_len; k++)
                delBlockEntity(B[i][j][k]);
            delete [] B[i][j];
        }
        delete [] B[i];
    }
    delete B;
}
*/

/*
MCRegion::MCRegion(int x0, int z0, int y0, int xl, int zl, int yl) {

    A = (BlockInfo***) malloc( sizeof(BlockInfo**) * xl);
    for (int i = 0; i < xl; i++) {
        A[i] = (BlockInfo**) malloc( sizeof(BlockInfo*) * zl);
        for (int j = 0; j < zl; j++) {
            A[i][j] = (BlockInfo*) malloc( sizeof(BlockInfo) * yl);
            memset(A[i][j], 0, yl * sizeof(BlockInfo));
        }
    }

    B = (BlockEntity****) malloc( sizeof(BlockEntity***) * xl);
    for (int i = 0; i < xl; i++) {
        B[i] = (BlockEntity***) malloc( sizeof(BlockEntity**) * zl);
        for (int j = 0; j < zl; j++) {
            B[i][j] = (BlockEntity**) malloc( sizeof(BlockEntity*) * yl);
            memset(B[i][j], 0, yl * sizeof(BlockEntity*));
        }
    }

    x_len = xl, z_len = zl, y_len = yl;
    x_ori = x0, z_ori = z0, y_ori = y0;
}
*/


/*
MCRegion::~MCRegion() //crashes on....THIS.
{
    for (int i = 0; i < x_len; i++)
    {
        for (int j = 0; j < z_len; j++) {
            if (A[i][j]!=NULL) { free(A[i][j]); A[i][j]=NULL; }
            for (int k = 0; k < y_len; k++) delBlockEntity(B[i][j][k]);
            if (B[i][j]!=NULL) { free(B[i][j]); B[i][j]=NULL; }
        }
        if (A[i]!=NULL) { free(A[i]); A[i]=NULL; };
        if (B[i]!=NULL) { free(B[i]); B[i]=NULL; };
    }
    if (A!=NULL) { free(A); A=NULL; }
    if (B!=NULL) { free(B); B=NULL; }
}
*/

void MCRegion::delBlockEntity(BlockEntity* entity)
{
    if (!entity) return;

    string id = entity->entity_id;
    if (id == "minecraft:noteblock") {
        delete ((BlockEntityNote*)entity);
    } else if (id == "minecraft:teglowstone") {
        delete ((BlockEntityGlowColor*)entity);
//        printf("Entity deleted\n");
    } else {
        delete entity;
    }
    entity=NULL;
    //TODO
}

////////////////////////////////MCEditor Member Functions///////////////////////

void MCEditor::setRegion(const MCRegion &R)
{
    x_len = R.x_len, z_len = R.z_len, y_len = R.y_len;
    x_ori = R.x_ori, z_ori = R.z_ori, y_ori = R.y_ori;
    block_entities = R.B;

    initArrays(x_len + 00, z_len + 00, 256);

    printf(" initBlocks\b\b\b\b\b\b\b\b\b\b\b");
    initBlocks(R);

    printf(" computeBlockLight\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    computeBlockLight(R);
//    printf("3");

    printf(" computeSkyLight   \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    computeSkyLight();

//    printf(" ");
/*
    printf(" Clear all lights");
    for (int x = 0; x < x_len; x++) {
        for (int z = 0; z < z_len; z++) {
            for (int y = 0; y < 256; y++) {
                blocklight[x][z][y]=0;
                skylight[x][z][y]=0;
            }
        }
    }
*/

    printf(" updateMCA\b\b\b\b\b\b\b\b\b\b");

    mca_coder.modification_saved = false;

    updateMCA_FAST(R);

//    updateMCA();

//    printf("clearArrays()\n");
    clearArrays(x_len + 00, z_len + 00, 256);
}

void MCEditor::initArrays(int l1, int l2, int l3)
{
    blocks = new3DUIArray(l1, l2, l3);
    blockdata = new3DUIArray(l1, l2, l3);
    blocklight = new3DUIArray(l1, l2, l3);
    skylight = new3DUIArray(l1, l2, l3);
}

void MCEditor::clearArrays(int l1, int l2, int l3)
{
    del3DUIArray(blocks, l1, l2, l3);
    del3DUIArray(blockdata, l1, l2, l3);
    del3DUIArray(blocklight, l1, l2, l3);
    del3DUIArray(skylight, l1, l2, l3);
}


void MCEditor::initBlocks(const MCRegion &R)
{
    BlockInfo*** AX=R.A;

    printf("Computing: ");
    for (int i = 0; i < x_len; i++) {
        BlockInfo** AZ=AX[i];
        ui** AZ_blockdata=blockdata[i];
        ui** AZ_blocks=blocks[i];
        ui** AZ_blocklight=blocklight[i];
        for (int j = 0; j < z_len; j++) {
            toggle2();
            BlockInfo* AY=AZ[j];
            ui* AY_blockdata=AZ_blockdata[j];
            ui* AY_blocks=AZ_blocks[j];
            ui* AY_blocklight=AZ_blocklight[j];
            for (int k = 0; k < y_len; k++) {
                BlockInfo bi = AY[k];
                ui id = bi.id | (bi.add << 8);
                AY_blocks[k] = id;
                AY_blockdata[k] = bi.data;
                AY_blocklight[k] = bi.block_light;
            }
        }
    }
    int x0 = x_ori , x1 = x_ori + x_len , z0 = z_ori , z1 = z_ori + z_len ,  y0 = 0, y1 = 256;
}

            //hoppa
void MCEditor::computeBlockLight(const MCRegion &R)
{
//    fprintf(stderr, "Computing Block Light...\n");
    for (int x = 0; x < x_len;  x++) {
        ui** AZ_blocklight=blocklight[x];
        ui** AZ_blocks=blocks[x];
        toggle2();
        for (int z = 0; z < z_len; z++) {
            ui* AY_blocklight=AZ_blocklight[z];
            ui* AY_blocks=AZ_blocks[z];
            for (int y = 0; y < 256; y++) {
/*
                if (blocks[x][z][y]==50) {
                    blocklight[x][z][y]=14;
                } else
                    blocklight[x][z][y]=0;
*/
//                if (AY_blocklight[y]==(ui)0)
                    ui bl = get_block_light(AY_blocks[y]);
                    if (bl > AY_blocklight[y]) AY_blocklight[y]=bl;
//                blocklight[x][z][y] = get_block_light(blocks[x][z][y]);
            }
        }
    }
    lightPropagate(blocklight);
/*
    for (int x = 0; x < x_len; x++) {
        ui** AZ_blocks=blocks[x];
        toggle2();
        for (int z = 0; z < z_len; z++) {
            ui* AY_blocks=AZ_blocks[z];
            for (int y = 0; y < 256; y++) {
//lightlight
//                if (AY_blocks[y]==50 || AY_blocks[y]==76) {
//                    AY_blocks[y]=0;
//                }
//                if (blocks[x][z][y]==50) {
//                    blocks[x][z][y]=0;
//                }
            }
        }
    }
*/
}

void MCEditor::computeSkyLight()
{
    for (int x = 00; x < x_len + 00; x++) {
        ui** AZ_skylight=skylight[x];
        toggle2();
        for (int z = 00; z < z_len + 00; z++) {
            ui* AY_skylight=AZ_skylight[z];
            memset(AZ_skylight[z], 0, 256 * sizeof(ui));
        }
    }

    for (int x = 00; x < x_len + 00; x++) {
        ui** AZ_skylight=skylight[x];
        ui** AZ_blocks=blocks[x];
        toggle2();
        for (int z = 00; z < z_len + 00; z++) {
            ui* AY_skylight=AZ_skylight[z];
            ui* AY_blocks=AZ_blocks[z];
            for (int y = 255; y >= 0; y--) {
                if (get_opacity(AY_blocks[y]) <= 1) AY_skylight[y] = 15;
                else break;
            }
        }
    }

    lightPropagate(skylight);
}

void MCEditor::updateMCA_FAST(const MCRegion &R)
{
    //remove block entities in the editing region;
    printf("- Packing: ");

    int x0 = x_ori , z0 = z_ori ;

    BlockInfo*** AX=R.A;

    for (int x = 0; x < x_len ; x+=16) {
        for (int z = 0; z < z_len ; z+=16) {
            toggle2();
            for (int y = 0; y < 256; y+=16) {
                for (int x_inner = 0; x_inner < 16 ; x_inner++) {
                    BlockInfo** AZ=AX[x+x_inner];

                    ui** AZ_skylight=skylight[x+x_inner];
                    ui** AZ_blocks=blocks[x+x_inner];
                    ui** AZ_blocklight=blocklight[x+x_inner];
                    ui** AZ_blockdata=blockdata[x+x_inner];

                    for (int z_inner = 0; z_inner < 16 ; z_inner++) {
                        BlockInfo* AY=AZ[z+z_inner];

                        ui* AY_skylight=AZ_skylight[z+z_inner];
                        ui* AY_blocks=AZ_blocks[z+z_inner];
                        ui* AY_blocklight=AZ_blocklight[z+z_inner];
                        ui* AY_blockdata=AZ_blockdata[z+z_inner];

                        for (int y_inner = 0; y_inner < 16 ; y_inner++) {
                            int y_tot=y+y_inner;

                            ui id = AY_blocks[y_tot] & (ui)0xFF;
//                            if (id!=(ui)0) {
                                ui add = (AY_blocks[y_tot] >> 8) & 0xF;
                                ui data = AY_blockdata[y_tot];
                                AY[y_tot] = BlockInfo(id, add, data, AY_blocklight[y_tot], AY_skylight[y_tot]);
//                            }
                        }
                    }
                }
            }
        }
    }

    printf("1");

    mca_coder.setBlock_FAST(R);

    printf("2");

    for (int x = 00; x < x_len + 00; x++) {
        ui** AZ_skylight=skylight[x];
        for (int z = 00; z < z_len + 00; z++) {
            ui* AY_skylight=AZ_skylight[z];
            toggle2();
            for (int y = 0; y < 256; y++) {
                if (AY_skylight[y] == 15) {
                    mca_coder.setHeightMap(x + x_ori, z + z_ori, y);  break;
                }
            }
        }
    }

    printf("3");

    printf("Save modification: ");
    mca_coder.saveModification();
    printf(" Saved.");
}


void MCEditor::updateMCA()
{
    //remove block entities in the editing region;
    printf("- Packing: ");
    vector<Pos> VP;
    for (int x = 0; x < x_len; x++) {
        toggle2();
        for (int z = 0; z < z_len; z++) {
            for (int y = 0; y < y_len; y++) {
                VP.push_back(Pos(x + x_ori, z + z_ori, y + y_ori));
            }
        }
    }
//    printf("1");
//    printf("sort()\n");
//    sort(VP.begin(), VP.end());

//hoppa
    printf("-");
extern int remove_block_entities;
    if (remove_block_entities)
        for (auto position : VP) {  toggle3();   mca_coder.removeBlockEntity(position);  }
    printf("-");

    //update blocks
    vector<Block> VB;

    int x0 = x_ori , z0 = z_ori ;

    for (int x = 0; x < x_len ; x+=16) {
        for (int z = 0; z < z_len ; z+=16) {
            toggle2();
            for (int y = 0; y < 256; y+=16) {
                for (int x_inner = 0; x_inner < 16 ; x_inner++) {
                    ui** AZ_skylight=skylight[x+x_inner];
                    ui** AZ_blocks=blocks[x+x_inner];
                    ui** AZ_blocklight=blocklight[x+x_inner];
                    ui** AZ_blockdata=blockdata[x+x_inner];

                    for (int z_inner = 0; z_inner < 16 ; z_inner++) {
                        ui* AY_skylight=AZ_skylight[z+z_inner];
                        ui* AY_blocks=AZ_blocks[z+z_inner];
                        ui* AY_blocklight=AZ_blocklight[z+z_inner];
                        ui* AY_blockdata=AZ_blockdata[z+z_inner];

                        for (int y_inner = 0; y_inner < 16 ; y_inner++) {
                            Pos position = Pos(x + x0 + x_inner, z + z0 + z_inner, y + y_inner);
                            int y_tot=y+y_inner;

                            ui id = AY_blocks[y_tot] & (ui)0xFF;
//                            ui id = blocks[x+x_inner][z+z_inner][y+y_inner] & (ui)0xFF;
                            ui add = (AY_blocks[y_tot] >> 8) & 0xF;
//                            ui add = (blocks[x+x_inner][z+z_inner][y+y_inner] >> 8) & 0xF;
//                            if (add>0 || (z==0 && y==1 && x<4))
//                                printf("hier 2: add=%u  x=%d, z=%d, y=%d\n",add,x+x_inner,z+z_inner,y+y_inner);
                            ui data = AY_blockdata[y_tot];
//                            ui data = blockdata[x+x_inner][z+z_inner][y+y_inner];
                            BlockInfo info = BlockInfo(id, add, data, AY_blocklight[y_tot], AY_skylight[y_tot]);
//                            BlockInfo info = BlockInfo(id, add, data, blocklight[x+x_inner][z+z_inner][y+y_inner], skylight[x+x_inner][z+z_inner][y+y_inner]);
                            VB.push_back(Block(position, info));
                        }
                    }
                }
            }
        }
    }
//    printf("3");

    printf("-");

//    printf("sort()\n");
//    sort(VB.begin(), VB.end());

    addnew_counter=0;
    lookup_counter1=0;
    lookup_counter2=0;
    lookup_counter3=0;
    lookup_counter4=0;
    lookup_counter5=0;
    lookup_counter6=0;

    old_idx=0;
    old_sec_no=0;
    old_T=0;
    old_sec_root=0;

    for (Block u : VB) {  mca_coder.setBlock(u.position, u.info);/*  toggle3();*/  }
//    printf("4");
    printf("-");

    old_idx=0;
    old_sec_no=0;
    old_T=0;
    old_sec_root=0;
//    printf("\n");
/*
    printf("Number of lookups: lookup1=%d\n",lookup_counter1);
    printf("Number of lookups: lookup2=%d\n",lookup_counter2);
    printf("Number of lookups: lookup3=%d\n",lookup_counter3);
    printf("Number of lookups: lookup4=%d\n",lookup_counter4);
    printf("Number of lookups: lookup5=%d\n",lookup_counter5);
    printf("Number of lookups: lookup6=%d\n",lookup_counter6);
    printf("Number of addnews: addnews=%d\n",addnew_counter);
*/
    //update HeightMap
//hoppa
//    printf("\nsetHeightMap: ");
    for (int x = 00; x < x_len + 00; x++) {
        ui** AZ_skylight=skylight[x];
        for (int z = 00; z < z_len + 00; z++) {
            ui* AY_skylight=AZ_skylight[z];
            toggle2();
//tuuttuut
            for (int y = 0; y < 256; y++) { if (AY_skylight[y] == 15) { mca_coder.setHeightMap(x + x_ori, z + z_ori, y);  break; } }
//            for (int y = 0; y < 255; y++) { if (skylight[x][z][y] == 15) { mca_coder.setHeightMap(x + x_ori, z + z_ori, y);  break; } }
        }
    }
//    printf("5");
    printf("-");

    //insert associated block entities
//    printf("Make pair: ");
    vector<pair<Pos, BlockEntity*> > VE;
    for (int x = 0; x < x_len; x++) {
        BlockEntity*** AZ_block_entities=block_entities[x];
        for (int z = 0; z < z_len; z++) {
            BlockEntity** AY_block_entities=AZ_block_entities[z];
            toggle2();
            for (int y = 0; y < y_len; y++) { VE.push_back(make_pair(Pos(x + x_ori, z + z_ori, y + y_ori), AY_block_entities[y])); }
//            for (int y = 0; y < y_len; y++) { VE.push_back(make_pair(Pos(x + x_ori, z + z_ori, y + y_ori), block_entities[x][z][y])); }
        }
    }
//    printf("6");
//    sort(VE.begin(), VE.end());
    printf("-");

//    printf("insertBlockEntity()\n");
//    printf("Insert: ");
    for (auto u : VE) { mca_coder.insertBlockEntity(u.first, u.second);  toggle3(); }

    //make sure that all modifications are saved
//    printf("\n");
    printf("Save modification: ");
    mca_coder.saveModification();
    printf(" Saved.");
}

void MCEditor::lightPropagate(ui*** light)
{
//    fprintf(stderr, "Propagating Light...\n");
    queue<Pos> Q;

    for (int x = 0; x < x_len; x++) {
        ui** AZ_light=light[x];
//        ui** AZ_blocks=blocks[x];
        for (int z = 0; z < z_len; z++) {
            ui* AY_light=AZ_light[z];
//            ui* AY_blocks=AZ_blocks[z];
            toggle2();
            for (int y = 255; y >= 0; y--) {
                if (AY_light[y]) {
//                if (light[x][z][y]) {
                    Q.push(Pos(x, z, y));
                    while (!Q.empty()) {
                        Pos u = Q.front();
                        Q.pop();
                        for (int d = 0; d < 6; d++) {
                            int vx = u.x + DX[d],   vz = u.z + DZ[d],     vy = u.y + DY[d];
                            if (vx<0 || vx>=x_len || vz<0 || vz>=z_len || vy<0 || vy>=256) continue;
//                            if (!in_region(vx, vz, vy, 0, 0, 0, x_len , z_len , 256))  continue;

                            int dec = get_opacity(blocks[vx][vz][vy]);
                            int vlight = (int)light[u.x][u.z][u.y] - dec;
                            if (vlight <= 0) continue;
                            if (light[vx][vz][vy] < vlight) {
                                light[vx][vz][vy] = vlight;
                                Q.push(Pos(vx, vz, vy));
                            }
                        }
                    }
                }
            }
        }
    }
//    fprintf(stderr, "Finished Propagating Light.\n");
}


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
//                node *u;

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

                            uc id;
                            if (old_u_blocks) {
                                id = (int)old_u_blocks->tag.va[block_pos];
                            } else id=0;

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

//uc NBTCoder::getHalfByteInArrayContent(node* T, int idx)
//    uc res = T->tag.va[idx >> 1];
//    return (idx & 1)? ((res >> 4) & 0xF): (res & 0xF);

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

extern int region_xxx,region_zzz;

void MCACoder::setBlock_FAST(const MCRegion &region) {

//    ui** AZ_skylight=skylight[3];

    int totx=region_xxx*512;
    int totz=region_zzz*512;

    int n=0;
    BlockEntity**** BX=region.B;
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
//                fprintf(stderr, "1) Chunk %d,%d not initialized\n", chunk_x, chunk_z);
/*
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
*/
                //nbt_coder.Clear(Chunk[i]);
                continue;
//                return;
            }

            node *level_root = chunk_root->childWithName("Level");
            node *sec_root = level_root->childWithName("Sections");

            node *tile_root  = level_root->childWithName("TileEntities");
            if (!tile_root) {  fprintf(stderr,"TileEntities does not exits chunk (%d, %d)\n", chunk_x, chunk_z); }
            else {
                if (remove_block_entities) {
                    for (auto it = tile_root->ch.begin(); it != tile_root->ch.end(); it++)
                    {
                        node *u = *it;

//                        if (u->ch.empty()) continue;

                        nbt_coder.Clear(u);
//                        delete u;
//                        it = tile_root->ch.erase(it);
//                        break;
                    }
//                    nbt_coder.Clear(u);
                    tile_root->ch.clear();
                }
            }

            bool content_chunk=false;
            for (int y_outer = 0; y_outer < 256; y_outer+=16) {
                int sec_no = y_outer >> 4;

                node *T = sectionNodeWithY(sec_root, sec_no);

                if (!T) {
                    bool content=false;
                    for (int x_inner = 0; x_inner < 16 ; x_inner++) {
                        int x=x_outer + x_inner;
                        BlockInfo** AZ=AX[x];
                        for (int z_inner = 0; z_inner < 16 ; z_inner++) {
                            int z=z_outer + z_inner;
                            BlockInfo* AY=AZ[z];
                            if (!(n++&31)) toggle2();
                            for (int y_inner = 0; y_inner < 16 ; y_inner++) {
                                int y=y_outer + y_inner;
                                if (AY[y].id!=0) {
                                    content=true;
                                    break;
                                }
                            }
                            if (content) break;
                        }
                        if (content) break;
                    }
                    if (!content) continue;

                    T = newSectionNodeWithY(sec_no);
                    sec_root->addChild(T);
                }

                node *old_u_blocks = T->childWithName("Blocks");
                node *old_u_add = T->childWithName("Add");
                node *old_u_data = T->childWithName("Data");
                node *old_u_blocklight=T->childWithName("BlockLight");
                node *old_u_skylight = T->childWithName("SkyLight");

                bool content_section=false;
                for (int x_inner = 0; x_inner < 16 ; x_inner++) {
                    int x=x_outer + x_inner;
                    BlockInfo** AZ=AX[x];
                    BlockEntity*** BZ=BX[x];

                    for (int z_inner = 0; z_inner < 16 ; z_inner++) {
                        int z=z_outer + z_inner;
                        BlockInfo* AY=AZ[z];
                        BlockEntity** BY=BZ[z];
                        if (!(n++&31)) toggle2();

                        BlockInfo* info;
                        BlockEntity* entity;

                        for (int y_inner = 0; y_inner < 16 ; y_inner++) {
                            int y=y_outer + y_inner;
                            int block_pos = y_inner * 256 + z_inner * 16 + x_inner;

                            info=&AY[y];
                            entity=BY[y];

                            if (entity) {
                                tile_root->tag.ch_type = TAG_COMPOUND;
                                tile_root->addChild(newBlockEntityNode(entity));
                            }

                            if (info->id!=0) content_section=true;

                            if (old_u_blocks) {
                                nbt_coder.setByteInArrayContent(old_u_blocks, block_pos, (uc)info->id);
                            }

                            if (old_u_add || info->add)
                            {
                                if (!old_u_add)
                                {
                                    old_u_add = new node(TAG_BYTE_ARRAY, "Add");
                                    old_u_add->tag.va.resize(K2);
                                    T->addChild(old_u_add);
                                }
                                nbt_coder.setHalfByteInArrayContent(old_u_add, block_pos, info->add);
                            }

                            if (old_u_data) {
                                nbt_coder.setHalfByteInArrayContent(old_u_data, block_pos, info->data);
                            };

                            nbt_coder.setHalfByteInArrayContent(old_u_blocklight, block_pos, info->block_light);
                            nbt_coder.setHalfByteInArrayContent(old_u_skylight, block_pos, info->sky_light);
                        }
                    }
                }
//                if (!content_section) {
//                    nbt_coder.Clear(T);
//                }
            }
        }
    }
}



void MCACoder::setBlock_old(const Pos &position, const BlockInfo &info)
//void setBlock_old(const Pos &position, const BlockInfo &info)
{

    //fprintf(stderr, "Setting (%d, %d, %d).\n", x, y, z);
    int x = position.x, z = position.z, y = position.y;

    int chunk_x = x >> 4, chunk_z = z >> 4;
    int region_x = chunk_x >> 5, region_z = chunk_z >> 5;

//    static string file_name_MCA;
//    static int region_x_old=0,region_z_old=0;
//    static int first_MCEDIT=1;

    int idx = (chunk_x & 31) + 32 * (chunk_z & 31);
    node *chunk_root = Chunk[idx];

    if (!chunk_root) { fprintf(stderr, "1) Chunk that contains (%d, %d, %d) not initialized\n", x, y, z); return; }

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
