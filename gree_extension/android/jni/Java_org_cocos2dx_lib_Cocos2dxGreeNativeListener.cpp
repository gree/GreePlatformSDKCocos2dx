#include "GreeJniHelper.h"
#include <string.h>
#include <jni.h>

#include "CCGreeAuthorizer.h"
#include "CCGreeUser.h"
#include "CCGreePayment.h"
#include "CCGreeAchievement.h"
#include "CCGreeLeaderboard.h"
#include "CCGreeFriendCode.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::gree_extension;

extern "C" {
	// from NativeIconDownloadListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeIconDownloadListener_nativeIconDownloadOnSuccess(JNIEnv *env, jobject obj, jlong delegate, jint funcType, jintArray src, jint width, jint height){
		jint* arr = env->GetIntArrayElements(src, 0);
		int *pBuf = (int*)malloc(width * height * 4);
		if(pBuf != NULL){
			// convert ARGB -> ABGR
			//memcpy(pBuf, arr, width * height * 4);
			for(int i = 0; i < width * height; i++){
				unsigned int colorData = *((unsigned int *)arr + i);
				 *((unsigned int*)pBuf + i) = ((colorData & 0xff00ff00) |
												((colorData & 0x00ff0000) >> 16) |
												((colorData & 0x000000ff) << 16));
			}
			if(delegate){
				switch(funcType){
					case fTypeLoadUserThumbnail:
						((CCGreeUser *)delegate)->handleLoadThumbnailOnSuccess(pBuf, width, height);
						break;
					case fTypeLoadAchievementThumbnail:
						((CCGreeAchievement *)delegate)->handleLoadThumbnailOnSuccess(pBuf, width, height);
						break;
					case fTypeLoadLeaderboardThumbnail:
						((CCGreeLeaderboard *)delegate)->handleLoadThumbnailOnSuccess(pBuf, width, height);
						break;
					case fTypeLoadScoreThumbnail:
						((CCGreeScore *)delegate)->handleLoadThumbnailOnSuccess(pBuf, width, height);
						break;
					default:
						CCLog("++++++ No appropriate callback for %s", __func__);
						break;
				}
			}
			free(pBuf);
		}
		env->ReleaseIntArrayElements(src, arr, 0);
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeIconDownloadListener_nativeIconDownloadOnFailure(JNIEnv *env, jobject obj, jlong delegate, jint funcType, jint responseCode, jstring response){
		const char* str = env->GetStringUTFChars(response, 0);
		if(delegate){
			switch(funcType){
				case fTypeLoadUserThumbnail:
					((CCGreeUser *)delegate)->handleLoadThumbnailOnFailure(responseCode, str);
					break;
				case fTypeLoadAchievementThumbnail:
					((CCGreeAchievement *)delegate)->handleLoadThumbnailOnFailure(responseCode, str);
					break;
				case fTypeLoadLeaderboardThumbnail:
					((CCGreeLeaderboard *)delegate)->handleLoadThumbnailOnFailure(responseCode, str);
					break;
				default:
					CCLog("++++++ No appropriate callback for %s", __func__);
					break;
			}
			env->ReleaseStringUTFChars(response, str);
		}
	}


	// from NativeGreeUserListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeGreeUserListener_nativeGreeUserOnSuccess(JNIEnv *env, jobject obj, jlong delegate, jint funcType, jint index, jint count, jobjectArray users){
		//int size = env->GetArrayLength(users);
		jobject *pArr = (jobject*)malloc(sizeof(jobject) * count);
		if(pArr != NULL){
			for ( int i = 0; i < count; i++){
				pArr[i] = env->GetObjectArrayElement(users, i);
			}
			if(delegate){
				switch(funcType){
					case fTypeLoadFriends:
						((CCGreeUser *)delegate)->handleLoadFriendsOnSuccess(index, count, (void **)pArr);
						break;
					default:
						CCLog("++++++ No appropriate callback for %s", __func__);
						break;
				}
			}else{
				if(funcType == fTypeLoadUserWithId){
					CCGreeUser::handleLoadUserWithIdOnSuccess(index, count, (void **)pArr);
				}else{
					CCLog("++++++ No appropriate callback for %s", __func__);
				}
			}
			free(pArr);
		}
	}

	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeGreeUserListener_nativeGreeUserOnFailure(JNIEnv * env, jobject obj, jlong delegate, jint funcType, jint responseCode, jstring response){
		const char* str = env->GetStringUTFChars(response, 0);
		if(delegate){
			switch(funcType){
				case fTypeLoadUserThumbnail:
					((CCGreeUser *)delegate)->handleLoadFriendsOnFailure(responseCode, str);
					break;
				default:
					CCLog("++++++ No appropriate callback for %s", __func__);
					break;
			}
			env->ReleaseStringUTFChars(response, str);
		}else{
			if(funcType == fTypeLoadUserWithId){
				CCGreeUser::handleLoadUserWithIdOnFailure(responseCode, str);
			}else{
				CCLog("++++++ No appropriate callback for %s", __func__);
			}
		}
		env->ReleaseStringUTFChars(response, str);
	}


	// from GreeIgnoredUserListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeGreeIgnoredUserListener_nativeGreeIgnoredUserOnSuccess(JNIEnv * env, jobject obj, jlong delegate, jint funcType, jint index, jint count, jobjectArray users){
		//int size = env->GetArrayLength(users);
		jstring *pArr = (jstring*)malloc(sizeof(jstring) * count);
		const char **pStrArr = (const char**)malloc(sizeof(char*) * count);
		if(pArr != NULL && pStrArr != NULL){
			for(int i = 0; i < count; i++){
				pArr[i] = (jstring)env->GetObjectArrayElement(users, i);
				pStrArr[i] = env->GetStringUTFChars(pArr[i], 0);
				//pArr[i] = env->GetObjectArrayElement(users, i);
			}
			if(delegate){
				switch(funcType){
					case fTypeLoadIgnoredUserIds:
						((CCGreeUser *)delegate)->handleLoadIgnoredUserIdsOnSuccess(index, count, pStrArr);
						break;
					case fTypeIsIgnoringUserWithId:
						((CCGreeUser *)delegate)->handleIsIgnoringUserWithIdOnSuccess(index, count, pStrArr);
						break;
					default:
						CCLog("++++++ No appropriate callback for %s", __func__);
						break;
				}
			}
			// TODO release string
			for(int i = 0; i < count; i++){
				env->ReleaseStringUTFChars(pArr[i], pStrArr[i]);
				env->DeleteLocalRef(pArr[i]);
			}
		}
		if(pArr != NULL){
			free(pArr);
		}
		if(pStrArr != NULL){
			free(pStrArr);
		}
		
	}

	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeGreeIgnoredUserListener_nativeGreeIgnoredUserOnFailure(JNIEnv * env, jobject obj, jlong delegate, jint funcType, jint responseCode, jstring response){
		const char* str = env->GetStringUTFChars(response, 0);
		if(delegate){
			switch(funcType){
				case fTypeLoadIgnoredUserIds:
					((CCGreeUser *)delegate)->handleLoadIgnoredUserIdsOnFailure(responseCode, str);
					break;
				case fTypeIsIgnoringUserWithId:
					((CCGreeUser *)delegate)->handleIsIgnoringUserWithIdOnFailure(responseCode, str);
					break;
				default:
					CCLog("++++++ No appropriate callback for %s", __func__);
					break;
			}
		}
		env->ReleaseStringUTFChars(response, str);
	}

	// from NativeAchievementListUpdateListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeAchievementListUpdateListener_nativeAchievementListUpdateOnSuccess(JNIEnv *env, jobject obj, jint index, jint totalListSize, jobjectArray elements){
		//int size = env->GetArrayLength(elements);

		jobject *pArr = (jobject*)malloc(sizeof(jobject) * totalListSize);
		if(pArr != NULL){
			for(int i = 0; i < totalListSize; i++){
				pArr[i] = env->GetObjectArrayElement(elements, i);
			}
			CCGreeAchievement::handleLoadAchievementsOnSuccess(index, totalListSize, (void **)pArr);
			free(pArr);
		}
	}

	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeAchievementListUpdateListener_nativeAchievementListUpdateOnFailure(JNIEnv *env, jobject obj, jint responseCode, jstring response){
		const char* str = env->GetStringUTFChars(response, 0);
		CCGreeAchievement::handleLoadAchievementsOnFailure(responseCode, str);
		env->ReleaseStringUTFChars(response, str);
	}

	// from NativeAchievementChangeListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeAchievementChangeListener_nativeAchievementChangeOnSuccess(JNIEnv *env, jobject obj, jlong delegate, jint funcType){
		if(delegate){
			switch(funcType){
				case fTypeAchievementLock:
					((CCGreeAchievement *)delegate)->handleLockOnSuccess();
					break;
				case  fTypeAchievementUnlock:
					((CCGreeAchievement *)delegate)->handleUnlockOnSuccess();
					break;
				default:
					CCLog("++++++ No appropriate callback for %s", __func__);
					break;
			}
		}
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeAchievementChangeListener_nativeAchievementChangeOnFailure(JNIEnv *env, jobject obj, jlong delegate, jint funcType, jint responseCode, jstring response){
		const char* str = env->GetStringUTFChars(response, 0);
		if(delegate){
			switch(funcType){
				case fTypeAchievementLock:
					((CCGreeAchievement *)delegate)->handleLockOnFailure(responseCode, str);
					break;
				case fTypeAchievementUnlock:
					((CCGreeAchievement *)delegate)->handleUnlockOnFailure(responseCode, str);
					break;
				default:
					CCLog("++++++ No appropriate callback for %s", __func__);
					break;
			}
		}
		env->ReleaseStringUTFChars(response, str);
	}

	// from NativeRequestListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativePaymentListener_nativePaymentOnSuccess(JNIEnv *env, jobject obj, jlong delegate, jint responseCode, jstring paymentId){
		const char *str = env->GetStringUTFChars(paymentId, 0);
//		ON_DELEGATE(CCGreePayment, handleOnPaymentRequestSuccess, "resposencode,     str");
		CCGreePayment *pGreePayment = (CCGreePayment*)delegate;
		if(pGreePayment != NULL){
			pGreePayment->handlePaymentRequestOnSuccess(responseCode, str);
		}
		env->ReleaseStringUTFChars(paymentId, str);
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativePaymentListener_nativePaymentOnCancel(JNIEnv *env, jobject obj, jlong delegate, jint responseCode, jstring paymentId){
		const char *str = env->GetStringUTFChars(paymentId, 0);
		CCGreePayment *pGreePayment = (CCGreePayment*)delegate;
		if(pGreePayment != NULL){
			pGreePayment->handlePaymentRequestOnCancel(responseCode, str);
		}
		env->ReleaseStringUTFChars(paymentId, str);
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativePaymentListener_nativePaymentOnFailure(JNIEnv *env, jobject obj, jlong delegate, jint responseCode, jstring paymentId, jstring response){
		const char *str1 = env->GetStringUTFChars(paymentId, 0);
		const char *str2 = env->GetStringUTFChars(response, 0);

		CCGreePayment *pGreePayment = (CCGreePayment *)delegate;
		if(pGreePayment != NULL){
			pGreePayment->handlePaymentRequestOnFailure(responseCode, str1, str2);
		}
		env->ReleaseStringUTFChars(paymentId, str1);
		env->ReleaseStringUTFChars(response, str2);
	}

	// from NativeVerifyListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeVerifyListener_nativeVerifyOnSuccess(JNIEnv *env, jobject obj, jint responseCode, jstring paymentId){
		const char *str = env->GetStringUTFChars(paymentId, 0);
		CCGreePayment::handlePaymentVerifyOnSuccess(responseCode, str);
		env->ReleaseStringUTFChars(paymentId, str);
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeVerifyListener_nativeVerifyOnCancel(JNIEnv *env, jobject obj, jint responseCode, jstring paymentId){
		const char *str = env->GetStringUTFChars(paymentId, 0);
		CCGreePayment::handlePaymentVerifyOnCancel(responseCode, str);
		env->ReleaseStringUTFChars(paymentId, str);
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeVerifyListener_nativeVerifyOnFailure(JNIEnv *env, jobject obj, jint responseCode, jstring paymentId, jstring response){
		const char *str1 = env->GetStringUTFChars(paymentId, 0);
		const char *str2 = env->GetStringUTFChars(response, 0);
		CCGreePayment::handlePaymentVerifyOnFailure(responseCode, str1, str2);
		env->ReleaseStringUTFChars(paymentId, str1);
		env->ReleaseStringUTFChars(response, str2);
	}


	// from NativeAuthorizeListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeAuthorizeListener_nativeOnAuthorized(JNIEnv *env, jobject obj, jint funcType){
		switch(funcType){
			case fTypeAuthorize:
				CCGreeAuthorizer::handleOnAuthorized();
				break;
			case fTypeLogout:
				//CCGreeAuthorizer::handleOnAuthorized();
				break;
			default:
				CCLog("++++++ No appropriate callback for %s", __func__);
				break;
		}
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeAuthorizeListener_nativeOnAuthorizeCancel(JNIEnv *env, jobject obj, jint funcType){
		switch(funcType){
			case fTypeAuthorize:
				CCGreeAuthorizer::handleOnAuthorizeCancel();
				break;
			case fTypeLogout:
				//CCGreeAuthorizer::handleOnAuthorized();
				break;
			default:
				CCLog("++++++ No appropriate callback for %s", __func__);
				break;
		}
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeAuthorizeListener_nativeOnAuthorizeError(JNIEnv *env, jobject obj, jint funcType){
		switch(funcType){
			case fTypeAuthorize:
				CCGreeAuthorizer::handleOnAuthorizeError();
				break;
			case fTypeLogout:
				//CCGreeAuthorizer::handleOnAuthorized();
				break;
			default:
				CCLog("++++++ No appropriate callback for %s", __func__);
				break;
		}
	}

	// from NativeUpdatedLocalUserListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeUpdatedLocalUserListener_nativeOnUpdateLocalUser(JNIEnv *env, jobject obj, jint funcType){
		switch(funcType){
			case fTypeAuthorize:
				CCGreeAuthorizer::handleOnAuthorizeUpdateLocalUser();
				break;
			case fTypeLogout:
				CCGreeAuthorizer::handleOnLogoutUpdateLocalUser();
				break;
			case fTypeUpgrade:
				CCGreeAuthorizer::handleOnUpgradeUpdateLocalUser();
				break;
			default:
				CCLog("++++++ No appropriate callback for %s", __func__);
				break;
		}
	}

	// from LogoutListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeLogoutListener_nativeOnLogouted(JNIEnv *env, jobject obj, jint funcType){
		switch(funcType){
		//	case fTypeAuthorize:
		//		break;
			case fTypeLogout:
				CCGreeAuthorizer::handleOnLogouted();
				break;
		//	case fTypeUpgrade:
		//		break;
			default:
				CCLog("++++++ No appropriate callback for %s", __func__);
				break;
		}
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeLogoutListener_nativeOnLogoutError(JNIEnv *env, jobject obj, jint funcType){
		switch(funcType){
		//	case fTypeAuthorize:
		//		break;
			case fTypeLogout:
				CCGreeAuthorizer::handleOnLogoutError();
				break;
		//	case fTypeUpgrade:
		//		break;
			default:
				CCLog("++++++ No appropriate callback for %s", __func__);
				break;
		}
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeLogoutListener_nativeOnLogoutCancel(JNIEnv *env, jobject obj, jint funcType){
		switch(funcType){
		//	case fTypeAuthorize:
		//		break;
			case fTypeLogout:
				CCGreeAuthorizer::handleOnLogoutCancel();
				break;
		//	case fTypeUpgrade:
		//		break;
			default:
				CCLog("++++++ No appropriate callback for %s", __func__);
				break;
		}
	}
	

	// from NativeUpgradeListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeUpgradeListener_nativeOnUpgraded(JNIEnv *env, jobject obj){
		CCGreeAuthorizer::handleOnUpgraded();
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeUpgradeListener_nativeOnUpgradeError(JNIEnv *env, jobject obj){
		CCGreeAuthorizer::handleOnUpgradeError();
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeUpgradeListener_nativeOnUpgradeCancel(JNIEnv *env, jobject obj){
		 CCGreeAuthorizer::handleOnUpgradeCancel();
	}	

	// from NativeLeaderboardListner
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeLeaderboardListener_nativeLeaderboardOnSuccess(JNIEnv *env, jobject obj, jint index, jint totalListSize, jobjectArray leaderboards){
		//int size = env->GetArrayLength(leaderboards);
		jobject *pArr = (jobject*)malloc(sizeof(jobject) * totalListSize);
		if(pArr != NULL){
			for(int i = 0; i < totalListSize; i++){
				pArr[i] = env->GetObjectArrayElement(leaderboards, i);
			}
			CCGreeLeaderboard::handleLoadLeaderboardsOnSuccess(index, totalListSize, (void **)pArr);
			free(pArr);
		}
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeLeaderboardListener_nativeLeaderboardOnFailure(JNIEnv *env, jobject obj, jint responseCode, jstring response){
		const char* str = env->GetStringUTFChars(response, 0);
		CCGreeLeaderboard::handleLoadLeaderboardsOnFailure(responseCode, str);
		env->ReleaseStringUTFChars(response, str);
	}


	// from NativeLeaderboardSuccessListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeLeaderboardSuccessListener_nativeLeaderboardSuccessListenerOnSuccess(JNIEnv *env, jobject obj, jlong delegate, jint funcType){
		if(delegate){
			switch(funcType){
				case fTypeCreateScore:
					((CCGreeLeaderboard *)delegate)->handleCreateScoreOnSuccess();
					break;
				case fTypeDeleteScore:
					((CCGreeLeaderboard *)delegate)->handleDeleteScoreOnSuccess();
					break;
				default:
					CCLog("++++++ No appropriate callback for %s", __func__);
					break;
			}
		}
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeLeaderboardSuccessListener_nativeLeaderboardSuccessListenerOnFailure(JNIEnv *env, jobject obj, jlong delegate, jint funcType, int responseCode, jstring response){
		const char* str = env->GetStringUTFChars(response, 0);
		if(delegate){
			switch(funcType){
				case fTypeCreateScore:
					((CCGreeLeaderboard *)delegate)->handleCreateScoreOnFailure(responseCode, str);
					break;
				case fTypeDeleteScore:
					((CCGreeLeaderboard *)delegate)->handleDeleteScoreOnFailure(responseCode, str);
					break;
				default:
					CCLog("++++++ No appropriate callback for %s", __func__);
					break;
			}
		}
		env->ReleaseStringUTFChars(response, str);
	}


	// from NativeScoreListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeScoreListener_nativeScoreOnSuccess(JNIEnv *env, jobject obj, jlong delegate, jint listSize, jobjectArray entries){
		//int size = env->GetArrayLength(entries);
		jobject *pArr = (jobject*)malloc(sizeof(jobject) * listSize);
		if(pArr != NULL){
			for(int i = 0; i < listSize; i++){
				pArr[i] = env->GetObjectArrayElement(entries, i);
			}
			CCGreeLeaderboard *pGreeLeaderboard = (CCGreeLeaderboard *)delegate;
			if(pGreeLeaderboard != NULL){
				pGreeLeaderboard->handleGetScoreOnSuccess(listSize, (void **)pArr);
			}
			free(pArr);
		}
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeScoreListener_nativeScoreOnFailure(JNIEnv *env, jobject obj, jlong delegate, jint responseCode, jstring response){
		const char* str = env->GetStringUTFChars(response, 0);
		CCGreeLeaderboard *pGreeLeaderboard = (CCGreeLeaderboard *)delegate;
		if(pGreeLeaderboard != NULL){
			pGreeLeaderboard->handleGetScoreOnFailure(responseCode, str);
		}
		env->ReleaseStringUTFChars(response, str);
	}

	// from NativeCodeListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeCodeListener_nativeCodeListenerOnSuccess(JNIEnv *env, jobject obj, jint funcType, jobject code){
		switch(funcType){
			case fTypeLoadCode:
				CCGreeFriendCode::handleLoadCodeOnSuccess(code);
				break;
			case fTypeRequestCode:
				CCGreeFriendCode::handleRequestCodeOnSuccess(code);
				break;
			default:
				CCLog("++++++ No appropriate callback for %s", __func__);
				break;
		}
	}

	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeCodeListener_nativeCodeListenerOnFailure(JNIEnv *env, jobject obj, jint funcType, jint responseCode, jstring response){
		const char* str = env->GetStringUTFChars(response, 0);
		switch(funcType){
			case fTypeLoadCode:
				CCGreeFriendCode::handleLoadCodeOnFailure(responseCode, str);
				break;
			case fTypeRequestCode:
				CCGreeFriendCode::handleRequestCodeOnFailure(responseCode, str);
				break;
			default:
				CCLog("++++++ No appropriate callback for %s", __func__);
				break;
		}
		env->ReleaseStringUTFChars(response, str);
	}


	// from NativeFriendCodeSuccessListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeFriendCodeSuccessListener_nativeFriendCodeSuccessListenerOnSuccess(JNIEnv *env, jobject obj, jlong delegate, jint funcType){
		if(!delegate){
			switch(funcType){
				case fTypeDeleteCode:
					CCGreeFriendCode::handleDeleteCodeOnSuccess();
					break;
				case fTypeVerifyCode:
					CCGreeFriendCode::handleVerifyCodeOnSuccess();
					break;
				default:
					CCLog("++++++ No appropriate callback for %s", __func__);
					break;
			}
		}
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeFriendCodeSuccessListener_nativeFriendCodeSuccessListenerOnFailure(JNIEnv *env, jobject obj, jlong delegate, jint funcType, jint responseCode, jstring response){
		const char* str = env->GetStringUTFChars(response, 0);
		if(!delegate){
			switch(funcType){
				case fTypeDeleteCode:
					CCGreeFriendCode::handleDeleteCodeOnFailure(responseCode, str);
					break;
				case fTypeVerifyCode:
					CCGreeFriendCode::handleVerifyCodeOnFailure(responseCode, str);
					break;
				default:
					CCLog("++++++ No appropriate callback for %s", __func__);
					break;
			}
		}
		env->ReleaseStringUTFChars(response, str);
	}


	// from NativeEntryListGetListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeEntryListGetListener_nativeEntryListGetListenerOnSuccess(JNIEnv *env, jobject obj, jint startIndex, jint itemsPerPage, jint totalResults, jobjectArray entries){
		//int size = env->GetArrayLength(entries);
		jobject *pArr = (jobject*)malloc(sizeof(jobject) * totalResults);
		if(pArr != NULL){
			for(int i = 0; i < totalResults; i++){
				pArr[i] = env->GetObjectArrayElement(entries, i);
			}
			CCGreeFriendCode::handleLoadFriendIdsOnSuccess(startIndex, itemsPerPage, totalResults, (void **)pArr);
			free(pArr);
		}
	}

	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeEntryListGetListener_nativeEntryListGetListenerOnFailure(JNIEnv *env, jobject obj, jint responseCode, jstring response){
		const char* str = env->GetStringUTFChars(response, 0);
		CCGreeFriendCode::handleLoadFriendIdsOnFailure(responseCode, str);	
		env->ReleaseStringUTFChars(response, str);
	}

	// from NativeOwnerGetListener
	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeOwnerGetListener_nativeOwnerGetListenerOnSuccess(JNIEnv *env, jobject obj, jobject owner){
		CCGreeFriendCode::handleLoadOwnerOnSuccess(owner);
	}

	JNIEXPORT void JNICALL Java_org_cocos2dx_lib_gree_NativeOwnerGetListener_nativeOwnerGetListenerOnFailure(JNIEnv *env, jobject obj, jint responseCode, jstring response){
		const char* str = env->GetStringUTFChars(response, 0);
		CCGreeFriendCode::handleLoadOwnerOnFailure(responseCode, str);	
		env->ReleaseStringUTFChars(response, str);
	}
}

