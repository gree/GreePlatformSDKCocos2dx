#ifndef __Java_org_cocos2dx_lib_Cocos2dxGreeRequestDialog_H__
#define __Java_org_cocos2dx_lib_Cocos2dxGreeRequestDialog_H__

#include <string.h>
#include "cocos2d.h"
//#include "cocos-gree-ext.h"

extern "C"
{
	jobject createRequestDialogJni(void);

	void setRequestDialogHandlerJni(jobject obj);
	void setRequestDialogParamsJni(jobject obj, cocos2d::CCDictionary *params);
	void showRequestDialogJni(jobject obj);
}
#endif

