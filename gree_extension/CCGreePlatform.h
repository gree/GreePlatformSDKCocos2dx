#ifndef __CC_GREEPLATFORM_H__
#define __CC_GREEPLATFORM_H__


#include "cocos-gree-ext.h"

//#include "platform/CCPlatformMacros.h"
#include "CCStdC.h"
#include "cocoa/CCString.h"

#include "CCGreeUser.h"

NS_CC_GREE_EXT_BEGIN;

class CCGreePlatformDelegate : public cocos2d::gree_extension::CCGreeAuthorizerDelegate, public cocos2d::gree_extension::CCGreePaymentDelegate, public cocos2d::gree_extension::CCGreeUserDelegate, public cocos2d::gree_extension::CCGreeAchievementDelegate, public cocos2d::gree_extension::CCGreeLeaderboardDelegate, public cocos2d::gree_extension::CCGreeFriendCodeDelegate
{
};

class CCGreePlatform {
	public:
		static CCString *getLocalUserId();
		static CCGreeUser *getLocalUser();

		// Delegate
		// Currently only one client can be registered with setXXXXDelegate,
		// but if needed can be modified to support multi client, 
		//and to support that removeXXXXDelegate is defined to get Delegate as args.
		static void setUserDelegate(CCGreeUserDelegate *pDelegate) { s_pUserDelegate = pDelegate; }
		static void removeUserDelegate(CCGreeUserDelegate *pDelegate) { s_pUserDelegate = NULL; }
		static CCGreeUserDelegate *getUserDelegate() { return s_pUserDelegate; }
		static void setPaymentDelegate(CCGreePaymentDelegate *pDelegate) { s_pPaymentDelegate = pDelegate; }
		static void removePaymentDelegate(CCGreePaymentDelegate *pDelegate) { s_pPaymentDelegate = NULL; }
		static CCGreePaymentDelegate *getPaymentDelegate() { return s_pPaymentDelegate; }
		static void setAchievementDelegate(CCGreeAchievementDelegate *pDelegate) { s_pAchievementDelegate = pDelegate; }
		static void removeAchievementDelegate(CCGreeAchievementDelegate *pDelegate) { s_pAchievementDelegate = NULL; }
		static CCGreeAchievementDelegate *getAchievementDelegate() { return s_pAchievementDelegate; }
		static void setAuthorizerDelegate(CCGreeAuthorizerDelegate *pDelegate) { s_pAuthorizerDelegate = pDelegate; }
		static void removeAuthorizerDelegate(CCGreeAuthorizerDelegate *pDelegate) { s_pAuthorizerDelegate = NULL; }
		static CCGreeAuthorizerDelegate *getAuthorizerDelegate() { return s_pAuthorizerDelegate; }
		static void setLeaderboardDelegate(CCGreeLeaderboardDelegate *pDelegate) { s_pLeaderboardDelegate = pDelegate; }
		static void removeLeaderboardDelegate(CCGreeLeaderboardDelegate *pDelegate) { s_pLeaderboardDelegate = NULL; }
		static CCGreeLeaderboardDelegate *getLeaderboardDelegate() { return s_pLeaderboardDelegate; }
		static void setFriendCodeDelegate(CCGreeFriendCodeDelegate *pDelegate) { s_pFriendCodeDelegate = pDelegate; }
		static CCGreeFriendCodeDelegate *getFriendCodeDelegate() { return s_pFriendCodeDelegate; }
		static void removeFriendCodeDelegate(CCGreeFriendCodeDelegate *pDelegate) { s_pFriendCodeDelegate = NULL; }

	private:
		static CCGreeUserDelegate        *s_pUserDelegate;
		static CCGreePaymentDelegate     *s_pPaymentDelegate;
		static CCGreeAchievementDelegate *s_pAchievementDelegate;
		static CCGreeAuthorizerDelegate  *s_pAuthorizerDelegate;
		static CCGreeLeaderboardDelegate *s_pLeaderboardDelegate;
		static CCGreeFriendCodeDelegate  *s_pFriendCodeDelegate;
};

NS_CC_GREE_EXT_END

#endif

