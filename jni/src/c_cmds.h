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

#if !defined(__C_CMDS__)
#define __C_CMDS__

#include "doomtype.h"

typedef enum
{
    keyboard = 1,
    mouse    = 2,
    gamepad  = 3,
    invalid  = 4
} controltype_t;

typedef struct
{
    char                *control;
    controltype_t       type;
    int                 value;
} control_t;

typedef struct
{
    char                *action;
    void                *keyboard;
    void                *mouse;
    void                *gamepad;
} action_t;

typedef enum
{
    CT_CMD   = 1,
    CT_CVAR  = 2,
    CT_CHEAT = 3
} cmdtype_t;

typedef enum
{
    CF_NONE            =   0,
    CF_BOOLEAN         =   1,
    CF_FLOAT           =   2,
    CF_INTEGER         =   4,
    CF_PERCENT         =   8,
    CF_POSITION        =  16,
    CF_READONLY        =  32,
    CF_SIZE            =  64,
    CF_STRING          = 128,
    CF_TIME            = 256,
} cmdflags_t;

typedef struct
{
    char                *name;
    dboolean            (*func1)(char *cmd, char *parm1, char *parm2, char *parm3);
    void                (*func2)(char *cmd, char *parm1, char *parm2, char *parm3);
    int                 parameters;
    cmdtype_t           type;
    cmdflags_t          flags;
    void                *variable;
    int                 aliases;
    int                 minimumvalue;
    int                 maximumvalue;
    int                 defaultvalue;
    char                *format;
    char                *description;
} consolecmd_t;

extern action_t         actions[];
extern control_t        controls[];
extern consolecmd_t     consolecmds[];
extern int              numconsolecmds;

#endif
