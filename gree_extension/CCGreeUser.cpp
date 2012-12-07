#include "CCDirector.h"

#include "CCGreePlatform.h"
#include "CCGreeUser.h"

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

CCGreeUser::CCGreeUser(jobject user){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	mGreeUser = pEnv->NewGlobalRef(user);
}

CCGreeUser::~CCGreeUser(){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	pEnv->DeleteGlobalRef(mGreeUser);
}


CCString *CCGreeUser::getNickname(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getNickname, mGreeUser);
}

CCString *CCGreeUser::getDisplayName(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getDisplayName, mGreeUser);
}

CCString *CCGreeUser::getId(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getUserId, mGreeUser);
}

CCString *CCGreeUser::getRegion(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getRegion, mGreeUser);
}

CCString *CCGreeUser::getSubregion(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getSubregion, mGreeUser);
}

CCString *CCGreeUser::getLanguage(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getLanguage, mGreeUser);
}

CCString *CCGreeUser::getTimezone(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getTimezone, mGreeUser);
}

CCString *CCGreeUser::getAboutMe(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getAboutMe, mGreeUser);
}

CCString *CCGreeUser::getBirthday(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getBirthday, mGreeUser);
}

CCString *CCGreeUser::getGender(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getGender, mGreeUser);
}

CCString *CCGreeUser::getAge(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getAge, mGreeUser);
}

CCString *CCGreeUser::getBloodType(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getBloodType, mGreeUser);
}

CCString *CCGreeUser::getUserHash(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getUserHash, mGreeUser);
}

CCString *CCGreeUser::getUserType(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getUserType, mGreeUser);
}


bool CCGreeUser::getHasApp(){
	CALL_JNI_BOOL_METHOD_WITHOBJECT(getHasApp, mGreeUser);
}

int CCGreeUser::getUserGrade(){
	CALL_JNI_BOOL_METHOD_WITHOBJECT(getUserGrade, mGreeUser);
}

bool CCGreeUser::loadThumbnail(int size){
	bool ret = false;
	if(mGreeUser != NULL){
		ret = loadUserThumbnailJni(mGreeUser, size, (void *)this);
	}
	return ret;
}

void CCGreeUser::loadFriends(int offset, int count){
	if(mGreeUser != NULL){
		loadFriendsJni(mGreeUser, offset, count, (void *)this);
	}
}

void CCGreeUser::loadIgnoredUserIds(int offset, int count){
	if(mGreeUser != NULL){
		loadIgnoredUserIdsJni(mGreeUser, offset, count, (void *)this);
	}
}

void CCGreeUser::isIgnoringUserWithId(const char *pid){
	if(mGreeUser != NULL){
		isIgnoringUserWithIdJni(mGreeUser, pid, (void *)this);
	}
}

void CCGreeUser::loadUserWithId(const char *pid)
{
	loadUserWithIdJni(pid);
}


// Callback Handling
void CCGreeUser::handleLoadThumbnailOnSuccess(int *arr, int width, int height){
	CCImage* img = new CCImage();
	img->initWithImageData((void *)arr, width * height * 4, CCImage::kFmtRawData, width, height);
	CCGreeUserDelegate *delegate = CCGreePlatform::getUserDelegate();
	if(delegate != NULL){
		delegate->loadThumbnailSuccess(this, img);
	}
}

void CCGreeUser::handleLoadThumbnailOnFailure(int responseCode, const char *response){

	CCGreeUserDelegate *delegate = CCGreePlatform::getUserDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->loadThumbnailFailure(this, responseCode, str);
	}
}


void CCGreeUser::handleLoadFriendsOnSuccess(int index, int count, jobject *users)
{
	CCArray *userArray = new CCArray();
	for(int i = 0; i < count; i++){
		CCGreeUser* user = new CCGreeUser(users[i]);
		user->autorelease();
		userArray->addObject(user);
	}
	CCGreeUserDelegate *delegate = CCGreePlatform::getUserDelegate();
	if(delegate != NULL){
		delegate->loadFriendsSuccess(this, index, count, userArray);
	}
}

void CCGreeUser::handleLoadFriendsOnFailure(int responseCode, const char *response){
	CCGreeUserDelegate *delegate = CCGreePlatform::getUserDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->loadFriendsFailure(this, responseCode, str);
	}
}


void CCGreeUser::handleLoadUserWithIdOnSuccess(int index, int count, jobject *users)
{
	CCArray *userArray = new CCArray();
	for(int i = 0; i < count; i++){
		userArray->addObject(new CCGreeUser(users[i]));
	}
	CCGreeUserDelegate *delegate = CCGreePlatform::getUserDelegate();
	if(delegate != NULL){
		delegate->loadUserWithIdSuccess(index, count, userArray);
	}
}

void CCGreeUser::handleLoadUserWithIdOnFailure(int responseCode, const char *response){
	CCGreeUserDelegate *delegate = CCGreePlatform::getUserDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->loadUserWithIdFailure(responseCode, str);
	}
}


void CCGreeUser::handleLoadIgnoredUserIdsOnSuccess(int index, int count, const char **users)
{

	CCArray *userStringArray = new CCArray();
	for(int i = 0; i < count; i++){
		CCString *str = new CCString(users[i]);
		str->autorelease();
		userStringArray->addObject(str);
	}
	CCGreeUserDelegate *delegate = CCGreePlatform::getUserDelegate();
	if(delegate != NULL){
		delegate->loadIgnoredUserIdsSuccess(this, index, count, userStringArray);
	}
}

void CCGreeUser::handleLoadIgnoredUserIdsOnFailure(int responseCode, const char *response){
	CCGreeUserDelegate *delegate = CCGreePlatform::getUserDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->loadIgnoredUserIdsFailure(this, responseCode, str);
	}
}

void CCGreeUser::handleIsIgnoringUserWithIdOnSuccess(int index, int count, const char **users)
{

	CCArray *userStringArray = new CCArray();
	for(int i = 0; i < count; i++){
		CCString *str = new CCString(users[i]);
		str->autorelease();
		userStringArray->addObject(str);
	}
	CCGreeUserDelegate *delegate = CCGreePlatform::getUserDelegate();
	if(delegate != NULL){
		delegate->isIgnoringUserWithIdSuccess(this, index, count, userStringArray);
	}
}

void CCGreeUser::handleIsIgnoringUserWithIdOnFailure(int responseCode, const char *response){
	CCGreeUserDelegate *delegate = CCGreePlatform::getUserDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->isIgnoringUserWithIdFailure(this, responseCode, str);
	}
}


NS_CC_GREE_EXT_END


