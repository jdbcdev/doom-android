#include "doomtype.h"
#include "SDL.h"
#include "SDL_image.h"

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern int displaywidth;
extern int displayheight;

void I_InitVirtualpad();
void I_ShutdownVirtualpad();
void I_RenderVirtualpad();
dboolean I_ButtonUseTouched(const float x, const float y);
dboolean I_ButtonFireTouched(const float x, const float y);
int I_WeaponSelected(const float x, const float y);
