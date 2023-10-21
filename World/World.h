#pragma once

#include "ChunkMeshGenerator/ChunkMeshGenerator.h"
#include "ChunkGenerator/ChunkGenerator.h"
#include "Player.h"

#include <algorithm>
#include <unordered_map>
#include <queue>
#include <string>
#include <cmath>

#include <memory>
#include <thread>
#include <chrono>

class World {
    private:
        bool initialLoad = true;
        int chunkDistance = 8; // render distance, hardcoded for now

        Player player;
        int currPlayerChunkPosX = 0;
        int currPlayerChunkPosZ = 0;

        ChunkMeshGenerator chunkMeshGenerator;
        ChunkGenerator chunkGenerator;

        // chunks that are currently in the game world
        std::unordered_map<std::string, std::shared_ptr<IChunk>> m_Chunks;

        // world generation and meshing threads
        std::queue<glm::vec3> toGenerate;
        std::queue<std::shared_ptr<IChunk>> toMesh;

        std::jthread generationThread;
        std::jthread meshingThread;

        std::mutex toMeshMutex;
        std::mutex toGenerateMutex;
        std::mutex playerMutex;

        // generation and meshing thread functions
        void generateChunks();
        void meshChunks();

    public:
        std::mutex m_ChunksMutex;
        explicit World(const Camera& camera);

        /* generate chunks near to the player
        * and remove those far away from the player
        */
        void cycle();

        // getters
        Player& getPlayer() { return player; }
        const std::unordered_map<std::string, std::shared_ptr<IChunk>>& getChunks() const { return m_Chunks; }
};
