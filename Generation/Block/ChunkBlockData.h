#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "glm/glm.hpp"

using Block_t = uint8_t;

enum class ChunkBlockType :  Block_t
{
    Air = 0,
    Grass,
    Dirt,
    Cobblestone,
    Sand,
    Wood,
    Water,
    Cactus,
    Bush,
    Shrug,
    Flower,
    Mathos,
    Coal,
    MathosSinister
};

struct ChunkBlockData {

    ChunkBlockData(ChunkBlockType type, const std::string& name, bool breakable = true)
            : name(name), blockType(type), breakable(breakable){}
    ChunkBlockData(
            ChunkBlockType type,
            const std::string& name,
            const glm::vec2& topFaceTextureMin,
            const glm::vec2& topFaceTextureMax,
            const glm::vec2& bottomFaceTextureMin,
            const glm::vec2& bottomFaceTextureMax,
            const glm::vec2& leftFaceTextureMin,
            const glm::vec2& leftFaceTextureMax,
            const glm::vec2& rightFaceTextureMin,
            const glm::vec2& rightFaceTextureMax,
            const glm::vec2& frontFaceTextureMin,
            const glm::vec2& frontFaceTextureMax,
            const glm::vec2& backFaceTextureMin,
            const glm::vec2& backFaceTextureMax,
            bool breakable = true
    ) : blockType(type), name(name), topFaceTextureMax(topFaceTextureMax / 256.f), topFaceTextureMin(topFaceTextureMin / 256.f),
        bottomFaceTextureMax(bottomFaceTextureMax / 256.f), bottomFaceTextureMin(bottomFaceTextureMin / 256.f),
        leftFaceTextureMax(leftFaceTextureMax / 256.f), leftFaceTextureMin(leftFaceTextureMin / 256.f),
        rightFaceTextureMax(rightFaceTextureMax / 256.f), rightFaceTextureMin(rightFaceTextureMin / 256.f),
        frontFaceTextureMax(frontFaceTextureMax / 256.f), frontFaceTextureMin(frontFaceTextureMin / 256.f),
        backFaceTextureMax(backFaceTextureMax / 256.f), backFaceTextureMin(backFaceTextureMin / 256.f), breakable(breakable){}


    ChunkBlockType blockType{ChunkBlockType::Air};
    std::string name;
    glm::vec2 topFaceTextureMin{-1,-1};
    glm::vec2 topFaceTextureMax{-1,-1};
    glm::vec2 bottomFaceTextureMin{-1,-1};
    glm::vec2 bottomFaceTextureMax{-1,-1};
    glm::vec2 leftFaceTextureMin{-1,-1};
    glm::vec2 leftFaceTextureMax{-1,-1};
    glm::vec2 rightFaceTextureMin{-1,-1};
    glm::vec2 rightFaceTextureMax{-1,-1};
    glm::vec2 frontFaceTextureMin{-1,-1};
    glm::vec2 frontFaceTextureMax{-1,-1};
    glm::vec2 backFaceTextureMin{-1,-1};
    glm::vec2 backFaceTextureMax{-1,-1};
    bool breakable = true;
};

namespace block_data {
    extern const std::vector<float> backFace;
    extern const std::vector<float> frontFace;
    extern const std::vector<float> rightFace;
    extern const std::vector<float> leftFace;
    extern const std::vector<float> topFace;
    extern const std::vector<float> bottomFace;
    extern const std::vector<unsigned int> indices;
}

namespace block_type_data {
    const ChunkBlockData AirBlock= ChunkBlockData(ChunkBlockType::Air, "Air", false);

    const ChunkBlockData GrassBlock = ChunkBlockData(
            ChunkBlockType::Grass, "Grass", {0,240}, {16, 256},
            {32,240}, {48,256},
            {16,240},{32,256},{16,240},
            {32,256},{16,240},
            {32,256},{16,240},{32,256}
    );
    const ChunkBlockData SandBlock = ChunkBlockData(
            ChunkBlockType::Sand, "Sand",
            {112,240}, {128,256},
            {112,240}, {128,256},
            {112,240}, {128,256},
            {112,240}, {128,256},
            {112,240}, {128,256},
            {112,240}, {128,256}
    );
    const ChunkBlockData DirtBlock = ChunkBlockData(
            ChunkBlockType::Dirt, "Dirt",
            {32,240}, {48,256},
            {32,240}, {48,256},
            {32,240}, {48,256},
            {32,240}, {48,256},
            {32,240}, {48,256},
            {32,240}, {48,256}
    );
    const ChunkBlockData CobblestoneBlock = ChunkBlockData(
            ChunkBlockType::Cobblestone, "Cobblestone",
            {48,240}, {64,256},
            {48,240}, {64,256},
            {48,240}, {64,256},
            {48,240}, {64,256},
            {48,240}, {64,256},
            {48,240}, {64,256}
    );
    const ChunkBlockData WoodBlock = ChunkBlockData(
            ChunkBlockType::Wood, "Wood",
            {80,240}, {96,256},
            {80,240}, {96,256},
            {64,240}, {80,256},
            {64,240}, {80,256},
            {64,240}, {80,256},
            {64,240}, {80,256}
    );
    const ChunkBlockData CactusBlock = ChunkBlockData(
            ChunkBlockType::Cactus, "Cactus",
            {144,224}, {160,240},
            {144,224}, {160,240},
            {144,240}, {160,256},
            {144,240}, {160,256},
            {144,240}, {160,256},
            {144,240}, {160,256}
    );
    const ChunkBlockData BushBlock = ChunkBlockData(
            ChunkBlockType::Bush, "Bush",
            {96,240}, {112,256},
            {96,240}, {112,256},
            {96,240}, {112,256},
            {96,240}, {112,256},
            {96,240}, {112,256},
            {96,240}, {112,256}
    );
    const ChunkBlockData WaterBlock = ChunkBlockData(
            ChunkBlockType::Water, "Water",
            {128,240}, {144,256},
            {128,240}, {144,256},
            {128,240}, {144,256},
            {128,240}, {144,256},
            {128,240}, {144,256},
            {128,240}, {144,256},
            false
    );
    const ChunkBlockData ShrugBlock = ChunkBlockData(
            ChunkBlockType::Shrug, "Shrug",
            {0,224}, {16, 240},
            {112,240}, {128,256},
            {112,240}, {128,256},
            {112,240}, {128,256},
            {112,240}, {128,256},
            {112,240}, {128,256},
            true
    );
    const ChunkBlockData FlowerBlock = ChunkBlockData(
            ChunkBlockType::Flower, "Flower",
            {16,224}, {32, 240},
            {32,240}, {48,256},
            {16,240},{32,256},{16,240},
            {32,256},{16,240},
            {32,256},{16,240},{32,256},true
    );
    const ChunkBlockData MathosBlock = ChunkBlockData(
            ChunkBlockType::Mathos, "Mathos",
            {96,224}, {112, 240},
            {96,224}, {112, 240},
            {96,224}, {112, 240},
            {96,224}, {112, 240},
            {96,224}, {112, 240},
            {96,224}, {112, 240},
            true
    );
    const ChunkBlockData CoalBlock = ChunkBlockData(
            ChunkBlockType::Coal, "Coal",
            {160,224}, {176,240},
            {160,224}, {176,240},
            {160,224}, {176,240},
            {160,224}, {176,240},
            {160,224}, {176,240},
            {160,224}, {176,240},
            true
    );
    const ChunkBlockData MathosSinisterBlock = ChunkBlockData(
            ChunkBlockType::MathosSinister, "MathosSinister",
            {176,224}, {192,240},
            {176,224}, {192,240},
            {176,224}, {192,240},
            {176,224}, {192,240},
            {176,224}, {192,240},
            {176,224}, {192,240},
            true
    );
    const ChunkBlockData& getBlockDataByType(const ChunkBlockType& blockType);
};