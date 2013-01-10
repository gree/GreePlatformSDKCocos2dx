#ifndef __CC_GREEINVITEDIALOG_H__
#define __CC_GREEINVITEDIALOG_H__

#include "CCStdC.h"
#include "cocoa/CCString.h"
#include "cocoa/CCDictionary.h"

#include "GreeExtensionMacros.h"

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
		CCGreeInviteDialog(void* obj);
		void* mInviteDialog;
};

NS_CC_GREE_EXT_END

#endif

