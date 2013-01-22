#import "GreePlatform.h"
#import "CCGreePlatform.h"

using namespace cocos2d;

NS_CC_GREE_EXT_BEGIN


CCGreeUserDelegate        *CCGreePlatform::s_pUserDelegate = NULL;
CCGreePaymentDelegate     *CCGreePlatform::s_pPaymentDelegate = NULL;
//CCGreeAchievementDelegate *CCGreePlatform::s_pAchievementDelegate = NULL;
CCGreeAuthorizerDelegate  *CCGreePlatform::s_pAuthorizerDelegate = NULL;
//CCGreeLeaderboardDelegate *CCGreePlatform::s_pLeaderboardDelegate = NULL;
//CCGreeFriendCodeDelegate  *CCGreePlatform::s_pFriendCodeDelegate = NULL;
CCGreeShareDialogDelegate *CCGreePlatform::s_pShareDialogDelegate = NULL;
CCGreeInviteDialogDelegate *CCGreePlatform::s_pInviteDialogDelegate = NULL;


CCString *CCGreePlatform::getLocalUserId(){
    NSString *pStr = [GreePlatform sharedInstance].localUserId;
    CCString *ret = new CCString([pStr UTF8String]);
    ret->autorelease();
	return ret;
}

CCGreeUser *CCGreePlatform::getLocalUser(){
    void* user = (void*)([GreePlatform sharedInstance].localUser);
	CCGreeUser *greeUser = new CCGreeUser(user);
	return greeUser;
}

NS_CC_GREE_EXT_END




