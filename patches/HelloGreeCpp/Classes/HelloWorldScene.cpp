#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#define FRIEND_X_OFFSET (300)
#define FRIEND_Y_OFFSET (480)

using namespace cocos2d;
using namespace CocosDenshion;

CCLabelTTF* pGreeButtonText;
CCSprite* pSprite;

void HelloWorld::menuGreeButtonCallback(CCObject *pSender){
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

void HelloWorld::showResult(std::string* str1, std::string* str2){
	CCMessageBox(str1->c_str(), str2->c_str());	
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

    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
