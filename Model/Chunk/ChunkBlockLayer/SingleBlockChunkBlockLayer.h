#pragma once


#include "Chunk/ChunkBlockLayer/IChunkBlockLayer.h"

class SingleBlockChunkBlockLayer: public IChunkBlockLayer {
    private:
        ChunkBlock block;
    public:
        SingleBlockChunkBlockLayer(ChunkBlock block, int yLevel): block(block) {
            this->yLevel = yLevel;
        }
        ChunkBlock getBlockAt(int x, int z) override {
            return block;
        }
        ChunkBlock getBlockTypeAt(int x, int z) override {
            return block.getType();
        }
};
