#include "NBTCoder.h"
using namespace std;

node* NBTCoder::Decode(uc* A)
{
    buffer = A;
    ull offset = 0;
    return decode(offset);
}

ull NBTCoder::Encode(node* T, uc* A)
{
    buffer = A;
    ull offset = 0;
    encode(T, offset);
    return offset;
}

void NBTCoder::Print(node* T)
{
    print(T, 0);
}

void NBTCoder::Clear(node* T)
{
    if (!T) return;
    for (node* u : T->ch)
        Clear(u);
    delete(T);
}

void NBTCoder::setIntContent(node *T, ll x)
{
    switch (T->tag.type)
    {
        case 1: T->tag.vi = (char)x; break;
        case 2: T->tag.vi = (short)x; break;
        case 3: T->tag.vi = (int)x; break;
        case 4: T->tag.vi = x; break;
        default: break;
    }
}

void NBTCoder::setStringContent(node* T, const string &s)
{
    T->tag.vs = s;
}

void NBTCoder::setByteArrayContent(node* T, uc* A, ull len)
{
    T->tag.va.clear();
    for (int i = 0; i < len; i++)
        T->tag.va.push_back(A[i]);
}

void NBTCoder::setIntArrayContent(node* T, int* A, ull len)
{
    T->tag.va.clear();
    for (int i = 0; i < len; i++)
        T->tag.va.push_back(A[i]);
}

uc NBTCoder::getByteInArrayContent(node* T, int idx)
{
    return T->tag.va[idx];
}

void NBTCoder::setByteInArrayContent(node* T, int idx, uc v)
{
    T->tag.va[idx] = v;
}

uc NBTCoder::getHalfByteInArrayContent(node* T, int idx)
{
    uc res = T->tag.va[idx >> 1];
    return (idx & 1)? ((res >> 4) & 0xF): (res & 0xF);
}

void NBTCoder::setHalfByteInArrayContent(node* T, int idx, uc v)
{
    v &= 0xF;
    uc x = T->tag.va[idx >> 1];
    if (idx & 1)
        x = (x & 0xF) | (v << 4);
    else x = (x & (0xF << 4)) | v;
    T->tag.va[idx >> 1] = x;
}

///////////////////////////////Private Functions////////////////////////////////

node* NBTCoder::decodePayload(int type, ull &offset)
{
    node* root = NULL;
    switch (type)
    {
        case 0: root = NULL; break;
        case 1: root = decodeByte(offset); break;
        case 2: root = decodeShort(offset); break;
        case 3: root = decodeInt(offset); break;
        case 4: root = decodeLong(offset); break;
        case 5: root = decodeFloat(offset); break;
        case 6: root = decodeDouble(offset); break;
        case 7: root = decodeByteArray(offset); break;
        case 8: root = decodeString(offset); break;
        case 9: root = decodeList(offset); break;
        case 10: root = decodeCompound(offset); break;
        case 11: root = decodeIntArray(offset); break;
        default: root = NULL;
    }
    return root;
}

node* NBTCoder::decode(ull &offset)
{
    int type = buffer[offset]; offset++;
    int name_len = (int)byteToInt(buffer, offset, 2); offset += 2;
    string name = byteToString(buffer, offset, name_len); offset += name_len;

    node *root = decodePayload(type, offset);

    if (!root) return root;
    root->tag.type = type; root->tag.name = name;
    return root;
}

node* NBTCoder::decodeByte(ull &offset)
{
    node* root = new node();
    root->tag.vi = (char)byteToInt(buffer, offset, 1);
    root->tag.vi = (char)byteToInt(buffer, offset, 1);
    offset += 1;
    return root;
}

node* NBTCoder::decodeShort(ull &offset)
{
    node* root = new node();
    root->tag.vi = (short)byteToInt(buffer, offset, 2);
    offset += 2;
    return root;
}

node* NBTCoder::decodeInt(ull &offset)
{
    node* root = new node();
    root->tag.vi = (int)byteToInt(buffer, offset, 4);
    offset += 4;
    return root;
}

node* NBTCoder::decodeLong(ull &offset)
{
    node* root = new node();
    root->tag.vi = byteToInt(buffer, offset, 8);
    offset += 8;
    return root;
}

node* NBTCoder::decodeFloat(ull &offset)
{
    node* root = new node();
    root->tag.vf = byteToFloat(buffer, offset, 4);
    offset += 4;
    return root;
}

node* NBTCoder::decodeDouble(ull &offset)
{
    node* root = new node();
    root->tag.vf = byteToDouble(buffer, offset, 8);
    offset += 8;
    return root;
}

node* NBTCoder::decodeByteArray(ull &offset)
{
    node* root = new node();
    int len = (int)byteToInt(buffer, offset, 4);
    offset += 4;

    root->tag.va.clear();
    for (int i = 0; i < len; i++)
    {
        root->tag.va.push_back((char)byteToInt(buffer, offset, 1));
        offset += 1;
    }

    return root;
}

node* NBTCoder::decodeString(ull &offset)
{
    node* root = new node();

    int len = (short)byteToInt(buffer, offset, 2);
    offset += 2;

    root->tag.vs = byteToString(buffer, offset, len);
    offset += len;

    return root;
}

node* NBTCoder::decodeList(ull &offset)
{
    node* root = new node();

    int type = (char)byteToInt(buffer, offset, 1);
    root->tag.ch_type = type;
    offset++;

    int len = (int)byteToInt(buffer, offset, 4);
    offset += 4;

    root->ch.clear();
    for (int i = 0; i < len; i++)
    {
        node* u = decodePayload(type, offset);
        u->tag.type = type;
        root->ch.push_back(u);
    }

    return root;
}

node* NBTCoder::decodeCompound(ull &offset)
{
    node* root = new node();

    int type;
    while ((type = (char)byteToInt(buffer, offset, 1)))
        root->ch.push_back(decode(offset));
    offset++;

    return root;
}

node* NBTCoder::decodeIntArray(ull &offset)
{
    node* root = new node();

    root->tag.va.clear();
    int len = (int)byteToInt(buffer, offset, 4);
    offset += 4;

    for (int i = 0; i < len; i++)
    {
        root->tag.va.push_back((int)byteToInt(buffer, offset, 4));
        offset += 4;
    }

    return root;
}

void NBTCoder::encodePayload(node* T, ull &offset)
{
    switch (T->tag.type)
    {
    case 0: break;
    case 1: encodeByte(T, offset); break;
    case 2: encodeShort(T, offset); break;
    case 3: encodeInt(T, offset); break;
    case 4: encodeLong(T, offset); break;
    case 5: encodeFloat(T, offset); break;
    case 6: encodeDouble(T, offset); break;
    case 7: encodeByteArray(T, offset); break;
    case 8: encodeString(T, offset); break;
    case 9: encodeList(T, offset); break;
    case 10: encodeCompound(T, offset); break;
    case 11: encodeIntArray(T, offset); break;
    default: break;
    }
}

void NBTCoder::encode(node* T, ull &offset)
{
    char type = T->tag.type; buffer[offset] = type; offset++;
    int name_len = T->tag.name.length(); intToByte(name_len, buffer, offset, 2); offset += 2;
    stringToByte(T->tag.name, buffer, offset, name_len); offset += name_len;

    encodePayload(T, offset);
}

void NBTCoder::encodeByte(node* T, ull &offset)
{
    uc v = T->tag.vi;
    buffer[offset] = v;//intToByte(v, buffer, offset, 1);
    offset++;
}

void NBTCoder::encodeShort(node* T, ull &offset)
{
    ll v = T->tag.vi;
    intToByte(v, buffer, offset, 2);
    offset += 2;
}

void NBTCoder::encodeInt(node* T, ull &offset)
{
    ll v = T->tag.vi;
    intToByte(v, buffer, offset, 4);
    offset += 4;
}

void NBTCoder::encodeLong(node* T, ull &offset)
{
    ll v = T->tag.vi;
    intToByte(v, buffer, offset, 8);
    offset += 8;
}

void NBTCoder::encodeFloat(node* T, ull &offset)
{
    float v = T->tag.vf;
    floatToByte(v, buffer, offset, 4);
    offset += 4;
}

void NBTCoder::encodeDouble(node* T, ull &offset)
{
    double v = T->tag.vf;
    doubleToByte(v, buffer, offset, 8);
    offset += 8;
}

void NBTCoder::encodeByteArray(node* T, ull &offset)
{
    int len = T->tag.va.size();
    intToByte(len, buffer, offset, 4);
    offset += 4;

    for (int i = 0; i < len; i++)
    {
        intToByte(T->tag.va[i], buffer, offset, 1);
        offset++;
    }
}

void NBTCoder::encodeString(node* T, ull &offset)
{
    us len = (us)T->tag.vs.length();
    intToByte(len, buffer, offset, 2); offset += 2;

    stringToByte(T->tag.vs, buffer, offset, len); offset += len;
}

void NBTCoder::encodeList(node* T, ull &offset)
{
    char type = T->tag.ch_type;
    intToByte(type, buffer, offset, 1);
    offset++;

    int len = T->ch.size();
    intToByte(len, buffer, offset, 4);
    offset += 4;

    for (auto v : T->ch)
        encodePayload(v, offset);
}

void NBTCoder::encodeCompound(node* T, ull &offset)
{
    for (auto v : T->ch)
        encode(v, offset);
    intToByte(0, buffer, offset, 1);
    offset++;
}

void NBTCoder::encodeIntArray(node* T, ull &offset)
{
    int len = T->tag.va.size();
    intToByte(len, buffer, offset, 4);
    offset += 4;

    for (int x : T->tag.va)
    {
        intToByte(x, buffer, offset, 4);
        offset += 4;
    }
}

void NBTCoder::print(node* T, int d)
{
    //printf("\n");
    for (int i = 0; i < d; i++)
        printf("    ");
    printf("{\n");

    for (int i = 0; i < d; i++)
        printf("    ");
    printf("TYPE: %s,  NAME: %s\n",
           TypeName[T->tag.type].c_str(), T->tag.name.c_str());
    for (int i = 0; i < d; i++)
        printf("    ");
    printf("CONTENT: ");
    switch (T->tag.type)
    {
        case 1:
        case 2:
        case 3:
        case 4: printf("%lld", T->tag.vi); break;
        case 5:
        case 6: printf("%.4lf", T->tag.vf); break;
        case 8: printf("%s", T->tag.vs.c_str()); break;
        case 7:
        case 11: for (auto x : T->tag.va) printf("%d ", x); break;
        default: printf("No Content"); break;
    }
    printf("\n");

    for (node* v : T->ch)
        print(v, d + 1);

    printf("\n");
    for (int i = 0; i < d; i++)
        printf("    ");
    printf("}\n");
}
