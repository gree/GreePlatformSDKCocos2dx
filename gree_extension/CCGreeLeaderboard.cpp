#include "CCDirector.h"

#include "CCGreePlatform.h"
#include "CCGreeLeaderboard.h"

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


// CCGreeScore
CCGreeScore::CCGreeScore(jobject element){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	mGreeScore = pEnv->NewGlobalRef(element);
}

CCGreeScore::~CCGreeScore(){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	pEnv->DeleteGlobalRef(mGreeScore);
}


CCString *CCGreeScore::getId(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getScoreId, mGreeScore);
}

CCString *CCGreeScore::getNickname(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getNickname, mGreeScore);
}

CCString *CCGreeScore::getThumbnailUrl(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getScoreThumbnailUrl, mGreeScore);
}


long long CCGreeScore::getRank(){
	if(mGreeScore != NULL){
		return getScoreRankJni(mGreeScore);
	}
}

long long CCGreeScore::getScore(){
	if(mGreeScore != NULL){
		return getScoreJni(mGreeScore);
	}
}

CCString *CCGreeScore::getScoreAsString(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getScoreAsString, mGreeScore);
}

CCImage *CCGreeScore::getThumbnail(int size){
	int width = 0, height = 0;
	int *parr = NULL;
	CCImage *img = NULL;
	if(mGreeScore != NULL){
		getScoreThumbnailJni(mGreeScore, size, &parr, &width, &height);
	}
	if(width != 0 && height != 0 && parr != NULL){
		img = new CCImage();
		img->initWithImageData((void*)parr, width * height * 4, CCImage::kFmtRawData, width, height);
		free(parr);
	}
	return img;
}
		
bool CCGreeScore::loadThumbnail(int size){
	bool ret = false;
	if(mGreeScore != NULL){
		ret = loadScoreThumbnailJni(mGreeScore, size, (void *)this);
	}
	return ret;
}


void CCGreeScore::handleLoadThumbnailOnSuccess(int *arr, int width, int height){
	CCImage* img = new CCImage();
	img->initWithImageData((void *)arr, width * height * 4, CCImage::kFmtRawData, width, height);
	CCGreeLeaderboardDelegate *delegate = CCGreePlatform::getLeaderboardDelegate();
	if(delegate != NULL){
		delegate->loadScoreThumbnailSuccess(this, img);
	}
}
void CCGreeScore::handleLoadThumbnailOnFailure(int responseCode, const char *response){
	CCGreeLeaderboardDelegate *delegate = CCGreePlatform::getLeaderboardDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->loadScoreThumbnailFailure(this, responseCode, str);
	}
}

// CCGreeLeaderboard
CCGreeLeaderboard::CCGreeLeaderboard(jobject element){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	mGreeLeaderboard = pEnv->NewGlobalRef(element);
}

CCGreeLeaderboard::~CCGreeLeaderboard(){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	pEnv->DeleteGlobalRef(mGreeLeaderboard);
}

void CCGreeLeaderboard::loadLeaderboards(int index, int count){
	loadLeaderboardsJni(index, count);
}

void CCGreeLeaderboard::createScore(long long score)
{
	if(mGreeLeaderboard != NULL){
		createScoreJni(mGreeLeaderboard, score, (void *)this);
	}
}

void CCGreeLeaderboard::deleteScore()
{
	if(mGreeLeaderboard != NULL){
		deleteScoreJni(mGreeLeaderboard, (void *)this);
	}
}


void CCGreeLeaderboard::getScore(int selector, int period, int index, int count)
{
	if(mGreeLeaderboard != NULL){
		getLeaderboardScoresJni(mGreeLeaderboard, selector, period, index, count, (void *)this);
	}
}


CCString *CCGreeLeaderboard::getId(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getLeaderboardId, mGreeLeaderboard);
}

CCString *CCGreeLeaderboard::getName(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getLeaderboardName, mGreeLeaderboard);
}

CCString *CCGreeLeaderboard::getThumbnailUrl(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getLeaderboardThumbnailUrl, mGreeLeaderboard);
}

int CCGreeLeaderboard::getFormat(){
	CALL_JNI_INT_METHOD_WITHOBJECT(getFormat, mGreeLeaderboard);
}

CCString *CCGreeLeaderboard::getFormatSuffix(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getFormatSuffix, mGreeLeaderboard);
}

CCString *CCGreeLeaderboard::getTimeFormat(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getTimeFormat, mGreeLeaderboard);
}

int CCGreeLeaderboard::getFormatDecimal(){
	CALL_JNI_INT_METHOD_WITHOBJECT(getFormatDecimal, mGreeLeaderboard);
}

int CCGreeLeaderboard::getSort(){
	CALL_JNI_INT_METHOD_WITHOBJECT(getSort, mGreeLeaderboard);
}

bool CCGreeLeaderboard::isSecret(){
	CALL_JNI_BOOL_METHOD_WITHOBJECT(isLeaderboardSecret, mGreeLeaderboard);
}

CCImage *CCGreeLeaderboard::getThumbnail(){
	int width = 0, height = 0;
	int *parr = NULL;
	CCImage *img = NULL;
	if(mGreeLeaderboard != NULL){
		getLeaderboardThumbnailJni(mGreeLeaderboard, &parr, &width, &height);
	}
	if(width != 0 && height != 0 && parr != NULL){
		img = new CCImage();
		img->initWithImageData((void*)parr, width * height * 4, CCImage::kFmtRawData, width, height);
		free(parr);
	}
	return img;
}

bool CCGreeLeaderboard::loadThumbnail(){
	bool ret = false;
	if(mGreeLeaderboard != NULL){
		ret = loadLeaderboardThumbnailJni(mGreeLeaderboard, (void *)this);
	}
	return ret;
}

void CCGreeLeaderboard::handleLoadLeaderboardsOnSuccess(int index, int count, jobject *leaderboards)
{
	CCArray *leaderboardArray = new CCArray();
	for(int i = 0; i < count; i++){
		leaderboardArray->addObject(new CCGreeLeaderboard(leaderboards[i]));
	}
	CCGreeLeaderboardDelegate *delegate = CCGreePlatform::getLeaderboardDelegate();
	if(delegate != NULL){
		delegate->loadLeaderboardsSuccess(index, count, leaderboardArray);
	}
}

void CCGreeLeaderboard::handleLoadLeaderboardsOnFailure(int responseCode, const char* response)
{
	CCGreeLeaderboardDelegate *delegate = CCGreePlatform::getLeaderboardDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->loadLeaderboardsFailure(responseCode, str);
	}
}


void CCGreeLeaderboard::handleCreateScoreOnSuccess(){
	CCGreeLeaderboardDelegate *delegate = CCGreePlatform::getLeaderboardDelegate();
	if(delegate != NULL){
CCLog("%s", __func__);
		delegate->createScoreSuccess(this);
	}
}

void CCGreeLeaderboard::handleCreateScoreOnFailure(int responseCode, const char *response){
	CCGreeLeaderboardDelegate *delegate = CCGreePlatform::getLeaderboardDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->createScoreFailure(this, responseCode, str);
	}
}

void CCGreeLeaderboard::handleDeleteScoreOnSuccess(){
	CCGreeLeaderboardDelegate *delegate = CCGreePlatform::getLeaderboardDelegate();
	if(delegate != NULL){
		delegate->deleteScoreSuccess(this);
	}
}

void CCGreeLeaderboard::handleDeleteScoreOnFailure(int responseCode, const char *response){
	CCGreeLeaderboardDelegate *delegate = CCGreePlatform::getLeaderboardDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->deleteScoreFailure(this, responseCode, str);
	}
}

void CCGreeLeaderboard::handleGetScoreOnSuccess(int count, jobject *entries){
	CCArray *scoreArray = new CCArray();
	for(int i = 0; i < count; i++){
		scoreArray->addObject(new CCGreeScore(entries[i]));
	}
	CCGreeLeaderboardDelegate *delegate = CCGreePlatform::getLeaderboardDelegate();
	if(delegate != NULL){
		delegate->getScoreSuccess(this, scoreArray);
	}
}

void CCGreeLeaderboard::handleGetScoreOnFailure(int responseCode, const char *response){
	CCGreeLeaderboardDelegate *delegate = CCGreePlatform::getLeaderboardDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->getScoreFailure(this, responseCode, str);
	}
}

void CCGreeLeaderboard::handleLoadThumbnailOnSuccess(int *arr, int width, int height){
	CCImage* img = new CCImage();
	img->initWithImageData((void *)arr, width * height * 4, CCImage::kFmtRawData, width, height);
	CCGreeLeaderboardDelegate *delegate = CCGreePlatform::getLeaderboardDelegate();
	if(delegate != NULL){
		delegate->loadLeaderboardThumbnailSuccess(this, img);
	}
}

void CCGreeLeaderboard::handleLoadThumbnailOnFailure(int responseCode, const char *response){
	CCGreeLeaderboardDelegate *delegate = CCGreePlatform::getLeaderboardDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(response);
		str->autorelease();
		delegate->loadLeaderboardThumbnailFailure(this, responseCode, str);
	}
}

	

NS_CC_GREE_EXT_END




