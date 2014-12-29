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

#include <SDL2/SDL.h>

#include "TileWorld.h"

#include "OrthoMatrix.h"

#include <stdio.h>

namespace tile_renderer
{

namespace
{
  int const MOVE = 4;

  int const TILE_SIZE = 32;
  int const COL_SIZE  = 128;
  int const ROW_SIZE  = 128;
}

TileWorld::TileWorld(TileWorldSettings const& settings)
  : camera_rect_(settings.camera)
  , world_rect_ ({settings.offset_x, settings.offset_y,
                  COL_SIZE * TILE_SIZE + settings.offset_x,
                  ROW_SIZE * TILE_SIZE + settings.offset_y}) 
  , terrain_(ROW_SIZE, COL_SIZE, camera_rect_)
  , screen_width_ (settings.screen_width)
  , screen_height_(settings.screen_height)
  , trans_x_(0.0f)
  , trans_y_(0.0f)
  , diff_x_(0.0f)
  , diff_y_(0.0f)
  , zoom_(1.0f)
  , diff_zoom_(0.0f)
  , mouse_down_(false)
{
}

void TileWorld::UpdateCameraMoving()
{
  camera_rect_.SetX(camera_rect_.x() + diff_x_);
  camera_rect_.SetY(camera_rect_.y() + diff_y_);

  if (MoveWasInvalid())
  {
    camera_rect_.SetX(camera_rect_.x() - diff_x_);
    camera_rect_.SetY(camera_rect_.y() - diff_y_);
  }

  trans_x_ = world_rect_.x() - camera_rect_.x();
  trans_y_ = world_rect_.y() - camera_rect_.y();
}

void TileWorld::Draw()
{
  UpdateCameraMoving();

  OrthoMatrix orth_mat(screen_width_, screen_height_);

  if (zoom_ + diff_zoom_ > 0.0f)
    zoom_    += diff_zoom_;

  glm::mat4 mat_mvp = orth_mat.GetMVPMatrix(trans_x_, trans_y_, zoom_);

  glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mat_mvp));

  terrain_.Draw();
}

Rect TileWorld::CameraRect()  const
{
  return camera_rect_;
}

Rect TileWorld::WorldRect() const
{
  return world_rect_;
}

void TileWorld::HandleKeyUp(int keysym)
{
  switch (keysym)
  {
    case SDLK_LEFT:
    case SDLK_RIGHT:
      diff_x_ = 0.0f;
      break;
    case SDLK_UP:
    case SDLK_DOWN:
      diff_y_ = 0.0f;
      break;
    case SDLK_z:
    case SDLK_x:
      diff_zoom_ = 0.0f;
      break;
    default:
      break;
  }
}

void TileWorld::HandleKeyDown(int keysym)
{
  switch (keysym)
  {
    case SDLK_LEFT:
      diff_x_ = -MOVE;
      break;
    case SDLK_RIGHT:
      diff_x_ = MOVE;
      break;
    case SDLK_UP:
      diff_y_ = MOVE;
      break;
    case SDLK_DOWN:
      diff_y_ = -MOVE;
      break;
    case SDLK_z:
      diff_zoom_ = 0.01f;
      break;
    case SDLK_x:
      diff_zoom_ = -0.01f;
      break;
    default:
      break;
  }
}

void TileWorld::HandleMouseClick(int x, int y)
{
  int opengl_x = x - trans_x_;
  int opengl_y = screen_height_ - (y + trans_y_);

  terrain_.HandleMouseClick(opengl_x, opengl_y);
}

void TileWorld::HandleMouseUp(int x, int y)
{
  mouse_down_ = false;
  CheckIfMouseDownAroundTheEdge(x, y);
}

void TileWorld::HandleMouseDown(int x, int y)
{
  mouse_down_ = true;
  CheckIfMouseDownAroundTheEdge(x, y);
}

void TileWorld::HandleMouseMove(int x, int y)
{
  CheckIfMouseDownAroundTheEdge(x, y);
}

// FIXME clean this up a bit... Also should look at changing cursor when at the edge!
void TileWorld::CheckIfMouseDownAroundTheEdge(int x, int y)
{
  if (mouse_down_)
  {
    float size        = 20;
    // FIXME Get a correct size from somewhere
    float border_size = 44;

    // Create edge barriers to detect when a mouse is inside
    Rect left_edge  = {world_rect_.x() - border_size,
                       world_rect_.y(),
                       size + border_size,
                       camera_rect_.height()};

    Rect right_edge = {world_rect_.x() + camera_rect_.width() - size,
                       world_rect_.y(),
                       size + border_size,
                       camera_rect_.height()};

    Rect up_edge    = {world_rect_.x(),
                       world_rect_.y() - border_size,
                       camera_rect_.width(),
                       size + border_size};

    Rect down_edge  = {world_rect_.x(),
                       world_rect_.y() + camera_rect_.height() - size,
                       camera_rect_.width(),
                       size + border_size};

    if (left_edge.IsPointInside({x, y}))
    {
      diff_x_ = -MOVE;
    }
    else if (right_edge.IsPointInside({x, y}))
    {
      diff_x_ = MOVE;
    }
    else
    {
      diff_x_ = 0.0f;
    }

    if (up_edge.IsPointInside({x, y}))
    {
      diff_y_ = MOVE;
    }
    else if (down_edge.IsPointInside({x, y}))
    {
      diff_y_ = -MOVE;
    }
    else
    {
      diff_y_ = 0.0f;
    }
  }
  else
  {
    diff_x_ = 0.0f;
    diff_y_ = 0.0f;
  }
}

bool TileWorld::MoveWasInvalid() const
{
  if (camera_rect_.x() < world_rect_.x() ||
      camera_rect_.y() < world_rect_.y() ||
      camera_rect_.x() + camera_rect_.width()  > world_rect_.width() ||
      camera_rect_.y() + camera_rect_.height() > world_rect_.height())
  {
    return true;
  }

  return false;
}

} // namespace tile_renderer
