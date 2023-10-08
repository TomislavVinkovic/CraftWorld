#pragma once

#include "Chunk/Chunk/Chunk.h"

#include <random>
#include <memory>

/*
 * This class is used to generate terrain for a practicular chunk
 */
class ChunkGenerator {

    public:
        ChunkGenerator() = default;
        ~ChunkGenerator() = default;

        std::shared_ptr<IChunk> generate(const glm::vec3& position);
};
