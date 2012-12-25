#ifndef __CC_GREEDASHBOARD_H__
#define __CC_GREEDASHBOARD_H__

#include "CCStdC.h"
#include "cocoa/CCString.h"
#include "cocoa/CCDictionary.h"

#include "GreeExtensionMacros.h"

using namespace std;

NS_CC_GREE_EXT_BEGIN

class CCGreeDashboard;

// to be user with launch
typedef enum {
	launchTypeAutoSelect = 0,
	launchTypeGDTop = 1,
	launchTypeGDLeaderboardList = 2,
	launchTypeGDLeaderboardDetail = 3,
	launchTypeGDAchievementList = 4,
	launchTypeGDUserList = 5,
	launchTypeGDApplicationSetting = 6,
	launchTypeGDInviteFriend = 7,
	launchTypeGDCommunity = 8,
} ccDashboardLaunchType;


// to be used with launch
#define GD_PARAMS_KEY_APP_ID              "app_id"
#define GD_PARAMS_KEY_USER_ID             "user_id"
#define GD_PARAMS_KEY_LEADERBOARD_ID      "leaderboard_id"
#define GD_PARAMS_KEY_EXTRA_URL           "extra_url"
#define GD_PARAMS_KEY_CIMMUNITY_ID        "community_id"
#define GD_PARAMS_KEY_COMMUNITY_THREAD_ID "thread_id"

class CCGreeDashboard {
	public:
		static bool launch();
		static bool launch(int type, CCDictionary *params);
};

NS_CC_GREE_EXT_END

#endif

