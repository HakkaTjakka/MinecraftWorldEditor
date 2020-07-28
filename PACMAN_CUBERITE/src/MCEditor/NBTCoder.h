#ifndef NBTCoder_h
#define NBTCoder_h

#include <cstdio>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cstring>
#include "globals.h"

struct NBTData
{
    int type, ch_type; std::string name;
    ll vi; double vf; std::string vs; std::vector<int> va;

    NBTData()
    : type(-1), ch_type(-1), name("none"), vi(0), vf(0), vs("") {
        va.clear();
    }

    NBTData(int type_, const char* name_)
    : type(type_), ch_type(-1), name(name_), vi(0), vf(0), vs("") {
        va.clear();
    }
};

struct node
{
    NBTData tag;
    std::list<node*> ch;

    node() {}
    node(int type_, const char* name_)
    : tag(NBTData(type_, name_)) {}

    void addChild(node* u) { ch.push_back(u); }

    node* childWithName(const char* name)
    {
        for (auto v : this->ch)
            if (v->tag.name == name)
                return v;
        return 0;
    }
};

class NBTCoder
{
public:
    node* Decode(uc* A);
    ull Encode(node* T, uc* A);
    void Print(node* T);
    void Clear(node* T);

    void setIntContent(node* T, ll x);
    void setStringContent(node* T, const std::string &s);
    void setByteArrayContent(node* T, uc* A, ull len);
    void setIntArrayContent(node* T, int* A, ull len);

    uc getByteInArrayContent(node* T, int idx);
    void setByteInArrayContent(node* T, int idx, uc v);
    uc getHalfByteInArrayContent(node* T, int idx);
    void setHalfByteInArrayContent(node* T, int idx, uc v);

private:
    uc* buffer;

    node* decodePayload(int type, ull &offset);
    node* decode(ull &offset);
    node* decodeByte(ull &offset);
    node* decodeShort(ull &offset);
    node* decodeInt(ull &offset);
    node* decodeLong(ull &offset);
    node* decodeFloat(ull &offset);
    node* decodeDouble(ull &offset);
    node* decodeByteArray(ull &offset);
    node* decodeString(ull &offset);
    node* decodeList(ull &offset);
    node* decodeCompound(ull &offset);
    node* decodeIntArray(ull &offset);

    void encodePayload(node* T, ull &offset);
    void encode(node* T, ull &offset);
    void encodeByte(node* T, ull &offset);
    void encodeShort(node* T, ull &offset);
    void encodeInt(node* T, ull &offset);
    void encodeLong(node* T, ull &offset);
    void encodeFloat(node* T, ull &offset);
    void encodeDouble(node* T, ull &offset);
    void encodeByteArray(node* T, ull &offset);
    void encodeString(node* T, ull &offset);
    void encodeList(node* T, ull &offset);
    void encodeCompound(node* T, ull &offset);
    void encodeIntArray(node* T, ull &offset);

    void print(node* T, int d);
};

#endif
