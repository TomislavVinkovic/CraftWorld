cmake_minimum_required(VERSION 3.26)
project(CraftWorld)

set(CMAKE_CXX_STANDARD 20)

include_directories(src vendor vendor/glad GLDebug Renderer Player Camera Util Generation Mesh Model)

set(SOURCE_FILES
        vendor/glad/glad.c
        vendor/stb_image/stb_image.cpp
        main.cpp
        GLDebug/GLDebug.h
        GLDebug/GLDebug.cpp
        Renderer/Shader/Shader.cpp
        Renderer/Shader/Shader.h
        Camera/Camera.cpp
        Camera/Camera.h
        Player/Player.cpp
        Player/Player.h
        Util/DeltaTime/DeltaTime.cpp
        Util/DeltaTime/DeltaTime.h
        Renderer/IndexBuffer/IndexBuffer.cpp
        Renderer/IndexBuffer/IndexBuffer.h
        Renderer/VertexArray/VertexArray.cpp
        Renderer/VertexArray/VertexArray.h
        Renderer/VertexBuffer/VertexBuffer.cpp
        Renderer/VertexBuffer/VertexBuffer.h
        Renderer/VertexBufferLayout/VertexBufferLayout.h
        Renderer/Texture/TextureAtlas.cpp
        Renderer/Texture/TextureAtlas.h
        Generation/Block/ChunkBlockData.cpp
        Generation/Block/ChunkBlockData.h
        Model/Block/Block.cpp
        Model/Block/Block.h
        Mesh/BlockMesh/BlockMesh.cpp
        Mesh/BlockMesh/BlockMesh.h
        Model/Chunk/Chunk/Chunk.cpp
        Model/Chunk/Chunk/Chunk.h
        Mesh/ChunkMesh/ChunkMesh.cpp
        Mesh/ChunkMesh/ChunkMesh.h
        Model/ChunkBlock/ChunkBlock.cpp
        Model/ChunkBlock/ChunkBlock.h
        Generation/AdjacentChunkPositions.h
        Generation/AdjacentChunkBlockPositions.h
        Generation/ChunkMeshGenerator/ChunkMeshGenerator.cpp
        Generation/ChunkMeshGenerator/ChunkMeshGenerator.h
        World/World.cpp
        World/World.h
        Generation/ChunkGenerator/ChunkGenerator.cpp
        Generation/ChunkGenerator/ChunkGenerator.h
        Generation/ChunkGenerator/ChunkGenerator.cpp
        Model/Chunk/ChunkBlockLayer/IChunkBlockLayer.h
        Model/Chunk/ChunkBlockLayer/ChunkBlockLayer/ChunkBlockLayer.cpp
        Model/Chunk/ChunkBlockLayer/ChunkBlockLayer/ChunkBlockLayer.h
        Model/Chunk/ChunkBlockLayer/SingleBlockChunkBlockLayer.h
        Model/Chunk/IChunk/IChunk.cpp
        Model/Chunk/IChunk/IChunk.h
        Model/Chunk/SingleBlockTypeChunk/SingleBlockTypeChunk.cpp
        Model/Chunk/SingleBlockTypeChunk/SingleBlockTypeChunk.h
        Generation/NoiseGenerator/PerlinNoise.h
)

add_executable(CraftWorld ${SOURCE_FILES})
target_link_libraries(CraftWorld glfw3 wayland-client m GL GLU fmt)