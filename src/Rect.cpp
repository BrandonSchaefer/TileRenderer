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

#include "Rect.h"

namespace tile_renderer
{

Rect::Rect(int x, int y, int width, int height)
  : x_(x)
  , y_(y)
  , width_ (width)
  , height_(height)
{
}

int Rect::x() const
{
  return x_;
}

int Rect::y() const
{
  return y_;
}

int Rect::width() const
{
  return width_;
}

int Rect::height() const
{
  return height_;
}

void Rect::SetX(int x)
{
  x_ = x;
}

void Rect::SetY(int y)
{
  y_ = y;
}

void Rect::SetWidth(int width)
{
  width_ = width;
}

void Rect::SetHeight(int height)
{
  height_ = height;
}

bool Rect::IsPointInside(Point const& p)
{
  if (p.x >= x_ && p.x < x_ + width_ &&
      p.y >= y_ && p.y < y_ + height_)
  {
    return true;
  }

  return false;
}

} // namespace tile_renderer
