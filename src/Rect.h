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

#ifndef RECT_H
#define RECT_H

#include "Point.h"

namespace tile_renderer
{

class Rect
{
public:
  Rect(float x = 0, float y = 0, float width = 0, float height = 0);

  float x() const;
  float y() const;
  float width() const;
  float height() const;

  void SetX(float x);
  void SetY(float y);
  void SetWidth(float width);
  void SetHeight(float height);

  bool IsPointInside(Point const& p);

private:
  float x_;
  float y_;
  float width_;
  float height_;
};

} // namespace tile_renderer

#endif // RECT_H
