LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

$(call import-add-path, $(LOCAL_PATH)/../../cocos2d)
$(call import-add-path, $(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path, $(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path, $(LOCAL_PATH)/../../cocos2d/cocos/ui)
$(call import-add-path, $(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := shared
LOCAL_MODULE_FILENAME := libhalfo

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../source

HALFO_PATH := $(LOCAL_PATH)/../../source
CRYPTO_PATH := $(LOCAL_PATH)/../../crypto
SOURCE_FILES := main.cpp
SOURCE_FILES += $(wildcard $(HALFO_PATH)/*.cpp)
SOURCE_FILES += $(wildcard $(HALFO_PATH)/**/*.cpp)
SOURCE_FILES += $(wildcard $(HALFO_PATH)/**/**/*.cpp)
SOURCE_FILES += $(CRYPTO_PATH)/aes_modes.c $(CRYPTO_PATH)/aes_ni.c $(CRYPTO_PATH)/aescrypt.c $(CRYPTO_PATH)/aeskey.c $(CRYPTO_PATH)/aestab.c
SOURCE_FILES := $(SOURCE_FILES:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES := $(SOURCE_FILES)

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += cocos_extension_static
LOCAL_STATIC_LIBRARIES += cocos_ui_static
LOCAL_STATIC_LIBRARIES += cocos_external_static

include $(BUILD_SHARED_LIBRARY)
$(call import-module, extensions)
$(call import-module, audio/android)
$(call import-module, ui)
$(call import-module, .)
