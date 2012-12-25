#include "GreeJniHelper.h"
#include <string.h>
#include <jni.h>

#include "CCDirector.h"

#include "CCGreeAchievement.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.h"

#define JAVAVM    cocos2d::JniHelper::getJavaVM()

using namespace cocos2d;
using namespace cocos2d::gree_extension;
extern  "C" {
	void loadAchievementsJni(int startIndex, int count){
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/Achievement", "loadAchievements", "(IILnet/gree/asdk/api/Achievement$AchievementListUpdateListener;)V")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeAchievementListUpdateListener", "<init>", "()V")){
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


	std::string getAchievementIdJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getId", "()Ljava/lang/String;")){
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
	std::string getAchievementNameJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getName", "()Ljava/lang/String;")){
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
	std::string getAchievementDescriptionJni(jobject obj){
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
	int getAchievementScoreJni(jobject obj){
		JniMethodInfo t;
		int ret = -1;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getScore", "()I")){
			ret = t.env->CallIntMethod(obj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}
	bool isUnlockedJni(jobject obj){
		JniMethodInfo t;
		bool ret = false;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "isUnlocked", "()Z")){
			ret = t.env->CallBooleanMethod(obj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}
	bool isSecretJni(jobject obj){
		JniMethodInfo t;
		bool ret = false;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "isSecret", "()Z")){
			ret = t.env->CallBooleanMethod(obj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}

	bool loadAchievementThumbnailJni(jobject obj, void *delegate){
		bool ret = false;
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "loadThumbnail", "(Lnet/gree/asdk/api/IconDownloadListener;)Z")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeIconDownloadListener", "<init>", "(JI)V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID, (unsigned long long)delegate, (int)fTypeLoadAchievementThumbnail);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return ret;
				}

				ret = t.env->CallBooleanMethod(obj, t.methodID, listener);
				l.env->DeleteLocalRef(l.classID);
			}
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}

	void getIconJni(jobject obj, int** pBuf, int *pw, int *ph){
		JniMethodInfo t;
		jobject img = NULL;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getIcon", "()Landroid/graphics/Bitmap;")){
			img = (jobject)t.env->CallObjectMethod(obj, t.methodID);
			if(img == NULL){
				return;
			}
			// get raw data
			{
				jclass jParser = JniHelper::getClassID("org/cocos2dx/lib/gree/NativeBitmapParser", t.env);
				if(jParser == NULL){
					return;
				}
				jmethodID method = t.env->GetStaticMethodID(jParser, "getBitmapWidth", "(Ljava/lang/Object;)I");
				if(method == NULL){
					return;
				}
				*pw = t.env->CallStaticIntMethod(jParser, method, img);

				method = t.env->GetStaticMethodID(jParser, "getBitmapHeight", "(Ljava/lang/Object;)I");
				if(method == NULL){
					return;
				}
				*ph = t.env->CallStaticIntMethod(jParser, method, img);

				if(*pw > 0 && *ph > 0){
					*pBuf = (int*)malloc(*pw * *ph * 4);
					if(*pBuf != NULL){

						method = t.env->GetStaticMethodID(jParser, "getBitmapData", "(Ljava/lang/Object;)[I");
						if(method == NULL){
							free(*pBuf);
							return;
						}
						jintArray jArr = (jintArray)t.env->CallStaticObjectMethod(jParser, method, img);
						jint* arr = t.env->GetIntArrayElements(jArr, 0);
						// convert ARGB -> ABGR
						//memcpy(*pBuf, arr, *pw * *ph * 4);
						for(int i = 0; i < *pw * *ph; i++){
							unsigned int colorData = *((unsigned int *)arr + i);
							*((unsigned int*)(*pBuf) + i) = ((colorData & 0xff00ff00) |
														((colorData & 0x00ff0000) >> 16) |
														((colorData & 0x000000ff) << 16));
						}

						t.env->ReleaseIntArrayElements(jArr, arr, 0);
					}
				}
				t.env->DeleteLocalRef(jParser);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}

	void unlockJni(jobject obj, void *delegate){
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "unlock", "(Lnet/gree/asdk/api/Achievement$AchievementChangeListener;)V")){
			JniMethodInfo f;
			if(JniHelper::getMethodInfo(f, "org/cocos2dx/lib/gree/NativeAchievementChangeListener", "<init>", "(JI)V")){
				jobject listener = f.env->NewObject(f.classID, f.methodID, (unsigned long long)delegate, (int)fTypeAchievementUnlock);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}

				t.env->CallVoidMethod(obj, t.methodID, listener);
				f.env->DeleteLocalRef(f.classID);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}

	void lockJni(jobject obj, void *delegate){
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "lock", "(Lnet/gree/asdk/api/Achievement$AchievementChangeListener;)V")){
			JniMethodInfo f;
			if(JniHelper::getMethodInfo(f, "org/cocos2dx/lib/gree/NativeAchievementChangeListener", "<init>", "(JI)V")){
				jobject listener = f.env->NewObject(f.classID, f.methodID, (unsigned long long)delegate, (int)fTypeAchievementLock);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}

				t.env->CallVoidMethod(obj, t.methodID, listener);
				f.env->DeleteLocalRef(f.classID);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}
}

