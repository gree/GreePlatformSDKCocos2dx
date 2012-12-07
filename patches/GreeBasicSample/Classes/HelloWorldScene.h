#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-gree-ext.h"

USING_NS_CC;
USING_NS_CC_GREE_EXT;

class HelloWorld : public cocos2d::CCLayer, public cocos2d::gree_extension::CCGreePlatformDelegate
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void menuUserCallback(CCObject* pSender);
    void menuFriendCallback(CCObject* pSender);
	void menuPaymentCallback(CCObject* pSender);
	void menuAchievementCallback(CCObject* pSender);
	void menuLeaderboardCallback(CCObject* pSender);
	void menuCreateScoreCallback(CCObject* pSender);
	void menuLockUnlockCallback(CCObject* pSender);
	void menuLogoutCallback(CCObject* pSender);
	//
	void menuGreeButtonCallback(CCObject *pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	// scheduled func
	void Func(float dt);

	void ccTouchesEnded(CCSet* touches, CCEvent* event);

	// Authorizer
	virtual void authorizeAuthorized();
	virtual void logoutLogouted();
	virtual void logoutError();
	virtual void logoutCancel();

/*
	virtual void authorizeError(){};
	virtual void authorizeCancel(){};
	virtual void logoutLogouted(){};
	virtual void logoutError(){};
	virtual void logoutCancel(){};
	virtual void upgradeUpgraded(){};
	virtual void upgradeError(){};
	virtual void upgradeCancel(){};
*/

	// People
	virtual void loadThumbnailSuccess(CCGreeUser *user, CCImage *img);
	virtual void loadThumbnailFailure(CCGreeUser *user, int responseCode, CCString *response);
	virtual void loadFriendsSuccess(CCGreeUser *user, int index, int count, CCArray *userArray);
	void loadUserWithIdSuccess(int index, int count, CCArray *userArray);
	void loadIgnoredUserIdsSuccess(CCGreeUser *user, int index, int count, CCArray *userStringArray);
/*
	virtual void loadFriendsFailure(CCGreeUser *user, int responseCode, CCString *response){};
*/
	// Payment
	virtual void paymentRequestSuccess(CCGreePayment *payment, int responseCode, CCString* paymentId);
	virtual void paymentRequestCancel(CCGreePayment *payment, int responseCode, CCString* paymentId);
	virtual void paymentRequestFailure(CCGreePayment *payment, int responsCode, CCString *paymentID, CCString *response);

	// Achievement
	virtual void loadAchievementsSuccess(int index, int count, CCArray *elementArray);
	virtual void loadAchievementsFailure(int responseCode, CCString *response);

 	virtual void lockSuccess(CCGreeAchievement *element);
	virtual void lockFailure(CCGreeAchievement *element, int responseCode, CCString *response);
	virtual void unlockSuccess(CCGreeAchievement *element);
 	virtual void unlockFailure(CCGreeAchievement *element, int responseCode, CCString *response);
	virtual void loadAchievementThumbnailSuccess(CCGreeAchievement *achievement, CCImage *img);
	virtual void loadAchievementThumbnailFailure(CCGreeAchievement *achievement, int responseCode, CCString *response);

	// Leaderboard
	virtual void loadLeaderboardsSuccess(int index, int cound, CCArray *leaderboardArray);
	virtual void createScoreSuccess(CCGreeLeaderboard *leaderboard);
	virtual void loadLeaderboardThumbnailSuccess(CCGreeLeaderboard *leaderboard, CCImage *img);
	virtual void loadLeaderboardThumbnailFailure(CCGreeLeaderboard *leaderboard, int responseCode, CCString *response);
	virtual void getScoreSuccess(CCGreeLeaderboard *leaderboard, CCArray *scoreArray);
	virtual void getScoreFailure(CCGreeLeaderboard *leaderboard, int responseCode, CCString *response);
	virtual void loadScoreThumbnailSuccess(CCGreeScore *score, CCImage *img);

private:
	void dumpUserInfo(CCGreeUser *user);	
	void showAchievementInfo();
	void showLeaderboardInfo();
	void showResult(std::string* str1, std::string* str2);
};

#endif // __HELLOWORLD_SCENE_H__
