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

#ifndef RENDERER_UTILS_H
#define RENDERER_UTILS_H

#include "Point.h"
#include "Rect.h"
#include "Vector3.h"

namespace tile_renderer
{

extern void gen_tex_coords (Rect const& s_rect, Vector3 out_tex_coords[4]);
extern void gen_vert_coords(Rect const& v_rect, Vector3 out_vert_coords[4]);

} // namespace tile_renderer

#endif // RENDERER_UTILS_H
