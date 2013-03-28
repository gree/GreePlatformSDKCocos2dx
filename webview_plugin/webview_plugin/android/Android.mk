LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_webview_plugin_static

LOCAL_MODULE_FILENAME := libwebview_plugin

LOCAL_SRC_FILES := \
	CCWebView.cpp \
	jni/Java_org_cocos2dx_lib_Cocos2dxWebView.cpp \


LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../cocos2dx \
							$(LOCAL_PATH)/../../cocos2dx/include \
							$(LOCAL_PATH)/../../cocos2dx/platform/android \
							$(LOCAL_PATH)/../include \
							$(LOCAL_PATH)/ \
							$(LOCAL_PATH)/jni
                    
include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx)
