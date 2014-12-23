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

#include "TextureLoader.h"

#include <SOIL/SOIL.h>

#include <stdexcept>

namespace tile_renderer
{

Texture LoadTexture(std::string const& path)
{
  Texture texture;
  GLuint texture_id;

  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &texture_id);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id);

  int width, height;
  unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

  SOIL_free_image_data(image);

  texture.id     = texture_id;
  texture.width  = width;
  texture.height = height;

  if (texture_id == 0)
    throw std::runtime_error("Failed to load texture!");

  return texture;
}

} // namespace tile_renderer
