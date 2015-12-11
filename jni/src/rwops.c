#include "rwops.h"
#include <stddef.h>
#include <stdarg.h>

// feof equivalent for SDL_rwops
int rweof(SDL_RWops *ctx) {
    return SDL_RWsize(ctx) == SDL_RWtell(ctx);
}

// fgetc equivalent for SDL_rwops
int rwgetc(SDL_RWops *rw) {
    char c;

    return SDL_RWread(rw, &c, 1, 1) == 1 ? c : EOF;
}

// fgets equivalent for SDL_rwops
char *rwgets(char *buf, int count, SDL_RWops *rw) {

    Sint64 base = SDL_RWtell(rw);
    SDL_RWread(rw, buf, count, 1);

    char *end = strchr(buf, '\n');
    ptrdiff_t offs =  end - buf;

    if (offs != 0) {
        SDL_RWseek(rw, base + offs + 1, RW_SEEK_SET);
        *end = '\0';
    }

    return buf;
}

// fprinf equivalent for SDL_RWops
int rwprintf(SDL_RWops *ctx, const char *format, ...) {

    //char buffer[255];
    va_list args;
    va_start(args, format);
    while( *format != '\0' ) {
      char *buffer = va_arg( args, char * );
      sprintf(buffer, format, args);
      size_t len = SDL_strlen(buffer);
      SDL_RWwrite(ctx, buffer, 1, len);
      *format++;
    }
    //sprintf(str, "%s", format);
    /*sprintf(buffer, format, args);
    size_t len = SDL_strlen(buffer);
    SDL_RWwrite(ctx, buffer, 1, len);*/
    va_end(args);
}
