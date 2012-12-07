#include "GreeJniHelper.h"
#include <string.h>
#include <jni.h>

#include "CCDirector.h"
#include "cocoa/CCDictionary.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.h"

using namespace cocos2d;
using namespace cocos2d::gree_extension;



extern "C" {

bool launchJni(){
	JniMethodInfo t;
	bool ret;
	if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/ui/Dashboard", "launch", "(Landroid/content/Context;)Z")){
		jobject context = getPlatformContext();
		if(context == NULL){
			return false;
		}
		ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, context);
		t.env->DeleteLocalRef(t.classID);
	}
	return ret;
	}


	bool launchWithParamJni(int type, CCDictionary *params){
		JniMethodInfo t;
		jobject map = NULL;
		if(params != NULL){
			if(JniHelper::getMethodInfo(t, "java/util/TreeMap", "<init>", "()V")){
				map = t.env->NewObject(t.classID, t.methodID);
				if(map == NULL){
					CCLog("Cannot create new TreeMap objeect in %S", __func__);
					return false;
				}

				JniMethodInfo m;
				if(GreeJniHelper::getInstanceMethodInfo(m, map, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;")){
					CCDictElement* pElement = NULL;
					CCDICT_FOREACH(params, pElement){
						const std::string str = pElement->getStrKey();
						const char *pStr = str.c_str();
						const char *pVal  = ((CCString *)(pElement->getObject()))->getCString();
						jstring jStr;
						jstring jVal;
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
				}
			}
			t.env->DeleteLocalRef(t.classID);
		}

		JniMethodInfo l;
		if(JniHelper::getStaticMethodInfo(l, "net/gree/asdk/api/ui/Dashboard", "launch", "(Landroid/content/Context;ILjava/util/TreeMap;)Z")){
			jobject context = getPlatformContext();
			if(context == NULL){
				return false;
			}
			l.env->CallStaticBooleanMethod(l.classID, l.methodID, context, type, map);
				
			l.env->DeleteLocalRef(l.classID);
		}
		return true;
	}
}
