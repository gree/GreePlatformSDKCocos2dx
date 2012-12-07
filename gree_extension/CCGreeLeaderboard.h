#ifndef __CCGREELEADERBOARD_H__
#define __CCGREELEADERBOARD_H__

#include "jni/JniHelper.h"
#include "cocos2d.h"
#include "cocos-gree-ext.h"

// leaderbaord selector
typedef enum {
	kLeaderboardSelectorMyScores = 0,
	kLeaderboardSelectorFriendsScores,
	kLeaderboardSelectorAllScores,
} LeaderboardSelector;

// leaderboard period
typedef enum {
	kLeaderboardPeriodDaily = 0,
	kLeaderboardPeriodWeekly,
	kLeaderboardPeriodAllTime,
} LeaderboardPeriod;

// score Thumbnail size
typedef enum {
	kScoreThumbnailSizeSmall = 0,
	kScoreThumbnailSizeStandard,
	kScoreThumbnailSizeHuge,
} ScoreThumbnailSize;

NS_CC_GREE_EXT_BEGIN

class CCGreeLeaderboard;


// CCGreeScore
class CCGreeScore : public CCObject
{
	public:
		CCGreeScore(jobject element);
		~CCGreeScore();

		CCString *getId();
		CCString *getNickname();
		CCString *getThumbnailUrl();
		long long getRank();
		long long getScore();
		CCString *getScoreAsString();
		CCImage *getThumbnail(int size);
		
		bool loadThumbnail(int size);

		void handleLoadThumbnailOnSuccess(int *arr, int width, int height);
		void handleLoadThumbnailOnFailure(int responseCode, const char *response);
	private:
		jobject mGreeScore;
};




// CCGreeLeaderboard
class CCGreeLeaderboardDelegate
{
	public:
		virtual void loadLeaderboardsSuccess(int index, int count, CCArray *leaderboardArray){};
		virtual void loadLeaderboardsFailure(int responseCode, CCString *response){};

		virtual void createScoreSuccess(CCGreeLeaderboard *leaderboard){};
		virtual void createScoreFailure(CCGreeLeaderboard *leaderboard, int responseCode, CCString *response){};
		virtual void deleteScoreSuccess(CCGreeLeaderboard *leaderboard){};
		virtual void deleteScoreFailure(CCGreeLeaderboard *leaderboard, int responseCode, CCString *response){};
		virtual void getScoreSuccess(CCGreeLeaderboard *leaderboard, CCArray* scoreArray){};
		virtual void getScoreFailure(CCGreeLeaderboard *leaderboard, int responseCode, CCString *response){};
		virtual void loadLeaderboardThumbnailSuccess(CCGreeLeaderboard *leaderboard, CCImage *img){};
		virtual void loadLeaderboardThumbnailFailure(CCGreeLeaderboard *leaderboard, int responseCode, CCString *response){};
		virtual void loadScoreThumbnailSuccess(CCGreeScore *score, CCImage *img){};
		virtual void loadScoreThumbnailFailure(CCGreeScore *score, int responseCode, CCString *response){};
};

class CCGreeLeaderboard : public CCObject
{
	public:
		CCGreeLeaderboard(jobject element);
		~CCGreeLeaderboard();

		static void loadLeaderboards(int index, int count);

		void createScore(long long score);
		void getScore(int selector, int period, int index, int count);

		// This is for debuggin use
		void deleteScore();
		CCString *getId();
		CCString *getName();
		CCString *getThumbnailUrl();
		int getFormat();
		CCString *getFormatSuffix();
		CCString *getTimeFormat();
		int getFormatDecimal();
		int getSort();
		bool isSecret();
		CCImage *getThumbnail();
		bool loadThumbnail();

		// callback
		static void handleLoadLeaderboardsOnSuccess(int index, int count, jobject *leaderboards);
		static void handleLoadLeaderboardsOnFailure(int responseCode, const char* response);


		void handleCreateScoreOnSuccess();
		void handleCreateScoreOnFailure(int responseCode, const char* response);
		void handleDeleteScoreOnSuccess();
		void handleDeleteScoreOnFailure(int responseCode, const char* response);
		void handleGetScoreOnSuccess(int count, jobject *entries);
		void handleGetScoreOnFailure(int responseCode, const char* response);
		void handleLoadThumbnailOnSuccess(int *arr, int width, int height);
		void handleLoadThumbnailOnFailure(int responseCode, const char *response);
	private:
		 jobject mGreeLeaderboard;
};

NS_CC_GREE_EXT_END

#endif
