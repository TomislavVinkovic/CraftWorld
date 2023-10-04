#pragma once

#include "ChunkBlock/ChunkBlock.h"

#include <vector>

/* An interface for defining various Chunk layer types
 * some properties can include: is the layer opaque, does it consist of a single block type etc.
*/

class IChunkBlockLayer {
    protected:
        bool isSolid;
        int yLevel;
    public:
        virtual ChunkBlock getBlockAt(int x, int z) = 0;
        virtual ChunkBlock getBlockTypeAt(int x, int z) = 0;

        virtual bool getIsSolid() const { return isSolid; }
        virtual bool setIsSolid(bool isSolid = true) { return this->isSolid = isSolid; }
};