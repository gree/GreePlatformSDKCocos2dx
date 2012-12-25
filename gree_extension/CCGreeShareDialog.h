#ifndef __CC_GREESHAREDIALOG_H__
#define __CC_GREESHAREDIALOG_H__

#include "CCStdC.h"
#include "cocoa/CCString.h"
#include "cocoa/CCDictionary.h"

#include "GreeExtensionMacros.h"

// setParams
#define GD_SHARE_DIALOG_PARAM_KEY_MESSAGE "message"
#define GD_SHARE_DIALOG_PARAM_KEY_IMG     "image"

using namespace std;

NS_CC_GREE_EXT_BEGIN

class CCGreeShareDialog : CCObject {
	public:
		static CCGreeShareDialog* create();
		void setParams(CCDictionary *params);
		void show();

	private:
		CCGreeShareDialog(void* obj);
		void* mShareDialog;
};

NS_CC_GREE_EXT_END

#endif

