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
		setRequestDialogHandlerJni((jobject)mRequestDialog);
		showRequestDialogJni((jobject)mRequestDialog);
	}
}


NS_CC_GREE_EXT_END




