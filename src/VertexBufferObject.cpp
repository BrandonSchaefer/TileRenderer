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

#include "VertexBufferObject.h"
#include "VertexData.h"

// FIXME Shader specific... think about this if i want multiple shaders
#define VERT_SIZE  3 // x y z
#define TEX_SIZE   2 // s v

// FIXME define these in a bit, either bind or get the location
#define VERT_INDEX  0 // attrib
#define TEX_INDEX   1 // attrib

namespace tile_renderer
{

VertexBufferObject::VertexBufferObject()
  : num_indices_(0)
{
}

VertexBufferObject::~VertexBufferObject()
{
  glDeleteBuffers(1, &vbo_);
  glDeleteBuffers(1, &ibo_);
}

void VertexBufferObject::InitVBOs(GLint num_vert, VertexData* vert_buff,
                                  GLint num_indices, GLushort* indices)
{
  glGenBuffers(1, &vbo_);
  glGenBuffers(1, &ibo_);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(VertexData) * num_vert,
               vert_buff, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(GLushort) * num_indices,
               indices, GL_STATIC_DRAW);

  num_indices_ = num_indices;
}

void VertexBufferObject::DrawVBOs()
{
  uintptr_t offset = 0;

  glEnableVertexAttribArray(VERT_INDEX);
  glEnableVertexAttribArray(TEX_INDEX);

  glVertexAttribPointer(VERT_INDEX, VERT_SIZE,
                        GL_FLOAT, GL_FALSE,
                        sizeof(VertexData), 0);

  offset += VERT_SIZE * sizeof(GLfloat);
  glVertexAttribPointer(TEX_INDEX, TEX_SIZE,
                        GL_FLOAT, GL_FALSE,
                        sizeof(VertexData), (void const*)offset);

  glDrawElements(GL_TRIANGLES, num_indices_, GL_UNSIGNED_SHORT, 0);
}

} // namespace tile_renderer
