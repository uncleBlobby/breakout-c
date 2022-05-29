# BREAKOUT.C

Quick implementation of classic "Breakout" style brick-breaking game using C language and SDL.  Intended as a project to help develop further understanding of rudimentary C syntax and the SDL2 library for rendering simple graphics to the screen.

The current project is about 280 lines of code and produces an executable 26 KB in size.

## Dependencies

- MAKE
- SDL2 development library
- GCC 

## Installation

When all dependencies are installed, simply run:

```bash
make
```
Then run:

```bash
./hello-sdl
```

If you do not wish to install make, simply compile the executable with the following command (GCC and SDL2 are still required):

```bash
gcc hello-sdl.c -lSDL2 -o hello-sdl
```

or for more verbose error logging:

```bash
gcc hello-sdl.c -Wall -Werror -lSDL2 -o hello-sdl
```

## Controls

```
[spacebar]  - initialize ball
a           - move paddle left
d           - move paddle right
```

## Changelog

2022-05-29

Added readme file.

2022-05-28

Finished MVP.  BREAKOUT.C now features collisions (with paddle, with bricks) and bricks are successfully removed from the screen as they are collided.  Paddle movement is working, but not yet constrained to the boundaries of the screen.  Ball movement is satisfactory, however have not yet implemented a "loss" mechanic when the paddle actually misses the ball -- currently, ball will simply bounce off the bottom of the screen as it would any other wall.  

## Todos:

- Introduce "lives" / "extra balls" mechanic: player ought to start with a limited number of attempts (ie: 3) and lose one every time the ball is missed by the paddle and travels through the southern wall.
- Introduce "restart" mechanic: after play has lost a ball to the southern wall, using spacebar should restart the game (as it does in the first initialization).
- Introduce sound effect mechanics: ball hit paddle, ball hit wall, player loses ball, ball hit brick all may have different types of 'blip' sound effect.
- Introduce score keeping mechanic: each successful brick destroyed ought to increase a score counter -- perhaps a multiplier for extra bricks destroyed before the ball returns to the paddle (score multiplier resets every time the ball hits the paddle).
- Change paddle rebound mechanics: treat paddle as if it were slightly curved (upward in the center) in order to further diversify the core rebound mechanic.  Currently the velocity changes in a very predictable way, and only certain angles of return are available to the player.  ie: no matter which part of the paddle the ball bounces from, the velocity currently changes in the exact same manner -- making the gameplay very predictable and boring.  