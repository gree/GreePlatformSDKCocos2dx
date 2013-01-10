#include "CCGreePlatform.h"

#include "CCGreeUser.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.h"

using namespace cocos2d;

NS_CC_GREE_EXT_BEGIN


CCGreeUserDelegate        *CCGreePlatform::s_pUserDelegate = NULL;
CCGreePaymentDelegate     *CCGreePlatform::s_pPaymentDelegate = NULL;
CCGreeAchievementDelegate *CCGreePlatform::s_pAchievementDelegate = NULL;
CCGreeAuthorizerDelegate  *CCGreePlatform::s_pAuthorizerDelegate = NULL;
CCGreeLeaderboardDelegate *CCGreePlatform::s_pLeaderboardDelegate = NULL;
CCGreeFriendCodeDelegate  *CCGreePlatform::s_pFriendCodeDelegate = NULL;


CCString *CCGreePlatform::getLocalUserId(){
	const std::string str = getLocalUserIdJni();
	CCString *ret = new CCString(str);
	ret->autorelease();
	return ret;
}

CCGreeUser *CCGreePlatform::getLocalUser(){
	jobject user;
	user = getLocalUserJni();
	CCGreeUser *greeUser = new CCGreeUser(user);
	greeUser->autorelease();
	//TODO : Want to remove retain().
	//       But in such case, developer have to issue retain() by himself to use
	//       object outside the function where it has gotten
	//       Furthermore some of current callbacks are including correspoding 
	//       object information and to get them developer also have to issue retain()
	//       not to be automatically released.
	greeUser->retain();
	return greeUser;	
}

NS_CC_GREE_EXT_END




