# A simple Makefile for compiling small SDL projects

# set the compiler
CC := gcc

# set the compiler flags
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lSDL2_ttf -lm

# add header files here
HDRS := main.h Window_and_Renderer.h Floor.h Forest.h Player_Input.h Hero.h Movement.h Window.h Menu.h Hand.h Character.h Words.h header.h
# add source files here
SRCS := main.c Window_and_Renderer.c Floor.c Forest.c Player_Input.c Hero.c Movement.c Window.c Menu.c Hand.c Character.c 

# generate names of object files
OBJS := $(SRCS:.c=.o)

# name of executable
EXEC := game

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) 
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
$(OBJS): $(SRCS)
	$(CC) -c $(CFLAGS) $(@:.o=.c) 

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
