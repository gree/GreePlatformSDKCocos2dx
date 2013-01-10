#include "CCGreePlatform.h"

#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreeShareDialog.h"

using namespace cocos2d;

NS_CC_GREE_EXT_BEGIN

CCGreeShareDialog::CCGreeShareDialog(void* obj){
	mShareDialog = obj;
}

CCGreeShareDialog* CCGreeShareDialog::create(){
	jobject obj = createShareDialogJni();
	CCGreeShareDialog* dialog = NULL;
	if(obj != NULL){
		dialog = new CCGreeShareDialog((jobject)obj);
		dialog->autorelease();
	}
	return dialog;
}

void CCGreeShareDialog::setParams(CCDictionary *params){
	if(params != NULL && mShareDialog != NULL){
		setShareDialogParamsJni((jobject)mShareDialog, params);
	}
}


void CCGreeShareDialog::show(){
	if(mShareDialog != NULL){
		setShareDialogHandlerJni((jobject)mShareDialog);
		showShareDialogJni((jobject)mShareDialog);
	}
}


NS_CC_GREE_EXT_END




