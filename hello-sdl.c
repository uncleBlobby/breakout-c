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
    int x;
    int y;
} Velocity;

typedef struct {
    SDL_Rect rect;
    bool is_alive;
} Brick;

typedef struct {
    SDL_Rect rect;
    Velocity velocity;
    Position position;
    int height;
    int width;
} Ball;

typedef struct {
    SDL_Rect rect;
    Velocity velocity;
    Position position;
    int height;
    int width;
} Paddle;

typedef struct {
    Brick bricks[16][10];
    Ball ball;
    Paddle paddle;
} Game;

int initPaddle();
int initBall();

void movePaddle();
void stopPaddle();
void updatePaddleState();

void drawBoard();
void drawPaddle();
void drawBall();

int main(int argc, char* args[]) {

    Game game;
    Game* game_ptr = &game;

    Paddle paddle;
    Paddle* paddle_ptr = &paddle;

    if (initPaddle(paddle_ptr) != 0) {
        printf("Error: could not initialize paddle.\n");
        return 1;
    }

    Ball ball;
    Ball* ball_ptr = &ball;

    if (initBall(ball_ptr) != 0) {
        printf("Error: could not initialize ball.\n");
        return 1;
    }

    bool quit = false;

    SDL_Window* window = NULL;

    SDL_Surface* screenSurface = NULL;

    SDL_Log("Initializing SDL.\n");

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

                    if( event.type == SDL_KEYDOWN ){
                        movePaddle(paddle_ptr, event.key.keysym.sym);
                    }
                    if( event.type == SDL_KEYUP ){
                        stopPaddle(paddle_ptr);
                    } 
                }

            // update game state, draw the current frame
            // update game state
            // -- test: move paddle right
            
            updatePaddleState(paddle_ptr);
            
            
            // draw current frame
            // 1. grab the screen surface and paint it black
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 0, 0));
            
            // 2. draw the board
            drawBoard(screenSurface, window, game_ptr);
            // 3. draw the paddle
            drawPaddle(screenSurface, window, game_ptr, paddle);
            // 4. draw the ball
            drawBall(screenSurface, window, game_ptr, ball);
            // 5. update the screen
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

int initPaddle(Paddle* paddle) {
    if (paddle){
        paddle->position.x = 350;
        paddle->position.y = 550;
        paddle->width = 100;
        paddle->height = 20;
        paddle->velocity.x = 0;
        paddle->velocity.y = 0;
        paddle->rect.x = paddle->position.x;
        paddle->rect.y = paddle->position.y;
        paddle->rect.w = paddle->width;
        paddle->rect.h = paddle->height;
        return 0;
    } else {
        printf("Error: paddle is null.\n");
        return 1;
    }
}

int initBall(Ball* ball) {
    if (ball){
        ball->position.x = 395;
        ball->position.y = 295;
        ball->width = 10;
        ball->height = 10;
        ball->velocity.x = 0;
        ball->velocity.y = 0;
        ball->rect.x = ball->position.x;
        ball->rect.y = ball->position.y;
        ball->rect.w = ball->width;
        ball->rect.h = ball->height;
        return 0;
    } else {
        printf("Error: ball is null.\n");
        return 1;
    }
}

void movePaddle(Paddle* paddle, SDL_KeyCode key) {
    if (paddle){
        if (key == SDLK_a){
            printf("Pressing a.\n");
            paddle->velocity.x = -1;
        }
        if (key == SDLK_d){
            printf("Pressing d.\n");
            paddle->velocity.x = 1;
        }
    }
}

void stopPaddle(Paddle* paddle) {
    if (paddle){
        paddle->velocity.x = 0;
    }
}

void updatePaddleState(Paddle* paddle) {
    if (paddle){
        paddle->position.x += paddle->velocity.x;
        paddle->rect.x = paddle->position.x;
        paddle->rect.y = paddle->position.y;
    }
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

void drawPaddle(SDL_Surface* screen, SDL_Window* window, Game* game, Paddle paddle) {
    //game->paddle = paddle;
    SDL_FillRect(screen, &paddle.rect, SDL_MapRGB( screen->format, 0, 255, 0));
    //SDL_UpdateWindowSurface(window);
}

void drawBall(SDL_Surface* screen, SDL_Window* window, Game* game, Ball ball) {
    //game->ball = ball;
    SDL_FillRect(screen, &ball.rect, SDL_MapRGB( screen->format, 255, 255, 255));
    //SDL_UpdateWindowSurface(window);
}