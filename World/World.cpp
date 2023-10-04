#include "World.h"

#define FMT_HEADER_ONLY
#include "fmt/core.h"

World::World(const Camera& camera)
: player(camera), chunkMeshGenerator(m_Chunks){}

void World::cycle() {
    player.updatePosition();

    const auto& playerPos = player.getPosition();
    auto chunkSize = Chunk::chunkSize;
    int newPlayerChunkPosX = static_cast<int>(floor(playerPos.x / chunkSize))* chunkSize;
    int newPlayerChunkPosZ = static_cast<int>(floor(playerPos.z / chunkSize)) * chunkSize;

    if(initialLoad || newPlayerChunkPosX != currPlayerChunkPosX || newPlayerChunkPosZ != currPlayerChunkPosZ) {
        if(initialLoad) {
            initialLoad = false;
        }

        // update the current player chunk position
        currPlayerChunkPosX = newPlayerChunkPosX;
        currPlayerChunkPosZ = newPlayerChunkPosZ;
        // int chunkPosY = static_cast<int>(floor(playerPos.y) * 16) / 16;

        int chunkPosY = 0; // hardcoded for now

        // loop through all the chunk positions and see if you need to add new chunks
        int chunkSize = Chunk::chunkSize;
        for(int x = currPlayerChunkPosX - chunkSize*chunkDistance;
            x <= currPlayerChunkPosX + chunkSize*chunkDistance;
            x+=chunkSize
        ) {
            for(int z = currPlayerChunkPosZ - chunkSize*chunkDistance;
                z <= currPlayerChunkPosZ + chunkSize*chunkDistance;
                z+=chunkSize
            ) {
                std::string key = fmt::format("{} {} {}", x, chunkPosY, z);
                auto chunkIter = m_Chunks.find(key);
                if(chunkIter == m_Chunks.end()) {
                    auto chunkPtr = std::make_shared<Chunk>(glm::vec3(x, chunkPosY, z));
                    m_Chunks[key] = chunkPtr;
                }
            }
        }


        std::vector<std::string> chunksToDelete;
        // loop through all the chunks in the chunk database and see if you need to remove some of them
        for(auto& [key, chunk]: m_Chunks) {
            auto chunkPos = chunk->getPosition();

            auto diffX = abs(currPlayerChunkPosX - static_cast<int>(chunkPos.x));
            auto diffZ = abs(currPlayerChunkPosZ - static_cast<int>(chunkPos.z));

            auto limitX = chunkSize * (chunkDistance + 3);
            auto limitZ = chunkSize * (chunkDistance + 3);

            if(diffX > limitX || diffZ > limitZ) {
                chunksToDelete.push_back(key);
            }
        }

        for(auto& key: chunksToDelete) {
            m_Chunks.erase(key);
        }
        chunkMeshGenerator.setWorldChunks(m_Chunks);
        // mesh all chunks that are not meshed
        for(auto& [key, chunk]: m_Chunks) {
            if(!chunk->getIsMeshed()) {
                chunkMeshGenerator.mesh(chunk);
            }
        }
        for(auto& iter: chunkMeshGenerator.getToRemeshTable()) {
            chunkMeshGenerator.mesh(iter.second, false);
        }
        chunkMeshGenerator.clearToRemeshTable();
    }
}