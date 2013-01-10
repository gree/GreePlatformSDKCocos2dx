#ifndef __Java_org_cocos2dx_lib_Cocos2dxGreeLeaderboard_H__
#define __Java_org_cocos2dx_lib_Cocos2dxGreeLeaderboard_H__

#include <string.h>

#include "cocos2d.h"

extern "C"
{
	// Score
	std::string getScoreIdJni(jobject obj);
	std::string getScoreNicknameJni(jobject obj);
	std::string getScoreThumbnailUrlJni(jobject obj);
	long long getScoreRankJni(jobject obj);
	long long getScoreJni(jobject obj);
	std::string getScoreAsStringJni(jobject obj);
	void getScoreThumbnailJni(jobject obj, int size, int** pBuf, int *pw, int *ph);
	bool loadScoreThumbnailJni(jobject obj, int size, void *delegate);



	// Leaderboard
	void loadLeaderboardsJni(int index, int count);
	std::string getLeaderboardIdJni(jobject obj);
	std::string getLeaderboardNameJni(jobject obj);
	std::string getLeaderboardThumbnailUrlJni(jobject obj);
	int getFormatJni(jobject obj);
	std::string getFormatSuffixJni(jobject obj);
	std::string getTimeFormatJni(jobject obj);
	int getFormatDecimalJni(jobject obj);
	int getSortJni(jobject obj);
	bool isLeaderboardSecretJni(jobject obj);
	void getLeaderboardThumbnailJni(jobject obj, int** pBuf, int *pw, int *ph);
	bool loadLeaderboardThumbnailJni(jobject obj, void *delegate);


	void createScoreJni(jobject obj, long long score, void *delegate);
	void getLeaderboardScoresJni(jobject obj, int selector, int period, int index, int count, void *delegate);
	
	void deleteScoreJni(jobject obj, void *delegate);
}


#endif

