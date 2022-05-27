#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int BRICK_WIDTH = 48;
const int BRICK_HEIGHT = 20;

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    SDL_Rect rect;
    bool is_alive;
} Brick;

typedef struct {
    SDL_Rect rect;
    int x_velocity;
    int y_velocity;
    Position position;
} Ball;

typedef struct {
    SDL_Rect rect;
    int x_velocity;
    int y_velocity;
    Position position;
} Paddle;

typedef struct {
    Brick bricks[16][10];
    Ball ball;
    Paddle paddle;
} Game;




void drawBoard();
void drawPaddle();
void drawBall();

int main(int argc, char* args[]) {

    Game game;
    Game* game_ptr = &game;

    bool quit = false;

    SDL_Window* window = NULL;

    SDL_Surface* screenSurface = NULL;

    printf("Initializing SDL.\n");

    /* Initialize defaults, Video and Audio */
    if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)) {
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
    } else {
        // Create Window
        window = SDL_CreateWindow( "Hello SDL", 500, 500, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL ){
            printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
        } else {
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)){
                    // decide what to do with the current event
                    if( event.type == SDL_QUIT){
                        quit = true;
                        SDL_Log("Program exited.");
                        break;
                    }
                }

                // update game state, draw the current frame
            screenSurface = SDL_GetWindowSurface(window);

            SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 0, 0));
            

            drawBoard(screenSurface, window, game_ptr);
            drawPaddle(screenSurface, window, game_ptr);
            drawBall(screenSurface, window, game_ptr);
            //SDL_Delay(2000);
            SDL_UpdateWindowSurface(window);

            }

        }
    }

    SDL_DestroyWindow(window);

    printf("SDL initialized.\n");

    printf("Quitting SDL.\n");

    /* Shutdown all subsystems (Video, Audio, etc) */
    SDL_Quit();

    printf("Quitting...\n");

    exit(0);
}

void drawBoard(SDL_Surface* screen, SDL_Window* window, Game* game) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 10; j++){
            Brick newBrick;
            SDL_Rect rect = {x: 1 + (i * (BRICK_WIDTH + 2 )), y: 1 + (j * (BRICK_HEIGHT + 2)), w: BRICK_WIDTH, h: BRICK_HEIGHT};
            newBrick.rect = rect;
            newBrick.is_alive = true;
            game->bricks[i][j] = newBrick;
            SDL_FillRect(screen, &rect, SDL_MapRGB( screen->format, 255, 0, 0));
        }
    }
    //SDL_UpdateWindowSurface(window);
}

void drawPaddle(SDL_Surface* screen, SDL_Window* window, Game* game) {
    SDL_Rect rect = {x: 350, y: 550, w: 100, h: 20};
    Paddle paddle = {rect: rect, x_velocity: 0, y_velocity: 0};
    game->paddle = paddle;
    SDL_FillRect(screen, &rect, SDL_MapRGB( screen->format, 0, 255, 0));
    //SDL_UpdateWindowSurface(window);
}

void drawBall(SDL_Surface* screen, SDL_Window* window, Game* game) {
    SDL_Rect rect = {x: 395, y: 295, w: 10, h: 10};
    Ball ball = {rect: rect, x_velocity: 0, y_velocity: 0};
    game->ball = ball;
    SDL_FillRect(screen, &rect, SDL_MapRGB( screen->format, 255, 255, 255));
    //SDL_UpdateWindowSurface(window);
}