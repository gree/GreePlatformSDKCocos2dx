#ifndef __Java_org_cocos2dx_lib_Cocos2dxGreeDashboard_H__
#define __Java_org_cocos2dx_lib_Cocos2dxGreeDashboard_H__

#include <string.h>
#include "cocos2d.h"


extern "C"
{
	bool launchJni(void);
	bool launchWithParamJni(int type, cocos2d::CCDictionary *params);
}
#endif

