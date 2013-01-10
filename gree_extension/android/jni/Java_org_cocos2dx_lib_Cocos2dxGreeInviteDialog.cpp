#include "GreeJniHelper.h"
#include <string.h>
#include <jni.h>

#include "CCDirector.h"

#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.h"

using namespace cocos2d;
using namespace cocos2d::gree_extension;



extern "C" {

jobject createInviteDialogJni_(){
	JniMethodInfo t;
	jobject ret = NULL;
	if(JniHelper::getMethodInfo(t, "net/gree/asdk/api/ui/InviteDialog", "<init>", "(Landroid/content/Context;)V")){
		jobject context = getPlatformContext();
		if(context == NULL){
			return ret;
		}
		ret = t.env->NewObject(t.classID, t.methodID, context);
		t.env->DeleteLocalRef(t.classID);
	}
	return ret;
	}


	jobject createInviteDialogJni__(){
		JniMethodInfo t;
		jobject ret = NULL;
		if(JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/gree/NativeThreadHelper", "createInviteDialog", "(Landroid/content/Context;)Lnet/gree/asdk/api/ui/InviteDialog;")){
			jobject context = getPlatformContext();
			if(context == NULL){
				return ret;
			}
			ret = t.env->CallStaticObjectMethod(t.classID, t.methodID, context);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}

	jobject createInviteDialogJni(){
		JniMethodInfo t;
		jobject ret = NULL;
		if(JniHelper::getMethodInfo(t, "org/cocos2dx/lib/gree/NativeThreadHelper", "<init>", "()V")){
			jobject helper = t.env->NewObject(t.classID, t.methodID);
			if(helper == NULL){
				CCLog("Cannot create object %s", __func__);
				return ret;
			}
			t.env->DeleteLocalRef(t.classID);
			JniMethodInfo k;
			if(GreeJniHelper::getInstanceMethodInfo(k, helper, "createDialog", "(Landroid/content/Context;Ljava/lang/String;)Ljava/lang/Object;")){
				jobject context = getPlatformContext();
				jstring dialogType = k.env->NewStringUTF("InviteDialog");
				ret = k.env->CallObjectMethod(helper, k.methodID, context, dialogType);
				k.env->DeleteLocalRef(k.classID);
				k.env->DeleteLocalRef(dialogType);
			}
		}
		return ret;
	}


	void setInviteDialogHandlerJni(jobject obj){
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "setHandler", "(Landroid/os/Handler;)V")){
			JniMethodInfo h;
			if(JniHelper::getStaticMethodInfo(h, "org/cocos2dx/lib/gree/Cocos2dxGreePlatform", "getPlatformUIHandler", "()Landroid/os/Handler;")){
				jobject handler = h.env->CallStaticObjectMethod(h.classID, h.methodID);
				if(handler == NULL){
					CCLog("Cannot get handler object %s", __func__);
					return;
				}
				h.env->DeleteLocalRef(h.classID);
				t.env->CallVoidMethod(obj, t.methodID, handler);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}

	void setInviteDialogParamsJni(jobject obj, CCDictionary *params){
		JniMethodInfo t;
		if(params == NULL){
			return;
		}
		if(JniHelper::getMethodInfo(t, "java/util/TreeMap", "<init>", "()V")){
			jobject map = t.env->NewObject(t.classID, t.methodID);
			if(map == NULL){
				CCLog("Cannot create new TreeMap objeect in %S", __func__);
				return;
			}
			JniMethodInfo m;
			if(GreeJniHelper::getInstanceMethodInfo(m, map, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;")){
				CCDictElement* pElement = NULL;
				CCDICT_FOREACH(params, pElement){
					const std::string str = pElement->getStrKey();
					const char *pStr = str.c_str();
					const char *pVal  = ((CCString *)(pElement->getObject()))->getCString();
					jstring jStr, jVal;
					if(!pStr){
						jStr = t.env->NewStringUTF("");
					}else{
						jStr = t.env->NewStringUTF(pStr);
					}
					if(!pVal){
						jVal = t.env->NewStringUTF("");
					}else{
						jVal = t.env->NewStringUTF(pVal);
					}
					m.env->CallObjectMethod(map, m.methodID, jStr, jVal);
					m.env->DeleteLocalRef(jStr);
					m.env->DeleteLocalRef(jVal);
				}
				m.env->DeleteLocalRef(m.classID);
			

				JniMethodInfo l;
				if(GreeJniHelper::getInstanceMethodInfo(l, obj, "setParams", "(Ljava/util/TreeMap;)V")){
					l.env->CallVoidMethod(obj, l.methodID, map);
					l.env->DeleteLocalRef(l.classID);
				}
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}

	void showInviteDialogJni(jobject obj){
		JniMethodInfo t;

		if(JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/gree/NativeThreadHelper", "showDialog", "(Ljava/lang/Object;Ljava/lang/String;)V")){
			jstring dialogType = t.env->NewStringUTF("InviteDialog");
			t.env->CallStaticVoidMethod(t.classID, t.methodID, obj, dialogType);
			t.env->DeleteLocalRef(dialogType);
			t.env->DeleteLocalRef(t.classID);
		}
	}


}
