#ifndef __CC_GREESHAREDIALOG_H__
#define __CC_GREESHAREDIALOG_H__

#include "CCStdC.h"
#include "cocoa/CCString.h"
#include "cocoa/CCDictionary.h"

#include "GreeExtensionMacros.h"

// setParams
#define GD_SHARE_DIALOG_PARAM_KEY_MESSAGE "message" // to be set with CCString
#define GD_SHARE_DIALOG_PARAM_KEY_IMG     "image" // to be set with CCImage

using namespace std;

NS_CC_GREE_EXT_BEGIN

class CCGreeShareDialog;

class CCGreeShareDialogDelegate {
	public:
		virtual void shareDialogOpened(CCGreeShareDialog *dialog){};
		virtual void shareDialogCompleted(CCGreeShareDialog *dialog, CCArray *userArray){};
		virtual void shareDialogClosed(CCGreeShareDialog *dialog){};
};

class CCGreeShareDialog : public CCObject {
	public:
		static CCGreeShareDialog* create();
		void setParams(CCDictionary *params);
		void show();

		void handleDialogOpened();
		void handleDialogCompleted(int count, const char** users);
		void handleDialogClosed();
	private:
		CCGreeShareDialog(void* obj);
		void* mShareDialog;
};

NS_CC_GREE_EXT_END

#endif

