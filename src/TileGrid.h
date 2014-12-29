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

#ifndef TILE_GRID_H
#define TILE_GRID_H

#include "Tile.h"

#include <vector>

namespace tile_renderer
{

class TileGrid
{
public:
  typedef std::vector<std::vector<Tile>>::iterator       Iterator;
  typedef std::vector<std::vector<Tile>>::const_iterator ConstIterator;

  TileGrid(int col_size, int row_size);

  Iterator Begin();
  Iterator End();

  ConstIterator Begin() const;
  ConstIterator End()   const;

  void SetTilePosition(Point const& index, Point const& position);
  void SetTileBreed   (Point const& index, TileBreed const& breed);

  Tile GetTile(Point const& index) const;

  std::vector<std::vector<Tile>> grid_;
private:
  bool InBounds(Point const& index) const;
};

} // namespace tile_renderer

#endif // TILE_GRID_H
