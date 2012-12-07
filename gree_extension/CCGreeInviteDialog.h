#ifndef __CC_GREEINVITEDIALOG_H__
#define __CC_GREEINVITEDIALOG_H__

#include <map>

#include "CCStdC.h"
#include "cocoa/CCString.h"
#include "cocoa/CCDictionary.h"

#include "cocos-gree-ext.h"

// for setParams
#define GD_INVITE_DIALOG_PARAM_KEY_BODY  "body"
#define GD_INVITE_DIALOG_PARAM_KEY_TOUSERID "to_user_id"


using namespace std;

NS_CC_GREE_EXT_BEGIN

class CCGreeInviteDialog : CCObject {
	public:
		static CCGreeInviteDialog* create();
		void show();
		void setParams(CCDictionary *params);

	private:
		CCGreeInviteDialog(jobject obj);
		jobject mInviteDialog;
};

NS_CC_GREE_EXT_END

#endif

