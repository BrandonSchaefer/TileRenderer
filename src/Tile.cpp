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

#include "Tile.h"

namespace tile_renderer
{

Tile::Tile()
  : position_({0,0})
  , type_(TileType::GRASS)
  , texture_offset_(0)
  , vbo_index_(0)
{
}

Tile::Tile(TileBreed const& breed)
  : position_({0,0})
  , type_(breed.type)
  , texture_offset_(breed.texture_offset)
  , vbo_index_(0)
{
}

Tile::Tile(TileBreed const& breed, Point const& p)
  : position_(p)
  , type_(breed.type)
  , texture_offset_(breed.texture_offset)
  , vbo_index_(0)
{
}

void Tile::SetVBOIndex(int index)
{
  vbo_index_ = index;
}

int Tile::GetVBOIndex() const
{
  return vbo_index_;
}

Point Tile::Position() const
{
  return position_;
}

TileType Tile::Type() const
{
  return type_;
}

unsigned Tile::TextureOffset() const
{
  return texture_offset_;
}

void Tile::ChangeBreed(TileBreed const& breed)
{
  type_           = breed.type;
  texture_offset_ = breed.texture_offset;
  changed.emit();
}

} // namespace tile_renderer
