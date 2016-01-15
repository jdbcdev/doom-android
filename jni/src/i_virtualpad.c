#include "i_virtualpad.h"
#include "doomdef.h"

// Fire and use buttons
SDL_Texture *buttonfire;
SDL_Rect rectfire;
SDL_Texture *buttonuse;
SDL_Rect rectuse;

//Weapon selected
SDL_Rect rectweapon[7];
SDL_Texture *imgWeapon[7];

static SDL_Texture* LoadTextureFromBMP(const char *filename) {
    // Load image as SDL_Surface
    SDL_Surface* surface = SDL_LoadBMP(filename);
    if ( surface == NULL )
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Texture file %s not found", filename);
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
    SDL_FreeSurface( surface );

    return texture;
}

static SDL_Texture* LoadTextureFromPNG(const char *filename) {
    // Load image as SDL_Surface
    SDL_Surface* surface = IMG_Load(filename);
    if ( surface == NULL )
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Texture file %s not found", filename);
        return NULL;
    } else {
        SDL_Log("Texture %s loaded", filename);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
    SDL_FreeSurface( surface );

    return texture;
}

static void DrawButtons() {
    const int size = (64 * displayheight) / SCREENHEIGHT;
    int posx = (550 * displaywidth) / SCREENWIDTH;
    int firey = (140 * displayheight) / SCREENHEIGHT;
    int usey = (60 * displayheight) / SCREENHEIGHT;
    //Fire button
    rectfire.x = posx;
    rectfire.y = firey;
    rectfire.w = size;
    rectfire.h = size;

    //Use button
    rectuse.x = posx;
    rectuse.y = usey;
    rectuse.w = size;
    rectuse.h = size;
#if defined(ANDROID)
  buttonfire = LoadTextureFromPNG("circle_grey.png");
  buttonuse = LoadTextureFromPNG("circle_blue.png");
#else
  buttonfire = LoadTextureFromPNG("../assets/circle_grey.png");
  buttonuse = LoadTextureFromPNG("../assets/circle_blue.png");
#endif
}

static void DrawWeapons() {
    const int size = (40 * displayheight) / SCREENHEIGHT;
    int i;
    for(i=0;i <= 6; i++) {
        rectweapon[i].x = 10 * (i+1) + i * size;
        rectweapon[i].y = 20;
        rectweapon[i].w = size;
        rectweapon[i].h = size;
#if defined(ANDROID)
        char filename[12];
        sprintf(filename, "number%d.png", i + 1);
        SDL_Log("DrawWeapons filename: %s", filename);
        imgWeapon[i] = LoadTextureFromPNG(filename);
#else
        char filename[12];
        sprintf(filename, "../assets/number%d.png", i + 1);
        imgWeapon[i] = LoadTextureFromPNG(filename);
#endif
    }
}

void I_InitVirtualpad() {
    SDL_Log("I_InitVirtualpad");
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(IMG_INIT_PNG) & imgFlags)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return;
    }

    DrawButtons();
    DrawWeapons();
}

void I_ShutdownVirtualpad() {
    SDL_DestroyTexture(buttonfire);
    SDL_DestroyTexture(buttonuse);
    IMG_Quit();
}

void I_RenderVirtualpad() {
    SDL_RenderCopy(renderer, buttonfire, NULL, &rectfire);
    SDL_RenderCopy(renderer, buttonuse, NULL, &rectuse);
    int i = 0;
    for(i=0; i <=6; i++) {
        SDL_Rect rect = rectweapon[i];
        SDL_RenderCopy(renderer, imgWeapon[i], NULL, &rect);
    }
}

dboolean I_ButtonUseTouched(const float x, const float y) {
    return (x > (float)rectuse.x && x < (float) (rectuse.x + rectuse.w)
        && y > (float)rectuse.y && y < (float) (rectuse.y + rectuse.h));
}

dboolean I_ButtonFireTouched(const float x, const float y) {
    return (x > (float)rectfire.x && x < (float)(rectfire.x + rectfire.w)
            && y > (float)rectfire.y && y < (float)(rectfire.y + rectfire.h));
}

int I_WeaponSelected(const float x, const float y) {
    const int size = (40 * displayheight) / SCREENHEIGHT;
    int i;
    int weapon = -1;
    for(i=0; i <= 6; i++) {
        int startx = 10 * (i+1) + i * size;
        int endx = startx + size;
        if (x >= (float)startx && x <= (float)endx
            && y > 10 && y < 10 + size) {
            SDL_Log("I_WeaponSelected weapon: %d", i);
            weapon = i;
            break;
        }
    }

    return weapon;
}
