#ifndef __Java_org_cocos2dx_lib_Cocos2dxWebView_H__
#define __Java_org_cocos2dx_lib_Cocos2dxWebView_H__

#include <string.h>
#include <jni.h>

extern "C"
{
    jobject createWebViewJni();
	void setJavascriptIfJni(jobject obj, void *delegate);
    void setWebViewClientJni(jobject obj, void *delegate);
	void loadUrlJni(jobject obj, const char* url, bool transparent);
    void clearCacheJni(jobject obj);
	void evaluateJSJni(jobject obj, const char* js);
	void setVisibilityJni(jobject obj, bool enable);
	void setRectJni(jobject obj, int x, int y, int w, int h);
	void destroyJni(jobject obj);
    void setBannerModeEnableJni(jobject obj, bool enable);
    void setCloseButtonJni(jobject obj, void* delegate, const char* imageName,
                           int x, int y, int w, int h);
    void setUrlSchemeNotFoundMessageJni(jobject obj, const char* message);
}
#endif

