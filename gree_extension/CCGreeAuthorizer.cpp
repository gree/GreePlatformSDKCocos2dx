#include "CCDirector.h"

#include "CCGreePlatform.h"
#include "CCGreeAuthorizer.h"

#define JAVAVM    cocos2d::JniHelper::getJavaVM()

using namespace cocos2d;

NS_CC_GREE_EXT_BEGIN


// Method
void CCGreeAuthorizer::authorize(){
	authorizeJni(-1);
}
//void CCGreeAuthorizer::authorize(int userGrade){
//	authorizeJni(userGrade);
//}

void CCGreeAuthorizer::logout(){
	logoutJni();
}

void CCGreeAuthorizer::upgrade(int targetGrade){
	upgradeJni(targetGrade);
}

CCString *CCGreeAuthorizer::getOAuthAccessToken(){
	CALL_JNI_STRING_METHOD(getOAuthAccessToken);
}

CCString *CCGreeAuthorizer::getOAuthAccessTokenSecret(){
	CALL_JNI_STRING_METHOD(getOAuthAccessTokenSecret);
	
}

bool CCGreeAuthorizer::isAuthorized(){
	CALL_JNI_BOOL_METHOD(isAuthorized);
}

bool CCGreeAuthorizer::hasOAuthAccessToken(){
	CALL_JNI_BOOL_METHOD(isAuthorized);
}


// Callback Handling
void CCGreeAuthorizer::handleOnAuthorized(){
	CCGreeAuthorizerDelegate *delegate = CCGreePlatform::getAuthorizerDelegate();
	if(delegate != NULL){
		delegate->authorizeAuthorized();
	}
}
void CCGreeAuthorizer::handleOnAuthorizeCancel(){
	CCGreeAuthorizerDelegate *delegate = CCGreePlatform::getAuthorizerDelegate();
	if(delegate != NULL){
		delegate->authorizeCancel();
	}
}
void CCGreeAuthorizer::handleOnAuthorizeError(){
	CCGreeAuthorizerDelegate *delegate = CCGreePlatform::getAuthorizerDelegate();
	if(delegate != NULL){
		delegate->authorizeError();
	}
}

void CCGreeAuthorizer::handleOnAuthorizeUpdateLocalUser(){
	CCGreeAuthorizerDelegate *delegate = CCGreePlatform::getAuthorizerDelegate();
	if(delegate != NULL){
		delegate->authorizeUpdateLocalUser();
	}
}

void CCGreeAuthorizer::handleOnLogouted(){
	CCGreeAuthorizerDelegate *delegate = CCGreePlatform::getAuthorizerDelegate();
	if(delegate != NULL){
		delegate->logoutLogouted();
	}
}

void CCGreeAuthorizer::handleOnLogoutError(){
	CCGreeAuthorizerDelegate *delegate = CCGreePlatform::getAuthorizerDelegate();
	if(delegate != NULL){
		delegate->logoutError();
	}
}

void CCGreeAuthorizer::handleOnLogoutCancel(){
	CCGreeAuthorizerDelegate *delegate = CCGreePlatform::getAuthorizerDelegate();
	if(delegate != NULL){
		delegate->logoutCancel();
	}
}

void CCGreeAuthorizer::handleOnLogoutUpdateLocalUser(){
	CCGreeAuthorizerDelegate *delegate = CCGreePlatform::getAuthorizerDelegate();
	if(delegate != NULL){
		delegate->logoutUpdateLocalUser();
	}
}


void CCGreeAuthorizer::handleOnUpgraded(){
	CCGreeAuthorizerDelegate *delegate = CCGreePlatform::getAuthorizerDelegate();
	if(delegate != NULL){
		delegate->upgradeUpgraded();
	}
}

void CCGreeAuthorizer::handleOnUpgradeError(){
	CCGreeAuthorizerDelegate *delegate = CCGreePlatform::getAuthorizerDelegate();
	if(delegate != NULL){
		delegate->upgradeError();
	}
}

void CCGreeAuthorizer::handleOnUpgradeCancel(){
	CCGreeAuthorizerDelegate *delegate = CCGreePlatform::getAuthorizerDelegate();
	if(delegate != NULL){
		delegate->upgradeCancel();
	}
}

void CCGreeAuthorizer::handleOnUpgradeUpdateLocalUser(){
	CCGreeAuthorizerDelegate *delegate = CCGreePlatform::getAuthorizerDelegate();
	if(delegate != NULL){
		delegate->upgradeUpdateLocalUser();
	}
}

NS_CC_GREE_EXT_END

