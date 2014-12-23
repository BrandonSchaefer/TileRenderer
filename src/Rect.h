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
  Rect(int x = 0, int y = 0, int width = 0, int height = 0);

  int x() const;
  int y() const;
  int width() const;
  int height() const;

  void SetX(int x);
  void SetY(int y);
  void SetWidth(int width);
  void SetHeight(int height);

  bool IsPointInside(Point const& p);

private:
  int x_;
  int y_;
  int width_;
  int height_;
};

} // namespace tile_renderer

#endif // RECT_H
