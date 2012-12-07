//#include "cocos2d.h"
//#include "cocos-gree-ext.h"

#include "CCGreePlatform.h"
#include "CCGreeFriendCode.h"

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
void CCGreeFriendCode::handleLoadCodeOnSuccess(jobject code){
	CCGreeFriendCodeDelegate *delegate = CCGreePlatform::getFriendCodeDelegate();
	if(delegate != NULL){
		CCGreeCode *pCode = new CCGreeCode(code);
		pCode->autorelease();
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


void CCGreeFriendCode::handleRequestCodeOnSuccess(jobject code){
	CCGreeFriendCodeDelegate *delegate = CCGreePlatform::getFriendCodeDelegate();
	if(delegate != NULL){
		CCGreeCode *pCode = new CCGreeCode(code);
		//code->autorelease();
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

void CCGreeFriendCode::handleLoadFriendIdsOnSuccess(int startIndex, int itemsPerPage, int totalResults, jobject *entries){
	CCArray *dataArray = new CCArray();
	for(int i = 0; i < totalResults; i++){
		CCGreeData *data = new CCGreeData(entries[i]);
		data->autorelease();
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

void CCGreeFriendCode::handleLoadOwnerOnSuccess(jobject owner){
	CCGreeData *data = NULL;
	if(owner != NULL){
		data = new CCGreeData(owner);
		data->autorelease();
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
CCGreeCode::CCGreeCode(jobject code){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	mGreeCode = pEnv->NewGlobalRef(code);
}
CCGreeCode::~CCGreeCode(){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	pEnv->DeleteGlobalRef(mGreeCode);
}

CCString *CCGreeCode::getCode(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getCode, mGreeCode);
}
CCString *CCGreeCode::getExpireTime(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getExpireTime, mGreeCode);
}

// CCGreeData
CCGreeData::CCGreeData(jobject data){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	mGreeData = pEnv->NewGlobalRef(data);
}
CCGreeData::~CCGreeData(){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	pEnv->DeleteGlobalRef(mGreeData);
}

CCString *CCGreeData::getUserId(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getUserIdFromGreeData, mGreeData);
}


NS_CC_GREE_EXT_END

