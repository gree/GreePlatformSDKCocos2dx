#include "CCGreePlatform.h"

using namespace cocos2d;

NS_CC_GREE_EXT_BEGIN

CCGreeRequestDialog::CCGreeRequestDialog(jobject obj){
	mRequestDialog = obj;
}

CCGreeRequestDialog* CCGreeRequestDialog::create(){
	jobject obj = createRequestDialogJni();
	CCGreeRequestDialog* dialog = NULL;
	if(obj != NULL){
		dialog = new CCGreeRequestDialog(obj);
		dialog->autorelease();
	}
	return dialog;
}

void CCGreeRequestDialog::setParams(CCDictionary *params){
	if(params != NULL && mRequestDialog != NULL){
		setRequestDialogParamsJni(mRequestDialog, params);
	}
}


void CCGreeRequestDialog::show(){
	if(mRequestDialog != NULL){
		setRequestDialogHandlerJni(mRequestDialog);
		showRequestDialogJni(mRequestDialog);
	}
}


NS_CC_GREE_EXT_END




