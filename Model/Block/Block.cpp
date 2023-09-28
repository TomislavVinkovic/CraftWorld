#include "Block.h"

Block::Block(ChunkBlockType blockType): m_BlockType{blockType} {
    std::vector<float> vertices{};

    const auto& blockTypeData = block_type_data::getBlockDataByType(m_BlockType);

    int i = 0;
    for(const auto& blob: block_data::backFace) {
        vertices.push_back(blob);

        if(i == 2) {
            vertices.push_back(blockTypeData.backFaceTextureMin.x);
            vertices.push_back(blockTypeData.backFaceTextureMin.y);
        }
        if(i == 5) {
            vertices.push_back(blockTypeData.backFaceTextureMax.x);
            vertices.push_back(blockTypeData.backFaceTextureMin.y);
        }
        if(i == 8) {
            vertices.push_back(blockTypeData.backFaceTextureMax.x);
            vertices.push_back(blockTypeData.backFaceTextureMax.y);
        }
        if(i == 11) {
            vertices.push_back(blockTypeData.backFaceTextureMin.x);
            vertices.push_back(blockTypeData.backFaceTextureMax.y);
        }
        i++;
    }

    i = 0;
    for(const auto& blob: block_data::frontFace) {
        vertices.push_back(blob);

        if(i == 2) {
            vertices.push_back(blockTypeData.frontFaceTextureMin.x);
            vertices.push_back(blockTypeData.frontFaceTextureMin.y);
        }
        if(i == 5) {
            vertices.push_back(blockTypeData.frontFaceTextureMax.x);
            vertices.push_back(blockTypeData.frontFaceTextureMin.y);
        }
        if(i == 8) {
            vertices.push_back(blockTypeData.frontFaceTextureMax.x);
            vertices.push_back(blockTypeData.frontFaceTextureMax.y);
        }
        if(i == 11) {
            vertices.push_back(blockTypeData.frontFaceTextureMin.x);
            vertices.push_back(blockTypeData.frontFaceTextureMax.y);
        }
        i++;
    }

    i = 0;
    for(const auto& blob: block_data::rightFace) {
        vertices.push_back(blob);

        if(i == 2) {
            vertices.push_back(blockTypeData.rightFaceTextureMin.x);
            vertices.push_back(blockTypeData.rightFaceTextureMin.y);
        }
        if(i == 5) {
            vertices.push_back(blockTypeData.rightFaceTextureMax.x);
            vertices.push_back(blockTypeData.rightFaceTextureMin.y);
        }
        if(i == 8) {
            vertices.push_back(blockTypeData.rightFaceTextureMax.x);
            vertices.push_back(blockTypeData.rightFaceTextureMax.y);
        }
        if(i == 11) {
            vertices.push_back(blockTypeData.rightFaceTextureMin.x);
            vertices.push_back(blockTypeData.rightFaceTextureMax.y);
        }
        i++;
    }

    i = 0;
    for(const auto& blob: block_data::leftFace) {
        vertices.push_back(blob);

        if(i == 2) {
            vertices.push_back(blockTypeData.leftFaceTextureMin.x);
            vertices.push_back(blockTypeData.leftFaceTextureMin.y);
        }
        if(i == 5) {
            vertices.push_back(blockTypeData.leftFaceTextureMax.x);
            vertices.push_back(blockTypeData.leftFaceTextureMin.y);
        }
        if(i == 8) {
            vertices.push_back(blockTypeData.leftFaceTextureMax.x);
            vertices.push_back(blockTypeData.leftFaceTextureMax.y);
        }
        if(i == 11) {
            vertices.push_back(blockTypeData.leftFaceTextureMin.x);
            vertices.push_back(blockTypeData.leftFaceTextureMax.y);
        }
        i++;
    }

    i = 0;
    for(const auto& blob: block_data::topFace) {
        vertices.push_back(blob);

        if(i == 2) {
            vertices.push_back(blockTypeData.topFaceTextureMin.x);
            vertices.push_back(blockTypeData.topFaceTextureMin.y);
        }
        if(i == 5) {
            vertices.push_back(blockTypeData.topFaceTextureMax.x);
            vertices.push_back(blockTypeData.topFaceTextureMin.y);
        }
        if(i == 8) {
            vertices.push_back(blockTypeData.topFaceTextureMax.x);
            vertices.push_back(blockTypeData.topFaceTextureMax.y);
        }
        if(i == 11) {
            vertices.push_back(blockTypeData.topFaceTextureMin.x);
            vertices.push_back(blockTypeData.topFaceTextureMax.y);
        }
        i++;
    }

    i = 0;
    for(const auto& blob: block_data::bottomFace) {
        vertices.push_back(blob);

        if(i == 2) {
            vertices.push_back(blockTypeData.bottomFaceTextureMin.x);
            vertices.push_back(blockTypeData.bottomFaceTextureMin.y);
        }
        if(i == 5) {
            vertices.push_back(blockTypeData.bottomFaceTextureMax.x);
            vertices.push_back(blockTypeData.bottomFaceTextureMin.y);
        }
        if(i == 8) {
            vertices.push_back(blockTypeData.bottomFaceTextureMax.x);
            vertices.push_back(blockTypeData.bottomFaceTextureMax.y);
        }
        if(i == 11) {
            vertices.push_back(blockTypeData.bottomFaceTextureMin.x);
            vertices.push_back(blockTypeData.bottomFaceTextureMax.y);
        }
        i++;
    }

    m_BlockMesh = new BlockMesh(vertices, block_data::indices);
}

void Block::bind() {
    if(m_BlockMesh != nullptr) {
        m_BlockMesh->getVao().bind();
    }

}

void Block::unbind() {
    if(m_BlockMesh != nullptr) {
        m_BlockMesh->getVao().unbind();
    }
}
