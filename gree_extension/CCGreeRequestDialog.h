#ifndef __CC_GREEREQUESTDIALOG_H__
#define __CC_GREEREQUESTDIALOG_H__

#include "CCStdC.h"
#include "cocoa/CCString.h"
#include "cocoa/CCDictionary.h"

#include "GreeExtensionMacros.h"

// setParams
#define GD_REQUEST_DIALOG_PARAM_KEY_TITLE "title"
#define GD_REQUEST_DIALOG_PARAM_KEY_BODY  "body"
#define GD_REQUEST_DIALOG_PARAM_KEY_LISTTYPE "list_type"
#define GD_REQUEST_DIALOG_PARAM_KEY_TOUSERID "to_user_id"
#define GD_REQUEST_DIALOG_PARAM_KEY_EXPIRETIME "expire_time"
#define GD_REQUEST_DIALOG_PARAM_KEY_ATTRS "attrs"

using namespace std;

NS_CC_GREE_EXT_BEGIN

class CCGreeRequestDialog : CCObject {
	public:
		static CCGreeRequestDialog* create();
		void setParams(CCDictionary *params);
		void show();

	private:
		CCGreeRequestDialog(void* obj);
		void* mRequestDialog;
};

NS_CC_GREE_EXT_END

#endif

