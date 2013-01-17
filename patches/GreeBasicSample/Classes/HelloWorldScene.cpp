#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#define FRIEND_X_OFFSET (300)
#define FRIEND_Y_OFFSET (480)

using namespace cocos2d;
using namespace CocosDenshion;

CCLabelTTF* pGreeButtonText;

CCSprite* pSprite;
CCSprite* pIcon = NULL;

int gThumbFlag = 0;
CCImage *pThumb = NULL;


int gFriendFlag = 0;
CCArray *pFriends = NULL;
int gNumOfFriend = 0;

int gElementFlag = 0;
CCArray *pElements = NULL;
int gNumOfElm  = 0;

int gLeaderboardFlag = 0;
CCArray *pLeaderboards = NULL;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


void HelloWorld::dumpUserInfo(CCGreeUser *user){
	CCString *nickName = user->getNickname();
	CCString *dispName = user->getDisplayName();
	CCString *id = user->getId();
	CCString *region = user->getRegion();
	CCString *subRegion = user->getSubregion();
	CCString *lang = user->getLanguage();
	CCString *timeZone = user->getTimezone();
	CCString *me = user->getAboutMe();
	CCString *birthDay = user->getBirthday();
	//CCString *url = pUser->getProfileUrl();
	//CCLog("++++++ ProfileUrl %s", url->getCString());	
	CCString *gender = user->getGender();
	CCString *age = user->getAge();
	CCString *blood = user->getBloodType();
	bool hasApp = user->getHasApp();
	CCString *hash = user->getUserHash();
	CCString *type = user->getUserType();
	int grade = user->getUserGrade();
	CCLog("++++++ NickName %s", nickName->getCString());
	CCLog("++++++ DisplayName %s", dispName->getCString());
	CCLog("++++++ Id %s", id->getCString());
	CCLog("++++++ Region %s", region->getCString());
	CCLog("++++++ Subregion %s", subRegion->getCString());
	CCLog("++++++ Language %s", lang->getCString());
	CCLog("++++++ Timezone %s", timeZone->getCString());
	CCLog("++++++ me %s", me->getCString());
	CCLog("++++++ BirthDay %s", birthDay->getCString());
	CCLog("++++++ Gender %s", gender->getCString());
	CCLog("++++++ Age %s", age->getCString());
	CCLog("++++++ BloodType %s", blood->getCString());
	CCLog("++++++ HasApp %d", hasApp);
	CCLog("++++++ UserHash %s", hash->getCString());
	CCLog("++++++ UserType %s", type->getCString());
	CCLog("++++++ grade %d", grade);
}


void HelloWorld::menuGreeButtonCallback(CCObject *pSender){
	CCGreePlatform::setUserDelegate(this);
	CCGreePlatform::setAuthorizerDelegate(this);
	CCGreePlatform::setAchievementDelegate(this);
	CCGreePlatform::setPaymentDelegate(this);
	CCGreePlatform::setLeaderboardDelegate(this);
	if(CCGreeAuthorizer::isAuthorized() != true){
		CCGreeAuthorizer::authorize();
	}else{
		CCDictionary *dict = CCDictionary::create();
		dict->setObject(new CCString("16311"), GD_PARAMS_KEY_APP_ID);
		dict->setObject(new CCString("1000020828"), GD_PARAMS_KEY_USER_ID);
		//CCGreeDashboard::launch(launchTypeAutoSelect, dict);
		CCGreeDashboard::launch(launchTypeAutoSelect, NULL);
		//CCGreeDashboard::launch();
	}
}


void HelloWorld::menuUserCallback(CCObject *pSender){
	// Load Thumbnail 
	CCGreeUser::loadUserWithId("1000020828");

	CCGreeUser *user = CCGreePlatform::getLocalUser();
	//user->load
	user->loadThumbnail(UserThumbnailSizeHuge);

	user->loadIgnoredUserIds(0, 10);
}


void HelloWorld::menuFriendCallback(CCObject *pSender){
	// Load Friend list
	CCGreeUser *user = CCGreePlatform::getLocalUser();
	user->loadFriends(1, 10);
}

void HelloWorld::menuPaymentCallback(CCObject *pSender){
	//CCGreePaymentItem *item1 = new CCGreePaymentItem("01234", "TestItem1", 100, 20);
	//CCGreePaymentItem *item2 = new CCGreePaymentItem("56789", "TestItem2", 200, 30);
	CCGreePaymentItem *item1 = CCGreePaymentItem::create("01234", "TestItem1", 100, 2);
	CCGreePaymentItem *item2 = CCGreePaymentItem::create("56789", "TestItem2", 200, 30);

/*
	std::string str1 = "new CCGreePaymentItem 1";
	std::string str2 = "ItemId : ";
	str2.append(item1->getItemId()->getCString());
	str2.append(" ItemName : ");
	str2.append(item1->getItemName()->getCString());
	str2.append(" UnitPrice : ");
	char text[48];
	sprintf(text, "%f", item1->getUnitPrice());
	str2.append(text);
	str2.append(" Quantity : ");
	sprintf(text, "%d", item1->getQuantity());
	str2.append(text);
	str2.append(" ImageUrl : ");
	str2.append(item1->getImageUrl()->getCString());
	str2.append(" Desc : ");
	str2.append(item1->getDescription()->getCString());
	showResult(&str2, &str1);
*/

	CCArray *itemArray = new CCArray();
	itemArray->addObject(item1);
	itemArray->addObject(item2);
	//CCGreePayment *pay = new CCGreePayment("Payment Test", itemArray);
	CCGreePayment *pay = CCGreePayment::create("Payment Test", itemArray);
	pay->request();
}

#define ACHIEVEMENT_X_OFFSET (200)
#define ACHIEVEMENT_Y_OFFSET (500)

void HelloWorld::showAchievementInfo(){
	static CCMenuItemLabel* pLabel[10];
	static CCLabelTTF *lName[10];
	static CCLabelTTF *lId[10];
	static CCLabelTTF *lLock[10];

	static CCImage *lockImg[10] = {NULL};
	static CCTexture2D *lockTex[10] = {NULL};
	static CCSprite *lockSp[10] = {NULL};

	static CCMenu *pMenu;

	CCObject *it;
	int i = 0;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if(pMenu == NULL){
		// 1st time
		pMenu = CCMenu::create(NULL, NULL);
		CCARRAY_FOREACH(pElements, it){
			CCGreeAchievement *ach = dynamic_cast<CCGreeAchievement *>(it);

			lName[i] = CCLabelTTF::create(ach->getName()->getCString(), "Thonburi", 40);
			pLabel[i] = CCMenuItemLabel::create(lName[i], this, menu_selector(HelloWorld::menuLockUnlockCallback));
			pLabel[i]->setPosition(ccp(size.width - ACHIEVEMENT_X_OFFSET, size.height - ACHIEVEMENT_Y_OFFSET - i * 120));
			pMenu->addChild(pLabel[i], 1, 2000 + i);

			lId[i] = CCLabelTTF::create(ach->getId()->getCString(), "Thonburi", 30);
			if(ach->isUnlocked() == true){
				lLock[i] = CCLabelTTF::create("UnLocked", "Thonburi", 30);
			}else{
				lLock[i] = CCLabelTTF::create("Locked", "Thonburi", 30);
			}
			lId[i]->setPosition(ccp(size.width - ACHIEVEMENT_X_OFFSET, size.height - ACHIEVEMENT_Y_OFFSET - 40 - i * 120));
			lLock[i]->setPosition(ccp(size.width - ACHIEVEMENT_X_OFFSET, size.height - ACHIEVEMENT_Y_OFFSET - 70 - i * 120));
			this->addChild(lId[i], 1);
			this->addChild(lLock[i], 1);
			i++;

			// loadThumbnail
			ach->loadThumbnail();
		}
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 1);
	}else{
		CCARRAY_FOREACH(pElements, it){
			CCGreeAchievement *ach = dynamic_cast<CCGreeAchievement *>(it);
			if(ach->isUnlocked() == true){
				lLock[i]->setString("UnLocked");
				CCLog("++++++ Achievement Unocked");
			}else{
				CCLog("++++++ Achievement Locked");
				lLock[i]->setString("Locked");
			}
			{
				lockImg[i] = ach->getIcon();
				if(lockTex[i] != NULL){
					CCTextureCache::sharedTextureCache()->removeTexture(lockTex[i]);
				}
				if(i == 0){
					lockTex[i] = CCTextureCache::sharedTextureCache()->addUIImage(lockImg[i], "key_icon0");
				}else{
					lockTex[i] = CCTextureCache::sharedTextureCache()->addUIImage(lockImg[i], "key_icon1");
				}
				if(lockSp[i] != NULL){
					this->removeChild(lockSp[i], 0);
				}
				lockSp[i] = CCSprite::spriteWithTexture(lockTex[i]);
				lockSp[i]->setPosition(ccp(size.width - ACHIEVEMENT_X_OFFSET - 100, size.height - ACHIEVEMENT_Y_OFFSET - 70 - i * 120));
				this->addChild(lockSp[i], 0);
			}
			i++;
		}

	}
}

#define LEADERBOARD_X_OFFSET (200)
#define LEADERBOARD_Y_OFFSET (180)
void HelloWorld::showLeaderboardInfo(){
	static CCMenuItemLabel* pLabel[10];
	static CCLabelTTF *lName[10];
	static CCLabelTTF *lId[10];
	static CCLabelTTF *lScore[10];

	//static CCImage *lockImg[10] = {NULL};
	//static CCTexture2D *lockTex[10] = {NULL};
	//static CCSprite *lockSp[10] = {NULL};

	static CCMenu *pMenu;

	int i = 0;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	pMenu = CCMenu::create(NULL, NULL);
	CCObject *it;
	CCARRAY_FOREACH(pLeaderboards, it){
		CCGreeLeaderboard *board = dynamic_cast<CCGreeLeaderboard *>(it);

		lName[i] = CCLabelTTF::create(board->getName()->getCString(), "Thonburi", 40);
		lScore[i] = CCLabelTTF::create("createScore", "Thonburi", 30);
		lId[i] = CCLabelTTF::create(board->getId()->getCString(), "Thonburi", 30);

		pLabel[i] = CCMenuItemLabel::create(lScore[i], this, menu_selector(HelloWorld::menuCreateScoreCallback));

		lName[i]->setPosition(ccp(size.width - LEADERBOARD_X_OFFSET, size.height - LEADERBOARD_Y_OFFSET - i * 120));
        lId[i]->setPosition(ccp(size.width - LEADERBOARD_X_OFFSET, size.height - LEADERBOARD_Y_OFFSET - 40 - i * 120));
		pLabel[i]->setPosition(ccp(size.width - LEADERBOARD_X_OFFSET, size.height - LEADERBOARD_Y_OFFSET - 70 - i * 120));

		pMenu->addChild(pLabel[i], 1, 3000 + i);
        this->addChild(lId[i], 1);
        this->addChild(lName[i], 1);
        i++;
		board->loadThumbnail();
	}
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
}

void HelloWorld::menuAchievementCallback(CCObject *pSender){
	// Load Achievement
	CCGreeAchievement::loadAchievements(1, 10);
}

void HelloWorld::menuLeaderboardCallback(CCObject *pSender){
	CCGreeLeaderboard::loadLeaderboards(1, 10);
}

void HelloWorld::menuCreateScoreCallback(CCObject *pSender){
	int tag = (int)((CCMenuItem*)pSender)->getTag() - 3000;
	CCLog("++++++ %s Tag:%d", __func__, tag);
	CCGreeLeaderboard *pBrd = dynamic_cast<CCGreeLeaderboard *>(pLeaderboards->objectAtIndex(tag));
	CCLog("%s", pBrd->getName()->getCString());
	//ALL_SCORE, ALL_TIME,
	pBrd->getScore(2, 2, 1, 10);
}



void HelloWorld::menuLockUnlockCallback(CCObject *pSender){
	CCLog("++++++ %s Tag:%d", __func__, (int)((CCMenuItem*)pSender)->getTag());
	int tag = (int)((CCMenuItem*)pSender)->getTag() - 2000;
	CCGreeAchievement *pAch = dynamic_cast<CCGreeAchievement *>(pElements->objectAtIndex(tag));
	CCLog("%s", pAch->getName()->getCString());
	if(pAch->isUnlocked() == true){
		pAch->lock();
	}else{
		pAch->unlock();
	}
}

void HelloWorld::menuLogoutCallback(CCObject *pSender){
	CCGreeAuthorizer::logout();
}

// Authorizer Callback
int authFlag = 0;
void HelloWorld::authorizeAuthorized(){
	CCLog("++++++ %s\n", __func__);

	//CCGreeAuthorizer::upgrade(2);

	std::string str1 = "Callback";
	std::string str2 = "authorize Success";
	showResult(&str2, &str1);

	if(authFlag == 0){
	pGreeButtonText->setString("Dashboard");


	CCSize size = CCDirector::sharedDirector()->getWinSize();


	CCMoveTo *action = CCMoveTo::actionWithDuration(0.5f, ccp(0, size.height - 100));
	pSprite->runAction(action);

	CCMenu* pMenu = CCMenu::create(NULL, NULL);

	// User Information
	CCSprite *pSUser = CCSprite::create("friends.png");
	pSUser->setPosition( ccp(size.width/2 - 200, size.height - 120) );
	this->addChild(pSUser, 0);
	CCLabelTTF *textUser = CCLabelTTF::create("Get User Info", "Thonburi", 50);
	CCMenuItemLabel* pUser = CCMenuItemLabel::create(textUser, this, menu_selector(HelloWorld::menuUserCallback));
	pUser->setPosition(ccp(size.width/2 + 40, size.height - 120));


	// Friend Infomation
	CCSprite *pSFri = CCSprite::create("friends.png");
	pSFri->setPosition( ccp(size.width/2 - 200, size.height - 200) );
	this->addChild(pSFri, 0);
	CCLabelTTF *textFri = CCLabelTTF::create("Get Friend Info", "Thonburi", 50);
	CCMenuItemLabel* pFri = CCMenuItemLabel::create(textFri, this, menu_selector(HelloWorld::menuFriendCallback));
	pFri->setPosition(ccp(size.width/2 + 40, size.height - 200));


	// Payment
	CCSprite *pSPay = CCSprite::create("payment.png");
	pSPay->setPosition( ccp(size.width/2 - 200, size.height - 280) );
	this->addChild(pSPay, 0);
	CCLabelTTF *textPay = CCLabelTTF::create("Request Payment", "Thonburi", 50);
	CCMenuItemLabel* pPay = CCMenuItemLabel::create(textPay, this, menu_selector(HelloWorld::menuPaymentCallback));
	pPay->setPosition(ccp(size.width/2 + 40, size.height - 280));


	// Achievement
	CCSprite *pSAch = CCSprite::create("achieve.png");
	pSAch->setPosition( ccp(size.width/2 - 200, size.height - 360));
	this->addChild(pSAch, 0);
	CCLabelTTF *textAch = CCLabelTTF::create("Load Achievement", "Thonburi", 50);
	CCMenuItemLabel* pAch = CCMenuItemLabel::create(textAch, this, menu_selector(HelloWorld::menuAchievementCallback));
	pAch->setPosition(ccp(size.width/2 + 40, size.height - 360));


	// Leaderboard
	CCSprite *pSLea = CCSprite::create("leaderboard.png");
	pSLea->setPosition(ccp(size.width/2 - 200, size.height - 440));
	this->addChild(pSLea, 0);
	CCLabelTTF *textLea = CCLabelTTF::create("Load Leaderboard", "Thonburi", 50);
	CCMenuItemLabel* pLea = CCMenuItemLabel::create(textLea, this, menu_selector(HelloWorld::menuLeaderboardCallback));
	pLea->setPosition(ccp(size.width/2 + 40, size.height - 440));


	CCLabelTTF *textLogout = CCLabelTTF::create("Logout User", "Thonburi", 50);
	CCMenuItemLabel* pLogout = CCMenuItemLabel::create(textLogout, this, menu_selector(HelloWorld::menuLogoutCallback));
	pLogout->setPosition(ccp(size.width/2 + 40, 100));
	

	pMenu->setPosition(CCPointZero);

	pMenu->addChild(pUser, 1000);
	pMenu->addChild(pPay, 1001);
	pMenu->addChild(pFri, 1002);
	pMenu->addChild(pAch, 1003);
	pMenu->addChild(pLea, 1004);
	pMenu->addChild(pLogout, 1010);

	this->addChild(pMenu, 1);

	authFlag = 1;


	//test 
	CCGreeInviteDialog *dialog1 = CCGreeInviteDialog::create();
	if(dialog1 == NULL){
		CCLog("+++++++++++++++++ Error ++++++++++");
	}else{
		CCDictionary *dict = CCDictionary::create();
        CCArray *array = new CCArray();
        array->addObject(new CCString("1000038120"));
        array->addObject(new CCString("1000038121"));
        dict->setObject(array, GD_INVITE_DIALOG_PARAM_KEY_TOUSERID);
		dict->setObject(new CCString("TestInviteBody"), GD_INVITE_DIALOG_PARAM_KEY_BODY);
		dialog1->setParams(dict);
		dialog1->show();
	}
	#if 0
	CCGreeRequestDialog *dialog2 = CCGreeRequestDialog::create();
	if(dialog2 == NULL){
		CCLog("+++++++++++++++++ Error ++++++++++");
	}else{
		CCDictionary *dict = CCDictionary::create();
		dict->setObject(new CCString("1000020828"), GD_REQUEST_DIALOG_PARAM_KEY_TOUSERID);
		dict->setObject(new CCString("TestRequest"), GD_REQUEST_DIALOG_PARAM_KEY_TITLE);
		dialog2->setParams(dict);
		dialog2->show();
	}
	CCGreeShareDialog *dialog3 = CCGreeShareDialog::create();
	if(dialog3 == NULL){
		CCLog("+++++++++++++++++ Error ++++++++++");
	}else{
		CCDictionary *dict = CCDictionary::create();
		dict->setObject(new CCString("Share Message"), GD_SHARE_DIALOG_PARAM_KEY_MESSAGE);
		dialog3->setParams(dict);
		dialog3->show();
	}
	#endif
	}
}
void HelloWorld::logoutLogouted(){
	std::string str1 = "Callback";
	std::string str2 = "logout Success";
	showResult(&str2, &str1);
}
void HelloWorld::logoutError(){
	std::string str1 = "Callback";
	std::string str2 = "logout Error";
	showResult(&str2, &str1);
}
void HelloWorld::logoutCancel(){
	std::string str1 = "Callback";
	std::string str2 = "logout Cancel";
	showResult(&str2, &str1);
}


void HelloWorld::showResult(std::string* str1, std::string* str2){
	CCMessageBox(str1->c_str(), str2->c_str());	
}

// User
void HelloWorld::loadThumbnailSuccess(CCGreeUser* user, CCImage *img){
	CCLog("++++++ %s", __func__);
	img->retain(); // To use mainthread
	std::string str1 = "Callback";
	std::string str2 = "loadThumbnail Success";
	showResult(&str2, &str1);
	pThumb = img;
	gThumbFlag = 1;
}
void HelloWorld::loadThumbnailFailure(CCGreeUser* user, int responseCode, CCString *response){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "loadThumbnail Failed : ";
	str2.append(response->getCString());
	showResult(&str2, &str1);
}
void HelloWorld::loadFriendsSuccess(CCGreeUser *user, int index, int count, CCArray *userArray){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "loadFriends Success";
	showResult(&str2, &str1);
	gFriendFlag = 1;
	pFriends = userArray;
	gNumOfFriend = count;
}
void HelloWorld::loadUserWithIdSuccess(int index, int count, CCArray *userArray){
	std::string str1 = "Callback";
	std::string str2 = "loadUserWithIdSuccess : ";
	CCGreeUser *user = dynamic_cast<CCGreeUser *>(userArray->objectAtIndex(0));
	str2.append(user->getNickname()->getCString());
	showResult(&str2, &str1);
}
void HelloWorld::loadIgnoredUserIdsSuccess(CCGreeUser *user, int index, int count, CCArray *userStringArray){
	std::string str1 = "Callback";
	std::string str2 = "loadIgnoredUserIdsSuccess : ";
	//CCGreeUser *user = dynamic_cast<CCGreeUser *>(userArray->objectAtIndex(0));
	str2.append(user->getNickname()->getCString());
	showResult(&str2, &str1);
}

// Payment
void HelloWorld::paymentRequestSuccess(CCGreePayment *payment, int responseCode, CCString *paymentId){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "paymentRequest Success : ";
	str2.append(paymentId->getCString());
	showResult(&str2, &str1);
}
void HelloWorld::paymentRequestCancel(CCGreePayment *payment, int responseCode, CCString* paymentId){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "paymentRequest Cancel : ";
	str2.append(paymentId->getCString());
	showResult(&str2, &str1);
}
void HelloWorld::paymentRequestFailure(CCGreePayment *payment, int responsCode, CCString *paymentID, CCString *response){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "paymentRequest Failure : ";
	str2.append(response->getCString());
	showResult(&str2, &str1);
}

// Achievement
void HelloWorld::loadAchievementsSuccess(int index, int count, CCArray *elementArray){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "loadAchievements Success";
	showResult(&str2, &str1);

	pElements = elementArray;
	gNumOfElm = count;
	gElementFlag = 1;
	CCGreeAchievement *pAchieve = dynamic_cast<CCGreeAchievement *>(elementArray->objectAtIndex(0));
	CCLog("++++++ ID:%s", pAchieve->getId()->getCString());
	CCLog("++++++ Name:%s", pAchieve->getName()->getCString());
	CCLog("++++++ Descript:%s", pAchieve->getDescription()->getCString());
	CCLog("++++++ Score:%d", pAchieve->getScore());
	CCLog("++++++ Unlock:%d", pAchieve->isUnlocked());
	CCLog("++++++ Secret:%d", pAchieve->isSecret());
}
void HelloWorld::loadAchievementsFailure(int responseCode, CCString *response){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "loadAchievements Failure : ";
	str2.append(response->getCString());
	showResult(&str2, &str1);
}
void HelloWorld::lockSuccess(CCGreeAchievement *element){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "lock Success";
	showResult(&str2, &str1);
	gElementFlag = 1;
}
void HelloWorld::lockFailure(CCGreeAchievement *element, int responseCode, CCString *response){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "lock Failure : ";
	str2.append(response->getCString());
	showResult(&str2, &str1);
}
void HelloWorld::unlockSuccess(CCGreeAchievement *element){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "unlock Success";
	showResult(&str2, &str1);
	gElementFlag = 1;
}
void HelloWorld::unlockFailure(CCGreeAchievement *element, int responseCode, CCString *response){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "unlock Failure : ";
	str2.append(response->getCString());
	showResult(&str2, &str1);
}
void HelloWorld::loadAchievementThumbnailSuccess(CCGreeAchievement *achievement, CCImage *img){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "load achievement thumbnail success";
	showResult(&str2, &str1);

}
void HelloWorld::loadAchievementThumbnailFailure(CCGreeAchievement *achievement, int responseCode, CCString *response){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "load achievement thumbnail failure : ";
	str2.append(response->getCString());
	showResult(&str2, &str1);

}


// Leaderboard
void HelloWorld::loadLeaderboardsSuccess(int index, int count, CCArray *leaderboardArray){
	CCLog("++++++ %s %d", __func__, count);
	CCGreeLeaderboard *pLeaderboard = dynamic_cast<CCGreeLeaderboard *>(leaderboardArray->objectAtIndex(0));
	gLeaderboardFlag = 1;
	pLeaderboards = leaderboardArray;	
	std::string str1 = "Callback";
	std::string str2 = "loadLeaderboards Success";
	showResult(&str2, &str1);
}
void HelloWorld::createScoreSuccess(CCGreeLeaderboard *leaderboard){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "createScore Success";
	showResult(&str2, &str1);
}

void HelloWorld::loadLeaderboardThumbnailSuccess(CCGreeLeaderboard *leaderboard, CCImage *img){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "load leaderboard thumbnail success";
	showResult(&str2, &str1);

}
void HelloWorld::loadLeaderboardThumbnailFailure(CCGreeLeaderboard *leaderboard, int responseCode, CCString *response){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "load leaderboard thumbnail failure : ";
	str2.append(response->getCString());
	showResult(&str2, &str1);
}
void HelloWorld::getScoreSuccess(CCGreeLeaderboard *leaderboard, CCArray *scoreArray){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "get score success";
	CCObject *it;
	CCARRAY_FOREACH(scoreArray, it){
		CCGreeScore *score = dynamic_cast<CCGreeScore *>(it);
		str2.append(" ID : ");
		str2.append(score->getId()->getCString());
		str2.append(" Nickname : ");
		str2.append(score->getNickname()->getCString());
		str2.append(" Score(s) : ");
		str2.append(score->getScoreAsString()->getCString());
		CCLog("++++++ Score : %lld\n", score->getScore());
		score->loadThumbnail(2); //HUGE
	}
	showResult(&str2, &str1);
}
void HelloWorld::getScoreFailure(CCGreeLeaderboard *leaderboard, int responseCode, CCString *response){
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "get score failure : ";
	str2.append(response->getCString());
	showResult(&str2, &str1);
}
	
// Leaderboard$Score
void HelloWorld::loadScoreThumbnailSuccess(CCGreeScore *score, CCImage *img)
{
	CCLog("++++++ %s", __func__);
	std::string str1 = "Callback";
	std::string str2 = "load score thumbnail ";
	showResult(&str2, &str1);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Cocos2dx GreePlatform Binding Test", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

	// GreeButton
	pGreeButtonText = CCLabelTTF::create("Log in", "Thonburi", 34);
	pGreeButtonText->setPosition(ccp(size.width - 100, size.height - 40));
	this->addChild(pGreeButtonText, 1);
	CCMenuItemImage *pGree = CCMenuItemImage::create("gree.png", "gree.png", this, menu_selector(HelloWorld::menuGreeButtonCallback));
	pGree->setPosition(ccp(size.width - 100, size.height - 100));
	CCMenu* pGreeMenu = CCMenu::create(pGree, NULL);
	this->addChild(pGreeMenu, 1);
	pGreeMenu->setPosition(CCPointZero);
	pGree->setScaleY(3.0);
	pGree->setScaleX(3.0);		

	// Set Scheduled Func
	this->schedule(schedule_selector(HelloWorld::Func), 1.0);
   
	this->setTouchEnabled(true);
 
    return true;
}

void HelloWorld::Func(float dt){
	CCLog("++++++ %s", __func__);
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// User Information
	if(gThumbFlag == 1){
		CCGreeUser *pUser = CCGreePlatform::getLocalUser();
		dumpUserInfo(pUser);

		CCLabelTTF *pName = CCLabelTTF::create(pUser->getNickname()->getCString(), "Thonburi", 34);
		pName->setPosition(ccp(100, size.height - 300));
		CCLabelTTF *pId = CCLabelTTF::create(pUser->getId()->getCString(), "Thonburi", 34);
		pId->setPosition(ccp(100, size.height - 340));
		CCLabelTTF *pReg = CCLabelTTF::create(pUser->getRegion()->getCString(), "Thonburi", 34);
		pReg->setPosition(ccp(100, size.height - 380));
		CCLabelTTF *pBir = CCLabelTTF::create(pUser->getBirthday()->getCString(), "Thonburi", 34);
		pBir->setPosition(ccp(100, size.height - 420));
		CCLabelTTF *pAge = CCLabelTTF::create(pUser->getAge()->getCString(), "Thonburi", 34);
		pAge->setPosition(ccp(100, size.height - 460));
		//CCLabelTTF *pGra = CCLabelTTF::create(pUser->getUserGrade()->getValue(), "Thonburi", 34);
		//pGra->setPosition(ccp(100, size.height - 500));


		this->addChild(pName, 1);
		this->addChild(pId, 1);
		this->addChild(pReg, 1);
		this->addChild(pBir, 1);
		this->addChild(pAge, 1);

		if(pThumb != NULL){
			CCTexture2D *tex = CCTextureCache::sharedTextureCache()->addUIImage(pThumb, "key_name");
			pIcon = CCSprite::spriteWithTexture(tex);
			pThumb->release(); // declement reference count, lead to autorelease
			pIcon->setPosition(ccp(100, size.height - 600));
			this->addChild(pIcon, 0);
		}
		gThumbFlag = 0;
	}
	// Friend List
	if(gFriendFlag == 1){

		CCLabelTTF *lname[gNumOfFriend];
		CCLabelTTF *lbir[gNumOfFriend];
		CCLabelTTF *lage[gNumOfFriend];
		CCObject *it;
		int i = 0;
		CCLabelTTF *fList = CCLabelTTF::create("Friends List", "Thonburi", 40);
		fList->setPosition(ccp(FRIEND_X_OFFSET, size.height - FRIEND_Y_OFFSET));
		this->addChild(fList, 1);

		CCARRAY_FOREACH(pFriends, it){
			CCGreeUser *user = dynamic_cast<CCGreeUser *>(it);
			dumpUserInfo(user);
			lname[i] = CCLabelTTF::create(user->getNickname()->getCString(), "Thonburi", 30);
			lbir[i] = CCLabelTTF::create(user->getBirthday()->getCString(), "Thonburi", 30);
			lage[i] = CCLabelTTF::create(user->getAge()->getCString(), "Thonburi", 30);
			lname[i]->setPosition(ccp(FRIEND_X_OFFSET, size.height - FRIEND_Y_OFFSET - 50 - i*100));
			lbir[i]->setPosition(ccp(FRIEND_X_OFFSET, size.height - FRIEND_Y_OFFSET - 50 - 30 - i*100));
			lage[i]->setPosition(ccp(FRIEND_X_OFFSET, size.height - FRIEND_Y_OFFSET - 50 - 60 - i*100));
			this->addChild(lname[i], 1);
			this->addChild(lbir[i], 1);
			this->addChild(lage[i], 1);
			i++;
		}
		gFriendFlag = 0;
	}

	// Achievement
	if(gElementFlag == 1){
		gElementFlag = 0;
		showAchievementInfo();
	}


	// Leaderboard
	if(gLeaderboardFlag == 1){
		gLeaderboardFlag = 0;
		showLeaderboardInfo();
		CCObject *it;
		//CCARRAY_FOREACH(pLeaderboards, it){
			//CCGreeLeaderboard *board = dynamic_cast<CCGreeLeaderboad *>(it);
			CCGreeLeaderboard *board = dynamic_cast<CCGreeLeaderboard *>(pLeaderboards->objectAtIndex(1));
			board->createScore(12345678);
			CCLog("++++++ Leaderboard Id : %s\n", board->getId()->getCString());
			CCLog("++++++ Leaderboard Name : %s\n", board->getName()->getCString());
			CCLog("++++++ Leaderboard ThumbnailUrl : %s\n", board->getThumbnailUrl()->getCString());
		
		//}
	}
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event){
	if(pIcon != NULL){
	CCTouch* touch = (CCTouch*)(touches->anyObject());
	CCPoint location = touch->getLocation();
	CCMoveTo *action = CCMoveTo::actionWithDuration(0.5f, ccp(location.x, location.y));
	pIcon->runAction(action);
	}
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
