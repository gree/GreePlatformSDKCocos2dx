#include "CCWebView.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxWebView.h"

#include "CCEGLView.h"
#include "CCDirector.h"

namespace cocos2d { namespace webview_plugin {

CCWebViewDelegate *CCWebView::s_pWebViewDelegate = NULL;

CCWebView::CCWebView(void* obj){
	mWebView = obj;
}

CCWebView* CCWebView::create(){
	jobject obj = createWebViewJni();
	CCWebView* webview = NULL;
	if(obj != NULL){
		webview = new CCWebView((void*)obj);
		setJavascriptIfJni(obj, webview);
        setWebViewClientJni(obj, webview);
		webview->autorelease();
		webview->retain();
	}
	return webview;
}

void CCWebView::loadUrl(const char* url){
	if(mWebView != NULL){
		loadUrlJni((jobject)mWebView, url);
	}
}

CCString* CCWebView::evaluateJS(const char* js){
	if(mWebView != NULL){
		evaluateJSJni((jobject)mWebView, js);
	}
    return NULL;
}

void CCWebView::setVisibility(bool enable){
	if(mWebView != NULL){
		setVisibilityJni((jobject)mWebView, enable);
	}
}

void CCWebView::setRect(int x, int y, int w, int h){
	if(mWebView != NULL){
        CCSize designSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize();
        CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
        float scale = frameSize.width / designSize.width;
        setRectJni((jobject)mWebView, scale * x, 1 + scale * y + (frameSize.height - designSize.height * scale) / 2,
                   scale * w, scale * h);
	}
}

void CCWebView::destroy(){
	if(mWebView != NULL){
		destroyJni((jobject)mWebView);
	}
}

void CCWebView::handleCalledFromJS(const char *message){
	CCWebViewDelegate *delegate = CCWebView::getWebViewDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(message);
		str->autorelease();
		delegate->callbackFromJS(this, str);
	}
}
    
bool CCWebView::handleShouldOverrideUrlLoading(const char *url) {
    CCWebViewDelegate *delegate = CCWebView::getWebViewDelegate();
    if (delegate != NULL) {
        CCString *str = CCString::create(url);
        return delegate->shouldOverrideUrlLoading(this, str);
    }
    return false;
}
    
void CCWebView::handleOnPageFinished(const char *url) {
    CCWebViewDelegate *delegate = CCWebView::getWebViewDelegate();
    if (delegate != NULL) {
        CCString *str = CCString::create(url);
        delegate->onPageFinished(this, str);
    }
}
    
void CCWebView::setBannerModeEnable(bool enable) {
    if (mWebView != NULL) {
        setBannerModeEnableJni((jobject)mWebView, enable);
    }
}

}} // End of namespae cocos2d::webview_plugin
