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

#include "RendererUtils.h"
#include "TileRenderer.h"
#include "TextureLoader.h"

#include "config.h"

namespace tile_renderer
{

namespace
{
  char const SPRITE_SHEET_PATH[] = RESDIR"/grass_dirt_sprite_sheet.png";

  int const VERTEX_TILE_SIZE = 4;
  int const INDICE_TILE_SIZE = 6;
  float const SPRITE_SIZE    = 32.0f;
  float const SPACING        =  1.0f;
}

TileRenderer::TileRenderer(int col_size, int row_size)
  : col_size_(col_size)
  , row_size_(row_size)
  , sprite_sheet_(LoadTexture(SPRITE_SHEET_PATH))
  , vertex_data_(new VertexData[row_size_ * col_size_ * VERTEX_TILE_SIZE])
  , indices_(    new GLushort  [row_size_ * col_size_ * INDICE_TILE_SIZE])
{
}

TileRenderer::~TileRenderer()
{
  delete[] vertex_data_;
  delete[] indices_;
}

constexpr int convert_neighbours_binary_to_decimal(int const rlud[4])
{
  return 8 * rlud[0] +
         4 * rlud[1] +
         2 * rlud[2] +
         1 * rlud[3];
}

// Check each neighbours to see if they are different types. If they are
// Then set rlud to 1, which will then be turned from a binary to decimal
int TileRenderer::GetBinaryFormTileNeighbours(TileGrid const& tiles, Point const& p)
{
  // RIGHT LEFT UP DOWN
  int rlud[4] = {0};

  Tile self  = tiles.GetTile(p);
  Tile right = tiles.GetTile({p.x, p.y + 1});
  Tile left  = tiles.GetTile({p.x, p.y - 1});
  Tile up    = tiles.GetTile({p.x + 1, p.y});
  Tile down  = tiles.GetTile({p.x - 1, p.y});

  TileType type = self.Type();

  if (right.Valid() && right.Type() != type)
    rlud[0]++;
  if (left.Valid()  && left.Type()  != type)
    rlud[1]++;
  if (up.Valid()    && up.Type()    != type)
    rlud[2]++;
  if (down.Valid()  && down.Type()  != type)
    rlud[3]++;

  // Turn rlud from a binary number to a dec.
  return convert_neighbours_binary_to_decimal(rlud);
}

Point TileRenderer::GetSpritePosition(TileGrid const& tiles, Point const& index)
{
  int s_col = 0;
  int s_row = 0;

  Tile self = tiles.GetTile(index);

  if (self.Type() != TileType::GRASS)
  {
    int bin            = GetBinaryFormTileNeighbours(tiles, index);
    int texture_offset = self.TextureOffset();

    s_col = (bin + texture_offset) / 8;
    s_row = (bin + texture_offset) % 8;
  }

  return {s_col, s_row};
}

Rect TileRenderer::GetSpriteRectangle(TileGrid const& tiles, Point const& index)
{
  Point s_p = GetSpritePosition(tiles, index);

  float spacing_w = SPACING / sprite_sheet_.width;
  float spacing_h = SPACING / sprite_sheet_.height;

  float s_w = SPRITE_SIZE / sprite_sheet_.width;
  float s_h = SPRITE_SIZE / sprite_sheet_.height;

  float s_x = s_p.y * s_w + spacing_w * s_p.y;
  float s_y = s_p.x * s_h + spacing_h * s_p.x;

  return {s_x, s_y, s_w, s_h};
}

void TileRenderer::UpdateTileVertexData(TileGrid const& tiles, Point const& index)
{
  Tile tile = tiles.GetTile(index);

  if (tile.Valid())
  {
    VertexData vertex_data[VERTEX_TILE_SIZE];
    Vector3    tex_coords[4];

    Rect s_rect = GetSpriteRectangle(tiles, index);
    gen_tex_coords(s_rect, tex_coords);

    int vbo_index = tile.GetVBOIndex();
    int offset    = vbo_index * VERTEX_TILE_SIZE;

    for (int i = 0; i < VERTEX_TILE_SIZE; i++)
    {
      vertex_data[i]   = vertex_data_[offset + i];
      vertex_data[i].s = tex_coords[i].x;
      vertex_data[i].t = tex_coords[i].y;
    }

    GLintptr vbo_offset = vbo_index * VERTEX_TILE_SIZE * sizeof(VertexData);
    GLsizeiptr vbo_size = VERTEX_TILE_SIZE * sizeof(VertexData);

    vbo_.UpdateVBOData(vbo_offset, vbo_size, vertex_data);
  }
}

void TileRenderer::AddNewTileVertexData(Vector3 const vert_coords[4], Vector3 const tex_coords[4])
{
  static int index = 0;
  int i = 0;
  for (int i = 0; i < VERTEX_TILE_SIZE; i++)
  {
    vertex_data_[index].x = vert_coords[i].x;
    vertex_data_[index].y = vert_coords[i].y;
    vertex_data_[index].z = vert_coords[i].z;

    vertex_data_[index].s = tex_coords[i].x;
    vertex_data_[index].t = tex_coords[i].y;
    index++;
  }
}

void TileRenderer::InitRenderer(TileGrid& tiles)
{
  int vbo_index = 0;

  Vector3 tex_coords[4];
  Vector3 vert_coords[4];

  int col = 0, row = 0;

  for (auto tile_col = tiles.Begin(); tile_col != tiles.End(); ++tile_col)
  {
    for (auto tile = tile_col->begin(); tile != tile_col->end(); ++tile)
    {
      Point p     = tile->Position();
      Rect s_rect = GetSpriteRectangle(tiles, {col, row});
      Rect v_rect = {(float)p.x, (float)p.y, SPRITE_SIZE, SPRITE_SIZE};

      gen_vert_coords(v_rect, vert_coords);
      gen_tex_coords (s_rect, tex_coords);

      AddNewTileVertexData(vert_coords, tex_coords);

      tile->SetVBOIndex(vbo_index);

      vbo_index++;
      row++;
    }

    row = 0;
    col++;
  }

  int cur_indice = 0;

  // FIXME clean this part up... should be able to do this in a loop or so
  for (int i = 0; i < row_size_ * col_size_ * INDICE_TILE_SIZE; i += INDICE_TILE_SIZE)
  {
    indices_[i]   = cur_indice;
    indices_[i+1] = cur_indice + 1;
    indices_[i+2] = cur_indice + 2;
    indices_[i+3] = cur_indice;
    indices_[i+4] = cur_indice + 2;
    indices_[i+5] = cur_indice + 3;

    cur_indice += 4;
  }

  vbo_.InitVBOs(row_size_ * col_size_ * VERTEX_TILE_SIZE, vertex_data_,
                row_size_ * col_size_ * INDICE_TILE_SIZE, indices_);
}

void TileRenderer::RenderTiles()
{
  glBindTexture(GL_TEXTURE_2D, sprite_sheet_.id);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  vbo_.DrawVBOs();

  glDisable(GL_BLEND);
}

} // tile_renderer
