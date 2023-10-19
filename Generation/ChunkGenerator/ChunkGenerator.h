#pragma once

#include "Chunk/Chunk/Chunk.h"
#include "NoiseGenerator/PerlinNoise.h"

#include <random>
#include <memory>

/*
 * This class is used to generate terrain for a practicular chunk
 */
class ChunkGenerator {
    private:
        siv::PerlinNoise noiseGenerator;
    public:
        ChunkGenerator() = default;
        ~ChunkGenerator() = default;

        std::shared_ptr<IChunk> generate(const glm::vec3& position);
};
