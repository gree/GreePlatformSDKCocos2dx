#ifndef __CCGREEAUTHORIZER_H__
#define __CCGREEAUTHORIZER_H__

#include <string.h>

#include "GreeExtensionMacros.h"

#include "cocoa/CCString.h"
#include "platform/CCImage.h"

NS_CC_GREE_EXT_BEGIN

class CCGreeAuthorizer;

class CCGreeAuthorizerDelegate
{
	public:
		virtual void authorizeAuthorized(){};
		virtual void authorizeError(){};
		virtual void authorizeCancel(){};
		virtual void authorizeUpdateLocalUser(){};

		virtual void logoutLogouted(){};
		virtual void logoutError(){};
		virtual void logoutCancel(){};
		virtual void logoutUpdateLocalUser(){};

		virtual void upgradeUpgraded(){};
		virtual void upgradeError(){};
		virtual void upgradeCancel(){};
		virtual void upgradeUpdateLocalUser(){};
};

class CCGreeAuthorizer
{
	public:
		static void authorize();
		//If needed, remove comment out
		//static void authorize(int userGrade);
		static bool isAuthorized();
		static bool hasOAuthAccessToken();
		static CCString *getOAuthAccessToken();
		static CCString *getOAuthAccessTokenSecret();
		static void logout();

		static void upgrade(int targetGrade);
		// directLogout():

		// authorize callback
		static void handleOnAuthorized();
		static void handleOnAuthorizeCancel();
		static void handleOnAuthorizeError();
		static void handleOnAuthorizeUpdateLocalUser();

		// logout callback
		static void handleOnLogouted();	
		static void handleOnLogoutCancel();
		static void handleOnLogoutError();
		static void handleOnLogoutUpdateLocalUser();

		// upgrade callback
		static void handleOnUpgraded();	
		static void handleOnUpgradeCancel();
		static void handleOnUpgradeError();
		static void handleOnUpgradeUpdateLocalUser();

};


NS_CC_GREE_EXT_END

#endif
