#include "GreeJniHelper.h"
#include <string.h>
#include <jni.h>

#include "CCDirector.h"

#include "CCGreePayment.h"

#define JAVAVM    cocos2d::JniHelper::getJavaVM()

#define ON_DELEGATE(type, func, ...) CCLog("++++++ %s", __func__); \
	type *pType = (type *)delegate; \
	if(pType != NULL){ \
	pType->func(__VA_ARGS__); \
	}

using namespace cocos2d;
using namespace cocos2d::gree_extension;
extern  "C" {
static bool getEnv(JNIEnv **env){
	bool bRet = false;

	do{
		if (JAVAVM->GetEnv((void**)env, JNI_VERSION_1_4) != JNI_OK){
 			CCLog("Failed to get the environment using GetEnv()");
 			break;
 		}
 
		if (JAVAVM->AttachCurrentThread(env, 0) < 0){
 			CCLog("Failed to get the environment using AttachCurrentThrea    d()");
			break;
		}

		bRet = true;
	} while (0);

	return bRet;
}
	
// Payment Item
	jobject createPaymentItemJni(const char *itemId, const char* itemName, double unitPrice, int quantity){
		JniMethodInfo t;
		jobject item = NULL;
		if(JniHelper::getMethodInfo(t, "net/gree/asdk/api/wallet/PaymentItem", "<init>", "(Ljava/lang/String;Ljava/lang/String;DI)V")){
				item = t.env->NewObject(t.classID, t.methodID, t.env->NewStringUTF(itemId), t.env->NewStringUTF(itemName), unitPrice, quantity);
				if(item == NULL){
					CCLog("Cannot create new object in %s", __func__);
					return item;
				}
		}
		return item;
	}

	void setImageUrlJni(jobject obj, const char *url){
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "setImageUrl", "(Ljava/lang/String;)V")){
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

	void setDescriptionJni(jobject obj, const char *desc){
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "setDescription", "(Ljava/lang/String;)V")){
			jstring jDesc;
			if(!desc){
				jDesc = t.env->NewStringUTF("");
			}else{
				jDesc = t.env->NewStringUTF(desc);
			}
			t.env->CallVoidMethod(obj, t.methodID, jDesc);
			t.env->DeleteLocalRef(jDesc);
			t.env->DeleteLocalRef(t.classID);
		}
	}


	std::string getItemIdJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getItemId", "()Ljava/lang/String;")){
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
			

	std::string getItemNameJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getItemName", "()Ljava/lang/String;")){
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

	double getUnitPriceJni(jobject obj){
		JniMethodInfo t;
		double ret = -1;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getUnitPrice", "()D")){
			ret = t.env->CallDoubleMethod(obj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}

	int getQuantityJni(jobject obj){
		JniMethodInfo t;
		int ret = -1;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getQuantity", "()I")){
			ret = t.env->CallIntMethod(obj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}


	std::string getImageUrlJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getImageUrl", "()Ljava/lang/String;")){
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

	std::string getDescription(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getDescription", "()Ljava/lang/String;")){
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
			

// Payment
	jobject createPaymentJni(const char *message, CCArray *items){
		JniMethodInfo t;
		jobject payment = NULL;
		if(JniHelper::getMethodInfo(t, "java/util/ArrayList", "<init>", "()V")){
			jobject list = t.env->NewObject(t.classID, t.methodID);
			if(list == NULL){
				CCLog("Cannot create new List object in %s", __func__);
				return payment;
			}
			//Call java add method
			JniMethodInfo l;
			if(GreeJniHelper::getInstanceMethodInfo(l, list, "add", "(Ljava/lang/Object;)Z")){ 
				CCObject *it;
				CCARRAY_FOREACH(items, it){
					CCGreePaymentItem *item = dynamic_cast<CCGreePaymentItem *>(it);
					jobject paymentItem = item->getPaymentItemObject();

					bool ret = l.env->CallBooleanMethod(list, l.methodID, paymentItem);
				}
				l.env->DeleteLocalRef(l.classID);
			}else{
				CCLog("Cannot add element %s", __func__);
				return NULL;
			}
			JniMethodInfo k;
			if(JniHelper::getMethodInfo(k, "net/gree/asdk/api/wallet/Payment", "<init>", "(Ljava/lang/String;Ljava/util/List;)V")){
				payment = k.env->NewObject(k.classID, k.methodID, k.env->NewStringUTF(message), list);
				if(payment == NULL){
					CCLog("Cannot create new Payment object in %s", __func__);
					return payment;
				}
			}
		}
		return payment;
	}



	void setPaymentHandlerJni(jobject obj, void *delegate){
		//SetHandler
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "setHandler", "(Landroid/os/Handler;)Lnet/gree/asdk/api/wallet/Payment;")){
			JniFieldInfo k;
			if(GreeJniHelper::getStaticFieldInfo(k, "org/cocos2dx/lib/gree/Cocos2dxGreePlatform", "sHandler", "Lorg/cocos2dx/lib/gree/NativePaymentHandler;")){
				jobject handler = k.env->GetStaticObjectField(k.classID, k.fieldID);
				if(handler == NULL){
					CCLog("Cannot create new Handler object in %s", __func__);
					return;
				}
				t.env->CallVoidMethod(obj, t.methodID, handler);
				k.env->DeleteLocalRef(k.classID);
				t.env->DeleteLocalRef(t.classID);
			}
		}
	}

	void requestJni(jobject obj, void *delegate){
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "request", "(Landroid/content/Context;Lnet/gree/asdk/api/wallet/Payment$PaymentListener;)V")){
			// get request method
			JniMethodInfo f;
			if(JniHelper::getMethodInfo(f, "org/cocos2dx/lib/gree/NativePaymentListener", "<init>", "(J)V")){
				jobject listener = f.env->NewObject(f.classID, f.methodID, (unsigned long long)delegate);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}

				jobject context = getPlatformContext();
				t.env->CallVoidMethod(obj, t.methodID, context, listener);
			}
		}
	}


	void setCallbackUrlJni(jobject obj, const char *url){
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "setCallbackUrl", "(Ljava/lang/String;)Lnet/gree/asdk/api/wallet/Payment;")){
			jstring jUrl;
			if(!url){
				jUrl = t.env->NewStringUTF("");
			}else{
				jUrl = t.env->NewStringUTF(url);
			}
			jobject ret = t.env->CallObjectMethod(obj, t.methodID, jUrl);
			t.env->DeleteLocalRef(jUrl);
			t.env->DeleteLocalRef(t.classID);
		}
	}

	void verifyJni(const char *paymentId){
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/wallet/Payment", "verify", "(Ljava/lang/String;Lnet/gree/asdk/api/wallet/Payment$VerifyListener;)V")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeVerifyListener", "<init>", "()V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}
				jstring jPaymentId;
				if(!paymentId){
					jPaymentId = t.env->NewStringUTF("");
				}else{
					jPaymentId = t.env->NewStringUTF(paymentId);
				}
				t.env->CallStaticVoidMethod(t.classID, t.methodID, jPaymentId, listener);
				t.env->DeleteLocalRef(jPaymentId);
				l.env->DeleteLocalRef(l.classID);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}

	// Current Payment.request api is directly calling ProgressDialog.show
	// this should be called inside UI thread...
	// So, wrapping request with new Handler.  (SDK should be fixed!!)
	void requestWithHandlerJni(jobject obj, void *delegate){
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/gree/Cocos2dxGreePlatform", "requestWithHandler", "(Lnet/gree/asdk/api/wallet/Payment;Lnet/gree/asdk/api/wallet/Payment$PaymentListener;)V")){
			JniMethodInfo f;
			if(JniHelper::getMethodInfo(f, "org/cocos2dx/lib/gree/NativePaymentListener", "<init>", "(J)V")){
				jobject listener = f.env->NewObject(f.classID, f.methodID, (unsigned long long)delegate);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}
			
				t.env->CallStaticVoidMethod(t.classID, t.methodID, obj, listener);
			}
		}
	}

}
	
	
