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

#ifndef VERTEX_BUFFER_OBJECT_H
#define VERTEX_BUFFER_OBJECT_H

#include <GLES2/gl2.h>

namespace tile_renderer
{

struct VertexData;

class VertexBufferObject
{
public:
  VertexBufferObject();
  ~VertexBufferObject();

  void InitVBOs(GLint num_vert, VertexData* vert_buff,
                GLint num_indices, GLushort* indices);

  void DrawVBOs();

private:
  GLuint vbo_;
  GLuint ibo_;

  GLint num_indices_;
};

} // namespace tile_renderer

#endif // VERTEX_BUFFER_OBJECT_H
