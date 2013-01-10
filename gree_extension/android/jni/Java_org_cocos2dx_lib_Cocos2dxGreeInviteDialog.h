#ifndef __Java_org_cocos2dx_lib_Cocos2dxGreeInviteDialog_H__
#define __Java_org_cocos2dx_lib_Cocos2dxGreeInviteDialog_H__

#include <string.h>
#include "cocos2d.h"
#include "jni.h"

extern "C"
{
	jobject createInviteDialogJni(void);

	void setInviteDialogHandlerJni(jobject obj);
	void setInviteDialogParamsJni(jobject obj, cocos2d::CCDictionary *params);
	void showInviteDialogJni(jobject obj);
}
#endif

