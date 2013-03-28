#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCLabelTTF* pGreeButtonText;

CCSprite* pSprite;
CCSprite* pIcon = NULL;

#define FRIEND_X_OFFSET (100)
#define FRIEND_Y_OFFSET (100)

void HelloWorld::showResult(std::string* str1, std::string* str2){
    CCMessageBox(str1->c_str(), str2->c_str());
}

CCWebView *pWebView = NULL;

void HelloWorld::callbackFromJS(CCWebView *webview, CCString *message){
    CCLog("++++++++++callbackFromJS %s", message->getCString());
	std::string str1 = "Callback";
	std::string str2 = "Message From JS";
	showResult(&str2, &str1);
	pWebView->destroy();
}


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
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

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
    
    //CCWebView Test 
	CCWebView::setWebViewDelegate(this);
    pWebView = CCWebView::create();
    pWebView->setRect(100, 100, size.width - 110, size.height - 20);
    pWebView->setVisibility(true);

    pWebView->loadUrl("http://www.yahoo.co.jp");
    pWebView->evaluateJS(
                             "window.addEventListener('load', function() {"
                             "   window.Cocos2dx = {"
                             "       call:function(msg) {"
                             "           var iframe = document.createElement('IFRAME');"
                             "           iframe.setAttribute('src', 'cocos2dx:' + msg);"
                             "           document.documentElement.appendChild(iframe);"
                             "           iframe.parentNode.removeChild(iframe);"
                             "           iframe = null;"
                             "       }"
                             "   }"
                             "}, false);");
    pWebView->evaluateJS(
     "window.addEventListener('load', function() {"
     "   window.addEventListener('click', function() {"
     "       Cocos2dx.call('clicked');"
     "   }, false);"
     "}, false);");    

    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
