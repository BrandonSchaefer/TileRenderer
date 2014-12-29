find_package (PkgConfig)

set (TILE_RENDERER_REQUIRED
     glesv2
     sigc++-2.0
     sdl2
    )

pkg_check_modules(TILE_RENDERER REQUIRED ${TILE_RENDERER_REQUIRED})

set (TILE_RENDERER_LOADER_SRC
     OrthoMatrix.cpp
     Rect.cpp
     RendererUtils.cpp
     SDLTimer.cpp
     ShaderLoader.cpp
     Texture.cpp
     TextureLoader.cpp
     Tile.cpp
     TileGrid.cpp
     TileRenderer.cpp
     TileTerrain.cpp
     TileWorld.cpp
     Vector3.cpp
     VertexBufferObject.cpp
     main.cpp
    )

set (TILE_RENDERER_LOADER_HDR
     Directions.h
     OrthoMatrix.h
     Point.h
     Rect.h
     RendererUtils.h
     SDLTimer.h
     ShaderLoader.h
     Texture.h
     TextureLoader.h
     Tile.h
     TileGrid.h
     TileBreed.h
     TileRenderer.h
     TileTerrain.h
     TileWorld.h
     Vector3.h
     VertexBufferObject.h
     VertexData.h
    )

include_directories (${TILE_RENDERER_INCLUDE_DIRS} ${CMAKE_BINARY_DIR})

add_executable (tile_renderer ${TILE_RENDERER_LOADER_SRC} ${TILE_RENDERER_LOADER_HDR})

target_link_libraries (tile_renderer -lSOIL ${TILE_RENDERER_LIBRARIES} ${TILE_RENDERER_LDFLAGS})
