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

// Check each neighbours to see if they are different types. If they are
// Then set rlud to 1, which will then be turned from a binary to decimal
// FIXME I need to clean this up...
int TileRenderer::GetBinaryFormTileNeighbours(std::vector<std::vector<Tile>> const& tiles, Point const& p)
{
  // RIGHT LEFT UP DOWN
  int rlud[4] = {0};

  TileType type = tiles[p.x][p.y].Type();

  // Up
  if (p.x + 1 < col_size_ && tiles[p.x + 1][p.y].Type() != type)
    rlud[2] = 1;

  // Down
  if (p.x - 1 >= 0 && tiles[p.x - 1][p.y].Type() != type)
    rlud[3] = 1;

  // Right
  if (p.y + 1 < row_size_ && tiles[p.x][p.y + 1].Type() != type)
    rlud[0] = 1;

  // Left
  if (p.y - 1 >= 0 && tiles[p.x][p.y - 1].Type() != type)
    rlud[1] = 1;

  // Turn rlud from a binary number to a dec.
  return 8 * rlud[0] +
         4 * rlud[1] +
         2 * rlud[2] +
         1 * rlud[3];
}

// How am i going to update a specific tile? a VBO Index possibly:
// pointer_offset = index * 4 * sizeof(GLfloat);
// FIXME Look at reducing the size of this functions...clean up!
void TileRenderer::InitRenderer(std::vector<std::vector<Tile>> const& tiles)
{
  int index     = 0;
  int vbo_index = 0;

  for (int col = 0; col < col_size_; col++)
  {
    for (int row = 0; row < row_size_; row++)
    {
      // FIXME Consider a better way to do all the sprite s_col/s_row selection.
      // Will need this when I can update each cells
      int s_col = 0;
      int s_row = 0;

      if (tiles[col][row].Type() == TileType::DIRT)
      {
        int bin = GetBinaryFormTileNeighbours(tiles, {col,row});
        int texture_offset = tiles[col][row].TextureOffset();

        s_col = (bin + texture_offset) / 8;
        s_row = (bin + texture_offset) % 8;
      }

      Point p = tiles[col][row].Position();

      float spacing_w = SPACING / sprite_sheet_.width;
      float spacing_h = SPACING / sprite_sheet_.height;

      float s_w = SPRITE_SIZE / sprite_sheet_.width;
      float s_h = SPRITE_SIZE / sprite_sheet_.height;

      float s_x = s_row * s_w + spacing_w * s_row;
      float s_y = s_col * s_h + spacing_h * s_col;

      float tl_x = p.x;
      float tl_y = p.y + SPRITE_SIZE;

      float bl_x = p.x;
      float bl_y = p.y;

      float br_x = p.x + SPRITE_SIZE;
      float br_y = p.y;

      float tr_x = p.x + SPRITE_SIZE;
      float tr_y = p.y + SPRITE_SIZE;

      vertex_data_[index++] = {bl_x, bl_y, 0.0f, s_x,       s_y + s_h};
      vertex_data_[index++] = {br_x, br_y, 0.0f, s_x + s_w, s_y + s_h};
      vertex_data_[index++] = {tr_x, tr_y, 0.0f, s_x + s_w, s_y};
      vertex_data_[index++] = {tl_x, tl_y, 0.0f, s_x,       s_y};

      //tiles_[col][row].SetVBOIndex(vbo_index);

      vbo_index++;
    }
  }

  int cur_indice = 0;
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

  vbo_.DrawVBOs();
}

} // tile_renderer
