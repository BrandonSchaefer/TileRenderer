//-*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/* * Copyright (C) CURRENT_YEAR Brandon Scckhaefer
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

#ifndef TILE_WORLD_H
#define TILE_WORLD_H

#include "Directions.h"
#include "Rect.h"
#include "TileTerrain.h"

namespace tile_renderer
{

struct TileWorldSettings
{
  float screen_width;
  float screen_height;

  float offset_x;
  float offset_y;

  Rect camera;
};

class TileWorld
{
public:
  TileWorld(TileWorldSettings const& settings);

  Rect CameraRect() const;
  Rect WorldRect()  const;

  void Draw();

  void HandleKeyUp(int keysym);
  void HandleKeyDown(int keysym);

  void HandleMouseUp(int x, int y);
  void HandleMouseDown(int x, int y);
  void HandleMouseClick(int x, int y);
  void HandleMouseMove(int x, int y);

private:
  bool MoveWasInvalid() const;

  void UpdateCameraMoving();

  void CheckIfMouseDownAroundTheEdge(int x, int y);

  int screen_width_;
  int screen_height_;

  Rect camera_rect_;
  Rect world_rect_;

  TileTerrain terrain_;

  float trans_x_;
  float trans_y_;
  float diff_x_;
  float diff_y_;

  float zoom_;
  float diff_zoom_;

  bool mouse_down_;
};

} // namespace tile_renderer

#endif // TILE_WORLD_H
