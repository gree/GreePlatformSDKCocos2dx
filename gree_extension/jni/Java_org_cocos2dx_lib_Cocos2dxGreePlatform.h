#ifndef __Java_org_cocos2dx_lib_Cocos2dxGreePlatform_H__
#define __Java_org_cocos2dx_lib_Cocos2dxGreePlatform_H__

#include <string.h>

typedef enum {
	fTypeLoadUserThumbnail = 1,
	fTypeLoadAchievementThumbnail,
	fTypeLoadLeaderboardThumbnail,
	fTypeLoadScoreThumbnail,
} ccLoadThumbnailFuncType;

typedef enum {
	fTypeLoadFriends = 1,
	fTypeLoadUserWithId,
} ccLoadUserFuncType;

typedef enum {
	fTypeLoadIgnoredUserIds = 1,
	fTypeIsIgnoringUserWithId,
} ccIgnoredUserFuncType;

typedef enum {
	fTypeAchievementLock = 1,
	fTypeAchievementUnlock,
} ccAchievementChangeFuncType;

typedef enum {
	fTypeAuthorize = 1,
	fTypeLogout,
	fTypeUpgrade,
} ccAuthorizeFuncType;

typedef enum {
	fTypeCreateScore = 1,
	fTypeDeleteScore,
} ccLeaderboardScoreFuncType;

typedef enum {
	fTypeLoadCode = 1,
	fTypeRequestCode,
} ccFriendCodeFuncType;
typedef enum {
	fTypeVerifyCode = 1,
	fTypeDeleteCode,
} ccFriendCodeConfirmFuncType;

#define CALL_JNI_STRING_METHOD(func) \
	const std::string str = func##Jni(); \
	CCString *ret = new CCString(str); \
	ret->autorelease(); \
	return ret; \

#define CALL_JNI_INT_METHOD(func) \
	int ret = -1; \
	ret = func##Jni(); \
	return ret;

#define CALL_JNI_BOOL_METHOD(func) \
	bool ret = false; \
	ret = func##Jni(); \
	return ret;

#define CALL_JNI_STRING_METHOD_WITHOBJECT(func, obj) \
	if(obj != NULL){ \
		const std::string str = func##Jni((jobject)obj); \
		CCString *ret = new CCString(str); \
		ret->autorelease(); \
			return ret; \
		} \
	return NULL;

#define CALL_JNI_INT_METHOD_WITHOBJECT(func, obj) \
	int ret = -1; \
	if(obj != NULL){ \
		ret = func##Jni((jobject)obj); \
	} \
	return ret;

#define CALL_JNI_BOOL_METHOD_WITHOBJECT(func, obj) \
	bool ret = false; \
	if(obj != NULL){ \
		ret = func##Jni((jobject)obj); \
	} \
	return ret;


extern "C"
{
    std::string getLocalUserIdJni(void);
    jobject getLocalUserJni();

	jobject getPlatformContext();
}
#endif

