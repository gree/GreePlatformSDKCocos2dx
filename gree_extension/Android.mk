LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_gree_extension_static

LOCAL_MODULE_FILENAME := libgree_extension

LOCAL_SRC_FILES := GreeJniHelper.cpp \
	CCGreeUser.cpp \
	CCGreePlatform.cpp \
 	CCGreeAuthorizer.cpp \
	CCGreeDashboard.cpp \
	CCGreePayment.cpp \
	CCGreeAchievement.cpp \
	CCGreeLeaderboard.cpp \
	CCGreeInviteDialog.cpp \
	CCGreeRequestDialog.cpp \
	CCGreeShareDialog.cpp \
	CCGreeFriendCode.cpp \
	jni/Java_org_cocos2dx_lib_Cocos2dxGreeAuthorizer.cpp \
	jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.cpp \
	jni/Java_org_cocos2dx_lib_Cocos2dxGreeUser.cpp \
	jni/Java_org_cocos2dx_lib_Cocos2dxGreeDashboard.cpp \
	jni/Java_org_cocos2dx_lib_Cocos2dxGreePayment.cpp \
	jni/Java_org_cocos2dx_lib_Cocos2dxGreeAchievement.cpp \
	jni/Java_org_cocos2dx_lib_Cocos2dxGreeLeaderboard.cpp \
	jni/Java_org_cocos2dx_lib_Cocos2dxGreeInviteDialog.cpp \
	jni/Java_org_cocos2dx_lib_Cocos2dxGreeRequestDialog.cpp \
	jni/Java_org_cocos2dx_lib_Cocos2dxGreeShareDialog.cpp \
	jni/Java_org_cocos2dx_lib_Cocos2dxGreeFriendCode.cpp \
	jni/Java_org_cocos2dx_lib_Cocos2dxGreeNativeListener.cpp \



LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
#LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../cocos2dx \
							$(LOCAL_PATH)/../../cocos2dx/include \
							$(LOCAL_PATH)/../../cocos2dx/platform/android \
							$(LOCAL_PATH) \
                           $(LOCAL_PATH)/jni
                    
include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx)
#$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
