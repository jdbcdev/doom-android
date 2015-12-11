#include "SDL.h"

// feof equivalent for SDL_RWops
int rweof(SDL_RWops *ctx);

// fgetc equivalent for SDL_RWops
int rwgetc(SDL_RWops *rw);

// fgets equivalent for SDL_RWops
char *rwgets(char *buf, int count, SDL_RWops *rw);

// fprinf equivalent for SDL_RWops
rwprintf(SDL_RWops *ctx, const char *format,...);
