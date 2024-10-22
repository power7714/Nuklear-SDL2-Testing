#define NK_IMPLEMENTATION
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_SDL_GL3_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES

#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "nuklear.h"
#include "nuklear_sdl.h"

static struct nk_color bg_color;

// Function to initialize Nuklear with SDL2
struct nk_context* nk_sdl_init(SDL_Renderer *renderer) {
    struct nk_context *ctx = malloc(sizeof(struct nk_context));
    if (!ctx) {
        return NULL;
    }

    nk_init(ctx, 0);
    bg_color = nk_rgb(28, 48, 62);

    return ctx;
}

// Function to handle SDL events for Nuklear
void nk_sdl_handle_event(const SDL_Event *evt) {
    if (evt->type == SDL_MOUSEMOTION) {
        nk_input_motion(nk_sdl_get_context(), evt->motion.x, evt->motion.y);
    }
    else if (evt->type == SDL_MOUSEBUTTONDOWN) {
        if (evt->button.button == SDL_BUTTON_LEFT)
            nk_input_button(nk_sdl_get_context(), NK_BUTTON_LEFT, evt->button.x, evt->button.y, 1);
    }
    else if (evt->type == SDL_MOUSEBUTTONUP) {
        if (evt->button.button == SDL_BUTTON_LEFT)
            nk_input_button(nk_sdl_get_context(), NK_BUTTON_LEFT, evt->button.x, evt->button.y, 0);
    }
    else if (evt->type == SDL_KEYDOWN) {
        nk_input_key(nk_sdl_get_context(), evt->key.keysym.sym, 1);
    }
    else if (evt->type == SDL_KEYUP) {
        nk_input_key(nk_sdl_get_context(), evt->key.keysym.sym, 0);
    }
    else if (evt->type == SDL_TEXTINPUT) {
        nk_input_text(nk_sdl_get_context(), evt->text.text, 1);
    }
    else if (evt->type == SDL_MOUSEWHEEL) {
        nk_input_scroll(nk_sdl_get_context(), nk_vec2(0, evt->wheel.y));
    }
}

// Function to render Nuklear UI with SDL2
void nk_sdl_render(int max_vertex_buffer, int max_element_buffer) {
    // Render to the screen
    nk_clear(nk_sdl_get_context());
    // Render GUI here as per your drawing calls...
}

// Function to shut down Nuklear and free resources
void nk_sdl_shutdown(void) {
    nk_free(nk_sdl_get_context());
    free(nk_sdl_get_context());
}
