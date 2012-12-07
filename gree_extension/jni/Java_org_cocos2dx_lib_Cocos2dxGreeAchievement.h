#ifndef __Java_org_cocos2dx_lib_Cocos2dxGreeAchievement_H__
#define __Java_org_cocos2dx_lib_Cocos2dxGreeAchievement_H__

#include <string.h>

#include "cocos2d.h"

extern "C"
{
	void loadAchievementsJni(int index, int count);
	std::string getAchievementIdJni(jobject obj);
	std::string getAchievementNameJni(jobject obj);
	std::string getDescriptionJni(jobject obj);
	int getAchievementScoreJni(jobject obj);
	bool isUnlockedJni(jobject obj);
	bool isSecretJni(jobject obj);
	void getIconJni(jobject obj, int** parr, int *pw, int *ph);

	void lockJni(jobject obj, void *delegate);
	void unlockJni(jobject obj, void *delegate);

	bool loadAchievementThumbnailJni(jobject obj, void *delegate);
}

#endif

