#include "CCGreePlatform.h"

#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreeInviteDialog.h"

using namespace cocos2d;

NS_CC_GREE_EXT_BEGIN

CCGreeInviteDialog::CCGreeInviteDialog(void* obj){
	mInviteDialog = obj;
}

CCGreeInviteDialog* CCGreeInviteDialog::create(){
	jobject obj = createInviteDialogJni();
	CCGreeInviteDialog* dialog = NULL;
	if(obj != NULL){
		dialog = new CCGreeInviteDialog((void*)obj);
		dialog->autorelease();
	}
	return dialog;
}

void CCGreeInviteDialog::setParams(CCDictionary *params){
	if(params != NULL && mInviteDialog != NULL){
		setInviteDialogParamsJni((jobject)mInviteDialog, params);
	}
}

void CCGreeInviteDialog::show(){
	if(mInviteDialog != NULL){
		setInviteDialogHandlerJni((jobject)mInviteDialog);
		showInviteDialogJni((jobject)mInviteDialog);
	}
}

NS_CC_GREE_EXT_END




