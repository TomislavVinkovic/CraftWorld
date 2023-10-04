#pragma once

#include "ChunkMeshGenerator/ChunkMeshGenerator.h"
#include "ChunkGenerator/ChunkGenerator.h"
#include "Player.h"

#include <algorithm>
#include <unordered_map>
#include <string>
#include <cmath>
#include <memory>

class World {
    private:
        bool initialLoad = true;
        int chunkDistance = 3; // render distance, hardcoded for now

        Player player;
        int currPlayerChunkPosX = 0;
        int currPlayerChunkPosZ = 0;

        ChunkMeshGenerator chunkMeshGenerator;
        ChunkGenerator chunkGenerator;

        std::unordered_map<std::string, std::shared_ptr<Chunk>> m_Chunks;

    public:
        World(const Camera& camera);

        /* generate chunks near to the player
        * and remove those far away from the player
        */
        void cycle();

        // getters
        Player& getPlayer() { return player; }
        const std::unordered_map<std::string, std::shared_ptr<Chunk>>& getChunks() const { return m_Chunks; }
};
