#include "CCGreePlatform.h"
#include "CCGreeFriendCode.h"

#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreeFriendCode.h"
#include "jni/JniHelper.h"

#define JAVAVM    cocos2d::JniHelper::getJavaVM()

using namespace cocos2d;

NS_CC_GREE_EXT_BEGIN

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



// Method
void CCGreeFriendCode::loadCode(){
	loadCodeJni();
}

bool CCGreeFriendCode::requestCode(const char* expireTime){
	return requestCodeJni(expireTime);
}

void CCGreeFriendCode::deleteCode(){
	deleteCodeJni();
}

void CCGreeFriendCode::verifyCode(const char* code){
	verifyCodeJni(code);
}

//void CCGreeFriendCode::loadFriends(int startIndex, int count){
void CCGreeFriendCode::loadFriendIds(int startIndex, int count){
	loadFriendIdsJni(startIndex, count);
}

void CCGreeFriendCode::loadOwner(){
	loadOwnerJni();
}


// Callback Handling
void CCGreeFriendCode::handleLoadCodeOnSuccess(void* code){
	CCGreeFriendCodeDelegate *delegate = CCGreePlatform::getFriendCodeDelegate();
	if(delegate != NULL){
		CCGreeCode *pCode = new CCGreeCode(code);
		pCode->autorelease();
		//TODO : Want to remove retain().
		//       But in such case, developer have to issue retain() by himself to use
		//       object outside the function where it has gotten
		//       Furthermore some of current callbacks are including correspoding 
		//       object information and to get them developer also have to issue retain()
		//       not to be automatically released.
		pCode->retain();
		delegate->loadCodeSuccess(pCode);
	}
}
void CCGreeFriendCode::handleLoadCodeOnFailure(int responseCode, const char*response){
	CCGreeFriendCodeDelegate *delegate = CCGreePlatform::getFriendCodeDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->loadCodeFailure(responseCode, str);
	}
}


void CCGreeFriendCode::handleRequestCodeOnSuccess(void* code){
	CCGreeFriendCodeDelegate *delegate = CCGreePlatform::getFriendCodeDelegate();
	if(delegate != NULL){
		CCGreeCode *pCode = new CCGreeCode(code);
		pCode->autorelease();
		//TODO : Want to remove retain().
		//       But in such case, developer have to issue retain() by himself to use
		//       object outside the function where it has gotten
		//       Furthermore some of current callbacks are including correspoding 
		//       object information and to get them developer also have to issue retain()
		//       not to be automatically released.
		pCode->retain();
		delegate->requestCodeSuccess(pCode);
	}
}
void CCGreeFriendCode::handleRequestCodeOnFailure(int responseCode, const char*response){
	CCGreeFriendCodeDelegate *delegate = CCGreePlatform::getFriendCodeDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->requestCodeFailure(responseCode, str);
	}
}
	


void CCGreeFriendCode::handleDeleteCodeOnSuccess(){
	CCGreeFriendCodeDelegate *delegate = CCGreePlatform::getFriendCodeDelegate();
	if(delegate != NULL){
		delegate->deleteCodeSuccess();
	}
}
void CCGreeFriendCode::handleDeleteCodeOnFailure(int responseCode, const char*response){
	CCGreeFriendCodeDelegate *delegate = CCGreePlatform::getFriendCodeDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->deleteCodeFailure(responseCode, str);
	}
}


void CCGreeFriendCode::handleVerifyCodeOnSuccess(){
	CCGreeFriendCodeDelegate *delegate = CCGreePlatform::getFriendCodeDelegate();
	if(delegate != NULL){
		delegate->verifyCodeSuccess();
	}
}
void CCGreeFriendCode::handleVerifyCodeOnFailure(int responseCode, const char* response){
	CCGreeFriendCodeDelegate *delegate = CCGreePlatform::getFriendCodeDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->verifyCodeFailure(responseCode, str);
	}
}

void CCGreeFriendCode::handleLoadFriendIdsOnSuccess(int startIndex, int itemsPerPage, int totalResults, void **entries){
	CCArray *dataArray = new CCArray();
	for(int i = 0; i < totalResults; i++){
		CCGreeData *data = new CCGreeData(entries[i]);
		data->autorelease();
		//TODO : Want to remove retain().
		//       But in such case, developer have to issue retain() by himself to use
		//       object outside the function where it has gotten
		//       Furthermore some of current callbacks are including correspoding 
		//       object information and to get them developer also have to issue retain()
		//       not to be automatically released.
		data->retain();
		dataArray->addObject(data);
	}
	CCGreeFriendCodeDelegate *delegate = CCGreePlatform::getFriendCodeDelegate();
	if(delegate != NULL){
		delegate->loadFriendIdsSuccess(startIndex, itemsPerPage, totalResults, dataArray);
	}
}

void CCGreeFriendCode::handleLoadFriendIdsOnFailure(int responseCode, const char* response){
	CCGreeFriendCodeDelegate *delegate = CCGreePlatform::getFriendCodeDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->loadFriendIdsFailure(responseCode, str);
	}
}

void CCGreeFriendCode::handleLoadOwnerOnSuccess(void* owner){
	CCGreeData *data = NULL;
	if(owner != NULL){
		data = new CCGreeData(owner);
		data->autorelease();
		//TODO : Want to remove retain().
		//       But in such case, developer have to issue retain() by himself to use
		//       object outside the function where it has gotten
		//       Furthermore some of current callbacks are including correspoding 
		//       object information and to get them developer also have to issue retain()
		//       not to be automatically released.
		data->retain();
	}
	CCGreeFriendCodeDelegate *delegate = CCGreePlatform::getFriendCodeDelegate();
	if(delegate != NULL){
		delegate->loadOwnerSuccess(data);
	}
}


void CCGreeFriendCode::handleLoadOwnerOnFailure(int responseCode, const char* response){
	CCGreeFriendCodeDelegate *delegate = CCGreePlatform::getFriendCodeDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->loadOwnerFailure(responseCode, str);
	}
}


// CCGreeCode
CCGreeCode::CCGreeCode(void* code){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	mGreeCode = (void *)(pEnv->NewGlobalRef((jobject)code));
}
CCGreeCode::~CCGreeCode(){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	pEnv->DeleteGlobalRef((jobject)mGreeCode);
}

CCString *CCGreeCode::getCode(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getCode, mGreeCode);
}
CCString *CCGreeCode::getExpireTime(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getExpireTime, mGreeCode);
}

// CCGreeData
CCGreeData::CCGreeData(void *data){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	mGreeData = (void *)(pEnv->NewGlobalRef((jobject)data));
}
CCGreeData::~CCGreeData(){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	pEnv->DeleteGlobalRef((jobject)mGreeData);
}

CCString *CCGreeData::getUserId(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getUserIdFromGreeData, mGreeData);
}


NS_CC_GREE_EXT_END

