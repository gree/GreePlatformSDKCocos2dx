#include "CCDirector.h"

#include "CCGreePlatform.h"
#include "CCGreeLeaderboard.h"

#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreeLeaderboard.h"

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
CCGreeScore::CCGreeScore(void* element){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	mGreeScore = (void*)(pEnv->NewGlobalRef((jobject)element));
}

CCGreeScore::~CCGreeScore(){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	pEnv->DeleteGlobalRef((jobject)mGreeScore);
}


CCString *CCGreeScore::getId(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getScoreId, mGreeScore);
}

CCString *CCGreeScore::getNickname(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getScoreNickname, mGreeScore);
}

CCString *CCGreeScore::getThumbnailUrl(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getScoreThumbnailUrl, mGreeScore);
}


long long CCGreeScore::getRank(){
	if(mGreeScore != NULL){
		return getScoreRankJni((jobject)mGreeScore);
	}
}

long long CCGreeScore::getScore(){
	if(mGreeScore != NULL){
		return getScoreJni((jobject)mGreeScore);
	}
}

CCString *CCGreeScore::getScoreAsString(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getScoreAsString, (jobject)mGreeScore);
}

CCImage *CCGreeScore::getThumbnail(int size){
	int width = 0, height = 0;
	int *parr = NULL;
	CCImage *img = NULL;
	if(mGreeScore != NULL){
		getScoreThumbnailJni((jobject)mGreeScore, size, &parr, &width, &height);
	}
	if(width != 0 && height != 0 && parr != NULL){
		img = new CCImage();
		img->autorelease();
		img->initWithImageData((void*)parr, width * height * 4, CCImage::kFmtRawData, width, height);
		free(parr);
	}
	return img;
}
		
bool CCGreeScore::loadThumbnail(int size){
	bool ret = false;
	if(mGreeScore != NULL){
		ret = loadScoreThumbnailJni((jobject)mGreeScore, size, (void *)this);
	}
	return ret;
}


void CCGreeScore::handleLoadThumbnailOnSuccess(int *arr, int width, int height){
	CCImage* img = new CCImage();
	img->autorelease();
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
CCGreeLeaderboard::CCGreeLeaderboard(void* element){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	mGreeLeaderboard = (void *)(pEnv->NewGlobalRef((jobject)element));
}

CCGreeLeaderboard::~CCGreeLeaderboard(){
	JNIEnv *pEnv = 0;
	getEnv(&pEnv);
	pEnv->DeleteGlobalRef((jobject)mGreeLeaderboard);
}

void CCGreeLeaderboard::loadLeaderboards(int index, int count){
	loadLeaderboardsJni(index, count);
}

void CCGreeLeaderboard::createScore(long long score)
{
	if(mGreeLeaderboard != NULL){
		createScoreJni((jobject)mGreeLeaderboard, score, (void *)this);
	}
}

void CCGreeLeaderboard::deleteScore()
{
	if(mGreeLeaderboard != NULL){
		deleteScoreJni((jobject)mGreeLeaderboard, (void *)this);
	}
}


void CCGreeLeaderboard::getScore(int selector, int period, int index, int count)
{
	if(mGreeLeaderboard != NULL){
		getLeaderboardScoresJni((jobject)mGreeLeaderboard, selector, period, index, count, (void *)this);
	}
}


CCString *CCGreeLeaderboard::getId(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getLeaderboardId, (jobject)mGreeLeaderboard);
}

CCString *CCGreeLeaderboard::getName(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getLeaderboardName, (jobject)mGreeLeaderboard);
}

CCString *CCGreeLeaderboard::getThumbnailUrl(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getLeaderboardThumbnailUrl, (jobject)mGreeLeaderboard);
}

int CCGreeLeaderboard::getFormat(){
	CALL_JNI_INT_METHOD_WITHOBJECT(getFormat, (jobject)mGreeLeaderboard);
}

CCString *CCGreeLeaderboard::getFormatSuffix(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getFormatSuffix, (jobject)mGreeLeaderboard);
}

CCString *CCGreeLeaderboard::getTimeFormat(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getTimeFormat, (jobject)mGreeLeaderboard);
}

int CCGreeLeaderboard::getFormatDecimal(){
	CALL_JNI_INT_METHOD_WITHOBJECT(getFormatDecimal, (jobject)mGreeLeaderboard);
}

int CCGreeLeaderboard::getSort(){
	CALL_JNI_INT_METHOD_WITHOBJECT(getSort, (jobject)mGreeLeaderboard);
}

bool CCGreeLeaderboard::isSecret(){
	CALL_JNI_BOOL_METHOD_WITHOBJECT(isLeaderboardSecret, (jobject)mGreeLeaderboard);
}

CCImage *CCGreeLeaderboard::getThumbnail(){
	int width = 0, height = 0;
	int *parr = NULL;
	CCImage *img = NULL;
	if(mGreeLeaderboard != NULL){
		getLeaderboardThumbnailJni((jobject)mGreeLeaderboard, &parr, &width, &height);
	}
	if(width != 0 && height != 0 && parr != NULL){
		img = new CCImage();
		img->autorelease();
		img->initWithImageData((void*)parr, width * height * 4, CCImage::kFmtRawData, width, height);
		free(parr);
	}
	return img;
}

bool CCGreeLeaderboard::loadThumbnail(){
	bool ret = false;
	if(mGreeLeaderboard != NULL){
		ret = loadLeaderboardThumbnailJni((jobject)mGreeLeaderboard, (void *)this);
	}
	return ret;
}

void CCGreeLeaderboard::handleLoadLeaderboardsOnSuccess(int index, int count, void **leaderboards)
{
	CCArray *leaderboardArray = new CCArray();
	for(int i = 0; i < count; i++){
		CCGreeLeaderboard *board = new CCGreeLeaderboard(leaderboards[i]);
		board->autorelease();
		//TODO : Want to remove retain().
		//       But in such case, developer have to issue retain() by himself to use
		//       object outside the function where it has gotten
		//       Furthermore some of current callbacks are including correspoding 
		//       object information and to get them developer also have to issue retain()
		//       not to be automatically released.
		board->retain();
		leaderboardArray->addObject(board);
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

void CCGreeLeaderboard::handleGetScoreOnSuccess(int count, void **entries){
	CCArray *scoreArray = new CCArray();
	for(int i = 0; i < count; i++){
		CCGreeScore *score = new CCGreeScore(entries[i]);
		score->autorelease();
		//TODO : Want to remove retain().
		//       But in such case, developer have to issue retain() by himself to use
		//       object outside the function where it has gotten
		//       Furthermore some of current callbacks are including correspoding 
		//       object information and to get them developer also have to issue retain()
		//       not to be automatically released.
		score->retain();
		scoreArray->addObject(score);
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
	img->autorelease();
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




