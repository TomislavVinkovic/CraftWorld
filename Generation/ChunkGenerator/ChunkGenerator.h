#pragma once

#include "Chunk/Chunk.h"

#include <random>

/*
 * This class is used to generate terrain for a practicular chunk
 */
class ChunkGenerator {

    public:
        ChunkGenerator() = default;
        ~ChunkGenerator() = default;

        void generate(Chunk& chunk);
};
