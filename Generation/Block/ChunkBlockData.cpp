#include "ChunkBlockData.h"

#include "ChunkBlockData.h"

namespace block_type_data {
    const ChunkBlockData& getBlockDataByType(const ChunkBlockType& blockType) {
        if(blockType == ChunkBlockType::Air) {
            return AirBlock;
        }
        if(blockType == ChunkBlockType::Sand) {
            return SandBlock;
        }
        if(blockType == ChunkBlockType::Cobblestone) {
            return CobblestoneBlock;
        }
        if(blockType == ChunkBlockType::Water) {
            return WaterBlock;
        }
        if(blockType == ChunkBlockType::Wood) {
            return WoodBlock;
        }
        if(blockType == ChunkBlockType::Dirt) {
            return DirtBlock;
        }
        if(blockType == ChunkBlockType::Grass) {
            return GrassBlock;
        }
        if(blockType == ChunkBlockType::Cactus) {
            return CactusBlock;
        }
        if(blockType == ChunkBlockType::Bush) {
            return BushBlock;
        }
        if(blockType == ChunkBlockType::Shrug) {
            return ShrugBlock;
        }
        if(blockType == ChunkBlockType::Flower) {
            return FlowerBlock;
        }
        if(blockType == ChunkBlockType::Mathos) {
            return MathosBlock;
        }
        if(blockType == ChunkBlockType::MathosSinister) {
            return MathosSinisterBlock;
        }
        if(blockType == ChunkBlockType::Coal) {
            return CoalBlock;
        }
        else return GrassBlock;
    }
}

namespace block_data {
    const std::vector<float> backFace {
            // Back
            1.f, 0.f, 0.f,
            0.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            1.f, 1.f, 0.f,
    };
    const std::vector<float> frontFace {
            // Front
            0.f, 0.f, 1.f,
            1.f, 0.f, 1.f,
            1.f, 1.f, 1.f,
            0.f, 1.f, 1.f,
    };
    const std::vector<float> rightFace {
            // Right
            1.f, 0.f, 1.f,
            1.f, 0.f, 0.f,
            1.f, 1.f, 0.f,
            1.f, 1.f, 1.f,
    };

    const std::vector<float> leftFace {
            // Left
            0.f, 0.f, 0.f,
            0.f, 0.f, 1.f,
            0.f, 1.f, 1.f,
            0.f, 1.f, 0.f,
    };

    const std::vector<float> topFace {
            // Top
            0.f, 1.f, 1.f,
            1.f, 1.f, 1.f,
            1.f, 1.f, 0.f,
            0.f, 1.f, 0.f,
    };

    const std::vector<float> bottomFace {
            // Bottom
            0.f, 0.f, 0.f,
            1.f, 0.f, 0.f,
            1.f, 0.f, 1.f,
            0.f, 0.f, 1.f
    };

    const std::vector<unsigned int> indices {
            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            6, 7, 4,

            8, 9, 10,
            10, 11, 8,

            12, 13, 14,
            14, 15, 12,

            16, 17, 18,
            18, 19, 16,

            20, 21, 22,
            22, 23, 20
    };
}