#ifndef __CC_WEBVIEW_H__
#define __CC_WEBVIEW_H__

#include "CCStdC.h"
#include "cocoa/CCString.h"
#include "cocoa/CCDictionary.h"

#define USING_NS_CC_WEBVIEW  using namespace cocos2d::webview_plugin

#define CREATE_DELEGATE(module) \
    public: \
        static void set##module(CC##module *pDelegate) { s_p##module = pDelegate; } \
        static CC##module *get##module() { return s_p##module; }; \
        static void remove##module(CC##module *pDelegate) { s_p##module = NULL; } \
    private: \
        static CC##module *s_p##module;

using namespace std;

namespace cocos2d { namespace webview_plugin {

class CCWebView;

class CCWebViewDelegate {
	public:
		virtual void callbackFromJS(CCWebView* webview, CCString* message){};
};

class CCWebView : public CCObject {
	public:
		static CCWebView* create();
		void loadUrl(const char* url);
		void evaluateJS(const char* js);
		void setVisibility(bool enable);
		void setRect(int x, int y, int w, int h);
		void destroy();

		void handleCalledFromJS(const char* message);

		CREATE_DELEGATE(WebViewDelegate);
	private:
		CCWebView(void* obj);
		void* mWebView;
};

}} // End of namespace cocos2d::webview_plugin

#endif

