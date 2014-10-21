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

#define CCWebView_FullScreenMode_enabled 1

using namespace std;

namespace cocos2d { namespace webview_plugin {

class CCWebView;

class CCWebViewDelegate {
	public:
		virtual void callbackFromJS(CCWebView* webview, CCString* message){};
        virtual bool shouldOverrideUrlLoading(CCWebView* webview, CCString* url){return false;};
		virtual void onPageFinished(CCWebView* webview, CCString* url){};
        virtual void onLoadError(CCWebView* webview, CCString* url){};
};

class CCWebView : public CCObject {
	public:
		static CCWebView* create(bool fullScreenMode = false);
		void loadUrl(const char* url, bool transparent = false);
        void loadHtml(const char *filepath, bool transparent = false);
        void clearCache();
    
        // AndroidとiOSでJS実行の仕様が異なる。
        // iOSはCCStringを返すが、Androidではwindow.Cocos2dx.call(%s)でdelegate経由で結果を受け取る
		CCString* evaluateJS(const char* js);
		void setVisibility(bool enable);
		void setRect(int x, int y, int w, int h);
		void destroy();

		void handleCalledFromJS(const char* message);
        bool handleShouldOverrideUrlLoading(const char* url);
        void handleOnPageFinished(const char* url);
        void handleOnLoadError(const char* url);
        // クリックした時、ブラウザを開くようにする
        void setBannerModeEnable(bool enable);
        void setCloseButton(const char* imagePath, int x, int y, int w, int h);
        // 指定したURLスキーマが見つからなかった場合のメッセージ(Android用)
        void setUrlSchemeNotFoundMessage(const char* message);

        // バウンス時のエフェクトや、iPadで発生する不自然なボーダーを消す
        void disableEffect();

        // この下で定義された変数などはPrivateになる
		CREATE_DELEGATE(WebViewDelegate);
    
	private:
		CCWebView(void* obj);
		void* mWebView;
        void* mCloseButton;
        // m_fullScreenModeは、フルスクリーンモードにするためのフラグ
        // iPadの表示崩れに対応するために実装
        // フルスクリーンモードの時に、setRectを呼ぶとデバイスの設定が無視されてフルスクリーンになる
        // フルスクリーンモードの時に、setCloseButtonを呼ぶと、cocos座標の左上が、デバイス座標の左上に移動する
        bool m_fullScreenMode;
};

}} // End of namespace cocos2d::webview_plugin

#endif

