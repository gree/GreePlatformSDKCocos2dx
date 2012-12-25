#include "CCGreePlatform.h"
#include "CCGreeDashboard.h"

#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreeDashboard.h"

using namespace cocos2d;

NS_CC_GREE_EXT_BEGIN

bool CCGreeDashboard::launch(){
	return launchJni();
}

bool CCGreeDashboard::launch(int type, CCDictionary *params){
	return launchWithParamJni(type, params);
	return false;
}

NS_CC_GREE_EXT_END




