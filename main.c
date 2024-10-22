#define NK_IMPLEMENTATION
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_SDL_GL3_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "nuklear.h"
#include "nuklear_sdl.h"

#define ADD 1
#define MULT 2

// Function prototypes
double arithGame(int max, int quantity, int op);
int numPoints(double timesec);
void drawUI(struct nk_context *ctx, int *score, double *avgTime);

int SDL_main(void) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Create a window
    SDL_Window *win = SDL_CreateWindow("Arithmetic Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 300, SDL_WINDOW_SHOWN);
    if (!win) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return -1;
    }

    // Initialize Nuklear
    struct nk_context *ctx = nk_sdl_init(renderer);
    struct nk_color background = nk_rgb(28, 48, 62);

    // Seed the random number generator
    srand(time(0));

    int score = 0;
    double avgTime = 0;

    // Main loop
    int running = 1;
    while (running) {
        SDL_Event evt;
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) {
                running = 0;
            }
            nk_sdl_handle_event(&evt);
        }

        // Start a new frame
        nk_sdl_new_frame();

        // Draw the UI
        drawUI(ctx, &score, &avgTime);

        // Render
        SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, 255);
        SDL_RenderClear(renderer);
        nk_sdl_render(NK_ANTI_ALIASING_ON);
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    nk_sdl_shutdown();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

double arithGame(int max, int quantity, int op) {
    int correctAnswers = 0;
    double totalTimeSpent = 0.0;

    for (int i = 0; i < quantity; i++) {
        int num1 = rand() % max + 1; // Generate random number between 1 and max
        int num2 = rand() % max + 1; // Generate random number between 1 and max
        int correctAnswer = (op == ADD) ? (num1 + num2) : (num1 * num2);
        int userAnswer;

        // Start timing
        time_t startTime = time(0);

        // Create question prompt
        char prompt[100];
        snprintf(prompt, sizeof(prompt), "Question %d: %d %s %d = ?", i + 1, num1, (op == ADD) ? "+" : "*", num2);

        // Wait for user input (simulated in the UI)
        printf("%s\n", prompt); // For console output, this is just for initial testing

        // User answers via UI, we will simulate correct answer check
        // Simulated user input; replace with actual UI input in production
        scanf("%d", &userAnswer);

        // End timing
        time_t endTime = time(0);

        // Calculate time spent
        double timeSpent = difftime(endTime, startTime);
        totalTimeSpent += timeSpent;

        if (userAnswer == correctAnswer) {
            printf("Correct!\n");
            correctAnswers++;
        } else {
            printf("Incorrect. The correct answer is %d.\n", correctAnswer);
            totalTimeSpent += 1.0; // Penalty for incorrect answer
        }
    }

    // Calculate average time per question
    double averageTime = totalTimeSpent / quantity;
    return averageTime;
}

int numPoints(double timesec) {
    if (timesec < 1) return 10;
    else if (timesec < 2) return 9;
    else if (timesec < 3) return 8;
    else if (timesec < 4) return 7;
    else if (timesec < 5) return 6;
    else if (timesec < 6) return 5;
    else if (timesec < 7) return 4;
    else if (timesec < 8) return 3;
    else if (timesec < 9) return 2;
    else if (timesec < 10) return 1;
    return 0;
}

void drawUI(struct nk_context *ctx, int *score, double *avgTime) {
    if (nk_begin(ctx, "Arithmetic Game", nk_rect(50, 50, 300, 200), NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
        nk_layout_row_dynamic(ctx, 30, 1);
        nk_label(ctx, "Welcome to the Arithmetic Game!", NK_TEXT_ALIGN_CENTERED);

        nk_layout_row_dynamic(ctx, 30, 1);
        if (nk_button_label(ctx, "Play Arithmetic Game")) {
            int max = 10; // Maximum operand value
            int quantity = 5; // Number of questions
            int op = ADD; // Operation type (1 for addition)
            *avgTime = arithGame(max, quantity, op);
            *score += numPoints(*avgTime);
        }

        nk_layout_row_dynamic(ctx, 30, 1);
        char scoreText[50];
        snprintf(scoreText, sizeof(scoreText), "Total Score: %d", *score);
        nk_label(ctx, scoreText, NK_TEXT_ALIGN_CENTERED);

        nk_layout_row_dynamic(ctx, 30, 1);
        if (nk_button_label(ctx, "Quit")) {
            exit(0);
        }
    }
    nk_end(ctx);
}
