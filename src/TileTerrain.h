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

#ifndef TILE_TERRAIN_H
#define TILE_TERRAIN_H

#include "Texture.h"
#include "Tile.h"
#include "TileRenderer.h"

#include <vector>

namespace tile_renderer
{

class TileTerrain
{
public:
  TileTerrain(int row_size, int col_size);

  void HandleMouseClick(int x, int y);

  void Draw();

private:
  int GetBinaryFormTileNeighbours(Point const& p);
  void BuildVertexData();

  int row_size_;
  int col_size_;

  TileRenderer renderer_;

  std::vector<std::vector<Tile>> tiles_;
};

} // namespace tile_renderer

#endif // TILE_TERRAIN_H
