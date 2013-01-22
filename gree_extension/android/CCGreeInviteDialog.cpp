#include "CCGreePlatform.h"

//#include "jni/JniHelper.h"
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
		dialog->retain();
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
		setInviteDialogHandlerJni((jobject)mInviteDialog, (void*)this);
		showInviteDialogJni((jobject)mInviteDialog);
	}
}

void CCGreeInviteDialog::handleDialogOpened(){
	CCGreeInviteDialogDelegate *delegate = CCGreePlatform::getInviteDialogDelegate();
	if(delegate != NULL){
		delegate->inviteDialogOpened(this);
	}
}

void CCGreeInviteDialog::handleDialogCompleted(int count, const char** users){
	CCGreeInviteDialogDelegate *delegate = CCGreePlatform::getInviteDialogDelegate();
	if(delegate != NULL){
		CCArray *userStringArray = new CCArray();
		if(users != NULL){
			for(int i = 0; i < count; i++){
				CCString *str = new CCString(users[i]);
				str->autorelease();
				userStringArray->addObject(str);
			}
		}
		delegate->inviteDialogCompleted(this, userStringArray);
	}
}

void CCGreeInviteDialog::handleDialogCanceled(){
	CCGreeInviteDialogDelegate *delegate = CCGreePlatform::getInviteDialogDelegate();
	if(delegate != NULL){
		delegate->inviteDialogCanceled(this);
	}
}

NS_CC_GREE_EXT_END




