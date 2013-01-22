#include "CCGreePlatform.h"

#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreeRequestDialog.h"

using namespace cocos2d;

NS_CC_GREE_EXT_BEGIN

CCGreeRequestDialog::CCGreeRequestDialog(void* obj){
	mRequestDialog = obj;
}

CCGreeRequestDialog* CCGreeRequestDialog::create(){
	jobject obj = createRequestDialogJni();
	CCGreeRequestDialog* dialog = NULL;
	if(obj != NULL){
		dialog = new CCGreeRequestDialog((void*)obj);
		dialog->autorelease();
		dialog->retain();
	}
	return dialog;
}

void CCGreeRequestDialog::setParams(CCDictionary *params){
	if(params != NULL && mRequestDialog != NULL){
		setRequestDialogParamsJni((jobject)mRequestDialog, params);
	}
}

void CCGreeRequestDialog::show(){
	if(mRequestDialog != NULL){
		setRequestDialogHandlerJni((jobject)mRequestDialog, (void*)this);
		showRequestDialogJni((jobject)mRequestDialog);
	}
}

void CCGreeRequestDialog::handleDialogOpened(){
	CCGreeRequestDialogDelegate *delegate = CCGreePlatform::getRequestDialogDelegate();
	if(delegate != NULL){
		delegate->requestDialogOpened(this);
	}
}
void CCGreeRequestDialog::handleDialogCompleted(int count, const char** users){
	CCGreeRequestDialogDelegate *delegate = CCGreePlatform::getRequestDialogDelegate();
	if(delegate != NULL){
		CCArray *userStringArray = new CCArray();
		if(users != NULL){
			for(int i = 0; i < count; i++){
				CCString *str = new CCString(users[i]);
				str->autorelease();
				userStringArray->addObject(str);
			}
		}
		delegate->requestDialogCompleted(this, userStringArray);
	}
}

void CCGreeRequestDialog::handleDialogCanceled(){
	CCGreeRequestDialogDelegate *delegate = CCGreePlatform::getRequestDialogDelegate();
	if(delegate != NULL){
		delegate->requestDialogCanceled(this);
	}
}

NS_CC_GREE_EXT_END




