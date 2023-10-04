#pragma once


#include "Chunk/ChunkBlockLayer/IChunkBlockLayer.h"
#include <vector>

class ChunkBlockLayer: public IChunkBlockLayer {
    private:
        std::vector<ChunkBlock> blocks;
    public:
        ChunkBlockLayer(std::vector<ChunkBlock> blocks, int yLevel);
        ChunkBlock getBlockTypeAt(int x, int z) override;
        ChunkBlock getBlockAt(int x, int z) override;
};
