#ifndef __CCGREEUSER_H__
#define __CCGREEUSER_H__

#include "cocos2d.h"
#include "GreeExtensionMacros.h"

#include <string.h>

#include "cocoa/CCString.h"
#include "cocoa/CCArray.h"

#include "platform/CCImage.h"

// user Thumbnail size
typedef enum {
	UserThumbnailSizeSmall = 0,
	UserThumbnailSizeStandart,
	UserThumbnailSizeLarge,
	UserThumbnailSizeHuge,
} UserThumbnailSize;

NS_CC_GREE_EXT_BEGIN

class CCGreeUser;

class CCGreeUserDelegate
{
	public:
		virtual ~CCGreeUserDelegate() {}
		//virtual void loadThumbnailSuccess(CCGreeUser *user, int size, void (*func)(CCImage *img)) = 0;
		virtual void loadThumbnailSuccess(CCGreeUser *user, CCImage *img){};
		virtual void loadThumbnailFailure(CCGreeUser *user, int responseCode, CCString *response){};

		virtual void loadFriendsSuccess(CCGreeUser *user, int index, int count, CCArray *userArray){};
		virtual void loadFriendsFailure(CCGreeUser *user, int responseCode, CCString *response){};


		virtual void loadUserWithIdSuccess(int index, int count, CCArray *userArray){};
		virtual void loadUserWithIdFailure(int responseCode, CCString *response){};
		virtual void loadIgnoredUserIdsSuccess(CCGreeUser *user, int index, int count, CCArray *userStringArray){};
		virtual void loadIgnoredUserIdsFailure(CCGreeUser *user, int responseCode, CCString *response){};
		virtual void isIgnoringUserWithIdSuccess(CCGreeUser *user, int index, int cound, CCArray *userStringArray){};
		virtual void isIgnoringUserWithIdFailure(CCGreeUser *user, int responseCode, CCString *response){};
};

class CC_DLL CCGreeUser : public CCObject
{
	public:
		CCGreeUser(void* user);
		~CCGreeUser();	
		static void loadUserWithId(const char *pid);
		//CCBitmap getThumbnail();
		CCString *getNickname();
		CCString *getDisplayName();
		CCString *getId();
		CCString *getRegion();
		CCString *getSubregion();
		CCString *getLanguage();
		CCString *getTimezone();
		CCString *getAboutMe();
		CCString *getBirthday();
		CCString *getGender();
		CCString *getAge();
		CCString *getBloodType();
		bool      getHasApp();
		CCString *getUserHash();
		CCString *getUserType();
		int  getUserGrade();

		bool     loadThumbnail(int size);
		void     loadFriends(int offset, int count);
		void     loadIgnoredUserIds(int offset, int count);
		void     isIgnoringUserWithId(const char *pid);

		CCImage *getThumbnail();

		void handleSuccess(int *arr, int width, int height);
		void handleLoadThumbnailOnSuccess(int *arr, int width, int height);
		void handleLoadThumbnailOnFailure(int responseCode, const char* response);
		void handleLoadFriendsOnSuccess(int index, int count, void **users);
		void handleLoadFriendsOnFailure(int responseCode, const char* response);
		void handleLoadIgnoredUserIdsOnSuccess(int index, int count, const char** users);
		void handleLoadIgnoredUserIdsOnFailure(int responseCode, const char* response);
		void handleIsIgnoringUserWithIdOnSuccess(int index, int count, const char** users);
		void handleIsIgnoringUserWithIdOnFailure(int responseCode, const char* response);

		static void handleLoadUserWithIdOnSuccess(int index, int count, void **users);
		static void handleLoadUserWithIdOnFailure(int responseCode, const char* response);

	private:
		void* mGreeUser; // Java GreeUser Object, and also will be used Objective-C
};



NS_CC_GREE_EXT_END

#endif
