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

#include "ShaderLoader.h"

#include <iostream>

namespace tile_renderer
{

static GLuint LoadShader(char const* src, GLenum type)
{
  GLuint shader = glCreateShader(type);
  if (shader)
  {
    GLint compiled;
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
      GLint info_len;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);

      if (info_len > 1)
      {
        char* info_log = (char*)malloc(sizeof(char) * info_len);

        glGetShaderInfoLog(shader, info_len, NULL, info_log);
        std::cerr << "Failed to comiple shader:\n" << info_log << std::endl;

        free(info_log);
      }

      glDeleteShader(shader);

      return 0;
    }
  }

  return shader;
}

GLint LoadProgram(char const* vertex_src, char const* fragment_src)
{
  GLint program;
  GLuint vertex, fragment;

  vertex   = LoadShader(vertex_src,   GL_VERTEX_SHADER);
  fragment = LoadShader(fragment_src, GL_FRAGMENT_SHADER);

  if (!vertex || !fragment)
    return 0;

  program = glCreateProgram();

  if (program == 0)
    return 0;

  glAttachShader(program, vertex);
  glAttachShader(program, fragment);

  glLinkProgram(program);

  GLint linked;
  glGetProgramiv(program, GL_LINK_STATUS, &linked);

  if (!linked)
  {
    GLint info_len = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_len);

    if (info_len > 1)
    {
      char* info_log = (char*)malloc(sizeof(char) * info_len);
      glGetProgramInfoLog(program, info_len, NULL, info_log);

      std::cerr << "Failed to link shaders:\n" << info_log << std::endl;
      free(info_log);
    }

    glDeleteProgram(program);
    return 0;
  }

  return program;
}

} // namespace tile_renderer
