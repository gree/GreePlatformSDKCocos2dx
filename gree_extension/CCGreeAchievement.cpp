#include "CCDirector.h"

#include "CCGreePlatform.h"
#include "CCGreeAchievement.h"

#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreeAchievement.h"

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


CCGreeAchievement::CCGreeAchievement(void* element){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	mGreeAchievement = (void*)(pEnv->NewGlobalRef((jobject)element));
}

CCGreeAchievement::~CCGreeAchievement(){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	pEnv->DeleteGlobalRef((jobject)mGreeAchievement);
}


// Method 
void CCGreeAchievement::loadAchievements(int index, int count){
		loadAchievementsJni(index, count);
}

CCString *CCGreeAchievement::getId(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getAchievementId, mGreeAchievement);
}

CCString *CCGreeAchievement::getName(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getAchievementName, mGreeAchievement);
}

CCString *CCGreeAchievement::getDescription(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getAchievementDescription, mGreeAchievement);
}

int CCGreeAchievement::getScore(){
	CALL_JNI_INT_METHOD_WITHOBJECT(getAchievementScore, mGreeAchievement);
}

bool CCGreeAchievement::isUnlocked(){
	CALL_JNI_BOOL_METHOD_WITHOBJECT(isUnlocked, mGreeAchievement);
}

bool CCGreeAchievement::isSecret(){
	CALL_JNI_BOOL_METHOD_WITHOBJECT(isSecret, mGreeAchievement);
}

bool CCGreeAchievement::loadThumbnail(){
	//CALL_JNI_BOOL_METHOD(loadAchievementThumbnail);
	bool ret = false;
	if(mGreeAchievement != NULL){
		ret = loadAchievementThumbnailJni((jobject)mGreeAchievement, (void *)this);
	}
	return ret;
}

CCImage *CCGreeAchievement::getIcon(){
	int width = 0, height = 0;
	int *parr = NULL;
	CCImage *img = NULL;
	if(mGreeAchievement != NULL){
		getIconJni((jobject)mGreeAchievement, &parr, &width, &height);
	}
	if(width != 0 && height != 0 && parr != NULL){
		img = new CCImage();
		img->initWithImageData((void*)parr, width * height * 4, CCImage::kFmtRawData, width, height);
		free(parr);
	}
	return img;
}

void CCGreeAchievement::lock(){
	lockJni((jobject)mGreeAchievement, (void *)this);
}

void CCGreeAchievement::unlock(){
	unlockJni((jobject)mGreeAchievement, (void *)this);
}


// Callback Handling
void CCGreeAchievement::handleLoadAchievementsOnSuccess(int index, int count, void **elements)
{
	CCArray *elementArray = new CCArray();
	for(int i = 0; i < count; i++){
		elementArray->addObject(new CCGreeAchievement(elements[i]));	
	}
	CCGreeAchievementDelegate *delegate = CCGreePlatform::getAchievementDelegate();
	if(delegate != NULL){
		delegate->loadAchievementsSuccess(index, count, elementArray);
	}
}

void CCGreeAchievement::handleLoadAchievementsOnFailure(int responseCode, const char* response){
	CCGreeAchievementDelegate *delegate = CCGreePlatform::getAchievementDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->loadAchievementsFailure(responseCode, str);
	}
}

void CCGreeAchievement::handleLockOnSuccess(){
	CCGreeAchievementDelegate *delegate = CCGreePlatform::getAchievementDelegate();
	if(delegate != NULL){
		delegate->lockSuccess(this);
	}
}

void CCGreeAchievement::handleLockOnFailure(int responseCode, const char* response){
	CCGreeAchievementDelegate *delegate = CCGreePlatform::getAchievementDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->lockFailure(this, responseCode, str);
	}
}

void CCGreeAchievement::handleUnlockOnSuccess(){
	CCGreeAchievementDelegate *delegate = CCGreePlatform::getAchievementDelegate();
	if(delegate != NULL){
		delegate->unlockSuccess(this);
	}
}

void CCGreeAchievement::handleUnlockOnFailure(int responseCode, const char* response){
	CCGreeAchievementDelegate *delegate = CCGreePlatform::getAchievementDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->unlockFailure(this, responseCode, str);
	}
}

void CCGreeAchievement::handleLoadThumbnailOnSuccess(int *arr, int width, int height){
	CCImage* img = new CCImage();
	img->initWithImageData((void *)arr, width * height * 4, CCImage::kFmtRawData, width, height);
	CCGreeAchievementDelegate *delegate = CCGreePlatform::getAchievementDelegate();
	if(delegate != NULL){
		delegate->loadAchievementThumbnailSuccess(this, img);
	}
}

void CCGreeAchievement::handleLoadThumbnailOnFailure(int responseCode, const char *response){
	CCGreeAchievementDelegate *delegate = CCGreePlatform::getAchievementDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->loadAchievementThumbnailFailure(this, responseCode, str);
	}
}

NS_CC_GREE_EXT_END




