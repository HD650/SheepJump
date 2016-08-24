LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
					 ../../Classes/gamelayer.cpp \
					   ../../Classes/gamescene.cpp \
					    ../../Classes/MagicBook.cpp \
						 ../../Classes/monster.cpp \
						  ../../Classes/sheep.cpp \
						   ../../Classes/sheeplayer.cpp \
						   ../../Classes/bride.cpp \
						     ../../Classes/techscene.cpp \
							   ../../Classes/techsheeplayer.cpp \
							      ../../Classes/mainmenu.cpp \
								   ../../Classes/configscene.cpp \
						    ../../Classes/wolf.cpp
							 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)
