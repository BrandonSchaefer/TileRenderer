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

#ifndef TILE_BREED_H
#define TILE_BREED_H

namespace tile_renderer
{

enum TileType
{
  GRASS = 0,
  DIRT,
  TREE,
  WATER,
  MOUNTAIN,
  FOG_OF_WAR
};

struct TileBreed
{
  TileType type;
  unsigned texture_offset;
};

} // namespace tile_renderer

#endif // TILE_BREED_H
