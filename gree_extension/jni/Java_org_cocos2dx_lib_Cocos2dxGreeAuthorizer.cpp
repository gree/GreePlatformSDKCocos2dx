#include "GreeJniHelper.h"
#include <string.h>
#include <jni.h>

#include "CCDirector.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.h"

using namespace cocos2d;
using namespace cocos2d::gree_extension;

extern "C" {

	void authorizeJni(int user_grade){
		JniMethodInfo t;

		if(user_grade == -1){
			// No user_grade
			if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/auth/Authorizer", "authorize", "(Landroid/app/Activity;Lnet/gree/asdk/api/auth/Authorizer$AuthorizeListener;Lnet/gree/asdk/api/auth/Authorizer$UpdatedLocalUserListener;)V")){
			
				JniMethodInfo l1;
				if(JniHelper::getMethodInfo(l1, "org/cocos2dx/lib/gree/NativeAuthorizeListener", "<init>", "(I)V")){
					jobject listener1 = l1.env->NewObject(l1.classID, l1.methodID, (int)fTypeAuthorize);
					if(listener1 == NULL){
						CCLog("Cannot create new listener object in %s", __func__);
						return;	
					}
					JniMethodInfo l2;
					if(JniHelper::getMethodInfo(l2, "org/cocos2dx/lib/gree/NativeUpdatedLocalUserListener", "<init>", "(I)V")){
						jobject listener2 = l2.env->NewObject(l2.classID, l2.methodID, (int)fTypeAuthorize);
						if(listener2 == NULL){
							CCLog("Cannot create new listener object in %s", __func__);
							return;
						}
						jobject obj = getPlatformContext();
						t.env->CallStaticVoidMethod(t.classID, t.methodID, obj, listener1, listener2);
						l1.env->DeleteLocalRef(l1.classID);
					}
					l2.env->DeleteLocalRef(l2.classID);
				}
				t.env->DeleteLocalRef(t.classID);
			}
		}else{
			// With user_grade
			if(JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/gree/NativeAuthorizerWrapper", "authorizeWithUserGrade", "(Landroid/app/Activity;Lnet/gree/asdk/api/auth/Authorizer$AuthorizeListener;Lnet/gree/asdk/api/auth/Authorizer$UpdatedLocalUserListener;I)V")){
				JniMethodInfo l1;
				if(JniHelper::getMethodInfo(l1, "org/cocos2dx/lib/gree/NativeAuthorizeListener", "<init>", "(I)V")){
					jobject listener1 = l1.env->NewObject(l1.classID, l1.methodID, (int)fTypeAuthorize);
					if(listener1 == NULL){
						CCLog("Cannot create new listener object in %s", __func__);
						return;	
					}
					JniMethodInfo l2;
					if(JniHelper::getMethodInfo(l2, "org/cocos2dx/lib/gree/NativeUpdatedLocalUserListener", "<init>", "(I)V")){
						jobject listener2 = l2.env->NewObject(l2.classID, l2.methodID, (int)fTypeAuthorize);
						if(listener2 == NULL){
							CCLog("Cannot create new listener object in %s", __func__);
							return;
						}
						jobject obj = getPlatformContext();
						t.env->CallStaticVoidMethod(t.classID, t.methodID, obj, listener1, listener2, user_grade);
						l1.env->DeleteLocalRef(l1.classID);
					}
					l2.env->DeleteLocalRef(l2.classID);
				}
			}
//FIXME : Currenty, because authorize with user_grade seems to create handler inside api, it should be called inside UIThread.
/*
			if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/auth/Authorizer", "authorize", "(Landroid/app/Activity;Lnet/gree/asdk/api/auth/Authorizer$AuthorizeListener;Lnet/gree/asdk/api/auth/Authorizer$UpdatedLocalUserListener;I)V")){
				JniMethodInfo l1;
				if(JniHelper::getMethodInfo(l1, "org/cocos2dx/lib/gree/NativeAuthorizeListener", "<init>", "(I)V")){
					jobject listener1 = l1.env->NewObject(l1.classID, l1.methodID, (int)fTypeAuthorize);
					if(listener1 == NULL){
						CCLog("Cannot create new listener object in %s", __func__);
						return;	
					}
					JniMethodInfo l2;
					if(JniHelper::getMethodInfo(l2, "org/cocos2dx/lib/gree/NativeUpdatedLocalUserListener", "<init>", "(I)V")){
						jobject listener2 = l2.env->NewObject(l2.classID, l2.methodID, (int)fTypeAuthorize);
						if(listener2 == NULL){
							CCLog("Cannot create new listener object in %s", __func__);
							return;
						}
						jobject obj = getPlatformContext();
						t.env->CallStaticVoidMethod(t.classID, t.methodID, obj, listener1, listener2, user_grade);
						l1.env->DeleteLocalRef(l1.classID);
					}
					l2.env->DeleteLocalRef(l2.classID);
				}
			}
*/
		}
	}


	void logoutJni(){
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/auth/Authorizer", "logout", "(Landroid/app/Activity;Lnet/gree/asdk/api/auth/Authorizer$LogoutListener;Lnet/gree/asdk/api/auth/Authorizer$AuthorizeListener;Lnet/gree/asdk/api/auth/Authorizer$UpdatedLocalUserListener;)V")){
			JniMethodInfo l1;
			//jobject listener1, listener2;
			if(JniHelper::getMethodInfo(l1, "org/cocos2dx/lib/gree/NativeLogoutListener", "<init>", "(I)V")){
				jobject listener1 = l1.env->NewObject(l1.classID, l1.methodID, (int)fTypeLogout);
				if(listener1 == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}

				JniMethodInfo l2;
				if(JniHelper::getMethodInfo(l2, "org/cocos2dx/lib/gree/NativeAuthorizeListener", "<init>", "(I)V")){
					jobject listener2 = l2.env->NewObject(l2.classID, l2.methodID, (int)fTypeLogout);
					if(listener2 == NULL){
						CCLog("Cannot create new listener object in %s", __func__);
						return;
					}

					JniMethodInfo l3;
					if(JniHelper::getMethodInfo(l3, "org/cocos2dx/lib/gree/NativeUpdatedLocalUserListener", "<init>", "(I)V")){
						jobject listener3 = l3.env->NewObject(l3.classID, l3.methodID, (int)fTypeLogout);
						if(listener3 == NULL){
							CCLog("Cannot create new listener object in %s", __func__);
							return;
						}

						jobject obj = getPlatformContext();
						t.env->CallStaticVoidMethod(t.classID, t.methodID, obj, listener1, listener2, listener3);
						l3.env->DeleteLocalRef(l3.classID);
					}
					l2.env->DeleteLocalRef(l2.classID);
				}

				l1.env->DeleteLocalRef(l1.classID);
				t.env->DeleteLocalRef(t.classID);
			}
		}
	}

	void upgradeJni(int targetGrade){
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/auth/Authorizer", "upgrade", "(Landroid/app/Activity;ILnet/gree/asdk/api/auth/Authorizer$UpgradeListener;Lnet/gree/asdk/api/auth/Authorizer$UpdatedLocalUserListener;)V")){
			JniMethodInfo l1;
			if(JniHelper::getMethodInfo(l1, "org/cocos2dx/lib/gree/NativeUpgradeListener", "<init>", "()V")){
				jobject listener1 = l1.env->NewObject(l1.classID, l1.methodID);
				if(listener1 == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}

				JniMethodInfo l2;
				if(JniHelper::getMethodInfo(l2, "org/cocos2dx/lib/gree/NativeUpdatedLocalUserListener", "<init>", "(I)V")){
					jobject listener2 = l2.env->NewObject(l2.classID, l2.methodID, (int)fTypeUpgrade);
					if(listener2 == NULL){
						CCLog("Cannot create new listener object in %s", __func__);
						return;
					}
					jobject obj = getPlatformContext();
					t.env->CallStaticVoidMethod(t.classID, t.methodID, obj, targetGrade, listener1, listener2);
					l2.env->DeleteLocalRef(l2.classID);
				}
				l1.env->DeleteLocalRef(l1.classID);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}

	bool hasOAuthAccessTokenJni(){
		JniMethodInfo t;
		bool ret = false;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/auth/Authorizer", "hasOAuthAccessToken", "()Z")){
			ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}

	std::string getOAuthAccessTokenJni(){
		JniMethodInfo t;
		std::string ret;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/auth/Authorizer", "getOAuthAccessToken", "()Ljava/lang/String;")){
			jstring jstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			const char* str = NULL;
			if(jstr != NULL){
				str = t.env->GetStringUTFChars(jstr, 0);
				ret = str;
				t.env->ReleaseStringUTFChars(jstr, str);
			}
			t.env->ReleaseStringUTFChars(jstr, str);
		}
		return ret;
	}

	std::string getOAuthAccessTokenSecretJni(){
		JniMethodInfo t;
		std::string ret;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/auth/Authorizer", "getOAuthAccessTokenSecret", "()Ljava/lang/String;")){
			jstring jstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			const char* str = NULL;
			if(jstr != NULL){
				str = t.env->GetStringUTFChars(jstr, 0);
				ret = str;
				t.env->ReleaseStringUTFChars(jstr, str);
			}
			t.env->ReleaseStringUTFChars(jstr, str);
		}
		return ret;
	}


	bool isAuthorizedJni(void){
		JniMethodInfo t;
		bool ret;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/auth/Authorizer", "isAuthorized", "()Z")){
			ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}

}
