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

#include "TileGrid.h"

namespace tile_renderer
{

TileGrid::TileGrid(int col_size, int row_size)
  : grid_(col_size, std::vector<Tile>(row_size))
{
}

TileGrid::Iterator TileGrid::Begin()
{
  return grid_.begin();
}

TileGrid::Iterator TileGrid::End()
{
  return grid_.end();
}

TileGrid::ConstIterator TileGrid::Begin() const
{
  return grid_.cbegin();
}

TileGrid::ConstIterator TileGrid::End() const
{
  return grid_.cend();
}

void TileGrid::SetTilePosition(Point const& index, Point const& position)
{
  if (InBounds(index))
    grid_[index.x][index.y].SetPosition(position);
}

void TileGrid::SetTileBreed(Point const& index, TileBreed const& breed)
{
  if (InBounds(index))
    grid_[index.x][index.y].ChangeBreed(breed);
}

Tile TileGrid::GetTile(Point const& index) const
{
  if (InBounds(index))
    return grid_[index.x][index.y];

  return Tile();
}

bool TileGrid::InBounds(Point const& index) const
{
  if (index.y >= 0 && index.y < grid_.size() &&
      index.x >= 0 && index.x < grid_[0].size())
  {
    return true;
  }

  return false;
}


} // namespace tile_renderer
