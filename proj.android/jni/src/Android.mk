LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := main

#SDK_ROOT points to folder with SDL and oxygine-framework
LOCAL_SRC_FILES := ../../../../libs//SDL/src/main/android/SDL_android_main.c

LOCAL_SRC_FILES += ../../../src/Scene.cpp ../../../src/button.cpp ../../../src/editor.cpp ../../../src/example.cpp ../../../src/field.cpp ../../../src/main.cpp ../../../src/menu.cpp ../../../src/modify_data.cpp ../../../src/test.cpp 


LOCAL_STATIC_LIBRARIES := oxygine-framework_static
LOCAL_SHARED_LIBRARIES := SDL2

include $(BUILD_SHARED_LIBRARY)


#import from NDK_MODULE_PATH defined in build.cmd
$(call import-module, oxygine-framework)
