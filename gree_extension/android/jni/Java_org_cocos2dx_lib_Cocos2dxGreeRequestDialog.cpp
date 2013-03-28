#include "GreeJniHelper.h"
#include <string.h>
#include <jni.h>

#include "CCDirector.h"

#include "CCGreeRequestDialog.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.h"

using namespace cocos2d;
using namespace cocos2d::gree_extension;



extern "C" {

	jobject createRequestDialogJni(){
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
				jstring dialogType = k.env->NewStringUTF("RequestDialog");
				ret = k.env->CallObjectMethod(helper, k.methodID, context, dialogType);
				k.env->DeleteLocalRef(k.classID);
				k.env->DeleteLocalRef(dialogType);
			}
		}
		return ret;
	}

#if 0 // Obsolete
	void setRequestDialogHandlerJni(jobject obj){
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "setHandler", "(Landroid/os/Handler;)V")){
			JniMethodInfo h;
			if(JniHelper::getStaticMethodInfo(h, "org/cocos2dx/lib/gree/Cocos2dxGreePlatform", "getInviteDialogHandler", "()Landroid/os/Handler;")){
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
#endif
	void setRequestDialogHandlerJni(jobject obj, void* delegate){
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/gree/NativeThreadHelper", "setHandler", "(Landroid/content/Context;Ljava/lang/Object;Ljava/lang/String;J)V")){
			jobject context = getPlatformContext();
			jstring dialogType = t.env->NewStringUTF("RequestDialog");
			t.env->CallStaticVoidMethod(t.classID, t.methodID, context, obj, dialogType, delegate);
			t.env->DeleteLocalRef(dialogType);
			t.env->DeleteLocalRef(t.classID);
		}
	}

	void setRequestDialogParamsJni(jobject obj, CCDictionary *params){
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
					jstring jStr;
					if(!pStr){
						jStr = t.env->NewStringUTF("");
					}else{
						jStr = t.env->NewStringUTF(pStr);
					}
					if(!strncmp(GD_REQUEST_DIALOG_PARAM_KEY_TITLE, pStr, sizeof(GD_REQUEST_DIALOG_PARAM_KEY_TITLE)) || 
						!strncmp(GD_REQUEST_DIALOG_PARAM_KEY_BODY, pStr, sizeof(GD_REQUEST_DIALOG_PARAM_KEY_BODY)) ||
						!strncmp(GD_REQUEST_DIALOG_PARAM_KEY_LISTTYPE, pStr, sizeof(GD_REQUEST_DIALOG_PARAM_KEY_LISTTYPE)) ||
						!strncmp(GD_REQUEST_DIALOG_PARAM_KEY_EXPIRETIME, pStr, sizeof(GD_REQUEST_DIALOG_PARAM_KEY_EXPIRETIME))){
						// title, body, list_type, expire_time
						CCString *val = ((CCString *)(pElement->getObject()));
						if(val == NULL){
							return;
						}
						const char *pVal  = val->getCString();
						jstring jVal;
						if(!pVal){
							jVal = t.env->NewStringUTF("");
						}else{
							jVal = t.env->NewStringUTF(pVal);
						}
						m.env->CallObjectMethod(map, m.methodID, jStr, jVal);
						m.env->DeleteLocalRef(jVal);
					}else if(!strncmp(GD_REQUEST_DIALOG_PARAM_KEY_TOUSERID, pStr, sizeof(GD_REQUEST_DIALOG_PARAM_KEY_TOUSERID))){
						//touserid
						CCArray *array = ((CCArray *)(pElement->getObject()));
						if(array == NULL){
							return;
						}
						jclass jcl = JniHelper::getClassID("java/lang/String");
						if(jcl == NULL){
							return;
						}
						jobjectArray jarry = t.env->NewObjectArray(array->count(), jcl, NULL);
						CCObject *it;
						int i = 0;
						CCARRAY_FOREACH(array, it){
							CCString *val = dynamic_cast<CCString *>(it);
							const char *pVal = val->getCString();
							jstring jVal;
							if(!pVal){
								jVal = t.env->NewStringUTF("");
							}else{
								jVal = t.env->NewStringUTF(pVal);
							}
							t.env->SetObjectArrayElement(jarry, i, jVal);
							t.env->DeleteLocalRef(jVal);
							i++;
						}
						m.env->CallObjectMethod(map, m.methodID, jStr, jarry);
						m.env->DeleteLocalRef(jarry);
					}else if(!strncmp(GD_REQUEST_DIALOG_PARAM_KEY_ATTRS, pStr, sizeof(GD_REQUEST_DIALOG_PARAM_KEY_ATTRS))){
					}
					m.env->DeleteLocalRef(jStr);
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


	void showRequestDialogJni(jobject obj){
		JniMethodInfo t;

		if(JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/gree/NativeThreadHelper", "showDialog", "(Ljava/lang/Object;Ljava/lang/String;)V")){
			jstring dialogType = t.env->NewStringUTF("RequestDialog");
			t.env->CallStaticVoidMethod(t.classID, t.methodID, obj, dialogType);
			t.env->DeleteLocalRef(dialogType);
			t.env->DeleteLocalRef(t.classID);
		}
	}
}
