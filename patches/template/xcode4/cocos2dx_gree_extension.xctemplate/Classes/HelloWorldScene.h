#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-gree-ext.h"


USING_NS_CC;
USING_NS_CC_GREE_EXT;

class HelloWorld : public cocos2d::CCLayer, public cocos2d::gree_extension::CCGreePlatformDelegate
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    void menuGreeButtonCallback(CCObject *pSender);
    void menuUserCallback(CCObject *pSender);
    void menuFriendCallback(CCObject *pSender);
    void menuPaymentCallback(CCObject *pSender);
    void menuShareCallback(CCObject *pSender);
    void menuInviteCallback(CCObject *pSender);
    void menuLogoutCallback(CCObject *pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);

    void dumpUserInfo(CCGreeUser *user);
    void Func(float dt);
    void showResult(std::string* str1, std::string* str2);
    void authorizeAuthorized();
    void loadThumbnailSuccess(CCGreeUser* user, CCImage *img);
    void loadFriendsSuccess(CCGreeUser *user, int index, int count, CCArray *userArray);
    void paymentRequestSuccess(CCGreePayment *payment, int responseCode, CCString* paymentId);
    void paymentRequestCancel(CCGreePayment *payment, int responseCode, CCString* paymentId);
    void paymentRequestFailure(CCGreePayment *payment, int responsCode, CCString *paymentID, CCString *response);
    void shareDialogOpened(CCGreeShareDialog *dialog);
    void shareDialogCompleted(CCGreeShareDialog *dialog, CCArray *userArray);
    void shareDialogClosed(CCGreeShareDialog *dialog);
    void inviteDialogOpened(CCGreeInviteDialog *dialog);
    void inviteDialogCompleted(CCGreeInviteDialog *dialog, CCArray *userArray);
    void inviteDialogClosed(CCGreeInviteDialog *dialog);
};

#endif // __HELLOWORLD_SCENE_H__
