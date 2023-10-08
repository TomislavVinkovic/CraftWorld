#pragma once

#include "ChunkMeshGenerator/ChunkMeshGenerator.h"
#include "ChunkGenerator/ChunkGenerator.h"
#include "Player.h"

#include <algorithm>
#include <unordered_map>
#include <string>
#include <cmath>
#include <memory>

#include <thread>
#include <queue>

class World {
    private:
        bool initialLoad = true;
        int chunkDistance = 3; // render distance, hardcoded for now

        Player player;
        int currPlayerChunkPosX = 0;
        int currPlayerChunkPosZ = 0;

        ChunkMeshGenerator chunkMeshGenerator;
        ChunkGenerator chunkGenerator;

        std::unordered_map<std::string, std::shared_ptr<IChunk>> m_Chunks;

        // world generation and meshing threads

        std::mutex toMeshMutex;

        std::thread generationThread;
        std::thread meshingThread;

        std::queue<glm::vec3> toGenerate;
        std::queue<std::shared_ptr<IChunk>> toMesh;

        void generateChunks();
        void meshChunks();

    public:
    std::mutex m_ChunksMutex;
        World(const Camera& camera);

        /* generate chunks near to the player
        * and remove those far away from the player
        */
        void cycle();

        // getters
        Player& getPlayer() { return player; }
        const std::unordered_map<std::string, std::shared_ptr<IChunk>>& getChunks() const { return m_Chunks; }
};
