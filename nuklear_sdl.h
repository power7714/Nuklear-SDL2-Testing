#ifndef NUKLEAR_SDL_H
#define NUKLEAR_SDL_H

#include <SDL2/SDL.h>

// Function to initialize Nuklear with SDL2
struct nk_context* nk_sdl_init(SDL_Renderer *renderer);

// Function to handle SDL events for Nuklear
void nk_sdl_handle_event(const SDL_Event *evt);

// Function to render Nuklear UI with SDL2
void nk_sdl_render(int max_vertex_buffer, int max_element_buffer);

// Function to shut down Nuklear and free resources
void nk_sdl_shutdown(void);

#endif // NUKLEAR_SDL_H
