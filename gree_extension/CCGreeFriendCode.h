#ifndef __CCGREEFRIENDCODE_H__
#define __CCGREEFRIENDCODE_H__

#include "jni/JniHelper.h"
#include "cocos2d.h"
#include "cocos-gree-ext.h"

NS_CC_GREE_EXT_BEGIN

class CCGreeFriendCode;
class CCGreeCode;
class CCGreeData;

class CCGreeFriendCodeDelegate{
	public:
		virtual void loadCodeSuccess(CCGreeCode *code){};
		virtual void loadCodeFailure(int responseCode, CCString *response){};
		virtual void requestCodeSuccess(CCGreeCode *code){};
		virtual void requestCodeFailure(int responseCode, CCString *response){};

		virtual void deleteCodeSuccess(){};
		virtual void deleteCodeFailure(int responseCode, CCString *response){};
		virtual void verifyCodeSuccess(){};
		virtual void verifyCodeFailure(int responseCode, CCString *response){};

		virtual void loadFriendIdsSuccess(int startIndex, int itemsPerPage, int totalResults, CCArray *dataArray){};
		virtual void loadFriendIdsFailure(int responseCode, CCString *response){};
		virtual void loadOwnerSuccess(CCGreeData *owner){};
		virtual void loadOwnerFailure(int responseCode, CCString *response){};

};

class CCGreeFriendCode {
	public:
		static void loadCode();
		//static void loadFriends(int startIndex, int count);
		static void loadFriendIds(int startIndex, int count);
		static void loadOwner();
		static bool requestCode(const char* expireTime);
		static void verifyCode(const char* code);
		static void deleteCode();


		static void handleLoadCodeOnSuccess(jobject code);
		static void handleLoadCodeOnFailure(int responseCode, const char *response);
		static void handleRequestCodeOnSuccess(jobject code);
		static void handleRequestCodeOnFailure(int responseCode, const char *response);

		static void handleDeleteCodeOnSuccess();
		static void handleDeleteCodeOnFailure(int responseCode, const char *response);
		static void handleVerifyCodeOnSuccess();
		static void handleVerifyCodeOnFailure(int responseCode, const char *response);

		static void handleLoadFriendIdsOnSuccess(int startIndex, int itemsPerPage, int totalResults, jobject *entries);
		static void handleLoadFriendIdsOnFailure(int responseCode, const char *response);
		static void handleLoadOwnerOnSuccess(jobject owner);
		static void handleLoadOwnerOnFailure(int responseCode, const char *response);
		
};


class CCGreeCode : public CCObject
{
	public:
		CCGreeCode(jobject code);
		~CCGreeCode();
		CCString *getCode();
		CCString *getExpireTime();

	private:
		jobject mGreeCode;
};

class CCGreeData : public CCObject
{
	public:
		CCGreeData(jobject data);
		~CCGreeData();
		CCString *getUserId();

	private:
		jobject mGreeData;

};

NS_CC_GREE_EXT_END

#endif

