#OBJS specifies which files to compile for the project
OBJS = hello-sdl.c

#CC specifies which compiler to use
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options
# -Wall: enable all warnings
# -Werror: treat warnings as errors
COMPILER_FLAGS = -Wall -Werror

#LINKER_FLAGS specifies the additional linking options (in this case, SDL2)
LINKER_FLAGS = -lSDL2

#OBJ_NAME specifies the name of our executable
OBJ_NAME = hello-sdl

#TARGET compiles the executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)