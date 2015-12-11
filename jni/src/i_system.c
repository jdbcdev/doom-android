/*
========================================================================

                               DOOM Retro
         The classic, refined DOOM source port. For Windows PC.

========================================================================

  Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company.
  Copyright (C) 2013-2015 Brad Harding.

  DOOM Retro is a fork of Chocolate DOOM by Simon Howard.
  For a complete list of credits, see the accompanying AUTHORS file.

  This file is part of DOOM Retro.

  DOOM Retro is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation, either version 3 of the License, or (at your
  option) any later version.

  DOOM Retro is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with DOOM Retro. If not, see <http://www.gnu.org/licenses/>.

  DOOM is a registered trademark of id Software LLC, a ZeniMax Media
  company, in the US and/or other countries and is used without
  permission. All other trademarks are the property of their respective
  holders. DOOM Retro is in no way affiliated with nor endorsed by
  id Software LLC.

========================================================================
*/

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void I_ShutdownWindows32(void);
#else
#include <unistd.h>
#endif

#include "c_console.h"
#include "d_loop.h"
#include "doomdef.h"
#include "doomstat.h"
#include "g_game.h"
#include "i_gamepad.h"
#include "i_timer.h"
#include "i_video.h"
#include "m_argv.h"
#include "m_config.h"
#include "m_misc.h"
#include "s_sound.h"
#include "SDL.h"
#include "version.h"
#include "w_merge.h"
#include "w_wad.h"
#include "z_zone.h"

extern dboolean vid_widescreen;
extern dboolean r_hud;
extern dboolean returntowidescreen;

#if defined(WIN32)
typedef long(__stdcall *PRTLGETVERSION)(PRTL_OSVERSIONINFOEXW);
typedef BOOL(WINAPI *PGETPRODUCTINFO)(DWORD, DWORD, DWORD, DWORD, PDWORD);
typedef BOOL(WINAPI *PISWOW64PROCESS)(HANDLE, PBOOL);

#define PRODUCT_PROFESSIONAL    0x00000030
#define PRODUCT_CORE            0x00000065

#endif

//
// I_Quit
//
void I_Quit(dboolean shutdown)
{
    if (shutdown)
    {
        S_Shutdown();

        if (returntowidescreen)
            vid_widescreen = true;

        M_SaveCVARs();

        I_ShutdownGraphics();

        I_ShutdownKeyboard();

        I_ShutdownGamepad();

        I_ShutdownVirtualpad();
    }

#if defined(WIN32)
    I_ShutdownWindows32();
#endif

    SDL_Quit();

    exit(0);
}

void I_WaitVBL(int count)
{
    I_Sleep((count * 1000) / 70);
}

//
// I_Error
//
static dboolean already_quitting;

void I_Error(char *error, ...)
{
    va_list     argptr;
    char        msgbuf[512];

    if (already_quitting)
        exit(-1);
    else
        already_quitting = true;

    // Shutdown. Here might be other errors.
    S_Shutdown();

    if (returntowidescreen)
        vid_widescreen = true;

    M_SaveCVARs();

    I_ShutdownGraphics();

    I_ShutdownKeyboard();

    I_ShutdownGamepad();

#if defined(WIN32)
    I_ShutdownWindows32();
#endif

    va_start(argptr, error);
    vfprintf(stderr, error, argptr);
    fprintf(stderr, "\n\n");
    va_end(argptr);
    fflush(stderr);

    va_start(argptr, error);
    memset(msgbuf, 0, sizeof(msgbuf));
    M_vsnprintf(msgbuf, sizeof(msgbuf) - 1, error, argptr);
    va_end(argptr);

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, PACKAGE_NAME, msgbuf, NULL);

    SDL_Quit();

    exit(-1);
}
