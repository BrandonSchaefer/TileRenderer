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

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "OrthoMatrix.h"

OrthoMatrix::OrthoMatrix(int width, int height)
  : width_ (width)
  , height_(height)
{
}

glm::mat4 OrthoMatrix::GetMVPMatrix(float trans_x, float trans_y, float zoom) const
{
  glm::mat4 mat_mvp;

  mat_mvp = glm::ortho(0.0f, (float)width_  * zoom,
                       0.0f, (float)height_ * zoom,
                       -1.0f, 1.0f);

  mat_mvp = glm::translate(mat_mvp, glm::vec3(trans_x, trans_y, 0.0f));

  return mat_mvp;
}
