#include "GreeJniHelper.h"
#include <jni.h>

using namespace cocos2d;
using namespace cocos2d::gree_extension;

extern "C" {
	void loadCodeJni(){
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/FriendCode", "loadCode", "(Lnet/gree/asdk/api/FriendCode$CodeListener;)V")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeCodeListener", "<init>", "(I)V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID, (int)fTypeLoadCode);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}
				t.env->CallStaticVoidMethod(t.classID, t.methodID, listener);
				l.env->DeleteLocalRef(l.classID);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}

	bool requestCodeJni(const char *expireTime){
		bool ret = false;
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/FriendCode", "requestCode", "(Ljava/lang/String;Lnet/gree/asdk/api/FriendCode$CodeListener;)Z")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeCodeListener", "<init>", "(I)V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID, (int)fTypeRequestCode);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return ret;
				}
				jstring jStr;
				if(!expireTime){
					jStr = t.env->NewStringUTF("");
				}else{
					jStr = t.env->NewStringUTF(expireTime);
				}
				ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, jStr, listener);
				l.env->DeleteLocalRef(l.classID);
				t.env->DeleteLocalRef(jStr);
			}
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}

	void deleteCodeJni(){
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/FriendCode", "deleteCode", "(Lnet/gree/asdk/api/FriendCode$SuccessListener;)V")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeFriendCodeSuccessListener", "<init>", "(JI)V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID, (unsigned long long)0, (int)fTypeDeleteCode);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}
				t.env->CallStaticVoidMethod(t.classID, t.methodID, listener);
				l.env->DeleteLocalRef(l.classID);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}


	void verifyCodeJni(const char* code){
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/FriendCode", "verifyCode", "(Ljava/lang/String;Lnet/gree/asdk/api/FriendCode$SuccessListener;)V")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeFriendCodeSuccessListener", "<init>", "(JI)V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID, (unsigned long long)0, (int)fTypeVerifyCode);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}
				jstring jStr;
				if(!code){
					jStr = t.env->NewStringUTF("");
				}else{
					jStr = t.env->NewStringUTF(code);
				}
				t.env->CallStaticVoidMethod(t.classID, t.methodID, jStr, listener);
				l.env->DeleteLocalRef(l.classID);
				t.env->DeleteLocalRef(jStr);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}

	void loadFriendIdsJni(int startIndex, int count){
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/FriendCode", "loadFriends", "(IILnet/gree/asdk/api/FriendCode$EntryListGetListener;)V")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeEntryListGetListener", "<init>", "()V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}
				t.env->CallStaticVoidMethod(t.classID, t.methodID, startIndex, count, listener);
				l.env->DeleteLocalRef(l.classID);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}

	void loadOwnerJni(){
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/FriendCode", "loadOwner", "(Lnet/gree/asdk/api/FriendCode$OwnerGetListener;)V")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeOwnerGetListener", "<init>", "()V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}
				t.env->CallStaticVoidMethod(t.classID, t.methodID, listener);
				l.env->DeleteLocalRef(l.classID);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}


	std::string getCodeJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getCode", "()Ljava/lang/String;")){
			jstring jstr = (jstring)t.env->CallObjectMethod(obj, t.methodID);
			const char* str = NULL;
			if(jstr != NULL){
				str = t.env->GetStringUTFChars(jstr, 0);
				ret = str;
				t.env->ReleaseStringUTFChars(jstr, str);
			}
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}

	std::string getExpireTimeJni(jobject obj){	
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getExpireTime", "()Ljava/lang/String;")){
			jstring jstr = (jstring)t.env->CallObjectMethod(obj, t.methodID);
			const char* str = NULL;
			if(jstr != NULL){
				str = t.env->GetStringUTFChars(jstr, 0);
				ret = str;
				t.env->ReleaseStringUTFChars(jstr, str);
			}
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}

	std::string getUserIdFromGreeDataJni(jobject obj){	
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getUserId", "()Ljava/lang/String;")){
			jstring jstr = (jstring)t.env->CallObjectMethod(obj, t.methodID);
			const char* str = NULL;
			if(jstr != NULL){
				str = t.env->GetStringUTFChars(jstr, 0);
				ret = str;
				t.env->ReleaseStringUTFChars(jstr, str);
			}
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}
}

