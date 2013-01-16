#include "GreeJniHelper.h"
#include <string.h>
#include <jni.h>

#include "CCDirector.h"
#include "platform/CCImage.h"

#include "CCGreeShareDialog.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.h"

using namespace cocos2d;
using namespace cocos2d::gree_extension;



extern "C" {

	jobject createShareDialogJni(){
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
				jstring dialogType = k.env->NewStringUTF("ShareDialog");
				ret = k.env->CallObjectMethod(helper, k.methodID, context, dialogType);
				k.env->DeleteLocalRef(k.classID);
				k.env->DeleteLocalRef(dialogType);
			}
		}
		return ret;
	}


	void setShareDialogHandlerJni(jobject obj){
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

	static jobject createDefaultBitmapObject(CCImage *img){
		if(img == NULL){
			return NULL;
		}
		unsigned short width = img->getWidth();
		unsigned short height = img->getHeight();
		//int len = img->getDataLen();
		if(width == 0 || height == 0){
			return NULL;
		}
		int *pSrc = (int*)(img->getData());
		if(pSrc == NULL){
			return NULL;
		}

		//convert ABGR -> ARGB
		for(int i = 0; i < width * height; i++){
			unsigned int colorData = *((unsigned int *)pSrc + i);
										*((unsigned int*)pSrc + i) = ((colorData & 0xff00ff00) |
										((colorData & 0x00ff0000) >> 16) |
										((colorData & 0x000000ff) << 16));
		}

		//generate Bitmap object
		JniMethodInfo b;
		jobject config = NULL, bmpObj = NULL;
		if(JniHelper::getStaticMethodInfo(b, "android.graphics.Bitmap$Config", "nativeToConfig", "(I)Landroid/graphics/Bitmap$Config;")){
			config = b.env->CallStaticObjectMethod(b.classID, b.methodID, (6));
			b.env->DeleteLocalRef(b.classID);
			if(config == NULL){
				return NULL;
			}

			if(JniHelper::getStaticMethodInfo(b, "android.graphics.Bitmap", "createBitmap", "([IIILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;")){
				jintArray array = b.env->NewIntArray(width * height);
				b.env->SetIntArrayRegion(array, 0, width * height, pSrc);
				bmpObj = b.env->CallStaticObjectMethod(b.classID, b.methodID, array, width, height, config);
				//Clear intarray
				b.env->DeleteLocalRef(array);
				b.env->DeleteLocalRef(b.classID);
				if(bmpObj == NULL){
					return NULL;
				}
			}
		}
		return bmpObj;
	}

	void setShareDialogParamsJni(jobject obj, CCDictionary *params){
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
					if(!strncmp(GD_SHARE_DIALOG_PARAM_KEY_IMG, pStr, sizeof(GD_SHARE_DIALOG_PARAM_KEY_IMG))){
						// CCimage
						CCImage* img = ((CCImage *)(pElement->getObject()));
						jobject bmpObj = createDefaultBitmapObject(img);
						if(bmpObj == NULL){
							return;
						}
						jstring jStr;
						if(!pStr){
							jStr = t.env->NewStringUTF("");
						}else{
							jStr = t.env->NewStringUTF(pStr);
						}
						m.env->CallObjectMethod(map, m.methodID, jStr, bmpObj);
						m.env->DeleteLocalRef(jStr);
					}else{
						// String
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


	void showShareDialogJni(jobject obj){
		JniMethodInfo t;

		if(JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/gree/NativeThreadHelper", "showDialog", "(Ljava/lang/Object;Ljava/lang/String;)V")){
			jstring dialogType = t.env->NewStringUTF("ShareDialog");
			t.env->CallStaticVoidMethod(t.classID, t.methodID, obj, dialogType);
			t.env->DeleteLocalRef(dialogType);
			t.env->DeleteLocalRef(t.classID);
		}
	}


}
