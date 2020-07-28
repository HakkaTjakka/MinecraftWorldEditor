#ifndef BlockEntity_h
#define BlockEntity_h

#include <string>
#include "globals.h"

extern int firstblen;

class BlockEntity
{
public:
    Pos position;
    std::string entity_id;

    BlockEntity() {}

    BlockEntity(const Pos &position_, const char *id_)
        : position(position_), entity_id(id_) {}

    bool operator < (const BlockEntity &B) const
    {
        if (firstblen==1) {
            firstblen=0;
            printf("\nIn sorting\n");
        }
        int ax = position.x , bx = B.position.x;
        if (ax >> 4 != bx >> 4) {
            return ax < bx;
        }
        else {
            int az = position.z, bz = B.position.z;
            if (az  >> 4 != bz >> 4) {
                return az < bz;
            } else {
                int ay = position.y, by = B.position.y;
                if (ay >> 4 != by >> 4) {
                    return ay < by;
                } else {
                    if (ay != by) return ay < by;
                    if (az != bz) return az < bz;
                    return ax < bx;
                }
            }
        }
    }


private:
};

class MobEntity
{
public:
    Pos position;
    std::string entity_id;

    MobEntity() {}

    MobEntity(const Pos &position_, const char *id_)
        : position(position_), entity_id(id_) {}

private:
};

class BlockEntityNote : public BlockEntity
{
public:
    int note;
    int powered;

    BlockEntityNote() {}

    BlockEntityNote(const Pos &position_,
                    const int &note_, const int &powered_)
        : BlockEntity(position_, "minecraft:noteblock"),
          note(note_), powered(powered_) {}

private:
};

class BlockEntityCommand : public BlockEntity
{
public:
    std::string command;
    int automatic;
    int powered;

    BlockEntityCommand() {}

    BlockEntityCommand(const Pos &position_,
                       const std::string &command_,
                       const int &automatic_,
                       const int &powered_
                       )
        : BlockEntity(position_, "minecraft:command_block"),
          command(command_), automatic(automatic_), powered(powered_)  {}
//          command(command_), automatic(automatic_) {}

private:
};

class BlockEntityGlowColor : public BlockEntity
{
public:
    char* id;

    BlockEntityGlowColor() {}

    BlockEntityGlowColor(const Pos &position_, const char* id_ ) : BlockEntity(position_, (char *)id_) {}


private:
};

#endif /* BlockEntity_h */
