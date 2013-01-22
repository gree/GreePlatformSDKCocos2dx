#ifndef __CC_GREEPLATFORM_H__
#define __CC_GREEPLATFORM_H__

#include "GreeExtensionMacros.h"
#include "CCGreeAuthorizer.h"
#include "CCGreeDashboard.h"
#include "CCGreeUser.h"
#include "CCGreePayment.h"
#include "CCGreeAchievement.h"
#include "CCGreeLeaderboard.h"
#include "CCGreeInviteDialog.h"
#include "CCGreeRequestDialog.h"
#include "CCGreeShareDialog.h"
#include "CCGreeFriendCode.h"

#include "CCStdC.h"
#include "cocoa/CCString.h"

NS_CC_GREE_EXT_BEGIN;


#define CREATE_DELEGATE(module) \
	public: \
		static void set##module(CCGree##module *pDelegate) { s_p##module = pDelegate; } \
		static CCGree##module *get##module() { return s_p##module; }; \
		static void remove##module(CCGree##module *pDelegate) { s_p##module = NULL; } \
	private: \
		static CCGree##module *s_p##module;

class CCGreePlatformDelegate : public cocos2d::gree_extension::CCGreeAuthorizerDelegate, public cocos2d::gree_extension::CCGreePaymentDelegate, public cocos2d::gree_extension::CCGreeUserDelegate, public cocos2d::gree_extension::CCGreeAchievementDelegate, public cocos2d::gree_extension::CCGreeLeaderboardDelegate, public cocos2d::gree_extension::CCGreeFriendCodeDelegate, public cocos2d::gree_extension::CCGreeInviteDialogDelegate, public cocos2d::gree_extension::CCGreeShareDialogDelegate, public cocos2d::gree_extension::CCGreeRequestDialogDelegate
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
		CREATE_DELEGATE(UserDelegate);
		CREATE_DELEGATE(PaymentDelegate);
		CREATE_DELEGATE(AchievementDelegate);
		CREATE_DELEGATE(AuthorizerDelegate);
		CREATE_DELEGATE(LeaderboardDelegate);
		CREATE_DELEGATE(FriendCodeDelegate);
		CREATE_DELEGATE(InviteDialogDelegate);
		CREATE_DELEGATE(ShareDialogDelegate);
		CREATE_DELEGATE(RequestDialogDelegate);

};


NS_CC_GREE_EXT_END

#endif

