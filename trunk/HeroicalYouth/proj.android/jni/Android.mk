LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/GameMenu.cpp \
                   ../../Classes/LoadingScene.cpp \
                   ../../Classes/LevelInfo.cpp \
                   ../../Classes/LevelSelect.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/Bullet.cpp \
                   ../../Classes/Enemy.cpp \
                   ../../Classes/Explode.cpp \
                   ../../Classes/GameOver.cpp \
                   ../../Classes/MyPoint.cpp \
                   ../../Classes/TD.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)
