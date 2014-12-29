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

#include <stdlib.h>
#include <time.h>

namespace tile_renderer
{

namespace
{
  float const TILE_SIZE = 32;

  TileBreed const GRASS_B = {TileType::GRASS, 0};
  TileBreed const DIRT_B  = {TileType::DIRT,  1};
  TileBreed const TREE_B  = {TileType::TREE,  17};
  TileBreed const WATER_B = {TileType::WATER, 22};
  TileBreed const FOG_B   = {TileType::FOG_OF_WAR, 65};
}

TileTerrain::TileTerrain(int row_size, int col_size, Rect const& camera)
  : row_size_ (row_size)
  , col_size_(col_size)
  , renderer_(col_size, row_size)
  , tiles_(col_size, row_size)
{
  int tile_size = TILE_SIZE;

  int x_size = camera.x();
  int y_size = camera.y();

  srand(time(nullptr));

  for (int col = 0; col < col_size_; col++)
  {
    for (int row = 0; row < row_size_; row++)
    {
      Point position = {x_size, y_size};
      Point index    = {col, row};

      int r = rand() % 2;
      if (r == 0)
        tiles_.SetTileBreed(index, TREE_B);
      else if (r == 1)
        tiles_.SetTileBreed(index, GRASS_B);

      tiles_.SetTilePosition(index, position);

      x_size += tile_size;
    }

    y_size += tile_size;
    x_size  = camera.x();
  }

  renderer_.InitRenderer(tiles_);
}

void TileTerrain::Draw()
{
  renderer_.RenderTiles();
}

// Mainly for test/fun remove w/e
void TileTerrain::HandleMouseClick(int x, int y)
{
  int col = 0, row = 0;

  for (auto tile_col = tiles_.Begin(); tile_col != tiles_.End(); ++tile_col)
  {
    for (auto tile = tile_col->begin(); tile != tile_col->end(); ++tile)
    {
      Point p = tile->Position();
      Rect r  = {(float)p.x, (float)p.y, TILE_SIZE, TILE_SIZE};

      if (r.IsPointInside({x,y}) && tile->Type() != DIRT)
      {
        tile->ChangeBreed(DIRT_B);

        renderer_.UpdateTileVertexData(tiles_, {col, row});

        renderer_.UpdateTileVertexData(tiles_, {col - 1, row});
        renderer_.UpdateTileVertexData(tiles_, {col + 1, row});
        renderer_.UpdateTileVertexData(tiles_, {col, row - 1});
        renderer_.UpdateTileVertexData(tiles_, {col, row + 1});
      }

      row++;
    }

    row = 0;
    col++;
  }
}

} // namespace tile_renderer
