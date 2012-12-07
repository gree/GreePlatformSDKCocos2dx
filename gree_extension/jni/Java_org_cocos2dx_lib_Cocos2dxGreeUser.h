#ifndef __Java_org_cocos2dx_lib_Cocos2dxGreeUser_H__
#define __Java_org_cocos2dx_lib_Cocos2dxGreeUser_H__


#include <string.h>

extern "C"
{
	std::string getNicknameJni(jobject obj);
	std::string getDisplayNameJni(jobject obj);
	std::string getUserIdJni(jobject obj);
	std::string getRegionJni(jobject obj);
	std::string getSubregionJni(jobject obj);
	std::string getLanguageJni(jobject obj);
	std::string getTimezoneJni(jobject obj);
	std::string getAboutMeJni(jobject obj);
	std::string getBirthdayJni(jobject obj);
	std::string getGenderJni(jobject obj);
	std::string getAgeJni(jobject obj);
	std::string getBloodTypeJni(jobject obj);
	bool        getHasAppJni(jobject obj);
	std::string getUserHashJni(jobject obj);
	std::string getUserTypeJni(jobject obj);
	int getUserGradeJni(jobject obj);

	bool loadUserThumbnailJni(jobject obj, int size, void * delegate);
	void loadFriendsJni(jobject obj, int offset, int count, void * delegate);
	void loadIgnoredUserIdsJni(jobject obj, int offset, int count, void * delegate);
	void isIgnoringUserWithIdJni(jobject obj, const char* pid, void * delegate);


	void loadUserWithIdJni(const char* pid);
}

#endif
