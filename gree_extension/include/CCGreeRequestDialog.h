#ifndef __CC_GREEREQUESTDIALOG_H__
#define __CC_GREEREQUESTDIALOG_H__

#include "CCStdC.h"
#include "cocoa/CCString.h"
#include "cocoa/CCDictionary.h"

#include "GreeExtensionMacros.h"

// setParams
#define GD_REQUEST_DIALOG_PARAM_KEY_TITLE "title" // to be set with CCString
#define GD_REQUEST_DIALOG_PARAM_KEY_BODY  "body"  // to be set with CCString
#define GD_REQUEST_DIALOG_PARAM_KEY_LISTTYPE "list_type" // to be set with CCString including GD_REQUEST_DIALOG_PARAM_KEY_LISTTYPE_ALL, GD_REQUEST_DIALOG_PARAM_KEY_LISTTYPE_JOINED, GD_REQUEST_DIALOG_PARAM_KEY_LISTTYPE_SPECIFIED
#define GD_REQUEST_DIALOG_PARAM_KEY_LISTTYPE_ALL       "all"
#define GD_REQUEST_DIALOG_PARAM_KEY_LISTTYPE_JOINED    "joined"
#define GD_REQUEST_DIALOG_PARAM_KEY_LISTTYPE_SPECIFIED "specified"
#define GD_REQUEST_DIALOG_PARAM_KEY_TOUSERID "to_user_id"  // to be set with CCArray that is including CCString
#define GD_REQUEST_DIALOG_PARAM_KEY_EXPIRETIME "expire_time" // to be set with CCString
#define GD_REQUEST_DIALOG_PARAM_KEY_ATTRS "attrs" // to be set with CCDictionary

using namespace std;

NS_CC_GREE_EXT_BEGIN

class CCGreeRequestDialog;

class CCGreeRequestDialogDelegate {
	public:
		virtual void requestDialogOpened(CCGreeRequestDialog *dialog){};
		virtual void requestDialogCompleted(CCGreeRequestDialog *dialog, CCArray *userArray){};
		virtual void requestDialogClosed(CCGreeRequestDialog *dialog){};
};

class CCGreeRequestDialog : public CCObject {
	public:
		static CCGreeRequestDialog* create();
		void setParams(CCDictionary *params);
		void show();

		void handleDialogOpened();
		void handleDialogCompleted(int count, const char** users);
		void handleDialogClosed();
	private:
		CCGreeRequestDialog(void* obj);
		void* mRequestDialog;
};

NS_CC_GREE_EXT_END

#endif

