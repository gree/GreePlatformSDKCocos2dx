#include "CCDirector.h"

#include "CCGreePlatform.h"
#include "CCGreePayment.h"

#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePlatform.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxGreePayment.h"

using namespace cocos2d;

NS_CC_GREE_EXT_BEGIN

CCGreePaymentItem::CCGreePaymentItem(void* obj){
	mPaymentItemObj = obj;
}


CCGreePaymentItem* CCGreePaymentItem::create(const char *itemId, const char* itemName, double unitPrice, int quantity){
	jobject obj = createPaymentItemJni(itemId, itemName, unitPrice, quantity);
	CCGreePaymentItem* item = NULL;
	if(obj != NULL){
		item = new CCGreePaymentItem((void*)obj);
		item->autorelease();
	}
	return item;
}


void* CCGreePaymentItem::getPaymentItemObject(){
	return mPaymentItemObj;
}


void CCGreePaymentItem::setImageUrl(const char *url){
	if(mPaymentItemObj != NULL){
		setImageUrlJni((jobject)mPaymentItemObj, url);
	}
}

void CCGreePaymentItem::setDescription(const char *desc){
	if(mPaymentItemObj != NULL){
		setDescriptionJni((jobject)mPaymentItemObj, desc);
	}
}

CCString *CCGreePaymentItem::getItemId(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getItemId, mPaymentItemObj);
}

CCString *CCGreePaymentItem::getItemName(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getItemName, mPaymentItemObj);
}
	
double CCGreePaymentItem::getUnitPrice(){
	if(mPaymentItemObj != NULL){
		return getUnitPriceJni((jobject)mPaymentItemObj);
	}
	return -1;
}

int CCGreePaymentItem::getQuantity(){
	CALL_JNI_INT_METHOD_WITHOBJECT(getQuantity, mPaymentItemObj);
}

CCString *CCGreePaymentItem::getImageUrl(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getImageUrl, mPaymentItemObj);
}


CCString *CCGreePaymentItem::getDescription(){
	CALL_JNI_STRING_METHOD_WITHOBJECT(getDescription, mPaymentItemObj);
}





// CCGreePayment
CCGreePayment::CCGreePayment(void* obj){
	mPaymentObj = obj;
}

CCGreePayment* CCGreePayment::create(const char *message, CCArray *items){
	jobject obj = createPaymentJni(message, items);
	CCGreePayment* payment = NULL;
	if(obj != NULL){
		payment = new CCGreePayment((void*)obj);
		payment->autorelease();
		//TODO : Want to remove retain().
		//       But in such case, developer have to issue retain() by himself to use
		//       object outside the function where it has gotten
		//       Furthermore some of current callbacks are including correspoding 
		//       object information and to get them developer also have to issue retain()
		//       not to be automatically released.
		payment->retain();
	}
	return payment;
}

void CCGreePayment::request(){
	//requestJni((jobject)this, mPaymentObj);
	if(mPaymentObj != NULL){
		setPaymentHandlerJni((jobject)mPaymentObj, (void *)this);
		requestWithHandlerJni((jobject)mPaymentObj, (void *)this);
	}
}

void CCGreePayment::setCallbackUrl(const char *url){
	if(mPaymentObj != NULL){
		setCallbackUrlJni((jobject)mPaymentObj, url);
	}
}

void CCGreePayment::verify(const char *paymentId){
	verifyJni(paymentId);
}


void CCGreePayment::handlePaymentRequestOnSuccess(int responseCode, const char* paymentId){
	CCGreePaymentDelegate *delegate = CCGreePlatform::getPaymentDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(paymentId);
		str->autorelease();
		delegate->paymentRequestSuccess(this, responseCode, str);
	}
}
void CCGreePayment::handlePaymentRequestOnCancel(int responseCode, const char* paymentId){
	CCGreePaymentDelegate *delegate = CCGreePlatform::getPaymentDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(paymentId);
		str->autorelease();
		delegate->paymentRequestCancel(this, responseCode, str);
	}
}
void CCGreePayment::handlePaymentRequestOnFailure(int responseCode, const char *paymentId, const char* response){
	CCGreePaymentDelegate *delegate = CCGreePlatform::getPaymentDelegate();
	if(delegate != NULL){
		CCString *str1 = new CCString(paymentId);
		CCString *str2 = new CCString(response);
		str1->autorelease();
		str2->autorelease();
		delegate->paymentRequestFailure(this, responseCode, str1, str2);
	}
}

void CCGreePayment::handlePaymentVerifyOnSuccess(int responseCode, const char* paymentId){
	CCGreePaymentDelegate *delegate = CCGreePlatform::getPaymentDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(paymentId);
		str->autorelease();
		delegate->paymentVerifySuccess(responseCode, str);
	}
}
void CCGreePayment::handlePaymentVerifyOnCancel(int responseCode, const char* paymentId){
	CCGreePaymentDelegate *delegate = CCGreePlatform::getPaymentDelegate();
	if(delegate != NULL){
		CCString *str = new CCString(paymentId);
		str->autorelease();
		delegate->paymentVerifyCancel(responseCode, str);
	}
}
void CCGreePayment::handlePaymentVerifyOnFailure(int responseCode, const char *paymentId, const char* response){
	CCGreePaymentDelegate *delegate = CCGreePlatform::getPaymentDelegate();
	if(delegate != NULL){
		CCString *str1 = new CCString(paymentId);
		CCString *str2 = new CCString(response);
		str1->autorelease();
		str2->autorelease();
		delegate->paymentVerifyFailure(responseCode, str1, str2);
	}
}

NS_CC_GREE_EXT_END




