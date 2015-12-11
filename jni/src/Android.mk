LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_CFLAGS := -w
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include

# Add your application source files here...
FILE_LIST := $(wildcard $(LOCAL_PATH)/*.c)
DOOMRETRO_FOLDER := /doomretro
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	$(FILE_LIST:$(LOCAL_PATH)/%=%)
	#SDL.cpp Tetris.cpp TetrisSDL.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_mixer SDL2_image

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog -lm -landroid

include $(BUILD_SHARED_LIBRARY)
