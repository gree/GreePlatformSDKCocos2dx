#include "jni/JniHelper.h"
#include <string.h>
#include <android/log.h>
#include <jni.h>

#include "CCDirector.h"
#include "CCWebView.h"

#define LOG_TAG "WebViewJni"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define JAVAVM    cocos2d::JniHelper::getJavaVM()

using namespace std;
using namespace cocos2d;
using namespace cocos2d::webview_plugin;

extern "C" {
    static bool getEnv(JNIEnv **env)
    {   
        bool bRet = false;

        do  
        {   
            if (JAVAVM->GetEnv((void**)env, JNI_VERSION_1_4) != JNI_OK)
            {   
                LOGD("Failed to get the environment using GetEnv()");
                break;
            }   

            if (JAVAVM->AttachCurrentThread(env, 0) < 0)
            {   
                LOGD("Failed to get the environment using AttachCurrentThread()");
                break;
            }   

            bRet = true;
        } while (0);    

        return bRet;
    }

	bool getInstanceMethodInfo(JniMethodInfo &methodinfo, jobject &obj, const char *methodName, const char *paramCode){
    	jmethodID methodID = 0;
    	JNIEnv *pEnv = 0;
    	bool bRet = false;
    	do{
        	if(!getEnv(&pEnv)){
        	    break;
        	}
        	jclass classID = pEnv->GetObjectClass(obj);
        	methodID = pEnv->GetMethodID(classID, methodName, paramCode);
        	if(methodID == NULL){
            	CCLog("Failed to get method id of %s", methodName);
            	break;
       		}
        	methodinfo.classID = classID;
        	methodinfo.env = pEnv;
        	methodinfo.methodID = methodID;

        	bRet = true;
    	}while(0);
    	return bRet;
	}

	static jobject sContext = NULL;

	jobject createWebViewJni(){
		JniMethodInfo t;
		jobject ret = NULL;
		if(JniHelper::getMethodInfo(t, "org/cocos2dx/lib/gree/webview/Cocos2dxWebView", "<init>", "()V")){
			ret = t.env->NewObject(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
            ret = t.env->NewGlobalRef(ret);
		}
		return ret;
	}
	void setJavascriptIfJni(jobject obj, void *delegate){
		JniMethodInfo t;
		if(getInstanceMethodInfo(t, obj, "setJavascriptIf", "(J)V")){
			t.env->CallVoidMethod(obj, t.methodID, delegate);
			t.env->DeleteLocalRef(t.classID);
		}
	}
    
    void setWebViewClientJni(jobject obj, void *delegate){
        JniMethodInfo t;
		if(getInstanceMethodInfo(t, obj, "setWebViewClient", "(J)V")){
			t.env->CallVoidMethod(obj, t.methodID, delegate);
			t.env->DeleteLocalRef(t.classID);
		}
    }

	void loadUrlJni(jobject obj, const char *url){
		JniMethodInfo t;
		if(getInstanceMethodInfo(t, obj, "loadURL", "(Ljava/lang/String;)V")){
			jstring jUrl;
			if(!url){
				jUrl = t.env->NewStringUTF("");
			}else{
				jUrl = t.env->NewStringUTF(url);
			}
			t.env->CallVoidMethod(obj, t.methodID, jUrl);
			t.env->DeleteLocalRef(jUrl);
			t.env->DeleteLocalRef(t.classID);
		}
	}

	void evaluateJSJni(jobject obj, const char *js){
		JniMethodInfo t;
		if(getInstanceMethodInfo(t, obj, "evaluateJS", "(Ljava/lang/String;)V")){
			jstring jJS;
			if(!js){
				jJS = t.env->NewStringUTF("");
			}else{
				jJS = t.env->NewStringUTF(js);
			}
			t.env->CallVoidMethod(obj, t.methodID, jJS);
			t.env->DeleteLocalRef(jJS);
			t.env->DeleteLocalRef(t.classID);
		}
	}

	void setVisibilityJni(jobject obj, bool enable){
		JniMethodInfo t;
		if(getInstanceMethodInfo(t, obj, "setVisibility", "(Z)V")){
			t.env->CallVoidMethod(obj, t.methodID, enable);
			t.env->DeleteLocalRef(t.classID);
		}
	}

	void setRectJni(jobject obj, int x, int y, int w, int h){
		JniMethodInfo t;
		if(getInstanceMethodInfo(t, obj, "setMargins", "(IIII)V")){
			t.env->CallVoidMethod(obj, t.methodID, x, y, w, h);
			t.env->DeleteLocalRef(t.classID);
		}
	}

	void destroyJni(jobject obj){
		JniMethodInfo t;
		if(getInstanceMethodInfo(t, obj, "destroy", "()V")){
			t.env->CallVoidMethod(obj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
            t.env->DeleteGlobalRef(obj);
		}
	}
    
    void setBannerModeEnableJni(jobject obj, bool enable){
		JniMethodInfo t;
		if(getInstanceMethodInfo(t, obj, "setBannerModeEnable", "(Z)V")){
			t.env->CallVoidMethod(obj, t.methodID, enable);
			t.env->DeleteLocalRef(t.classID);
		}
	}

    // from Cocos2dxWebView
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_webview_Cocos2dxWebView_nativeCalledFromJS(JNIEnv *env, jobject obj, jlong delegate, jstring message){
        if(delegate){
            const char* str = env->GetStringUTFChars(message, 0);
            CCWebView *webView = (CCWebView*)delegate; 
            webView->handleCalledFromJS(str);
            env->ReleaseStringUTFChars(message, str);
        }
    }
    
    JNIEXPORT bool JNICALL Java_org_cocos2dx_lib_gree_webview_Cocos2dxWebView_nativeShouldOverrideUrlLoading(JNIEnv *env, jobject obj, jlong delegate, jstring url){
        bool ret = false;
        if (delegate) {
            const char* str = env->GetStringUTFChars(url, 0);
            CCWebView *webView = (CCWebView*)delegate;
            ret = webView->handleShouldOverrideUrlLoading(str);
            env->ReleaseStringUTFChars(url, str);
        }
        return ret; //ret;
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_webview_Cocos2dxWebView_nativeOnPageFinished(JNIEnv *env, jobject obj, jlong delegate, jstring url){
        if (delegate) {
            const char* str = env->GetStringUTFChars(url, 0);
            CCWebView *webView = (CCWebView*)delegate;
            webView->handleOnPageFinished(str);
            env->ReleaseStringUTFChars(url, str);
        }
    }

}