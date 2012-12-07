#ifndef __Java_org_cocos2dx_lib_Cocos2dxGreeAuthorizer_H__
#define __Java_org_cocos2dx_lib_Cocos2dxGreeAuthorizer_H__

#include <string.h>

#include "cocos-gree-ext.h"

extern "C"
{
	void authorizeJni(int userGrade);
	void logoutJni();
	void upgradeJni(int targetGrade);
	bool hasOAuthAccessTokenJni();
	std::string getOAuthAccessTokenJni();
	std::string getOAuthAccessTokenSecretJni();
	bool isAuthorizedJni(void);
}
#endif

