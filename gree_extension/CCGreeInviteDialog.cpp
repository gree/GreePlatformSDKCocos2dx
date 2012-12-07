#include "CCGreePlatform.h"

using namespace cocos2d;

NS_CC_GREE_EXT_BEGIN

CCGreeInviteDialog::CCGreeInviteDialog(jobject obj){
	mInviteDialog = obj;
}

CCGreeInviteDialog* CCGreeInviteDialog::create(){
	jobject obj = createInviteDialogJni();
	CCGreeInviteDialog* dialog = NULL;
	if(obj != NULL){
		dialog = new CCGreeInviteDialog(obj);
		dialog->autorelease();
	}
	return dialog;
}

void CCGreeInviteDialog::setParams(CCDictionary *params){
	if(params != NULL && mInviteDialog != NULL){
		setInviteDialogParamsJni(mInviteDialog, params);
	}
}

void CCGreeInviteDialog::show(){
	if(mInviteDialog != NULL){
		setInviteDialogHandlerJni(mInviteDialog);
		showInviteDialogJni(mInviteDialog);
	}
}

NS_CC_GREE_EXT_END




