#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CCWebView.h"

USING_NS_CC;

USING_NS_CC_WEBVIEW;

class HelloWorld : public cocos2d::CCLayer, public cocos2d::webview_plugin::CCWebViewDelegate
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);

    void showResult(std::string* str1, std::string* str2);
	void callbackFromJS(CCWebView *webview, CCString *message);
};

#endif // __HELLOWORLD_SCENE_H__
