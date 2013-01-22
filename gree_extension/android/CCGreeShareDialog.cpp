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
		dialog->retain();
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
		setShareDialogHandlerJni((jobject)mShareDialog, (void*)this);
		showShareDialogJni((jobject)mShareDialog);
	}
}

void CCGreeShareDialog::handleDialogOpened(){
	CCGreeShareDialogDelegate *delegate = CCGreePlatform::getShareDialogDelegate();
	if(delegate != NULL){
		delegate->shareDialogOpened(this);
	}
}

void CCGreeShareDialog::handleDialogCompleted(int count, const char** users){
	CCGreeShareDialogDelegate *delegate = CCGreePlatform::getShareDialogDelegate();
	if(delegate != NULL){
		CCArray *userStringArray = new CCArray();
		if(users != NULL){
			for(int i = 0; i < count; i++){
				CCString *str = new CCString(users[i]);
				str->autorelease();
				userStringArray->addObject(str);
			}
		}
		delegate->shareDialogCompleted(this, userStringArray);
	}
}

void CCGreeShareDialog::handleDialogCanceled(){
	CCGreeShareDialogDelegate *delegate = CCGreePlatform::getShareDialogDelegate();
	if(delegate != NULL){
		delegate->shareDialogCanceled(this);
	}
}

NS_CC_GREE_EXT_END




