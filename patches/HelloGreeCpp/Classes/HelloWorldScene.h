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

    void menuGreeButtonCallback(CCObject *pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

private:
	void showResult(std::string* str1, std::string* str2);
};

#endif // __HELLOWORLD_SCENE_H__
