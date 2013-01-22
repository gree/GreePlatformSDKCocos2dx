#ifndef __CC_GREEINVITEDIALOG_H__
#define __CC_GREEINVITEDIALOG_H__

#include "CCStdC.h"
#include "cocoa/CCString.h"
#include "cocoa/CCDictionary.h"

#include "GreeExtensionMacros.h"

// for setParams
#define GD_INVITE_DIALOG_PARAM_KEY_BODY  "body" // to be set with CCStinrg
#define GD_INVITE_DIALOG_PARAM_KEY_TOUSERID "to_user_id" // to be set with CCArray that is including CCString


using namespace std;

NS_CC_GREE_EXT_BEGIN

class CCGreeInviteDialog;

class CCGreeInviteDialogDelegate {
	public:
		virtual void inviteDialogOpened(CCGreeInviteDialog *dialog){};
		virtual void inviteDialogCompleted(CCGreeInviteDialog *dialog, CCArray *userArray){};
		virtual void inviteDialogClosed(CCGreeInviteDialog *dialog){};
};

class CCGreeInviteDialog : public CCObject {
	public:
		static CCGreeInviteDialog* create();
		void show();
		void setParams(CCDictionary *params);

		void handleDialogOpened();
		void handleDialogCompleted(int count, const char** users);
		void handleDialogClosed();
	private:
		CCGreeInviteDialog(void* obj);
		void* mInviteDialog;
};

NS_CC_GREE_EXT_END

#endif

