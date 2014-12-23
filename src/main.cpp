// -*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/*
 * Copyright (C) 2014 Brandon Schaefer
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

#include <stdexcept>

#include "SDLTimer.h"
#include "ShaderLoader.h"
#include "Shaders.h"
#include "TileWorld.h"

namespace tile_renderer
{

namespace
{
  int const WIDTH  = 800;
  int const HEIGHT = 600;
  int const FRAMES_PER_SECOND = 60;
  float const ONE_SECOND      = 1000.0f;

  float const MOVE = 5.0f;
}

void InitSDL()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    throw std::runtime_error("Failed to INIT SDL");
}

void StartGame()
{
  SDL_Window* window;
  SDL_GLContext context;
  VertexBufferObject vbo;

  InitSDL();

  window = SDL_CreateWindow("Tile Renderer",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
  if (!window)
    throw std::runtime_error("Error could not create SDL window");

  context = SDL_GL_CreateContext(window);

  GLint program = LoadProgram(VERTEX_SHADER_DEFAULT_SRC,
                              FRAGMENT_SHADER_DEFAULT_SRC);

  SDL_GL_MakeCurrent(window, context);

  glUseProgram(program);

  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

  TileWorld t_world(WIDTH, HEIGHT);

  tile_renderer::SDLTimer fps;

  bool done = false;
  bool flip = true;
  bool mouse_down = false;

  while (!done)
  {
    fps.start();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_KEYUP:
        {
          t_world.HandleKeyUp(event.key.keysym.sym);
          break;
        }
        case SDL_KEYDOWN:
        {
          t_world.HandleKeyDown(event.key.keysym.sym);

          if (event.key.keysym.sym == SDLK_ESCAPE)
            done = true;
          break;
        }
        case SDL_MOUSEMOTION:
        {
          if (mouse_down)
            t_world.HandleMouseClick(event.button.x, event.button.y);
          break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
          mouse_down = true;
          t_world.HandleMouseClick(event.button.x, event.button.y);
          break;
        }
        case SDL_MOUSEBUTTONUP:
        {
          mouse_down = false;
          break;
        }
        case SDL_QUIT:
          done = true;
          break;
      }
    }

    // FIXME Move this to a different class.
    // Think about only updating this when sometings changed!
    /*
    if (trans_x < 0)
      trans_x -= diff_x;
    if (trans_y < 0)
      trans_y -= diff_y;

    if (trans_x + WIDTH * zoom > 32 * 128)
      trans_x -= diff_x;
    if (trans_y + WIDTH * zoom > 32 * 128)
      trans_y -= diff_y;

    zoom += zoom_diff;
    */

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    t_world.Draw();

    SDL_GL_SwapWindow(window);

    // FIXME replace with a better FPS, dont just cap it at 60...
    if (fps.ticks() < ONE_SECOND / FRAMES_PER_SECOND)
      SDL_Delay((ONE_SECOND / FRAMES_PER_SECOND) - fps.ticks());
  }

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);

  SDL_Quit();
}

} // namespace tile_renderer

int main()
{
  tile_renderer::StartGame();
}
