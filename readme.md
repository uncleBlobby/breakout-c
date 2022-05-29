# BREAKOUT.C
***

Quick implementation of classic ["Breakout" style brick-breaking game, developed in 1976 by Atari](https://en.wikipedia.org/wiki/Breakout_(video_game)), using [C language](https://en.wikipedia.org/wiki/C_(programming_language)) and [SDL2](https://www.libsdl.org/).  Intended as a project to help develop further understanding of rudimentary C syntax and the SDL2 library for rendering simple graphics to the screen. This implementation uses [GNU Make 4.3](https://www.gnu.org/software/make/) and [GCC 12.1.1](https://gcc.gnu.org/).

The current project is about 280 lines of code and produces an executable 26 KB in size.

***
## Dependencies

- MAKE
- SDL2 development library
- GCC 

***
## Installation


### Linux

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

***
## Controls

```
[spacebar]  - initialize ball
a           - move paddle left
d           - move paddle right
```

***
## Changelog

### 2022-05-29

Added readme file.

Added detailed todos.

Completed paddle restraints (clamped paddle to screen width so player can no longer move paddle off-screen).

Began work on "extra lives" mechanic.

Began work on "score" mechanic.

***
### 2022-05-28

Finished MVP.  

BREAKOUT.C now features collisions (with paddle, with bricks) and bricks are successfully removed from the screen as they are collided.  Paddle movement is working, but not yet constrained to the boundaries of the screen.  Ball movement is satisfactory, however have not yet implemented a "loss" mechanic when the paddle actually misses the ball -- currently, ball will simply bounce off the bottom of the screen as it would any other wall.  

***
## Todos:

- [x] Restrain paddle movement to window bounds.  Player should not be able to move the paddle off the screen!
- [ ] Introduce "lives" / "extra balls" mechanic: player ought to start with a limited number of attempts (ie: 3) and lose one every time the ball is missed by the paddle and travels through the southern wall.
    - [x] Display extra lives in bottom left corner of screen.
    - [x] Add lives field to game struct.
    - [ ] Remove life on ball exit screen south.
    - [ ] Introduce mechanic to respawn ball after loss of life -- after player has lost a ball, using spacebar should restart the game.
- [ ] Introduce sound effect mechanics: ball hit paddle, ball hit wall, player loses ball, ball hit brick all may have different types of 'blip' sound effect.
    - [x] Add "beep.wav" sound effect for future use.
- [ ] Introduce score keeping mechanic: each successful brick destroyed ought to increase a score counter -- perhaps a multiplier for extra bricks destroyed before the ball returns to the paddle (score multiplier resets every time the ball hits the paddle).
    - [x] Add score field to game struct.
    - [x] Increment score (+ 10 points) for every brick destroyed.
    - [ ] Introduce multiplier for more bricks broken between each paddle hit (combo scoring).
    - [ ] Learn how to render fonts and draw score to screen (bottom right?).
- [ ] Change paddle rebound mechanics: treat paddle as if it were slightly curved (upward in the center) in order to further diversify the core rebound mechanic.  Currently the velocity changes in a very predictable way, and only certain angles of return are available to the player.  ie: no matter which part of the paddle the ball bounces from, the velocity currently changes in the exact same manner -- making the gameplay very predictable and boring.
- [ ] Multiple Brick Colors: original breakout had bricks ranging from yellow (lowest bricks) to green, to orange, to red (highest bricks near top of screen), each different color of bricks was worth more points.
- [ ] Increase Ball Speed ???: original breakout increased ball speed after a certain number of hits, and after breaking through different layers of the wall.
- [ ] Powerups ???: later versions of breakout had powerups which would "drop" to the player on the destruction of random bricks.  Some powerups included: multiple balls, increased paddle width, sticky paddle, and so on.

***
