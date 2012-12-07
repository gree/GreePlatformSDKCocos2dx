#include "CCGreePlatform.h"

#include "CCGreeUser.h"

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
	return greeUser;	
}

NS_CC_GREE_EXT_END




