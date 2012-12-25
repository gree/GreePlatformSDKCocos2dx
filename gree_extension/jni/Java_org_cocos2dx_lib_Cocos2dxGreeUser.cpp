#include "GreeJniHelper.h"
#include <string.h>
#include <jni.h>

#include "CCDirector.h"
#include "CCGreeUser.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::gree_extension;

extern "C" {
	std::string getNicknameJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getNickname", "()Ljava/lang/String;")){
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

	std::string getDisplayNameJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getDisplayName", "()Ljava/lang/String;")){
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
	std::string getUserIdJni(jobject obj){
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
	std::string getRegionJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getRegion", "()Ljava/lang/String;")){
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
	std::string getSubregionJni(jobject obj){	
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getSubregion", "()Ljava/lang/String;")){
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
	std::string getLanguageJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getLanguage", "()Ljava/lang/String;")){
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
	std::string getTimezoneJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getTimezone", "()Ljava/lang/String;")){
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
	std::string getAboutMeJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getAboutMe", "()Ljava/lang/String;")){
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
	std::string getBirthdayJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getBirthday", "()Ljava/lang/String;")){
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
	std::string getGenderJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getGender", "()Ljava/lang/String;")){
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
	std::string getAgeJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getAge", "()Ljava/lang/String;")){
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
	std::string getBloodTypeJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getBloodType", "()Ljava/lang/String;")){
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
	std::string getUserHashJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getUserHash", "()Ljava/lang/String;")){
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
	std::string getUserTypeJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getUserType", "()Ljava/lang/String;")){
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
	bool getHasAppJni(jobject obj){
		JniMethodInfo t;
		bool ret = false;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getHasApp", "()Z")){
			ret = t.env->CallBooleanMethod(obj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}
	int getUserGradeJni(jobject obj){
		JniMethodInfo t;
		int ret = -1;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getUserGrade", "()I")){
			ret = t.env->CallIntMethod(obj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}


	//obj : GreeUser, delegate : CCGreeUser
	bool loadUserThumbnailJni(jobject obj, int size, void *delegate){
		JniMethodInfo t;
		bool ret = false;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "loadThumbnail", "(ILnet/gree/asdk/api/IconDownloadListener;)Z")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeIconDownloadListener", "<init>", "(JI)V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID, (unsigned long long)delegate, (int)fTypeLoadUserThumbnail);
				// FIXME listener might well be made NewGlobalRef.....
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return ret;
				}
				ret = t.env->CallBooleanMethod(obj, t.methodID, size, listener);
				l.env->DeleteLocalRef(l.classID);
			}
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}


	void loadFriendsJni(jobject obj, int offset, int count, void *delegate){
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "loadFriends", "(IILnet/gree/asdk/api/GreeUser$GreeUserListener;)V")){
			
			JniMethodInfo f;
			if(JniHelper::getMethodInfo(f, "org/cocos2dx/lib/gree/NativeGreeUserListener", "<init>", "(JI)V")){
				jobject listener = f.env->NewObject(f.classID, f.methodID, (unsigned long long)delegate, (int)fTypeLoadFriends);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}
				t.env->CallVoidMethod(obj, t.methodID, offset, count, listener);
				f.env->DeleteLocalRef(f.classID);
			}
			t.env->DeleteLocalRef(t.classID);
		}

	}

	void loadIgnoredUserIdsJni(jobject obj, int offset, int count, void *delegate){
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "loadIgnoredUserIds", "(IILnet/gree/asdk/api/GreeUser$GreeIgnoredUserListener;)V")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeGreeIgnoredUserListener", "<init>", "(JI)V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID, (unsigned long long)delegate, (int)fTypeLoadIgnoredUserIds);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}
				t.env->CallVoidMethod(obj, t.methodID, offset, count, listener);
				l.env->DeleteLocalRef(l.classID);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}

	void isIgnoringUserWithIdJni(jobject obj, const char* pid, void *delegate){
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "isIgnoringUserWithId", "(Ljava/lang/String;Lnet/gree/asdk/api/GreeUser$GreeIgnoredUserListener;)V")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeGreeIgnoredUserListener", "<init", "(JI)V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID, (unsigned long long)delegate, (int)fTypeIsIgnoringUserWithId);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}
				jstring jPid;
				if(!pid){
					jPid = t.env->NewStringUTF("");
				}else{
					jPid = t.env->NewStringUTF(pid);
				}
				t.env->CallVoidMethod(obj, t.methodID, jPid, listener);
				l.env->DeleteLocalRef(l.classID);
				t.env->DeleteLocalRef(jPid);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}



	void loadUserWithIdJni(const char* pid){
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/GreeUser", "loadUserWithId", "(Ljava/lang/String;Lnet/gree/asdk/api/GreeUser$GreeUserListener;)V")){
			JniMethodInfo f;
			if(JniHelper::getMethodInfo(f, "org/cocos2dx/lib/gree/NativeGreeUserListener", "<init>", "(JI)V")){
				jobject listener = f.env->NewObject(f.classID, f.methodID, (unsigned long long)0, (int)fTypeLoadUserWithId);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}
				jstring jPid;
				if(!pid){
					jPid = t.env->NewStringUTF("");
				}else{
					jPid = t.env->NewStringUTF(pid);
				}
				t.env->CallStaticVoidMethod(t.classID, t.methodID, jPid, listener);
				f.env->DeleteLocalRef(f.classID);
				t.env->DeleteLocalRef(jPid);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}
}
	
	
