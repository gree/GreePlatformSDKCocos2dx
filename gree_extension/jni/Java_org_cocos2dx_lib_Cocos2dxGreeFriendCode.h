#ifndef __Java_org_cocos2dx_lib_Cocos2dxGreeFriendCode_H__
#define __Java_org_cocos2dx_lib_Cocos2dxGreeFriendCode_H__

#include "cocos2d.h"

extern "C"
{
	void loadCodeJni();
	bool requestCodeJni(const char* expireTime);
	void deleteCodeJni();
	void verifyCodeJni(const char* code);
	void loadFriendIdsJni(int startIndex, int count);
	void loadOwnerJni();

	// Code
	std::string getCodeJni(jobject obj);
	std::string getExpireTimeJni(jobject obj);

	// Data
	std::string getUserIdFromGreeDataJni(jobject obj);


}


#endif
