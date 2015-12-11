#!/bin/sh

#mkdir obj
#cd obj

#gcc -w -lm -o doomretro src/*.c -I/usr/local/include/SDL2 -D_REENTRANT -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lSDL2 -lSDL2_mixer -lm
gcc -w -g -o doomretro src/*.c `sdl2-config --cflags --libs` -lSDL2_mixer -lSDL2_image -lm
#gcc -w -lm -o doomretro src/*.c -I/usr/local/include/SDL2 -D_REENTRANT -Wl,-rpath,/usr/local/lib -L/usr/local/lib -lSDL2_mixer -lSDL2 -lm -lvorbis -logg

#gcc -w -g -o test test.c `sdl2-config --cflags --libs` -lSDL2_mixer -lm
