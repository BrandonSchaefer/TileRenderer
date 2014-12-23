find_package (PkgConfig)

set (TILE_RENDERER_REQUIRED
     glesv2
     sigc++-2.0
     sdl2
    )

pkg_check_modules(TILE_RENDERER REQUIRED ${TILE_RENDERER_REQUIRED})

set (TILE_RENDERER_LOADER_SRC
     Rect.cpp
     SDLTimer.cpp
     ShaderLoader.cpp
     Texture.cpp
     TextureLoader.cpp
     Tile.cpp
     TileRenderer.cpp
     TileTerrain.cpp
     TileWorld.cpp
     VertexBufferObject.cpp
     main.cpp
    )

set (TILE_RENDERER_LOADER_HDR
     Directions.h
     Point.h
     Rect.h
     SDLTimer.h
     ShaderLoader.h
     Texture.h
     TextureLoader.h
     Tile.h
     TileBreed.h
     TileRenderer.h
     TileTerrain.h
     TileWorld.h
     VertexBufferObject.h
     VertexData.h
    )

include_directories (${TILE_RENDERER_INCLUDE_DIRS} ${CMAKE_BINARY_DIR})

add_executable (tile_renderer ${TILE_RENDERER_LOADER_SRC} ${TILE_RENDERER_LOADER_HDR})

target_link_libraries (tile_renderer -lSOIL ${TILE_RENDERER_LIBRARIES} ${TILE_RENDERER_LDFLAGS})
