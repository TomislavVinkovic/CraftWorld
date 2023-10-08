#pragma once

#include <vector>
#include <cmath>
#include <cstdlib>
#include <memory>

#include "ChunkBlock/ChunkBlock.h"
#include "ChunkMesh/ChunkMesh.h"
#include "Chunk/ChunkBlockLayer/IChunkBlockLayer.h"
#include "Chunk/IChunk/IChunk.h"

class Chunk: public IChunk {
    private:
        std::vector<std::shared_ptr<IChunkBlockLayer>> blockLayers;

    public:
        Chunk(
            std::vector<std::shared_ptr<IChunkBlockLayer>>& layers,
            glm::vec3 position = glm::vec3(0.f, 0.f, 0.f)
        );

        // getters
        // const std::vector<std::shared_ptr<IChunkBlockLayer>>& getBlockLayers() const { return blockLayers; }

        ChunkBlock getBlockAtPosition(const glm::vec3 &blockPosition) const override;
};
