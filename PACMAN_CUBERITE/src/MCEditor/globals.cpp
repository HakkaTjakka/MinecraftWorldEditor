#include "globals.h"
#include "zlib.h"
using namespace std;

std::string TypeName[18] = {"", "Byte", "Short", "Int", "Long Long",
                            "Float", "Double", "Byte Array", "String",
                            "List", "Compound", "Int Array"};

//reverse [offset, offset + len) in buffer
void reverse_(uc* buffer, ull offset, ull len)
{
    for (int i = 0; i < len - 1 - i; i++)
        swap(buffer[offset + i], buffer[offset + len - 1 - i]);
}

//convert bytes to a integer value (big endian)
ll byteToInt(uc* buffer, ull offset, ull len)
{
    ll res = 0;
    reverse_(buffer, offset, len);
    memcpy(&res, buffer + offset, len);
    return res;
}

//convert bytes to a float value (big endian)
float byteToFloat(uc* buffer, ull offset, ull len)
{
    float res = 0;
    reverse_(buffer, offset, len);
    memcpy(&res, buffer + offset, len);
    return res;
}

//convert bytes to a double value (big endian)
double byteToDouble(uc* buffer, ull offset, ull len)
{
    double res = 0;
    reverse_(buffer, offset, len);
    memcpy(&res, buffer + offset, len);
    return res;
}

//convert bytes to a string value ("little endian")
string byteToString(uc* buffer, ull offset, ull len)
{
    string res = "";
    for (int i = (int)offset; i < offset + len; i++)
        res += (char)buffer[i];
    return res;
}

//convert an integer value to bytes (big endian)
void intToByte(ll v, uc* buffer, ull offset, ull len)
{
    memcpy(buffer + offset, &v, len);
    reverse_(buffer, offset, len);
}

//convert a float value to bytes (big endian)
void floatToByte(float v, uc* buffer, ull offset, ull len)
{
    memcpy(buffer + offset, &v, len);
    reverse_(buffer, offset, len);
}

//convert a double value to bytes (big endian)
void doubleToByte(double v, uc* buffer, ull offset, ull len)
{
    memcpy(buffer + offset, &v, len);
    reverse_(buffer, offset, len);
}

//convert a string to bytes ("little endian")
void stringToByte(const std::string &str, uc* buffer, ull offset, ull len)
{
    for (int i = 0; i < len; i++)
        buffer[offset + i] = (uc)str[i];
}

//decompress src into dest
void decompress(uc *dest, ull dest_len, uc* src, ull src_len)
{
    z_stream infstream;
    infstream.zalloc = Z_NULL;
    infstream.zfree = Z_NULL;
    infstream.opaque = Z_NULL;

    infstream.avail_in = (ui)src_len;
    infstream.next_in = src;
    infstream.avail_out = (ui)dest_len;
    infstream.next_out = dest;

    inflateInit(&infstream);
    inflate(&infstream, Z_NO_FLUSH);
    inflateEnd(&infstream);
}

//compress src into dest
ull compress(uc *dest, ull dest_len, uc* src, ull src_len)
{
    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;

    defstream.avail_in = (ui)src_len;
    defstream.next_in = src;
    defstream.avail_out = (ui)dest_len;
    defstream.next_out = dest;

    deflateInit(&defstream, Z_BEST_SPEED);
    deflate(&defstream, Z_FINISH);
    ull len = defstream.total_out;
    deflateEnd(&defstream);

    return len;
}

//create a new l1 * l2 * l3 unsigned int array
ui*** new3DUIArray(int l1, int l2, int l3)
{
    ui*** p;
//    p = new ui** [l1];

    p = (ui***) malloc( sizeof(ui**) * l1);
    for (int i = 0; i < l1; i++) {
        p[i] = (ui**) malloc( sizeof(ui*) * l2);
        for (int j = 0; j < l2; j++) {
            p[i][j] = (ui*) malloc( sizeof(ui) * l3);
            memset(p[i][j], 0, l3 * sizeof(ui));
        }
    }
//    for (int i = 0; i < l1; i++)
//    {
//        p[i] = new ui* [l2];
//        for (int j = 0; j < l2; j++)
//            p[i][j] = new ui [l3];
//    }
    return p;
}

//delete a new l1 * l2 * l3 unsigned int array
void del3DUIArray(ui*** &p, int l1, int l2, int l3)
{
    for (int i = 0; i < l1; i++)
    {
        for (int j = 0; j < l2; j++) {
            if (p[i][j]!=NULL) { free(p[i][j]); p[i][j]=NULL; }
        }
        if (p[i]!=NULL) { free(p[i]); p[i]=NULL; }
    }
    if (p!=NULL) { free(p);  p=NULL; }
//    p = 0;

//    for (int i = 0; i < l1; i++)
//    {
//        for (int j = 0; j < l2; j++)
//            delete [] p[i][j];
//        delete [] p[i];
//    }
//    delete p; p = 0;
}

//get the opacity of block id
int get_opacity(ui id)
{
    switch (id)
    {
        case 0: return 1;
        case 8: return 2;
        case 9: return 2;
        case 20: return 1;
        case 50: return 1;
        case 95: return 1;
        case 171: return 1;
        case 2003: return 1;
//        default: return 15;
        default: return 15;
    }
}

//get the block light of block id
//pipo
int get_block_light(ui id)
{
    if (id>255) return 14;
    switch (id)
    {
        case 50: return 15;
//        case 50: {
//            if ( ! (rand()%3) ) return 15;
  //          else return 0;
//        }
        case 76: return 15;
        case 89: return 14;
        case 91: return 15;
        case 124: return 15;
        default: return 0;
    }
}
