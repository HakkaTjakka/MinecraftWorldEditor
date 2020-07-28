#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "globals.h"
#include "MCEditor.h"
using namespace std;

void setRedStone(MCRegion &R, int x, int z, int y);
void setBlockWithCommand(MCRegion &R, int x, int z, int y, const string &cmd);
void setRepeaterWithDelayDir(MCRegion &R, int x, int z, int y, int delay, int dir);
void setConcreteWithColor(MCRegion &R, int x, int z, int y, int color);

char tmp[256] = {0};
string cmdSetConcreteWithColor(int x, int z, int y, int color)
{
    int len = sprintf(tmp, "/setblock %d %d %d minecraft:concrete %d",
                      x, y, z, color);
    string res = tmp;
    return res;
}

string cmdFillWithAir(int x1, int z1, int y1, int x2, int z2, int y2)
{
    int len = sprintf(tmp, "/fill %d %d %d %d %d %d minecraft:air",
                      x1, y1, z1, x2, y2, z2);
    string res = tmp;
    return res;
}

string cmdTp(int x, int z, int y)
{
    int len = sprintf(tmp, "/tp @p %d %d %d", x, y, z);
    string res = tmp;
    return res;
}

void setRedStone(MCRegion &R, int x, int z, int y)
{
    R.A[x][z][y] = BlockInfo(55, 0, 0);
    R.B[x][z][y] = 0;
}

void setBlockWithCommand(MCRegion &R, int x, int z, int y, const string &cmd)
{
    ui data = 5; //facing east
    R.A[x][z][y] = BlockInfo(137, 0, data);

    Pos position(R.x_ori + x, R.z_ori + z, R.y_ori + y);
    R.B[x][z][y] = new BlockEntityCommand(position, cmd);
}

void setRepeaterWithDelayDir(MCRegion &R, int x, int z, int y, int delay, int dir)
{
    ui data = ((delay - 1) << 2) | ((ui)dir); //facing east
    R.A[x][z][y] = BlockInfo(93, 0, data);
    R.B[x][z][y] = 0;
}

void setConcreteWithColor(MCRegion &R, int x, int z, int y, int color)
{
    R.A[x][z][y] = BlockInfo(251, 0, color);
    R.B[x][z][y] = 0;
}

int D;
int H, W, L;
ui ***A;

int x_ori, y_ori, z_ori;
MCEditor Editor;

void input()
{
    fscanf(stdin, "%d%d%d", &x_ori, &y_ori, &z_ori);
    fscanf(stdin, "%d", &D);

    FILE *in = fopen("frames.txt", "r");
    fscanf(in, "%d%d%d", &L, &H, &W);
    A = new3DUIArray(L, H, W);
    for (int i = 0; i < L; i++)
        for (int j = 0; j < H; j++)
            for (int k = 0; k < W; k++)
                fscanf(in, "%u", &A[i][j][k]);
    fclose(in);
}

void buildFrame(MCRegion &R, int frame)
{
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
        {
            int x = frame;
            int z = j;
            int y = H - 1 - i;
            setConcreteWithColor(R, x, z, y, A[frame][i][j]);
        }
}

void buildControl(MCRegion &R)
{
    for (int frame = 0; frame < L; frame++)
    {
        int x = frame;
        int z = W;
        int y = 0;

        string cmd1 = cmdFillWithAir(x_ori + x, z_ori, y_ori,
                                     x_ori + x, z_ori + W - 1, y_ori + H - 1);
        string cmd2 = cmdTp(x_ori + x - D, z_ori + W / 2, y_ori + H / 2);

        for (int i = 0; i < 10; i++)
        {
            setConcreteWithColor(R, x, z + i, y, 0);
            setConcreteWithColor(R, x, z + i, y + 3, 0);
        }

        if (x % 4 == 0)
        {
            setRedStone(R, x, z + 1, y + 1);
            setRepeaterWithDelayDir(R, x, z + 2, y + 1, 2, 2); //facing south
            setBlockWithCommand(R, x, z + 3, y + 1, cmd1);
            for (int i = 4; i < 8; i++)
                setRepeaterWithDelayDir(R, x, z + i, y + 1, 4, 2);
            setRedStone(R, x, z + 8, y + 1);

            setRedStone(R, x, z + 1, y + 4);
            setRepeaterWithDelayDir(R, x, z + 2, y + 4, 2, 2); //facing south
            setBlockWithCommand(R, x, z + 3, y + 4, cmd2);
            for (int i = 4; i < 8; i++)
                setRepeaterWithDelayDir(R, x, z + i, y + 4, 4, 2);
            setRedStone(R, x, z + 8, y + 4);
        }

        if (x % 4 == 1)
        {
            setRedStone(R, x, z, y + 1);
            setRepeaterWithDelayDir(R, x, z + 1, y + 1, 2, 0); //facing north
            for (int i = 2; i < 6; i++)
                setRepeaterWithDelayDir(R, x, z + i, y + 1, 4, 0);
            setBlockWithCommand(R, x, z + 6, y + 1, cmd1);
            setRepeaterWithDelayDir(R, x, z + 7, y + 1, 4, 0);
            setRedStone(R, x, z + 8, y + 1);

            setRedStone(R, x, z, y + 4);
            setRepeaterWithDelayDir(R, x, z + 1, y + 4, 2, 0); //facing north
            for (int i = 2; i < 6; i++)
                setRepeaterWithDelayDir(R, x, z + i, y + 4, 4, 0);
            setBlockWithCommand(R, x, z + 6, y + 4, cmd2);
            setRepeaterWithDelayDir(R, x, z + 7, y + 4, 4, 0);
            setRedStone(R, x, z + 8, y + 4);
        }

        if (x % 4 == 2)
        {
            setRedStone(R, x, z, y + 1);
            setRepeaterWithDelayDir(R, x, z + 1, y + 1, 2, 2); //facing south
            setBlockWithCommand(R, x, z + 2, y + 1, cmd1);
            for (int i = 3; i < 9; i++)
                setRepeaterWithDelayDir(R, x, z + i, y + 1, 3, 2);
            setRedStone(R, x, z + 9, y + 1);

            setRedStone(R, x, z, y + 4);
            setRepeaterWithDelayDir(R, x, z + 1, y + 4, 2, 2); //facing south
            setBlockWithCommand(R, x, z + 2, y + 4, cmd2);
            for (int i = 3; i < 9; i++)
                setRepeaterWithDelayDir(R, x, z + i, y + 4, 3, 2);
            setRedStone(R, x, z + 9, y + 4);
        }

        if (x % 4 == 3)
        {
            setRedStone(R, x, z + 1, y + 1);
            setRepeaterWithDelayDir(R, x, z + 2, y + 1, 2, 0); //facing north
            for (int i = 3; i < 7; i++)
                setRepeaterWithDelayDir(R, x, z + i, y + 1, 4, 0);
            setBlockWithCommand(R, x, z + 7, y + 1, cmd1);
            setRepeaterWithDelayDir(R, x, z + 8, y + 1, 2, 0);
            setRedStone(R, x, z + 9, y + 1);

            setRedStone(R, x, z + 1, y + 4);
            setRepeaterWithDelayDir(R, x, z + 2, y + 4, 2, 0); //facing north
            for (int i = 3; i < 7; i++)
                setRepeaterWithDelayDir(R, x, z + i, y + 4, 4, 0);
            setBlockWithCommand(R, x, z + 7, y + 4, cmd2);
            setRepeaterWithDelayDir(R, x, z + 8, y + 4, 2, 0);
            setRedStone(R, x, z + 9, y + 4);
        }
    }
}

void work()
{
    MCRegion Region(x_ori, z_ori, y_ori,
                    L + 3, W + 10, max(H, 5));
    for (int frame = 0; frame < L; frame++)
        buildFrame(Region, frame);
    buildControl(Region);
    Editor.setRegion(Region);
}

int main()
{
    input();

    work();

    del3DUIArray(A, L, H, W);

    return 0;
}