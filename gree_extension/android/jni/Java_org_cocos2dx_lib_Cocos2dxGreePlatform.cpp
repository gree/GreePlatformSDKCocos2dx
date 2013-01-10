#include "GreeJniHelper.h"
#include <string.h>
#include <jni.h>

#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.h"

#include "CCDirector.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::gree_extension;

extern "C" {
	static jobject sContext = NULL;

	std::string getLocalUserIdJni(){
		JniMethodInfo t;
		std::string ret;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/GreePlatform", "getLocalUserId", "()Ljava/lang/String;")){
			jstring userId = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);

			t.env->DeleteLocalRef(t.classID);
			//CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
			//ret->autorelease();
			const char* str = t.env->GetStringUTFChars(userId, 0);
			ret = str;
			t.env->ReleaseStringUTFChars(userId, str);
		}
		return ret; 
	}

	jobject getLocalUserJni(){
		JniMethodInfo t;
		jobject user;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/GreePlatform", "getLocalUser", "()Lnet/gree/asdk/api/GreeUser;")){
			user = t.env->CallStaticObjectMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return user;
	}

	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_Cocos2dxGreePlatform_nativeSetContext(JNIEnv *env, jobject obj, jobject context){
		sContext = (jobject)env->NewGlobalRef(context);
	}

	jobject getPlatformContext(){
		return sContext;
	}


}

