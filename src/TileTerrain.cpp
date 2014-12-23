//-*- Mode: C++; indent-tabs-mode: nil; tab-row_size: 2 -*-
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

#include "Rect.h"
#include "TileBreed.h"
#include "TileTerrain.h"

namespace tile_renderer
{

namespace
{
  int const TILE_SIZE = 32;

  TileBreed const GRASS_B = {TileType::GRASS, 0};
  TileBreed const DIRT_B  = {TileType::DIRT,  1};
}

TileTerrain::TileTerrain(int row_size, int col_size)
  : row_size_ (row_size)
  , col_size_(col_size)
  , renderer_(col_size, row_size)
  , tiles_(col_size, std::vector<Tile>(row_size))
{
  int tile_size = TILE_SIZE;
  int y_size = 0;
  int x_size = 0;

  for (int col = 0; col < col_size_; col++)
  {
    for (int row = 0; row < row_size_; row++)
    {
      Point p = {y_size, x_size};
      tiles_[col][row] = Tile(GRASS_B, p);
      x_size += tile_size;
    }

    y_size += tile_size;
    x_size = 0;
  }

  renderer_.InitRenderer(tiles_);
}

void TileTerrain::Draw()
{
  renderer_.RenderTiles();
}

void TileTerrain::HandleMouseClick(int x, int y)
{
  int size = TILE_SIZE;

  for (int col = 0; col < col_size_; col++)
  {
    for (int row = 0; row < row_size_; row++)
    {
      Point p = tiles_[col][row].Position();
      Rect r  = {p.x, p.y, size, size};

      if (r.IsPointInside({x,y}))
      {
        tiles_[col][row].ChangeBreed(DIRT_B);
        // FIXME Only update the tiles that need updating, not ALL of them :(
        renderer_.InitRenderer(tiles_);
      }
    }
  }
}

} // namespace tile_renderer
