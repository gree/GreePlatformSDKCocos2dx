#include "CCGreePlatform.h"

using namespace cocos2d;

NS_CC_GREE_EXT_BEGIN

CCGreeShareDialog::CCGreeShareDialog(jobject obj){
	mShareDialog = obj;
}

CCGreeShareDialog* CCGreeShareDialog::create(){
	jobject obj = createShareDialogJni();
	CCGreeShareDialog* dialog = NULL;
	if(obj != NULL){
		dialog = new CCGreeShareDialog(obj);
		dialog->autorelease();
	}
	return dialog;
}

void CCGreeShareDialog::setParams(CCDictionary *params){
	if(params != NULL && mShareDialog != NULL){
		setShareDialogParamsJni(mShareDialog, params);
	}
}


void CCGreeShareDialog::show(){
	if(mShareDialog != NULL){
		setShareDialogHandlerJni(mShareDialog);
		showShareDialogJni(mShareDialog);
	}
}


NS_CC_GREE_EXT_END




