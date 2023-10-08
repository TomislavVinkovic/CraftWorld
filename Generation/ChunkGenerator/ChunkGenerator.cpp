#include "ChunkGenerator.h"
#include "Chunk/ChunkBlockLayer/SingleBlockChunkBlockLayer.h"
#include "Chunk/ChunkBlockLayer/ChunkBlockLayer/ChunkBlockLayer.h"
#include "Chunk/SingleBlockTypeChunk/SingleBlockTypeChunk.h"

/*
Chunk::Chunk(glm::vec3 position) {

}
*/

std::shared_ptr<IChunk> ChunkGenerator::generate(const glm::vec3& position) {
    std::vector<std::shared_ptr<IChunkBlockLayer>> blockLayers;

    // select a random block type for the chunk
    std::srand(static_cast<unsigned int>(time(nullptr)));
    // Define the range
    int min = 0;
    int max = 12;
    int type = std::rand() % (max - min + 1) + min;

    // check if the chunk consists of a single block type
    // and if it is solid
    bool areBlocksSame = true;
    bool areBlocksSolid = true;
    bool areChunkLayersSame = true;

    for(int y = 0; y < IChunk::chunkSize; y++) {
        std::vector<ChunkBlock> blocks;
        ChunkBlockType prevBlockType;



        for(int i = 0; i < pow(IChunk::chunkSize, 2); i++) {
            blocks.push_back(ChunkBlock(static_cast<ChunkBlockType>(type)));
            if(i == 0) {
                prevBlockType = blocks[0].getType();
            }
            auto& blockData = block_type_data::getBlockDataByType(blocks.back().getType());
            if(areBlocksSolid && !blockData.isSolid) {
                areBlocksSolid = false;
            }
            if(areBlocksSame && blocks.back().getType() != prevBlockType) {
                areBlocksSame = false;
            }
            prevBlockType = blocks.back().getType();
        }

        areChunkLayersSame = areChunkLayersSame && areBlocksSame;

        // if it consists of a single block type, we can store that layer as a single block, to save memory
        if(areBlocksSame) {
            blockLayers.push_back(std::make_shared<SingleBlockChunkBlockLayer>(blocks[0], y));
        }

            // otherwise, we have to save information about all blocks
        else {
            blockLayers.push_back(std::make_shared<ChunkBlockLayer>(blocks, y));
        }

        // if the entire block layer is solid, mark it as such
        blockLayers.back()->setIsSolid(areBlocksSolid);
    }

    if(areChunkLayersSame) {
        return std::make_shared<SingleBlockTypeChunk>(blockLayers[0]->getBlockAt(0,0).getType(), position);
    }
    else {
        return std::make_shared<Chunk>(blockLayers, position);
    }
}