/*
 * Copyright 2017 Joshua Vega
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#define PROJECT_NAME "Project 2"

SDL_Window *window;
SDL_GLContext context;

int init() {
  /* Request OpenGL 2.1 (for now) */
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("Error initializing SDL: %s\n", SDL_GetError());
    return 1;
  }
  
  window = SDL_CreateWindow(PROJECT_NAME,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            1280,
                            720,
                            SDL_WINDOW_OPENGL);

  if (!window) {
    printf("Error initializing SDL window: %s\n", SDL_GetError());
    return 1;
  }

  context = SDL_GL_CreateContext(window);
  GLenum err = glewInit();

  if (err != GLEW_OK) {
    printf("Error initializing GLEW: %s\n", glewGetErrorString(err));
    return 1;
  }
  
  return 0;
}

void render_frame() {
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  /* Draw a triangle using immediate mode */
  glBegin(GL_TRIANGLES);
  glColor3f(0.5, 0.0, 0.0);
  glVertex2f(0.0f, 1.0f);
  glVertex2f(-1.0f, -1.0f);
  glVertex2f(1.0f, -1.0f);
  glEnd();

  SDL_GL_SwapWindow(window);
}

int handle_events() {  
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return 1;
    } else if (event.type == SDL_WINDOWEVENT) {
      switch (event.window.event) {
      case SDL_WINDOWEVENT_CLOSE:
        return 1;
      }
    }
  }
  
  return 0;
}

void cleanup() {
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(int argc, char **argv) {
  init();

  while (1) {
    if (handle_events() != 0) break;
    render_frame();
  }

  cleanup();
  return 0;
}
