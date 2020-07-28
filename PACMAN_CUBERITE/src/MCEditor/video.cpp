#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "globals.h"
#include "MCEditor.h"
using namespace std;

#define N 64

struct event
{
    int offset, x, y, c;
    event() {}
    event(int offset_, int x_, int y_, int c_)
        : offset(offset_), x(x_), y(y_), c(c_) {}
};

int event_cnt, H, W, L;
vector<event> Track[N][N << 1];

int x_ori, y_ori, z_ori;
//MCRegion Region;
MCEditor Editor;

void setBlockWithCommand(MCRegion &R, int x, int z, int y, const string &cmd);
void setRepeaterWithDelay(MCRegion &R, int x, int z, int y, int delay);
void setConcreteWithColor(MCRegion &R, int x, int z, int y, int color);

char tmp[256] = {0};
string cmdSetConcreteWithColor(int x, int z, int y, int color)
{
    int len = sprintf(tmp, "/setblock %d %d %d minecraft:concrete %d",
                            x, y, z, color);
    if (len < 0)
    {
        fprintf(stderr, "Buffer overflow when generating command string.\n");
        exit(0);
    }
    string res = tmp;
    return res;
}

void setBlockWithCommand(MCRegion &R, int x, int z, int y, const string &cmd)
{
    ui data = 5; //facing east
    R.A[x][z][y] = BlockInfo(137, 0, data);

    Pos position(R.x_ori + x, R.z_ori + z, R.y_ori + y);
    R.B[x][z][y] = new BlockEntityCommand(position, cmd);
}

void setRepeaterWithDelay(MCRegion &R, int x, int z, int y, int delay)
{
    ui data = ((delay - 1) << 2) | 1; //facing east
    R.A[x][z][y] = BlockInfo(93, 0, data);
    R.B[x][z][y] = 0;
}

void setConcreteWithColor(MCRegion &R, int x, int z, int y, int color)
{
    R.A[x][z][y] = BlockInfo(251, 0, color);
    R.B[x][z][y] = 0;
}

void input()
{
    fscanf(stdin, "%d%d%d", &x_ori, &y_ori, &z_ori);

    FILE *in = fopen("events.txt", "r");
    fscanf(in, "%d%d%d", &event_cnt, &H, &W);

    int row = 0, col = 0;
    for (int i = 0; i < event_cnt; i++)
    {
        int offset, x, y, c;
        fscanf(in, "%d%d%d%d", &offset, &x, &y, &c);
        Track[row][col].push_back(event(offset + 8, x, y, c));

        //next position
        col++;
        if (col == W)
            row++, col = 0;
        if (row == H)
            row = 0, col = 0;
    }
    fclose(in);

    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
        {
            int len = 0, offset = 0;
            for (auto e : Track[i][j])
            {
                int dt = e.offset - offset;
                int dlen = dt / 4 + (dt % 4 == 0? 0: 1);
                len += dlen + 1; offset = e.offset;
            }
            L = max(L, len + 10);
        }
}

void buildTrack(MCRegion &R, int row, int col)
{
    int z = col, y = row * 2;
    int offset = 0, x_offset = 0;
    int count = 0;
    for (auto e : Track[row][col])
    {
        int delta = e.offset - offset;
        int q = delta / 4, r = delta % 4;

        for (int x = x_offset; x < x_offset + q; x++)
        {
            setConcreteWithColor(R, x, z, y, 0);
            setRepeaterWithDelay(R, x, z, y + 1, 4);
        }
        x_offset += q;

        if (r)
        {
            setConcreteWithColor(R, x_offset, z, y, 0);
            setRepeaterWithDelay(R, x_offset, z, y + 1, r);
            x_offset++;
        }

        setConcreteWithColor(R, x_offset, z, y, 0);
        string cmd = cmdSetConcreteWithColor(x_ori, z_ori + e.y - W - 10, y_ori + H - e.x, e.c);
        setBlockWithCommand(R, x_offset, z, y + 1, cmd);
        x_offset++;

        offset = e.offset;
    }
}

void work()
{
    MCRegion Region(x_ori, z_ori, y_ori,
                    L, W, H * 2);
    for (int row = 0; row < H; row++)
        for (int col = 0; col < W; col++)
            buildTrack(Region, row, col);
    Editor.setRegion(Region);
}

int main()
{
    input();

    work();

    return 0;
}