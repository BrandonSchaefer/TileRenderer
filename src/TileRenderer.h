//-*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/* * Copyright (C) CURRENT_YEAR Brandon Schaefer
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 3 as
* published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* Authored by: Brandon Schaefer <brandontschaefer@gmail.com>
*/

#ifndef TILE_RENDERER_H
#define TILE_RENDERER_H

#include <GLES2/gl2.h>

#include "Tile.h"
#include "Texture.h"
#include "TextureLoader.h"
#include "VertexBufferObject.h"
#include "VertexData.h"
#include <vector>

namespace tile_renderer
{

class TileRenderer
{
public:
  TileRenderer(int col_size, int row_size);
  ~TileRenderer();

  void InitRenderer(std::vector<std::vector<Tile>> const& tiles);
  void RenderTiles();

private:
  int GetBinaryFormTileNeighbours(std::vector<std::vector<Tile>> const& tiles, Point const& p);

  int col_size_;
  int row_size_;

  Texture     sprite_sheet_;
  VertexData* vertex_data_;
  GLushort*   indices_;
  VertexBufferObject vbo_;
};

} // tile_renderer

#endif // TILE_RENDERER_H
