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
            for(int j=0; j<zl; j++)
                A[i][j] = (*A[0]+zl*i*yl+yl*j);

        B  	    =   (BlockEntity****)   calloc(xl ,	        sizeof(BlockEntity***));
        B[0]    =   (BlockEntity***)	calloc(xl*zl,	    sizeof(BlockEntity**));
        for(int i=0; i<xl; i++)
            B[i] = (*B+zl*i);

        B[0][0] =   (BlockEntity**)     calloc(xl*zl*yl,	sizeof(BlockEntity*));
        memset(B[0][0], 0, xl*yl*zl*sizeof(BlockEntity*));
        for(int i=0; i<xl; i++) {
            for(int j=0; j<zl; j++) {
                B[i][j] = (*B[0]+zl*i*yl+yl*j);
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

    printf(" computeSkyLight\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
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
    updateMCA();

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
        for (int j = 0; j < z_len; j++) {
            toggle2();
            BlockInfo* AY=AZ[j];
            ui* AY_blockdata=AZ_blockdata[j];
            ui* AY_blocks=AZ_blocks[j];
            for (int k = 0; k < y_len; k++) {
                BlockInfo bi = AY[k];
//                ui *bd = &(AY_blockdata[k]);
                ui id = bi.id | (bi.add << 8);
//                ui id = R.A[i][j][k].id | (R.A[i][j][k].add << 8);
                AY_blocks[k] = id;
//                blocks[i][j][k] = id;
//                blockdata[i][j][k] = bi.data;
//                *bd = bi.data;
                AY_blockdata[k] = bi.data;
//                blockdata[i][j][k] = R.A[i][j][k].data;
            }
        }
    }
//    printf("1");
//hoppa
//    printf("initBlocks(1)\n");
    int x0 = x_ori , x1 = x_ori + x_len , z0 = z_ori , z1 = z_ori + z_len ,  y0 = 0, y1 = 256;

/*
    vector<Pos> V;
    for (int x = 0; x < x_len ; x+=16) {
        for (int z = 0; z < z_len ; z+=16) {
            for (int y = 0; y < 256; y+=16) {
                for (int x_inner = 0; x_inner < 16 ; x_inner++) {
                    toggle2();
                    for (int z_inner = 0; z_inner < 16 ; z_inner++) {
                        for (int y_inner = 0; y_inner < 16 ; y_inner++) {
                            if (in_region(x+x_inner, z+z_inner, y+y_inner,   x_ori, z_ori, y_ori,   x_ori + x_len, z_ori + z_len, y_ori + y_len)) {
                                continue;
                            }
                            //leave edited blocks unchanged;
                            printf("1");

                            V.push_back(Pos(x+x_inner, z+z_inner, y+y_inner));
                        }
                    }
                }
            }
        }
    }


//    printf("initBlocks(2)\n");
//    sort(V.begin(), V.end());

    addnew_counter=0;
    lookup_counter1=0;
    lookup_counter2=0;
    lookup_counter3=0;
    lookup_counter4=0;
    lookup_counter5=0;
    lookup_counter6=0;

    for (Pos u : V) {
        printf("2");
        int i = u.x - x0, j = u.z - z0, k = u.y - y0;
        toggle3();
        BlockInfo res = mca_coder.getBlock(u.x, u.z, u.y);
        blocks[i][j][k] = res.id + (res.add << 8);
        blockdata[i][j][k] = res.data;
        blocklight[i][j][k] = res.block_light;
        skylight[i][j][k] = res.sky_light;
//        toggle3();
    }

*/


//    printf("2");
//    printf("\n");
/*
    printf("Number of lookups: lookup1=%d\n",lookup_counter1);
    printf("Number of lookups: lookup2=%d\n",lookup_counter2);
    printf("Number of lookups: lookup3=%d\n",lookup_counter3);
    printf("Number of lookups: lookup4=%d\n",lookup_counter4);
    printf("Number of lookups: lookup5=%d\n",lookup_counter5);
    printf("Number of lookups: lookup6=%d\n",lookup_counter6);
    printf("Number of addnews: addnews=%d\n",addnew_counter);
    printf("\ninitBlocks(5)\n");
*/
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
                AY_blocklight[y] = get_block_light(AY_blocks[y]);
//                blocklight[x][z][y] = get_block_light(blocks[x][z][y]);
            }
        }
    }
    lightPropagate(blocklight);
    for (int x = 0; x < x_len; x++) {
        ui** AZ_blocks=blocks[x];
        toggle2();
        for (int z = 0; z < z_len; z++) {
            ui* AY_blocks=AZ_blocks[z];
            for (int y = 0; y < 256; y++) {
                if (AY_blocks[y]==50) {
                    AY_blocks[y]=0;
                }
//                if (blocks[x][z][y]==50) {
//                    blocks[x][z][y]=0;
//                }
            }
        }
    }
}

void MCEditor::computeSkyLight()
{
//    fprintf(stderr, "Computing Sky Light...\n");
    for (int x = 00; x < x_len + 00; x++) {
        ui** AZ_skylight=skylight[x];
        toggle2();
        for (int z = 00; z < z_len + 00; z++) {
            ui* AY_skylight=AZ_skylight[z];
            memset(AZ_skylight[z], 0, 256 * sizeof(ui));
//            for (int y = 0; y < 256; y++) skylight[x][z][y] = 0;
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
//                if (get_opacity(blocks[x][z][y]) <= 1) skylight[x][z][y] = 15;
                else break;
            }
        }
    }

    lightPropagate(skylight);
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
            for (int y = 0; y < 255; y++) { if (AY_skylight[y] == 15) { mca_coder.setHeightMap(x + x_ori, z + z_ori, y);  break; } }
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
        for (int z = 0; z < z_len; z++) {
            ui* AY_light=AZ_light[z];
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
                            if (!in_region(vx, vz, vy, 0, 0, 0, x_len , z_len , 256))  continue;
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
