#ifndef __Java_org_cocos2dx_lib_Cocos2dxGreeShareDialog_H__
#define __Java_org_cocos2dx_lib_Cocos2dxGreeShareDialog_H__

#include <string.h>
#include "cocos2d.h"
#include "jni.h"

extern "C"
{
	jobject createShareDialogJni(void);

	void setShareDialogHandlerJni(jobject obj, void *delegate);
	void setShareDialogParamsJni(jobject obj, cocos2d::CCDictionary *params);
	void showShareDialogJni(jobject obj);
}
#endif

