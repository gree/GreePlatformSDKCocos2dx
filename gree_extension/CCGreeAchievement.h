#ifndef __CCGREEACHIEVEMENT_H__
#define __CCGREEACHIEVEMENT_H__

#include "jni/JniHelper.h"

#include "cocos2d.h"
#include "GreeExtensionMacros.h"

#include <android/log.h>
#include <string.h>
#include <jni.h>

#include "cocoa/CCString.h"
#include "cocoa/CCInteger.h"
#include "cocoa/CCArray.h"

#include "platform/CCImage.h"


NS_CC_GREE_EXT_BEGIN

class CCGreeAchievement;

class CCGreeAchievementDelegate{
	public:
		virtual void loadAchievementsSuccess(int index, int count, CCArray *elementArray){};
		virtual void loadAchievementsFailure(int responseCode, CCString *response){};
		virtual void lockSuccess(CCGreeAchievement *element){};
		virtual void lockFailure(CCGreeAchievement *element, int responseCode, CCString *response){};
		virtual void unlockSuccess(CCGreeAchievement *element){};
		virtual void unlockFailure(CCGreeAchievement *element, int responseCode, CCString *response){};
		virtual void loadAchievementThumbnailSuccess(CCGreeAchievement *achievement, CCImage *img){};
		virtual void loadAchievementThumbnailFailure(CCGreeAchievement *achievement, int responseCode, CCString *response){};

};

class CCGreeAchievement : public CCObject
{
	public:
		CCGreeAchievement(void* element);
		~CCGreeAchievement();	

		// Static Func
		static void loadAchievements(int index, int count);

		// Normal Func
		CCString *getId();
		CCString *getName();
		CCString *getDescription();
		int getScore();
		bool isUnlocked();
		bool isSecret();
		bool loadThumbnail();
		CCImage *getIcon();
		
		void unlock();
		void lock();


		// Callback Handling
		static void handleLoadAchievementsOnSuccess(int index, int count, void **elements);
		static void handleLoadAchievementsOnFailure(int responseCode, const char* response);

		void handleLockOnSuccess();
		void handleUnlockOnSuccess();
		void handleLockOnFailure(int responseCode, const char *response);
		void handleUnlockOnFailure(int responseCode, const char *response);
		void handleLoadThumbnailOnSuccess(int *arr, int width, int height);
		void handleLoadThumbnailOnFailure(int responseCode, const char* response);

	private:
		void* mGreeAchievement; // Java GreeAchievement Object, and also will be used Objective-C
};



NS_CC_GREE_EXT_END

#endif
