#include "GreeJniHelper.h"
#include <string.h>

#include "CCDirector.h"

#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.h"

using namespace cocos2d;
using namespace cocos2d::gree_extension;

jobject  gCreateScoreListenerObj;

extern "C" {
	// Score
	std::string getScoreIdJni(jobject obj){
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

	std::string getScoreNicknameJni(jobject obj){
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

	std::string getScoreThumbnailUrlJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getThumbnailUrl", "()Ljava/lang/String;")){
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

	long long getScoreRankJni(jobject obj){
		JniMethodInfo t;
		long long ret = -1;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getRank", "()J")){
			ret = t.env->CallLongMethod(obj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}

	long long getScoreJni(jobject obj){
		JniMethodInfo t;
		long long ret = -1;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getScore", "()J")){
			ret = t.env->CallLongMethod(obj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}

	std::string getScoreAsStringJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getScoreAsString", "()Ljava/lang/String;")){
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

	void getScoreThumbnailJni(jobject obj, int size, int** pBuf, int *pw, int *ph){
		JniMethodInfo t;
		jobject img = NULL;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getThumbnail", "(I)Landroid/graphics/Bitmap;")){
			img = (jobject)t.env->CallObjectMethod(obj, t.methodID, size);
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

	bool loadScoreThumbnailJni(jobject obj, int size, void *delegate){
		JniMethodInfo t;
		bool ret = false;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "loadThumbnail", "(ILnet/gree/asdk/api/IconDownloadListener;)Z")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeIconDownloadListener", "<init>", "(JI)V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID, (unsigned long long)delegate, (int)fTypeLoadScoreThumbnail);
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




	// Leaderboard
	void loadLeaderboardsJni(int startIndex, int count){
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "net/gree/asdk/api/Leaderboard", "loadLeaderboards", "(IILnet/gree/asdk/api/Leaderboard$LeaderboardListener;)V")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeLeaderboardListener", "<init>", "()V")){
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

	std::string getLeaderboardIdJni(jobject obj){
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

	std::string getLeaderboardNameJni(jobject obj){
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

	std::string getLeaderboardThumbnailUrlJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getThumbnailUrl", "()Ljava/lang/String;")){
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

	int getFormatJni(jobject obj){
		JniMethodInfo t;
		int ret = -1;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getFormat", "()I")){
			ret = t.env->CallIntMethod(obj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}


	std::string getFormatSuffixJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getFormatSuffix", "()Ljava/lang/String;")){
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

	std::string getTimeFormatJni(jobject obj){
		JniMethodInfo t;
		std::string ret;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getTimeFormat", "()Ljava/lang/String;")){
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

	int getFormatDecimalJni(jobject obj){
		JniMethodInfo t;
		int ret = -1;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getFormatDecimal", "()I")){
			ret = t.env->CallIntMethod(obj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}

	int getSortJni(jobject obj){
		JniMethodInfo t;
		int ret = -1;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getSort", "()I")){
			ret = t.env->CallIntMethod(obj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}

	bool isLeaderboardSecretJni(jobject obj){
		JniMethodInfo t;
		bool ret = false;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "isSecret", "()Z")){
			ret = t.env->CallBooleanMethod(obj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
		return ret;
	}

	void getLeaderboardThumbnailJni(jobject obj, int** pBuf, int *pw, int *ph){
		JniMethodInfo t;
		jobject img = NULL;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getThumbnail", "()Landroid/graphics/Bitmap;")){
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

	bool loadLeaderboardThumbnailJni(jobject obj, void *delegate){
		JniMethodInfo t;
		bool ret = false;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "loadThumbnail", "(Lnet/gree/asdk/api/IconDownloadListener;)Z")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeIconDownloadListener", "<init>", "(JI)V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID, (unsigned long long)delegate, (int)fTypeLoadLeaderboardThumbnail);
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

	void createScoreJni(jobject obj, long long score, void *delegate){
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "createScore", "(JLnet/gree/asdk/api/Leaderboard$SuccessListener;)V")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeLeaderboardSuccessListener", "<init>", "(JI)V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID, (unsigned long long)delegate, (int)fTypeCreateScore);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}
				t.env->CallVoidMethod(obj, t.methodID, score, listener);
				l.env->DeleteLocalRef(l.classID);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}

	void getLeaderboardScoresJni(jobject obj, int selector, int period, int index, int count, void *delegate){
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "getScore", "(IIIILnet/gree/asdk/api/Leaderboard$ScoreListener;)V")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeScoreListener", "<init>", "(J)V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID, (unsigned long long)delegate);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}
				t.env->CallVoidMethod(obj, t.methodID, selector, period, index, count, listener);
				l.env->DeleteLocalRef(l.classID);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}

	void deleteScoreJni(jobject obj, void *delegate){
		JniMethodInfo t;
		if(GreeJniHelper::getInstanceMethodInfo(t, obj, "deleteScore", "(Lnet/gree/asdk/api/Leaderboard$SuccessListener;)V")){
			JniMethodInfo l;
			if(JniHelper::getMethodInfo(l, "org/cocos2dx/lib/gree/NativeLeaderboardSuccessListener", "<init>", "(JI)V")){
				jobject listener = l.env->NewObject(l.classID, l.methodID, (unsigned long long)delegate, (int)fTypeDeleteScore);
				if(listener == NULL){
					CCLog("Cannot create new listener object in %s", __func__);
					return;
				}
				t.env->CallVoidMethod(obj, t.methodID, listener);
				l.env->DeleteLocalRef(l.classID);
			}
			t.env->DeleteLocalRef(t.classID);
		}
	}


}

