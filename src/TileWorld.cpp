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

#define GLM_FORCE_RADIANS

//FIXME Make a simple orth matrix class to stuff all the glm in
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <stdio.h>

namespace tile_renderer
{

namespace
{
  int const MOVE = 8;

  int const TILE_SIZE = 32;
  int const COL_SIZE  = 64;
  int const ROW_SIZE  = 64;
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

  if (zoom_ + diff_zoom_ > 0.0f)
    zoom_    += diff_zoom_;

  glm::mat4 mat_mvp, mat_persp, mat_model;

  // ZOOM
  mat_mvp = glm::ortho(0.0f, (float)screen_width_  * zoom_,
                       0.0f, (float)screen_height_ * zoom_,
                       -1.0f, 1.0f);

  // MOVE X/Y
  mat_mvp = glm::translate(mat_mvp, glm::vec3(trans_x_, trans_y_, 0.0f));

  // SET MATRIX
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

void TileWorld::HandleMouseMove(int x, int y)
{
  // TODO Figure out how to pan the camera when the mouse hits the edge of the camera
}

void TileWorld::MoveCamera(Directions const& direction)
{
  switch (direction)
  {
    case Directions::RIGHT:
      MoveCameraRight();
      break;
    case Directions::LEFT:
      MoveCameraLeft();
      break;
    case Directions::UP:
      MoveCameraUp();
      break;
    case Directions::DOWN:
      MoveCameraDown();
      break;
  }
}

void TileWorld::MoveCameraRight()
{
  camera_rect_.SetX(camera_rect_.x() + MOVE);

  if (MoveWasInvalid())
    MoveCameraLeft();
}

void TileWorld::MoveCameraLeft()
{
  camera_rect_.SetX(camera_rect_.x() - MOVE);

  if (MoveWasInvalid())
    MoveCameraRight();
}

void TileWorld::MoveCameraUp()
{
  camera_rect_.SetY(camera_rect_.y() + MOVE);

  if (MoveWasInvalid())
    MoveCameraDown();
}

void TileWorld::MoveCameraDown()
{
  camera_rect_.SetY(camera_rect_.y() - MOVE);

  if (MoveWasInvalid())
    MoveCameraUp();
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
