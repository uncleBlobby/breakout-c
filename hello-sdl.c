#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BRICK_WIDTH = 48;
const int BRICK_HEIGHT = 20;

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
int initBricks();
void movePaddle();
void stopPaddle();
void updatePaddleState();
void startBall();
void updateBallState();
void checkBallBrickCollisions();
void initBoard();
void drawPaddle();
void drawBall();
void drawLiveBricks();

int main(int argc, char* args[]) {
    Game game;
    Game* game_ptr = &game;
    if (initBricks(game_ptr) != 0) {
        printf("Error initializing bricks\n");
        return 1;
    }
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
    if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)) {
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
    } else {
        window = SDL_CreateWindow( "breakout.c", 500, 500, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL ){
            printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
        } else {
            while (!quit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)){
                    if( event.type == SDL_QUIT){
                        quit = true;
                        SDL_Log("Program exited.");
                        break;
                    }
                    if( event.type == SDL_KEYDOWN ){
                        movePaddle(paddle_ptr, event.key.keysym.sym);
                        startBall(ball_ptr, event.key.keysym.sym);
                    }
                    if( event.type == SDL_KEYUP ){
                        stopPaddle(paddle_ptr);
                    } 
                }
            updatePaddleState(paddle_ptr);
            updateBallState(ball_ptr, paddle);
            checkBallBrickCollisions(ball_ptr, game_ptr->bricks);
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 0, 0));
            drawLiveBricks(screenSurface, window, game);
            drawPaddle(screenSurface, window, game_ptr, paddle);
            drawBall(screenSurface, window, game_ptr, ball);
            SDL_UpdateWindowSurface(window);
            }
        }
    }
    SDL_DestroyWindow(window);
    printf("SDL initialized.\n");
    printf("Quitting SDL.\n");
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

int initBricks(Game* game) {
    if (game){
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 10; j++) {
                game->bricks[i][j].rect.x = 1 + (i * (BRICK_WIDTH + 2));
                game->bricks[i][j].rect.y = 1 + (j * (BRICK_HEIGHT + 2));
                game->bricks[i][j].rect.w = BRICK_WIDTH;
                game->bricks[i][j].rect.h = BRICK_HEIGHT;
                game->bricks[i][j].is_alive = true;
            }
        }
        return 0;
    } else {
        printf("Error: game is null.\n");
        return 1;
    }
}

void movePaddle(Paddle* paddle, SDL_KeyCode key) {
    if (paddle){
        if (key == SDLK_a){
            paddle->velocity.x = -1;
        }
        if (key == SDLK_d){
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

void startBall(Ball* ball, SDL_KeyCode key) {
    if (ball){
        if (key == SDLK_SPACE){
            if (ball->velocity.x == 0 && ball->velocity.y == 0){
                ball->velocity.x = 1;
                ball->velocity.y = 1;
            }
        } 
    }
}

void updateBallState(Ball* ball, Paddle paddle) {
    if (ball){
        if (SDL_GetTicks() % 2 == 0) {
            if (ball->position.x <= 0 || ball->position.x >= SCREEN_WIDTH - ball->width) {
                ball->velocity.x *= -1;
            }
            if (ball->position.y <= 0 || ball->position.y >= SCREEN_HEIGHT - ball->height) {
                ball->velocity.y *= -1;
            }
            if (ball->position.y == (paddle.position.y)) {
                if ((ball->position.x >= paddle.position.x) && (ball->position.x <= paddle.position.x + paddle.width)) {
                    ball->velocity.y *= -1;
                }
            }     
            ball->position.x += ball->velocity.x;
            ball->position.y += ball->velocity.y;
            ball->rect.x = ball->position.x;
            ball->rect.y = ball->position.y;
        }
    }
}

void checkBallBrickCollisions(Ball* ball, Brick* bricks) {
    int numBricks = 160;
    if (ball){
        for (int i = 0; i < numBricks; i++) {
            if (SDL_HasIntersection(&ball->rect, &bricks[i].rect) && bricks[i].is_alive) {
                ball->position.y += 2;
                ball->velocity.y *= -1;
                bricks[i].is_alive = false;
            }
        }
    }
}

void initBoard(SDL_Surface* screen, SDL_Window* window, Game* game) {
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
}

void drawLiveBricks(SDL_Surface* screen, SDL_Window* window, Game game) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 10; j++){
            if (game.bricks[i][j].is_alive) {
                SDL_FillRect(screen, &game.bricks[i][j].rect, SDL_MapRGB( screen->format, 255, 0, 0));
            }
        }
    }
}

void drawPaddle(SDL_Surface* screen, SDL_Window* window, Game* game, Paddle paddle) {
    SDL_FillRect(screen, &paddle.rect, SDL_MapRGB( screen->format, 0, 255, 0));
}

void drawBall(SDL_Surface* screen, SDL_Window* window, Game* game, Ball ball) {
    SDL_FillRect(screen, &ball.rect, SDL_MapRGB( screen->format, 255, 255, 255));
}
