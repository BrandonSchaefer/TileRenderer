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

#ifndef TILE_H
#define TILE_H

#include "Point.h"
#include "TileBreed.h"

#include <sigc++/signal.h>

namespace tile_renderer
{

class Tile
{
public:
  Tile();
  Tile(TileBreed const& breed);
  Tile(TileBreed const& breed, Point const& p);

  void SetVBOIndex(int index);
  int  GetVBOIndex() const;

  Point Position() const;

  TileType Type() const;

  unsigned TextureOffset() const;

  void ChangeBreed(TileBreed const& breed);

  sigc::signal<void> changed;

private:
  Point position_;
  TileType type_;
  unsigned texture_offset_;
  int vbo_index_;
};

} // namespace tile_renderer

#endif // TILE_H
